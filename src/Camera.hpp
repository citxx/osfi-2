#pragma once

#include "Ray.hpp"
#include "Vector3D.hpp"

class Camera {
 public:
  Camera(
      const Vector3D &position,
      const Vector3D &direction,
      double width_angle,
      double height_angle);

  Ray getDirection(double x, double y) const;
  double getHeight(double width) const;

 private:
  Vector3D position_, direction_, up_, right_;
};
