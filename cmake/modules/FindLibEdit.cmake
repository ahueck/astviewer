include(FindPackageHandleStandardArgs)

find_path(LibEdit_INCLUDE_DIRS
  editline/readline.h
  PATHS ${LIBEDIT_INCLUDE_DIR} /usr/include /usr/local/include
)

find_library(LibEdit_LIBRARIES
  NAMES edit
  PATHS ${LIBEDIT_LIBRARY_DIR} /usr/lib /usr/local/lib /usr/lib64 /usr/local/lib64
) 

find_package_handle_standard_args(LibEdit 
  FOUND_VAR LibEdit_FOUND
  REQUIRED_VARS
  	LibEdit_LIBRARIES
  	LibEdit_INCLUDE_DIRS 
)

if(LibEdit_FOUND AND NOT TARGET LibEdit::LibEdit)
  add_library(LibEdit::LibEdit UNKNOWN IMPORTED)
  set_target_properties(LibEdit::LibEdit PROPERTIES
    IMPORTED_LOCATION "${LibEdit_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES "${LibEdit_INCLUDE_DIRS}")
endif()