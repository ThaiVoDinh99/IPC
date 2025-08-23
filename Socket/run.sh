#!/bin/bash
cd Server
g++ main.cpp -o main
exec ./main

cd ../Client
g++ main.cpp -o main
exec ./main