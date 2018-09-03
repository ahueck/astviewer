include(ExternalProject)
set(EXTERNALPACKAGES ${PROJECT_SOURCE_DIR}/externalpackages)

#############
# qt spinner widget
#############
set(qspinner_HEADERS
	${EXTERNALPACKAGES}/qspinner/waitingspinnerwidget.h 
	PARENT_SCOPE
)
set(qspinner_SOURCES
	${EXTERNALPACKAGES}/qspinner/waitingspinnerwidget.cpp
	PARENT_SCOPE
)

set(qspinner_INCLUDE_DIRS "${EXTERNALPACKAGES}/qspinner" PARENT_SCOPE)

#############
# c++ ast printer
#############
set(ASTPRINTER_INSTALL_DIR ${CMAKE_BINARY_DIR}/externalpackages/astprinter) 
ExternalProject_Add(
  astprinter
  GIT_REPOSITORY "https://github.com/ahueck/astprinter.git"
  GIT_TAG "master" 
  CMAKE_ARGS "-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE};-DCMAKE_INSTALL_PREFIX:PATH=${ASTPRINTER_INSTALL_DIR}"
  INSTALL_DIR ${ASTPRINTER_INSTALL_DIR}
)

ExternalProject_Get_property(astprinter INSTALL_DIR)
set(astprinter_INCLUDE_DIRS "${INSTALL_DIR}/include" PARENT_SCOPE)

#add_library(astprint STATIC IMPORTED)
#set_property(TARGET astprint PROPERTY IMPORTED_LOCATION "${INSTALL_DIR}/lib/libastprint${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(astprinter_LIBRARIES "${INSTALL_DIR}/lib/libastprint${CMAKE_STATIC_LIBRARY_SUFFIX}" PARENT_SCOPE)
#add_dependencies(astprint astprinter)

#add_library(libastprinter STATIC IMPORTED GLOBAL)
#set_target_properties(libastprinter PROPERTIES IMPORTED_LOCATION "${INSTALL_DIR}/libastprint.a")
#set_target_properties(libastprinter PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${INSTALL_DIR}/include")
