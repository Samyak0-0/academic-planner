# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Routine_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Routine_autogen.dir\\ParseCache.txt"
  "Routine_autogen"
  )
endif()
