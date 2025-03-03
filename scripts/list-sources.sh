#!/bin/bash

ls src/ | tr " " "\n" | sed 's/^/\t\t/; s/$/ \\/' >> src.mk
