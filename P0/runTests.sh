#!/bin/bash

gcc p0.c

for FILEPATH in ./inputs/*
do
    ./a.out < "$FILEPATH"
done
