#include "defs.hpp"
#include "Triangle.hpp"

#define EPS 0.0001

Triangle::Triangle(
    const Vector3D &v1,
    const Vector3D &v2,
    const Vector3D &v3): v1_(v1), v2_(v2), v3_(v3) {}

bool Triangle::rayIntersection(
    const Ray &ray,
    Vector3D *intersection_point,
    Vector3D *normal) const {
  //p + t * d = w1 * v1 + w2 * v2 + (1 - w1 - w2) * v3;
  //(w1, w2, t) = inv([v3 - v1, v3 - v2, d]) * (v3 - p)
  Vector3D m[3] = {v3_ - v1_, v3_ - v2_, ray.direction};
  Vector3D b = v3_ - ray.point;
  double det = Vector3D::dot(m[0], Vector3D::cross(m[1], m[2]));

  if (-EPS < det && det < EPS) {
    return false;
  }

  double w1 = Vector3D::dot(b, Vector3D::cross(m[1], m[2])) / det;
  double w2 = Vector3D::dot(b, Vector3D::cross(m[2], m[0])) / det;
  double w3 = 1.0 - w1 - w2;
  double t = Vector3D::dot(b, Vector3D::cross(m[0], m[1])) / det;

  if (w1 > -EPS && w2 > -EPS && w3 > -EPS & t > EPS) {
    *intersection_point = ray.point + t * ray.direction;
    *normal = Vector3D::cross(v2_ - v1_, v3_ - v1_);
    return true;
  } else {
    return false;
  }
}

void Triangle::randomPoint(
    Vector3D *point,
    Vector3D *normal) const {
  Vector3D u = v2_ - v1_;
  Vector3D v = v3_ - v1_;

  double x = 1.0 * rand() / RAND_MAX;
  double y = 1.0 * rand() / RAND_MAX;
  if (x + y > 1.0) {
    x = 1 - x;
    y = 1 - y;
  }

  *point = v3_ + x * u + y * v;
  *normal = Vector3D::cross(u, v);
}

// TODO: fair implementation
Ray Triangle::randomRay(const Vector3D &from_point) const {
  double x = 1.0 * rand() / RAND_MAX;
  double y = 1.0 * rand() / RAND_MAX;
  if (x + y > 1.0) {
    x = 1 - x;
    y = 1 - y;
  }

  Vector3D point = x * v1_ + y * v2_ + (1 - x - y) * v3_;
  return Ray(from_point, (point - from_point).normalized());
}
