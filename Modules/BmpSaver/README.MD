# 💾 BmpSaver Micro-Module

A lightweight, robust 24-bit and 32-bit BMP image exporter built natively with **C++23 Modules**. It utilizes monadic error handling (`std::expected<void, Error>`), making it an exception-free, predictable, and zero-overhead solution for screenshot capture, procedural texture generation, and canvas dumping.

## 🎯 Key Features

* **Monadic Execution Flow:** Returns a type-safe `std::expected` object, enforcing explicit error handling for IO and boundary state failures.
* **Format-Agnostic Input:** Accepts flat memory views (`std::span`) of both 24-bit (RGB) and 32-bit (RGBA) source configurations.
* **Flexible Target Depth:** Supports exporting directly to compact **24-bit RGB** (default) or pixel-aligned **32-bit RGBA** formats via a single boolean toggle.
* **Safe Header Serialization:** Assembles the physical bitmap headers byte-by-byte into a fixed stack array using secure memory coping. This approach completely bypasses struct-padding bugs and architecture alignment violations.
* **Zero Overhead & Pure C++:** Completely self-contained drops. No dependency on bulky third-party image frameworks. Powered entirely by `import std;`.

---

## 🚀 Quick Start

### 1. Integration (CMake 3.30+)
Add this directory to your build target hierarchy:
```cmake
add_subdirectory(BmpSaver)
target_link_libraries(YourApp PRIVATE BmpSaver)
```

### 2. Exporting a Screenshot or Buffer
```cpp
import BmpSaver;
import std;

int main() {
    constexpr std::uint32_t width = 800;
    constexpr std::uint32_t height = 600;
    constexpr std::uint8_t bpp = 4; // RGBA source buffer

    // Allocate mockup canvas pixels (e.g., from Software::PixelPainter)
    std::vector<std::uint8_t> frameBuffer(width * height * bpp, 255); 

    // Save out the screen buffer as a 24-bit BMP image file
    auto result = BmpSaver::Save(
        "outputs/screenshot.bmp",
        width, height, bpp,
        frameBuffer,
        false // Do not enforce 32-bit channel save layout (saves storage space)
    );

    if (!result.has_value()) {
        switch (result.error()) {
            case BmpSaver::Error::InvalidArguments: std::println(std::cerr, "Error: Malformed dimension parameters."); break;
            case BmpSaver::Error::EmptyData:        std::println(std::cerr, "Error: Source pixel span size mismatch."); break;
            case BmpSaver::Error::CannotOpenFile:   std::println(std::cerr, "Error: Failed to create or open file descriptor."); break;
            case BmpSaver::Error::WriteError:       std::println(std::cerr, "Error: Encountered standard IO stream write fault."); break;
        }
        return -1;
    }

    std::println("Canvas successfully serialized to disk!");
}
```

---

## 🛠️ API & Enumerations

### Core Function Signature
```cpp
[[nodiscard]] std::expected<void, Error> Save(
    const std::filesystem::path& path,
    std::uint32_t width,
    std::uint32_t height,
    std::uint8_t bpp,
    std::span<const std::uint8_t> pixels,
    bool save_as_32bit = false) noexcept;
```

### Monadic Error Enums
* `Error::InvalidArguments` — Triggered on null dimension boundaries or invalid BPP configurations.
* `Error::EmptyData` — Fired if the supplied pixel container span size is smaller than the calculated image byte footprint.
* `Error::CannotOpenFile` — Destination path cannot be initialized on disk.
* `Error::WriteError` — Standard physical storage write transaction failure.

---

## ⚠️ Requirements & Implementation Details

1. **Automatic Padding Correction:** The layout pipeline dynamically calculates and appends structural row padding bytes up to 4-byte aligned boundaries (`row_stride`), guaranteeing valid system file signatures.
2. **Channel Flip Handling:** BMP specifications natively dictate a standard bottom-up scanline structure. The internal serializer automatically reverses row indices on the fly during IO execution loops without mutating your active source memory spans.
