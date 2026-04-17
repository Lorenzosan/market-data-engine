#include "core/CommandLineOptions.h"

#include <iostream>


int main(int argc, char* argv[]) {
  CommandLineOptions opts;
  CommandLineOptions::statusReturn status = opts.parse(argc, argv);

  if(status == CommandLineOptions::OPTS_SUCCESS) {
    std::cout << "Using: " << opts.getInputFile() << std::endl;
    return 0;
  }

  if(status == CommandLineOptions::OPTS_HELP) {
    return 0;
  }

  if(status == CommandLineOptions::OPTS_VERSION) {
    std::cout << "Version output not implemented yet" << std::endl;
    return 0;
  }

  std::cout << "Error - problem with opts.parse" << std::endl;
  return 1;
}
