# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Laba5_2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Laba5_2_autogen.dir\\ParseCache.txt"
  "Laba5_2_autogen"
  )
endif()
