#include "EnvironmentManager.h"

EnvironmentManager::EnvironmentManager(int &argc, char **argv,
                                       const LoggerLevel level,
                                       const LoggerRanks ranks) :
  log_level(level), log_ranks(ranks) {
  // initialize MPI environment
  MPI_Init(&argc, &argv);
  comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);
}

EnvironmentManager::~EnvironmentManager() {
  // terminate MPI environment
  MPI_Finalize();
}

void EnvironmentManager::log(const LoggerLevel level, const LoggerRanks ranks,
                             const std::string &msg) {
  if (level <= log_level) {
    switch (level) {
    case LoggerLevel::emerg:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          log_emerg(msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, size)) {
          if (rank == i) {
            log_emerg(msg);
          }
          MPI_Barrier(comm);
        }
        break;
      }
      break;
    case LoggerLevel::alert:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          log_alert(msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, size)) {
          if (rank == i) {
            log_alert(msg);
          }
          MPI_Barrier(comm);
        }
        break;
      }
      break;
    case LoggerLevel::crit:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          log_crit(msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, size)) {
          if (rank == i) {
            log_crit(msg);
          }
          MPI_Barrier(comm);
        }
        break;
      }
      break;
    case LoggerLevel::err:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          log_err(msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, size)) {
          if (rank == i) {
            log_err(msg);
          }
          MPI_Barrier(comm);
        }
        break;
      }
      break;
    case LoggerLevel::warning:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          log_warning(msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, size)) {
          if (rank == i) {
            log_warning(msg);
          }
          MPI_Barrier(comm);
        }
        break;
      }
      break;
    case LoggerLevel::notice:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          log_notice(msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, size)) {
          if (rank == i) {
            log_notice(msg);
          }
          MPI_Barrier(comm);
        }
        break;
      }
      break;
    case LoggerLevel::info:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          log_info(msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, size)) {
          if (rank == i) {
            log_info(msg);
          }
          MPI_Barrier(comm);
        }
        break;
      }
      break;
    case LoggerLevel::debug:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          log_debug(msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, size)) {
          if (rank == i) {
            log_debug(msg);
          }
          MPI_Barrier(comm);
        }
        break;
      }
      break;
    }
  }
}

void EnvironmentManager::abort(const std::string &msg) {
  log_emerg(msg);
  MPI_Abort(comm, EXIT_FAILURE);
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