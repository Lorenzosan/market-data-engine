#ifndef COMMAND_LINE_OPTIONS_H__
#define COMMAND_LINE_OPTIONS_H__

#pragma once

#include <string>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

// Handle command line options

// Options:
//  [-h|--help]
//  [-v|--version]
//  [-f|--file] ARG (std::string)

class CommandLineOptions {
public:
  CommandLineOptions();
  ~CommandLineOptions();

  enum statusReturn {
    OPTS_SUCCESS,
    OPTS_VERSION,
    OPTS_HELP,
    OPTS_FAILURE
  };

  statusReturn parse(int argc, char* argv[]);

  inline const std::string& getInputFile() const;

protected:
  void setup();
  bool validateFiles();

private:
  CommandLineOptions(const CommandLineOptions &rhs) = delete;
  CommandLineOptions& operator=(const CommandLineOptions &rhs) = delete;

  po::options_description myOptions;
  std::string myInputFile;
};


inline const std::string& CommandLineOptions::getInputFile() const {
  static const std::string emptyString;
  return (0 < myInputFile.size()) ? myInputFile : emptyString;
}

#endif // COMMAND_LINE_OPTIONS_H__
