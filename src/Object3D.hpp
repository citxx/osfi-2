#pragma once

#include <memory>

#include "Surface.hpp"
#include "Vector3D.hpp"

class AbstractMaterial;

class Object3D {
 public:
  virtual ~Object3D() {}

  virtual std::shared_ptr<Surface> surface() const = 0;
  virtual std::shared_ptr<AbstractMaterial> material(const Vector3D &point) const = 0;
};
