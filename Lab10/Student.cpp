//Container1
#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"
#include <fstream>
#include <vector>
#include <ostream>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

bool operator==(const Student& left, const Student& right) {
  if (left.num != right.num) {
    return false;
  }
  if (left.name[0] != right.name[0]) {
    return false;
  }
  for (int i = 1; left.name[i - 1] != '\n'; ++i) {
    if (left.name[i] != right.name[i]) {
      return false;
    }
  }
  if (left.group != right.group) {
    return false;
  }
  if (left.grade != right.grade) {
    return false;
  }
  return true;
}

std::istream& operator>>(std::istream& in, Student& s) {
  std::string str;
  std::getline(in, str, '\n');
  int numb = 0, i = 0, j = 0;
  for (; i < 7; ++i) {
    int tmp = str[i] - 48;
    numb = numb * 10 + tmp;
  }
  s.num = numb;
  ++i;
  for (; i < 18; ++i) {
    s.name[j] = str[i];
    ++j;
  }
  if (j < 9) {
    s.name[j] = '\n';
  } else {
    s.name[9] = '\n';
  }
  numb = 0;
  ++i;
  for (; i < 21; ++i) {
    if (str[i] == ' ') {
      ++i;
    }
    int tmp = str[i] - 48;
    numb = numb * 10 + tmp;
  }
  s.group = numb;
  numb = str[i + 1] - 48;
  int numb2 = str[i + 3] - 48;
  s.grade = numb + numb2 / static_cast<double>(10);
  return in;
}

std::ostream& operator<<(std::ostream& out, const Student& s) {
  out << std::setw(7) << s.num << " ";
  int counter = 0;
  for (int i = 0; s.name[i] != '\n'; ++i) {
    out << s.name[i];
    ++counter;
  }
  out << " " << std::setw(2) << s.group << " " << std::setw(3) << s.grade;
  return out;
}

std::istream& operator>>(std::istream& in, StudContainer& s) {
  while (!in.eof()) {
    Student st;
    in >> st;
    s.rep.push_back(st);
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const StudContainer& s) {
  for (unsigned int i = 0; i < s.rep.size(); i++) {
    out << s.rep[i];
    out << "\n";
  }
  return out;
}

StudContainer::StudContainer() { rep.resize(0); }

StudContainer::StudContainer(const StudContainer& s) { rep = s.rep; }

int StudContainer::size() { return rep.size(); }

StudContainer operator+(StudContainer const& left, StudContainer const& right) {
  int resSize = left.rep.size() + right.rep.size();
  StudContainer res;
  for (unsigned int i = 0; i < left.rep.size(); i++) {
    res.rep.push_back(left.rep[i]);
  }
  Student tmp;
  for (size_t i = 0; i < right.rep.size(); i++) {
    tmp = right.rep[i];
    if (std::find_if(left.rep.begin(), left.rep.end(), [tmp](Student term) {
          return (tmp == term);
        }) == left.rep.end()) {
      res.rep.push_back(right.rep[i]);
    }
  }
  return res;
}

StudContainer operator*(StudContainer const& left, StudContainer const& right) {
  StudContainer res;
  Student tmp;
  for (size_t i = 0; i < right.rep.size(); i++) {
    tmp = right.rep[i];
    if (std::find_if(left.rep.begin(), left.rep.end(), [tmp](Student term) {
          return (tmp == term);
        }) !=
        left.rep.end()) {
      res.rep.push_back(right.rep[i]);
    }
  }
  return res;
}

StudContainer operator-(StudContainer const& left, StudContainer const& right) {
  StudContainer res;
  Student tmp;
  for (size_t i = 0; i < right.rep.size(); i++) {
    tmp = right.rep[i];
    if (std::find_if(left.rep.begin(), left.rep.end(), [tmp](Student term) {
          return (tmp == term);
        }) ==
        left.rep.end()) {
      res.rep.push_back(right.rep[i]);
    }
  }
  return res;
}

void StudContainer::operator=(const StudContainer& other) {
  rep = other.rep;
}

StudContainer StudContainer::sort_by_num() {
  StudContainer res = *this;
  sort(res.rep.begin(), res.rep.end(), [](Student a, Student b) { return a.num < b.num; });
  return res;
}

StudContainer StudContainer::sort_by_name() {
  StudContainer res = *this;
  sort(
      res.rep.begin(), res.rep.end(),
      [](const Student& a, const Student& b) -> bool {
    return (strcmp(a.name, b.name) == -1);
  });
  return res;
}

StudContainer StudContainer::sort_by_group() {
  StudContainer res = *this;
  sort(res.rep.begin(), res.rep.end(), [](Student a, Student b) {
    if (a.group == b.group) {
      return (strcmp(a.name, b.name) == -1);
    }
    return (a.group < b.group);
  });
  return res;
}

void StudContainer::write_bin(std::ofstream& out) {
    out.write((char*)&rep[0], sizeof(Student) * rep.size()); 
}

void StudContainer::read_bin(std::ifstream& in) {
  if (!in.good()) {
    std::cout << "****!!!\n";
    return;
  }
    in.seekg(0, std::ios::end);
    int count = in.tellg();
    count /= sizeof(Student);
    in.seekg(std::ios::beg);
    rep.resize(count);
    in.read((char*)&rep[0], sizeof(Student) * count);
}
