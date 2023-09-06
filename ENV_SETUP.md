# Programming Language II

## Required (or at least recommended) Code extensions:

```
code --install-extension ms-vscode.cmake-tools
code --install-extension ms-vscode.cpptools
code --install-extension ms-vscode.cpptools-extension-pack
code --install-extension ms-vscode.cpptools-themes
code --install-extension xaver.clang-format
code --install-extension matepek.vscode-catch2-test-adapter
```
## Clang formatter
How to configure default C++ formater:
1. Open any C++ file
2. Crtl + Shift + P
3. Find 'Format document with' and press Enter
4. Select 'Configure default formatter'
5. Select 'Clang-Format'

**Formatter usage:** Ctrl + Shift + I

## Required system packages install command
```
sudo apt install gcc g++ gdb cmake make build-essential clang-format libssl-dev git
```

## CMake 3.18.4 install
Ubuntu 18.04 use CMake version <3.11 by default. Some features required for project setup/compile require at CMake 3.11+.

How to check CMake version? Use following command:
```
cmake --version
```

If the version is too old, use following commands to install CMake:
```
wget https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4.tar.gz
tar -xzvf cmake-3.18.4.tar.gz
cd cmake-3.18.4/
sudo ./bootstrap
sudo make install
```

**Compiler**: GCC 7.5.0 or GCC 9.4.0 \
**System**: Ubuntu 18.04 or 20.04
<br/><br/>

## Ubuntu Virtual Machine on Windows PC
If you are not able to (or do not know how) install and setup native Ubuntu on your PC, you can use VM.

Download and install Oracle Virtual Box - https://www.virtualbox.org/wiki/Downloads

Tutorial how to setup Ubuntu in Virtual Box - https://www.youtube.com/watch?v=QbmRXJJKsvs

After proper Ubuntu install in VM install following: \
- Visual Studio Code: https://code.visualstudio.com/Download \
- Required system packages (list in previous section) \
- Install CMake 3.18.4 (only for Ubuntu 18.04, instruction above) \
- Install VS Code plugins (list in previous section)