// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

export module OpenGL1Painter;

import std;
import OpenGL;

export namespace OpenGL1
{
    inline constexpr std::uint8_t alphaByte = 255;

    struct Color
    {
        std::uint8_t r{ 0 };
        std::uint8_t g{ 0 };
        std::uint8_t b{ 0 };
        std::uint8_t a{ alphaByte };

        constexpr Color() noexcept = default;
        constexpr Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = alphaByte) noexcept :
            r(red),
            g(green),
            b(blue),
            a(alpha)
        {
        }
    };

    enum class TextureFormat
    {
        RGB,
        RGBA
    };

    class Texture
    {
    private:
        std::uint32_t _id{ 0 };
        std::size_t   _width{ 0 };
        std::size_t   _height{ 0 };
        TextureFormat _format{ TextureFormat::RGB };

    public:
        Texture() = default;

        Texture(std::size_t w, std::size_t h, TextureFormat format, std::span<const std::uint8_t> data) : 
            _width(w), _height(h), _format(format)
        {
            glGenTextures(1, &_id);
            glBindTexture(GL_TEXTURE_2D, _id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            GLenum glFormat = (_format == TextureFormat::RGBA) ? GL_RGBA : GL_RGB;

            glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(glFormat), static_cast<GLsizei>(w), static_cast<GLsizei>(h), 0, glFormat, GL_UNSIGNED_BYTE, data.data());

            glBindTexture(GL_TEXTURE_2D, 0);
        }

        ~Texture()
        {
            if (_id != 0)
            {
                glDeleteTextures(1, &_id);
            }
        }

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        Texture(Texture&& other) noexcept : 
            _id(other._id), 
            _width(other._width), 
            _height(other._height), 
            _format(other._format)
        {
            other._id = 0;
        }

        Texture& operator=(Texture&& other) noexcept
        {
            if (this != &other)
            {
                if (_id != 0)
                {
                    glDeleteTextures(1, &_id);
                }
                
                _id       = other._id;
                _width    = other._width;
                _height   = other._height;
                _format   = other._format;
                other._id = 0;
            }

            return *this;
        }

        [[nodiscard]] std::uint32_t GetId() const noexcept { return _id; }
        [[nodiscard]] std::size_t GetWidth() const noexcept { return _width; }
        [[nodiscard]] std::size_t GetHeight() const noexcept { return _height; }
    };

    class Painter
    {
    public:
        Painter(std::size_t width, std::size_t height) :
            _width(width),
            _height(height)
        {
            Resize(_width, _height);
        }

        void Resize(std::size_t width, std::size_t height) noexcept
        {
            glViewport(0, 0, width, height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            glOrtho(0, width, height, 0, -1, 1);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }

        void SetColor(Color color) noexcept
        {
            _color = color;
            glColor4ub(_color.r, _color.g, _color.b, _color.a);
        }

        void Clear() noexcept
        {
            glClearColor(_color.r / 255.0f, _color.g / 255.0f, _color.b / 255.0f, _color.a / 255.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void RectFill(int x, int y, int width, int height) noexcept
        {
            glBegin(GL_QUADS);
            {
                glVertex2i(x, y);
                glVertex2i(x + width, y);
                glVertex2i(x + width, y + height);
                glVertex2i(x, y + height);
            }
            glEnd();
        }

        void RectOutline(int x, int y, int width, int height) noexcept
        {
            glBegin(GL_LINE_LOOP);
            {
                glVertex2i(x, y);
                glVertex2i(x + width, y);
                glVertex2i(x + width, y + height);
                glVertex2i(x, y + height);
            }
            glEnd();
        }

        void Line(int x0, int y0, int x1, int y1) noexcept
        {
            glBegin(GL_LINES);
            {
                glVertex2i(x0, y0);
                glVertex2i(x1, y1);
            }
            glEnd();
        }

        void Draw(const Texture& texture, int x, int y, int width, int height) noexcept
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture.GetId());

            glColor4f(_color.r, _color.g, _color.b, _color.a);

            glBegin(GL_QUADS);
            {
                glTexCoord2f(0.0f, 0.0f); glVertex2i(x, y);
                glTexCoord2f(1.0f, 0.0f); glVertex2i(x + width, y);
                glTexCoord2f(1.0f, 1.0f); glVertex2i(x + width, y + height);
                glTexCoord2f(0.0f, 1.0f); glVertex2i(x, y + height);
            }
            glEnd();

            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
        }
    private:
        Color       _color;
        std::size_t _width;
        std::size_t _height;
    };
}
