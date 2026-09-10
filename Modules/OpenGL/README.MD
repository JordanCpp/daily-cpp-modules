# 🎮 OpenGL Micro-Module (OpenGLLoader)

An ultra-lightweight, zero-dependency OpenGL extension loader built natively with **C++23 Modules**. It serves as a modern, type-safe replacement for bulky third-party loaders like **GLAD** or **GLEW**, providing manual and explicit runtime function resolution for version standards from **OpenGL 1.0 up to 4.6**.

## 🎯 Key Features

* **Zero Boilerplate Generator:** No python/web generator scripts required. Just a single C++ module drop-in.
* **Modern C++ Native Interface:** Encapsulates raw function pointers beautifully behind an exported module interface (`import OpenGL;`).
* **Granular Context Control:** Instantiated dynamically via `OpenGLLoader(major, minor)` to load only what your target context demands.
* **High-Reliability Flag Compliance:** Compiles flawlessly with strict aerospace diagnostics flags (`-Werror`, `-Wold-style-cast`, `-Wzero-as-null-pointer-constant`).

---

## 🚀 Quick Start

### 1. Integration (CMake 3.30+)
Add this directory to your target hierarchy and link against it:
```cmake
add_subdirectory(OpenGL)
target_link_libraries(YourApp PRIVATE OpenGL)
```

### 2. Basic Initialization Example
The loader relies on an existing, active OpenGL context on the calling thread (e.g., created beforehand via `WinLite`).

```cpp
import OpenGL;
import std;

int main() {
    // 1. [Prerequisite] Create Window & Active RC via WinLite or OS API...
    // e.g., SetPixelFormat, wglCreateContext, wglMakeCurrent

    try {
        // 2. Instantiate loader and request OpenGL 4.6 Core functions
        OpenGLLoader gl(4, 6);

        // 3. The functions are resolved and ready for your loop
        gl::glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        
        while (/* window is open */) {
            gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
            
            // Draw your geometry here...
            
            // Swap Buffers...
        }
    } 
    catch (const std::exception& e) {
        std::println(std::cerr, "Failed to initialize OpenGL: {}", e.what());
        return -1;
    }
}
```

---

## 🛠️ API & Version Management

### Class Signature
```cpp
class OpenGLLoader {
public:
    // Resolves and maps API entry points up to the requested specifications
    OpenGLLoader(int major, int minor);
};
```

### Scope Architecture
All modern and legacy OpenGL macros, constants, and function calls are exported inside a dedicated namespace or matching module bindings (e.g., `gl::GL_TRUE`, `gl::glGenBuffers`, `gl::glCompileShader`), keeping global workspace scopes absolutely pollution-free.

---

## ⚠️ Requirements & Platform Notes

1. **Active Context Rule:** You *must* bind the OS-specific graphic context (`wglMakeCurrent` on Windows / `glXMakeCurrent` on Linux) **before** invoking the `OpenGLLoader` constructor. Otherwise, dynamic symbol resolution (`GetProcAddress`) will return `nullptr`.
2. **Standard Headers:** Completely isolates internal `<windows.h>` macro pollution when resolving WGL interfaces by containing platform inclusions strictly inside the private module implementation unit.
