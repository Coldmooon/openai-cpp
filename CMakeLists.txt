cmake_minimum_required(VERSION 3.10)
project(openai-cpp)

# requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find and include nlohmann_json
# include_directories(/path/to/nlohmann-json/include/)

add_library(http_client http_client.cpp)


# Add source files
add_executable(example example.cpp)

# Link CURL and other dependencies for the main program
find_package(CURL REQUIRED)
target_link_libraries(example PRIVATE http_client CURL::libcurl)

# Include directories
target_include_directories(example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})   
