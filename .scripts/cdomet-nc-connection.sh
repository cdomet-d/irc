#!/bin/bash

(
echo "PASS 0"
echo "NICK coco"
echo "USER coco 0 0 :delanight"
) | nc 0.0.0.0 80