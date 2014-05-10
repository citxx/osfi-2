#include <iostream>

#include "AbstractMaterial.hpp"

/*void AbstractMaterial::shade(*/
    //const Scene &scene,
    //const Vector3D &direction,
    //const Vector3D &hit_point,
    //const Vector3D &normal,
    //Vector3D *color,
    //Vector3D *k,
    //Ray *ray) const {
  //Vector3D n = normal.normalized();
  //Vector3D dir = direction.normalized();

  //double secondary_p;
  //Vector3D secondary_k;
  //Ray secondary_ray;
  //secondaryRay(scene, dir, hit_point, n, &secondary_p, &secondary_k, &secondary_ray);

  //Vector3D primary_radiosity;
  //double primary_p, primary_secondary_p;
  //Ray primary_ray;
  //directIllumination(
      //scene,
      //dir,
      //hit_point,
      //n,
      //secondary_ray,
      //&primary_secondary_p, &primary_p, &primary_radiosity, &primary_ray);
  //double secondary_primary_p = importanceDensity(dir, n, primary_ray.direction);

  //double primary_w = 1.0 / (primary_p + primary_secondary_p);
  //double secondary_w = 1.0 / (secondary_p + secondary_primary_p);
  ////std::cerr << direct_p << " " << secondary_p << " " << direct_w << " " << secondary_w << std::endl;
  //if (p > 1e-6) {
    //*color = direct_radiosity * primary_w;
    //*k = secondary_k * secondary_w;  // TODO: wtf
  //} else {
    //*k = Vector3D();
  //}
  //*ray = secondary_ray;

  ////std::cerr << p << " " << direct_radiosity << " " << *color << " " << secondary_k << std::endl;
//}

//void AbstractMaterial::directIllumination(
      //const Scene &scene,
      //const Vector3D &direction,
      //const Vector3D &hit_point,
      //const Vector3D &normal,
      //const Vector3D &secondary_ray,
      //double *secondary_probability,
      //double *probability,
      //Vector3D *radiosity) const {
  //directIllumination(scene, direction, hit_point, normal, probability, radiosity, nullptr);
/*}*/
