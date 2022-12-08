# render3d [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A basic 3D rendering framework built on top of OpenGL and GLFW. It includes all needed libraries as submodules, such as GLAD, GLM, and stb_image.

![Preview](https://i.postimg.cc/wjV55DXZ/1670461331000.gif)

## Building
To build render3d, ensure cmake is installed and available on your machine (version >= 3.23). Clone this repo, passing the recursive flag like so:
```bash
git clone --recursive https://github.com/tcadamson/render3d.git
```
Afterwards, you may run cmake to generate the needed project files for your specific platform/IDE using the appropriate generator. If you forget to include the recursive flag, just use `git submodule update --init` to manually fetch all the included dependencies after cloning.