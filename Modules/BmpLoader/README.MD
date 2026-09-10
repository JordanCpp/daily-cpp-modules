# 🖼️ BmpLoader Micro-Module

A lightweight, high-reliability 24-bit and 32-bit BMP image loader built natively with **C++23 Modules**. It utilizes monadic error handling (`std::expected`) instead of C++ exceptions, ensuring zero runtime overhead and strict predictability standard for mission-critical software.

## 🎯 Key Features

* **Monadic Error Design:** Returns a type-safe `std::expected<Image, Error>` container, enforcing safe handling of missing or corrupted assets.
* **Automatic RGBA Normalization:** Converts legacy uncompressed 24-bit (BGR) and 32-bit (BGRA) bitmaps directly into a uniform 32-bit RGBA pixel stream ready for GPU texture uploads or software blitting.
* **Coordinate Orientation Handling:** Automatically detects and normalizes both bottom-up (standard BMP) and top-down image orientations seamlessly.
* **Overflow & Exploit Protection:** Includes strict safety boundaries against integer overflows, negative dimensions memory exploits, and malformed header sizes.
* **Zero Boilerplate:** No external dependencies like `libbmp` or `stb_image`. Powered strictly by `import std;`.

---

## 🚀 Quick Start

### 1. Integration (CMake 3.30+)
Add this directory to your build system:
```cmake
add_subdirectory(BmpLoader)
target_link_libraries(YourApp PRIVATE BmpLoader)
```

### 2. Loading an Image Example
```cpp
import BmpLoader;
import std;

int main() {
    // Attempt to load a bitmap image safely
    auto result = BmpLoader::Load("assets/textures/hero.bmp");

    if (!result.has_value()) {
        // Evaluate clear monadic error enums
        switch (result.error()) {
            case BmpLoader::Error::FileNotFound:    std::println(std::cerr, "Error: Texture file not found!"); break;
            case BmpLoader::Error::InvalidFormat:   std::println(std::cerr, "Error: File is not a valid BMP asset."); break;
            case BmpLoader::Error::UnsupportedBpp:  std::println(std::cerr, "Error: BPP format is not 24-bit or 32-bit."); break;
            case BmpLoader::Error::CorruptedHeader: std::println(std::cerr, "Error: BMP header structure is corrupted."); break;
            case BmpLoader::Error::ReadError:       std::println(std::cerr, "Error: Stream read failure encountered."); break;
        }
        return -1;
    }

    // Move out the validated image object
    BmpLoader::Image img = std::move(result.value());
    std::println("Loaded asset: {}x{} (Total pixel bytes: {})", img.width, img.height, img.pixels.size());
    
    // Ready to be linked to your Software::PixelCopier or OpenGL texture upload loops!
}
```

---

## 🛠️ API & Core Definitions

### Data Structures
```cpp
struct Image {
    std::uint8_t  bpp;          // Bits-per-pixel (normalized to 4 bytes/RGBA)
    std::uint32_t width;        // Absolute width in pixels
    std::uint32_t height;       // Absolute height in pixels
    std::vector<std::uint8_t> pixels; // Contiguous RGBA flat array
};
```

### Monadic Error Enums
* `Error::FileNotFound`
* `Error::InvalidFormat`
* `Error::UnsupportedBpp` (Fires if the image uses compression or color depths other than 24/32 bits)
* `Error::CorruptedHeader`
* `Error::ReadError`

---

## ⚠️ Technical Specifications & Constraints

1. **Byte Boundary Alignment:** The raw loader correctly computes and strips out automatic row padding bytes up to 4-byte structural boundaries (`row_stride`).
2. **Header Packing Isolation:** Binary structures (`BmpFileHeader`, `BmpInfoHeader`) leverage local `#pragma pack(push, 1)` bounds to isolate custom struct layouts from standard system architectural padding leaks.
