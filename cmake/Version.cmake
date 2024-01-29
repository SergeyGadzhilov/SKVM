cmake_minimum_required (VERSION 3.4)

set(SKVM_VERSION_MAJOR 0)
set(SKVM_VERSION_MINOR 1)
set(SKVM_VERSION_PATCH 0)

if(NOT DEFINED SKVM_REVISION)
    if(DEFINED ENV{GIT_COMMIT})
        string(SUBSTRING $ENV{GIT_COMMIT} 0 8 SKVM_REVISION)
    else()
        find_program (GIT_BINARY git)
        if (NOT GIT_BINARY STREQUAL "GIT_BINARY-NOTFOUND")
            execute_process (
                COMMAND git rev-parse --short=8 HEAD
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE SKVM_REVISION
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )
        endif()
    endif()
endif()

string(LENGTH "${SKVM_REVISION}" SKVM_REVISION_LENGTH)
if (NOT SKVM_REVISION_LENGTH EQUAL 8 OR NOT SKVM_REVISION MATCHES "^[a-f0-9]+")
    set(SKVM_REVISION "00000000")
    message(WARNING "revision not found. setting to ${SKVM_REVISION}")
endif()
unset(SKVM_REVISION_LENGTH)

set(SKVM_VERSION "${SKVM_VERSION_MAJOR}.${SKVM_VERSION_MINOR}.${SKVM_VERSION_PATCH}")
message(STATUS "Full version string is '" ${SKVM_VERSION} "'")

add_definitions(-DSKVM_VERSION="${SKVM_VERSION}")
add_definitions(-DSKVM_VERSION_MAJOR=${SKVM_VERSION_MAJOR})
add_definitions(-DSKVM_VERSION_MINOR=${SKVM_VERSION_MINOR})
add_definitions(-DSKVM_VERSION_PATCH=${SKVM_VERSION_PATCH})
add_definitions(-DSKVM_REVISION="${SKVM_REVISION}")
