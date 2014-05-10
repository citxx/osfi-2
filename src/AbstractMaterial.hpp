#pragma once

#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "defs.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Spectrum.hpp"
#include "Vector3D.hpp"

class AbstractMaterial {
 public:
  virtual void shade(
      const Scene &scene,
      const Vector3D &direction,
      const Vector3D &hit_point,
      const Vector3D &normal,
      Vector3D *color,
      Vector3D *k,
      Ray *ray) const = 0;

};
