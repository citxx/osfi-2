#pragma once

#include "Vector3D.hpp"

class Material {
 public:
  explicit Material(
      const Vector3D &diffuse_color = Vector3D());


 //private:
  Vector3D diffuse_color_;
};
