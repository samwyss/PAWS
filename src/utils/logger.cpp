#include "logger.h"

Logger::Logger(const LoggerLevel level,
               const LoggerRanks ranks) : level_(level), ranks_(ranks) {

}

Logger::~Logger() = default;

void Logger::log(const LoggerLevel level, const LoggerRanks ranks,
                 const int world_size, const int rank, const std::string &msg) {

  if (level <= level_) {
    switch (level) {
    case LoggerLevel::emerg:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          emerg(rank, msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, world_size)) {
          if (rank == i) {
            emerg(rank, msg);
          }
          MPI_Barrier(MPI_COMM_WORLD);
        }
        break;
      }
      break;
    case LoggerLevel::alert:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          alert(rank, msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, world_size)) {
          if (rank == i) {
            alert(rank, msg);
          }
          MPI_Barrier(MPI_COMM_WORLD);
        }
        break;
      }
      break;
    case LoggerLevel::crit:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          crit(rank, msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, world_size)) {
          if (rank == i) {
            crit(rank, msg);
          }
          MPI_Barrier(MPI_COMM_WORLD);
        }
        break;
      }
      break;
    case LoggerLevel::err:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          err(rank, msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, world_size)) {
          if (rank == i) {
            err(rank, msg);
          }
          MPI_Barrier(MPI_COMM_WORLD);
        }
        break;
      }
      break;
    case LoggerLevel::warning:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          warning(rank, msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, world_size)) {
          if (rank == i) {
            warning(rank, msg);
          }
          MPI_Barrier(MPI_COMM_WORLD);
        }
        break;
      }
      break;
    case LoggerLevel::notice:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          notice(rank, msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, world_size)) {
          if (rank == i) {
            notice(rank, msg);
          }
          MPI_Barrier(MPI_COMM_WORLD);
        }
        break;
      }
      break;
    case LoggerLevel::info:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          info(rank, msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, world_size)) {
          if (rank == i) {
            info(rank, msg);
          }
          MPI_Barrier(MPI_COMM_WORLD);
        }
        break;
      }
      break;
    case LoggerLevel::debug:
      switch (ranks) {
      case LoggerRanks::zero:
        if (0 == rank) {
          debug(rank, msg);
        }
        break;
      case LoggerRanks::all:
        for (const auto i : std::views::iota(0, world_size)) {
          if (rank == i) {
            debug(rank, msg);
          }
          MPI_Barrier(MPI_COMM_WORLD);
        }
        break;
      }
      break;
    }
  }
}

void Logger::emerg(const int rank, const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::dark_red), "[EMERG]");
  fmt::print(": {}\n", msg);
}

void Logger::alert(const int rank, const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::red), "[ALERT]");
  fmt::print(": {}\n", msg);
}

void Logger::crit(const int rank, const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::dark_orange), "[CRIT]");
  fmt::print(": {}\n", msg);
}

void Logger::err(const int rank, const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::orange), "[ERR]");
  fmt::print(": {}\n", msg);
}

void Logger::warning(const int rank, const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::orange), "[WARNING]");
  fmt::print(": {}\n", msg);
}

void Logger::notice(const int rank, const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::green), "[NOTICE]");
  fmt::print(": {}\n", msg);
}


void Logger::info(const int rank, const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::blue), "[INFO]");
  fmt::print(": {}\n", msg);
}

void Logger::debug(const int rank, const std::string &msg) {
  fmt::print(fmt::emphasis::bold, "Rank {}: ", rank);
  fmt::print(fg(fmt::color::purple), "[DEBUG]");
  fmt::print(": {}\n", msg);
}