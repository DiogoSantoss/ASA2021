#!/bin/bash

#gcc p0.c
g++ p0.cpp

for FILEPATH in ./inputs/*
do
    ./a.out < "$FILEPATH"
    echo "Finish"
done
