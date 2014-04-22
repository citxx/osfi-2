#include <cmath>
#include <iomanip>

#include "Vector3D.hpp"

#define EPS 1e-6

Vector3D::Vector3D(double x, double y, double z):
    x(x), y(y), z(z) {}

Vector3D::Vector3D(const Vector3D &a):
    x(a.x), y(a.y), z(a.z) {}

double Vector3D::dot(const Vector3D &a, const Vector3D &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3D Vector3D::cross(const Vector3D &a, const Vector3D &b) {
  return Vector3D(a.y * b.z - a.z * b.y, -a.x * b.z + a.z * b.x, a.x * b.y - a.y * b.x);
}

double Vector3D::angle(const Vector3D &a, const Vector3D &b) {
  return atan2(cross(a, b).len(), dot(a, b));
}

Vector3D Vector3D::normal(const Vector3D &a, const Vector3D &b) {
  return cross(a, b).normalized();
}

double Vector3D::len() const {
  return sqrt(dot(*this, *this));
}

Vector3D Vector3D::normalized() const {
  return (*this) / len();
}

Vector3D Vector3D::operator -() const {
  return Vector3D(-x, -y, -z);
}

Vector3D Vector3D::operator +() const {
  return Vector3D(+x, +y, +z);
}

double Vector3D::operator [](int i) const {
  if (i == 0) return x;
  if (i == 1) return y;
  if (i == 2) return z;
  throw "Tried to get invalid component of Vector3D";
}

Vector3D Vector3D::refract(
    const Vector3D &normal,
    double n) const {
  double cos_s = Vector3D::dot(*this, normal) / len() / normal.len();

  if (cos_s > 0) {
    n = 1.0 / n;
  }

  double abs_cos_s = fabs(cos_s);
  Vector3D true_normal = - (cos_s * normal).normalized();
  Vector3D result = *this / n + (abs_cos_s / n - sqrt(1 - (1 - abs_cos_s * abs_cos_s) / n / n)) * true_normal;
  return result;
}


Vector3D Vector3D::reflect(const Vector3D &normal) const {
  return *this - 2 * Vector3D::dot(*this, normal) / normal.len() / len() * normal;
}

Vector3D Vector3D::orthogonal() const {
  if (std::abs(x - y) < EPS && std::abs(y - z) < EPS) {
    return Vector3D(-2 * x, y, z);
  } else {
    return Vector3D(y - z, z - x, x - y);
  }
}

bool operator ==(const Vector3D &a, const Vector3D &b) {
  return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool operator !=(const Vector3D &a, const Vector3D &b){
  return a.x != b.x || a.y != b.y || a.z != b.z;
}

Vector3D operator +(const Vector3D &a, const Vector3D &b) {
  return Vector3D(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3D operator -(const Vector3D &a, const Vector3D &b) {
  return Vector3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3D operator *(double a, const Vector3D &b) {
  return Vector3D(a * b.x, a * b.y, a * b.z);
}

Vector3D operator *(const Vector3D &b, double a) {
  return Vector3D(a * b.x, a * b.y, a * b.z);
}

Vector3D operator *(const Vector3D &a, const Vector3D &b) {
  return Vector3D(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector3D operator /(const Vector3D &a, double b) {
  return Vector3D(a.x / b, a.y / b, a.z / b);
}

Vector3D operator /(const Vector3D &a, const Vector3D &b) {
  return Vector3D(a.x / b.x, a.y / b.y, a.z / b.z);
}

std::ostream & operator <<(std::ostream &stream, const Vector3D &a) {
  stream << std::setprecision(2) << "(" << a.x << ", " << a.y << ", " << a.z << ")";
  return stream;
}
