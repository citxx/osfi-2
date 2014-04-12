#include <fstream>
#include <future>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Camera.hpp"
#include "Image.hpp"
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

void Scene::render(
    const std::string &output_file_path,
    const Camera &camera,
    int width,
    int pixel_grid_size) const {
  int PW, PH;
  PW = PH = pixel_grid_size;

  int height = camera.getHeight(width);
  Image img(width, height);
  for (int u = 0; true; ++u) {
    for (int v = 0; v < PH; ++v) {
      double n = u * PH + v + 1;
      std::cerr << "Rendering frame ";
      #pragma omp parallel for 
      for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
          Ray ray = camera.getDirection((i + 1.0 * (u % PW) / PW) / width, (j + 1.0 * v / PH) / height);
          Vector3D color = traceRay(ray);
          double r, g, b;
          img.getPixel(i, j, &r, &g, &b);
          img.setPixel(i, j,
              r * (n - 1) / n + color.x / n,
              g * (n - 1) / n + color.y / n,
              b * (n - 1) / n + color.z / n);
        }
        std::cerr << '.';
      }
      std::cerr << " done." << std::endl;
      std::cerr << "Writing file ...";
      img.savePPM(output_file_path);
      std::cerr << " done." << std::endl;
    }
  }
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

  while (k.len() > 0.05) {
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
