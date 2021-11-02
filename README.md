# 2D_GameEngine

## Technologies

- `C++ 11`
- `SDL2`
- `Lua`
- `Glm`

---

## Setup

# Linux Systems


Make sure all dependencies are installed

Debian:
```bash
sudo apt install build-essential sdl2 sdl2-image sdl2-ttf sdl2-mixer
```

Arch:
```bash
sudo pacman -S build-essential sdl2 sdl2_image sdl2_mixer sdl2_ttf-git
```

Download/update the submodules
```bash
git submodule sync
git submodule update --init --recursive
```

If the submodules don't work for whatever reason, you can install these dependancies and compile with them

Debian:
```bash
sudo apt install build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev liblua5.3-dev glm
```

Arch:
```bash
sudo pacman -S build-essential sdl2 sdl2_image sdl2_mixer sdl2_ttf-git lua glm
```

Now run the following command to init cmake

> cmake -S . -B build

Then run make using

> make -C ./build

---
