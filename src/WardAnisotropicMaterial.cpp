#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "WardAnisotropicMaterial.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Spectrum.hpp"
#include "Vector3D.hpp"
#include "defs.hpp"

WardAnisotropicMaterial::WardAnisotropicMaterial(
    const Vector3D &color,
    double c_x,
    double c_y): color_(color), c_x_(c_x), c_y_(c_y) {}

double WardAnisotropicMaterial::brdf(
    const Vector3D &dir_in,
    const Vector3D &normal,
    const Vector3D &dir_out) const {
  Vector3D x = Vector3D::cross(normal, Vector3D(0.0, 0.0, 1.0)).normalized();
  Vector3D y = Vector3D::cross(normal, x);
  Vector3D h = (dir_out - dir_in).normalized();

  return Vector3D::dot(-dir_in, normal) * ward(normal, -dir_out, -dir_in, h, x, y);
}

double WardAnisotropicMaterial::pdf(
    const Vector3D &dir_in,
    const Vector3D &normal,
    const Vector3D &dir_out) const {
  Vector3D x = Vector3D::cross(normal, Vector3D(0.0, 0.0, 1.0)).normalized();
  Vector3D y = Vector3D::cross(normal, x);
  Vector3D h = (dir_out - dir_in).normalized();

  return Vector3D::dot(-dir_in, normal) * ward(normal, -dir_out, -dir_in, h, x, y) * 2.0;
}

void WardAnisotropicMaterial::shade(
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
  //
  Vector3D hit;
  auto light = scene.lights()[rand() % scene.lights().size()];
  Vector3D position;
  Vector3D intensity = light->intensity(hit_point, &position);
  if (std::isnan(intensity.x) || std::isnan(intensity.y) || std::isnan(intensity.z)) {
    std::cerr << "Intensity is " << intensity << std::endl;
  }
  Vector3D light_dir = (position - hit_point).normalized();
  if (ray != nullptr) *ray = Ray(hit_point, light_dir);
  bool hitted = scene.castRay(Ray(hit_point, light_dir), &hit, nullptr, nullptr);
  if (hitted && Vector3D::dot(hit_point - hit, position - hit) > -1e-6) {
    double w = brdf(-light_dir, normal, -direction.normalized());
    p11 = light->density(hit_point);
    p12 = pdf(-light_dir, normal, -direction.normalized());
    f1 = intensity * color_ * w;
  }

  // Secondary

  Vector3D x = Vector3D::cross(normal, Vector3D(0.0, 0.0, 1.0)).normalized();
  Vector3D y = Vector3D::cross(normal, x);

  double sigma_x = c_x_ / 2.0, sigma_y = c_y_ / 2.0;
  double cos_nr = Vector3D::dot(normal, -direction);
  double sqrt_cos_nr = sqrt(cos_nr);

  double p, r;
  Vector3D reflected, h;
  do {
    double normal_x, normal_y, phi, cos_psi, sin_psi;
    do {
      double u, v, s;
      do {
        u = 1.0 * rand() / RAND_MAX;
        v = 1.0 * rand() / RAND_MAX;
        s = u * u + v * v;
      } while (s > 1.0);
      double ss = sqrt(-2 * log(s) / s);
      normal_x = u * ss * sigma_x;
      normal_y = v * ss * sigma_y;
      phi = atan2(normal_x, normal_y);
      cos_psi = sqrt(normal_x * normal_x + normal_y * normal_y);
      sin_psi = sqrt(1.0 - normal_x * normal_x - normal_y * normal_y);
    } while (std::abs(cos_psi) > 1.0);
    double hx = cos_psi * sin(phi);
    double hy = cos_psi * cos(phi);
    double hn = sin_psi;
    double r_exp = exp(-2.0 * (hx * hx / c_x_ / c_x_ + hy * hy / c_y_ / c_y_));
    r = r_exp / sqrt_cos_nr / 4.0 / PI / c_x_ / c_y_ * rand() / RAND_MAX;
    h = hx * x + hy * y + hn * normal;
    reflected = 2 * Vector3D::dot(-direction, h) * h + direction;
    p = ward(normal, direction, reflected, h, x, y);
    //std::cerr << reflected << "\t| " << " " << normal_x << " " << normal_y << " " << phi << " " << cos_psi << " " << sin_psi << " " << hx << " " << hy << " " << hn << std::endl;
  } while (r > p);

  f2 = color_ * brdf(-reflected, normal, -direction);  // TODO: check
  p22 = pdf(-reflected, normal, -direction);
  *ray = Ray(hit_point, reflected);
  Scene::ObjectType where_type;
  scene.castRay(*ray, nullptr, nullptr, nullptr, &where_type);
  if (where_type == Scene::ObjectType::Light) {
    p21 = light->density(hit_point);
  }

  if (p11 + p12 > 1e-6) {
    *color = f1 / (p11 + p12);
  }
  *k = f2 / (p21 + p22);
}

double WardAnisotropicMaterial::ward(
    const Vector3D &normal,
    const Vector3D &direction,
    const Vector3D &reflected,
    const Vector3D &h,
    const Vector3D &x,
    const Vector3D &y) const {
  double cos_nl = Vector3D::dot(normal, reflected);
  double cos_nr = Vector3D::dot(normal, -direction);
  if (cos_nl < 1e-6 || cos_nr < 1e-6) {
    return 0.0;
  } else {
    double cos_hx = Vector3D::dot(h, x);
    double cos_hy = Vector3D::dot(h, y);
    double cos_hn = Vector3D::dot(h, normal);
    double wx = cos_hx / c_x_;
    double wy = cos_hy / c_y_;
    double result =  cos_nl * exp(-2 * (wx * wx + wy * wy) /
        (1 + cos_hn)) / sqrt(cos_nl * cos_nr) / 4.0 / PI / c_x_ / c_y_;
    return result;
  }
}

