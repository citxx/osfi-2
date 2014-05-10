#pragma once

#include "Ray.hpp"
#include "Photon.hpp"
#include "Vector3D.hpp"

class Surface {
 public:
  virtual ~Surface() {}

  virtual bool rayIntersection(
      const Ray &ray,
      Vector3D *intersection_point,
      Vector3D *normal) const = 0;

  virtual void randomPoint(
      Vector3D *point,
      Vector3D *normal) const = 0;

  virtual Ray randomRay(const Vector3D &from_point) const = 0;

  virtual double angle(const Vector3D &from_point) const = 0;

  //virtual void storePhoton(int cell, double power) = 0;
};
