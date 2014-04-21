#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Camera.hpp"
#include "LightSource.hpp"
#include "Material.hpp"
#include "Object3D.hpp"

class AbstractMaterial;

class Scene {
 public:
  void addObject(std::shared_ptr<Object3D> object);
  void addLightSource(std::shared_ptr<AbstractLightSource> light_source);
  void render(
      const std::string &output_file_path,
      const Camera &camera,
      int width = 800,
      int pixel_grid_size = 4) const;
  void test(const Ray &ray) const;

  inline const std::vector<std::shared_ptr<AbstractLightSource>> &lights() const { return lights_; }

  bool castRay(
      const Ray &ray,
      Vector3D *intersection_point,
      Vector3D *normal,
      std::shared_ptr<AbstractMaterial> *material) const;

 private:
  Vector3D traceRay(const Ray &ray) const;

  std::vector<std::shared_ptr<Object3D>> objects_;
  std::vector<std::shared_ptr<AbstractLightSource>> lights_;
};
