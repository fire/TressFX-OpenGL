#include <ctime>
#include <cstring>
// #include <algorithm>

// Available patterns:
// - %h - hours
// - %m - minutes
// - %s - seconds
// - %p - log level (shortened to D/I/W/E)
// - %f - filename
// - %l - line
//
// e.g.
//  - "%h:%m:%s %f:%l [%p] "
//  - "%f:%l [%p] ";
logger::LogImpl::LogPattern logger::LogImpl::Pattern = "%f:%l [%p] ";

const char* level_symbol[] = {"T", "D","I","W","E"};

#define LOC_ACCURACY 5
#define FILENAME_LETTERS 25

namespace logger {


  struct MsgMetaData {
    logger::LogLevel level;
    char* const file_name;
    int line;
    std::tm* time;
  };

  LogImpl& Log::get(const char* const file_name, const int line, LogLevel level){
    std::time_t t = std::time(0);
    return *impl;
  }
}