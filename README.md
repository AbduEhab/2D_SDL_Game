# 2D_GameEngine

## Technologies

- `C++20`
- `SDL2`
- `Lua`
- `glm`

---

## Setup

# Linux Systems

> sdl's 'SDL_GetTicks()' has been very ify, it throws numbers in the millions every now and then which screws with the DeltaTime. I've implemented a temporary fix with the 'chrono' clock.

> Note that sdl2 has also been refusing to compile for me for a couple of days now due to a problem with Wayland. I've resorted to using the system SDL lib instead of my compiled one. 

Make sure all dependencies are installed

Debian:
```bash
sudo apt install build-essential sdl2 sdl2-image sdl2-ttf sdl2-mixer
```

Arch:
```bash
sudo pacman -S build-essential sdl2 sdl2_image sdl2_mixer sdl2_ttf-git
```

Download/update the submodules (cmake will get them automatically now)
```bash
git submodule sync
git submodule update --init --recursive
```

If the submodules don't work for whatever reason, you can install these dependancies and compile with them. (remove the `add_subdirectory()` calls from the ./CmakeLists if you're gonna use these system libs)

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
