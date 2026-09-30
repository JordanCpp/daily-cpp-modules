// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

export module SDL2.API;

import std;

// ============================================================
// FORWARD DECLARATIONS
// ============================================================

export struct SDL_Window;
export struct SDL_Renderer;
export struct SDL_Texture;
export struct SDL_Surface;
export struct SDL_PixelFormat;
export struct SDL_Palette;
export struct SDL_Joystick;
export struct SDL_GameController;
export struct SDL_Haptic;
export struct SDL_HapticEffect;
export struct SDL_AudioSpec;
export struct SDL_RWops;

// ============================================================
// BASIC TYPES
// ============================================================

export struct SDL_Rect {
    int x, y;
    int w, h;
};

export struct SDL_Point {
    int x, y;
};

export struct SDL_Color {
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a;
};

export struct SDL_Palette {
    int ncolors;
    SDL_Color* colors;
    std::uint32_t version;
    int refcount;
};

// ============================================================
// PIXEL FORMAT
// ============================================================

export struct SDL_PixelFormat {
    std::uint32_t format;
    SDL_Palette* palette;
    std::uint8_t BitsPerPixel;
    std::uint8_t BytesPerPixel;
    std::uint8_t padding[2];
    std::uint32_t Rmask;
    std::uint32_t Gmask;
    std::uint32_t Bmask;
    std::uint32_t Amask;
    std::uint8_t Rloss;
    std::uint8_t Gloss;
    std::uint8_t Bloss;
    std::uint8_t Aloss;
    std::uint8_t Rshift;
    std::uint8_t Gshift;
    std::uint8_t Bshift;
    std::uint8_t Ashift;
    int refcount;
    SDL_PixelFormat* next;
};

// ============================================================
// SURFACE
// ============================================================

export struct SDL_Surface {
    std::uint32_t flags;
    SDL_PixelFormat* format;
    int w, h;
    int pitch;
    void* pixels;
    void* userdata;

    int locked;
    void* lock_data;

    SDL_Rect clip_rect;
    void* map;
    int refcount;
};

// ============================================================
// DISPLAY MODE
// ============================================================

export struct SDL_DisplayMode {
    std::uint32_t format;
    int w, h;
    int refresh_rate;
    void* driverdata;
};

// ============================================================
// AUDIO
// ============================================================

export typedef std::uint32_t SDL_AudioDeviceID;

export struct SDL_AudioSpec {
    int freq;
    std::uint16_t format;
    std::uint8_t channels;
    std::uint8_t silence;
    std::uint16_t samples;
    std::uint16_t padding;
    std::uint32_t size;
    void (*callback)(void* userdata, std::uint8_t* stream, int len);
    void* userdata;
};

// ============================================================
// TIMER
// ============================================================

export typedef int SDL_TimerID;

// ============================================================
// KEYBOARD
// ============================================================

export struct SDL_Keysym {
    std::int32_t scancode;
    std::int32_t sym;
    std::uint16_t mod;
    std::uint32_t unused;
};

// ============================================================
// EVENTS
// ============================================================

export struct SDL_CommonEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
};

export struct SDL_WindowEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::uint32_t windowID;
    std::uint8_t event;
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint8_t padding3;
    std::int32_t data1;
    std::int32_t data2;
};

export struct SDL_KeyboardEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::uint32_t windowID;
    std::uint8_t state;
    std::uint8_t repeat;
    std::uint8_t padding2;
    std::uint8_t padding3;
    SDL_Keysym keysym;
};

export struct SDL_TextEditingEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::uint32_t windowID;
    char text[32];
    std::int32_t start;
    std::int32_t length;
};

export struct SDL_TextInputEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::uint32_t windowID;
    char text[32];
};

export struct SDL_MouseMotionEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::uint32_t windowID;
    std::uint32_t which;
    std::uint32_t state;
    std::int32_t x;
    std::int32_t y;
    std::int32_t xrel;
    std::int32_t yrel;
};

export struct SDL_MouseButtonEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::uint32_t windowID;
    std::uint32_t which;
    std::uint8_t button;
    std::uint8_t state;
    std::uint8_t clicks;
    std::uint8_t padding1;
    std::int32_t x;
    std::int32_t y;
};

export struct SDL_MouseWheelEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::uint32_t windowID;
    std::uint32_t which;
    std::int32_t x;
    std::int32_t y;
    std::uint32_t direction;
};

export struct SDL_JoyAxisEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::int32_t which;
    std::uint8_t axis;
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint8_t padding3;
    std::int16_t value;
    std::uint16_t padding4;
};

export struct SDL_JoyBallEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::int32_t which;
    std::uint8_t ball;
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint8_t padding3;
    std::int16_t xrel;
    std::int16_t yrel;
};

export struct SDL_JoyHatEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::int32_t which;
    std::uint8_t hat;
    std::uint8_t value;
    std::uint8_t padding1;
    std::uint8_t padding2;
};

export struct SDL_JoyButtonEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::int32_t which;
    std::uint8_t button;
    std::uint8_t state;
    std::uint8_t padding1;
    std::uint8_t padding2;
};

export struct SDL_JoyDeviceEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::int32_t which;
};

export struct SDL_ControllerAxisEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::int32_t which;
    std::uint8_t axis;
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint8_t padding3;
    std::int16_t value;
    std::uint16_t padding4;
};

export struct SDL_ControllerButtonEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::int32_t which;
    std::uint8_t button;
    std::uint8_t state;
    std::uint8_t padding1;
    std::uint8_t padding2;
};

export struct SDL_ControllerDeviceEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::int32_t which;
};

export struct SDL_AudioDeviceEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::uint32_t which;
    std::uint8_t iscapture;
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint8_t padding3;
};

export struct SDL_SensorEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::int32_t which;
    float data[6];
};

export struct SDL_QuitEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
};

export struct SDL_UserEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::uint32_t windowID;
    std::int32_t code;
    void* data1;
    void* data2;
};

export struct SDL_SysWMEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    void* msg;
};

export struct SDL_TouchFingerEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::int64_t touchId;
    std::int64_t fingerId;
    float x;
    float y;
    float dx;
    float dy;
    float pressure;
};

export struct SDL_MultiGestureEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::int64_t touchId;
    float dTheta;
    float dDist;
    float x;
    float y;
    std::uint16_t numFingers;
    std::uint16_t padding;
};

export struct SDL_DollarGestureEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::int64_t touchId;
    std::int64_t gestureId;
    std::uint32_t numFingers;
    float error;
    float x;
    float y;
};

export struct SDL_DropEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    char* file;
    std::uint32_t windowID;
};

export union SDL_Event {
    std::uint32_t type;
    SDL_CommonEvent common;
    SDL_WindowEvent window;
    SDL_KeyboardEvent key;
    SDL_TextEditingEvent edit;
    SDL_TextInputEvent text;
    SDL_MouseMotionEvent motion;
    SDL_MouseButtonEvent button;
    SDL_MouseWheelEvent wheel;
    SDL_JoyAxisEvent jaxis;
    SDL_JoyBallEvent jball;
    SDL_JoyHatEvent jhat;
    SDL_JoyButtonEvent jbutton;
    SDL_JoyDeviceEvent jdevice;
    SDL_ControllerAxisEvent caxis;
    SDL_ControllerButtonEvent cbutton;
    SDL_ControllerDeviceEvent cdevice;
    SDL_AudioDeviceEvent adevice;
    SDL_SensorEvent sensor;
    SDL_QuitEvent quit;
    SDL_UserEvent user;
    SDL_SysWMEvent syswm;
    SDL_TouchFingerEvent tfinger;
    SDL_MultiGestureEvent mgesture;
    SDL_DollarGestureEvent dgesture;
    SDL_DropEvent drop;
    std::uint8_t padding[56];
};

// ============================================================
// CONSTANTS
// ============================================================

// Initialization flags
export constexpr std::uint32_t SDL_INIT_TIMER = 0x00000001;
export constexpr std::uint32_t SDL_INIT_AUDIO = 0x00000010;
export constexpr std::uint32_t SDL_INIT_VIDEO = 0x00000020;
export constexpr std::uint32_t SDL_INIT_JOYSTICK = 0x00000200;
export constexpr std::uint32_t SDL_INIT_HAPTIC = 0x00001000;
export constexpr std::uint32_t SDL_INIT_GAMECONTROLLER = 0x00002000;
export constexpr std::uint32_t SDL_INIT_EVENTS = 0x00004000;
export constexpr std::uint32_t SDL_INIT_SENSOR = 0x00008000;
export constexpr std::uint32_t SDL_INIT_NOPARACHUTE = 0x00100000;
export constexpr std::uint32_t SDL_INIT_EVERYTHING = 0x0000FFFF;

// Window flags
export constexpr std::uint32_t SDL_WINDOW_FULLSCREEN = 0x00000001;
export constexpr std::uint32_t SDL_WINDOW_OPENGL = 0x00000002;
export constexpr std::uint32_t SDL_WINDOW_SHOWN = 0x00000004;
export constexpr std::uint32_t SDL_WINDOW_HIDDEN = 0x00000008;
export constexpr std::uint32_t SDL_WINDOW_BORDERLESS = 0x00000010;
export constexpr std::uint32_t SDL_WINDOW_RESIZABLE = 0x00000020;
export constexpr std::uint32_t SDL_WINDOW_MINIMIZED = 0x00000040;
export constexpr std::uint32_t SDL_WINDOW_MAXIMIZED = 0x00000080;
export constexpr std::uint32_t SDL_WINDOW_INPUT_GRABBED = 0x00000100;
export constexpr std::uint32_t SDL_WINDOW_INPUT_FOCUS = 0x00000200;
export constexpr std::uint32_t SDL_WINDOW_MOUSE_FOCUS = 0x00000400;
export constexpr std::uint32_t SDL_WINDOW_FULLSCREEN_DESKTOP = 0x00001001;
export constexpr std::uint32_t SDL_WINDOW_FOREIGN = 0x00000800;
export constexpr std::uint32_t SDL_WINDOW_ALLOW_HIGHDPI = 0x00002000;
export constexpr std::uint32_t SDL_WINDOW_MOUSE_CAPTURE = 0x00004000;
export constexpr std::uint32_t SDL_WINDOW_ALWAYS_ON_TOP = 0x00008000;
export constexpr std::uint32_t SDL_WINDOW_SKIP_TASKBAR = 0x00010000;
export constexpr std::uint32_t SDL_WINDOW_UTILITY = 0x00020000;
export constexpr std::uint32_t SDL_WINDOW_TOOLTIP = 0x00040000;
export constexpr std::uint32_t SDL_WINDOW_POPUP_MENU = 0x00080000;
export constexpr std::uint32_t SDL_WINDOW_VULKAN = 0x10000000;
export constexpr std::uint32_t SDL_WINDOW_METAL = 0x20000000;

// Renderer flags
export constexpr std::uint32_t SDL_RENDERER_SOFTWARE = 0x00000001;
export constexpr std::uint32_t SDL_RENDERER_ACCELERATED = 0x00000002;
export constexpr std::uint32_t SDL_RENDERER_PRESENTVSYNC = 0x00000004;
export constexpr std::uint32_t SDL_RENDERER_TARGETTEXTURE = 0x00000008;

// Texture access
export constexpr int SDL_TEXTUREACCESS_STATIC = 0;
export constexpr int SDL_TEXTUREACCESS_STREAMING = 1;
export constexpr int SDL_TEXTUREACCESS_TARGET = 2;

// Pixel format
export constexpr std::uint32_t SDL_PIXELFORMAT_UNKNOWN = 0;
export constexpr std::uint32_t SDL_PIXELFORMAT_ARGB8888 = 0x16362004;
export constexpr std::uint32_t SDL_PIXELFORMAT_RGBA8888 = 0x16462004;
export constexpr std::uint32_t SDL_PIXELFORMAT_ABGR8888 = 0x16762004;
export constexpr std::uint32_t SDL_PIXELFORMAT_BGRA8888 = 0x16862004;
export constexpr std::uint32_t SDL_PIXELFORMAT_RGB888 = 0x16162004;
export constexpr std::uint32_t SDL_PIXELFORMAT_BGR888 = 0x16562004;
export constexpr std::uint32_t SDL_PIXELFORMAT_RGB565 = 0x15151002;
export constexpr std::uint32_t SDL_PIXELFORMAT_ARGB4444 = 0x15321002;
export constexpr std::uint32_t SDL_PIXELFORMAT_ARGB1555 = 0x15551002;
export constexpr std::uint32_t SDL_PIXELFORMAT_INDEX8 = 0x13000001;

// Event types
export constexpr std::uint32_t SDL_FIRSTEVENT = 0;
export constexpr std::uint32_t SDL_QUIT = 0x100;
export constexpr std::uint32_t SDL_APP_TERMINATING = 0x101;
export constexpr std::uint32_t SDL_APP_LOWMEMORY = 0x102;
export constexpr std::uint32_t SDL_APP_WILLENTERBACKGROUND = 0x103;
export constexpr std::uint32_t SDL_APP_DIDENTERBACKGROUND = 0x104;
export constexpr std::uint32_t SDL_APP_WILLENTERFOREGROUND = 0x105;
export constexpr std::uint32_t SDL_APP_DIDENTERFOREGROUND = 0x106;
export constexpr std::uint32_t SDL_WINDOWEVENT = 0x200;
export constexpr std::uint32_t SDL_SYSWMEVENT = 0x201;
export constexpr std::uint32_t SDL_KEYDOWN = 0x300;
export constexpr std::uint32_t SDL_KEYUP = 0x301;
export constexpr std::uint32_t SDL_TEXTEDITING = 0x302;
export constexpr std::uint32_t SDL_TEXTINPUT = 0x303;
export constexpr std::uint32_t SDL_KEYMAPCHANGED = 0x304;
export constexpr std::uint32_t SDL_MOUSEMOTION = 0x400;
export constexpr std::uint32_t SDL_MOUSEBUTTONDOWN = 0x401;
export constexpr std::uint32_t SDL_MOUSEBUTTONUP = 0x402;
export constexpr std::uint32_t SDL_MOUSEWHEEL = 0x403;
export constexpr std::uint32_t SDL_JOYAXISMOTION = 0x600;
export constexpr std::uint32_t SDL_JOYBALLMOTION = 0x601;
export constexpr std::uint32_t SDL_JOYHATMOTION = 0x602;
export constexpr std::uint32_t SDL_JOYBUTTONDOWN = 0x603;
export constexpr std::uint32_t SDL_JOYBUTTONUP = 0x604;
export constexpr std::uint32_t SDL_JOYDEVICEADDED = 0x605;
export constexpr std::uint32_t SDL_JOYDEVICEREMOVED = 0x606;
export constexpr std::uint32_t SDL_CONTROLLERAXISMOTION = 0x650;
export constexpr std::uint32_t SDL_CONTROLLERBUTTONDOWN = 0x651;
export constexpr std::uint32_t SDL_CONTROLLERBUTTONUP = 0x652;
export constexpr std::uint32_t SDL_CONTROLLERDEVICEADDED = 0x653;
export constexpr std::uint32_t SDL_CONTROLLERDEVICEREMOVED = 0x654;
export constexpr std::uint32_t SDL_CONTROLLERDEVICEREMAPPED = 0x655;
export constexpr std::uint32_t SDL_FINGERDOWN = 0x700;
export constexpr std::uint32_t SDL_FINGERUP = 0x701;
export constexpr std::uint32_t SDL_FINGERMOTION = 0x702;
export constexpr std::uint32_t SDL_DOLLARGESTURE = 0x800;
export constexpr std::uint32_t SDL_DOLLARRECORD = 0x801;
export constexpr std::uint32_t SDL_MULTIGESTURE = 0x802;
export constexpr std::uint32_t SDL_CLIPBOARDUPDATE = 0x900;
export constexpr std::uint32_t SDL_DROPFILE = 0x1000;
export constexpr std::uint32_t SDL_DROPTEXT = 0x1001;
export constexpr std::uint32_t SDL_DROPBEGIN = 0x1002;
export constexpr std::uint32_t SDL_DROPCOMPLETE = 0x1003;
export constexpr std::uint32_t SDL_AUDIODEVICEADDED = 0x1100;
export constexpr std::uint32_t SDL_AUDIODEVICEREMOVED = 0x1101;
export constexpr std::uint32_t SDL_SENSORUPDATE = 0x1200;
export constexpr std::uint32_t SDL_RENDER_TARGETS_RESET = 0x2000;
export constexpr std::uint32_t SDL_RENDER_DEVICE_RESET = 0x2001;
export constexpr std::uint32_t SDL_USEREVENT = 0x8000;
export constexpr std::uint32_t SDL_LASTEVENT = 0xFFFF;

// Window events
export constexpr std::uint8_t SDL_WINDOWEVENT_NONE = 0;
export constexpr std::uint8_t SDL_WINDOWEVENT_SHOWN = 1;
export constexpr std::uint8_t SDL_WINDOWEVENT_HIDDEN = 2;
export constexpr std::uint8_t SDL_WINDOWEVENT_EXPOSED = 3;
export constexpr std::uint8_t SDL_WINDOWEVENT_MOVED = 4;
export constexpr std::uint8_t SDL_WINDOWEVENT_RESIZED = 5;
export constexpr std::uint8_t SDL_WINDOWEVENT_SIZE_CHANGED = 6;
export constexpr std::uint8_t SDL_WINDOWEVENT_MINIMIZED = 7;
export constexpr std::uint8_t SDL_WINDOWEVENT_MAXIMIZED = 8;
export constexpr std::uint8_t SDL_WINDOWEVENT_RESTORED = 9;
export constexpr std::uint8_t SDL_WINDOWEVENT_ENTER = 10;
export constexpr std::uint8_t SDL_WINDOWEVENT_LEAVE = 11;
export constexpr std::uint8_t SDL_WINDOWEVENT_FOCUS_GAINED = 12;
export constexpr std::uint8_t SDL_WINDOWEVENT_FOCUS_LOST = 13;
export constexpr std::uint8_t SDL_WINDOWEVENT_CLOSE = 14;
export constexpr std::uint8_t SDL_WINDOWEVENT_TAKE_FOCUS = 15;
export constexpr std::uint8_t SDL_WINDOWEVENT_HIT_TEST = 16;

// ============================================================
// FUNCTION POINTERS FOR DYNAMIC LOADING
// ============================================================

// --- Initialization, Errors, and Lifecycles ---
export inline int (*SDL_Init)(std::uint32_t flags) = nullptr;
export inline int (*SDL_InitSubSystem)(std::uint32_t flags) = nullptr;
export inline void (*SDL_QuitSubSystem)(std::uint32_t flags) = nullptr;
export inline std::uint32_t(*SDL_WasInit)(std::uint32_t flags) = nullptr;
export inline void (*SDL_Quit)() = nullptr;
export inline const char* (*SDL_GetError)() = nullptr;
export inline void (*SDL_ClearError)() = nullptr;

// --- Window management ---
export inline SDL_Window* (*SDL_CreateWindow)(const char* title, int x, int y, int w, int h, std::uint32_t flags) = nullptr;
export inline void (*SDL_DestroyWindow)(SDL_Window* window) = nullptr;
export inline void (*SDL_SetWindowTitle)(SDL_Window* window, const char* title) = nullptr;
export inline const char* (*SDL_GetWindowTitle)(SDL_Window* window) = nullptr;
export inline void (*SDL_SetWindowSize)(SDL_Window* window, int w, int h) = nullptr;
export inline void (*SDL_GetWindowSize)(SDL_Window* window, int* w, int* h) = nullptr;
export inline void (*SDL_ShowWindow)(SDL_Window* window) = nullptr;
export inline void (*SDL_HideWindow)(SDL_Window* window) = nullptr;
export inline void (*SDL_RaiseWindow)(SDL_Window* window) = nullptr;
export inline void (*SDL_MaximizeWindow)(SDL_Window* window) = nullptr;
export inline void (*SDL_MinimizeWindow)(SDL_Window* window) = nullptr;
export inline void (*SDL_RestoreWindow)(SDL_Window* window) = nullptr;
export inline int (*SDL_SetWindowFullscreen)(SDL_Window* window, std::uint32_t flags) = nullptr;
export inline SDL_Surface* (*SDL_GetWindowSurface)(SDL_Window* window) = nullptr;
export inline int (*SDL_UpdateWindowSurface)(SDL_Window* window) = nullptr;
export inline int (*SDL_UpdateWindowSurfaceRects)(SDL_Window* window, SDL_Rect* rects, int numrects) = nullptr;

// --- Renderer ---
export inline SDL_Renderer* (*SDL_CreateRenderer)(SDL_Window* window, int index, std::uint32_t flags) = nullptr;
export inline void (*SDL_DestroyRenderer)(SDL_Renderer* renderer) = nullptr;
export inline int (*SDL_SetRenderDrawColor)(SDL_Renderer* renderer, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) = nullptr;
export inline int (*SDL_GetRenderDrawColor)(SDL_Renderer* renderer, std::uint8_t* r, std::uint8_t* g, std::uint8_t* b, std::uint8_t* a) = nullptr;
export inline int (*SDL_RenderClear)(SDL_Renderer* renderer) = nullptr;
export inline void (*SDL_RenderPresent)(SDL_Renderer* renderer) = nullptr;
export inline int (*SDL_RenderFillRect)(SDL_Renderer* renderer, const SDL_Rect* rect) = nullptr;
export inline int (*SDL_RenderDrawRect)(SDL_Renderer* renderer, const SDL_Rect* rect) = nullptr;
export inline int (*SDL_RenderDrawLine)(SDL_Renderer* renderer, int x1, int y1, int x2, int y2) = nullptr;
export inline int (*SDL_RenderDrawPoint)(SDL_Renderer* renderer, int x, int y) = nullptr;
export inline int (*SDL_RenderCopy)(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect) = nullptr;
export inline int (*SDL_RenderCopyEx)(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, double angle, const SDL_Point* center, int flip) = nullptr;
export inline void (*SDL_RenderSetClipRect)(SDL_Renderer* renderer, const SDL_Rect* rect) = nullptr;
export inline void (*SDL_RenderGetClipRect)(SDL_Renderer* renderer, SDL_Rect* rect) = nullptr;
export inline int (*SDL_RenderSetLogicalSize)(SDL_Renderer* renderer, int w, int h) = nullptr;
export inline void (*SDL_RenderGetLogicalSize)(SDL_Renderer* renderer, int* w, int* h) = nullptr;
export inline int (*SDL_RenderSetViewport)(SDL_Renderer* renderer, const SDL_Rect* rect) = nullptr;
export inline void (*SDL_RenderGetViewport)(SDL_Renderer* renderer, SDL_Rect* rect) = nullptr;
export inline int (*SDL_RenderSetScale)(SDL_Renderer* renderer, float scaleX, float scaleY) = nullptr;
export inline void (*SDL_RenderGetScale)(SDL_Renderer* renderer, float* scaleX, float* scaleY) = nullptr;
export inline int (*SDL_SetRenderTarget)(SDL_Renderer* renderer, SDL_Texture* texture) = nullptr;
export inline SDL_Texture* (*SDL_GetRenderTarget)(SDL_Renderer* renderer) = nullptr;

// --- Textures ---
export inline SDL_Texture* (*SDL_CreateTexture)(SDL_Renderer* renderer, std::uint32_t format, int access, int w, int h) = nullptr;
export inline SDL_Texture* (*SDL_CreateTextureFromSurface)(SDL_Renderer* renderer, SDL_Surface* surface) = nullptr;
export inline void (*SDL_DestroyTexture)(SDL_Texture* texture) = nullptr;
export inline int (*SDL_QueryTexture)(SDL_Texture* texture, std::uint32_t* format, int* access, int* w, int* h) = nullptr;
export inline int (*SDL_SetTextureColorMod)(SDL_Texture* texture, std::uint8_t r, std::uint8_t g, std::uint8_t b) = nullptr;
export inline int (*SDL_GetTextureColorMod)(SDL_Texture* texture, std::uint8_t* r, std::uint8_t* g, std::uint8_t* b) = nullptr;
export inline int (*SDL_SetTextureAlphaMod)(SDL_Texture* texture, std::uint8_t alpha) = nullptr;
export inline int (*SDL_GetTextureAlphaMod)(SDL_Texture* texture, std::uint8_t* alpha) = nullptr;
export inline int (*SDL_SetTextureBlendMode)(SDL_Texture* texture, int blendMode) = nullptr;
export inline int (*SDL_GetTextureBlendMode)(SDL_Texture* texture, int* blendMode) = nullptr;
export inline int (*SDL_UpdateTexture)(SDL_Texture* texture, const SDL_Rect* rect, const void* pixels, int pitch) = nullptr;
export inline int (*SDL_LockTexture)(SDL_Texture* texture, const SDL_Rect* rect, void** pixels, int* pitch) = nullptr;
export inline void (*SDL_UnlockTexture)(SDL_Texture* texture) = nullptr;

// --- Surface management (SDL 1.2 compatible wrappers) ---
export inline SDL_Surface* (*SDL_CreateRGBSurface)(std::uint32_t flags, int width, int height, int depth, std::uint32_t Rmask, std::uint32_t Gmask, std::uint32_t Bmask, std::uint32_t Amask) = nullptr;
export inline SDL_Surface* (*SDL_CreateRGBSurfaceFrom)(void* pixels, int width, int height, int depth, int pitch, std::uint32_t Rmask, std::uint32_t Gmask, std::uint32_t Bmask, std::uint32_t Amask) = nullptr;
export inline void (*SDL_FreeSurface)(SDL_Surface* surface) = nullptr;
export inline int (*SDL_LockSurface)(SDL_Surface* surface) = nullptr;
export inline void (*SDL_UnlockSurface)(SDL_Surface* surface) = nullptr;
export inline int (*SDL_SaveBMP)(SDL_Surface* surface, const char* file) = nullptr;
export inline SDL_Surface* (*SDL_LoadBMP)(const char* file) = nullptr;
export inline int (*SDL_SetSurfacePalette)(SDL_Surface* surface, SDL_Palette* palette) = nullptr;
export inline int (*SDL_SetSurfaceRLE)(SDL_Surface* surface, int flag) = nullptr;
export inline int (*SDL_SetColorKey)(SDL_Surface* surface, int flag, std::uint32_t key) = nullptr;
export inline int (*SDL_GetColorKey)(SDL_Surface* surface, std::uint32_t* key) = nullptr;
export inline int (*SDL_SetSurfaceColorMod)(SDL_Surface* surface, std::uint8_t r, std::uint8_t g, std::uint8_t b) = nullptr;
export inline int (*SDL_GetSurfaceColorMod)(SDL_Surface* surface, std::uint8_t* r, std::uint8_t* g, std::uint8_t* b) = nullptr;
export inline int (*SDL_SetSurfaceAlphaMod)(SDL_Surface* surface, std::uint8_t alpha) = nullptr;
export inline int (*SDL_GetSurfaceAlphaMod)(SDL_Surface* surface, std::uint8_t* alpha) = nullptr;
export inline int (*SDL_SetSurfaceBlendMode)(SDL_Surface* surface, int blendMode) = nullptr;
export inline int (*SDL_GetSurfaceBlendMode)(SDL_Surface* surface, int* blendMode) = nullptr;
export inline int (*SDL_SetSurfaceClipRect)(SDL_Surface* surface, const SDL_Rect* rect) = nullptr;
export inline int (*SDL_GetSurfaceClipRect)(SDL_Surface* surface, SDL_Rect* rect) = nullptr;
export inline int (*SDL_ConvertPixels)(int width, int height, std::uint32_t src_format, const void* src, int src_pitch, std::uint32_t dst_format, void* dst, int dst_pitch) = nullptr;
export inline int (*SDL_FillRect)(SDL_Surface* dst, const SDL_Rect* rect, std::uint32_t color) = nullptr;
export inline int (*SDL_FillRects)(SDL_Surface* dst, const SDL_Rect* rects, int count, std::uint32_t color) = nullptr;
export inline int (*SDL_BlitSurface)(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) = nullptr;
export inline int (*SDL_BlitScaled)(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) = nullptr;
export inline int (*SDL_UpperBlit)(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) = nullptr;
export inline int (*SDL_LowerBlit)(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) = nullptr;
export inline int (*SDL_SoftStretch)(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, const SDL_Rect* dstrect) = nullptr;

// --- Pixel operations ---
export inline std::uint32_t(*SDL_MapRGB)(const SDL_PixelFormat* format, std::uint8_t r, std::uint8_t g, std::uint8_t b) = nullptr;
export inline std::uint32_t(*SDL_MapRGBA)(const SDL_PixelFormat* format, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) = nullptr;
export inline void (*SDL_GetRGB)(std::uint32_t pixel, const SDL_PixelFormat* format, std::uint8_t* r, std::uint8_t* g, std::uint8_t* b) = nullptr;
export inline void (*SDL_GetRGBA)(std::uint32_t pixel, const SDL_PixelFormat* format, std::uint8_t* r, std::uint8_t* g, std::uint8_t* b, std::uint8_t* a) = nullptr;
export inline SDL_PixelFormat* (*SDL_AllocFormat)(std::uint32_t pixel_format) = nullptr;
export inline void (*SDL_FreeFormat)(SDL_PixelFormat* format) = nullptr;
export inline SDL_Palette* (*SDL_AllocPalette)(int ncolors) = nullptr;
export inline int (*SDL_SetPaletteColors)(SDL_Palette* palette, const SDL_Color* colors, int firstcolor, int ncolors) = nullptr;
export inline void (*SDL_FreePalette)(SDL_Palette* palette) = nullptr;

// --- Events ---
export inline void (*SDL_PumpEvents)() = nullptr;
export inline int (*SDL_PollEvent)(SDL_Event* event) = nullptr;
export inline int (*SDL_WaitEvent)(SDL_Event* event) = nullptr;
export inline int (*SDL_WaitEventTimeout)(SDL_Event* event, int timeout) = nullptr;
export inline int (*SDL_PushEvent)(SDL_Event* event) = nullptr;
export inline void (*SDL_SetEventFilter)(int (*filter)(void* userdata, SDL_Event* event), void* userdata) = nullptr;
export inline int (*SDL_GetEventFilter)(int (**filter)(void* userdata, SDL_Event* event), void** userdata) = nullptr;
export inline void (*SDL_AddEventWatch)(int (*filter)(void* userdata, SDL_Event* event), void* userdata) = nullptr;
export inline void (*SDL_DelEventWatch)(int (*filter)(void* userdata, SDL_Event* event), void* userdata) = nullptr;
export inline void (*SDL_EventState)(std::uint32_t type, int state) = nullptr;
export inline std::uint32_t(*SDL_RegisterEvents)(int numevents) = nullptr;

// --- Keyboard ---
export inline const std::uint8_t* (*SDL_GetKeyboardState)(int* numkeys) = nullptr;
export inline int (*SDL_GetKeyFromScancode)(std::int32_t scancode) = nullptr;
export inline std::int32_t(*SDL_GetScancodeFromKey)(int key) = nullptr;
export inline const char* (*SDL_GetScancodeName)(std::int32_t scancode) = nullptr;
export inline std::int32_t(*SDL_GetScancodeFromName)(const char* name) = nullptr;
export inline const char* (*SDL_GetKeyName)(int key) = nullptr;
export inline int (*SDL_GetKeyFromName)(const char* name) = nullptr;
export inline void (*SDL_StartTextInput)() = nullptr;
export inline int (*SDL_IsTextInputActive)() = nullptr;
export inline void (*SDL_StopTextInput)() = nullptr;
export inline void (*SDL_SetTextInputRect)(SDL_Rect* rect) = nullptr;

// --- Mouse ---
export inline std::uint32_t(*SDL_GetMouseState)(int* x, int* y) = nullptr;
export inline std::uint32_t(*SDL_GetGlobalMouseState)(int* x, int* y) = nullptr;
export inline std::uint32_t(*SDL_GetRelativeMouseState)(int* x, int* y) = nullptr;
export inline void (*SDL_WarpMouseInWindow)(SDL_Window* window, int x, int y) = nullptr;
export inline int (*SDL_SetRelativeMouseMode)(int enabled) = nullptr;
export inline int (*SDL_GetRelativeMouseMode)() = nullptr;
export inline int (*SDL_ShowCursor)(int toggle) = nullptr;

// --- Joystick ---
export inline SDL_Joystick* (*SDL_JoystickOpen)(int device_index) = nullptr;
export inline void (*SDL_JoystickClose)(SDL_Joystick* joystick) = nullptr;
export inline const char* (*SDL_JoystickName)(SDL_Joystick* joystick) = nullptr;
export inline int (*SDL_JoystickNumAxes)(SDL_Joystick* joystick) = nullptr;
export inline int (*SDL_JoystickNumBalls)(SDL_Joystick* joystick) = nullptr;
export inline int (*SDL_JoystickNumHats)(SDL_Joystick* joystick) = nullptr;
export inline int (*SDL_JoystickNumButtons)(SDL_Joystick* joystick) = nullptr;
export inline std::int16_t(*SDL_JoystickGetAxis)(SDL_Joystick* joystick, int axis) = nullptr;
export inline std::uint8_t(*SDL_JoystickGetHat)(SDL_Joystick* joystick, int hat) = nullptr;
export inline int (*SDL_JoystickGetBall)(SDL_Joystick* joystick, int ball, int* dx, int* dy) = nullptr;
export inline std::uint8_t(*SDL_JoystickGetButton)(SDL_Joystick* joystick, int button) = nullptr;
export inline int (*SDL_NumJoysticks)() = nullptr;
export inline void (*SDL_JoystickUpdate)() = nullptr;
export inline int (*SDL_JoystickEventState)(int state) = nullptr;

// --- Game Controller ---
export inline SDL_GameController* (*SDL_GameControllerOpen)(int joystick_index) = nullptr;
export inline void (*SDL_GameControllerClose)(SDL_GameController* gamecontroller) = nullptr;
export inline const char* (*SDL_GameControllerName)(SDL_GameController* gamecontroller) = nullptr;
export inline std::int16_t(*SDL_GameControllerGetAxis)(SDL_GameController* gamecontroller, int axis) = nullptr;
export inline std::uint8_t(*SDL_GameControllerGetButton)(SDL_GameController* gamecontroller, int button) = nullptr;
export inline int (*SDL_GameControllerEventState)(int state) = nullptr;
export inline void (*SDL_GameControllerUpdate)() = nullptr;
export inline int (*SDL_IsGameController)(int joystick_index) = nullptr;
export inline const char* (*SDL_GameControllerNameForIndex)(int joystick_index) = nullptr;

// --- Timer ---
export inline std::uint32_t(*SDL_GetTicks)() = nullptr;
export inline std::uint64_t(*SDL_GetPerformanceCounter)() = nullptr;
export inline std::uint64_t(*SDL_GetPerformanceFrequency)() = nullptr;
export inline void (*SDL_Delay)(std::uint32_t ms) = nullptr;
export inline SDL_TimerID(*SDL_AddTimer)(std::uint32_t interval, std::uint32_t(*callback)(std::uint32_t, void*), void* param) = nullptr;
export inline bool (*SDL_RemoveTimer)(SDL_TimerID id) = nullptr;

// --- Audio ---
export inline int (*SDL_OpenAudio)(SDL_AudioSpec* desired, SDL_AudioSpec* obtained) = nullptr;
export inline void (*SDL_CloseAudio)() = nullptr;
export inline void (*SDL_PauseAudio)(int pause_on) = nullptr;
export inline int (*SDL_GetAudioStatus)() = nullptr;
export inline char* (*SDL_GetAudioDeviceName)(int index, int iscapture) = nullptr;
export inline SDL_AudioDeviceID(*SDL_OpenAudioDevice)(const char* device, int iscapture, const SDL_AudioSpec* desired, SDL_AudioSpec* obtained, int allowed_changes) = nullptr;
export inline void (*SDL_CloseAudioDevice)(SDL_AudioDeviceID dev) = nullptr;
export inline void (*SDL_PauseAudioDevice)(SDL_AudioDeviceID dev, int pause_on) = nullptr;
export inline int (*SDL_QueueAudio)(SDL_AudioDeviceID dev, const void* data, std::uint32_t len) = nullptr;
export inline std::uint32_t(*SDL_DequeueAudio)(SDL_AudioDeviceID dev, void* data, std::uint32_t len) = nullptr;
export inline std::uint32_t(*SDL_GetQueuedAudioSize)(SDL_AudioDeviceID dev) = nullptr;
export inline void (*SDL_ClearQueuedAudio)(SDL_AudioDeviceID dev) = nullptr;

// --- Haptic ---
export inline SDL_Haptic* (*SDL_HapticOpen)(int device_index) = nullptr;
export inline void (*SDL_HapticClose)(SDL_Haptic* haptic) = nullptr;
export inline int (*SDL_HapticNumEffects)(SDL_Haptic* haptic) = nullptr;
export inline int (*SDL_HapticNumEffectsPlaying)(SDL_Haptic* haptic) = nullptr;
export inline unsigned int (*SDL_HapticQuery)(SDL_Haptic* haptic) = nullptr;
export inline int (*SDL_HapticEffectSupported)(SDL_Haptic* haptic, SDL_HapticEffect* effect) = nullptr;
export inline int (*SDL_HapticNewEffect)(SDL_Haptic* haptic, SDL_HapticEffect* effect) = nullptr;
export inline int (*SDL_HapticRunEffect)(SDL_Haptic* haptic, int effect, std::uint32_t iterations) = nullptr;
export inline int (*SDL_HapticStopEffect)(SDL_Haptic* haptic, int effect) = nullptr;
export inline void (*SDL_HapticDestroyEffect)(SDL_Haptic* haptic, int effect) = nullptr;
export inline int (*SDL_HapticGetEffectStatus)(SDL_Haptic* haptic, int effect) = nullptr;
export inline int (*SDL_HapticSetGain)(SDL_Haptic* haptic, int gain) = nullptr;
export inline int (*SDL_HapticSetAutocenter)(SDL_Haptic* haptic, int autocenter) = nullptr;

// --- Clipboard ---
export inline int (*SDL_SetClipboardText)(const char* text) = nullptr;
export inline char* (*SDL_GetClipboardText)() = nullptr;
export inline int (*SDL_HasClipboardText)() = nullptr;

// --- CPU Info ---
export inline int (*SDL_GetCPUCount)() = nullptr;
export inline int (*SDL_GetCPUCacheLineSize)() = nullptr;
export inline int (*SDL_HasRDTSC)() = nullptr;
export inline int (*SDL_HasAltiVec)() = nullptr;
export inline int (*SDL_HasMMX)() = nullptr;
export inline int (*SDL_Has3DNow)() = nullptr;
export inline int (*SDL_HasSSE)() = nullptr;
export inline int (*SDL_HasSSE2)() = nullptr;
export inline int (*SDL_HasSSE3)() = nullptr;
export inline int (*SDL_HasSSE41)() = nullptr;
export inline int (*SDL_HasSSE42)() = nullptr;
export inline int (*SDL_HasAVX)() = nullptr;
export inline int (*SDL_HasAVX2)() = nullptr;
export inline int (*SDL_HasAVX512F)() = nullptr;
export inline int (*SDL_HasARMSIMD)() = nullptr;
export inline int (*SDL_HasNEON)() = nullptr;

// --- Power management ---
export inline int (*SDL_GetPowerInfo)(int* secs, int* pct) = nullptr;

// --- Platform ---
export inline const char* (*SDL_GetPlatform)() = nullptr;
