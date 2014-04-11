#pragma once

#include <vector>

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
    *k = reflect_;
    Vector3D new_dir = direction - 2 * Vector3D::dot(direction, normal) / normal.len() / direction.len() * normal;
    *ray = Ray(hit_point, new_dir);

    Vector3D hit;
    for (auto ls : scene.lights_) {
      Vector3D dir = ls.position - hit_point;
      bool hitted = scene.castRay(Ray(hit_point, dir), &hit, nullptr, nullptr);
      if (!hitted || Vector3D::dot(hit_point - hit, ls.position - hit) > EPS) {
        Vector3D dc = ls.intensity / Vector3D::dot(ls.position - hit_point, ls.position - hit_point) * diffuse_ * std::max(0.0, Vector3D::dot(dir.normalized(), normal.normalized()));
        *color = *color + dc;
      }
    }
  }

 private:
  static constexpr double EPS = 1e-5;

  Vector3D reflectionK(
      const Vector3D &direction,
      const Vector3D &normal,
      double cos_i,
      double cos_t) {

  }

  Vector3D diffuse_;
  Vector3D reflect_;
  Vector3D snell_;
};
