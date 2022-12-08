# render3d

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A basic 3D rendering framework built on top of OpenGL and GLFW. Includes all needed libraries as submodules, such as GLAD, GLM, and stb_image.

![Preview](https://i.postimg.cc/wjV55DXZ/1670461331000.gif)

## Building
To build render3d, ensure you have [cmake](http://www.cmake.org/download/) installed (version >= 3.23). Clone this repo, passing the recursive flag like so:
```bash
git clone --recursive https://github.com/tcadamson/render3d.git
```
Afterwards, you may run cmake to generate the needed project files for your platform. If you forget to include the recursive flag, just use `git submodule update --init` to manually fetch all the included dependencies after cloning.