#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "LightMaterial.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Spectrum.hpp"
#include "Vector3D.hpp"
#include "defs.hpp"

LightMaterial::LightMaterial(const Vector3D &luminocity): luminocity_(luminocity) {}

void LightMaterial::shade(
    const Scene &scene,
    const Vector3D &direction,
    const Vector3D &hit_point,
    const Vector3D &normal,
    Vector3D *color,
    Vector3D *k,
    Ray *ray) const {
  *color = luminocity_;
  *k = Vector3D();
}
