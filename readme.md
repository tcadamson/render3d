# render3d
A basic 3D rendering framework built on top of GLFW and OpenGL. Includes all needed libraries as submodules, including GLAD, GLM, and stb_image.

![Preview](https://i.postimg.cc/wjV55DXZ/1670461331000.gif)

## Building
To build render3d, ensure you have [cmake](http://www.cmake.org/download/) installed (version >= 3.23). Clone this repo, passing the --recursive flag like so:
```bash
git clone --recursive https://github.com/tcadamson/render3d.git
```
Afterwards, you may run cmake to generate the needed project files for your platform. If you forget to include the --recursive flag, just use `git submodule update --init` to manually fetch all the included dependencies.

## License
MIT License

Copyright (c) 2022 Taylor Adamson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.