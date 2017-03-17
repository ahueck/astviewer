#!/bin/bash

format=clang-format

# clang-format-3.6 does not support all file entries 
# TODO check compatibility with clang-format-3.7 
for v in 3.8 3.7 ; do
  if [[ $(type -p clang-format-"$v") ]] ; then  
    format="clang-format-"$v" -i -style=file -fallback-style=none"
    break
  fi
done

find -regextype posix-egrep -regex ".*\.(h|cpp|hpp)" \
         -path "./include/*" -o -path "./src/*"  \
         -exec $format {} \;

