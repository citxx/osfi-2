#include <cmath>
#include <iostream>

#include "Camera.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"

Camera::Camera(
    const Vector3D &position,
    const Vector3D &direction,
    double width_angle,
    double height_angle):
    position_(position),
    direction_(direction) {
  Vector3D z(0.0, 0.0, 1.0);
  right_ = Vector3D::cross(direction_, z).normalized() * direction_.len() * tan(width_angle / 2.0);
  up_ = Vector3D::cross(right_, direction_).normalized() * direction_.len() * tan(height_angle / 2.0);
}

Ray Camera::getDirection(double x, double y) const {
  return Ray(
      position_,
      (direction_ + (2 * x - 1) * right_ + (1 - 2 * y) * up_).normalized());
}

double Camera::getHeight(double width) const {
  return width * up_.len() / right_.len();
}
