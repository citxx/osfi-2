#include <fstream>
#include <future>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "AbstractMaterial.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include "Object3D.hpp"
#include "Scene.hpp"

#define EPS 1e-6

void Scene::addObject(std::shared_ptr<Object3D> object) {
  objects_.push_back(object);
  object_types_.push_back(ObjectType::Plain);
}

void Scene::addLightSource(
    std::shared_ptr<AbstractLightSource> light_source,
    std::shared_ptr<Object3D> light_object) {
  lights_.push_back(light_source);
  objects_.push_back(light_object);
  object_types_.push_back(ObjectType::Light);
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
  for (int u = 0; ; ++u) {
    for (int v = 0; v < PH; ++v) {
      int n = u * PH + v + 1;
      std::cerr << "Rendering frame " << n << " ";
      #pragma omp parallel for schedule(dynamic) 
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
      img.saveHDR(output_file_path);
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
    std::shared_ptr<AbstractMaterial> *material,
    Scene::ObjectType *type) const {
  bool result = false;
  Vector3D _ip, _n, int_point;
  for (int i = 0; i < objects_.size(); ++i) {
    std::shared_ptr<Object3D> obj = objects_[i];
    if (obj->surface()->rayIntersection(ray, &_ip, &_n)) {
      if (!result || Vector3D::dot(_ip - int_point, ray.direction) < 0.0) {
        int_point = _ip;
        if (intersection_point != nullptr) *intersection_point = int_point;
        if (normal != nullptr) *normal = _n;
        if (material != nullptr) *material = obj->material(_ip);
        if (type != nullptr) *type = object_types_[i];
      }
      result = true;
    }
  }
  return result;
}

Vector3D Scene::traceRay(const Ray &ray) const {
  Vector3D ip, n;
  std::shared_ptr<AbstractMaterial> m;
  Ray current_ray = ray;
  Vector3D k(1.0, 1.0, 1.0);
  Vector3D result;

  while (k.len() > 1e-3) {
    //std::cerr << "Trace step (" << current_ray.point << ", " << current_ray.direction << ")" << std::endl;
    if (castRay(current_ray, &ip, &n, &m)) {
      //std::cerr << "Hit(" << ip << ", " << n << ")" << std::endl;
      Vector3D color, nk;
      Ray nr;
      m->shade(*this, current_ray.direction.normalized(), ip, n.normalized(), &color, &nk, &nr);
      if (std::isnan(color.x) || std::isnan(color.y) || std::isnan(color.z) ||
          std::isinf(color.x) || std::isinf(color.y) || std::isinf(color.z)) {
        std::cerr << "Warning! color = " << color << std::endl;
      }
      result = result + k * color;
      k = k * nk;
      //std::cerr << result << " " << k << " " << color << std::endl;
      current_ray = nr;
    } else {
      k = Vector3D();
    }
  }

  return result;
}
