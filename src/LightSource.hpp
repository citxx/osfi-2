#pragma once

#include <memory>

#include "Material.hpp"
#include "Object3D.hpp"
#include "HomogeneousObject.hpp"
#include "Photon.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"

class AbstractLightSource {
 public:
  //Photon emit(double power) = 0;

  virtual ~AbstractLightSource() {};

  virtual Vector3D intensity(
      const Vector3D &from_point,
      Vector3D *light_point) const = 0;
};

class PointLightSource: public AbstractLightSource {
 public:
  PointLightSource(
      const Vector3D &position,
      const Vector3D &intensity): position_(position), intensity_(intensity) {}

  virtual Vector3D intensity(
      const Vector3D &from_point,
      Vector3D *light_point) const {
    *light_point = position_;
    return intensity_ / Vector3D::dot(position_ - from_point, position_ - from_point);
  }

 private:
  Vector3D position_;
  Vector3D intensity_;
};

class LambertLightSource: public AbstractLightSource {
 public:
  LambertLightSource(
      std::shared_ptr<Surface> surface,
      const Vector3D &luminosity): surface_(surface), luminosity_(luminosity) {}

  virtual Vector3D intensity(
      const Vector3D &from_point,
      Vector3D *light_point) const {
    Ray r = surface_->randomRay(from_point);
    Vector3D n;
    if (!surface_->rayIntersection(r, light_point, &n)) {
      return Vector3D();
    }
    Vector3D v = *light_point - from_point;
    auto result =  luminosity_ / Vector3D::dot(v, v) * std::abs(Vector3D::dot(-v.normalized(), n.normalized()));
    if (std::isnan(result.x) || std::isnan(result.y) || std::isnan(result.z)) {
      std::cerr << "NaN: " << from_point << " " << *light_point << " " << result << " " << r.point << " " << r.direction << " " << n << " " << v << " " << luminosity_ << std::endl;
    }
    return result;
  }

 private:
  std::shared_ptr<Surface> surface_;
  Vector3D luminosity_;
};
