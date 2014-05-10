#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "SpecularMaterial.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Spectrum.hpp"
#include "Vector3D.hpp"
#include "defs.hpp"

SpecularMaterial::SpecularMaterial(
    const Vector3D &reflect,
    const Vector3D &snell): reflect_(reflect), snell_(snell) {}

void SpecularMaterial::shade(
    const Scene &scene,
    const Vector3D &direction,
    const Vector3D &hit_point,
    const Vector3D &normal,
    Vector3D *color,
    Vector3D *k,
    Ray *ray) const {
  *color = Vector3D();

  double refl_f = reflectionF(direction, normal, snell_[0]);
  double refr_f = 1.0 - refl_f;

  if (std::isnan(refl_f)) std::cerr << "refl_f is NaN" << std::endl;

  double reflection_p = Vector3D::dot(refl_f * reflect_, Vector3D(1.0, 1.0, 1.0)) / 3.0;
  double refraction_p = Vector3D::dot(refr_f * reflect_, Vector3D(1.0, 1.0, 1.0)) / 3.0;
  double total_p = reflection_p + refraction_p;

  double dice = total_p * rand() / RAND_MAX;
  if (dice < reflection_p) {  // Reflection
    *k = refl_f * reflect_;
    Vector3D new_dir = direction.reflect(normal);
    *ray = Ray(hit_point, new_dir);
  } else {  // Refraction
    *k = refr_f * reflect_;
    Vector3D new_dir = direction.refract(normal, snell_[0]);
    *ray = Ray(hit_point, new_dir);
  }
}

double SpecularMaterial::reflectionF(
    const Vector3D &direction,
    const Vector3D &normal,
    double n) {
  if (Vector3D::dot(direction, normal) > 0) {
    n = 1.0 / n;
  }

  // Unfortunately c++ doesn't able to compute limit (n -> inf)
  if (n == INFINITY) {
    n = 1e20;
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
