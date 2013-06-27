#!/bin/bash
project_dir=$(pwd)
mkdir -p build
cd build
cmake $project_dir
cd $project_dir
