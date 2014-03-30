#include <cmath>

#include "Sphere.hpp"

#define EPS 0.0001

Sphere::Sphere(
    const Material &material,
    const Vector3D &center,
    double radius):
    material_(material),
    center_(center),
    radius_(radius) {}

bool Sphere::rayIntersection(
    const Ray &ray,
    Vector3D *intersectionPoint,
    Vector3D *normal) const {
  // (p + t * d - c) ^ 2 = r ^ 2
  Vector3D pmc = ray.point - center_;
  double a = Vector3D::dot(ray.direction, ray.direction);
  double b = 2 * Vector3D::dot(ray.direction, pmc);
  double c = Vector3D::dot(pmc, pmc) - radius_ * radius_;

  double disc = b * b - 4 * a * c;
  if (disc < 0.0) {
    return false;
  }

  double t1 = (- b - sqrt(disc)) / (2 * a);
  double t2 = (- b + sqrt(disc)) / (2 * a);
  if (t2 < EPS) {
    return false;
  } else {
    double t = t2;
    if (t1 > EPS) {
      t = t1;
    }
    *intersectionPoint = ray.point + t * ray.direction;
    *normal = *intersectionPoint - center_;
    return true;
  }
}

Material Sphere::material() const {
  return material_;
}

