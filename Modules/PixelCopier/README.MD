# 🖨️ PixelCopier Micro-Module

A high-performance, zero-allocation image blitter and texture scaling engine built natively with **C++23 Modules**. It features an ultra-fast fixed-point math rendering loop (`16.16` bit precision) for real-time software sprite scaling, sub-rectangle blitting, and texture mapping.

## 🎯 Key Features

* **Fixed-Point Scaling:** Uses zero floating-point operations for texture stretching, making it incredibly fast and deterministic.
* **Sub-Texture Blitting:** Supports advanced copying from a sub-rectangle source directly into a sub-rectangle destination with full clipping safety.
* **Format-Agnostic Blitting:** Seamlessly handles translations between combinations of **24-bit (RGB)** and **32-bit (RGBA)** memory streams on the fly.
* **No Dynamic Allocations:** Operates entirely on raw memory interfaces utilizing `std::span` views.

---

## 🚀 Quick Start

### 1. Integration (CMake 3.28+)
Add this directory to your project configuration:
```cmake
add_subdirectory(PixelCopier)
target_link_libraries(YourApp PRIVATE PixelCopier)
```

### 2. Basic Sprite Drawing Example
To copy an entire raw sprite texture (e.g., loaded from `BmpLoader` or `TgaLoader`) onto your primary framebuffer screen:

```cpp
import PixelCopier;
import std;

int main() {
    // 1. Setup screen canvas (800x600 RGBA)
    std::vector<std::uint8_t> screenBuffer(800 * 600 * 4, 0);
    Software::PixelCopier blitter(800, 600, 4, screenBuffer);

    // 2. Mock a sprite asset buffer (e.g., a 64x64 RGB character sprite)
    std::vector<std::uint8_t> spriteBuffer(64 * 64 * 3, 255); // Solid white sprite

    // 3. Fast blit whole sprite onto screen coordinates (X: 120, Y: 80)
    blitter.Copy(
        120, 80,                 // Target Destination Top-Left Coordinates
        64, 64, 3,               // Source Texture Metrics (Width, Height, BPP)
        spriteBuffer             // Source Data View
    );
}
```

### 3. Advanced Sprite Stretching & Sub-Rect Cropping
To select an individual sprite frame from a large texture atlas and scale it dynamically to a custom size on the screen:

```cpp
// Crop a 32x32 animation frame from an atlas at offset (X: 0, Y: 32)
// and stretch it to a 128x128 bounding box on the screen
blitter.Copy(
    200, 200,                 // Destination X, Y position
    128, 128,                 // Destination Target Size (Scale up to 128x128!)
    atlasBuffer,              // Source Texture Atlas data
    512, 512, 4,              // Source Atlas Metrics (512x512 RGBA)
    0, 32,                    // Source Sub-Rectangle Offset (srcX, srcY)
    32, 32                    // Source Sub-Rectangle Dimensions (srcSubW, srcSubH)
);
```

---

## 🛠️ API & Core Interface

All functions live inside the `Software::` namespace.

### Overloaded Methods

| Signature | Description |
|:---|:---|
| `Copy(screenX, screenY, bufferW, bufferH, bufferBpp, bufferSource)` | **Standard Blit:** Copies the entire source asset into the specified screen location matching its 1:1 pixel scale. |
| `Copy(screenX, screenY, screenW, screenH, bufferSource, bufferW, bufferH, bufferBpp, srcX, srcY, srcSubW, srcSubH)` | **Advanced Stretch Blit:** Samples a selected sub-region from the source texture atlas and scales it into the chosen target window. |

---

## ⚠️ Requirements & Technical Specifications

1. **Memory Buffers Validation:** The class constructor forces runtime bounds checking against incoming container spans (`ValidateBounds`). It guarantees no out-of-bounds pointer invalidations if metrics violate dimensions.
2. **Channel Mapping Continuity:** Natively maps cross-platform desktop bit arrays (`idxR`, `idxG`, `idxB`, `idxA`) matching standard structural platform window formats seamlessly.
