include_directories(inc)
set(rhoPrime inc/RhoPrime.h src/RhoPrime.cxx)

add_library(RhoPrime SHARED ${rhoPrime})
