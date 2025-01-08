#! /usr/bin/env bash
function print_info {
    echo -ne "\e[32m$1\e[0m \033[0K\r"
}

print_info "Fetching the latest Doxygen release URL..."
url="https://api.github.com/repos/doxygen/doxygen/"
download_url=$(curl -s https://api.github.com/repos/doxygen/doxygen/releases/latest | jq -r '.assets[] | select(.name | startswith("doxygen") and endswith("bin.tar.gz")) | .browser_download_url')

print_info "Downloading Doxygen..."
curl -sL "$download_url" -o "doxygen.tar.gz"

print_info "Extracting Doxygen..."
tar -xf doxygen*.tar.gz
rm doxygen*.tar.gz

print_info "Renaming Doxygen folder..."
mv doxygen* doxygen
cd doxygen

print_info "Setting permissions..."
sudo chmod 777 *

print_info "Building Doxygen..."
sudo make -B &> /dev/null
cd - &> /dev/null

print_info "Cleaning up..."
rm -rf doxygen*

print_info "Doxygen setup complete."