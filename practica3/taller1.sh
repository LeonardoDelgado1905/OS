#!/bin/bash


gcc Pipes/Parented/server.c -o Pipes/Parented/server
gcc Pipes/Non_Parented/writer.c -o Pipes/Non_Parented/writer
gcc Pipes/Non_Parented/reader.c -o Pipes/Non_Parented/reader
gcc Message_passing/server.c -o Message_passing/server
gcc Message_passing/client.c -o Message_passing/client
gcc Share_memory/shmem.c -o Share_memory/schmem.o
gcc File_communication/file_communication.c -o File_communication/file.o

echo -----------1KB test
./Pipes/Parented/server 1000 5
./Pipes/Non_Parented/reader 1000 5 & ./Pipes/Non_Parented/writer 1000 5
./Message_passing/server & ./Message_passing/client 127.0.0.1 1000 5
./Share_memory/schmem.o 1000 100
./File_communication/file.o 1000 100
echo -----------10KB test
./Pipes/Parented/server 10000 5
./Pipes/Non_Parented/reader 10000 5 & ./Pipes/Non_Parented/writer 10000 5
./Message_passing/server & ./Message_passing/client 127.0.0.1 10000 5
./Share_memory/schmem.o 10000 10
./File_communication/file.o 10000 10
echo -----------100KB test
./Pipes/Parented/server 100000 5
./Pipes/Non_Parented/reader 100000 5 & ./Pipes/Non_Parented/writer 100000 5
./Message_passing/server & ./Message_passing/client 127.0.0.1 100000 1
./Share_memory/schmem.o 100000 1
./File_communication/file.o 100000 10
echo -----------1MB test
./Pipes/Parented/server 1000000 5
./Pipes/Non_Parented/reader 1000000 5 & ./Pipes/Non_Parented/writer 1000000 5
./Message_passing/server & ./Message_passing/client 127.0.0.1 1000000 1
./Share_memory/schmem.o 1000000 1
./File_communication/file.o 1000000 10
echo -----------10MB test
./Pipes/Parented/server 10000000 5
./Pipes/Non_Parented/reader 10000000 5 & ./Pipes/Non_Parented/writer 10000000 5
./Message_passing/server & ./Message_passing/client 127.0.0.1 10000000 1
./Share_memory/schmem.o 10000000 1
./File_communication/file.o 10000000 10
echo -----------100MB test
./Pipes/Parented/server 100000000 5
./Pipes/Non_Parented/reader 100000000 5 & ./Pipes/Non_Parented/writer 100000000 5
./Message_passing/server & ./Message_passing/client 127.0.0.1 100000000 1
./Share_memory/schmem.o 100000000 1
./File_communication/file.o 100000000 5