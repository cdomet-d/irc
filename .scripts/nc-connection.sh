#!/bin/bash

(
echo "NICK alex"
echo "USER alexie"
echo "JOIN #test"
) | nc 0.0.0.0 4444