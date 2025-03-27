#include "EnvironmentManager.h"

EnvironmentManager::~EnvironmentManager() {
  // terminate MPI environment
  MPI_Finalize();
}


void EnvironmentManager::log_emerg(const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::dark_red), "[EMERG]");
  fmt::print(": {}\n", msg);
}

void EnvironmentManager::log_alert(const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::red), "[ALERT]");
  fmt::print(": {}\n", msg);
}

void EnvironmentManager::log_crit(const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::dark_orange), "[CRIT]");
  fmt::print(": {}\n", msg);
}

void EnvironmentManager::log_err(const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::orange), "[ERR]");
  fmt::print(": {}\n", msg);
}

void EnvironmentManager::log_warning(const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::orange), "[WARNING]");
  fmt::print(": {}\n", msg);
}

void EnvironmentManager::log_notice(const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::green), "[NOTICE]");
  fmt::print(": {}\n", msg);
}


void EnvironmentManager::log_info(const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::blue), "[INFO]");
  fmt::print(": {}\n", msg);
}

void EnvironmentManager::log_debug(const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::purple), "[DEBUG]");
  fmt::print(": {}\n", msg);
}