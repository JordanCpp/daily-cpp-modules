# 🖼️ TgaLoader Micro-Module

A high-performance, exception-free 24-bit and 32-bit Truevision TGA image loader built natively with **C++23 Modules**. It utilizes monadic error handling (`std::expected`), guaranteeing zero-overhead, safety, and strict predictability standard for real-time graphics applications and embedded systems.

## 🎯 Key Features

* **Monadic Error Handling:** Returns a type-safe `std::expected<Image, Error>` container, avoiding heavy C++ exception-unwinding overhead.
* **Automatic RGBA Normalization:** Converts raw 24-bit (BGR) and 32-bit (BGRA) uncompressed true-color TGA streams into a consistent, modern 32-bit RGBA pixel layout.
* **Descriptor Orientation Parsing:** Inspects the TGA image descriptor bits to dynamically handle and normalize both top-down and bottom-up vertical coordinate system layouts on the fly.
* **Exploit & Boundary Protection:** Hardened with arithmetic limits validation to eliminate potential buffer overflow vulnerabilities caused by corrupted dimensions or malformed metadata fields.
* **Zero Macro Pollution:** Powered strictly by `import std;`. The module isolates binary structures internally, leaving global project scopes clean.

---

## 🚀 Quick Start

### 1. Integration (CMake 3.30+)
Add this directory to your build system configuration:
```cmake
add_subdirectory(TgaLoader)
target_link_libraries(YourApp PRIVATE TgaLoader)
```

### 2. Loading a Texture Example
```cpp
import TgaLoader;
import std;

int main() {
    // Attempt to parse a TGA asset safely
    auto result = TgaLoader::load_from_file("assets/sprites/player.tga");

    if (!result.has_value()) {
        switch (result.error()) {
            case TgaLoader::Error::FileNotFound:    std::println(std::cerr, "Error: File target missing."); break;
            case TgaLoader::Error::InvalidFormat:   std::println(std::cerr, "Error: Unsupported TGA type (Only uncompressed true-color supported)."); break;
            case TgaLoader::Error::UnsupportedBpp:  std::println(std::cerr, "Error: Bit-depth is not 24 or 32 bits."); break;
            case TgaLoader::Error::CorruptedHeader: std::println(std::cerr, "Error: TGA file contains a truncated header."); break;
            case TgaLoader::Error::ReadError:       std::println(std::cerr, "Error: Failure during stream extraction loop."); break;
        }
        return -1;
    }

    // Move the fully validated image structure out
    TgaLoader::Image sprite = std::move(result.value());
    std::println("Loaded TGA asset successfully: {}x{} pixels.", sprite.width, sprite.height);

    // This output is ready for direct upload to your OpenGL texture array or Software::PixelCopier buffers!
}
```

---

## 🛠️ API & Definitions

### Data Structures
```cpp
struct Image {
    std::uint8_t  bpp;          // Bits-per-pixel (normalized to 4 bytes / RGBA)
    std::uint32_t width;        // Image width in pixels
    std::uint32_t height;       // Image height in pixels
    std::vector<std::uint8_t> pixels; // Flat uniform RGBA byte vector
};
```

### Monadic Error Enums
* `Error::FileNotFound` — The requested asset path could not be mapped to an active file handle.
* `Error::InvalidFormat` — The asset data type code does not equal `2` (Uncompressed True-Color image map).
* `Error::UnsupportedBpp` — The texture specifies depths other than 24-bit or 32-bit structures.
* `Error::CorruptedHeader` — The incoming file size is smaller than the formal structural specification requirements.
* `Error::ReadError` — Physical storage io interruption or premature end-of-file reached.

---

## ⚠️ Requirements & Implementation Notes

1. **ID Field Processing:** The engine evaluates `header.id_length` fields and automatically updates internal stream pointer positioning, maintaining compatibility with modern tools (Photoshop, Blender) that append custom layout records.
2. **Strict Structure Invalidation:** Custom structure padding is prevented using local boundary pack configurations (`#pragma pack(push, 1)`), enforcing secure byte-order memory alignments.
