# CMakeList.txt : CMake project for PongClone, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("PongClone")

# Add source to this project's executable.
add_executable (PongClone)

target_link_directories(PongClone PRIVATE vendor/SFML/lib)

target_link_libraries(PongClone PRIVATE sfml-graphics sfml-window sfml-system)

target_include_directories(PongClone PRIVATE vendor/SFML/include)

add_subdirectory(src)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PongClone PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
