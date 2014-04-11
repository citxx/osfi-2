#pragma once

#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "Ray.hpp"
#include "Scene.hpp"
#include "Vector3D.hpp"

class Material {
 public:
  explicit Material(
      const Vector3D &diffuse = Vector3D(),
      const Vector3D &reflect = Vector3D(),
      const Vector3D &snell = Vector3D()):
    diffuse_(diffuse), reflect_(reflect), snell_(snell) {}

  void shade(
      const Scene &scene,
      const Vector3D &direction,
      const Vector3D &hit_point,
      const Vector3D &normal,
      Vector3D *color,
      Vector3D *k,
      Ray *ray) {
    *color = Vector3D();

    // Diffuse
    Vector3D hit;
    double lights_number = 0.0;
    for (auto ls : scene.lights_) {
      Vector3D dir = ls.position - hit_point;
      bool hitted = scene.castRay(Ray(hit_point, dir), &hit, nullptr, nullptr);
      if (!hitted || Vector3D::dot(hit_point - hit, ls.position - hit) > EPS) {
        lights_number += 1.0;
        Vector3D dc = ls.intensity / Vector3D::dot(ls.position - hit_point, ls.position - hit_point) * diffuse_ * std::max(0.0, Vector3D::dot(dir.normalized(), normal.normalized()));
        *color = *color + dc;
      }
    }

    // Ref**ction
    double refl_f = reflectionF(direction, normal);
    double refr_f = 1.0 - refl_f;

    double reflection_p = Vector3D::dot(refl_f * reflect_, Vector3D(1.0, 1.0, 1.0)) / 3.0;
    double refraction_p = Vector3D::dot(refr_f * reflect_, Vector3D(1.0, 1.0, 1.0)) / 3.0;
    double diffuse_p = Vector3D::dot(diffuse_, Vector3D(1.0, 1.0, 1.0)) / 3.0;
    double total_p = reflection_p + refraction_p + diffuse_p;

    double dice = total_p * rand() / RAND_MAX;
    if (dice < diffuse_p) {  // Diffuse
      // TODO: diffuse reflection
      *color = *color * (total_p + lights_number) / (diffuse_p + lights_number);
      *k = Vector3D();
    } else if (dice < diffuse_p + reflection_p) {  // Reflection
      *k = refl_f * reflect_;
      Vector3D new_dir = reflectedDirection(direction, normal);
      *ray = Ray(hit_point, new_dir);
      *color = *color * (total_p + lights_number) / (reflection_p + lights_number);
    } else {  // Refraction
      *k = refr_f * reflect_;
      Vector3D new_dir = refractedDirection(direction, normal);
      *ray = Ray(hit_point, new_dir);
      *color = *color * (total_p + lights_number) / (refraction_p + lights_number);
    }
  }

 private:
  static constexpr double EPS = 1e-5;

  Vector3D refractedDirection(
      const Vector3D &direction,
      const Vector3D &normal) {
    double n = snell_[0];
    if (Vector3D::dot(direction, normal) > 0) {
      n = 1.0 / snell_[0];
    }

    double cos_s = fabs(Vector3D::dot(direction, normal) / direction.len() / normal.len());
    Vector3D true_normal = - (Vector3D::dot(direction, normal) * normal).normalized();
    Vector3D result = direction / n + (cos_s / n - sqrt(1 - (1 - cos_s * cos_s) / n / n)) * true_normal;
    //std::cerr << "direction = " << direction << std::endl;
    //std::cerr << "normal = " << normal << std::endl;
    //std::cerr << "n = " << n << std::endl;
    //std::cerr << "cos_s = " << cos_s << std::endl;
    //std::cerr << "true_normal = " << true_normal << std::endl;
    //std::cerr << "result = " << result << std::endl;
    //std::cerr << std::endl;
    return result;
  }


  Vector3D reflectedDirection(
      const Vector3D &direction,
      const Vector3D &normal) {
    return direction - 2 * Vector3D::dot(direction, normal) / normal.len() / direction.len() * normal;
  }

  double reflectionF(
      const Vector3D &direction,
      const Vector3D &normal) {
    double n = snell_[0];
    if (Vector3D::dot(direction, normal) > 0) {
      n = 1.0 / snell_[0];
    }

    double cos_s = fabs(Vector3D::dot(direction, normal) / direction.len() / normal.len());
    double sin_s = sqrt(1.0 - cos_s * cos_s);
    double sin_r = sin_s / n;
    if (sin_r > 1.0) return 1.0;
    double cos_r = sqrt(1.0 - sin_r * sin_r);

    double r_s = (cos_s - n * cos_r) / (cos_s + n * cos_r);
    double r_p = (n * cos_s - cos_r) / (n * cos_s + cos_r);

    return (r_s * r_s + r_p * r_p) * 0.5;
  }

  Vector3D diffuse_;
  Vector3D reflect_;
  Vector3D snell_;
};
