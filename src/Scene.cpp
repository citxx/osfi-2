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

void Scene::render(const std::string &output_file_path, const Camera &camera, int width) const {
  int PW = 4, PH = 4;

  int height = camera.getHeight(width);
  std::ofstream output(output_file_path);
  output << "P3" << std::endl;
  output << width << " " << height << std::endl;
  output << "255" << std::endl;
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      Vector3D color;
      for (int u = 0; u < PW; ++u) {
        for (int v = 0; v < PH; ++v) {
          Ray ray = camera.getDirection((i + 1.0 * u / PW) / width, (j + 1.0 * v / PH) / height);
          color = color + traceRay(ray);
        }
      }
      color = color / PW / PH;
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

void Scene::test(const Ray &ray) const {
  std::cerr << "Test scene (" << ray.point << ", " << ray.direction << ")" << std::endl;
  traceRay(ray);
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
  Ray current_ray = ray;
  Vector3D k(1.0, 1.0, 1.0);
  Vector3D result;

  while (k.len() > 0.001) {
    //std::cerr << "Trace step (" << current_ray.point << ", " << current_ray.direction << ")" << std::endl;
    if (castRay(current_ray, &ip, &n, &m)) {
      //std::cerr << "Hit(" << ip << ", " << n << ")" << std::endl;
      Vector3D color, nk;
      Ray nr;
      m.shade(*this, current_ray.direction, ip, n, &color, &nk, &nr);
      result = result + k * color;
      k = k * nk;
      current_ray = nr;
    } else {
      k = Vector3D();
    }
  }

  return result;
}
