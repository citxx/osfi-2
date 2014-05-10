#pragma once

#include "Surface.hpp"
#include "Vector3D.hpp"

class Sphere: public Surface {
 public:
  Sphere(
      const Vector3D &center,
      double radius);

  virtual bool rayIntersection(
      const Ray &ray,
      Vector3D *intersection_point,
      Vector3D *normal) const;

  virtual void randomPoint(
      Vector3D *point,
      Vector3D *normal) const;

  virtual Ray randomRay(const Vector3D &from_point) const;

  virtual double angle(const Vector3D &from_point) const;

 private:
  Vector3D center_;
  double radius_;
};
