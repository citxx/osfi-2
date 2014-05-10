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

class SpecularMaterial: public AbstractMaterial {
 public:
  explicit SpecularMaterial(
      const Vector3D &reflect = Vector3D(),
      const Vector3D &snell = Vector3D());

  virtual void shade(
      const Scene &scene,
      const Vector3D &direction,
      const Vector3D &hit_point,
      const Vector3D &normal,
      Vector3D *color,
      Vector3D *k,
      Ray *ray) const;

 private:
  static double reflectionF(
      const Vector3D &direction,
      const Vector3D &normal,
      double n);

  Vector3D reflect_;
  Vector3D snell_;
};
