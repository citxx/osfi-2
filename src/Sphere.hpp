#pragma once

#include "Material.hpp"
#include "Object3D.hpp"
#include "Vector3D.hpp"

class Sphere: public Object3D {
 public:
  Sphere(
      const Material &material,
      const Vector3D &center,
      double radius);

  virtual bool rayIntersection(const Ray &ray, Vector3D *intersectionPoint, Vector3D *normal) const;
  virtual Material material() const;

 private:
  Vector3D center_;
  double radius_;
  Material material_;
};
