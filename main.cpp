#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include <string.h>

using namespace std;

float clampedDepth ( float depthInput, float depthMin , float depthMax);

#include "bitmap_image.hpp"
int main( int argc, char* argv[] )
{
  // Fill in your implementation here.

    bool showDepth = false;
    Image* depthIm;
    string depthFileName;
    float minDepth, maxDepth, depthRange;

    bool showNormals = false;
    Image* normalIm;
    string normalFileName;

  // This loop loops over each of the input arguments.
  // argNum is initialized to 1 because the first
  // "argument" provided to the program is actually the
  // name of the executable (in our case, "a4").
  for( int argNum = 1; argNum < argc; ++argNum ) {
      std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;

      if (strcmp(argv[argNum], "-depth") == 0) {
          showDepth = true;
          minDepth = stof(argv[argNum + 1]);
          maxDepth = stof(argv[argNum + 2]);
          depthRange = maxDepth - minDepth;
          depthFileName = argv[argNum + 3];
      }
      else if (strcmp(argv[argNum], "-normals") == 0) {
          showNormals = true;
          normalFileName = argv[argNum + 1];
      }
  }

	
  // arguments are spaced-separated
    
  // First, parse the scene using SceneParser.
  // Then loop over each pixel in the image, shooting a ray
  // through that pixel and finding its intersection with
  // the scene.  Write the color at the intersection to that
  // pixel in your output image.

  SceneParser parser(argv[2]);
  int w = stoi(argv[4]);
  int h = stoi(argv[5]);
  Image image(w, h);

  if (showDepth) {
      depthIm = new Image(w, h);
  }
  if (showNormals) {
      normalIm = new Image(w, h);
  }


  Camera* cam = parser.getCamera();
  Group* scene = parser.getGroup();
  Vector3f bg = parser.getBackgroundColor();
  float tmin = cam->getTMin();

  for (size_t i = 0; i < h; i++) {
      for (size_t j = 0; j < w; j++) {
          Vector2f p((j + 0.5f) * 2.f /w - 1.f, (i + 0.5f) * 2.f /h - 1.f);
          Ray r = cam->generateRay(p);
          Hit h;
          bool hit = scene->intersect(r, h, tmin);

          if (hit) {
              Vector3f col = parser.getAmbientLight(); // ambient light intensity
              Vector3f hitPoint = r.pointAtParameter(h.getT());

              for (size_t k = 0; k < parser.getNumLights(); k++) {
                  Light* light = parser.getLight(k);
                  Vector3f cLight, lightDir; // light intensity/color, direction to light
                  float dist2Light; // not used, nor implemented

                  light->getIllumination(hitPoint, lightDir, cLight, dist2Light); // does NOT alter hitPoint
                  col += h.getMaterial()->Shade(r, h, lightDir, cLight); // diffuse & specular, texture too
              }

              image.SetPixel(j, i, col);

              if (showDepth) {
                  float depth = (maxDepth - clamp(h.getT(), minDepth, maxDepth)) / depthRange;
                  depthIm->SetPixel(j, i, depth*Vector3f(1.f, 1.f, 1.f));
              }
              if (showNormals) {
                  Vector3f n = h.getNormal();
                  if (n[0] < 0) n[0] = -n[0];
                  if (n[1] < 0) n[1] = -n[1];
                  if (n[2] < 0) n[2] = -n[2];
                  normalIm->SetPixel(j, i, n);
              }
          }
          else {
              image.SetPixel(j, i, bg);

              if (showDepth) {
                  depthIm->SetPixel(j, i, Vector3f());
              }
              if (showNormals) {
                  normalIm->SetPixel(j, i, Vector3f());
              }
          }
      }
  }
  image.SaveImage(argv[7]);

  if (showDepth) {
      depthIm->SaveImage(&depthFileName[0]);
      delete depthIm;
  }

  if (showNormals) {
      normalIm->SaveImage(&normalFileName[0]);
      delete normalIm;
  }

  return 0;
}

