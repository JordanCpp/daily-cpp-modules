// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

export module SDL1.Loader;

import std;
import SDL1.API;
import LibLoader;

export class SDL1Loader 
{
public:
    SDL1Loader() = default;

    ~SDL1Loader()
    {
        Unload();
    }

    SDL1Loader(const SDL1Loader&) = delete;
    SDL1Loader& operator=(const SDL1Loader&) = delete;
    SDL1Loader(SDL1Loader&&) noexcept = default;
    SDL1Loader& operator=(SDL1Loader&&) noexcept = default;

    bool load()
    {
#ifdef _WIN32
        const std::string lib_name = "SDL.dll";
#else
        const std::string lib_name = "libSDL-1.2.so.0";
#endif

        if (!_library.Load(lib_name)) 
        {
            return false;
        }

        bool success = true;

        // Initialization, Errors, and Lifecycles
        LoadProc(SDL_Init, "SDL_Init", success);
        LoadProc(SDL_InitSubSystem, "SDL_InitSubSystem", success);
        LoadProc(SDL_QuitSubSystem, "SDL_QuitSubSystem", success);
        LoadProc(SDL_WasInit, "SDL_WasInit", success);
        LoadProc(SDL_Quit, "SDL_Quit", success);
        LoadProc(SDL_GetError, "SDL_GetError", success);
        LoadProc(SDL_ClearError, "SDL_ClearError", success);

        // Video modes and Window management
        LoadProc(SDL_SetVideoMode, "SDL_SetVideoMode", success);
        LoadProc(SDL_VideoModeOK, "SDL_VideoModeOK", success);
        LoadProc(SDL_GetVideoSurface, "SDL_GetVideoSurface", success);
        LoadProc(SDL_Flip, "SDL_Flip", success);
        LoadProc(SDL_UpdateRect, "SDL_UpdateRect", success);
        LoadProc(SDL_UpdateRects, "SDL_UpdateRects", success);
        LoadProc(SDL_WM_SetCaption, "SDL_WM_SetCaption", success);
        LoadProc(SDL_WM_GetCaption, "SDL_WM_GetCaption", success);
        LoadProc(SDL_WM_ToggleFullScreen, "SDL_WM_ToggleFullScreen", success);

        // Surface management
        LoadProc(SDL_CreateRGBSurface, "SDL_CreateRGBSurface", success);
        LoadProc(SDL_CreateRGBSurfaceFrom, "SDL_CreateRGBSurfaceFrom", success);
        LoadProc(SDL_FreeSurface, "SDL_FreeSurface", success);
        LoadProc(SDL_LockSurface, "SDL_LockSurface", success);
        LoadProc(SDL_UnlockSurface, "SDL_UnlockSurface", success);

        // Pixel operations and Blitting
        LoadProc(SDL_UpperBlit, "SDL_UpperBlit", success);
        LoadProc(SDL_FillRect, "SDL_FillRect", success);
        LoadProc(SDL_DisplayFormat, "SDL_DisplayFormat", success);
        LoadProc(SDL_DisplayFormatAlpha, "SDL_DisplayFormatAlpha", success);

        // Color keys, Palettes, and Alpha channel
        LoadProc(SDL_SetColorKey, "SDL_SetColorKey", success);
        LoadProc(SDL_SetAlpha, "SDL_SetAlpha", success);
        LoadProc(SDL_MapRGB, "SDL_MapRGB", success);
        LoadProc(SDL_MapRGBA, "SDL_MapRGBA", success);
        LoadProc(SDL_GetRGB, "SDL_GetRGB", success);
        LoadProc(SDL_GetRGBA, "SDL_GetRGBA", success);

        // Events
        LoadProc(SDL_PollEvent, "SDL_PollEvent", success);
        LoadProc(SDL_WaitEvent, "SDL_WaitEvent", success);
        LoadProc(SDL_GetAppState, "SDL_GetAppState", success);

        // Time
        LoadProc(SDL_GetTicks, "SDL_GetTicks", success);
        LoadProc(SDL_Delay, "SDL_Delay", success);

        if (!success) 
        {
            std::println(std::cerr, "SdlLoader: Initialization failed due to missing functions.");
            Unload();
            return false;
        }

        return true;
    }

    void Unload() 
    {
        _library.Unload();
    }

    explicit operator bool() const noexcept 
    { 
        return static_cast<bool>(_library);
    }

private:
    LibLoader _library;

    template <typename T>
    void LoadProc(T& ptr, const char* name, bool& success) const noexcept
    {
        if (!success) return;

        auto result = _library.get_proc<T>(name);

        if (result.has_value())
        {
            ptr = result.value();
        }
        else
        {
            std::println(std::cerr, "SdlLoader: Link error -> {}", result.error());
            success = false;
        }
    }
};
