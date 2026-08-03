#!/bin/bash

echo "================================================================="
echo "Before continuing, please ensure you have the necessary"
echo "build dependencies installed."
echo ""
echo "On Debian/Ubuntu-based systems, run:"
echo "   sudo apt update && sudo apt install -y build-essential texinfo"
echo "================================================================="
echo ""
read -r -s -n 1 -p "(Press any key to continue)"
echo ""
echo ""

echo "Cloning 'sh2-elf-gcc'..."
echo "-----------------------------------------------------------------"
if [ ! -d "sh2-elf-gcc" ]; then
    git clone https://github.com/Synival/sh2-elf-gcc.git
    echo "Done."
else
    echo "Directory 'sh2-elf-gcc' already exists; skipping."
fi
echo ""

echo 'Building binutils, newlib, and gcc...'
echo "-----------------------------------------------------------------"
cd sh2-elf-gcc || { echo "Failed to enter directory 'sh2-elf-gcc'. Exiting."; exit 1; }
    ./build-toolchain.sh
cd ..
echo ""

echo "Creating 'sh2-toolchain' symlink..."
echo "-----------------------------------------------------------------"
if [ ! -e "sh2-toolchain" ]; then
    ln -s sh2-elf-gcc/sh2-toolchain sh2-toolchain
    echo "Done."
else
    echo "File or symlink 'sh2-toolchain' already exists; skipping."
fi
echo ""

echo "================================================================="
echo "Setup Complete!"
echo "You should now be able to run 'make' and compile."
echo "================================================================="
