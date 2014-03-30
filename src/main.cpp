#include <cmath>
#include <iostream>

#include "Camera.hpp"
#include "Material.hpp"
#include "Plane.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Vector3D.hpp"

void test() {
  Material material(Vector3D(1.0, 1.0, 0.0));
  Triangle triangle(
      material,
      Vector3D(1.0, 0.0, 0.0),
      Vector3D(0.0, 0.0, 0.0),
      Vector3D(0.0, 1.0, 1.0));
  Ray ray(
      Vector3D(0.0, 0.0, 0.0),
      Vector3D(0.0, 1.0, 1.0));
  
  Vector3D inter, normal;
  std::cout << triangle.rayIntersection(ray, &inter, &normal) << std::endl;
  std::cout << inter << " " << normal << std::endl << std::endl;

  Sphere sphere(material, Vector3D(0.0, 0.0, 1.0), 1.0);

  std::cout << sphere.rayIntersection(Ray(Vector3D(0.5, 0.5, 0.0), Vector3D(0.0, 0.0, 1.0)), &inter, &normal) << std::endl;
  std::cout << inter << " " << normal << std::endl << std::endl;
  std::cout << sphere.rayIntersection(Ray(Vector3D(0.0, 0.4, 0.4), Vector3D(0.0, 0.0, 1.0)), &inter, &normal) << std::endl;
  std::cout << inter << " " << normal << std::endl << std::endl;

  Camera camera(
      Vector3D(1.0, 2.0, 1.0),
      Vector3D(-1.0, -2.0, -1.0),
      0.5 * M_PI,
      0.25 * M_PI);

  Ray r;
  r = camera.getDirection(0, 0);
  std::cout << r.point << " " << r.direction << std::endl << std::endl;
  r = camera.getDirection(1, 1);
  std::cout << r.point << " " << r.direction << std::endl << std::endl;
  r = camera.getDirection(0.5, 0.5);
  std::cout << r.point << " " << r.direction << std::endl << std::endl;
}

int main() {
  Scene scene;
  Material blue(Vector3D(0.1, 0.1, 1.0));
  Material red(Vector3D(1.0, 0.1, 0.1));

  auto s1 = std::shared_ptr<Object3D>(new Sphere(
      blue,
      Vector3D(0.0, 0.0, 3.0),
      1.0));
  scene.addObject(s1);

  /*auto plane = std::shared_ptr<Object3D>(new Plane(*/
      //red,
      //Vector3D(0.0, 0.0, 1.0),
      /*Vector3D(0.0, 0.0, 0.0)));*/
  //scene.addObject(plane);

  auto tr1 = std::shared_ptr<Object3D>(new Triangle(
      red,
      Vector3D(2.0, 2.0),
      Vector3D(-8.0, -8.0),
      Vector3D(2.0, -8.0)));
  auto tr2 = std::shared_ptr<Object3D>(new Triangle(
      red,
      Vector3D(2.0, 2.0),
      Vector3D(-8.0, 2.0),
      Vector3D(-8.0, -8.0)));
  scene.addObject(tr1);
  scene.addObject(tr2);

  scene.addLightSource(LightSource(
      Vector3D(-2.0, 4.0, 6.0),
      Vector3D(1.0, 1.0, 1.0)));
  scene.addLightSource(LightSource(
      Vector3D(2.0, 6.0, 9.0),
      Vector3D(1.0, 1.0, 1.0)));
  
  Camera camera(Vector3D(2.0, 3.0, 4.0), Vector3D(-4.0, -5.0, -4.0), 0.50 * M_PI, 0.4 * M_PI);
  scene.render("default.ppm", camera);

  return 0;
}
