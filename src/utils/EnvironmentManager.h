#ifndef UTILS_ENVIRONMENTMANAGER_H
#define UTILS_ENVIRONMENTMANAGER_H

#include <chrono>
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/color.h>
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
   * @param ranks MPI ranks to log on
   * @param msg message to log
   */
  void log(LoggerLevel level, LoggerRanks ranks, const std::string &msg);

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

  /// highest level to log at
  const LoggerLevel log_level;

  /// ranks to log on
  const LoggerRanks log_ranks;

  /// stack of times
  struct times {
    /*!
     *
     * @param level
     * @param ranks
     * @param msg
     */
    void begin(LoggerLevel level, LoggerRanks ranks, const std::string &msg);

    /*!
     *
     */
    void end();

    /*!
     *
     */
    std::vector<std::chrono::time_point<std::chrono::system_clock>> time_starts;

    /*!
     *
     */
    std::vector<LoggerLevel> time_levels;

    /*!
     *
     */
    std::vector<LoggerRanks> time_ranks;

    /*!
     *
     */
    std::vector<std::string> time_msgs;
  };
};

#endif //UTILS_ENVIRONMENTMANAGER_H