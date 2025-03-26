#include "logger.hpp"

Logger::Logger(const LoggerLevel level,
               const LoggerRanks ranks) : level_(level), ranks_(ranks) {

}

Logger::~Logger() = default;

void Logger::log(const LoggerLevel level, const LoggerRanks ranks,
                 const int rank, const std::string &msg) {

}

void Logger::emerg(const int rank, const std::string &msg) {

}

void Logger::alert(const int rank, const std::string &msg) {

}

void Logger::crit(const int rank, const std::string &msg) {

}

void Logger::err(const int rank, const std::string &msg) {

}

void Logger::warning(const int rank, const std::string &msg) {

}

void Logger::info(const int rank, const std::string &msg) {

}

void Logger::debug(const int rank, const std::string &msg) {

}





