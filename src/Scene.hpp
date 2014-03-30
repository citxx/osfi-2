#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Camera.hpp"
#include "LightSource.hpp"
#include "Object3D.hpp"

class Scene {
 public:
  void addObject(std::shared_ptr<Object3D> object);
  void addLightSource(const LightSource &light_source);
  void render(const std::string &output_file_path, const Camera &camera, int width = 800);

 private:
  bool castRay(
      const Ray &ray,
      Vector3D *intersection_point,
      Vector3D *normal,
      Material *material) const;

  Vector3D traceRay(const Ray &ray) const;

  std::vector<std::shared_ptr<Object3D>> objects_;
  std::vector<LightSource> lights_;
};
