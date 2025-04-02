#include "EnvironmentManager.h"

/*!
* main driver function and build target
* @param argc command line argument count
* @param argv command line argument vector
* @return return code
*/
int main(int argc, char **argv) {
  auto manager = EnvironmentManager(argc, argv, LoggerLevel::debug,
                                    LoggerRanks::all);

  manager.log(LoggerLevel::debug, "debug");
  manager.log(LoggerLevel::info, "info");
  manager.log(LoggerLevel::notice, "notice");
  manager.log(LoggerLevel::warning, "warning");
  manager.log(LoggerLevel::err, "err");
  manager.log(LoggerLevel::crit, "crit");
  manager.log(LoggerLevel::alert, "alert");
  manager.log(LoggerLevel::emerg, "emerg");

  manager.timer_start(LoggerLevel::debug, "debug");
  manager.timer_start(LoggerLevel::info, "info");
  manager.timer_start(LoggerLevel::notice, "notice");
  manager.timer_start(LoggerLevel::warning, "warning");
  manager.timer_start(LoggerLevel::err, "err");
  manager.timer_start(LoggerLevel::crit, "crit");
  manager.timer_start(LoggerLevel::alert, "alert");
  manager.timer_start(LoggerLevel::emerg, "emerg");

  // return success
  return EXIT_SUCCESS;
}
