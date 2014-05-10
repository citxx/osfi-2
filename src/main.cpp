#include <cmath>
#include <ctime>
#include <iostream>
#include <memory>

#include "AbstractMaterial.hpp"
#include "Camera.hpp"
//#include "CombinedMaterial.hpp"
#include "CookTorranceMaterial.hpp"
#include "HomogeneousObject.hpp"
#include "LambertMaterial.hpp"
#include "LightMaterial.hpp"
#include "PhongMaterial.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "SpecularMaterial.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Vector3D.hpp"
#include "WardAnisotropicMaterial.hpp"

void cornellBox(Scene *scene) {
  auto blue = std::shared_ptr<AbstractMaterial>(
      new LambertMaterial(Vector3D(0.1, 0.1, 1.0)));

  auto red = std::shared_ptr<AbstractMaterial>(
      new LambertMaterial(Vector3D(1.0, 0.1, 0.1)));

  auto white = std::shared_ptr<AbstractMaterial>(
      new LambertMaterial(Vector3D(1.0, 1.0, 1.0)));

  auto gray = std::shared_ptr<AbstractMaterial>(
      new LambertMaterial(Vector3D(0.2, 0.2, 0.2)));

  auto reflective = std::shared_ptr<AbstractMaterial>(
      new SpecularMaterial(
        Vector3D(0.8, 0.8, 0.8),
        Vector3D(INFINITY, INFINITY, INFINITY)));

  auto reflective_green = std::shared_ptr<AbstractMaterial>(
      new SpecularMaterial(
        Vector3D(0.1, 0.7, 0.05),
        Vector3D(INFINITY, INFINITY, INFINITY)));

  auto reflective_orange = std::shared_ptr<AbstractMaterial>(
      new SpecularMaterial(
        Vector3D(0.8, 0.4, 0.05),
        Vector3D(INFINITY, INFINITY, INFINITY)));

  auto refractive = std::shared_ptr<AbstractMaterial>(
      new SpecularMaterial(
        Vector3D(0.8, 0.8, 0.8),
        Vector3D(2.6, 2.6, 2.6)));

  auto refractive_yellow = std::shared_ptr<AbstractMaterial>(
      new SpecularMaterial(
        Vector3D(0.8, 0.8, 0.1),
        Vector3D(1.8, 1.8, 1.8)));

  auto refractive_magneta = std::shared_ptr<AbstractMaterial>(
      new SpecularMaterial(
        Vector3D(0.6, 0.1, 0.6),
        Vector3D(1.4, 1.4, 1.4)));

  auto ct1 = std::shared_ptr<AbstractMaterial>(
      new CookTorranceMaterial(reflective_orange, 0.1));

  //auto ct2 = std::shared_ptr<AbstractMaterial>(
      //new CookTorranceMaterial(refractive_magneta, 0.25));

  //auto ct3 = std::shared_ptr<AbstractMaterial>(
      //new CookTorranceMaterial(refractive_yellow, 0.01));

  auto ward1 = std::shared_ptr<AbstractMaterial>(
      new WardAnisotropicMaterial(Vector3D(0.8, 0.4, 0.8), 0.001, 10.0));

  auto ward2 = std::shared_ptr<AbstractMaterial>(
      new WardAnisotropicMaterial(Vector3D(0.1, 0.8, 0.4), 10.0, 0.001));

  //auto refl_m = std::shared_ptr<AbstractMaterial>(
      //new CombinedMaterial({
        //{0.2, gray},
        //{0.8, reflective}}));

  //auto refr_m = std::shared_ptr<AbstractMaterial>(
      //new CombinedMaterial({
        //{0.2, gray},
        //{0.8, refractive}}));

  auto phong_m = std::shared_ptr<AbstractMaterial>(
      new PhongMaterial(
        Vector3D(0.8, 0.5, 0.6),
        16.5));

  auto sphere11 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Sphere(
          Vector3D(-2.5, -3.2, -2.5),
          1.5)),
      phong_m));
  scene->addObject(sphere11);

  auto sphere21 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Sphere(
          Vector3D(-2.5, 0.0, -2.5),
          1.5)),
      reflective_green));
      //refl_m));
  scene->addObject(sphere21);

  auto sphere31 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Sphere(
          Vector3D(-2.5, 3.2, -2.5),
          1.5)),
      gray));
  scene->addObject(sphere31);

  auto sphere12 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Sphere(
          Vector3D(0.5, -3.2, -3.0),
          1.0)),
      ct1));
  scene->addObject(sphere12);

  auto sphere22 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Sphere(
          Vector3D(2.0, -1.1, -3.2),
          0.8)),
      ward1));
  scene->addObject(sphere22);

  auto sphere32 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Sphere(
          Vector3D(2.0, 1.1, -3.2),
          0.8)),
      ward2));
  scene->addObject(sphere32);

  auto sphere42 = std::shared_ptr<Object3D>(new HomogeneousObject(
      std::shared_ptr<Surface>(new Sphere(
          Vector3D(0.5, 3.2, -3.0),
          1.0)),
      refractive_yellow));
  scene->addObject(sphere42);

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

  Vector3D luminosity(2.0, 2.0, 2.0);
  //auto lamp_surface = std::shared_ptr<Surface>(new Sphere(
      //Vector3D(0.0, 0.0, 3.0),
      //0.4));
  auto lamp_surface = std::shared_ptr<Surface>(new Triangle(
      Vector3D(0.0, 1.0, 3.99999),
      Vector3D(-3.0, 0.0, 3.99999),
      Vector3D(-1.0, 2.0, 3.99999)));

  auto lamp = std::shared_ptr<AbstractLightSource>(new LambertLightSource(
      lamp_surface,
      luminosity));
  
  auto lamp_object = std::shared_ptr<Object3D>(new HomogeneousObject(
      lamp_surface,
      std::shared_ptr<AbstractMaterial>(new LightMaterial(luminosity))
    )); 

  scene->addLightSource(lamp, lamp_object);

  Vector3D luminosity2(1.5, 1.3, 0.6);
  auto lamp2_surface = std::shared_ptr<Surface>(new Triangle(
      Vector3D(0.0, -4.99999, 2.0),
      Vector3D(1.3, -4.99999, 0.0),
      Vector3D(1.7, -4.99999, 1.0)));
  
  auto lamp2 = std::shared_ptr<AbstractLightSource>(new LambertLightSource(
      lamp2_surface,
      luminosity2));
  
  auto lamp2_object = std::shared_ptr<Object3D>(new HomogeneousObject(
      lamp2_surface,
      std::shared_ptr<AbstractMaterial>(new LightMaterial(luminosity2))
    )); 

  scene->addLightSource(lamp2, lamp2_object);
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  int pixel_grid_size = 4;
  if (argc > 1) {
    pixel_grid_size = std::stoi(argv[1]);
  }

  Scene scene;
  cornellBox(&scene);

  Camera camera(Vector3D(13.0, 0.0, 2.0), Vector3D(-13.0, 0.0, -2.0), 0.34 * M_PI, 0.25 * M_PI);
  scene.render("default.hdr", camera, 800, pixel_grid_size);
  //scene.test(Ray(Vector3D(5.0, 3.0, -2.5), Vector3D(-1.0, 0.0, 0.0)));

  return 0;
}
