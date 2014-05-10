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

class WardAnisotropicMaterial: public AbstractMaterial {
 public:
  WardAnisotropicMaterial(
      const Vector3D &color,
      double c_x,
      double c_y);

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
  double ward(
      const Vector3D &normal,
      const Vector3D &direction,
      const Vector3D &reflected,
      const Vector3D &h,
      const Vector3D &x,
      const Vector3D &y) const;

  Vector3D color_;
  double c_x_, c_y_;
};
