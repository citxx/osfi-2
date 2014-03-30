#pragma once

#include "Material.hpp"
#include "Object3D.hpp"
#include "Vector3D.hpp"

class Triangle: public Object3D {
 public:
  Triangle(
      const Material &material,
      const Vector3D &v1,
      const Vector3D &v2,
      const Vector3D &v3);
  virtual bool rayIntersection(const Ray &ray, Vector3D *intersectionPoint, Vector3D *normal) const;
  virtual Material material() const;

 private:
  Vector3D v1_, v2_, v3_;
  Material material_;
};
