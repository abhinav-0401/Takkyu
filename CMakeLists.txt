# CMakeList.txt : CMake project for Takkyu, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Takkyu")

# Add source to this project's executable.
add_executable (Takkyu)

target_link_directories(Takkyu PRIVATE vendor/SFML/lib)

target_link_libraries(Takkyu PRIVATE sfml-graphics sfml-window sfml-system)

target_include_directories(Takkyu PRIVATE vendor/SFML/include)

add_subdirectory(src)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Takkyu PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
