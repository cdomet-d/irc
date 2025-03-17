#!/bin/bash

(
echo "NICK coco"
echo "USER cdomet"
echo "JOIN #test"
) | nc 0.0.0.0 80