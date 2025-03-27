# CMake setup ----------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PAWS
        VERSION 0.0.1
        LANGUAGES CXX
        HOMEPAGE_URL https://github.com/samwyss/PAWS
)

# compiler settings ----------------------------------------------------------------------------------------------------
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "CMake Build Type: ${CMAKE_BUILD_TYPE}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-O0 -Wall -g3)
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O3 -g0 -DNDEBUG -Wall -fstrict-aliasing -ftree-vectorize -march=native -mtune=native -mprefer-vector-width=512 -fno-trapping-math -fno-math-errno -ffast-math -flto)
    elseif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        add_compile_options(-O3 -g3 -Wall -fstrict-aliasing -ftree-vectorize -march=native -mtune=native -mprefer-vector-width=512 -fno-trapping-math -fno-math-errno -ffast-math)
    endif ()
else ()
    message(STATUS "Build flags are not explicitly set for this compiler.")
endif ()

# dependencies ---------------------------------------------------------------------------------------------------------
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)

find_package(MPI REQUIRED COMPONENTS CXX)

find_package(OpenMP REQUIRED COMPONENTS CXX)

set(HDF5_PREFER_PARALLEL TRUE)
find_package(HDF5 REQUIRED)
if (NOT HDF5_IS_PARALLEL)
    message(FATAL_ERROR "Found HDF5 ${HDF5_VERSION} is not parallel. Consult PAWS documentation for help.")
endif ()

find_package(fmt QUIET)
if (NOT fmt_FOUND)
    message(STATUS "Library `{fmt}` not found. Installing locally now.")
    FetchContent_Declare(fmt
            GIT_REPOSITORY https://github.com/fmtlib/fmt.git
            GIT_TAG 11.1.4
            GIT_PROGRESS TRUE
            GIT_SHALLOW TRUE
            EXCLUDE_FROM_ALL
    )
    FetchContent_MakeAvailable(fmt)
else ()
    message(STATUS "Library `{fmt}` found on system.")
endif ()

# PAWS setup -----------------------------------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} src/main.cpp)

add_library(libutils
        ${PROJECT_SOURCE_DIR}/src/utils/utils.h
        ${PROJECT_SOURCE_DIR}/src/utils/logger.cpp
        ${PROJECT_SOURCE_DIR}/src/utils/logger.h
        ${PROJECT_SOURCE_DIR}/src/utils/mpi_manager.cpp
        ${PROJECT_SOURCE_DIR}/src/utils/mpi_manager.h
        ${PROJECT_SOURCE_DIR}/src/utils/EnvironmentManager.cpp
        ${PROJECT_SOURCE_DIR}/src/utils/EnvironmentManager.h
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE MPI::MPI_CXX
        PRIVATE OpenMP::OpenMP_CXX
        PRIVATE HDF5::HDF5
        PRIVATE fmt::fmt
        PRIVATE libutils
)

target_link_libraries(libutils
        PRIVATE fmt::fmt
)

target_include_directories(${PROJECT_NAME}
        PRIVATE ${MPI_CXX_INCLUDE_PATH}
        PRIVATE ${OPENMP_CXX_INCLUDE_PATH}
        PRIVATE ${HDF5_INCLUDE_DIRS}
        PRIVATE ${PROJECT_BINARY_DIR}
        PRIVATE ${PROJECT_SOURCE_DIR}/src/utils
)