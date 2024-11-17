# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Formal_Brmal_Bejeweled_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Formal_Brmal_Bejeweled_autogen.dir\\ParseCache.txt"
  "Formal_Brmal_Bejeweled_autogen"
  )
endif()
