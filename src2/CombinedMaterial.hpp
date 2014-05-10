#pragma once

#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "AbstractMaterial.hpp"
#include "defs.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Spectrum.hpp"
#include "Vector3D.hpp"

class CombinedMaterial: public AbstractMaterial {
 public:
  explicit CombinedMaterial(
      std::initializer_list<std::pair<double, std::shared_ptr<AbstractMaterial>>> parts);

  virtual void importanceDensity(
      const Vector3D &direction,
      const Vector3D &normal,
      const Vector3D &reflected) const;

  virtual void directIllumination(
      const Scene &scene,
      const Vector3D &direction,
      const Vector3D &hit_point,
      const Vector3D &normal,
      const Ray &secondary_ray,
      double *secondary_probability,
      double *probability,
      Vector3D *radiosity,
      Ray *ray) const;

  virtual void secondaryRay(
      const Scene &scene,
      const Vector3D &direction,
      const Vector3D &hit_point,
      const Vector3D &normal,
      double *probability,
      Vector3D *k,
      Ray *ray) const;

 private:
  std::vector<std::pair<double, std::shared_ptr<AbstractMaterial>>> parts_;
};
