CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(astviewer)

include(${PROJECT_SOURCE_DIR}/cmake/ToolchainOptions.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/clang-query)

set(QSOURCES
  src/clang-query/Query.cpp
  src/clang-query/QueryParser.cpp
)

# needs headers for correct moc'ing and ui building
set(UISOURCES
  src/gui/mainwindow.cpp
  include/gui/mainwindow.h
  src/gui/CommandInput.cpp
  include/gui/CommandInput.h
  
  src/util/QLogHandler.cpp
  include/util/QLogHandler.h

  include/util/Util.h
  
  src/core/ClangToolSession.cpp
  include/core/ClangToolSession.h
  src/core/QueryWrapper.cpp
  include/core/QueryWrapper.h
)

add_format_target(format-all
  "Formats astviewer source files"
  EXCLUDES "external"
)

add_tidy_target(tidy-run
  "Clang-tidy run on astviewer translation units"
  SOURCES ${PSOURCES} ${LSOURCES}
  EXCLUDES "external"
)

add_tidy_fix_target(tidy-core-fix
  "Clang-tidy run with fixes on astviewer translation units"
  SOURCES ${QSOURCES}
  EXCLUDES "external"
  OTHER -checks=-*,modernize-*,llvm-header-guard,llvm-namespace-comment,google-explicit-constructor
)

add_library(query ${QSOURCES})
add_library(astui ${UISOURCES})
target_link_libraries(astui Qt5::Widgets Qt5::Concurrent ${CLANG_LIBS})


add_executable(astviewer${EXE_SUFFIX} src/main.cpp)

target_link_libraries(astviewer${EXE_SUFFIX} query ${CLANG_LIBS} ${libedit_LIBRARIES} -lLLVMLineEditor -lLLVMSupport  -lLLVMLineEditor  -lLLVMMCParser  -lLLVMBitReader -lLLVMProfileData  -lLLVMOption -lLLVMCore -lLLVMMC -lLLVMSupport -lLLVMDemangle ${LLVM_SYSTEM_LIBS})

target_link_libraries(astviewer${EXE_SUFFIX} astui)

add_custom_target(executable
  COMMENT "Target to compile astviewer executable"
  DEPENDS astviewer${EXE_SUFFIX}
)









#enable_testing()
#add_subdirectory(test)

## Original link ordering:
#target_link_libraries(astviewer${EXE_SUFFIX} -ledit -lLLVMLineEditor -lLLVMSupport -ledit -lpthread -lclangAST -lclangASTMatchers -lclangBasic -lclangDynamicASTMatchers -lclangFrontend -lclangQuery -lclangTooling -lLLVMLineEditor -ledit -lclangDynamicASTMatchers -lclangASTMatchers -lclangFrontend -lclangParse -lLLVMMCParser -lclangSerialization -lclangSema -lclangEdit -lclangAnalysis -lLLVMBitReader -lLLVMProfileData -lclangDriver -lLLVMOption -lclangFormat -lclangToolingCore -lclangAST -lclangRewrite -lclangLex -lclangBasic -lLLVMCore -lLLVMMC -lLLVMSupport -lrt -ldl -ltinfo -lpthread -lz -lm -lLLVMDemangle)