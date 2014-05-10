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

class PhongMaterial: public AbstractMaterial {
 public:
  PhongMaterial(
      const Vector3D &specular,
      double k);

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

 private:
  Vector3D specular_;
  double k_;
};
