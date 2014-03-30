#pragma once

#include "Vector3D.hpp"

class LightSource {
 public:
  LightSource(
      const Vector3D &position,
      const Vector3D &intensity): position(position), intensity(intensity) {}

  Vector3D position, intensity;
};
