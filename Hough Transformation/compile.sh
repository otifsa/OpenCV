#!/bin/bash

g++ $1.cpp -o $1 `pkg-config --cflags --libs opencv` 
