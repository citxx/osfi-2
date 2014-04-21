/*#include <algorithm>*/
//#include <cmath>
//#include <fstream>
//#include <iostream>
//#include <numeric>
//#include <string>
//#include <utility>

//#include "Spectrum.hpp"
//#include "utils.hpp"

//const double Spectrum::EPS = 1e-6;

//Spectrum::Spectrum(
    //const std::vector<double> &values,
    //const std::vector<double> &frequencies): values_(values), freqs_(frequencies) {
  //if (freqs_.empty()) {
    //for (int i = 0; i < static_cast<int>(values_.size()); ++i) {
      //freqs_.push_back(static_cast<double>(i));
    //}
  //}
//}

//Spectrum Spectrum::fromCsvFile(const std::string &path) {
  //std::ifstream file(path);
  //std::vector<double> frequency, value;

  //std::string line;
  //while (file >> line) {
    //if (!line.empty()) {
      //std::vector<std::string> fields = utils::split(line, ",");
      //if (fields.size() != 2) {
        //throw "Invalid spectrum file format near '" + line + "'";  
      //}
      //frequency.push_back(std::stod(fields[0]));
      //value.push_back(std::stod(fields[1]));
    //}
  //}
  //file.close();

  //// TODO: check if sorted

  //return Spectrum(value, frequency);
//}

//std::vector<Spectrum> Spectrum::manyFromCsvFile(const std::string &path) {
  //std::ifstream file(path);
  //std::vector<double> frequency;
  //std::vector<std::vector<double>> values;

  //std::string line;
  //while (file >> line) {
    //if (!line.empty()) {
      //std::vector<std::string> fields = utils::split(line, ",");
      //if (!values.empty() && values.size() + 1 != fields.size()) {
        //throw "Invalid spectrum file format near '" + line + "'";
      //}
      //frequency.push_back(std::stod(fields[0]));
      //if (values.empty()) {
        //values.resize(static_cast<int>(fields.size()) - 1);
      //}
      //for (int i = 1; i < static_cast<int>(fields.size()); ++i) {
        //values[i - 1].push_back(std::stod(fields[i]));
      //}
    //}
  //}
  //file.close();

  //std::vector<Spectrum> result;
  //for (auto value : values) {
    //result.push_back(Spectrum(value, frequency));
  //}
  //return result;
//}

//int Spectrum::size() const {
  //return values_.size();
//}

//double Spectrum::sum() const {
  //return std::accumulate(values_.begin(), values_.end(), 0.0);
//}

//Spectrum Spectrum::normalized() const {
  //return *this / sum();
//}

//Spectrum Spectrum::operator -() const {
  //std::vector<double> v(values_.size());
  //std::transform(values_.begin(), values_.end(), v.begin(), [](double x) { return -x; });
  //return Spectrum(v, freqs_);
//}

//Spectrum Spectrum::operator +() const {
  //return *this;
//}

//double Spectrum::operator [](int i) const {
  //return values_[i];
//}

//double Spectrum::interpolate(double frequency) const {
  //// Binary search for first element greater than 'frequency'
  //int left = -1, right = freqs_.size();
  //while (left + 1 < right) {
    //int middle = (left + right) / 2.0;
    //if (freqs_[middle] <= frequency) {
      //left = middle;
    //} else {
      //right = middle;
    //}
  //}
  //int upper_i = right;

  //if (upper_i == 0) {
    //return 0.0;
  //} else if (fabs(freqs_[upper_i - 1] - frequency) < EPS) {
    //return values_[upper_i - 1];
  //} else if (right == freqs_.size()) {
    //return 0.0;
  //} else {
    //double lf = freqs_[upper_i - 1], rf = freqs_[upper_i];
    //double alpha = (frequency - lf) / (rf - lf);
    //return (1 - alpha) * values_[upper_i - 1] + alpha * values_[upper_i];
  //}
//}

//bool operator ==(const Spectrum &a, const Spectrum &b) {
  //// Check for hashes
  //// The next only if hashes are equal
  //if (a.values_.size() != b.values_.size() ||
      //a.freqs_.size() != b.freqs_.size()) {
    //return false;
  //}

  //for (int i = 0; i < static_cast<int>(a.values_.size()); ++i) {
    //if (abs(a.freqs_[i] - b.freqs_[i]) > EPS) {
      //return false;
    //}
    //if (abs(a.values_[i] - b.values_[i]) > EPS) {
      //return false;
    //}
  //}
  
  //return true;
//}

//bool operator !=(const Spectrum &a, const Spectrum &b) {
  //return !(a == b);
//}

//Spectrum operator +(const Spectrum &a, const Spectrum &b) {
  //std::vector<double> v(a.values_);
  //// If hashes are equal then
  //for (int i = 0; i < static_cast<int>(v.size()); ++i) {
    //v[i] += b.values_[i];
  //}
  //// else
  //for (int i = 0; i < static_cast<int>(v.size()); ++i) {
    //v[i] += b.interpolate(a.freqs_[i]);
  //}
  //return Spectrum(a.first_freq_, a.step_freq_, v);
//}

//Spectrum operator +(double a, const Spectrum &b) {
  //std::vector<double> v(b.values_.size());
  //std::transform(b.values_.begin(), b.values_.end(), v.begin(), [a](double x) { return a + x; });
  //return Spectrum(b.first_freq_, b.step_freq_, v);
//}

//Spectrum operator +(const Spectrum &a, double b) {
  //std::vector<double> v(a.values_.size());
  //std::transform(a.values_.begin(), a.values_.end(), v.begin(), [b](double x) { return x + b; });
  //return Spectrum(a.first_freq_, a.step_freq_, v);
//}

//// TODO: replace with copy of operator +
//Spectrum operator -(const Spectrum &a, const Spectrum &b) {
  //std::vector<double> v(a.values_);
  //for (int i = 0; i < static_cast<int>(v.size()); ++i) {
    //v[i] -= b.values_[i];
  //}
  //return Spectrum(a.first_freq_, a.step_freq_, v);
//}

//Spectrum operator -(double a, const Spectrum &b) {
  //std::vector<double> v(b.values_.size());
  //std::transform(b.values_.begin(), b.values_.end(), v.begin(), [a](double x) { return a - x; });
  //return Spectrum(b.first_freq_, b.step_freq_, v);
//}

//Spectrum operator -(const Spectrum &a, double b) {
  //std::vector<double> v(a.values_.size());
  //std::transform(a.values_.begin(), a.values_.end(), v.begin(), [b](double x) { return x - b; });
  //return Spectrum(a.first_freq_, a.step_freq_, v);
//}

//// TODO: replace with copy of operator +
//Spectrum operator *(const Spectrum &a, const Spectrum &b) {
  //std::vector<double> v(a.values_);
  //for (int i = 0; i < static_cast<int>(v.size()); ++i) {
    //v[i] *= b.values_[i];
  //}
  //return Spectrum(a.first_freq_, a.step_freq_, v);
//}

//Spectrum operator *(double a, const Spectrum &b) {
  //std::vector<double> v(b.values_.size());
  //std::transform(b.values_.begin(), b.values_.end(), v.begin(), [a](double x) { return a * x; });
  //return Spectrum(b.first_freq_, b.step_freq_, v);
//}

//Spectrum operator *(const Spectrum &a, double b) {
  //std::vector<double> v(a.values_.size());
  //std::transform(a.values_.begin(), a.values_.end(), v.begin(), [b](double x) { return x * b; });
  //return Spectrum(a.first_freq_, a.step_freq_, v);
//}

//// TODO: replace with copy of operator +
//Spectrum operator /(const Spectrum &a, const Spectrum &b) {
  //std::vector<double> v(a.values_);
  //for (int i = 0; i < static_cast<int>(v.size()); ++i) {
    //v[i] /= b.values_[i];
  //}
  //return Spectrum(a.first_freq_, a.step_freq_, v);
//}

//Spectrum operator /(const Spectrum &a, double b) {
  //std::vector<double> v(a.values_.size());
  //std::transform(a.values_.begin(), a.values_.end(), v.begin(), [b](double x) { return x / b; });
  //return Spectrum(a.first_freq_, a.step_freq_, v);
//}

//Spectrum operator /(double a, const Spectrum &b) {
  //std::vector<double> v(b.values_.size());
  //std::transform(b.values_.begin(), b.values_.end(), v.begin(), [a](double x) { return a / x; });
  //return Spectrum(b.first_freq_, b.step_freq_, v);
//}


//std::ostream & operator <<(std::ostream &stream, const Spectrum &t) {
  //const int MAX_HEIGHT = 10;

  //double mx = 0;
  //for (int i = 0; i < t.size(); ++i) {
    //mx = std::max(mx, t[i]);
    //mx = std::max(mx, -t[i]);
  //}

  //int lower = 0, upper = 0;
  //std::vector<int> height(t.size());
  //for (int i = 0; i < t.size(); ++i) {
    //height[i] = round(t[i] / mx * MAX_HEIGHT);
    //lower = std::min(lower, height[i]);
    //upper = std::max(upper, height[i]);
  //}

  //stream << "Specter: from " << t.freqs_[0]
    //<< " to " << t.freqs_.back() << std::endl;

  //for (int i = upper; i > 0; --i) {
    //for (auto h : height) {
      //stream << ((h >= i) ? "#" : " ");
    //}
    //stream << std::endl;
  //}

  //for (auto h : height) {
    //stream << "-";
  //}
  //stream << std::endl;

  //for (int i = -1; i >= lower; --i) {
    //for (auto h : height) {
      //stream << ((h >= i) ? "#" : " ");
    //}
    //stream << std::endl;
  //}

  //return stream;
/*}*/
