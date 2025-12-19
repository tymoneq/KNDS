cmake_minimum_required(VERSION 3.10)
project(antColony VERSION 0.1 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure Python3 embedding/dev headers are available
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Prefer local submodule, then installed package, then fall back to FetchContent
if(EXISTS "${CMAKE_SOURCE_DIR}/pybind11/CMakeLists.txt")
  add_subdirectory(pybind11)
else()
  # Try to find an installed pybind11 first (quietly)
  find_package(pybind11 QUIET)
  if(NOT pybind11_FOUND)
    include(FetchContent)
    FetchContent_Declare(
      pybind11
      GIT_REPOSITORY https://github.com/pybind/pybind11.git
      GIT_TAG v2.13.1
    )
    FetchContent_MakeAvailable(pybind11)
  endif()
endif()

pybind11_add_module(antColony _pybind.cpp src/antColony.cpp)
# Ensure headers in our include/ are visible to the module target
target_include_directories(antColony PRIVATE ${PROJECT_SOURCE_DIR}/include)
# If pybind11 provides a module target, link to it (safe to call whether it exists or not)
if(TARGET pybind11::module)
  target_link_libraries(antColony PRIVATE pybind11::module)
endif()