#include "distancer.h"
#include <exception>
#include <iostream>
#include <fstream>

int main() {
  #ifndef NDEBUG
  std::ofstream f("exe_debug.txt");
  #else
  std::ofstream f("exe_release.txt");
  #endif
  try
  {
    do_simulation(16);
  }
  catch (std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Error: Unknown\n";
    return 1;
  }
}
