#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include <fmt/core.h>
#include <fmt/color.h>
#include <mpi.h>
#include <string>
#include <ranges>

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
  void log(LoggerLevel level, LoggerRanks ranks, int world_size, int rank,
           const std::string &msg);

private:
  static void emerg(int rank, const std::string &msg);
  static void alert(int rank, const std::string &msg);
  static void crit(int rank, const std::string &msg);
  static void err(int rank, const std::string &msg);
  static void warning(int rank, const std::string &msg);
  static void notice(int rank, const std::string &msg);
  static void info(int rank, const std::string &msg);
  static void debug(int rank, const std::string &msg);
  const LoggerLevel level_;
  const LoggerRanks ranks_;
};


#endif //UTILS_LOGGER_H
