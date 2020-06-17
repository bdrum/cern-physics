cmake_minimum_required( VERSION 3.10.0 )

project( physics CXX )

include(CheckCXXCompilerFlag)

OPTION (BUILD_SHARED_LIBS "Build shared libraries." ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CFLAGS " -pthread -g -ansi -pedantic -Wall -Wextra -Wno-sign-compare -Wsign-promo -Wabi -std=c++17 -Wno-pragma-once-outside-header")
set(CMAKE_CXX_FLAGS ${CFLAGS})

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})
link_directories(${ROOT_LIBRARIES})

set( ALIROOT /home/bdrum/apps/alice/sw/ubuntu1804_x86-64/AliRoot/v5-09-53-1 )

find_program(ALIROOT_EXE NAMES aliroot PATHS ${ALIROOT}/bin NO_DEFAULT_PATH)
  
    mark_as_advanced(ALIROOT_EXE)
  
    include_directories(
      ${ALIROOT}/include
      ${ALIROOT}/include/pythia
    )

    link_directories(${ALIROOT}/lib)
    
    include(${ALIROOT}/etc/AliRoot-config.cmake)
    message(STATUS "Found AliRoot version : \"${AliRoot_VERSION}\", git hash : \"${AliRoot_REVISION}\"")

include_directories( /home/bdrum/apps/alice/sw/ubuntu1804_x86-64/ROOT/latest/include)
link_directories(/home/bdrum/apps/alice/sw/ubuntu1804_x86-64/ROOT/latest/lib)

add_subdirectory(RhoPrime)
add_subdirectory(vis)

