#ifndef UTILS_UTILS_HPP
#define UTILS_UTILS_HPP

#include <fmt/core.h>
#include <fmt/color.h>
#include <mpi.h>
#include <string>

/*!
 * formats and prints error messages
 * @param msg error message
 */
inline void error_msg(const std::string& msg)
{
    fmt::print(fg(fmt::color::crimson), "[ERROR]");
    fmt::print(": {}\n", msg);
};

/*!
 * formats and prints warning messages
 * @param msg warning message
 */
inline void warning_msg(const std::string& msg)
{
    fmt::print(fg(fmt::color::orange), "[WARNING]");
    fmt::print(": {}\n", msg);
};

/*!
 * formats and prints info messages
 * @param msg info message
 */
inline void info_msg(const std::string& msg)
{
    fmt::print(fg(fmt::color::green), "[INFO]");
    fmt::print(": {}\n", msg);
};

/*!
 * formats and prints logging messages
 * @param msg logging message
 */
inline void log_msg(const std::string& msg)
{
    fmt::print(fg(fmt::color::blue), "[LOG]");
    fmt::print(": {}\n", msg);
};

/*!
 * terminates mpi environment and ends program displaying error message
 * @param rank MPI rank on which error occurred
 * @param msg error message
 */
inline void abort_err(const int rank, const std::string& msg)
{
    // log out error message
    error_msg("Aborted on rank: " + fmt::to_string(rank) + ". Reason: " + msg);

    // terminate mpi environment
    MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
};

#endif //UTILS_UTILS_HPP
