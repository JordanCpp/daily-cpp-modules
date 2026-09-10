# 📐 GlmLite Micro-Module

An ultra-lightweight, zero-overhead vector and matrix math library built natively with **C++23 Modules**. It serves as a modern, self-contained drop-in replacement for standard **GLM**, designed specifically for graphics pipelines, software rasterizers, and custom game engines.

## 🎯 Key Features

* **Zero External Dependencies:** Only relies on `import std;`, completely isolating your workspace from global macro pollution.
* **Compile-Time Execution:** Fully `constexpr`-friendly vector and matrix structures, allowing procedural transformations to bake at compile time.
* **Strict Type Safety:** Fully compatible with aerospace-grade compilation flags (`-Wconversion`, `-Wshadow`, `-Wold-style-cast`).
* **Graphics Pipeline Ready:** Strict column-major alignment layout. Fully compatible with OpenGL/Vulkan buffers via `value_ptr`.
* **High-Reliability Branches:** Critical algorithms (like vector normalization) contain explicit zero-division guards combined with `[[unlikely]]` attributes.

---

## 🚀 Quick Start

### 1. Integration (CMake 3.30+)
Add this directory to your sub-project tree and link against it:
```cmake
add_subdirectory(glm_lite)
target_link_libraries(YourApp PRIVATE glm_lite)
```

### 2. Basic Usage Example
```cpp
import GlmLite;
import std;

int main() {
    // 1. Vector Operations
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 velocity{1.0f, 2.5f, -0.5f};
    glm::vec3 next_position = position + velocity * 2.0f;

    // 2. Linear Algebra Utilities
    float speed = glm::length(velocity);
    glm::vec3 direction = glm::normalize(velocity);

    // 3. Coordinate System Transformations
    glm::mat4 model = glm::mat4::identity();
    model = glm::translate(model, glm::vec3(0.0f, 1.5f, -3.0f));
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 mvp = projection * view * model;
}
```

---

## 🛠️ API & Mathematical Primitives

All entities reside in the `glm::` namespace.

### Data Types
* `glm::vec2`, `glm::vec3`, `glm::vec4` — Floating-point vector structures (`constexpr`).
* `glm::mat4` — 4x4 matrix representation stored as a `f32 col[4][4]` column-major sequence (`constexpr`).

### Vector Functions
* `length(v)` — Returns the geometric magnitude.
* `normalize(v)` — Safely scales a vector to unit length (returns zero-vector if original length is `0.0f`).
* `dot(a, b)` — Computes the algebraic scalar dot product.
* `cross(a, b)` — Computes the 3D vector cross product.
* `radians(deg)` — Converts degrees to floating-point radians (`constexpr`).

### Matrix Transformations
* `mat4::identity()` — Instantiates a standard `1.0f` scalar identity matrix.
* `translate(m, v)` — Multiplies a matrix by a translation matrix.
* `scale(m, v)` — Scales matrix vector axes inline.
* `rotate(m, angle, axis)` — Applies an arbitrary axis rotation via Rodrigues' rotation parameters.
* `perspective(fov, aspect, near, far)` — Generates a standard clip-space perspective projection matrix.
* `ortho(left, right, bottom, top, near, far)` — Generates an orthographic projection matrix.

### Buffer Extraction
* `value_ptr(matrix_or_vector)` — Performs a safe modern `reinterpret_cast` directly to a flat `const float*` pointer, allowing seamless uploads via `glUniformMatrix4fv` or Vulkan push constants.

---

## ⚠️ Requirements & Implementation Notes

1. **Explicit Indexation:** Loops inside matrix algebra methods strictly utilize `std::size_t` induction arguments to bypass any micro-architectural unsigned narrowings.
2. **Standard Library Overloads:** Trigonometric computations leverage native overloads from `import std;` instead of using standard legacy global `<math.h>` components.
