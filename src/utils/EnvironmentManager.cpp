#include "EnvironmentManager.h"

EnvironmentManager::EnvironmentManager(int &argc, char **argv,
                                       const LoggerLevel level,
                                       const LoggerRanks ranks) : level(level),
  ranks(ranks) {
  // initialize MPI environment
  MPI_Init(&argc, &argv);
  comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);
}

EnvironmentManager::~EnvironmentManager() {
  // end any remaining timers
  if (!timers.empty()) {
    log(LoggerLevel::warning,
        "Timers are running at the time of environment destruction.");
    for (auto timer : timers) {
      timer_stop();
    }
  }

  // terminate MPI environment
  MPI_Finalize();
}

void EnvironmentManager::log(const LoggerLevel level, const std::string &msg) {
  if (sufficient_rank() && sufficient_level(level)) {
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

bool EnvironmentManager::sufficient_level(const LoggerLevel level) const {
  if (level <= this->level) {
    return true;
  }
  return false;
}

bool EnvironmentManager::sufficient_rank() const {
  if (LoggerRanks::zero == ranks) {
    return 0 == rank;
  } else {
    return true;
  }
}


void EnvironmentManager::timer_start(LoggerLevel level,
                                     const std::string &name) {
  if (sufficient_rank() && sufficient_level(level)) {
    timers.emplace_back(std::chrono::high_resolution_clock::now(), level, name);
    log(level, "Timer: `" + name + "` started at: " + fmt::format(
                   fmt::runtime("{:%Y-%m-%d %H:%M:%S}"), timers.back().start));
  }
}

void EnvironmentManager::timer_stop() {
  if (sufficient_rank() && !timers.empty()) {
    const auto end = std::chrono::high_resolution_clock::now();
    const auto timer = timers.back();
    const auto duration = end - timer.start;
    log(timer.level,
        "Timer: `" + timer.name + "` stopped at: " + fmt::format(
            fmt::runtime("{:%Y-%m-%d %H:%M:%S}"),
            end) + " with duration: " + fmt::format(
            fmt::runtime("{:%H:%M:%S}"), duration));
    timers.pop_back();
  }
}
