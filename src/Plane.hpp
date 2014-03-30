#pragma once

#include "Material.hpp"
#include "Object3D.hpp"
#include "Vector3D.hpp"

class Plane: public Object3D {
 public:
  Plane(
      const Material &material,
      const Vector3D &n,
      const Vector3D &point);

  virtual bool rayIntersection(const Ray &ray, Vector3D *intersectionPoint, Vector3D *normal) const;
  virtual Material material() const;

 private:
  Vector3D n_;
  double c_;
  Material material_;
};
