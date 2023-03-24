#!/bin/sh

CHECK_FOLDERS='build, bin'

for folder in $(echo "$CHECK_FOLDERS" | sed "s/,/ /g"); do
  if [ ! -d "$folder" ]; then
    echo "Creating $folder..."
    mkdir "$folder"
  fi
done

cmake -S . -B build -GNinja
cmake --build build
ctest --test-dir build
