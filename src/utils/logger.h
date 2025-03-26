#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include <fmt/core.h>
#include <fmt/color.h>
#include <mpi.h>
#include <string>

/*!
 * logger level enum according to the Syslog standard
 */
enum class LoggerLevel {
  emerg,
  alert,
  crit,
  err,
  warning,
  notice,
  info,
  debug,
};

/*!
 * logger rank enum used to specify if all ranks are to write or just rank zero
 */
enum class LoggerRanks {
  zero,
  all,
};

class Logger {
public:
  Logger(LoggerLevel level, LoggerRanks ranks);
  ~Logger();
  void log(LoggerLevel level, LoggerRanks ranks, int rank,
           const std::string &msg);

private:
  void emerg(int rank, const std::string &msg);
  void alert(int rank, const std::string &msg);
  void crit(int rank, const std::string &msg);
  void err(int rank, const std::string &msg);
  void warning(int rank, const std::string &msg);
  void notice(int rank, const std::string &msg);
  void info(int rank, const std::string &msg);
  const LoggerLevel level_;
  const LoggerRanks ranks_;
};


#endif //UTILS_LOGGER_H
