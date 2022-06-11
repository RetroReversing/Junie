# ReversingEmulator.com (Fork of Junie)

ReversingEmulator.com is a web-based [LibRetroReversing](https://github.com/RetroReversing/libRetroReversing) frontend that aims to run entirely in your browser, desktop or mobile! 
* No installation on the end-devices.
* Near-native performances thanks to WebAssembly.
* Wide range of supported/compatible cores (... soon).

Junie currently runs on most recent browsers, though your experience will probably be the best on Chrome and Safari (I have issues on Firefox on my side, not sure if it's isolated to my computer).

# Supported Consoles
The following consoles are fully supported:
* Game Gear
* Sega Master System

The following consoles are in a semi-working state:
* NES
* SNES
* GB/GBC
* GBA - No reversing features yet
* NDS - No reversing features yet

# Games
No games are hosted on the site itself so you need to provide your own ROMS, these will be stored in your browser's local storage so reloading the page will continue where you left of. 

However if you clear your browser cache all your ROMS and reversing data will be removed.

# Supported features

- [x] All the systems described in the [Supported Consoles](#Supported-Consoles) section.
- [x] Save files (stored inside your browser's storage).
- [x] Additional core-specific system files.
- [x] Core-specific configurations override.
- [x] Multi-touch controller, with D-pad used as a joystick.
- [x] Re-mappable keyboard to joypad bindings. 
- [x] Touch inputs, enabled by pressing the top button.
- [x] Savestate creation and restore.
- [x] Fast-forward up to 4 times the original speed.

# Configuration

Junie and the underlying cores can be configured using the `settings.json` file, located in the `bin` directory. A typical default configuration looks like that:

```json
{
    "language": "ENGLISH",
    "assets": {
        "menu":    "menu.png",
        "left":    "left.png",
        "right":   "right.png",
        "loading": "loading.png"
    },
    "bindings": {
        "A":      "X",
        "B":      "Z",
        "X":      "S",
        "Y":      "A",
        "UP":     "UP",
        "DOWN":   "DOWN",
        "LEFT":   "LEFT",
        "RIGHT":  "RIGHT",
        "L":      "C",
        "R":      "D",
        "SELECT": "ENTER",
        "START":  "SPACE"
    },
    "melonDS": {
        "dependencies": [
            "bios7.bin",
            "bios9.bin",
            "firmware.bin"
        ],
        "configurations": {
            "melonds_touch_mode": "Touch"
        }
    }
}
```

## Global configurations

Those configuration will be used regardless of the underlying emulator in use.

| Name | Description |
| ---- | ----------- |
| language | The prefered language to use, currently used only for melonDS. Must match values defined in [`libretro.h`](https://github.com/libretro/libretro-common/blob/master/include/libretro.h#L260) without the prefix. |
| assets | Defines the list of UI assets to use. Files will be requested  as follows: relatively from the `/assets/<file_name>`. |
| bindings | Defines the joypad-keyboard bindings. On the left, values from [`libretro.h`](https://github.com/libretro/libretro-common/blob/master/include/libretro.h#L188) without the prefix. On the right, values from [`matoya.h`](https://github.com/matoya/libmatoya/blob/master/src/matoya.h#L344) without the prefix. |

## Core-specific configurations

Those configurations will only be applied to the core they target. Section name must reflect the full name of the core. See the credits section for the exact available names.

| Name | Description |
| ---- | ----------- |
| dependencies | A list of extra dependencies the emulator might require. Files will be exposed to the core as follows: `/system/<core_name>/<file_name>`. |
| configurations | A list of custom configurations to apply to the emulator. Details of available configurations for each core are logged in the browser console. |

# Build & Run

To initialize the submodules if you haven't already:

```bash
git submodule sync
git submodule update --init --recursive
```

To build a local version of Junie:

```bash
make
```

## Running the dev server
In order to get the latest changes and do development on the platfom, you can run the dev server.
```
cd libRetroReversing/websrc
yarn dev 
```
Then go to http://localhost:8081 

## Compiling the WASM cores
```bash
cd cores && rm -rf *.a && make all
```

## Packaging as an executable
To package for all the available platforms:

```bash
make dist
```

To run the packaged version, go to `dist/<platform>` and run:

```bash
./server   # UNIX platforms
server.exe # Windows platform
```

## Building with Docker
If you prefer to use Docker, here you go:

```bash
# Build the image
docker build -t junie .

# Run the container
docker run \
    -d --rm \
    --name junie \
    -p 8000:8000 \
    -v /path/to/settings.json:/app/bin/settings.json \
    -v /path/to/system:/app/system \
    -v /path/to/games:/app/games \
    junie
```

# Side notes

## Cores compatibility

Well, when I wrote "wide range of cores", it might be a little exagerated... 

Junie is using the [wasi-sdk](https://github.com/WebAssembly/wasi-sdk) to build the cores, and it currently lacks features that cores sometimes use extensively. 
Right now, the most problematic ones are threading and JIT backend. Also, no OpenGL support at this time (this one is actually doable but probably requires a lot of work).

That said, even after disabling all the above features when building the cores, performance is still far beyond acceptable for most cores. You will however have some trouble with 3D games on Nintendo DS (2D games run quite fine on recent hardware, as far as I've tested). Low-end mobile phones might also have struggle with the SNES.

# Credits

## Libraries
- All of this is only possible thanks to the [Junie](https://github.com/Namaneo/Junie) libRetro Frontend
- Also thanks to [libmatoya](https://github.com/matoya/libmatoya).
- The [zlib](https://github.com/madler/zlib) library is required for some cores.
- And of course, modules and headers from [libretro-common](https://github.com/libretro/libretro-common).

## Cores

- [mGBA](https://github.com/libretro/mgba) for Game Boy, Game Boy Color and Game Boy Advance emulation.
- [Snes9x](https://github.com/libretro/snes9x) for SNES emulation.
- [melonDS](https://github.com/libretro/melonDS) for Nintendo DS emulation.
- [Genesis Plus GX](https://github.com/libretro/Genesis-Plus-GX) for Mega Drive and Master System emulation.
- [QuickNES](https://github.com/libretro/QuickNES_Core) for NES emulation.

## Tools

- [ncc](https://github.com/vercel/ncc) is used to build the server standalone.
- [nexe](https://github.com/nexe/nexe) is used to package the server into executables.
 
## Assets

- Original controller assets come from the [Delta emulator](https://github.com/rileytestut/Delta).
- Menu graphics come from the [Google Material Icons](https://fonts.google.com/icons).
- Loading screen comes from [Pixel Art Maker](http://pixelartmaker.com/art/8f6c49d5035cd32) (not sure exactly who to credit).

# License

ReversingEmulator.com is licensed under the [GNU General Public License v3.0](https://github.com/Namaneo/Junie/blob/main/LICENSE.md). When applicable, dependencies listed in the [Credits](#credits) section retain their original licenses.