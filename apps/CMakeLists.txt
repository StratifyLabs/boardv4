cmake_minimum_required (VERSION 3.19)

project(Boardv4-Apps)

set(BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "Base directory ${BASE_DIRECTORY}")

option(APPS_IS_TESTSUITE "Clone and build the Test suite" ON)
option(APPS_IS_DEMO "Clone and build the Demo applications" ON)

macro(sdk_add_subdirectory NAME BRANCH)
	sos_sdk_git_clone_or_pull_branch(${BASE_DIRECTORY} ${NAME} https://github.com/StratifyLabs/${NAME}.git ${BRANCH})
	add_subdirectory(${BASE_DIRECTORY}/${NAME} ${NAME})
endmacro()

if(APPS_IS_DEMO)
	sdk_add_subdirectory(HelloWorld main)
	sdk_add_subdirectory(Blinky main)
endif()
sdk_add_subdirectory(SystemApps main)
if(APPS_IS_TESTSUITE)
	sdk_add_subdirectory(testsuite main)
endif()

