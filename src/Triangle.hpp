#pragma once

#include "Material.hpp"
#include "Surface.hpp"
#include "Vector3D.hpp"

class Triangle: public Surface {
 public:
  Triangle(
      const Vector3D &v1,
      const Vector3D &v2,
      const Vector3D &v3);

  virtual bool rayIntersection(
      const Ray &ray,
      Vector3D *intersection_point,
      Vector3D *normal) const;

  virtual void randomPoint(
      Vector3D *point,
      Vector3D *normal) const;

  virtual Ray randomRay(const Vector3D &from_point) const;

 private:
  Vector3D v1_, v2_, v3_;
};
