SET( PROJ_NAME      "cpp-ddp-client" )
########################## Project configuration ##############################
SET( PROJ_PATH      ${CMAKE_SOURCE_DIR} )
SET( PROJ_OUT_PATH  ${CMAKE_BINARY_DIR} )
SET( PROJ_SOURCES   "" )
SET( PROJ_HEADERS   "" )
SET( PROJ_LIBRARIES "" )
SET( PROJ_INCLUDES  "" )

####################### Minimum CMake version to run ##########################
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

############################## Project name ###################################
PROJECT( cpp-ddp-client )

MESSAGE( "--------------------------------------------------" )
MESSAGE( STATUS "Configuring cpp-ddp-client" )

########################## Modules configuration ##############################
OPTION( BUILD_TESTS                 "Build the unit tests"                                              OFF )
MESSAGE( STATUS "Building tests:                                                    " ${BUILD_TESTS}                 )

############################ External libraries ###############################
# Add current source directory as module path for Find*.cmake
SET( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJ_PATH} )

# Template for adding a library
#FIND_PACKAGE( <LibraryName> REQUIRED )
#SET( PROJ_INCLUDES  ${PROJ_INCLUDES}  ${<LibraryName>_INCLUDE_DIR} )
#SET( PROJ_LIBRARIES ${PROJ_LIBRARIES} ${<LibraryName>_LIBRARIES}   )

################################ Includes #####################################
INCLUDE_DIRECTORIES( ${PROJ_INCLUDES} ) # Include path


############################## Sources ########################################
FILE( GLOB_RECURSE PROJ_HEADERS src/*.h)
FILE( GLOB_RECURSE PROJ_SOURCES src/*.cpp )

SET( PROJ_INCLUDES ${PROJ_INCLUDES} 3rdparty/websocketpp 3rdparty/rapidjson)
INCLUDE_DIRECTORIES( ${PROJ_INCLUDES} ) # Include path

IF(STATIC)
	ADD_LIBRARY( cppdppclient STATIC ${PROJ_SOURCES} ${PROJ_HEADERS})
ELSE ( ON )
	ADD_LIBRARY( cppdppclient SHARED ${PROJ_SOURCES} ${PROJ_HEADERS})
ENDIF(STATIC)

TARGET_LINK_LIBRARIES( cppdppclient ${PROJ_LIBRARIES})


############################# Target Properties ###############################
SET_TARGET_PROPERTIES( cppdppclient PROPERTIES LINKER_LANGUAGE CXX ) # Language forced to C++

SET_TARGET_PROPERTIES( cppdppclient PROPERTIES DEBUG_POSTFIX   "d" ) # Debug mode: a trailing "d"
SET_TARGET_PROPERTIES( cppdppclient PROPERTIES RELEASE_POSTFIX ""  ) # Release mode: no postfix

SET_TARGET_PROPERTIES( cppdppclient PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJ_OUT_PATH} ) # Path for shared libraries
SET_TARGET_PROPERTIES( cppdppclient PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJ_OUT_PATH} ) # Path for module libraries
SET_TARGET_PROPERTIES( cppdppclient PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJ_OUT_PATH} ) # Path for import libraries

SET_TARGET_PROPERTIES( cppdppclient PROPERTIES OUTPUT_NAME "cppdppclient" ) # Output name