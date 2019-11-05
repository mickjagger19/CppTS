#!/usr/bin/env bash
src=$1
output=$2

for filename in $(ls $src)
do
    echo "processing:" $filename
    ./wmc -c $src/$filename $output/$filename
    echo "--------------------------------"
done
