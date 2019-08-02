#!/bin/bash

dir="."
cd $dir
for file in $(ls $dir | grep .proto)
    do
        echo $file
        protoc --cpp_out=$dir $file
    done

echo "done"

