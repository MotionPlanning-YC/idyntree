# Copyright: (C) 2015 Fondazione Istituto Italiano di Tecnologia
# Authors: Silvio Traversaro
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

project(iDynTree_ModelIO_iKin CXX)

find_package(YARP REQUIRED)
find_package(ICUB REQUIRED)

set(IDYNTREE_MODELIO_IKIN_HEADERS include/iDynTree/ModelIO/iKin_export.hpp)

set(IDYNTREE_MODELIO_IKIN_SOURCES src/iKin_export.cpp)

SOURCE_GROUP("Source Files" FILES ${IDYNTREE_MODELIO_IKIN_SOURCES})
SOURCE_GROUP("Header Files" FILES ${IDYNTREE_MODELIO_IKIN_HEADERS})

get_property(IDYNTREE_TREE_INCLUDE_DIRS GLOBAL PROPERTY IDYNTREE_TREE_INCLUDE_DIRS)

set(libraryname idyntree-modelio-ikin)

add_library(${libraryname} ${IDYNTREE_MODELIO_IKIN_SOURCES} ${IDYNTREE_MODELIO_IKIN_HEADERS})

target_include_directories(${libraryname} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include;${IDYNTREE_TREE_INCLUDE_DIRS}>"
                                                 "$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}>")
                                          
if(NOT CMAKE_VERSION VERSION_LESS 2.8.12)
    target_include_directories(${libraryname} SYSTEM PUBLIC ${orocos_kdl_INCLUDE_DIRS} ${iKin_INCLUDE_DIRS} ${YARP_INCLUDE_DIRS})
    target_include_directories(${libraryname} SYSTEM PRIVATE ${EIGEN3_INCLUDE_DIR})
else()
    target_include_directories(${libraryname} PUBLIC ${orocos_kdl_INCLUDE_DIRS} ${iKin_INCLUDE_DIRS} ${YARP_INCLUDE_DIRS})
    target_include_directories(${libraryname} PRIVATE ${EIGEN3_INCLUDE_DIR})
endif()

target_link_libraries(${libraryname} idyntree-core iKin ${orocos_kdl_LIBRARIES})

if(NOT CMAKE_VERSION VERSION_LESS 2.8.12)
    target_compile_options(${libraryname} PRIVATE ${IDYNTREE_WARNING_FLAGS})
endif()

set_property(TARGET ${libraryname} PROPERTY PUBLIC_HEADER ${IDYNTREE_MODELIO_IKIN_HEADERS})

install(TARGETS ${libraryname}
        EXPORT iDynTree
        COMPONENT runtime
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT bin
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT shlib
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT lib
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/iDynTree/ModelIO)

set_property(GLOBAL APPEND PROPERTY ${VARS_PREFIX}_TARGETS ${libraryname})
set_property(GLOBAL APPEND PROPERTY IDYNTREE_TREE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

