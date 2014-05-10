#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "CookTorranceMaterial.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Spectrum.hpp"
#include "Vector3D.hpp"
#include "defs.hpp"

CookTorranceMaterial::CookTorranceMaterial(
    std::shared_ptr<AbstractMaterial> base_material,
    double roughness): base_material_(base_material), roughness_(roughness) {}

void CookTorranceMaterial::shade(
    const Scene &scene,
    const Vector3D &direction,
    const Vector3D &hit_point,
    const Vector3D &normal,
    Vector3D *color,
    Vector3D *k,
    Ray *ray) const {

  double phi = 2.0 * PI * rand() / RAND_MAX;
  double psi, y;
  do {
    psi = 0.5 * PI * rand() / RAND_MAX;
    y = 1.0 * rand() / RAND_MAX;
  } while (y > beckmann(psi));

  Vector3D u = normal.orthogonal().normalized();
  Vector3D v = Vector3D::cross(normal, u);
  Vector3D local_normal = sin(psi) * sin(phi) * v + sin(psi) * cos(phi) * u + cos(psi) * normal;

  base_material_->shade(
      scene, direction, hit_point, local_normal, color, k, ray);

  *color = *color *
    masking(normal, (ray->direction - direction).normalized(), direction, ray->direction)/* / 4.0 /*/
    //Vector3D::dot(normal, -direction) /
    /*Vector3D::dot(normal, ray->direction)*/;

  *k = *k *
    masking(normal, (ray->direction - direction).normalized(), direction, ray->direction) /* 4.0 */
    //Vector3D::dot(normal, -direction) /
    /*Vector3D::dot(normal, ray->direction)*/;
}

double CookTorranceMaterial::beckmann(double alpha) const {
  double ta = tan(alpha);
  double ta2 = ta * ta;
  double ca = cos(alpha);
  double ca2 = ca * ca;
  double ca4 = ca2 * ca2;
  double r2 = roughness_ * roughness_;
  return exp(- ta2 / r2) / r2 / ca4;
}

double CookTorranceMaterial::masking(
      const Vector3D &normal,
      const Vector3D &local_normal,
      const Vector3D &direction,
      const Vector3D &reflected) const {
  double result = std::min(
      2.0 * Vector3D::dot(normal, local_normal) *
        Vector3D::dot(normal, -direction) /
        Vector3D::dot(-direction, local_normal),
      2.0 * Vector3D::dot(normal, local_normal) *
        Vector3D::dot(normal, reflected) /
        Vector3D::dot(-direction, local_normal));
  return std::min(1.0, result);
}
