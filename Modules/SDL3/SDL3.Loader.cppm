// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

export module SDL3.Loader;

import std;
import SDL3.API;
import LibLoader;

export class SDL3Loader
{
public:
    SDL3Loader() = default;

    ~SDL3Loader()
    {
        Unload();
    }

    SDL3Loader(const SDL3Loader&) = delete;
    SDL3Loader& operator=(const SDL3Loader&) = delete;
    SDL3Loader(SDL3Loader&&) noexcept = default;
    SDL3Loader& operator=(SDL3Loader&&) noexcept = default;

    bool load()
    {
#ifdef _WIN32
        const std::string lib_name = "SDL3.dll";
#else
        const std::string lib_name = "libSDL3.so.0";
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
        LoadProc(SDL_SetError, "SDL_SetError", success);

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
        LoadProc(SDL_SyncWindow, "SDL_SyncWindow", success);

        // --- Renderer ---
        LoadProc(SDL_CreateRenderer, "SDL_CreateRenderer", success);
        LoadProc(SDL_DestroyRenderer, "SDL_DestroyRenderer", success);
        LoadProc(SDL_SetRenderDrawColor, "SDL_SetRenderDrawColor", success);
        LoadProc(SDL_GetRenderDrawColor, "SDL_GetRenderDrawColor", success);
        LoadProc(SDL_RenderClear, "SDL_RenderClear", success);
        LoadProc(SDL_RenderPresent, "SDL_RenderPresent", success);
        LoadProc(SDL_RenderFillRect, "SDL_RenderFillRect", success);
        LoadProc(SDL_RenderRect, "SDL_RenderRect", success);
        LoadProc(SDL_RenderLine, "SDL_RenderLine", success);
        LoadProc(SDL_RenderPoint, "SDL_RenderPoint", success);
        LoadProc(SDL_RenderCopy, "SDL_RenderCopy", success);
        LoadProc(SDL_RenderCopyEx, "SDL_RenderCopyEx", success);
        LoadProc(SDL_SetRenderClipRect, "SDL_SetRenderClipRect", success);
        LoadProc(SDL_GetRenderClipRect, "SDL_GetRenderClipRect", success);
        LoadProc(SDL_SetRenderLogicalPresentation, "SDL_SetRenderLogicalPresentation", success);
        LoadProc(SDL_GetRenderLogicalPresentation, "SDL_GetRenderLogicalPresentation", success);
        LoadProc(SDL_SetRenderViewport, "SDL_SetRenderViewport", success);
        LoadProc(SDL_GetRenderViewport, "SDL_GetRenderViewport", success);
        LoadProc(SDL_SetRenderScale, "SDL_SetRenderScale", success);
        LoadProc(SDL_GetRenderScale, "SDL_GetRenderScale", success);
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

        // --- Surface management ---
        LoadProc(SDL_CreateSurface, "SDL_CreateSurface", success);
        LoadProc(SDL_CreateSurfaceFrom, "SDL_CreateSurfaceFrom", success);
        LoadProc(SDL_DestroySurface, "SDL_DestroySurface", success);
        LoadProc(SDL_LockSurface, "SDL_LockSurface", success);
        LoadProc(SDL_UnlockSurface, "SDL_UnlockSurface", success);
        LoadProc(SDL_SaveBMP, "SDL_SaveBMP", success);
        LoadProc(SDL_LoadBMP, "SDL_LoadBMP", success);
        LoadProc(SDL_SetSurfacePalette, "SDL_SetSurfacePalette", success);
        LoadProc(SDL_SetSurfaceRLE, "SDL_SetSurfaceRLE", success);
        LoadProc(SDL_SetSurfaceColorKey, "SDL_SetSurfaceColorKey", success);
        LoadProc(SDL_GetSurfaceColorKey, "SDL_GetSurfaceColorKey", success);
        LoadProc(SDL_SetSurfaceColorMod, "SDL_SetSurfaceColorMod", success);
        LoadProc(SDL_GetSurfaceColorMod, "SDL_GetSurfaceColorMod", success);
        LoadProc(SDL_SetSurfaceAlphaMod, "SDL_SetSurfaceAlphaMod", success);
        LoadProc(SDL_GetSurfaceAlphaMod, "SDL_GetSurfaceAlphaMod", success);
        LoadProc(SDL_SetSurfaceBlendMode, "SDL_SetSurfaceBlendMode", success);
        LoadProc(SDL_GetSurfaceBlendMode, "SDL_GetSurfaceBlendMode", success);
        LoadProc(SDL_SetSurfaceClipRect, "SDL_SetSurfaceClipRect", success);
        LoadProc(SDL_GetSurfaceClipRect, "SDL_GetSurfaceClipRect", success);
        LoadProc(SDL_ConvertPixels, "SDL_ConvertPixels", success);
        LoadProc(SDL_FillSurfaceRect, "SDL_FillSurfaceRect", success);
        LoadProc(SDL_FillSurfaceRects, "SDL_FillSurfaceRects", success);
        LoadProc(SDL_BlitSurface, "SDL_BlitSurface", success);
        LoadProc(SDL_BlitSurfaceScaled, "SDL_BlitSurfaceScaled", success);

        // --- Pixel operations ---
        LoadProc(SDL_MapRGB, "SDL_MapRGB", success);
        LoadProc(SDL_MapRGBA, "SDL_MapRGBA", success);
        LoadProc(SDL_GetRGB, "SDL_GetRGB", success);
        LoadProc(SDL_GetRGBA, "SDL_GetRGBA", success);
        LoadProc(SDL_CreatePixelFormat, "SDL_CreatePixelFormat", success);
        LoadProc(SDL_DestroyPixelFormat, "SDL_DestroyPixelFormat", success);
        LoadProc(SDL_CreatePalette, "SDL_CreatePalette", success);
        LoadProc(SDL_SetPaletteColors, "SDL_SetPaletteColors", success);
        LoadProc(SDL_DestroyPalette, "SDL_DestroyPalette", success);

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
        LoadProc(SDL_SetEventEnabled, "SDL_SetEventEnabled", success);
        LoadProc(SDL_EventEnabled, "SDL_EventEnabled", success);
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
        LoadProc(SDL_TextInputActive, "SDL_TextInputActive", success);
        LoadProc(SDL_StopTextInput, "SDL_StopTextInput", success);
        LoadProc(SDL_SetTextInputArea, "SDL_SetTextInputArea", success);

        // --- Mouse ---
        LoadProc(SDL_GetMouseState, "SDL_GetMouseState", success);
        LoadProc(SDL_GetGlobalMouseState, "SDL_GetGlobalMouseState", success);
        LoadProc(SDL_GetRelativeMouseState, "SDL_GetRelativeMouseState", success);
        LoadProc(SDL_WarpMouseInWindow, "SDL_WarpMouseInWindow", success);
        LoadProc(SDL_SetRelativeMouseMode, "SDL_SetRelativeMouseMode", success);
        LoadProc(SDL_GetRelativeMouseMode, "SDL_GetRelativeMouseMode", success);
        LoadProc(SDL_ShowCursor, "SDL_ShowCursor", success);
        LoadProc(SDL_HideCursor, "SDL_HideCursor", success);
        LoadProc(SDL_CursorVisible, "SDL_CursorVisible", success);

        // --- Joystick ---
        LoadProc(SDL_OpenJoystick, "SDL_OpenJoystick", success);
        LoadProc(SDL_CloseJoystick, "SDL_CloseJoystick", success);
        LoadProc(SDL_GetJoystickName, "SDL_GetJoystickName", success);
        LoadProc(SDL_GetNumJoystickAxes, "SDL_GetNumJoystickAxes", success);
        LoadProc(SDL_GetNumJoystickBalls, "SDL_GetNumJoystickBalls", success);
        LoadProc(SDL_GetNumJoystickHats, "SDL_GetNumJoystickHats", success);
        LoadProc(SDL_GetNumJoystickButtons, "SDL_GetNumJoystickButtons", success);
        LoadProc(SDL_GetJoystickAxis, "SDL_GetJoystickAxis", success);
        LoadProc(SDL_GetJoystickHat, "SDL_GetJoystickHat", success);
        LoadProc(SDL_GetJoystickBall, "SDL_GetJoystickBall", success);
        LoadProc(SDL_GetJoystickButton, "SDL_GetJoystickButton", success);
        LoadProc(SDL_GetJoysticks, "SDL_GetJoysticks", success);
        LoadProc(SDL_UpdateJoysticks, "SDL_UpdateJoysticks", success);
        LoadProc(SDL_JoystickEventsEnabled, "SDL_JoystickEventsEnabled", success);
        LoadProc(SDL_SetJoystickEventsEnabled, "SDL_SetJoystickEventsEnabled", success);

        // --- Gamepad ---
        LoadProc(SDL_OpenGamepad, "SDL_OpenGamepad", success);
        LoadProc(SDL_CloseGamepad, "SDL_CloseGamepad", success);
        LoadProc(SDL_GetGamepadName, "SDL_GetGamepadName", success);
        LoadProc(SDL_GetGamepadAxis, "SDL_GetGamepadAxis", success);
        LoadProc(SDL_GetGamepadButton, "SDL_GetGamepadButton", success);
        LoadProc(SDL_GamepadEventsEnabled, "SDL_GamepadEventsEnabled", success);
        LoadProc(SDL_SetGamepadEventsEnabled, "SDL_SetGamepadEventsEnabled", success);
        LoadProc(SDL_UpdateGamepads, "SDL_UpdateGamepads", success);
        LoadProc(SDL_IsGamepad, "SDL_IsGamepad", success);
        LoadProc(SDL_GetGamepadNameForID, "SDL_GetGamepadNameForID", success);
        LoadProc(SDL_GetGamepads, "SDL_GetGamepads", success);

        // --- Timer ---
        LoadProc(SDL_GetTicks, "SDL_GetTicks", success);
        LoadProc(SDL_GetTicksNS, "SDL_GetTicksNS", success);
        LoadProc(SDL_GetPerformanceCounter, "SDL_GetPerformanceCounter", success);
        LoadProc(SDL_GetPerformanceFrequency, "SDL_GetPerformanceFrequency", success);
        LoadProc(SDL_Delay, "SDL_Delay", success);
        LoadProc(SDL_DelayNS, "SDL_DelayNS", success);
        LoadProc(SDL_AddTimer, "SDL_AddTimer", success);
        LoadProc(SDL_RemoveTimer, "SDL_RemoveTimer", success);

        // --- Audio ---
        LoadProc(SDL_OpenAudioDevice, "SDL_OpenAudioDevice", success);
        LoadProc(SDL_OpenAudioDeviceStream, "SDL_OpenAudioDeviceStream", success);
        LoadProc(SDL_CloseAudioDevice, "SDL_CloseAudioDevice", success);
        LoadProc(SDL_PauseAudioDevice, "SDL_PauseAudioDevice", success);
        LoadProc(SDL_ResumeAudioDevice, "SDL_ResumeAudioDevice", success);
        LoadProc(SDL_AudioDevicePaused, "SDL_AudioDevicePaused", success);
        LoadProc(SDL_GetAudioDeviceFormat, "SDL_GetAudioDeviceFormat", success);
        LoadProc(SDL_GetAudioDeviceName, "SDL_GetAudioDeviceName", success);
        LoadProc(SDL_GetAudioPlaybackDevices, "SDL_GetAudioPlaybackDevices", success);
        LoadProc(SDL_GetAudioRecordingDevices, "SDL_GetAudioRecordingDevices", success);

        // --- Audio Stream ---
        LoadProc(SDL_CreateAudioStream, "SDL_CreateAudioStream", success);
        LoadProc(SDL_DestroyAudioStream, "SDL_DestroyAudioStream", success);
        LoadProc(SDL_BindAudioStream, "SDL_BindAudioStream", success);
        LoadProc(SDL_UnbindAudioStream, "SDL_UnbindAudioStream", success);
        LoadProc(SDL_PutAudioStreamData, "SDL_PutAudioStreamData", success);
        LoadProc(SDL_GetAudioStreamData, "SDL_GetAudioStreamData", success);
        LoadProc(SDL_GetAudioStreamAvailable, "SDL_GetAudioStreamAvailable", success);
        LoadProc(SDL_GetAudioStreamQueued, "SDL_GetAudioStreamQueued", success);
        LoadProc(SDL_FlushAudioStream, "SDL_FlushAudioStream", success);
        LoadProc(SDL_ClearAudioStream, "SDL_ClearAudioStream", success);
        LoadProc(SDL_PauseAudioStreamDevice, "SDL_PauseAudioStreamDevice", success);
        LoadProc(SDL_ResumeAudioStreamDevice, "SDL_ResumeAudioStreamDevice", success);

        // --- Haptic ---
        LoadProc(SDL_OpenHaptic, "SDL_OpenHaptic", success);
        LoadProc(SDL_CloseHaptic, "SDL_CloseHaptic", success);
        LoadProc(SDL_GetMaxHapticEffects, "SDL_GetMaxHapticEffects", success);
        LoadProc(SDL_GetMaxHapticEffectsPlaying, "SDL_GetMaxHapticEffectsPlaying", success);
        LoadProc(SDL_GetHapticFeatures, "SDL_GetHapticFeatures", success);
        LoadProc(SDL_HapticEffectSupported, "SDL_HapticEffectSupported", success);
        LoadProc(SDL_CreateHapticEffect, "SDL_CreateHapticEffect", success);
        LoadProc(SDL_RunHapticEffect, "SDL_RunHapticEffect", success);
        LoadProc(SDL_StopHapticEffect, "SDL_StopHapticEffect", success);
        LoadProc(SDL_DestroyHapticEffect, "SDL_DestroyHapticEffect", success);
        LoadProc(SDL_GetHapticEffectStatus, "SDL_GetHapticEffectStatus", success);
        LoadProc(SDL_SetHapticGain, "SDL_SetHapticGain", success);
        LoadProc(SDL_SetHapticAutocenter, "SDL_SetHapticAutocenter", success);
        LoadProc(SDL_OpenHapticFromJoystick, "SDL_OpenHapticFromJoystick", success);

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

        // --- Properties API ---
        LoadProc(SDL_CreateProperties, "SDL_CreateProperties", success);
        LoadProc(SDL_DestroyProperties, "SDL_DestroyProperties", success);
        LoadProc(SDL_SetProperty, "SDL_SetProperty", success);
        LoadProc(SDL_GetProperty, "SDL_GetProperty", success);
        LoadProc(SDL_SetStringProperty, "SDL_SetStringProperty", success);
        LoadProc(SDL_GetStringProperty, "SDL_GetStringProperty", success);
        LoadProc(SDL_SetNumberProperty, "SDL_SetNumberProperty", success);
        LoadProc(SDL_GetNumberProperty, "SDL_GetNumberProperty", success);
        LoadProc(SDL_SetBooleanProperty, "SDL_SetBooleanProperty", success);
        LoadProc(SDL_GetBooleanProperty, "SDL_GetBooleanProperty", success);

        // --- Filesystem API ---
        LoadProc(SDL_GetBasePath, "SDL_GetBasePath", success);
        LoadProc(SDL_GetPrefPath, "SDL_GetPrefPath", success);
        LoadProc(SDL_GetCurrentDirectory, "SDL_GetCurrentDirectory", success);
        LoadProc(SDL_CreateDirectory, "SDL_CreateDirectory", success);
        LoadProc(SDL_EnumerateDirectory, "SDL_EnumerateDirectory", success);
        LoadProc(SDL_RemovePath, "SDL_RemovePath", success);
        LoadProc(SDL_RenamePath, "SDL_RenamePath", success);

        // --- Dialog API ---
        LoadProc(SDL_ShowOpenFileDialog, "SDL_ShowOpenFileDialog", success);
        LoadProc(SDL_ShowSaveFileDialog, "SDL_ShowSaveFileDialog", success);
        LoadProc(SDL_ShowOpenFolderDialog, "SDL_ShowOpenFolderDialog", success);

        // --- Camera API ---
        LoadProc(SDL_GetCameras, "SDL_GetCameras", success);
        LoadProc(SDL_GetCameraFormat, "SDL_GetCameraFormat", success);
        LoadProc(SDL_GetCameraName, "SDL_GetCameraName", success);

        // --- Time API ---
        LoadProc(SDL_GetCurrentTime, "SDL_GetCurrentTime", success);
        LoadProc(SDL_TimeToDateTime, "SDL_TimeToDateTime", success);

        // --- System theme ---
        LoadProc(SDL_GetSystemTheme, "SDL_GetSystemTheme", success);

        if (!success)
        {
            std::println(std::cerr, "SDL3Loader: Initialization failed due to missing functions.");
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
            std::println(std::cerr, "SDL3Loader: Link error -> {}", result.error());
            success = false;
        }
    }
};
