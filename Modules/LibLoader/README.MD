# 🧰 LibLoader Micro-Module

A high-performance, exception-free cross-platform dynamic link library (`.dll` / `.so`) automation engine built natively with **C++23 Modules**. It wraps native platform subsystems (`Win32 LoadLibraryA` / `POSIX dlopen`) inside a clean, modern RAII container. Powered by monadic error handling (`std::expected`), it guarantees compile-time type-safety and absolute isolation from global macro pollution.

## 🎯 Key Features

* **Monadic Error Handling:** Returns type-safe `std::expected<void, std::string>` and `std::expected<T, std::string>` containers to propagate descriptive error payloads without exception-unwinding overhead.
* **Strict Compile-Time Validation:** Utilizes modern C++ constraints (`requires`) to block invalid function pointer casting attempts and audit signatures before extraction.
* **Linkage Conflict Protection:** Specifically optimized for modern compilers (like GCC 15/16 MinGW layouts). Includes `<bits/c++config.h>` within the global module fragment (`module;`) to preemptively stabilize `extern "C"` language linkage bugs.
* **Macro Poisoning Isolation:** Keeps heavy OS header dependencies (`<windows.h>`, `<dlfcn.h>`) encapsulated strictly inside the module's private global fragment, keeping global scopes clean.
* **Deterministic RAII Lifecycle:** Destructors trigger automatic platform-specific memory release (`FreeLibrary` / `dlclose`), ensuring zero resource leaks during runtime hot-reloading or shutdowns.
* **Modern Type-Safe Bit Manipulation:** Replaces dangerous old-style C casts with `std::bit_cast` for bit-perfect function pointer mapping, preserving compliance with strict `-Wold-style-cast` profiles.

---

## 🚀 Quick Start

### 1. Integration (CMake 3.30+)
Add this directory to your build system configuration:
```cmake
add_subdirectory(LibLoader)
target_link_libraries(YourApp PRIVATE LibLoader)
```

### 2. Dynamically Loading a Library Example
```cpp
import LibLoader;
import std;

// Define the targeted function signature
using PFN_OpenGlClear = void(*)(std::uint32_t mask);

int main() {
    LibLoader loader;

    // Attempt to mount the shared object dynamically
#ifdef _WIN32
    auto load_result = loader.Load("opengl32.dll");
#else
    auto load_result = loader.Load("libGL.so.1");
#endif

    if (!load_result.has_value()) {
        std::println(std::cerr, "Error: {}", load_result.error());
        return -1;
    }

    // Safely extract the procedure address with compile-time type checking
    auto proc_result = loader.get_proc<PFN_OpenGlClear>("glClear");
    if (!proc_result.has_value()) {
        std::println(std::cerr, "Error: {}", proc_result.error());
        return -1;
    }

    // Call the extracted function pointer securely
    PFN_OpenGlClear glClear = proc_result.value();
    glClear(0x00004000); // GL_COLOR_BUFFER_BIT

    std::println("Procedure loaded and executed successfully!");
    // 'loader' automatically calls Unload() when exiting local scope via RAII
}
```

---

## 🛠️ API & Definitions

### Class Definition & Lifecycle Interface
```cpp
export class LibLoader {
public:
    LibLoader() = default;
    ~LibLoader(); // Triggers automatic Unload()

    // Explicitly non-copyable to enforce clean asset ownership
    LibLoader(const LibLoader&) = delete;
    LibLoader& operator=(const LibLoader&) = delete;

    // Move semantics fully supported
    LibLoader(LibLoader&& other) noexcept;
    LibLoader& operator=(LibLoader&& other) noexcept;

    // Operational API
    std::expected<void, std::string> Load(const std::string& path);
    void Unload();

    // Validity checking
    explicit operator bool() const noexcept;

    // Constrained function extraction method
    template <typename T>
        requires std::is_pointer_v<T> && std::is_function_v<std::remove_pointer_t<T>>
    std::expected<T, std::string> get_proc(const char* funcName) const noexcept;
};
```

---

## ⚠️ Requirements & Implementation Notes

1. **GCC Module Fix:** The engine detects `__GNUC__` within the global module fragment to map `bits/c++config.h` before Windows runtime dependencies spin up. This bypasses the infamous `conflicting language linkage for imported declaration` error when working with `import std;`.
2. **Platform Handles:** The underlying implementation transparently abstracts OS differences using an internal conditional `LibHandle` type definition (`HMODULE` on Windows, `void*` on POSIX systems).
3. **Thread-Safety Note:** Function resolution via `get_proc` is completely `const noexcept`, enabling multiple execution threads to safely query entry points from a single globally cached library container concurrently.

---

## 📄 License
Copyright 2026-present Evgeny Zoshchuk (JordanCpp).  
Distributed under the **Boost Software License, Version 1.0**. (See accompanying file LICENSE_1_0.txt or copy at [https://www.boost.org/LICENSE_1_0.txt](https://www.boost.org/LICENSE_1_0.txt)).
