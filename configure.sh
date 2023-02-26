#!/usr/bin/env bash

CHECK_FOLDERS='build, bin'

for folder in $(echo $CHECK_FOLDERS | sed "s/,/ /g"); do
  if [[ ! -d $folder ]]; then
    echo -e "Creating $folder..."; mkdir $folder
  fi
done

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S . -B build -GNinja
