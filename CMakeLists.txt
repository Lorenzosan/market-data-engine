cmake_minimum_required(VERSION 3.16)
project(market-data-engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Boost
find_package(Boost REQUIRED COMPONENTS program_options filesystem)

# Define executable
add_executable(mde
    src/main.cpp
    src/core/CommandLineOptions.cpp
)

# Include headers
target_include_directories(mde
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

# Link Boost
target_link_libraries(mde
    PRIVATE
        Boost::program_options
	Boost::filesystem
)
