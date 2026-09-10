# ⏱️ FpsCounter Micro-Module

A lightweight, high-reliability frame rate counter built natively with **C++23 Modules**. It measures real-time performance metrics (FPS) using a non-drifting monotonic clock sequence, ideal for game loops, software engines, and rendering profiling.

## 🎯 Key Features

* **Non-Drifting Precision:** Uses steady clock accumulation (`_lastTime += elapsed`) instead of simple overrides, preventing interval drift over long execution periods.
* **Zero Boilerplate:** No external dependencies, operating entirely via modern standard library time primitives (`import std;`).
* **Aerospace Warning Compliant:** Passes strict static diagnostics including member initialization audits (`-Weffc++`) and explicit discarding checks (`[[nodiscard]]`).

---

## 🚀 Quick Start

### 1. Integration (CMake 3.30+)
Include this folder in your build setup:
```cmake
add_subdirectory(FpsCounter)
target_link_libraries(YourApp PRIVATE FpsCounter)
```

### 2. Usage Inside a Render Loop
```cpp
import FpsCounter;
import std;

int main() {
    FpsCounter counter;

    while (/* window is active */) {
        // ... perform your application or software rendering tasks ...

        // Update the counter once per frame
        if (counter.Update()) {
            std::println("Performance: {} FPS", counter.GetFps());
        }
    }
}
```

---

## 🛠️ API Overview

### Methods
* `FpsCounter()` — Initializes the internal point of reference to the current monotonic system tick.
* `Update()` — Increments internal tick accumulation and evaluates window segments. Returns `true` exactly once every 1000 milliseconds when the calculation window shifts.
* `GetFps()` — Thread-safe read access returning the calculated frames per second from the last completed time bracket.
