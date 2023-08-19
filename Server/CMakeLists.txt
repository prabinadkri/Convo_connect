cmake_minimum_required(VERSION 3.0)
project(server)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Find Boost package
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Set the path to the bcrypt library (relative to your project root)
set(BCRYPT_LIB_PATH ${CMAKE_SOURCE_DIR}/bcrypt)

# Add include directory for bcrypt
include_directories(${BCRYPT_LIB_PATH}/include)

# Include SQLite3 headers
include_directories("/Sqlite")

# Add your source files here
set(SOURCES
    server.cpp
    # Sqlite/shell.c 
    Sqlite/sqlite3.c
    # Add your other source files here
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Boost, SQLite3, and other libraries
target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES}
    # "/path/to/sqlite3/libsqlite3.a"
)
