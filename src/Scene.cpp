#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Camera.hpp"
#include "Material.hpp"
#include "Object3D.hpp"
#include "Scene.hpp"

#define EPS 0.0001

void Scene::addObject(std::shared_ptr<Object3D> object) {
  objects_.push_back(object);
}

void Scene::addLightSource(const LightSource &light_source) {
  lights_.push_back(light_source);
}

void Scene::render(const std::string &output_file_path, const Camera &camera, int width) {
  int height = camera.getHeight(width);
  std::ofstream output(output_file_path);
  output << "P3" << std::endl;
  output << width << " " << height << std::endl;
  output << "255" << std::endl;
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      Ray ray = camera.getDirection(1.0 * i / width, 1.0 * j / height);
      Vector3D color = traceRay(ray);
      if (color.x < 0.0) color.x = 0.0; if (color.x > 1.0) color.x = 1.0;
      if (color.y < 0.0) color.y = 0.0; if (color.y > 1.0) color.y = 1.0;
      if (color.z < 0.0) color.z = 0.0; if (color.z > 1.0) color.z = 1.0;
      int r = color.x * 255;
      int g = color.y * 255;
      int b = color.z * 255;
      output << r << " " << g << " " << b << std::endl;
    }
  }
  output.close();
}

bool Scene::castRay(
    const Ray &ray,
    Vector3D *intersection_point,
    Vector3D *normal,
    Material *material) const {
  bool result = false;
  Vector3D _ip, _n;
  Material m;
  for (auto obj : objects_) {
    if (obj->rayIntersection(ray, &_ip, &_n)) {
      if (!result || Vector3D::dot(_ip - *intersection_point, ray.direction) < 0.0) {
        *intersection_point = _ip;
        if (normal != nullptr) *normal = _n;
        if (material != nullptr) *material = obj->material();
      }
      result = true;
    }
  }
  return result;
}

Vector3D Scene::traceRay(const Ray &ray) const {
  Vector3D ip, n;
  Material m;
  if (castRay(ray, &ip, &n, &m)) {
    Vector3D color, hit;
    for (auto ls : lights_) {
      Vector3D dir = ls.position - ip;
      bool hitted = castRay(Ray(ip, dir), &hit, nullptr, nullptr);
      if (!hitted || Vector3D::dot(ip - hit, ls.position - hit) > EPS) {
        Vector3D dc = ls.intensity * m.diffuse_color_ * std::max(0.0, Vector3D::dot(dir.normalized(), n.normalized()));
        color = color + dc;
      }
    }
    return color;
  } else {
    return Vector3D();
  }
}
