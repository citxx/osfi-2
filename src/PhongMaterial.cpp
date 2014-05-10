#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "PhongMaterial.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Spectrum.hpp"
#include "Vector3D.hpp"
#include "defs.hpp"

PhongMaterial::PhongMaterial(
    const Vector3D &specular,
    double k): specular_(specular), k_(k) {}

double PhongMaterial::brdf(
    const Vector3D &dir_in,
    const Vector3D &normal,
    const Vector3D &dir_out) const {
  Vector3D reflected = dir_in.reflect(normal);
  return Vector3D::dot(-dir_in, normal) *
      pow(std::max(0.0, Vector3D::dot(reflected, dir_out)), k_) / 2.0 / PI * (k_ + 1);
}

double PhongMaterial::pdf(
    const Vector3D &dir_in,
    const Vector3D &normal,
    const Vector3D &dir_out) const {
  Vector3D reflected = dir_in.reflect(normal);
  return Vector3D::dot(-dir_in, normal) *
      pow(std::max(0.0, Vector3D::dot(reflected, dir_out)), k_) * 0.35 / PI / Vector3D::dot(normal, dir_out) * k_;
}

void PhongMaterial::shade(
    const Scene &scene,
    const Vector3D &direction,
    const Vector3D &hit_point,
    const Vector3D &normal,
    Vector3D *color,
    Vector3D *k,
    Ray *ray) const {
  *color = Vector3D();
  *k = Vector3D();

  double p11 = 0.0, p12 = 0.0, p21 = 0.0, p22 = 0.0;
  Vector3D f1, f2;

  // Primary
  auto light = scene.lights()[rand() % scene.lights().size()];

  Vector3D hit;
  Vector3D position;
  Vector3D intensity = light->intensity(hit_point, &position);
  if (std::isnan(intensity.x) || std::isnan(intensity.y) || std::isnan(intensity.z)) {
    std::cerr << "Intensity is " << intensity << std::endl;
  }
  Vector3D light_dir = (position - hit_point).normalized();
  if (ray != nullptr) *ray = Ray(hit_point, light_dir);
  bool hitted = scene.castRay(Ray(hit_point, light_dir), &hit, nullptr, nullptr);
  if (hitted && Vector3D::dot(hit_point - hit, position - hit) > -1e-6) {
     p12 = pdf(-light_dir, normal, -direction);
     p11 = light->density(hit_point);
     f1 = intensity * specular_ * brdf(-light_dir, normal, -direction);
  }


  if (std::isnan(f1.x) || std::isnan(f1.y) || std::isnan(f1.z)) {
    std::cerr << "Diffuse f1 is " << f1 << std::endl;
  }

  // Secondary

  double phi =  2 * PI * rand() / RAND_MAX;
  double psi, y;
  do {
    psi = 0.5 * PI * rand() / RAND_MAX;
    y = 1.0 * rand() / RAND_MAX;
  } while (pow(cos(psi), k_) > y);

  Vector3D reflected_r = direction.reflect(normal).normalized();

  Vector3D u = reflected_r.orthogonal().normalized();
  Vector3D v = Vector3D::cross(reflected_r, u);
  
  Vector3D specular_r =
    sin(psi) * reflected_r +
    cos(psi) * sin(phi) * u +
    cos(psi) * cos(phi) * v;

  p22 = pdf(-specular_r, normal, -direction);

  f2 = specular_ * brdf(-specular_r, normal, -direction);  // TODO: check
  *ray = Ray(hit_point, specular_r);
  Scene::ObjectType where_type;
  scene.castRay(*ray, nullptr, nullptr, nullptr, &where_type);
  if (where_type == Scene::ObjectType::Light) {
    p21 = light->density(hit_point);
  }

  if (p11 + p12 > 1e-6) {
    *color = f1 / (p11 + p12);
  }
  *k = f2 / (p21 + p22);
/*  std::cerr << "==========================================================================" << std::endl;*/
  //std::cerr << f1 << "\t" << f2 << std::endl;
  //std::cerr << p11 << "\t" << p12 << "\t" << p21 << "\t" << p22 << std::endl;
  //std::cerr << *color << "\t" << *k << std::endl;

}
