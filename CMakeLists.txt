cmake_minimum_required(VERSION 3.10)
project(openai-cpp)

# requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(OPENAI_BUILD_EXAMPLES "Build example programs" ON)

# Find dependencies
find_package(CURL REQUIRED)
# find_package(nlohmann_json REQUIRED)
# include_directories(/path/to/nlohmann-json/include/)

# Create header-only library target
add_library(openai-cpp INTERFACE)

target_include_directories(openai-cpp
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(openai-cpp
    INTERFACE
        CURL::libcurl
        # nlohmann_json::nlohmann_json
)

# Examples
if(OPENAI_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Installation rules
install(FILES openai.hpp
    DESTINATION include
)

install(DIRECTORY include/
    DESTINATION include
)

