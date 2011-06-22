#!/bin/sh

echo "Compiling and installing shared library..."
cd Default
make clean
make
sudo cp libstanford-scene-database.so /usr/local/lib

echo "Compiling sceneViewer..."
cd ../sceneViewer/Default
make clean
make
cp sceneViewer ../../bin

echo "Compiling modelViewer..."
cd ../../modelViewer/Default
make clean
make
cp modelViewer ../../bin

echo "Done. Run modelViewer or sceneViewer from bin directory."
