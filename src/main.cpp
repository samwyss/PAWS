#include <mpi.h>
#include <chrono>
#include <fmt/chrono.h>

#include "utils.hpp"

/*!
* main driver function and build target
* @param argc argument count
* @param argv argument vector
* @return
*/
int main(int argc, char** argv)
{
	// PAWS start time
	const auto start_time = std::chrono::high_resolution_clock::now();

	// initialize mpi environment
	MPI_Init(&argc, &argv);

	// get size of MPI_COMM_WORLD communicator
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// get rank of process inside MPI_COMM_WORLD communicator
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	// start_time formatted as string for output file name
	std::string start_time_str;

	// size of start_time_str
	int start_time_str_size;

	// broadcast the start time to all ranks for use in naming the output file
	if (0 == world_rank)
	{
		// format start time as string
		start_time_str = fmt::format("{:%Y-%m-%d_%H:%M:%S}", start_time);

		// size of start time string for broadcasting
		start_time_str_size = static_cast<int>(start_time_str.size());

		// broadcast start time string length to all ranks
		MPI_Bcast(&start_time_str_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

		// broadcast config string to all ranks
		MPI_Bcast(start_time_str.data(), start_time_str_size, MPI_CHAR, 0, MPI_COMM_WORLD);
	}
	else
	{
		// participate in broadcast of start time size
		MPI_Bcast(&start_time_str_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

		// resize start time string
		start_time_str.resize(start_time_str_size);

		// participate in broadcast of start time string
		MPI_Bcast(start_time_str.data(), start_time_str_size, MPI_CHAR, 0, MPI_COMM_WORLD);
	}

	// initial diagnostics
	if (0 == world_rank)
	{
		info_msg("PAWS started at: " + fmt::format("{:%Y-%m-%d %H:%M:%S}", start_time) + ".");
		info_msg("MPI environment initialized with " + fmt::to_string(world_size) + " rank(s).");
	}

	// fetch simulation end time
	const auto end_time = std::chrono::high_resolution_clock::now();

	// final diagnostic messages
	if (world_rank == 0)
	{
		const auto total_time = end_time - start_time;
		info_msg("PAWS successfully completed at " + fmt::format("{:%Y-%m-%d %H:%M:%S}.", end_time));
		info_msg("Total Time: " + fmt::format("{:%H:%M:%S}.", total_time));
		info_msg("Destructing MPI environment and exiting.");
	}

	// finalize mpi environment
	MPI_Finalize();

	// return success
	return EXIT_SUCCESS;
}
