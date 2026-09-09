# 🧰 Daily C++ Modules

A curated collection of production-ready, lightweight, and zero-overhead C++ micro-modules for everyday development. 

Instead of pulling in heavy, monolithic libraries for basic tasks, developers can simply copy a single folder from this repository and drop it straight into their project.

---

## 🎯 The Philosophy

* **Zero Boilerplate:** No heavy configurations, no external dependencies. Just pure C++23.
* **Plug & Play:** Designed natively with modern CMake (`FILE_SET CXX_MODULES`). Copy-paste and use via `add_subdirectory`.
* **Modern Standards:** Built from the ground up using C++20/C++23 features (`import std;`, `std::expected`, `std::ranges`, `std::print`) for modern safety and performance.
* **Bite-Sized:** Each directory solves exactly *one* specific domain problem beautifully and minimally.

---

## 🚀 High-Reliability Mission-Critical Build Configuration

This project supports a compilation mode with the maximum possible level of static analysis and runtime safety guards, standard for aerospace and mission-critical software. It aims to completely eliminate undefined behavior (UB), implicit type narrowings, and memory safety issues. 

Every single compiler warning is strictly treated as a hard compilation error.

---

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
└── glm_lite/              # A plug-and-play micro-module
    ├── CMakeLists.txt     # Local CMake target definition
    ├── glm_lite.ixx       # C++23 module interface
    └── main.cpp           # Usage examples / Integration tests
```

---

## 🚀 Quick Integration Guide

To use any module (e.g., `glm_lite`) in your codebase:

1. **Copy** the module's directory into your project.
2. Link it in your **`CMakeLists.txt`** (requires CMake 3.28+):

```cmake
cmake_minimum_required(VERSION 3.28)
project(YourApp LANGUAGES CXX)

# Include the copied module
add_subdirectory(glm_lite)

add_executable(app main.cpp)
target_link_libraries(app PRIVATE glm_lite)
```

3. **Import** it directly in your source code:
```cpp
import glm_lite;

int main() {
    glm::vec3 velocity{0.0f, 9.8f, 0.0f};
    // Ready to use!
}
```

---

## Prerequisites

* **CMake 3.30+** (Strictly required for stable C++23 Standard Library Modules support via `import std;`)
* **Compilers:** MSVC 2026+ (Windows) or GCC 15.1+ (32/64) (Linux/MinGW)

## 🛠️ Building & Testing Locally

To build the entire ecosystem and run validation tests for all modules simultaneously, ensure you have a compiler with robust C++23 module support (MSVC v143+, Clang 16+, or GCC 14+) and **Ninja**.

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
| [`WinLite`](./WinLite) | Lightweight Win32/XLib window, event loop, input, and OpenGL context. | `export module`, `import std;`, Win32 API/XLib |
| [`PixelPainter`](./PixelPainter) | Software rasterizer for primitives. | `export module`, `import std;`, SIMD-friendly |
| [`PixelCopier`](./PixelCopier) | Software rasterizer for fast pixel blitting. | `export module`, `import std;`, SIMD-friendly |
| [`GlmLite`](./GlmLite) | Ultra-lightweight vector math & linear algebra primitives. | `export module`, `import std;` |
| [`OpenGL`](./OpenGL) | Ultra-lightweight OpenGL extension loader (GLAD alternative). | `export module`, `import std;`, `GetProcAddress` |
| [`BmpLoader`](./BmpLoader) | Zero-dependency BMP image loader (24-bit and 32-bit support). | `export module`, `import std;` |
| [`TgaLoader`](./TgaLoader) | Fast TGA image loader (24-bit and 32-bit, raw & RLE support). | `export module`, `import std;` |
| [`HighResTimer`](./HighResTimer) | High-resolution performance timer / stopwatch for benchmarking. | `export module`, `import std;` |
| [`BmpSaver`](./BmpSaver) | BMP image writer and exporter supporting various color depths. | `export module`, `import std;` |

---

## 🤝 Contributing

Have a tiny C++23 utility module that you use in every project? Feel free to open a Pull Request! Please ensure your module is fully self-contained, provides a `CMakeLists.txt` with `FILE_SET CXX_MODULES`, and includes a `main.cpp` for automated testing.

## 📄 License
This project is open-source software licensed under the **Boost Software License - Version 1.0 - August 17th, 2003**. Use these modules freely in personal, educational, or commercial projects.

---

## 🖼️ Gallery & Demos

Here is the `RenderPixels` showcase running live, combining both **WinLite** (window management) and **SoftwareRender** (fixed-point canvas primitives, Bresenham lines, and clipping math) modules:

| | | |
| :---: | :---: | :---: |
| <img src="./screenshots/Screenshot_App_2026-08-23_22-30-20.840527800.jpg" width="100%" /> | <img src="./screenshots/Screenshot_App_2026-08-23_22-28-41.772413900.jpg" width="100%" /> | <img src="./screenshots/Screenshot_App_2026-08-23_22-29-56.984734100.jpg" width="100%" /> |
| <img src="./screenshots/Screenshot_App_2026-08-23_22-30-43.389195200.jpg" width="100%" /> | <img src="./screenshots/Screenshot_App_2026-08-23_22-30-01.051758300.jpg" width="100%" /> | <img src="./screenshots/Screenshot_App_2026-08-23_22-29-31.586720600.jpg" width="100%" /> |
| <img src="./screenshots/Screenshot_App_2026-08-23_22-29-13.341868300.jpg" width="100%" /> | <img src="./screenshots/Screenshot_App_2026-08-23_22-30-31.460795000.jpg" width="100%" /> | <img src="./screenshots/Screenshot_App_2026-08-23_22-29-53.556601400.jpg" width="100%" /> |
| <img src="./screenshots/Screenshot_App_2026-08-23_22-29-45.236693900.jpg" width="100%" /> | <img src="./screenshots/Screenshot_App_2026-08-23_22-28-51.884814200.jpg" width="100%" /> | <img src="./screenshots/Screenshot_App_2026-08-23_22-30-34.809726400.jpg" width="100%" /> |
| <img src="./screenshots/Screenshot_App_2026-08-23_22-28-28.941165600.jpg" width="100%" /> | <img src="./screenshots/Screenshot_App_2026-08-23_22-29-50.363840400.jpg" width="100%" /> | <img src="./screenshots/Screenshot_App_2026-08-23_22-28-34.580100600.jpg" width="100%" /> |
| <img src="./screenshots/Screenshot_App_2026-08-23_22-28-46.796540000.jpg" width="100%" /> | <img src="./screenshots/Screenshot_App_2026-08-23_22-30-38.275667200.jpg" width="100%" /> | <img src="./screenshots/Screenshot_App_2026-08-23_22-30-49.236747700.jpg" width="100%" /> |


---