# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Jewels_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Jewels_autogen.dir\\ParseCache.txt"
  "Jewels_autogen"
  )
endif()
