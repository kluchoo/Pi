#!/usr/bin/env bash 
# Dodaj funkcje do .bashrc dla wszystkich użytkowników
cat << 'EOF' >> /etc/bash.bashrc

VSC-compile() {
  if [[ $1 = "DEBUG" ]]; then
    find . -type f -iname "*.cpp" -exec echo -ne "kompilowanie (DEBUG): \e[32m {}\e[0m \033[0K\r" \; -execdir /usr/bin/x86_64-w64-mingw32-g++- -Wall -D $1 -fdiagnostics-color=always -static {} -o output.exe \;
  else
    find . -type f -iname "*.cpp" -exec echo -ne "kompilowanie: \e[32m {} \e[0m \033[0K\r" \; -execdir /usr/bin/x86_64-w64-mingw32-g++-win32 -std=c++2a -Wall -fdiagnostics-color=always -static {} -o output.out \;
    find . -type f -iname "*.cpp" -exec echo -ne "kompilowanie: \e[32m {} \e[0m \033[0K\r" \; -exec g++ -std=c++2a -Wall {} -o output.out \;
  fi
}

VSC-compile-headers() {
   if [[ $1 = "DEBUG" ]]; then
    /usr/bin/x86_64-w64-mingw32-g++-win32 -std=c++2a -Wall -D $1 -fdiagnostics-color=always -static  -o output.exe *.cpp
    g++ -std=c++2a -Wall -D $1 -o output.out *.cpp
  else
    echo -ne "kompilowanie:  \e[32m output.exe \e[0m \033[0K\r"
    /usr/bin/x86_64-w64-mingw32-g++-win32 -std=c++2a -Wall -fdiagnostics-color=always -static -o output.exe *.cpp
    echo -ne "kompilowanie: \e[31m output.out \e[0m \033[0K\r"
    g++ -std=c++2a -Wall -o output.out *.cpp
  fi

  echo -e "\n"
  if [ $? -eq 0 ]; then
  ./output.out
  fi
}

cmake-compile() {
    if [[ -f makefile ]]; then
        make && ctest
    else
      cmake CMakeLists.txt && make && ctest
    fi
}
EOF
# Dodaj aliasy do .bashrc dla wszystkich użytkowników
echo "alias cpp-compile='VSC-compile'" >> /etc/bash.bashrc
echo "alias cpp-compile-headers='VSC-compile-headers'" >> /etc/bash.bashrc
echo "alias cpp-tests='cmake-compile'" >> /etc/bash.bashrc