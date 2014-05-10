#pragma once

#include "AbstractMaterial.hpp"
#include "Object3D.hpp"

class HomogeneousObject: public Object3D {
 public:
  HomogeneousObject(
      std::shared_ptr<Surface> surface,
      std::shared_ptr<AbstractMaterial> material): surface_(surface), material_(material) {
  }

  virtual std::shared_ptr<Surface> surface() const {
    return surface_;
  }

  virtual std::shared_ptr<AbstractMaterial> material(const Vector3D &point) const {
    return material_;
  }

 private:
  std::shared_ptr<Surface> surface_;
  std::shared_ptr<AbstractMaterial> material_;
};
