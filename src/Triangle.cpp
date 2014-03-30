#include "Triangle.hpp"

#define EPS 0.0001

Triangle::Triangle(
    const Material &material,
    const Vector3D &v1,
    const Vector3D &v2,
    const Vector3D &v3): material_(material), v1_(v1), v2_(v2), v3_(v3) {}

bool Triangle::rayIntersection(
    const Ray &ray,
    Vector3D *intersectionPoint,
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
    *intersectionPoint = ray.point + t * ray.direction;
    *normal = Vector3D::cross(v2_ - v1_, v3_ - v1_);
    return true;
  } else {
    return false;
  }
}

Material Triangle::material() const {
  return material_;
}

