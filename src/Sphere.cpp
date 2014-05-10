#include <cmath>
#include <cstdlib>

#include "defs.hpp"
#include "Sphere.hpp"

#define EPS 0.0001

Sphere::Sphere(
    const Vector3D &center,
    double radius):
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

void Sphere::randomPoint(
    Vector3D *point,
    Vector3D *normal) const {
  double theta = 2 * PI * rand() / RAND_MAX;
  double phi = 2 * asin(sqrt(1.0 * rand() / RAND_MAX));

  Vector3D v(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));

  *point = center_ + radius_ * v;
  *normal = v;
}

Ray Sphere::randomRay(const Vector3D &from_point) const {
  double sin_a = radius_ / (center_ - from_point).len();

  double theta = 2 * PI * rand() / RAND_MAX;
  double phi = asin(sqrt(sin_a * sin_a * rand() / RAND_MAX));

  Vector3D dir = (center_ - from_point).normalized();

  Vector3D u = dir.orthogonal().normalized();
  Vector3D v = Vector3D::cross(dir, u);

  return Ray(
      from_point,
      cos(phi) * dir + sin(phi) * cos(theta) * u + sin(phi) * sin(theta) * v);
}

double Sphere::angle(const Vector3D &from_point) const {
  double sin_a = radius_ / (center_ - from_point).len();
  double cos_a = sqrt(1 - sin_a * sin_a);
  double r = cos_a * radius_;

  return r * r * PI / ((center_ - from_point).len() - sin_a * radius_);
}
