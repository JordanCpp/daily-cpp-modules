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
| [`glm_lite`](./glm_lite) | Ultra-lightweight vector math & linear algebra primitives. | `export module`, `import std;` |

---

## 🤝 Contributing

Have a tiny C++23 utility module that you use in every project? Feel free to open a Pull Request! Please ensure your module is fully self-contained, provides a `CMakeLists.txt` with `FILE_SET CXX_MODULES`, and includes a `main.cpp` for automated testing.

## 📄 License
This project is open-source software licensed under the **Boost Software License - Version 1.0 - August 17th, 2003**. Use these modules freely in personal, educational, or commercial projects.
