#!/bin/bash

rm src.mk
prevdir="";

find src -type f -name "*.cpp" | while read -r file; do
	dir="$(dirname "$file")"
	if [ "$prevdir" != "$dir" ]; then
		echo >> src.mk
		echo "in $dir" >> src.mk
		prevdir="$dir";
	fi
	filename="$(basename "$file")"
	echo "	$filename" >> src.mk
done