# 2D_GameEngine

MSBuild.exe .\bin\win32\SDL_GAME.sln

cmake -S . -B bin/win32/ -G "Visual Studio 16 2019"

## Technologies

- `C++ 11`
- `SDL2`
- `Lua`
- `Glm`

---

## Setup

# Linux Systems

Make sure that these (or similar) directories are included

```javascript
"${default}",
  "lib/lua",
  "/usr/include",
  "/usr/local/include",
  "${workspaceRoot}";
```

Then make sure all dependencies are installed

Debian:

> build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev liblua5.3-dev glm

Arch:

> build-essential sdl2 sdl2_image sdl2_mixer sdl2_ttf-git lua glm

Run the following command to init cmake

> cmake -S . -B build

Then run the make using

> make -C ./build/linux

---
