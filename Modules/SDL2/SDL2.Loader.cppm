// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

export module SDL2.Loader;

import std;
import SDL2.API;
import LibLoader;

export class SDL2Loader
{
public:
    SDL2Loader() = default;

    ~SDL2Loader()
    {
        Unload();
    }

    SDL2Loader(const SDL2Loader&) = delete;
    SDL2Loader& operator=(const SDL2Loader&) = delete;
    SDL2Loader(SDL2Loader&&) noexcept = default;
    SDL2Loader& operator=(SDL2Loader&&) noexcept = default;

    bool load()
    {
#ifdef _WIN32
        const std::string lib_name = "SDL2.dll";
#else
        const std::string lib_name = "libSDL2-2.0.so.0";
#endif

        if (!_library.Load(lib_name))
        {
            return false;
        }

        bool success = true;

        // --- Initialization, Errors, and Lifecycles ---
        LoadProc(SDL_Init, "SDL_Init", success);
        LoadProc(SDL_InitSubSystem, "SDL_InitSubSystem", success);
        LoadProc(SDL_QuitSubSystem, "SDL_QuitSubSystem", success);
        LoadProc(SDL_WasInit, "SDL_WasInit", success);
        LoadProc(SDL_Quit, "SDL_Quit", success);
        LoadProc(SDL_GetError, "SDL_GetError", success);
        LoadProc(SDL_ClearError, "SDL_ClearError", success);

        // --- Window management ---
        LoadProc(SDL_CreateWindow, "SDL_CreateWindow", success);
        LoadProc(SDL_DestroyWindow, "SDL_DestroyWindow", success);
        LoadProc(SDL_SetWindowTitle, "SDL_SetWindowTitle", success);
        LoadProc(SDL_GetWindowTitle, "SDL_GetWindowTitle", success);
        LoadProc(SDL_SetWindowSize, "SDL_SetWindowSize", success);
        LoadProc(SDL_GetWindowSize, "SDL_GetWindowSize", success);
        LoadProc(SDL_ShowWindow, "SDL_ShowWindow", success);
        LoadProc(SDL_HideWindow, "SDL_HideWindow", success);
        LoadProc(SDL_RaiseWindow, "SDL_RaiseWindow", success);
        LoadProc(SDL_MaximizeWindow, "SDL_MaximizeWindow", success);
        LoadProc(SDL_MinimizeWindow, "SDL_MinimizeWindow", success);
        LoadProc(SDL_RestoreWindow, "SDL_RestoreWindow", success);
        LoadProc(SDL_SetWindowFullscreen, "SDL_SetWindowFullscreen", success);
        LoadProc(SDL_GetWindowSurface, "SDL_GetWindowSurface", success);
        LoadProc(SDL_UpdateWindowSurface, "SDL_UpdateWindowSurface", success);
        LoadProc(SDL_UpdateWindowSurfaceRects, "SDL_UpdateWindowSurfaceRects", success);

        // --- Renderer ---
        LoadProc(SDL_CreateRenderer, "SDL_CreateRenderer", success);
        LoadProc(SDL_DestroyRenderer, "SDL_DestroyRenderer", success);
        LoadProc(SDL_SetRenderDrawColor, "SDL_SetRenderDrawColor", success);
        LoadProc(SDL_GetRenderDrawColor, "SDL_GetRenderDrawColor", success);
        LoadProc(SDL_RenderClear, "SDL_RenderClear", success);
        LoadProc(SDL_RenderPresent, "SDL_RenderPresent", success);
        LoadProc(SDL_RenderFillRect, "SDL_RenderFillRect", success);
        LoadProc(SDL_RenderDrawRect, "SDL_RenderDrawRect", success);
        LoadProc(SDL_RenderDrawLine, "SDL_RenderDrawLine", success);
        LoadProc(SDL_RenderDrawPoint, "SDL_RenderDrawPoint", success);
        LoadProc(SDL_RenderCopy, "SDL_RenderCopy", success);
        LoadProc(SDL_RenderCopyEx, "SDL_RenderCopyEx", success);
        LoadProc(SDL_RenderSetClipRect, "SDL_RenderSetClipRect", success);
        LoadProc(SDL_RenderGetClipRect, "SDL_RenderGetClipRect", success);
        LoadProc(SDL_RenderSetLogicalSize, "SDL_RenderSetLogicalSize", success);
        LoadProc(SDL_RenderGetLogicalSize, "SDL_RenderGetLogicalSize", success);
        LoadProc(SDL_RenderSetViewport, "SDL_RenderSetViewport", success);
        LoadProc(SDL_RenderGetViewport, "SDL_RenderGetViewport", success);
        LoadProc(SDL_RenderSetScale, "SDL_RenderSetScale", success);
        LoadProc(SDL_RenderGetScale, "SDL_RenderGetScale", success);
        LoadProc(SDL_SetRenderTarget, "SDL_SetRenderTarget", success);
        LoadProc(SDL_GetRenderTarget, "SDL_GetRenderTarget", success);

        // --- Textures ---
        LoadProc(SDL_CreateTexture, "SDL_CreateTexture", success);
        LoadProc(SDL_CreateTextureFromSurface, "SDL_CreateTextureFromSurface", success);
        LoadProc(SDL_DestroyTexture, "SDL_DestroyTexture", success);
        LoadProc(SDL_QueryTexture, "SDL_QueryTexture", success);
        LoadProc(SDL_SetTextureColorMod, "SDL_SetTextureColorMod", success);
        LoadProc(SDL_GetTextureColorMod, "SDL_GetTextureColorMod", success);
        LoadProc(SDL_SetTextureAlphaMod, "SDL_SetTextureAlphaMod", success);
        LoadProc(SDL_GetTextureAlphaMod, "SDL_GetTextureAlphaMod", success);
        LoadProc(SDL_SetTextureBlendMode, "SDL_SetTextureBlendMode", success);
        LoadProc(SDL_GetTextureBlendMode, "SDL_GetTextureBlendMode", success);
        LoadProc(SDL_UpdateTexture, "SDL_UpdateTexture", success);
        LoadProc(SDL_LockTexture, "SDL_LockTexture", success);
        LoadProc(SDL_UnlockTexture, "SDL_UnlockTexture", success);

        // --- Surface management (SDL 1.2 compatible wrappers) ---
        LoadProc(SDL_CreateRGBSurface, "SDL_CreateRGBSurface", success);
        LoadProc(SDL_CreateRGBSurfaceFrom, "SDL_CreateRGBSurfaceFrom", success);
        LoadProc(SDL_FreeSurface, "SDL_FreeSurface", success);
        LoadProc(SDL_LockSurface, "SDL_LockSurface", success);
        LoadProc(SDL_UnlockSurface, "SDL_UnlockSurface", success);
        LoadProc(SDL_SaveBMP, "SDL_SaveBMP", success);
        LoadProc(SDL_LoadBMP, "SDL_LoadBMP", success);
        LoadProc(SDL_SetSurfacePalette, "SDL_SetSurfacePalette", success);
        LoadProc(SDL_SetSurfaceRLE, "SDL_SetSurfaceRLE", success);
        LoadProc(SDL_SetColorKey, "SDL_SetColorKey", success);
        LoadProc(SDL_GetColorKey, "SDL_GetColorKey", success);
        LoadProc(SDL_SetSurfaceColorMod, "SDL_SetSurfaceColorMod", success);
        LoadProc(SDL_GetSurfaceColorMod, "SDL_GetSurfaceColorMod", success);
        LoadProc(SDL_SetSurfaceAlphaMod, "SDL_SetSurfaceAlphaMod", success);
        LoadProc(SDL_GetSurfaceAlphaMod, "SDL_GetSurfaceAlphaMod", success);
        LoadProc(SDL_SetSurfaceBlendMode, "SDL_SetSurfaceBlendMode", success);
        LoadProc(SDL_GetSurfaceBlendMode, "SDL_GetSurfaceBlendMode", success);
        LoadProc(SDL_SetSurfaceClipRect, "SDL_SetSurfaceClipRect", success);
        LoadProc(SDL_GetSurfaceClipRect, "SDL_GetSurfaceClipRect", success);
        LoadProc(SDL_ConvertPixels, "SDL_ConvertPixels", success);
        LoadProc(SDL_FillRect, "SDL_FillRect", success);
        LoadProc(SDL_FillRects, "SDL_FillRects", success);
        LoadProc(SDL_BlitSurface, "SDL_BlitSurface", success);
        LoadProc(SDL_BlitScaled, "SDL_BlitScaled", success);
        LoadProc(SDL_UpperBlit, "SDL_UpperBlit", success);
        LoadProc(SDL_LowerBlit, "SDL_LowerBlit", success);
        LoadProc(SDL_SoftStretch, "SDL_SoftStretch", success);

        // --- Pixel operations ---
        LoadProc(SDL_MapRGB, "SDL_MapRGB", success);
        LoadProc(SDL_MapRGBA, "SDL_MapRGBA", success);
        LoadProc(SDL_GetRGB, "SDL_GetRGB", success);
        LoadProc(SDL_GetRGBA, "SDL_GetRGBA", success);
        LoadProc(SDL_AllocFormat, "SDL_AllocFormat", success);
        LoadProc(SDL_FreeFormat, "SDL_FreeFormat", success);
        LoadProc(SDL_AllocPalette, "SDL_AllocPalette", success);
        LoadProc(SDL_SetPaletteColors, "SDL_SetPaletteColors", success);
        LoadProc(SDL_FreePalette, "SDL_FreePalette", success);

        // --- Events ---
        LoadProc(SDL_PumpEvents, "SDL_PumpEvents", success);
        LoadProc(SDL_PollEvent, "SDL_PollEvent", success);
        LoadProc(SDL_WaitEvent, "SDL_WaitEvent", success);
        LoadProc(SDL_WaitEventTimeout, "SDL_WaitEventTimeout", success);
        LoadProc(SDL_PushEvent, "SDL_PushEvent", success);
        LoadProc(SDL_SetEventFilter, "SDL_SetEventFilter", success);
        LoadProc(SDL_GetEventFilter, "SDL_GetEventFilter", success);
        LoadProc(SDL_AddEventWatch, "SDL_AddEventWatch", success);
        LoadProc(SDL_DelEventWatch, "SDL_DelEventWatch", success);
        LoadProc(SDL_EventState, "SDL_EventState", success);
        LoadProc(SDL_RegisterEvents, "SDL_RegisterEvents", success);

        // --- Keyboard ---
        LoadProc(SDL_GetKeyboardState, "SDL_GetKeyboardState", success);
        LoadProc(SDL_GetKeyFromScancode, "SDL_GetKeyFromScancode", success);
        LoadProc(SDL_GetScancodeFromKey, "SDL_GetScancodeFromKey", success);
        LoadProc(SDL_GetScancodeName, "SDL_GetScancodeName", success);
        LoadProc(SDL_GetScancodeFromName, "SDL_GetScancodeFromName", success);
        LoadProc(SDL_GetKeyName, "SDL_GetKeyName", success);
        LoadProc(SDL_GetKeyFromName, "SDL_GetKeyFromName", success);
        LoadProc(SDL_StartTextInput, "SDL_StartTextInput", success);
        LoadProc(SDL_IsTextInputActive, "SDL_IsTextInputActive", success);
        LoadProc(SDL_StopTextInput, "SDL_StopTextInput", success);
        LoadProc(SDL_SetTextInputRect, "SDL_SetTextInputRect", success);

        // --- Mouse ---
        LoadProc(SDL_GetMouseState, "SDL_GetMouseState", success);
        LoadProc(SDL_GetGlobalMouseState, "SDL_GetGlobalMouseState", success);
        LoadProc(SDL_GetRelativeMouseState, "SDL_GetRelativeMouseState", success);
        LoadProc(SDL_WarpMouseInWindow, "SDL_WarpMouseInWindow", success);
        LoadProc(SDL_SetRelativeMouseMode, "SDL_SetRelativeMouseMode", success);
        LoadProc(SDL_GetRelativeMouseMode, "SDL_GetRelativeMouseMode", success);
        LoadProc(SDL_ShowCursor, "SDL_ShowCursor", success);

        // --- Joystick ---
        LoadProc(SDL_JoystickOpen, "SDL_JoystickOpen", success);
        LoadProc(SDL_JoystickClose, "SDL_JoystickClose", success);
        LoadProc(SDL_JoystickName, "SDL_JoystickName", success);
        LoadProc(SDL_JoystickNumAxes, "SDL_JoystickNumAxes", success);
        LoadProc(SDL_JoystickNumBalls, "SDL_JoystickNumBalls", success);
        LoadProc(SDL_JoystickNumHats, "SDL_JoystickNumHats", success);
        LoadProc(SDL_JoystickNumButtons, "SDL_JoystickNumButtons", success);
        LoadProc(SDL_JoystickGetAxis, "SDL_JoystickGetAxis", success);
        LoadProc(SDL_JoystickGetHat, "SDL_JoystickGetHat", success);
        LoadProc(SDL_JoystickGetBall, "SDL_JoystickGetBall", success);
        LoadProc(SDL_JoystickGetButton, "SDL_JoystickGetButton", success);
        LoadProc(SDL_NumJoysticks, "SDL_NumJoysticks", success);
        LoadProc(SDL_JoystickUpdate, "SDL_JoystickUpdate", success);
        LoadProc(SDL_JoystickEventState, "SDL_JoystickEventState", success);

        // --- Game Controller ---
        LoadProc(SDL_GameControllerOpen, "SDL_GameControllerOpen", success);
        LoadProc(SDL_GameControllerClose, "SDL_GameControllerClose", success);
        LoadProc(SDL_GameControllerName, "SDL_GameControllerName", success);
        LoadProc(SDL_GameControllerGetAxis, "SDL_GameControllerGetAxis", success);
        LoadProc(SDL_GameControllerGetButton, "SDL_GameControllerGetButton", success);
        LoadProc(SDL_GameControllerEventState, "SDL_GameControllerEventState", success);
        LoadProc(SDL_GameControllerUpdate, "SDL_GameControllerUpdate", success);
        LoadProc(SDL_IsGameController, "SDL_IsGameController", success);
        LoadProc(SDL_GameControllerNameForIndex, "SDL_GameControllerNameForIndex", success);

        // --- Timer ---
        LoadProc(SDL_GetTicks, "SDL_GetTicks", success);
        LoadProc(SDL_GetPerformanceCounter, "SDL_GetPerformanceCounter", success);
        LoadProc(SDL_GetPerformanceFrequency, "SDL_GetPerformanceFrequency", success);
        LoadProc(SDL_Delay, "SDL_Delay", success);
        LoadProc(SDL_AddTimer, "SDL_AddTimer", success);
        LoadProc(SDL_RemoveTimer, "SDL_RemoveTimer", success);

        // --- Audio ---
        LoadProc(SDL_OpenAudio, "SDL_OpenAudio", success);
        LoadProc(SDL_CloseAudio, "SDL_CloseAudio", success);
        LoadProc(SDL_PauseAudio, "SDL_PauseAudio", success);
        LoadProc(SDL_GetAudioStatus, "SDL_GetAudioStatus", success);
        LoadProc(SDL_GetAudioDeviceName, "SDL_GetAudioDeviceName", success);
        LoadProc(SDL_OpenAudioDevice, "SDL_OpenAudioDevice", success);
        LoadProc(SDL_CloseAudioDevice, "SDL_CloseAudioDevice", success);
        LoadProc(SDL_PauseAudioDevice, "SDL_PauseAudioDevice", success);
        LoadProc(SDL_QueueAudio, "SDL_QueueAudio", success);
        LoadProc(SDL_DequeueAudio, "SDL_DequeueAudio", success);
        LoadProc(SDL_GetQueuedAudioSize, "SDL_GetQueuedAudioSize", success);
        LoadProc(SDL_ClearQueuedAudio, "SDL_ClearQueuedAudio", success);

        // --- Haptic ---
        LoadProc(SDL_HapticOpen, "SDL_HapticOpen", success);
        LoadProc(SDL_HapticClose, "SDL_HapticClose", success);
        LoadProc(SDL_HapticNumEffects, "SDL_HapticNumEffects", success);
        LoadProc(SDL_HapticNumEffectsPlaying, "SDL_HapticNumEffectsPlaying", success);
        LoadProc(SDL_HapticQuery, "SDL_HapticQuery", success);
        LoadProc(SDL_HapticEffectSupported, "SDL_HapticEffectSupported", success);
        LoadProc(SDL_HapticNewEffect, "SDL_HapticNewEffect", success);
        LoadProc(SDL_HapticRunEffect, "SDL_HapticRunEffect", success);
        LoadProc(SDL_HapticStopEffect, "SDL_HapticStopEffect", success);
        LoadProc(SDL_HapticDestroyEffect, "SDL_HapticDestroyEffect", success);
        LoadProc(SDL_HapticGetEffectStatus, "SDL_HapticGetEffectStatus", success);
        LoadProc(SDL_HapticSetGain, "SDL_HapticSetGain", success);
        LoadProc(SDL_HapticSetAutocenter, "SDL_HapticSetAutocenter", success);

        // --- Clipboard ---
        LoadProc(SDL_SetClipboardText, "SDL_SetClipboardText", success);
        LoadProc(SDL_GetClipboardText, "SDL_GetClipboardText", success);
        LoadProc(SDL_HasClipboardText, "SDL_HasClipboardText", success);

        // --- CPU Info ---
        LoadProc(SDL_GetCPUCount, "SDL_GetCPUCount", success);
        LoadProc(SDL_GetCPUCacheLineSize, "SDL_GetCPUCacheLineSize", success);
        LoadProc(SDL_HasRDTSC, "SDL_HasRDTSC", success);
        LoadProc(SDL_HasAltiVec, "SDL_HasAltiVec", success);
        LoadProc(SDL_HasMMX, "SDL_HasMMX", success);
        LoadProc(SDL_Has3DNow, "SDL_Has3DNow", success);
        LoadProc(SDL_HasSSE, "SDL_HasSSE", success);
        LoadProc(SDL_HasSSE2, "SDL_HasSSE2", success);
        LoadProc(SDL_HasSSE3, "SDL_HasSSE3", success);
        LoadProc(SDL_HasSSE41, "SDL_HasSSE41", success);
        LoadProc(SDL_HasSSE42, "SDL_HasSSE42", success);
        LoadProc(SDL_HasAVX, "SDL_HasAVX", success);
        LoadProc(SDL_HasAVX2, "SDL_HasAVX2", success);
        LoadProc(SDL_HasAVX512F, "SDL_HasAVX512F", success);
        LoadProc(SDL_HasARMSIMD, "SDL_HasARMSIMD", success);
        LoadProc(SDL_HasNEON, "SDL_HasNEON", success);

        // --- Power management ---
        LoadProc(SDL_GetPowerInfo, "SDL_GetPowerInfo", success);

        // --- Platform ---
        LoadProc(SDL_GetPlatform, "SDL_GetPlatform", success);

        if (!success)
        {
            std::println(std::cerr, "SDL2Loader: Initialization failed due to missing functions.");
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
            std::println(std::cerr, "SDL2Loader: Link error -> {}", result.error());
            success = false;
        }
    }
};
