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

class CookTorranceMaterial: public AbstractMaterial {
 public:
  CookTorranceMaterial(
      std::shared_ptr<AbstractMaterial> base_material,
      double roughness);

  virtual void shade(
      const Scene &scene,
      const Vector3D &direction,
      const Vector3D &hit_point,
      const Vector3D &normal,
      Vector3D *color,
      Vector3D *k,
      Ray *ray) const;

 private:
  double beckmann(double alpha) const;
  double masking(
      const Vector3D &normal,
      const Vector3D &local_normal,
      const Vector3D &direction,
      const Vector3D &reflected) const;

  std::shared_ptr<AbstractMaterial> base_material_;
  double roughness_;
};
