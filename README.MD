# 🧰 Daily C++ Modules

A curated collection of production-ready, lightweight, and zero-overhead C++ micro-modules for everyday development. 

Instead of pulling in heavy, monolithic libraries for basic tasks, developers can simply copy a single folder from this repository and drop it straight into their project.

### 🐧 Fully Supported Platforms:
* **Windows** — Native Win32 / WinNT API & WGL graphics contexts.
* **Linux** — Pure X11 / Xlib sockets & GLX context mapping (No heavy desktop environments toolkits needed).

---

## 🎯 The Philosophy

* **Zero Boilerplate:** No heavy configurations, no external cascade dependencies. Just pure C++23.
* **Plug & Play:** Designed natively with modern CMake (`FILE_SET CXX_MODULES`). Copy-paste and use via `add_subdirectory`.
* **Modern Standards:** Built from the ground up using modern features (`import std;`, `std::expected`, `std::ranges`, `std::println`) for absolute compile-time safety and performance.
* **Bite-Sized:** Each directory solves exactly *one* specific domain problem beautifully and minimally.

---

## 🚀 High-Reliability Mission-Critical Build Configuration

This project supports a compilation mode with the maximum possible level of static analysis and runtime safety guards, standard for aerospace and mission-critical software. It aims to completely eliminate undefined behavior (UB), implicit type narrowings, and memory safety issues. 

Every single compiler warning is strictly treated as a hard compilation error.

### Applied Compiler Flags & Security Guards

*   **`-Werror`** – Zero tolerance for warnings; turns every compiler warning into a build-stopping error.
*   **`-Wall -Wextra -Wpedantic`** – Enables the core, extra, and strict ISO C++ standard conformance diagnostics.
*   **`-Wconversion -Wsign-conversion`** – Audits all implicit type narrowing and sign changes (e.g., mixing `int` and `unsigned`).
*   **`-Weffc++`** – Enforces Scott Meyers' Effective C++ guidelines (proper member initialization, safe destructors).
*   **`-Wshadow -Wlogical-op -Wstrict-overflow=5`** – Detects variable shadowing, suspicious logical conditions, and dangerous compiler assumptions about overflows.
*   **`-Wold-style-cast -Wzero-as-null-pointer-constant`** – Completely bans old C-style casts and raw `0` pointers, enforcing type-safe C++ casts (`static_cast`, `reinterpret_cast`) and `nullptr`.
*   **`-Wcast-align -Wcast-qual -Wformat=2`** – Checks pointer alignment safety, const correctness modifications, and strictly validates string formatting arguments.
*   **`-Wmissing-declarations`** – Ensures every exported or global function has a proper forward declaration to maintain interface integrity.
*   **`-fstack-protector-strong`** – Injects defensive "canaries" into the stack to crash the application instantly if a buffer overflow is attempted.
*   **`-D_GLIBCXX_ASSERTIONS`** – Forces runtime bounds checking on standard STL containers (`std::vector::operator[]`, `std::string`).
*   **`-DCMAKE_BUILD_TYPE=RelWithDebInfo`** – Builds with stable `-O2` optimizations while preserving full debugging symbols for precise crash dump analysis.

---

## 📁 Repository Structure

Every tool is completely isolated in its own directory:

```text
.
├── CMakeLists.txt         # Global build configuration (runs tests for all modules)
└── glm_lite/              # A plug-and-play micro-module example
    ├── CMakeLists.txt     # Local CMake target definition
    ├── glm_lite.ixx       # C++23 module interface
    └── main.cpp           # Usage examples / Integration tests
```

---

## 🚀 Quick Integration Guide

To use any module (e.g., `glm_lite`) in your codebase:

1. **Copy** the module's directory into your project.
2. Link it in your **`CMakeLists.txt`** (requires CMake 3.30+ for robust standard library modules support):

```cmake
cmake_minimum_required(VERSION 3.30)
project(YourApp LANGUAGES CXX)

# Include the copied module
add_subdirectory(glm_lite)

add_executable(app main.cpp)
target_link_libraries(app PRIVATE glm_lite)
```

3. **Import** it directly in your source code:
```cpp
import glm_lite;
import std;

int main() {
    glm::vec3 velocity{0.0f, 9.8f, 0.0f};
    std::println("Vector initialized at gravity acceleration: [{}, {}, {}]", velocity.x, velocity.y, velocity.z);
}
```

---

## Prerequisites

* **CMake 3.30+** (Strictly required for stable C++23 Standard Library Modules support via `import std;`)
* **Compilers:** MSVC 2026+ (Windows) or GCC 15.1+ (Linux/MinGW) / Clang 19+

## 🛠️ Building & Testing Locally

To build the entire ecosystem and run validation tests for all modules simultaneously, ensure you have a compiler with robust C++23 module support and **Ninja**.

```bash
git clone https://github.com
cd daily-cpp-modules

# Configure using the Ninja generator (highly recommended for C++ Modules)
cmake -B build -G Ninja

# Build all modules and verification drivers
cmake --build build
```

---

## 🗂️ Available Micro-Modules

| Module | Purpose / Domain | Key C++ Features Used |
|:---|:---|:---|
| **[`WinLite`](./Modules/WinLite)** | Lightweight Windowing & Event loop for **Windows (WinNT)** and **Linux (Xlib)**. | Native OS Display Handles, C++23 Unions |
| **[`PixelPainter`](./Modules/PixelPainter)** | Software rasterizer canvas for custom 2D primitives. | `std::span`, Bresenham's loops, `constexpr` |
| **[`PixelCopier`](./Modules/PixelCopier)** | Real-time texture blitting, clipping, and sprite scaling. | Fixed-Point `16.16` bit precision mapping, `std::span` |
| **[`GlmLite`](./Modules/GlmLite)** | Ultra-lightweight vector math, 4x4 matrices & matrix transformations. | Column-major layout, `constexpr`, `std::sqrt/sin/cos` |
| **[`OpenGL`](./Modules/OpenGL)** | Explicit OpenGL extension loader matrix (Modern **GLAD replacement**). | Dynamic symbol resolution (`GetProcAddress`), `import std;` |
| **[`BmpLoader`](./Modules/BmpLoader)** | Exception-free 24/32-bit BMP image loader. | Monadic `std::expected`, layout padding checks |
| **[`TgaLoader`](./Modules/TgaLoader)** | Exception-free 24/32-bit TGA true-color texture loader. | Monadic `std::expected`, descriptor orientation flags |
| **[`BmpSaver`](./Modules/BmpSaver)** | 24/32-bit BMP image exporter and canvas dumper. | Monadic `std::expected`, safe memory serialization |
| **[`HighResTimer`](./Modules/HighResTimer)** | Stopwatch performance timer for profiling loops. | Monadic clocks (`std::chrono::high_resolution_clock`) |
| **[`FpsCounter`](./Modules/FpsCounter)** | Non-drifting real-time frames-per-second indicator. | Steady non-drifting accumulator intervals |
| **[`LibLoader`](./Modules/LibLoader)** | Cross-platform dynamic library loader for `.dll` and `.so` files. | OS-independent runtime binary loading |
| **[`SDL1Loader`](./Modules/SDL1)** | Dynamic wrapper for the SDL 1.2 library. | Basic runtime `.dll`/`.so` abstraction |
| **[`SDL2Loader`](./Modules/SDL2)** | Dynamic wrapper for the SDL 2.x library. | Basic runtime `.dll`/`.so` abstraction |
| **[`SDL2Loader`](./Modules/SDL3)** | Dynamic wrapper for the SDL 3.x library. | Basic runtime `.dll`/`.so` abstraction |

---

## 🤝 Contributing

Have a tiny C++23 utility module that you use in every project? Feel free to open a Pull Request! Please ensure your module is fully self-contained, provides a `CMakeLists.txt` with `FILE_SET CXX_MODULES`, and includes a clean automated testing driver.

## 📄 License
This project is open-source software licensed under the **Boost Software License - Version 1.0 - August 17th, 2003**. Use these modules freely in personal, educational, or commercial projects.

---

## 🖼️ Gallery & Demos

Here is the `RenderPixels` showcase running live, combining both **WinLite** (window management) and **SoftwareRender** (fixed-point canvas primitives, Bresenham lines, and clipping math) modules:

| | | | |
| :---: | :---: | :---: | :---: |
| <img src="./screenshots/104 20.10.2026 13_38_39.png" width="100%" /> | <img src="./screenshots/1066 20.10.2026 12_56_41.png" width="100%" /> | <img src="./screenshots/1212 20.10.2026 12_56_00.png" width="100%" /> | <img src="./screenshots/1272 20.10.2026 12_56_58.png" width="100%" /> |
| <img src="./screenshots/16 20.10.2026 12_58_23.png" width="100%" /> | <img src="./screenshots/344 20.10.2026 12_57_08.png" width="100%" /> | <img src="./screenshots/3611 20.10.2026 12_56_10.png" width="100%" /> | <img src="./screenshots/3653 20.10.2026 12_55_38.png" width="100%" /> |
| <img src="./screenshots/406 20.10.2026 13_37_24.png" width="100%" /> | <img src="./screenshots/473 20.10.2026 12_58_11.png" width="100%" /> | <img src="./screenshots/5371 20.10.2026 12_56_25.png" width="100%" /> | <img src="./screenshots/542 20.10.2026 12_56_50.png" width="100%" /> |
| <img src="./screenshots/574 20.10.2026 13_38_29.png" width="100%" /> | <img src="./screenshots/580 20.10.2026 13_37_00.png" width="100%" /> | <img src="./screenshots/591 20.10.2026 13_37_07.png" width="100%" /> | <img src="./screenshots/596 20.10.2026 13_38_09.png" width="100%" /> |
| <img src="./screenshots/601 20.10.2026 13_37_52.png" width="100%" /> | <img src="./screenshots/705 20.10.2026 12_54_29.png" width="100%" /> | <img src="./screenshots/756 20.10.2026 12_57_27.png" width="100%" /> | <img src="./screenshots/776 20.10.2026 12_55_33.png" width="100%" /> |
| <img src="./screenshots/Daily C++ Modules - Demo 10_ Raster Screen Wobble 20.10.2026 13_44_51.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules - Demo 11_ Distortion Portal 20.10.2026 13_43_22.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules - Demo 12_ Voxel Landscape 20.10.2026 13_44_36.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules - Demo 13_ Interactive Fractal Fern 20.10.2026 13_43_33.png" width="100%" /> |
| <img src="./screenshots/Daily C++ Modules - Demo 16_ Ray-traced Tunnel with Attenuation 20.10.2026 13_43_53.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules - Demo 17_ CPU Water Ripple Effect 20.10.2026 13_44_43.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules - Demo 18_ CPU Real-time Lens Effect 20.10.2026 13_43_43.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules - Demo 19_ Procedural Maze DFS Visualizer 20.10.2026 13_44_06.png" width="100%" /> |
| <img src="./screenshots/Daily C++ Modules - Demo 1_ Retro Plasma 20.10.2026 13_44_20.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules - Demo 20_ 2D Dissolve Fade Effect 20.10.2026 13_43_18.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules - Demo 2_ 3D Starfield 20.10.2026 13_44_24.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules - Demo 3_ Digital Matrix Rain 20.10.2026 13_44_02.png" width="100%" /> |
| <img src="./screenshots/Daily C++ Modules - Demo 4_ Mandelbrot Fractal 20.10.2026 13_43_48.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules - Demo 6_ Dense Particle Fountain (15k) 20.10.2026 13_44_15.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules - Demo 7_ Oldschool Fire Effect 20.10.2026 13_43_28.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules - Demo 8_ 3D Tunnel Effect 20.10.2026 13_44_29.png" width="100%" /> |
| <img src="./screenshots/Daily C++ Modules - Demo 9_ Organic Metaballs 20.10.2026 13_44_10.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules_ 3D Hyper-Tunnel 20.10.2026 12_58_06.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules_ Enhanced Interactive Demo 20.10.2026 13_37_12.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules_ Interactive Plexus Network 20.10.2026 13_38_01.png" width="100%" /> |
| <img src="./screenshots/Daily C++ Modules_ Lissajous Laser Show 20.10.2026 13_37_39.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules_ Magnetic Vector Field 20.10.2026 13_37_47.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules_ Morphing Julia Fractal 20.10.2026 13_37_34.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules_ Morphing Julia Fractal 20.10.2026 13_37_56.png" width="100%" /> |
| <img src="./screenshots/Daily C++ Modules_ Sine Plasma via Pixel API 20.10.2026 13_38_14.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules_ Starfield Warp 20.10.2026 13_38_21.png" width="100%" /> | <img src="./screenshots/Daily C++ Modules_ Tesla Lightning Show 20.10.2026 13_38_34.png" width="100%" /> | <img src="./screenshots/Demo 01_ Raymarching SDF 20.10.2026 12_57_36.png" width="100%" /> |
| <img src="./screenshots/GL3 Game of Life on GPU 20.10.2026 12_56_45.png" width="100%" /> | <img src="./screenshots/GL3 Poincare Disk 20.10.2026 12_57_31.png" width="100%" /> | <img src="./screenshots/GL3 Superformula 3D 20.10.2026 12_57_45.png" width="100%" /> | <img src="./screenshots/GL3 Voronoi Crystal 20.10.2026 12_57_51.png" width="100%" /> |
| <img src="./screenshots/GL3 Wave Interference 20.10.2026 12_58_00.png" width="100%" /> | <img src="./screenshots/OpenGL 1.2 + GLM - Rotating Color Cube 20.10.2026 12_55_53.png" width="100%" /> | <img src="./screenshots/OpenGL 1.2 - Mirror Equalizer 3D 20.10.2026 12_55_43.png" width="100%" /> | <img src="./screenshots/OpenGL 1.2 - Psychedelic Fractal Carpet 20.10.2026 12_54_49.png" width="100%" /> |
| <img src="./screenshots/OpenGL 1.2 - Specular Disco Ball & Dynamic Lights 20.10.2026 12_56_04.png" width="100%" /> | <img src="./screenshots/OpenGL 1.2 - Synthwave Retro Landscape 20.10.2026 12_56_19.png" width="100%" /> | <img src="./screenshots/OpenGL 1.2 - Vector XOR Explosion 20.10.2026 12_56_28.png" width="100%" /> | <img src="./screenshots/OpenGL 1.2 - Volumetric 3D Stained Glass Hall 20.10.2026 12_55_48.png" width="100%" /> |
| <img src="./screenshots/OpenGL 1.2 - X-Ray Stencil Scanner 20.10.2026 12_56_34.png" width="100%" /> | <img src="./screenshots/OpenGL 1.2 - Z-Buffer Planar Reflection 20.10.2026 12_56_15.png" width="100%" /> | <img src="./screenshots/OpenGL 3.3 Core - Cosmic Particle Galaxy 20.10.2026 12_57_18.png" width="100%" /> | <img src="./screenshots/OpenGL 3.3 Core - Soft Fluid Water Caustics 20.10.2026 12_57_56.png" width="100%" /> |
| <img src="./screenshots/OpenGL 3.3 Core - Specular Disco Ball Shader 20.10.2026 12_57_40.png" width="100%" /> | <img src="./screenshots/SDL2 3D Raycaster Demo 20.10.2026 13_46_35.png" width="100%" /> | <img src="./screenshots/SDL2 Autonomous Agents (Boids) Demo 20.10.2026 13_45_33.png" width="100%" /> | <img src="./screenshots/SDL2 Barnsley Fern Fractal Demo 20.10.2026 13_45_38.png" width="100%" /> |
| <img src="./screenshots/SDL2 Color Wave Demo 20.10.2026 13_45_44.png" width="100%" /> | <img src="./screenshots/SDL2 Crystal Growth (DLA Fractal) Demo 20.10.2026 13_45_51.png" width="100%" /> | <img src="./screenshots/SDL2 Delaunay Triangulation Demo 20.10.2026 13_45_57.png" width="100%" /> | <img src="./screenshots/SDL2 Elastic Grid Demo 20.10.2026 13_46_02.png" width="100%" /> |
| <img src="./screenshots/SDL2 Epicycles Fourier Demo 20.10.2026 13_46_09.png" width="100%" /> | <img src="./screenshots/SDL2 Interactive Wave Equation Demo 20.10.2026 13_47_09.png" width="100%" /> | <img src="./screenshots/SDL2 Inverse Kinematics Demo 20.10.2026 13_46_20.png" width="100%" /> | <img src="./screenshots/SDL2 Lissajous Curves Demo 20.10.2026 13_46_24.png" width="100%" /> |
| <img src="./screenshots/SDL2 Physarum Slime Simulation Demo 20.10.2026 13_46_28.png" width="100%" /> | <img src="./screenshots/SDL2 Raymarched Clouds Demo 20.10.2026 13_46_44.png" width="100%" /> | <img src="./screenshots/SDL2 Raymarched Metaballs Demo 20.10.2026 13_46_49.png" width="100%" /> | <img src="./screenshots/SDL2 Soft Body Physics Demo 20.10.2026 13_46_56.png" width="100%" /> |
| <img src="./screenshots/SDL2 Verlet Cloth Demo 20.10.2026 13_47_02.png" width="100%" /> | <img src="./screenshots/Wow Effect_ Fractal Neon Tunnel 20.10.2026 12_57_14.png" width="100%" /> | <img src="./screenshots/Wow Effect_ Liquid Mirror Ocean 20.10.2026 12_57_02.png" width="100%" /> | <img src="./screenshots/Wow Effect_ Plasma Sphere 20.10.png" width="100%" /> |
