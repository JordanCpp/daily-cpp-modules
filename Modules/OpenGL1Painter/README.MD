# 🎨 OpenGL1Painter Micro-Module

A high-performance, lightweight 2D graphics abstraction layer built on top of the **OpenGL 1.2** fixed-function pipeline, engineered natively with **C++20/C++23 Modules**. This module encapsulates low-level graphics state-machine operations into a safe, object-oriented (RAII) interface, completely eliminating raw memory allocations during runtime and reducing redundant state updates.

## 🎯 Key Features

* **Zero-Allocation Layout:** Texture binding operates directly on any pre-existing contiguous memory buffer using `std::span<const std::uint8_t>`, preventing internal memory duplication or unexpected heap allocations.
* **Native C++ Modules Support:** Features full isolation via `export module` with zero old-school `#include` overhead. This guarantees lightning-fast compilation times and eliminates header-level macro pollution from legacy OpenGL headers.
* **Graphics State Optimization:** Color updates (`SetColor`) are piped atomically through `glColor4ub`. Primitives (`RectFill`, `Line`) safely leverage this persistent state instead of generating redundant, heavy pipeline color-binding instructions before every single draw call.
* **Robust Resource Management (RAII):** The `Texture` class strictly encapsulates GPU texture memory lifetime (`glDeleteTextures`) using clean, move-only type semantics.

---

## 🚀 Quick Start

### 1. Integration (CMake 3.28+)
Add the module directory to your root build tree and link your application target against it:
```cmake
add_subdirectory(Modules/OpenGL1Painter)
target_link_libraries(YourApp PRIVATE OpenGL1Painter)
```

### 2. Complete Rendering Setup
Here is a comprehensive setup showcasing how to initialize the windowing context, upload raw image data to the GPU via `std::span`, and handle a basic game-loop sequence using `OpenGL1Painter`:

```cpp
import OpenGL1Painter;
import WinLite;
import OpenGL;
import std;

constexpr std::size_t width  = 1024;
constexpr std::size_t height = 768;

using namespace WinLite;
using namespace OpenGL1;

int main()
{
    // 1. Initialize safe window and graphics context
    auto windowResult = OpenGL1Window::Create(width, height, "OpenGL1Painter - Demo");
    if (!windowResult)
    {
        std::println("Error: {}", windowResult.error());
        return -1;
    }

    auto window = std::move(*windowResult);
    OpenGLLoader loader(1, 2);

    // 2. Instantiate the Painter (automatically configures glViewport & glOrtho)
    Painter painter(width, height);

    // 3. Populate texture asynchronously using std::span
    std::vector<std::uint8_t> rawPixelData = { 
        255, 0, 0, 255,   0, 255, 0, 255,
        0, 0, 255, 255,   255, 255, 0, 255 
    }; // Small 2x2 RGBA checkerboard texture
    
    Texture texture(2, 2, TextureFormat::RGBA, rawPixelData);

    // --- Main Game Loop ---
    while (window.IsRunning())
    {
        Event event;
        while (window.GetEvent(event))
        {
            if ((event.Type == EventType::Quit) || event.IsKeyPressed(Key::Escape))
            {
                window.StopEvent();
            }
        }

        // Clear display with a Slate Gray background color
        painter.SetColor(Color{ 30, 30, 40, 255 });
        painter.Clear();

        // Render a solid rectangle (Bright Orange)
        painter.SetColor(Color{ 230, 90, 40, 255 });
        painter.RectFill(100, 150, 200, 100);

        // Render an outline border (White)
        painter.SetColor(Color{ 255, 255, 255, 255 });
        painter.RectOutline(100, 150, 200, 100);

        // Render a sharp geometric line
        painter.Line(0, 0, 1024, 768);

        // Draw texture (modulated by the currently active white color state)
        painter.Draw(texture, 400, 300, 64, 64);

        window.Present();
    }

    return 0;
}
```

---

## 🛠️ API & Core Primitives

All active classes and types reside safely inside the `OpenGL1::` namespace block.

### Exposed Types & Flags
* `OpenGL1::Color` — A pristine, aggregate `constexpr` struct representing standalone `r, g, b, a` values (`std::uint8_t`).
* `OpenGL1::TextureFormat` — Explicit scoped enumeration flagging valid pixel array storage variants (`RGB`, `RGBA`).

### Primary Member Methods (`Painter`)

| Method Signature | Core Behavioral Description |
|:---|:---|
| `Resize(width, height)` | Updates the active window scissor viewport (`glViewport`) and recalculates the internal `glOrtho` modern matrix transform projection bounds on window scale changes. |
| `SetColor(Color)` | Atomic caching structure updating the hardware state-machine context exactly once via `glColor4ub`. |
| `Clear()` | Fills the viewport buffer using the active color (safely applies `255.0f` scale conversions to feed `glClearColor`). |
| `Line(x0, y0, x1, y1)` | Draws a thin, hardware-rasterized connection path between two separate coordinate points. |
| `RectFill(x, y, w, h)` | Submits structured geometry layout to render a solid filled quad block (`GL_QUADS`). |
| `RectOutline(x, y, w, h)` | Triggers a loop pass generating sharp, wireframe hollow rectangles (`GL_LINE_LOOP`). |
| `Draw(texture, x, y, w, h)` | Safely shifts pipeline state to `GL_TEXTURE_2D`, binds the unique texture id, pushes custom texture vertex maps (`glTexCoord2f`), and clean-restores pipeline state flags automatically. |

---

## ⚠️ Requirements & Implementation Notes

1. **External Context Dependency:** This module explicitly assumes that a rendering context has been bound to the running application thread *before* any `Painter` or `Texture` operations occur. Context management must be handled upstream (e.g., via `WinLite::OpenGL1Window` and `OpenGLLoader`).
2. **Diagnostic Compliance:** The underlying code structure has been audited to pass strict compiler flags such as `-Wsign-conversion`, `-Wconversion`, and `-Wshadow` cleanly. All numerical standard type casts to native API variants (`GLint`, `GLsizei`, `GLenum`) are explicitly evaluated during compilation.
3. **Legacy Framework Stability:** Target pipeline architecture relies exclusively on core backward-compatible fixed-function routines, removing the overhead of mandatory custom shader compiling routines for classic retro-engines, tools, or lightweight user interfaces.
