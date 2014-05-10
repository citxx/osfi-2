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

class LightMaterial: public AbstractMaterial {
 public:
  LightMaterial(const Vector3D &luminocity);

  virtual void shade(
      const Scene &scene,
      const Vector3D &direction,
      const Vector3D &hit_point,
      const Vector3D &normal,
      Vector3D *color,
      Vector3D *k,
      Ray *ray) const;

 private:
  Vector3D luminocity_;
};
