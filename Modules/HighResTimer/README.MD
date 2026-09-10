# ⏱️ HighResTimer Micro-Module

A high-precision, zero-overhead performance stopwatch and metrics tracker built natively with **C++23 Modules**. It wraps standard monotonic chrono sub-systems (`std::chrono::high_resolution_clock`) to provide microsecond and nanosecond timing intervals without structural overhead.

## 🎯 Key Features

* **Dynamic Run-State Sampling:** Allows fetching precise elapsed intervals on the fly *while the clock is running* without needing to explicitly call `Stop()`.
* **Sub-Millisecond Accuracy:** Perfect for benchmarking rendering passes, evaluating software rasterizer pipeline constraints, and tracking hardware timing loops.
* **Aerospace Static Analysis Safe:** Explicitly isolates type-narrowing vulnerabilities using modern casting barriers and passes strict member initialization audits (`-Weffc++`).
* **Zero Boilerplate:** Pure drop-in component operating without platform-specific header pollution (`<windows.h>`, `<sys/time.h>`). Driven entirely by `import std;`.

---

## 🚀 Quick Start

### 1. Integration (CMake 3.30+)
Add this folder to your target CMake project:
```cmake
add_subdirectory(HighResTimer)
target_link_libraries(YourApp PRIVATE HighResTimer)
```

### 2. High-Precision Benchmarking Example
```cpp
import HighResTimer;
import std;

int main() {
    Time::HighResTimer stopwatch;

    // 1. Start tracking an execution frame
    stopwatch.Start();

    // ... run complex logic, software rendering, or file parsing ...
    for (int i = 0; i < 1'000'000; ++i) {
        // Sample execution mid-flight without stopping the timer
        if (i == 500'000) {
            std::println("Halfway checkpoint reached at: {} ms", stopwatch.ElapsedSeconds() * 1000.0);
        }
    }

    // 2. Lock the end timeline
    stopwatch.Stop();

    // 3. Extract diverse precision metrics
    std::println("Task complete. Execution profile:");
    std::println("-> Seconds:      {:.6f} s", stopwatch.ElapsedSeconds());
    std::println("-> Microseconds: {} μs", stopwatch.ElapsedMicroseconds());
    std::println("-> Nanoseconds:  {} ns", stopwatch.ElapsedNanoseconds());
}
```

---

## 🛠️ API & Core Interface

All definitions live inside the `Time::` namespace.

### Member Methods

| Signature | Description |
|:---|:---|
| `Start()` | Captures the current CPU performance counter tick and marks the timer as active. |
| `Stop()` | Captures the terminal CPU tick boundary and stops active clock sampling. |
| `Reset()` | Flags the internal execution status as stopped without clearing history points. |
| `IsRunning()` | Returns the active sampling status flag (`true` or `false`). |
| `ElapsedSeconds()` | Returns the elapsed timeframe as a high-precision `double` floating-point value. |
| `ElapsedMicroseconds()` | Returns the elapsed timeframe cast directly to a 64-bit unsigned integer (`std::uint64_t`). |
| `ElapsedNanoseconds()` | Returns the maximum available system clock precision interval cast to `std::uint64_t`. |

---

## ⚠️ Requirements & Implementation Notes

1. **Monotonic Guarantee:** Internal layouts rely on `std::chrono::high_resolution_clock`, which maps to stable hardware instructions (`RDTSC` on x86/x64 or virtual counters on ARM), preventing values from drifting or turning negative if system time changes.
2. **Discard Verification:** Metric resolution properties use the `[[nodiscard]]` modifier attribute to flag unassigned scope evaluations during compiler static diagnostic evaluations.
