#ifndef LOG_H_
#define LOG_H_


#include <sstream>


#define LogInfo ewok::Log().get(ewok::LOG_INFO)
#define LogWarn ewok::Log().get(ewok::LOG_WARN)
#define LogError ewok::Log().get(ewok::LOG_ERROR)

#define Assert(condition, msg)                                          \
  do {                                                                  \
    if ((condition) == false) {                                         \
      ewok::Log().get(ewok::LOG_ERROR) << msg << std::endl << "Assertion: '" << #condition << "' failed" << std::endl;      \
        abort();                                                        \
    }                                                                   \
  } while (false)


namespace ewok {

  enum LogLevel {
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
  };


  static const char *LogPrefix[] = {
    "INFO:  ",
    "WARN:  ",
    "ERROR: "
  };


  class Log {
  public:
    Log() {}
    ~Log()
    {
      os_ << std::endl;
      fprintf(stderr, "%s", os_.str().c_str());
      fflush(stderr);
    }     

    std::ostringstream &get(LogLevel level)
    {
      os_ << LogPrefix[level];
      return os_;
    }
    
  private:
    Log(const Log &log) {}
    Log &operator=(const Log &other) { return *this; }
    
    std::ostringstream os_;
  };

} // namespace ewok


#endif  // LOG_H_
