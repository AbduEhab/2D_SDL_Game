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

Get these packages form your package manager

> build-essential git lua

Then update the submodules using these 2 lines

```bash
git submodule init
git submodule update
```


Run the following command to init cmake

> cmake -S . -B build

Then run the make using

> make -C ./build

---

[submodule "external/SDL2_ttf"]
	path = external/SDL2_ttf
	url = https://github.com/libsdl-org/SDL_ttf.git
[submodule "external/SDL2"]
	path = external/SDL2
	url = https://github.com/libsdl-org/SDL.git
[submodule "external/glm"]
	path = external/glm
	url = https://github.com/g-truc/glm.git
