#!/bin/bash

#gcc p0.c
g++ p0.cpp

OUTPUTFILENAMEBASE="out"
i=1

for FILEPATH in ./inputs/*
do
    OUTPUTFILENAME="$OUTPUTFILENAMEBASE$i.txt"
    ./a.out < "$FILEPATH" > $OUTPUTFILENAME
    if cmp --silent -- ./outputs/output$i.txt $OUTPUTFILENAME; then
        echo "Correct"
    else
        echo "Incorrect"
    fi
    echo "Finish"
    i=$(($i+1))
    
done
