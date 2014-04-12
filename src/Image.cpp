#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>

#include "Image.hpp"

Image::Image(int width, int height):
  width_(width),
  height_(height),
  data_(3 * width * height, 0.0) {}

void Image::setPixel(int x, int y, double r, double g, double b) {
  int pixel_pos = 3 * (width_ * y + x);
  data_[pixel_pos] = r;
  data_[pixel_pos + 1] = g;
  data_[pixel_pos + 2] = b;
}

void Image::getPixel(int x, int y, double *r, double *g, double *b) {
  int pixel_pos = 3 * (width_ * y + x);
  *r = data_[pixel_pos];
  *g = data_[pixel_pos + 1];
  *b = data_[pixel_pos + 2];
}

void Image::savePPM(const std::string &path) const {
  std::ofstream file(path);

  file << "P3" << std::endl;
  file << width_ << " " << height_ << std::endl;
  file << "255" << std::endl;
  float mn = *std::min_element(data_.begin(), data_.end());
  float mx = *std::max_element(data_.begin(), data_.end());
  for (auto value : data_) {
    file << static_cast<int>(round(255 * pow((value - mn) / (mx - mn), 1 / 2.2))) << std::endl;
  }

  file.close();
}
