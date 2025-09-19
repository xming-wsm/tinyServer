#!/bin/bash

# 定义构建目录
BUILD_DIR="./build"

# 检查构建目录是否存在，不存在则创建
if [ ! -d "$BUILD_DIR" ]; then
    echo "创建build目录..."
    mkdir -p "$BUILD_DIR"
    if [ $? -ne 0 ]; then
        echo "错误：创建build目录失败"
        exit 1
    fi
fi

# 进入构建目录
echo "进入build目录..."
cd "$BUILD_DIR" || {
    echo "错误：无法进入build目录"
    exit 1
}

# 移动 compile_commands.json 文件
cp ./compile_commands.json ../.vscode

# 运行cmake生成Makefile
echo "运行cmake配置项目..."
cmake ..
if [ $? -ne 0 ]; then
    echo "错误：cmake配置失败"
    exit 1
fi

# 执行make编译
echo "开始编译项目..."
ninja
if [ $? -ne 0 ]; then
    echo "错误：编译失败"
    exit 1
fi

echo "构建成功！可执行文件在 build 目录下"


echo "Running Progaram ..."
echo " "
./tinyServer


exit 0
    
