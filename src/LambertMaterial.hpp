#pragma once

#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "AbstractMaterial.hpp"
#include "defs.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Spectrum.hpp"
#include "Vector3D.hpp"

class LambertMaterial: public AbstractMaterial {
 public:
  explicit LambertMaterial(const Vector3D &diffuse = Vector3D());

  double brdf(
      const Vector3D &dir_in,
      const Vector3D &normal,
      const Vector3D &dir_out) const;

  double pdf(
      const Vector3D &dir_in,
      const Vector3D &normal,
      const Vector3D &dir_out) const;

  virtual void shade(
      const Scene &scene,
      const Vector3D &direction,
      const Vector3D &hit_point,
      const Vector3D &normal,
      Vector3D *color,
      Vector3D *k,
      Ray *ray) const;

  static const double BRDF_K;
 private:
  Vector3D diffuse_;
};
