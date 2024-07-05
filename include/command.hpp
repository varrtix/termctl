#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

class cmds {
public:
  static void help();
  static void list();
  static void exit();
  static void get(const std::string &param);
  static void set(const std::string &param, const std::string &value);
};

void cmds::help() {
  std::cout << "Available commands: help, list, exit, get <param>, set <param> "
               "<value>"
            << std::endl;
}

void cmds::list() { std::cout << "Listing items..." << std::endl; }

void cmds::exit() {
  std::cout << "Exiting..." << std::endl;
  std::exit(0);
}

void cmds::get(const std::string &param) {
  std::cout << "Getting parameter: " << param << std::endl;
}

void cmds::set(const std::string &param, const std::string &value) {
  std::cout << "Setting parameter " << param << " to " << value << std::endl;
}

#endif // CMDS_H
