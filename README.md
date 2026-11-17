# Procedural GLSL Shader Visualizer (C++ & Raylib)

A real-time interactive **GLSL Fragment Shader** visualization application built using C++ and the **Raylib** library. It generates dynamic, neon-styled geometric patterns utilizing Inigo Quilez-style cosine color palettes and coordinate folding techniques, enabling real-time parameter manipulation via keyboard and mouse input.

---

## Controls and Shortcuts

The application operates with two primary modes (Normal / Edit Mode). Edit mode is enabled by default (`editmode = true`).

### General Controls
* **`E`**: Toggle the edit UI overlay on/off.
* **`S`**: Toggle the color palette editing panel on/off.
* **`L`**: Toggle mouse interaction (Mouse Mode) on/off.
* **`Shift + R`**: Reset all parameters and color vectors to their default values.

### Parameter Adjustments
* **`Shift + Right / Left Arrow`**: Increase / decrease the `cnt` (frequency multiplier) value.
* **`M` / `N`**: Increase / decrease the `neon` intensity parameter.

### Color Palette Editor (Active when `showcolors` is enabled)
Select the target color vector using keys `1`, `2`, `3`, or `4`:
* **`1`**: Vector `a`
* **`2`**: Vector `b`
* **`3`**: Vector `c`
* **`4`**: Vector `d`

Modify the channel values of the selected vector by holding down the corresponding color key and pressing the **Right / Left Arrow** keys:
* **`R` + Arrows**: Adjust the Red channel.
* **`G` + Arrows**: Adjust the Green channel.
* **`B` + Arrows**: Adjust the Blue channel.

---

## Requirements

* **C++ Compiler** supporting C++17 or newer (e.g., GCC, Clang, MSVC)
* **Raylib Library** for window management and rendering
* **OpenGL 3.3+** compatible graphics card

---

## Compilation and Execution (Linux / GCC Example)

Ensure that `main.cpp` and `shader.fs` are located in the same directory, then compile using the terminal command:

```bash
g++ main.cpp -o shader_app -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
