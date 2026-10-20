// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

import std;
import OpenGL;
import GlutLite;

using namespace glut;

void display() noexcept;
void keyboard(unsigned char key, int x, int y) noexcept;

void display() noexcept
{
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.5f, -0.5f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.0f, 0.5f);
    glEnd();
}

void keyboard(unsigned char key, int x, int y) noexcept
{
    (void)x; (void)y;

    if (key == 'q') 
    {
        std::println("Exiting via GLUT keyboard event!");
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("My Modern-Oldschool Custom GLUT");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
