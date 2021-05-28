#LIBMATHS

set(MATHS_LIB libMaths)

cmake_minimum_required(VERSION 3.16)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/CMakeLists_sources.cmake)

message(${libMaths_SOURCES})
add_library(${MATHS_LIB} STATIC ${libMaths_SOURCES})

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${${MATHS_LIB}_SOURCES})
		
if(MSVC)
	target_compile_options(${MATHS_LIB} PRIVATE /W4 /WX)
endif()

target_include_directories(${MATHS_LIB} PUBLIC ${LIB_DIR})

