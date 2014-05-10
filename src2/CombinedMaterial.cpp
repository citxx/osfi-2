#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "CombinedMaterial.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Spectrum.hpp"
#include "Vector3D.hpp"
#include "defs.hpp"

CombinedMaterial::CombinedMaterial(
    std::initializer_list<std::pair<double, std::shared_ptr<AbstractMaterial>>> parts
  ): parts_(parts) {}

virtual void CombinedMaterial::importanceDensity(
    const Vector3D &direction,
    const Vector3D &normal,
    const Vector3D &reflected) const {
  double total = 0.0;
  for (auto x : parts_) {
    total += x.first;
  }

  double p = 0.0;
  for (auto x : parts_) {
    p += x.first * x.second->importanceDensity(direction, normal, reflected);
    if (rest <= 0.0) {
      x.second->directIllumination(scene, direction, hit_point, normal, secondary_ray, secondary_probability, probability, radiosity, ray);
      break;
    }
  }

  return p / total;
}

void CombinedMaterial::directIllumination(
    const Scene &scene,
    const Vector3D &direction,
    const Vector3D &hit_point,
    const Vector3D &normal,
    const Ray &secondary_ray,
    double *secondary_probability,
    double *probability,
    Vector3D *radiosity,
    Ray *ray) const {
  double total = 0.0;
  for (auto x : parts_) {
    total += x.first;
  }

  double p = total * rand() / RAND_MAX;
  double rest = p;
  for (auto x : parts_) {
    rest -= x.first;
    if (rest <= 0.0) {
      x.second->directIllumination(scene, direction, hit_point, normal, secondary_ray, secondary_probability, probability, radiosity, ray);
      break;
    }
  }
}

void CombinedMaterial::secondaryRay(
    const Scene &scene,
    const Vector3D &direction,
    const Vector3D &hit_point,
    const Vector3D &normal,
    double *probability,
    Vector3D *k,
    Ray *ray) const {
  double total = 0.0;
  for (auto x : parts_) {
    total += x.first;
  }

  double p = total * rand() / RAND_MAX;
  double rest = p;
  for (auto x : parts_) {
    rest -= x.first;
    if (rest <= 0.0) {
      x.second->secondaryRay(scene, direction, hit_point, normal, probability, k, ray);
      break;
    }
  }
}
