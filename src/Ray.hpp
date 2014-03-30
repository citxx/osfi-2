#pragma once

#include "Vector3D.hpp"

class Ray {
 public:
  Ray(const Vector3D &point = Vector3D(), const Vector3D &direction = Vector3D());

  Vector3D point, direction;
};
