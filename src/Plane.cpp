#include <cmath>

#include "Plane.hpp"

#define EPS 0.0001

Plane::Plane(
    const Material &material,
    const Vector3D &n,
    const Vector3D &point):
    material_(material),
    n_(n),
    c_(- Vector3D::dot(n, point)) {}

bool Plane::rayIntersection(
    const Ray &ray,
    Vector3D *intersection_point,
    Vector3D *normal) const {
  // (p + t * d) * n + c = 0
  // t = (- (p, n) - c) / (d, n)
  double t = (- Vector3D::dot(ray.point, n_) - c_) / Vector3D::dot(ray.direction, n_);
  
  if (t < EPS) {
    return false;
  } else {
    *intersection_point = ray.point + t * ray.direction;
    *normal = n_;
    return true;
  }
}

Material Plane::material() const {
  return material_;
}

