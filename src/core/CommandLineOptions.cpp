#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string/trim.hpp>
namespace fs = boost::filesystem;

#include "core/CommandLineOptions.h"


CommandLineOptions::CommandLineOptions()
  : myOptions(""),
    myInputFile("") {
  setup();
}


CommandLineOptions::~CommandLineOptions() {}


void CommandLineOptions::setup() {
  po::options_description options("Program options");
  options.add_options()
    ("help,h", "Display help menu")
    ("version,v", "Display program version number")
    ("file,f", po::value<std::string>(&myInputFile), "User-specified input file");
  myOptions.add(options);
}


CommandLineOptions::statusReturn CommandLineOptions::parse(int argc, char* argv[]) {
  statusReturn ret = OPTS_SUCCESS;
  po::variables_map varMap;
  char filename[2000];

  try {
    po::store(po::parse_command_line(argc, argv, myOptions), varMap);
    po::notify(varMap);

    // Help option
    if(varMap.count("help")) {
      std::cout << myOptions << std::endl;
      return OPTS_HELP;
    }

    // Version info
    if(varMap.count("version")) {
      return OPTS_VERSION;
    }

    // Enforce input file argument
    if(!(0 < varMap.count("file"))) {
      std::cout << "ERROR - Input file must be specified!" << std::endl;
      std::cout << myOptions << std::endl;
      return OPTS_FAILURE;
    } else {
      // Strip whitespaces from back/front of the filename string
      boost::algorithm::trim(myInputFile);

      // Resolve the filename
      realpath(myInputFile.c_str(), filename);
      myInputFile = filename;

      ret = validateFiles() ? OPTS_SUCCESS : OPTS_FAILURE;
    }
    
  } catch(std::exception& e ) {
    std::cout << "ERROR - parsing error: " << e.what() << std::endl;
    ret = OPTS_FAILURE;
  } catch(...) {
    std::cout << "ERROR - parsing error (unknown type) " << std::endl;
    ret = OPTS_FAILURE;
  }

  return ret;
}


bool CommandLineOptions::validateFiles() {
  if(!boost::filesystem::is_regular_file(myInputFile)) {
    std::cout << "ERROR - Input file provided does not exist [" << myInputFile << "[" << std::endl;
    return false;
  }
  return true;
}

