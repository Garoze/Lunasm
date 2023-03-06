#!/bin/sh

ninja -C build -j4 && bin/Lunasm "$@"
