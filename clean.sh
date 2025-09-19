#!/bin/bash
BUILD_DIR="./build"
if [ -d "$BUILD_DIR" ]; then
    echo "清理build目录..."
    rm -rf "$BUILD_DIR"/*
fi
echo "清理完成"