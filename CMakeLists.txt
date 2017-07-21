CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(astviewer)

include(${PROJECT_SOURCE_DIR}/cmake/ToolchainOptions.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/clang)
include_directories(${PROJECT_SOURCE_DIR}/include/clang/clang-query)

add_subdirectory(${PROJECT_SOURCE_DIR}/externalpackages)
include_directories(${PROJECT_SOURCE_DIR}/externalpackages/qspinner)

# needs headers for correct moc'ing and ui building
set(UI_SOURCES
  src/gui/mainwindow.cpp
  include/gui/mainwindow.h
  src/gui/CommandInput.cpp
  include/gui/CommandInput.h
  src/gui/RecentFileManager.cpp
  include/gui/RecentFileManager.h
    
  src/util/QLogHandler.cpp
  include/util/QLogHandler.h
  src/util/FileLoader.cpp
  include/util/FileLoader.h
  src/util/StatusHandler.cpp
  include/util/StatusHandler.h
  include/util/Util.h
  
  src/core/CoreManager.cpp
  include/core/CoreManager.h
  src/core/TaskManager.cpp
  include/core/TaskManager.h
  src/core/Task.cpp
  include/core/Task.h
  
  src/core/ToolWrapper.cpp
  include/core/ToolWrapper.h
  
  ${QSpinner_SOURCES}
)

set(CLANG_UI_SOURCES
  src/clang/ClangToolSession.cpp
  include/clang/ClangToolSession.h
  src/clang/QueryWrapper.cpp
  include/clang/QueryWrapper.h
  
  include/QueryApp.h
  src/QueryApp.cpp
)

set(CLANG_QUERY_SOURCES
  src/clang/clang-query/Query.cpp
  src/clang/clang-query/QueryParser.cpp
)

add_format_target(format-all
  "Formats astviewer source files"
  EXCLUDES "external"
)

add_tidy_target(tidy-run
  "Clang-tidy run on astviewer translation units"
  SOURCES ${CLANG_UI_SOURCES} ${UI_SOURCES}
  EXCLUDES "externalpackages"
)

add_tidy_fix_target(tidy-core-fix
  "Clang-tidy run with fixes on astviewer translation units"
  SOURCES ${CLANG_UI_SOURCES} ${UI_SOURCES}
  EXCLUDES "externalpackages"
  OTHER -checks=-*,modernize-*,llvm-header-guard,llvm-namespace-comment,google-explicit-constructor
)

add_library(query ${CLANG_UI_SOURCES} ${CLANG_QUERY_SOURCES})
add_library(astui ${UI_SOURCES})
target_link_libraries(astui Qt5::Widgets Qt5::Concurrent)
target_link_libraries(query Qt5::Widgets Qt5::Concurrent)


add_executable(astviewer${EXE_SUFFIX} src/main.cpp)

target_link_libraries(astviewer${EXE_SUFFIX} query ${CLANG_LIBS} ${libedit_LIBRARIES} -lLLVMLineEditor -lLLVMSupport  -lLLVMLineEditor  -lLLVMMCParser  -lLLVMBitReader -lLLVMProfileData  -lLLVMOption -lLLVMCore -lLLVMMC -lLLVMSupport -lLLVMDemangle ${LLVM_SYSTEM_LIBS})

target_link_libraries(astviewer${EXE_SUFFIX} astui)

add_custom_target(executable
  COMMENT "Target to compile astviewer executable"
  DEPENDS astviewer${EXE_SUFFIX}
)