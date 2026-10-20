# GlutLite

A modern, zero-overhead, headerless C++23 module that faithfully mirrors the classic GLUT / FreeGLUT API. It acts as an elegant adapter layer, bridging the low-level windowing/event system of `WinLite` with the OpenGL rendering context.

Designed specifically for modernizing legacy codebases, porting classic computer graphics books (like the *OpenGL SuperBible*), and learning computer graphics with lightning-fast C++ Modules compilation speeds.

## Features

- **100% Headerless:** Powered entirely by C++23 Modules (`import GlutLite;`) — no macros, no global namespace pollution, no `#include <GL/glut.h>`.
- **Classic Behavior Preservation:** Faithfully mirrors original GLUT lifecycle, including double buffering (`GLUT_DOUBLE`), viewport updates, and explicit resource handling (`std::exit(0)` on window closure).
- **Type-Safe Events:** Re-routes platform-specific events into familiar callback primitives (`glutDisplayFunc`, `glutTimerFunc`, etc.) using modern C++ safety.
- **Ultra-Lightweight:** Zero external heavy dependencies. Built seamlessly on top of `WinLite`.

## Architecture Overview

 [ Your Application (e.g., Bounce.cpp) ]
                 │
                 ▼ (Classic GLUT API)
           [ GlutLite ]
                 │
                 ▼ (Platform-Agnostic Events)
            [ WinLite ]
                 │
                 ▼
     [ Native OS Window (Win32/X11) ]

## Quick Start Example

Here is how the classic `Bounce` animation program looks using modern C++ Modules and **GlutLite**:

```cpp
// Bounce.cpp
import std;
import OpenGL;
import GlutLite;

using namespace glut;

GLfloat x = 100.0f, y = 150.0f;
GLsizei rsize = 50;
GLfloat xstep = 1.5f, ystep = 1.5f;
GLfloat windowWidth, windowHeight;

void RenderScene() noexcept {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glRectf(x, y, x + rsize, y + rsize);
    glutSwapBuffers();
}

void TimerFunction(int value) noexcept {
    if (x > windowWidth - rsize || x < 0)   xstep = -xstep;
    if (y > windowHeight - rsize || y < 0) ystep = -ystep;

    x += xstep;
    y += ystep;

    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1); // ~30 FPS
}

void ChangeSize(GLsizei w, GLsizei h) noexcept {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h) {
        windowHeight = 250.0f * h / w;
        windowWidth = 250.0f;
    } else {
        windowWidth = 250.0f * w / h;
        windowHeight = 250.0f;
    }

    glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Bounce - GlutLite Showcase");

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(33, TimerFunction, 1);

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Blue Background

    glutMainLoop();
    return 0;
}
```

## Supported GLUT Interface Subset

- **Lifecycle & Windows:** `glutInit`, `glutInitWindowSize`, `glutInitDisplayMode`, `glutCreateWindow`, `glutMainLoop`
- **Callbacks:** `glutDisplayFunc`, `glutReshapeFunc`, `glutIdleFunc`, `glutTimerFunc`
- **Input System:** `glutKeyboardFunc`, `glutKeyboardUpFunc`, `glutSpecialFunc`, `glutSpecialUpFunc`, `glutMouseFunc`, `glutMotionFunc`, `glutPassiveMotionFunc`
- **Frame Control:** `glutPostRedisplay`, `glutSwapBuffers`

## License

This project is licensed under the **Boost Software License 1.0**. Feel free to use, modify, and distribute.
