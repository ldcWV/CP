#!/bin/bash

g++ -std=c++11 $1.cpp -o solution
g++ -std=c++11 $1Dumb.cpp -o stupid
g++ -std=c++11 $1Gen.cpp -o gen

for((i = 1; ; i++)) do
    ./gen $i > input
    ./solution < input > out
    ./stupid < input > out-stupid

    if ! cmp -s out out-stupid
    then
        echo 'FAIL'
        echo 'Test case:'
        cat input
        echo 'Output:'
        cat out
        echo 'Answer:'
        cat out-stupid
        break
    fi
    echo 'OK'
done
