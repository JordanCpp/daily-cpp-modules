// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

export module SDL1.API;

import std;

// --- INTERNAL AND UNDERLYING STRUCTURES ---

export struct SDL_Rect {
    std::int16_t  x, y;
    std::uint16_t w, h;
};

export struct SDL_Color {
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t unused;
};

export struct SDL_Palette {
    int        ncolors;
    SDL_Color* colors;
};

export struct SDL_PixelFormat {
    SDL_Palette* palette;
    std::uint8_t  BitsPerPixel;
    std::uint8_t  BytesPerPixel;
    std::uint8_t  Rloss, Gloss, Bloss, Aloss;
    std::uint8_t  Rshift, Gshift, Bshift, Ashift;
    std::uint32_t Rmask, Gmask, Bmask, Amask;
    std::uint32_t colorkey;
    std::uint8_t  alpha;
};

export struct SDL_Surface;

// Internal blit map structure used inside SDL_Surface
export struct SDL_BlitMap {
    SDL_Surface* dst;
    int identity;
    std::uint8_t* table;
    void* blit;            // Pointer to internal blit function (SDL_loblit)
    void* data;            // Private blit map data

    // Hardware acceleration palette versions (SDL 1.2.x specifics)
    std::uint32_t dst_palette_version;
    std::uint32_t src_palette_version;
};

// --- COMPLETE SDL_SURFACE STRUCTURE ---

export struct SDL_Surface {
    std::uint32_t    flags;             // Read-only
    SDL_PixelFormat* format;            // Read-only
    int              w, h;              // Read-only
    std::uint16_t    pitch;             // Read-only
    void* pixels;            // Read-write
    int              offset;            // Private SDL use

    // Hardware-specific information
    void* hwdata;            // private_hwdata *

    // Clipping information
    SDL_Rect         clip_rect;         // Read-only
    std::uint32_t    unused1;           // For binary compatibility

    // Info for fast blit optimization
    std::uint32_t    locked;            // Allow recursive locks

    // Blit map info
    SDL_BlitMap* map;               // Private blit map info

    // Reference count
    int              refcount;          // Read-mostly, write inside SDL
};

// --- EVENT STRUCTURES (SDL_Event) ---

export struct SDL_keysym { std::uint8_t scancode; std::uint32_t sym; std::uint32_t mod; std::uint16_t unicode; };

export struct SDL_ActiveEvent { std::uint8_t type; std::uint8_t gain; std::uint8_t state; };
export struct SDL_KeyboardEvent { std::uint8_t type; std::uint8_t which; std::uint8_t state; SDL_keysym keysym; };
export struct SDL_MouseMotionEvent { std::uint8_t type; std::uint8_t which; std::uint8_t state; std::uint16_t x, y; std::int16_t xrel, yrel; };
export struct SDL_MouseButtonEvent { std::uint8_t type; std::uint8_t which; std::uint8_t button; std::uint8_t state; std::uint16_t x, y; };
export struct SDL_JoyAxisEvent { std::uint8_t type; std::uint8_t which; std::uint8_t axis; std::int16_t value; };
export struct SDL_JoyBallEvent { std::uint8_t type; std::uint8_t which; std::uint8_t ball; std::int16_t xrel, yrel; };
export struct SDL_JoyHatEvent { std::uint8_t type; std::uint8_t which; std::uint8_t hat; std::uint8_t value; };
export struct SDL_JoyButtonEvent { std::uint8_t type; std::uint8_t which; std::uint8_t button; std::uint8_t state; };
export struct SDL_ResizeEvent { std::uint8_t type; int w; int h; };
export struct SDL_ExposeEvent { std::uint8_t type; };
export struct SDL_QuitEvent { std::uint8_t type; };
export struct SDL_UserEvent { std::uint8_t type; int code; void* data1; void* data2; };
export struct SDL_SysWMEvent { std::uint8_t type; void* msg; }; // private_syswmmsg *

export union SDL_Event {
    std::uint8_t type;
    SDL_ActiveEvent active;
    SDL_KeyboardEvent key;
    SDL_MouseMotionEvent motion;
    SDL_MouseButtonEvent button;
    SDL_JoyAxisEvent jaxis;
    SDL_JoyBallEvent jball;
    SDL_JoyHatEvent jhat;
    SDL_JoyButtonEvent jbutton;
    SDL_ResizeEvent resize;
    SDL_ExposeEvent expose;
    SDL_QuitEvent quit;
    SDL_UserEvent user;
    SDL_SysWMEvent syswm;
};

// --- CONSTANTS ---

// Initialization flags
export constexpr std::uint32_t SDL_INIT_TIMER = 0x00000001;
export constexpr std::uint32_t SDL_INIT_AUDIO = 0x00000010;
export constexpr std::uint32_t SDL_INIT_VIDEO = 0x00000020;
export constexpr std::uint32_t SDL_INIT_CDROM = 0x00000100;
export constexpr std::uint32_t SDL_INIT_JOYSTICK = 0x00000200;
export constexpr std::uint32_t SDL_INIT_NOPARACHUTE = 0x00100000;
export constexpr std::uint32_t SDL_INIT_EVENTTHREAD = 0x01000000;
export constexpr std::uint32_t SDL_INIT_EVERYTHING = 0x0000FFFF;

// Surface flags
export constexpr std::uint32_t SDL_SWSURFACE = 0x00000000;
export constexpr std::uint32_t SDL_HWSURFACE = 0x00000001;
export constexpr std::uint32_t SDL_ASYNCBLIT = 0x00000004;
export constexpr std::uint32_t SDL_ANYFORMAT = 0x10000000;
export constexpr std::uint32_t SDL_HWPALETTE = 0x20000000;
export constexpr std::uint32_t SDL_DOUBLEBUF = 0x40000000;
export constexpr std::uint32_t SDL_FULLSCREEN = 0x80000000;
export constexpr std::uint32_t SDL_OPENGL = 0x00000002;
export constexpr std::uint32_t SDL_OPENGLBLIT = 0x0000000A;
export constexpr std::uint32_t SDL_RESIZABLE = 0x00000010;
export constexpr std::uint32_t SDL_NOFRAME = 0x00000020;

// Internal state / Query flags
export constexpr std::uint32_t SDL_HWACCEL = 0x00000100;
export constexpr std::uint32_t SDL_SRCCOLORKEY = 0x00001000;
export constexpr std::uint32_t SDL_RLEACCELOK = 0x00002000;
export constexpr std::uint32_t SDL_RLEACCEL = 0x00004000;
export constexpr std::uint32_t SDL_SRCALPHA = 0x00010000;
export constexpr std::uint32_t SDL_PREALLOC = 0x01000000;

// Event types
export constexpr std::uint8_t  SDL_NOEVENT = 0;
export constexpr std::uint8_t  SDL_ACTIVEEVENT = 1;
export constexpr std::uint8_t  SDL_KEYDOWN = 2;
export constexpr std::uint8_t  SDL_KEYUP = 3;
export constexpr std::uint8_t  SDL_MOUSEMOTION = 4;
export constexpr std::uint8_t  SDL_MOUSEBUTTONDOWN = 5;
export constexpr std::uint8_t  SDL_MOUSEBUTTONUP = 6;
export constexpr std::uint8_t  SDL_JOYAXISMOTION = 7;
export constexpr std::uint8_t  SDL_JOYBALLMOTION = 8;
export constexpr std::uint8_t  SDL_JOYHATMOTION = 9;
export constexpr std::uint8_t  SDL_JOYBUTTONDOWN = 10;
export constexpr std::uint8_t  SDL_JOYBUTTONUP = 11;
export constexpr std::uint8_t  SDL_QUIT = 12;
export constexpr std::uint8_t  SDL_SYSWMEVENT = 13;
export constexpr std::uint8_t  SDL_VIDEORESIZE = 16;
export constexpr std::uint8_t  SDL_VIDEOEXPOSE = 17;
export constexpr std::uint8_t  SDL_USEREVENT = 24;

// --- FUNCTION POINTERS FOR DYNAMIC LOADING ---

// Initialization, Errors, and Lifecycles
export inline int (*SDL_Init)(std::uint32_t flags) = nullptr;
export inline int (*SDL_InitSubSystem)(std::uint32_t flags) = nullptr;
export inline void (*SDL_QuitSubSystem)(std::uint32_t flags) = nullptr;
export inline std::uint32_t(*SDL_WasInit)(std::uint32_t flags) = nullptr;
export inline void (*SDL_Quit)() = nullptr;
export inline const char* (*SDL_GetError)() = nullptr;
export inline void (*SDL_ClearError)() = nullptr;

// Video modes and Window management
export inline SDL_Surface* (*SDL_SetVideoMode)(int width, int height, int bpp, std::uint32_t flags) = nullptr;
export inline int (*SDL_VideoModeOK)(int width, int height, int bpp, std::uint32_t flags) = nullptr;
export inline SDL_Surface* (*SDL_GetVideoSurface)() = nullptr;
export inline int (*SDL_Flip)(SDL_Surface* screen) = nullptr;
export inline void (*SDL_UpdateRect)(SDL_Surface* screen, std::int32_t x, std::int32_t y, std::uint32_t w, std::uint32_t h) = nullptr;
export inline void (*SDL_UpdateRects)(SDL_Surface* screen, int numrects, SDL_Rect* rects) = nullptr;
export inline void (*SDL_WM_SetCaption)(const char* title, const char* icon) = nullptr;
export inline void (*SDL_WM_GetCaption)(const char** title, const char** icon) = nullptr;
export inline int (*SDL_WM_ToggleFullScreen)(SDL_Surface* surface) = nullptr;

// Surface management
export inline SDL_Surface* (*SDL_CreateRGBSurface)(std::uint32_t flags, int width, int height, int depth, std::uint32_t Rmask, std::uint32_t Gmask, std::uint32_t Bmask, std::uint32_t Amask) = nullptr;
export inline SDL_Surface* (*SDL_CreateRGBSurfaceFrom)(void* pixels, int width, int height, int depth, int pitch, std::uint32_t Rmask, std::uint32_t Gmask, std::uint32_t Bmask, std::uint32_t Amask) = nullptr;
export inline void (*SDL_FreeSurface)(SDL_Surface* surface) = nullptr;
export inline int (*SDL_LockSurface)(SDL_Surface* surface) = nullptr;
export inline void (*SDL_UnlockSurface)(SDL_Surface* surface) = nullptr;

// Pixel operations and Blitting
export inline int (*SDL_UpperBlit)(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) = nullptr;
export inline int (*SDL_FillRect)(SDL_Surface* dst, SDL_Rect* dstrect, std::uint32_t color) = nullptr;
export inline SDL_Surface* (*SDL_DisplayFormat)(SDL_Surface* surface) = nullptr;
export inline SDL_Surface* (*SDL_DisplayFormatAlpha)(SDL_Surface* surface) = nullptr;

// Color keys, Palettes, and Alpha channel
export inline int (*SDL_SetColorKey)(SDL_Surface* surface, std::uint32_t flag, std::uint32_t key) = nullptr;
export inline int (*SDL_SetAlpha)(SDL_Surface* surface, std::uint32_t flag, std::uint8_t alpha) = nullptr;
export inline std::uint32_t(*SDL_MapRGB)(const SDL_PixelFormat* format, std::uint8_t r, std::uint8_t g, std::uint8_t b) = nullptr;
export inline std::uint32_t(*SDL_MapRGBA)(const SDL_PixelFormat* format, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) = nullptr;
export inline void (*SDL_GetRGB)(std::uint32_t pixel, const SDL_PixelFormat* format, std::uint8_t* r, std::uint8_t* g, std::uint8_t* b) = nullptr;
export inline void (*SDL_GetRGBA)(std::uint32_t pixel, const SDL_PixelFormat* format, std::uint8_t* r, std::uint8_t* g, std::uint8_t* b, std::uint8_t* a) = nullptr;

// Events
export inline int (*SDL_PollEvent)(SDL_Event* event) = nullptr;
export inline int (*SDL_WaitEvent)(SDL_Event* event) = nullptr;
export inline std::uint8_t(*SDL_GetAppState)() = nullptr;
// Time
export inline std::uint32_t(*SDL_GetTicks)() = nullptr;
export inline void (*SDL_Delay)(std::uint32_t ms) = nullptr;
// Macro aliases from original SDL headers
export inline int SDL_BlitSurface(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) 
{
    return SDL_UpperBlit(src, srcrect, dst, dstrect);
}
// Helper macro function to check if the surface must be locked before accessing pixels directly
export constexpr bool SDL_MUSTLOCK(const SDL_Surface* surface)
{
    return (surface->flags & (SDL_HWSURFACE | SDL_ASYNCBLIT | SDL_RLEACCEL)) != 0;
}