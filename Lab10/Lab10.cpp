#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ostream>
#include <istream>
#include "Student.h"
/*
int main() {
  std::ofstream out("Container1.bin", std::ios::binary);
  std::ifstream in("Container1.txt");
  StudContainer temp;
  in >> temp;
  temp.write_bin(out);
  return 0;
} */

int main() {
  std::string file_name = "";
  StudContainer first, second, res;
  int choise = -1;
  do {
    std::cout << "First file\n1) text in\n2) binary in\nSelect an "
                 "action: ";
    std::cin >> choise;
    switch (choise) {
      case 1: {
        std::cout << "Input first file name:  ";
        std::string file_name = "";
        std::cin >> file_name;
        std::ifstream input(file_name);
        if (!input.is_open()) {
          std::cout << "Error...\n";
          return 1;
        }
        while (!input.eof()) {
          input >> first;
        }
        input.close();
        break;
      }
      case 2: {
        std::cout << "Input first file name:  ";
        std::string file_name = "";
        std::cin >> file_name;
        std::ifstream input(file_name, std::ios::binary);
        if (!input.is_open()) {
          std::cout << "Error...\n";
          return 1;
        }
        first.read_bin(input);
        input.close();
        break;
      }
      default:
        std::cout << "There is no such option, try again\n";
        choise = -1;
    }
  } while (choise < 0);
  choise = -1;
  do {
    std::cout << "Second file\n1) text in\n2) binary in\nSelect an "
                 "action: ";
    std::cin >> choise;
    switch (choise) {
      case 1: {
        std::cout << "Input second file name:  ";
        std::string file_name = "";
        std::cin >> file_name;
        std::ifstream input(file_name);
        if (!input.is_open()) {
          std::cout << "Error...\n";
          return 1;
        }
        while (!input.eof()) {
          input >> second;
        }
        input.close();
        break;
      }
      case 2: {
        std::cout << "Input second file name:  ";
        std::string file_name = "";
        std::cin >> file_name;
        std::ifstream input(file_name, std::ios::binary);
        if (!input.is_open()) {
          std::cout << "Error...\n";
          return 1;
        }
        second.read_bin(input);
        input.close();
        break;
      }

      default:
        std::cout << "There is no such option, try again\n";
        choise = -1;
    }
  } while (choise < 0);
  choise = -1;
  do {
    std::cout << "1) unification\n2) intersection\n3) difference\nSelect an "
                 "action: ";
    std::cin >> choise;
    switch (choise) {
      case 1:
        res = first + second;
        break;
      case 2:
        res = first * second;
        break;
      case 3:
        res = first - second;
        break;
      default:
        std::cout << "There is no such option, try again\n";
        choise = -1;
    }
  } while (choise < 0);
  choise = -1;
  do {
    std::cout << "1) sort by number\n2) sort by group\n3) do not touch\nSelect "
                 "an action: ";
    std::cin >> choise;
    switch (choise) {
      case 1:
        res = res.sort_by_num();
        break;
      case 2:
        res = res.sort_by_name();
        break;
      case 3:
        break;
      default:
        std::cout << "There is no such option, try again\n";
        choise = -1;
    }
  } while (choise < 0);
  choise = -1;
  do {
    std::cout << "1) text out\n2) binary out\nSelect "
                 "an action: ";
    std::cin >> choise;
    switch (choise) {
      case 1: {
        std::ofstream out("output.txt");
        if (!out.is_open()) {
          std::cout << "Error...\n";
          return 1;
        }
        out << res;
      }
      case 2: {
        std::ofstream out("output.bin", std::ios::binary);
        if (!out.is_open()) {
          std::cout << "Error...\n";
          return 1;
        }
        res.write_bin(out);

        break;
      }
      default: {
        std::cout << "There is no such option, try again\n";
        choise = -1;
      }
    }
  } while (choise < 0);

  std::cout << "Thanks for the working with us!\n";
  return 0;
}