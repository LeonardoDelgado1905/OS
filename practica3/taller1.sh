#!/bin/bash

cd Pipes/Non_Parented

gcc writer.c -o writer
gcc reader.c -o reader
echo "Si compile xd"
./reader 1000 1 & ./writer 1000 1
./reader 10000 1 & ./writer 10000 1
./reader 100000 1 & ./writer 100000 1