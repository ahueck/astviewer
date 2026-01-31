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
  GIT_TAG "devel" 
  CMAKE_ARGS "-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE};-DCMAKE_INSTALL_PREFIX:PATH=${ASTPRINTER_INSTALL_DIR}"
  INSTALL_DIR ${ASTPRINTER_INSTALL_DIR}
)

ExternalProject_Get_property(astprinter INSTALL_DIR)
file(MAKE_DIRECTORY "${INSTALL_DIR}/include")
set(astprinter_INCLUDE_DIRS "${INSTALL_DIR}/include" PARENT_SCOPE)

add_library(libastprint STATIC IMPORTED GLOBAL)
set_target_properties(libastprint PROPERTIES
  IMPORTED_LOCATION "${INSTALL_DIR}/lib/libclang-ast-print${CMAKE_STATIC_LIBRARY_SUFFIX}"
  INTERFACE_INCLUDE_DIRECTORIES "${INSTALL_DIR}/include"
)
add_dependencies(libastprint astprinter)

set(astprinter_LIBRARIES libastprint PARENT_SCOPE)
