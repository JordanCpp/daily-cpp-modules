// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#ifdef __GNUC__
    #include <bits/c++config.h>
#endif

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

export module LibLoader;

import std;

#ifdef _WIN32
    using LibHandle = HMODULE;
#else
    using LibHandle = void*;
#endif

export class LibLoader
{
private:
    LibHandle _handle = nullptr;

public:
    LibLoader() = default;

    ~LibLoader()
    {
        Unload();
    }

    LibLoader(const LibLoader&) = delete;
    LibLoader& operator=(const LibLoader&) = delete;

    LibLoader(LibLoader&& other) noexcept :
        _handle(std::exchange(other._handle, nullptr))
    {
    }

    LibLoader& operator=(LibLoader&& other) noexcept
    {
        if (this != &other)
        {
            Unload();
            _handle = std::exchange(other._handle, nullptr);
        }

        return *this;
    }

    std::expected<void, std::string> Load(const std::string& path)
    {
        if (_handle)
        {
            return {};
        }

#ifdef _WIN32
        _handle = LoadLibraryA(path.c_str());
#else
        _handle = dlopen(path.c_str(), RTLD_LAZY);
#endif

        if (!_handle)
        {
            return std::unexpected(std::format("LibLoader: Failed to load: {}", path));
        }

        return {};
    }

    void Unload()
    {
        if (!_handle)
        {
            return;
        }

#ifdef _WIN32
        FreeLibrary(_handle);
#else
        dlclose(_handle);
#endif
        _handle = nullptr;
    }

    explicit operator bool() const noexcept
    {
        return _handle != nullptr;
    }

    template <typename T>
        requires std::is_pointer_v<T>&& std::is_function_v<std::remove_pointer_t<T>>
    std::expected<T, std::string> get_proc(const char* funcName) const noexcept
    {
        if (!_handle)
        {
            return std::unexpected("LibLoader: Attempted to get procedure from an uninitialized library.");
        }

#ifdef _WIN32
        auto symbol = reinterpret_cast<void*>(GetProcAddress(_handle, funcName));
#else
        auto symbol = dlsym(_handle, funcName);
#endif

        if (!symbol)
        {
            return std::unexpected(std::format("LibLoader: Failed to find symbol: {}", funcName));
        }

        return std::bit_cast<T>(symbol);
    }
};
