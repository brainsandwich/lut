cmake_minimum_required(VERSION 3.0)
project(lut VERSION 0.1.0 LANGUAGES CXX)

set(LUT_EXTERNALS_DIR ${PROJECT_SOURCE_DIR}/external)

# LUT SOURCES
file(GLOB_RECURSE LUT_SOURCES "${PROJECT_SOURCE_DIR}/src/**.cpp")
file(GLOB_RECURSE LUT_INCLUDES "${PROJECT_SOURCE_DIR}/include/**.hpp")
set(LUT_INCLUDEDIR ${PROJECT_SOURCE_DIR}/include)

# FETCH DEPENDENCIES
message(STATUS "cmd: python deps_fetcher.py")
execute_process(COMMAND "python" "./deps_fetcher.py"
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	RESULT_VARIABLE fetch_result
)
message(STATUS "command returned ${fetch_result}")

# LUT LIB
add_library(lut ${LUT_SOURCES} ${LUT_INCLUDES})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(lut PROPERTIES FOLDER LUT/CORE)
target_include_directories(lut PUBLIC ${LUT_INCLUDEDIR})

# FORMAT
add_subdirectory(${LUT_EXTERNALS_DIR}/fmt)
target_link_libraries(lut fmt)