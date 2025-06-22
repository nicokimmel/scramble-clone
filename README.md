# Dependencies
```Bash
dnf install gcc-c++ pkg-config glfw-devel mesa-libGL-devel glew-devel
```

# Compilation

```Bash
g++ -std=c++20 -Wall -Wextra \
    $(pkg-config --cflags glew glfw3) \
    $(find src -type f -name '*.cpp') \
    -o dist/Scramble \
    $(pkg-config --libs glew glfw3)
```
