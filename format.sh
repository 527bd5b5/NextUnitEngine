#!/bin/bash

clang-format -i $(find src/ -type f -name "*.cpp")
clang-format -i $(find src/ -type f -name "*.hpp")
