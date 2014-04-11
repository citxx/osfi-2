#pragma once

#include "Ray.hpp"
#include "Vector3D.hpp"

class Material;

class Object3D {
 public:
  virtual ~Object3D() {}

  virtual bool rayIntersection(const Ray &ray, Vector3D *intersectionPoint, Vector3D *normal) const = 0;
  virtual Material material() const = 0;
};
