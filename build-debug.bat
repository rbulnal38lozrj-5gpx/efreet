@echo off

if not exist "build-debug" md build-debug
if not exist "bin-debug" md bin-debug

cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=bin-debug
cmake --build build-debug -j9 --config Debug
cmake --install build-debug --config Debug