#!/bin/bash

set eu

if [ -s src.mk  ]; then
	rm src.mk
fi

prevdir="";

echo -n "Enter a directory to list: "

read -r dir;

find "$dir" -type f -name "*.cpp" | while read -r file; do
	dir="$(dirname "$file")"
	if [ "$prevdir" != "$dir" ]; then
		echo >> src.mk
		echo "$dir" >> src.mk
		prevdir="$dir";
	fi
	filename="$(basename "$file")"
	echo "		$filename \\" >> src.mk
done