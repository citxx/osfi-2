#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "LambertMaterial.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Spectrum.hpp"
#include "Vector3D.hpp"
#include "defs.hpp"

LambertMaterial::LambertMaterial(const Vector3D &diffuse): diffuse_(diffuse) {}

double LambertMaterial::brdf(
    const Vector3D &dir_in,
    const Vector3D &normal,
    const Vector3D &dir_out) const {
  return std::max(0.0, Vector3D::dot(-dir_in, normal)) / 2.0 / PI;
}

double LambertMaterial::pdf(
    const Vector3D &dir_in,
    const Vector3D &normal,
    const Vector3D &dir_out) const {
  return std::max(0.0, Vector3D::dot(-dir_in, normal)) / PI;
}

void LambertMaterial::shade(
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
  Vector3D light_position;
  Vector3D intensity = light->intensity(hit_point, &light_position);
  Vector3D light_dir = (light_position - hit_point).normalized();
  bool hitted = scene.castRay(Ray(hit_point, light_dir), &hit, nullptr, nullptr);
  double l_over_e = brdf(-light_dir, normal, -direction);
  if (hitted && Vector3D::dot(hit_point - hit, light_position - hit) > -1e-6) {
    p12 = pdf(-light_dir, normal, -direction);
    p11 = light->density(hit_point);
    f1 = intensity * diffuse_ * l_over_e;
  }


  // Secondary
  double phi = 2 * PI * rand() / RAND_MAX;
  double psi, y;
  do {
    psi = 0.5 * PI * rand() / RAND_MAX;
    y = 1.0 * rand() / RAND_MAX;
  } while (cos(psi) > y);

  Vector3D u = normal.orthogonal().normalized();
  Vector3D v = Vector3D::cross(normal, u);
  
  Vector3D diffuse_r =
    sin(psi) * normal +
    cos(psi) * sin(phi) * u +
    cos(psi) * cos(phi) * v;

  double l_over_e_2 = brdf(-diffuse_r, normal, -direction);
  //std::cerr << "brdf(" << -diffuse_r << ", " << normal << ", " << -direction << ")" << std::endl;
  p22 = pdf(-diffuse_r, normal, -direction);

  f2 = diffuse_ * l_over_e_2;  // TODO: check
  *ray = Ray(hit_point, diffuse_r);
  Scene::ObjectType where_type;
  scene.castRay(*ray, nullptr, nullptr, nullptr, &where_type);
  if (where_type == Scene::ObjectType::Light) {
    p21 = light->density(hit_point);
  }

  if (p11 + p12 > 1e-6) {
    *color = f1 / (p11 + p12);
  }
  *k = f2 / (p21 + p22);
  if (color->len() > 1.0) {
    std::cerr << "==========================================================================" << std::endl;
    std::cerr << f1 << "\t" << f2 << std::endl;
    std::cerr << p11 << "\t" << p12 << "\t" << p21 << "\t" << p22 << std::endl;
    std::cerr << *color << "\t" << *k << std::endl;
    std::cerr << l_over_e << "\t" << l_over_e_2 << std::endl;
  }
}
