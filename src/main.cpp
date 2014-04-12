#include <cmath>
#include <ctime>
#include <iostream>

#include "Camera.hpp"
#include "Material.hpp"
#include "Plane.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Vector3D.hpp"

/*void test() {*/
  //Material material(Vector3D(1.0, 1.0, 0.0));
  //Triangle triangle(
      //material,
      //Vector3D(1.0, 0.0, 0.0),
      //Vector3D(0.0, 0.0, 0.0),
      //Vector3D(0.0, 1.0, 1.0));
  //Ray ray(
      //Vector3D(0.0, 0.0, 0.0),
      //Vector3D(0.0, 1.0, 1.0));
  
  //Vector3D inter, normal;
  //std::cout << triangle.rayIntersection(ray, &inter, &normal) << std::endl;
  //std::cout << inter << " " << normal << std::endl << std::endl;

  //Sphere sphere(material, Vector3D(0.0, 0.0, 1.0), 1.0);

  //std::cout << sphere.rayIntersection(Ray(Vector3D(0.5, 0.5, 0.0), Vector3D(0.0, 0.0, 1.0)), &inter, &normal) << std::endl;
  //std::cout << inter << " " << normal << std::endl << std::endl;
  //std::cout << sphere.rayIntersection(Ray(Vector3D(0.0, 0.4, 0.4), Vector3D(0.0, 0.0, 1.0)), &inter, &normal) << std::endl;
  //std::cout << inter << " " << normal << std::endl << std::endl;

  //Camera camera(
      //Vector3D(1.0, 2.0, 1.0),
      //Vector3D(-1.0, -2.0, -1.0),
      //0.5 * M_PI,
      //0.25 * M_PI);

  //Ray r;
  //r = camera.getDirection(0, 0);
  //std::cout << r.point << " " << r.direction << std::endl << std::endl;
  //r = camera.getDirection(1, 1);
  //std::cout << r.point << " " << r.direction << std::endl << std::endl;
  //r = camera.getDirection(0.5, 0.5);
  //std::cout << r.point << " " << r.direction << std::endl << std::endl;
/*}*/

void cornellBox(Scene *scene) {
  Material blue(Vector3D(0.1, 0.1, 1.0), Vector3D(), Vector3D(999999999.0, 999999999.0, 999999999.0));
  Material red(Vector3D(1.0, 0.1, 0.1), Vector3D(), Vector3D(999999999.0, 999999999.0, 999999999.0));
  Material white(Vector3D(1.0, 1.0, 1.0), Vector3D(), Vector3D(999999999.0, 999999999.0, 999999999.0));
  Material refl_m(Vector3D(0.1, 0.1, 0.1), Vector3D(0.8, 0.8, 0.8), Vector3D(999999999.0, 999999999.0, 999999999.0));
  Material refr_m(Vector3D(0.1, 0.1, 0.1), Vector3D(0.8, 0.8, 0.8), Vector3D(1.01, 1.01, 1.01));

  auto reflective_sphere = std::shared_ptr<Object3D>(new Sphere(
      refl_m,
      Vector3D(-2.5, -2.5, -2.5),
      1.5));
  scene->addObject(reflective_sphere);
  
  auto refractive_sphere = std::shared_ptr<Object3D>(new Sphere(
      refr_m,
      Vector3D(0.0, 2.5, -2.5),
      1.5));
  scene->addObject(refractive_sphere);
  
  auto red_tr_1 = std::shared_ptr<Object3D>(new Triangle(
      red,
      Vector3D(5.0, -5.0, -4.0),
      Vector3D(-5.0, -5.0, -4.0),
      Vector3D(-5.0, -5.0, 4.0)));
  scene->addObject(red_tr_1);

  auto red_tr_2 = std::shared_ptr<Object3D>(new Triangle(
      red,
      Vector3D(-5.0, -5.0, 4.0),
      Vector3D(5.0, -5.0, 4.0),
      Vector3D(5.0, -5.0, -4.0)));
  scene->addObject(red_tr_2);
  
  auto blue_tr_1 = std::shared_ptr<Object3D>(new Triangle(
      blue,
      Vector3D(-5.0, 5.0, -4.0),
      Vector3D(5.0, 5.0, -4.0),
      Vector3D(-5.0, 5.0, 4.0)));
  scene->addObject(blue_tr_1);

  auto blue_tr_2 = std::shared_ptr<Object3D>(new Triangle(
      blue,
      Vector3D(5.0, 5.0, 4.0),
      Vector3D(-5.0, 5.0, 4.0),
      Vector3D(5.0, 5.0, -4.0)));
  scene->addObject(blue_tr_2);

  auto ceiling_tr_1 = std::shared_ptr<Object3D>(new Triangle(
      white,
      Vector3D(5.0, -5.0, 4.0),
      Vector3D(-5.0, -5.0, 4.0),
      Vector3D(-5.0, 5.0, 4.0)));
  scene->addObject(ceiling_tr_1);

  auto ceiling_tr_2 = std::shared_ptr<Object3D>(new Triangle(
      white,
      Vector3D(5.0, -5.0, 4.0),
      Vector3D(-5.0, 5.0, 4.0),
      Vector3D(5.0, 5.0, 4.0)));
  scene->addObject(ceiling_tr_2);

  auto floor_tr_1 = std::shared_ptr<Object3D>(new Triangle(
      white,
      Vector3D(-5.0, -5.0, -4.0),
      Vector3D(5.0, -5.0, -4.0),
      Vector3D(-5.0, 5.0, -4.0)));
  scene->addObject(floor_tr_1);

  auto floor_tr_2 = std::shared_ptr<Object3D>(new Triangle(
      white,
      Vector3D(-5.0, 5.0, -4.0),
      Vector3D(5.0, -5.0, -4.0),
      Vector3D(5.0, 5.0, -4.0)));
  scene->addObject(floor_tr_2);

  auto back_wall_tr_1 = std::shared_ptr<Object3D>(new Triangle(
      white,
      Vector3D(-5.0, -5.0, -4.0),
      Vector3D(-5.0, 5.0, -4.0),
      Vector3D(-5.0, 5.0, 4.0)));
  scene->addObject(back_wall_tr_1);

  auto back_wall_tr_2 = std::shared_ptr<Object3D>(new Triangle(
      white,
      Vector3D(-5.0, -5.0, -4.0),
      Vector3D(-5.0, 5.0, 4.0),
      Vector3D(-5.0, -5.0, 4.0)));
  scene->addObject(back_wall_tr_2);

  scene->addLightSource(LightSource(
      Vector3D(0.0, 0.0, 1.5),
      Vector3D(10.0, 10.0, 10.0)));
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  int pixel_grid_size = 4;
  if (argc > 1) {
    pixel_grid_size = std::stoi(argv[1]);
  }

  Scene scene;
  cornellBox(&scene);

  Camera camera(Vector3D(13.0, 0.0, 0.0), Vector3D(-1.0, 0.0, 0.0), 0.34 * M_PI, 0.25 * M_PI);
  scene.render("default.ppm", camera, 800, pixel_grid_size);
  //scene.test(Ray(Vector3D(5.0, 3.0, -2.5), Vector3D(-1.0, 0.0, 0.0)));

  return 0;
}
