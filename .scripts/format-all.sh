#!/bin/bash

find . -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec clang-format -style=file -i {} +