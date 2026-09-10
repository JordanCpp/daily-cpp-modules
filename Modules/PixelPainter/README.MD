# 🎨 PixelPainter Micro-Module

A high-performance, zero-allocation 2D software rasterizer built natively with **C++23 Modules**. It operates directly on raw memory overlays using `std::span`, making it ideal for custom engines, retro games, UI rendering, or frame-buffer operations.

## 🎯 Key Features

* **Zero-Allocation Layout:** Does not manage graphics memory itself. It binds to any existing array, buffer, or vector via `std::span<std::uint8_t>`.
* **Compile-Time Execution:** Fully `constexpr`-friendly primitives. You can bake procedurally generated textures or icons directly at compile time.
* **Format Agnostic:** Natively supports both **RGB (24-bit)** and **RGBA (32-bit)** contiguous pixel layouts.
* **Robust Clipping & Safety:** All primitive drawing operations feature hardware-like bound checks and utilize branch prediction attributes (`[[unlikely]]`, `[[likely]]`).

---

## 🚀 Quick Start

### 1. Integration (CMake 3.28+)
Add this directory to your sub-project tree and link against it:
```cmake
add_subdirectory(PixelPainter)
target_link_libraries(YourApp PRIVATE PixelPainter)
```

### 2. Basic Rendering Example
Here is how you can initialize a stack-allocated or heap-allocated canvas and draw primitives:

```cpp
import PixelPainter;
import std;

int main() {
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;
    constexpr std::size_t bytesPerPixel = 4; // RGBA
    
    // Allocate pixel buffer
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel, 0);

    // Bind PixelPainter to the buffer view
    Software::PixelPainter painter(width, height, bytesPerPixel, frameBuffer);

    // 1. Clear screen with a background color
    painter.SetColor(Software::Color(30, 30, 40)); // Dark gray slate
    painter.Clear();

    // 2. Draw a filled rectangle (e.g., UI element or platform)
    painter.SetColor(Software::Color(230, 90, 40)); // Orange
    painter.Fill(100, 150, 200, 100);

    // 3. Draw high-performance lines (Bresenham's algorithm)
    painter.SetColor(Software::Color(0, 255, 120)); // Neon green
    painter.Line(0, 0, 799, 599);

    // 4. Draw a pixel-perfect circle
    painter.SetColor(Software::Color(255, 220, 0)); // Yellow
    painter.Circle(400, 300, 50);
}
```

---

## 🛠️ API & Core Primitives

All functions live inside the `Software::` namespace.

### Types & Flags
* `Software::Color` — Simple aggregate struct representing `r, g, b, a` values (`constexpr`).
* Supports automatic fast paths during `Clear()` if the assigned color contains uniform grayscale components (utilizes optimized `std::fill`).

### Methods

| Signature | Description |
|:---|:---|
| `Clear()` | Fills the entire linked buffer with the current active color. |
| `Pixel(x, y)` | Draws a single isolated pixel with coordinate range validation. |
| `Line(x0, y0, x1, y1)` | Draws a pixel-perfect line using an optimized Bresenham loop. |
| `Fill(x, y, w, h)` | Fills a rectangular area with safe canvas boundary clipping. |
| `Circle(xc, yc, radius)` | Rasterizes a clean circle border using the Midpoint Circle algorithm. |

---

## ⚠️ Requirements & Implementation Notes

1. **Compiler Diagnostics Compatibility:** Built from scratch to pass rigorous aerospace static analysis guidelines without emitting conversions or structural shadowing alerts.
2. **Channel Ordering:** Defaults to standard sequential channel configuration arrays. Easily compatible with desktop platform windowing pipelines (Win32 GDI bitmaps / Linux X11 Shm).
