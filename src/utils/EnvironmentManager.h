#ifndef UTILS_ENVIRONMENTMANAGER_H
#define UTILS_ENVIRONMENTMANAGER_H

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

class EnvironmentManager {
public:
  EnvironmentManager(int &argc, char **argv, LoggerLevel level,
                     LoggerRanks ranks);
  ~EnvironmentManager();
  void abort(const std::string &msg);
  void log(LoggerLevel level, LoggerRanks ranks, const std::string &msg);
  /// MPI communicator
  MPI_Comm comm;

  /// rank within MPI communicator
  int rank = -1;

  /// size of MPI communicator
  int size = -1;

private:
  void log_emerg(const std::string &msg);
  void log_alert(const std::string &msg);
  void log_crit(const std::string &msg);
  void log_err(const std::string &msg);
  void log_warning(const std::string &msg);
  void log_notice(const std::string &msg);
  void log_info(const std::string &msg);
  void log_debug(const std::string &msg);
  const LoggerLevel level_;
  const LoggerRanks ranks_;
};


#endif //UTILS_ENVIRONMENTMANAGER_H
