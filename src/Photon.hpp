#pragma once

class Photon {
 public:
  Photon(
      const Ray &ray,
      int cell,
      double frequency,
      double power): ray(ray), cell(cell), frequency(frequency), power(power) {}

  Ray ray;
  int cell;
  double frequency;
  double power;
};
