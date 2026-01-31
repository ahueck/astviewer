#!/bin/bash

format=clang-format

# Try to find a modern clang-format version
for v in 21 20 19 18 ; do
  if [[ $(type -p clang-format-"$v") ]] ; then  
    format="clang-format-"$v" -i -style=file -fallback-style=none"
    break
  fi
done

find -regextype posix-egrep -regex ".*\.(h|cpp|hpp)" \
         -path "./include/*" -o -path "./src/*"  \
         -exec $format {} \;

