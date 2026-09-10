# 🪟 WinLite Sub-System

A lightweight, zero-boilerplate, and cross-platform window management and input handling sub-system built natively using **C++23 Modules**. It serves as an ultra-fast, modern replacement for **GLFW**, **SDL**, or **SFML**, abstracting platform-specific APIs behind a unified, zero-overhead compile-time modular interface.

### 🐧 Fully Supported Platforms:
* **Windows** — Native Win32 / WinNT API & WGL context creation.
* **Linux** — Pure X11 / Xlib protocol & GLX context mapping (No heavy desktop environment toolkits required).

## 🎯 Key Features

* **Native OS Specialization:** Automatically switches at compile time between high-performance WinNT native handles and POSIX XLib sockets via advanced CMake architecture orchestration.
* **Three Flexible Rendering Modes:** 
  1. `SoftwareWindow` — Deeply integrated with Windows GDI (`SetDIBitsToDevice`) and Linux XImage buffers for direct pixel-array software blitting (optimized top-down row memory mapping via negative heights).
  2. `OpenGL1Window` — Instantiates a hardware-accelerated legacy compatibility immediate rendering context.
  3. `OpenGL3Window` — Utilizes double-buffered modern dummy tracking procedures to safely initialize an independent, modern **OpenGL 3.3+ Core Profile** graphics pipeline under both WGL and GLX platforms.
* **Type-Safe Object-Oriented Events:** Encapsulates system queues inside a secure memory-aligned `union` variant layer, supporting zero-allocation event querying.
* **Zero Macro Pollution:** Completely encapsulates dangerous global macro definitions (`NOMINMAX`, `WIN32_LEAN_AND_MEAN`, structural windows/X11 symbols) within private module partitions, keeping your client application context absolutely clean.

---

## 🚀 Quick Start

### 1. Integration (CMake 3.30+)
Add the window sub-system target to your parent build hierarchy. The library automatically links against platform dependencies (`opengl32` on Windows, `GL X11` on Linux):
```cmake
add_subdirectory(WinLite)
target_link_libraries(YourApp PRIVATE WinLite)
```

### 2. High-Performance Software Rendering Loop
Perfect for integration alongside your `Software::PixelPainter` and `Software::PixelCopier` engines:

```cpp
import WinLite;
import std;

int main() {
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;
    
    // Create a software frame buffer window
    auto winResult = WinLite::SoftwareWindow::Create(width, height, "Modern C++23 Software Engine");
    if (!winResult.has_value()) {
        std::println(std::cerr, "Failed to instantiate window: {}", winResult.error());
        return -1;
    }
    
    auto window = std::move(*winResult);
    std::vector<std::uint8_t> backBuffer(width * height * 4, 0); // Raw RGBA memory array

    WinLite::Event event{};
    while (window.IsRunning()) {
        // 1. Process IO event queue
        while (window.GetEvent(event)) {
            if (event.Type == WinLite::EventType::Quit) {
                window.StopEvent();
            }
            if (event.IsKeyPressed(WinLite::Key::Escape)) {
                window.StopEvent();
            }
        }

        // 2. [Procedural rendering happens here - e.g., mutate backBuffer bytes] ...

        // 3. Fast GDI/X11 memory blit onto screen (Top-Down array optimization)
        window.Present(backBuffer.data(), 4, width, height);
    }
}
```

### 3. Modern OpenGL 3.3+ Core Profile Setup
Perfect for uploading graphics structures initialized via your custom `OpenGLLoader` module:

```cpp
import WinLite;
import OpenGL; // Your custom C++23 extension loader
import std;

int main() {
    // Instantiates modern window bounds and loads custom driver extensions
    auto winResult = WinLite::OpenGL3Window::Create(800, 600, "Core Profile Window", 4.6f, 0.0f);
    if (!winResult.has_value()) return -1;

    auto window = std::move(*winResult);

    // Initialize your C++23 OpenGLLoader extension matrix
    OpenGLLoader gl(4, 6);

    WinLite::Event event{};
    while (window.IsRunning()) {
        while (window.GetEvent(event)) {
            if (event.Type == WinLite::EventType::Quit) window.StopEvent();
        }

        gl::glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        gl::glClear(gl::GL_COLOR_BUFFER_BIT);

        // Swap buffers using underlying WGL / GLX platform routines
        window.Present();
    }
}
```

---

## 🛠️ Input & Event Messaging Matrix

All system events pass within a single robust polymorphic structure `WinLite::Event`, matching internal tracking fields below:

### Event Types (`WinLite::EventType`)
* `EventType::Quit` — Fires when closing window decorations.
* `EventType::Keyboard` — Emits structural updates on key transactions (`ButtonState::Pressed` / `Released`).
* `EventType::MouseMove` / `EventType::MouseClick` / `EventType::MouseScroll` — High-precision cursor tracing interfaces.
* `EventType::Resize` — Notifies active grid alteration properties.

### Key Mapping Evaluation Helpers
Instead of manually processing raw union records, use highly efficient inline evaluation predicates:
* `event.IsKeyPressed(WinLite::Key::Space)`
* `event.IsKeyReleased(WinLite::Key::W)`
* `event.IsMousePressed(WinLite::MouseButton::Left)`

---

## ⚠️ Requirements & Platform Specifications

1. **Move-Only RAII Semantics:** Window targets explicitly disable copy constructors and assignment operators. Resource handles (`HWND`, `HDC`, `HGLRC`, X-Displays) are deterministic, preventing resource leaks.
2. **Platform Separation Build Scheme:**
```text
WinLite/
├── CMakeLists.txt                 # Multi-platform static target coordinator
├── WinLite.ixx                    # Core module umbrella interface
├── WinLite.Events.ixx             # Common type-safe input event structures
├── WinLite.KeyEnums.ixx           # Unified hardware keyboard cross-mappings
├── WinLite.KeyMapper.ixx          # Internal dictionary mapping virtual keys
├── WinLite.Queue.ixx              # Internal event ring-buffer sequence
├── WinLite.MainWindow.WinNt.ixx   # Private Win32 OS-specific loop architecture
└── WinLite.MainWindow.XLib.ixx    # Private Linux X11 display loop architecture
```
