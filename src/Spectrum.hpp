/*#pragma once*/

//#include <string>
//#include <vector>

//class Spectrum {
 //public:
  //explicit Spectrum(
      //const std::vector<double> &values = 
      //{0.0},
      //const std::vector<double> &frequencies = {});

  //static Spectrum fromCsvFile(const std::string &path);
  //static std::vector<Spectrum> manyFromCsvFile(const std::string &path);

  //int size() const;
  //double sum() const;
  //Spectrum normalized() const;
  //Spectrum operator -() const;
  //Spectrum operator +() const;
  //double operator [](int i) const;
  //double interpolate(double frequency) const;

  //friend bool operator ==(const Spectrum &a, const Spectrum &b);
  //friend bool operator !=(const Spectrum &a, const Spectrum &b);
 
  //friend Spectrum operator +(double a, const Spectrum &b);
  //friend Spectrum operator +(const Spectrum &a, double b);
  //friend Spectrum operator +(const Spectrum &a, const Spectrum &b);
  //friend Spectrum operator -(double a, const Spectrum &b);
  //friend Spectrum operator -(const Spectrum &a, double b);
  //friend Spectrum operator -(const Spectrum &a, const Spectrum &b);
 
  //friend Spectrum operator *(double a, const Spectrum &b);
  //friend Spectrum operator *(const Spectrum &a, double b);
  //friend Spectrum operator *(const Spectrum &a, const Spectrum &b);
  //friend Spectrum operator /(const Spectrum &a, double b);
  //friend Spectrum operator /(double a, const Spectrum &b);
  //friend Spectrum operator /(const Spectrum &a, const Spectrum &b);

  //friend std::ostream & operator <<(std::ostream &stream, const Spectrum &t);

 //private:
  //std::vector<double> values_;
  //std::vector<double> freqs_;
  //// hash_;
//};

//bool operator ==(const Spectrum &a, const Spectrum &b);
//bool operator !=(const Spectrum &a, const Spectrum &b);

//Spectrum operator +(const Spectrum &a, const Spectrum &b);
//Spectrum operator -(const Spectrum &a, const Spectrum &b);

//Spectrum operator *(double a, const Spectrum &b);
//Spectrum operator *(const Spectrum &a, double b);
//Spectrum operator *(const Spectrum &a, const Spectrum &b);
//Spectrum operator /(const Spectrum &a, double b);
//Spectrum operator /(double a, const Spectrum &b);
//Spectrum operator /(const Spectrum &a, const Spectrum &b);

//std::ostream & operator <<(std::ostream &stream, const Spectrum &t);
