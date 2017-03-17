#!/bin/bash

function find_tidy() {
  # Try for most current clang-tidy
  # out: $ctidy
  for v in 4.0 3.8 3.7 3.6 ; do
    if [[ $(type -p clang-tidy-"$v") ]] ; then  
      ctidy=clang-tidy-"$v"
      break
    fi
  done
  if [[ $(type -p clang-tidy) ]] ; then
    local v1=$("$ctidy" --version | grep -o -E '[0-9]\.[0-9]\.[0-9]')
    local v2=$(clang-tidy --version | grep -o -E '[0-9]\.[0-9]\.[0-9]')
    if [[ "$v2" > "$v1" ]] ; then 
      ctidy=clang-tidy
    fi
  fi
}

headerfilter="/astviewer/include/"
build_folder="build/"
find_tidy # sets "$ctidy"

find \( -path "./src/*" \) -name '*.cpp' \
  -exec "$ctidy" -p "$build_folder" --header-filter="$headerfilter" \
        -checks=misc-*,modernize-*,cppcoreguidelines-*,readability-*,performance-*,llvm-header-guard,llvm-namespace-comment,google-build-using-namespace,google-explicit-constructor,google-readability-* \
        {} \;
