#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Camera.hpp"
#include "LightSource.hpp"
#include "AbstractMaterial.hpp"
#include "Object3D.hpp"

class AbstractMaterial;

class Scene {
 public:
  enum class ObjectType {Plain, Light};

  void addObject(std::shared_ptr<Object3D> object);
  void addLightSource(
      std::shared_ptr<AbstractLightSource> light_source,
      std::shared_ptr<Object3D> light_object);
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
      std::shared_ptr<AbstractMaterial> *material,
      ObjectType *type = nullptr) const;

 private:
  Vector3D traceRay(const Ray &ray) const;

  std::vector<std::shared_ptr<Object3D>> objects_;
  std::vector<std::shared_ptr<AbstractLightSource>> lights_;
  std::vector<ObjectType> object_types_;
};
