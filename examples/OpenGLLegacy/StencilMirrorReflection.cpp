// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

import std;
import AppGL1;
import GlmLite;
import WinLite;
import OpenGL;

using namespace WinLite;

static float cubeAngle = 0.0f;

static void setMatrix(GLenum matrixMode, const glm::mat4& matrix) noexcept
{
	glMatrixMode(matrixMode);
	glLoadMatrixf(glm::value_ptr(matrix));
}

static void drawCube() noexcept
{
	glBegin(GL_QUADS);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.3f, 0.3f, 0.3f);
	glVertex3f(0.3f, 0.3f, 0.3f);
	glVertex3f(0.3f, -0.3f, 0.3f);
	glVertex3f(-0.3f, -0.3f, 0.3f);

	glColor3f(0.0f, 0.7f, 0.0f);
	glVertex3f(-0.3f, 0.3f, -0.3f);
	glVertex3f(0.3f, 0.3f, -0.3f);
	glVertex3f(0.3f, -0.3f, -0.3f);
	glVertex3f(-0.3f, -0.3f, -0.3f);

	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex3f(-0.3f, 0.3f, -0.3f);
	glVertex3f(-0.3f, 0.3f, 0.3f);
	glVertex3f(-0.3f, -0.3f, 0.3f);
	glVertex3f(-0.3f, -0.3f, -0.3f);

	glColor3f(0.0f, 0.3f, 0.8f);
	glVertex3f(0.3f, 0.3f, -0.3f);
	glVertex3f(0.3f, 0.3f, 0.3f);
	glVertex3f(0.3f, -0.3f, 0.3f);
	glVertex3f(0.3f, -0.3f, -0.3f);

	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3f(-0.3f, 0.3f, -0.3f);
	glVertex3f(0.3f, 0.3f, -0.3f);
	glVertex3f(0.3f, 0.3f, 0.3f);
	glVertex3f(-0.3f, 0.3f, 0.3f);

	glColor3f(0.8f, 0.3f, 0.0f);
	glVertex3f(-0.3f, -0.3f, -0.3f);
	glVertex3f(0.3f, -0.3f, -0.3f);
	glVertex3f(0.3f, -0.3f, 0.3f);
	glVertex3f(-0.3f, -0.3f, 0.3f);

	glEnd();

}

static void drawFloor() noexcept
{
	glBegin(GL_QUADS);
	glVertex3f(-2.0f, 0.0f, -2.0f);
	glVertex3f(2.0f, 0.0f, -2.0f);
	glVertex3f(2.0f, 0.0f, 2.0f);
	glVertex3f(-2.0f, 0.0f, 2.0f);
	glEnd();
}

int main()
{
	constexpr std::size_t width = 1024;
	constexpr std::size_t height = 768;

	AppGL1 app;
	if (!app.Init(width, height, "OpenGL 1.2 - Z-Buffer Planar Reflection"))
	{
		return -1;
	}

	const glm::mat4 projectionMatrix = glm::perspective(
		glm::radians(60.0f),
		static_cast<float>(width) / static_cast<float>(height),
		0.1f,
		20.0f
	);

	setMatrix(GL_PROJECTION, projectionMatrix);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);

	app.OnUpdate = [&](float deltaTime) noexcept {
		cubeAngle += deltaTime * 1.0f;
		if (cubeAngle > 2.0f * std::numbers::pi_v<float>)
		{
			cubeAngle -= 2.0f * std::numbers::pi_v<float>;
		}
		};

	app.OnRender = [&]() noexcept {
		const glm::mat4 viewMatrix = glm::lookAt(
			glm::vec3(2.5f, 2.0f, 4.0f),
			glm::vec3(0.0f, 0.5f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		setMatrix(GL_MODELVIEW, viewMatrix);

		glPushMatrix();
		glScalef(1.0f, -1.0f, 1.0f);
		glTranslatef(0.0f, -0.6f, 0.0f);
		glRotatef(cubeAngle * (180.0f / std::numbers::pi_v<float>), 0.0f, 1.0f, 0.0f);

		const double clipPlane[4] = { 0.0, 1.0, 0.0, 0.0 };
		glClipPlane(GL_CLIP_PLANE0, clipPlane);
		glEnable(GL_CLIP_PLANE0);

		glFrontFace(GL_CW);
		drawCube();
		glFrontFace(GL_CCW);

		glDisable(GL_CLIP_PLANE0);
		glPopMatrix();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor4f(0.15f, 0.25f, 0.35f, 0.65f);
		drawFloor();

		glDisable(GL_BLEND);

		glPushMatrix();
		glTranslatef(0.0f, 0.6f, 0.0f);
		glRotatef(cubeAngle * (180.0f / std::numbers::pi_v<float>), 0.0f, 1.0f, 0.0f);

		drawCube();

		glPopMatrix();

		};

	app.Run();

	return 0;

}