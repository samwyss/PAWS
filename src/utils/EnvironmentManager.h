#ifndef UTILS_ENVIRONMENTMANAGER_H
#define UTILS_ENVIRONMENTMANAGER_H

#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/chrono.h>
#include <chrono>
#include <mpi.h>
#include <string>
#include <ranges>
#include <vector>

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

/*!
 *
 */
struct Timer {
  /*!
  *
  */
  std::chrono::time_point<std::chrono::system_clock> start;

  /*!
   *
   */
  LoggerLevel level;

  /*!
   *
   */
  std::string name;
};

class EnvironmentManager {
public:
  /*!
   * constructs PAWS environment
   * @param argc command line argument count
   * @param argv command line argument vector
   * @param level highest level to log
   * @param ranks ranks to log on
   */
  EnvironmentManager(int &argc, char **argv, LoggerLevel level,
                     LoggerRanks ranks);

  /*!
   * destructs PAWS environment
   */
  ~EnvironmentManager();

  /*!
   * aborts PAWS and displays error msg at emergency level
   * @param msg error message
   */
  void abort(const std::string &msg);

  /*!
   * logs msg to terminal at specified level and ranks
   * @param level Syslog level to log at
   * @param msg message to log
   */
  void log(LoggerLevel level, const std::string &msg);

  /*!
 *
 * @param level
 * @param name
 */
  void timer_start(LoggerLevel level, const std::string &name);

  /*!
   *
   */
  void timer_stop();

  /// MPI communicator
  MPI_Comm comm;

  /// rank within MPI communicator
  int rank = -1;

  /// size of MPI communicator
  int size = -1;

private:
  /*!
   * logs msg at emergency level
   * @param msg message to log
   */
  void log_emerg(const std::string &msg);

  /*!
   * logs msg at alert level
   * @param msg message to log
   */
  void log_alert(const std::string &msg);

  /*!
   * logs msg at critical level
   * @param msg message to log
   */
  void log_crit(const std::string &msg);

  /*!
   * logs msg at error level
   * @param msg message to log
   */
  void log_err(const std::string &msg);

  /*!
   * logs msg at warning level
   * @param msg message to log
   */
  void log_warning(const std::string &msg);

  /*!
   * logs msg at notice level
   * @param msg message to log
   */
  void log_notice(const std::string &msg);

  /*!
   *
   * @param msg
   */
  void log_info(const std::string &msg);

  /*!
   * logs msg at debug level
   * @param msg message to log
   */
  void log_debug(const std::string &msg);

  /*!
   * 
   * @param level 
   */
  [[nodiscard]] bool sufficient_level(LoggerLevel level) const;

  /*!
   *
   * @return
   */
  [[nodiscard]] bool sufficient_rank() const;

  /// highest level to log at
  const LoggerLevel level;

  /// ranks to log on
  const LoggerRanks ranks;

  /// stack of timers
  std::vector<Timer> timers;
};

#endif //UTILS_ENVIRONMENTMANAGER_H