﻿# CMakeList.txt : CMake project for VenomCompiler, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (VenomCompiler "Compilers.h"	"Compilers.c"
	"Reader.h"		"Reader.c"		"MainReader.c"	"MainScanner.c"		"Scanner.c"		"Scanner.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET VenomCompiler PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
