#include <cmath>
#include <ctime>
#include <iostream>
#include <memory>

#include "Camera.hpp"
#include "HomogeneousObject.hpp"
#include "Material.hpp"
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
  auto blue = std::shared_ptr<AbstractMaterial>(
      new LambertSpecularMaterial(
        Vector3D(0.1, 0.1, 1.0),
        Vector3D(),
        Vector3D(INFINITY, INFINITY, INFINITY)));

  auto red = std::shared_ptr<AbstractMaterial>(
      new LambertSpecularMaterial(
        Vector3D(1.0, 0.1, 0.1),
        Vector3D(),
        Vector3D(INFINITY, INFINITY, INFINITY)));

  auto white = std::shared_ptr<AbstractMaterial>(
      new LambertSpecularMaterial(
        Vector3D(1.0, 1.0, 1.0),
        Vector3D(),
        Vector3D(INFINITY, INFINITY, INFINITY)));

  auto refl_m = std::shared_ptr<AbstractMaterial>(
      new LambertSpecularMaterial(
        Vector3D(0.1, 0.1, 0.1),
        Vector3D(0.8, 0.8, 0.8),
        Vector3D(INFINITY, INFINITY, INFINITY)));
  auto refr_m = std::shared_ptr<AbstractMaterial>(
      new LambertSpecularMaterial(
        Vector3D(0.01, 0.01, 0.01),
        Vector3D(0.9, 0.9, 0.9),
        Vector3D(2.6, 2.6, 2.6)));

  auto reflective_sphere = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Sphere(
          Vector3D(-2.5, -2.5, -2.5),
          1.5)),
      refl_m));
  scene->addObject(reflective_sphere);

  auto refractive_sphere = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Sphere(
          Vector3D(0.0, 2.5, -2.5),
          1.5)),
      refr_m));
  scene->addObject(refractive_sphere);

  auto red_tr_1 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Triangle(
          Vector3D(5.0, -5.0, -4.0),
          Vector3D(-5.0, -5.0, -4.0),
          Vector3D(-5.0, -5.0, 4.0))),
      red));
  scene->addObject(red_tr_1);

  auto red_tr_2 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Triangle(
          Vector3D(-5.0, -5.0, 4.0),
          Vector3D(5.0, -5.0, 4.0),
          Vector3D(5.0, -5.0, -4.0))),
      red));
  scene->addObject(red_tr_2);

  auto blue_tr_1 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Triangle(
          Vector3D(-5.0, 5.0, -4.0),
          Vector3D(5.0, 5.0, -4.0),
          Vector3D(-5.0, 5.0, 4.0))),
      blue));
  scene->addObject(blue_tr_1);

  auto blue_tr_2 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Triangle(
          Vector3D(5.0, 5.0, 4.0),
          Vector3D(-5.0, 5.0, 4.0),
          Vector3D(5.0, 5.0, -4.0))),
      blue));
  scene->addObject(blue_tr_2);

  auto ceiling_tr_1 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Triangle(
          Vector3D(5.0, -5.0, 4.0),
          Vector3D(-5.0, -5.0, 4.0),
          Vector3D(-5.0, 5.0, 4.0))),
      white));
  scene->addObject(ceiling_tr_1);

  auto ceiling_tr_2 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Triangle(
          Vector3D(5.0, -5.0, 4.0),
          Vector3D(-5.0, 5.0, 4.0),
          Vector3D(5.0, 5.0, 4.0))),
      white));
  scene->addObject(ceiling_tr_2);

  auto floor_tr_1 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Triangle(
          Vector3D(-5.0, -5.0, -4.0),
          Vector3D(5.0, -5.0, -4.0),
          Vector3D(-5.0, 5.0, -4.0))),
      white));
  scene->addObject(floor_tr_1);

  auto floor_tr_2 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Triangle(
          Vector3D(-5.0, 5.0, -4.0),
          Vector3D(5.0, -5.0, -4.0),
          Vector3D(5.0, 5.0, -4.0))),
      white));
  scene->addObject(floor_tr_2);

  auto back_wall_tr_1 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Triangle(
          Vector3D(-5.0, -5.0, -4.0),
          Vector3D(-5.0, 5.0, -4.0),
          Vector3D(-5.0, 5.0, 4.0))),
      white));
  scene->addObject(back_wall_tr_1);

  auto back_wall_tr_2 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Triangle(
          Vector3D(-5.0, -5.0, -4.0),
          Vector3D(-5.0, 5.0, 4.0),
          Vector3D(-5.0, -5.0, 4.0))),
      white));
  scene->addObject(back_wall_tr_2);

  Vector3D luminosity(8.0, 8.0, 8.0);
  //auto lamp_surface = std::shared_ptr<Surface>(new Sphere(
      //Vector3D(0.0, 0.0, 3.0),
      //0.4));
  auto lamp_surface = std::shared_ptr<Surface>(new Triangle(
      Vector3D(0.0, 1.0, 3.99),
      Vector3D(-3.0, 0.0, 3.99),
      Vector3D(-1.0, 2.0, 3.99)));

  auto lamp = std::shared_ptr<AbstractLightSource>(new LambertLightSource(
      lamp_surface,
      luminosity));
  scene->addLightSource(lamp);
  
  auto lamp_object = std::shared_ptr<Object3D>(new HomogeneousObject(
      lamp_surface,
      std::shared_ptr<AbstractMaterial>(new LightMaterial(luminosity))
    )); 

  scene->addObject(lamp_object);

  Vector3D luminosity2(4.5, 4.3, 2.0);
  auto lamp2_surface = std::shared_ptr<Surface>(new Triangle(
      Vector3D(0.0, -4.99, 2.0),
      Vector3D(1.3, -4.99, 0.0),
      Vector3D(1.7, -4.99, 1.0)));
  
  auto lamp2 = std::shared_ptr<AbstractLightSource>(new LambertLightSource(
      lamp2_surface,
      luminosity2));
  scene->addLightSource(lamp2);
  
  auto lamp2_object = std::shared_ptr<Object3D>(new HomogeneousObject(
      lamp2_surface,
      std::shared_ptr<AbstractMaterial>(new LightMaterial(luminosity2))
    )); 

  scene->addObject(lamp2_object);
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
  scene.render("default.hdr", camera, 800, pixel_grid_size);
  //scene.test(Ray(Vector3D(5.0, 3.0, -2.5), Vector3D(-1.0, 0.0, 0.0)));

  return 0;
}
