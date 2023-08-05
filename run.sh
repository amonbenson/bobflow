#!/bin/bash

gcc -Wall -Wextra -Werror -std=c17 -Iinclude -o build/bobflow src/bobflow/*.c src/*.c && \
    ./build/bobflow
