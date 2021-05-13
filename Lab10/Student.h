#pragma once
#include <fstream>
#include <vector>
#include <ostream>

struct Student {
  long num;
  char name[10];
  int group;
  double grade;
  friend bool operator==(Student& left, const Student& right);
};

std::istream& operator>>(std::istream& in, Student& s);
std::ostream& operator<<(std::ostream& out, const Student& s);

class StudContainer {
  std::vector<Student> rep;
 public:
  StudContainer();
  StudContainer(const StudContainer& c);
  int size();
  
  friend std::istream& operator>>(std::istream& in, StudContainer& s);
  friend std::ostream& operator<<(std::ostream& out, const StudContainer& s);
  friend StudContainer operator+(const StudContainer& left,
                                 const StudContainer& right);
  friend StudContainer operator*(const StudContainer& left,
                                 const StudContainer& right);
  friend StudContainer operator-(const StudContainer& left,
                                 const StudContainer& right);
  void operator=(const StudContainer& other);

  StudContainer sort_by_num();
  StudContainer sort_by_name();
  StudContainer sort_by_group();
  void write_bin(std::ofstream& out);
  void read_bin(std::ifstream& in);
};
