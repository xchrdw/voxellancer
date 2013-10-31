# - Locate FMOD library (By Matt Raykowski, OpenNeL Project http://www.opennel.org/)
# http://www.opennel.org/fisheye/browse/~raw,r=1353/NeL/trunk/nel/CMakeModules/FindFMOD.cmake
# (with permission to relicense as LGPL-with-staticlink-exemption by Matt Raykowski)
# This module defines
# FMOD_LIBRARY, the library to link against
# FMOD_FOUND, if false, do not try to link to FMOD
# FMOD_INCLUDE_DIR, where to find headers.

IF(FMOD_LIBRARY AND FMOD_INCLUDE_DIR)
    # in cache already
    SET(FMOD_FIND_QUIETLY TRUE)
ENDIF(FMOD_LIBRARY AND FMOD_INCLUDE_DIR)

FIND_PATH(FMOD_INCLUDE_DIR
    fmod.h
    PATHS
    ${LIB_DIR}/fmod/api/inc
    $ENV{FMOD_DIR}/inc
    $ENV{FMOD_DIR}/include
    /usr/local/include
    /usr/include
    /sw/include
    /opt/local/include
    /opt/csw/include
    /opt/include
    PATH_SUFFIXES fmod fmod3
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(FMOD_LIBRARY_NAMES fmod fmodex64_vc fmodex64)
else()
	set(FMOD_LIBRARY_NAMES fmod fmodex libfmod)
endif()

FIND_LIBRARY(FMOD_LIBRARY
    NAMES ${FMOD_LIBRARY_NAMES}
    PATHS
    ${LIB_DIR}/fmod/api/lib
    $ENV{FMOD_DIR}/lib
    /usr/local/lib
    /usr/lib
    /usr/local/X11R6/lib
    /usr/X11R6/lib
    /sw/lib
    /opt/local/lib
    /opt/csw/lib
    /opt/lib
    /usr/freeware/lib64
)



if(WIN32)
    find_file(FMOD_BINARY
        NAMES fmodex64.dll
        PATHS
        ${LIB_DIR}/fmod/api/
        $ENV{FMOD_DIR}
        DOC "The FMOD binary")
endif()

IF(FMOD_LIBRARY AND FMOD_INCLUDE_DIR)
    SET(FMOD_FOUND "YES")
    SET( FMOD_LIBRARIES ${FMOD_LIBRARY} )
    IF(NOT FMOD_FIND_QUIETLY)
        MESSAGE(STATUS "Found FMOD: ${FMOD_LIBRARY}")
    ENDIF(NOT FMOD_FIND_QUIETLY)
ELSE(FMOD_LIBRARY AND FMOD_INCLUDE_DIR)
    IF(NOT FMOD_FIND_QUIETLY)
        MESSAGE(STATUS "Warning: Unable to find FMOD!")
    ENDIF(NOT FMOD_FIND_QUIETLY)
ENDIF(FMOD_LIBRARY AND FMOD_INCLUDE_DIR)