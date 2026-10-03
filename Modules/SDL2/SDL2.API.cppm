// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

export module SDL2.API;

import std;

export inline constexpr std::uint32_t SDL_WINDOWPOS_MASK = 0x2FFF0000U;
export inline constexpr std::uint32_t SDL_WINDOWPOS_CENTERED = SDL_WINDOWPOS_MASK | 0U;

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
export inline int (*SDL_RenderDrawLines)(SDL_Renderer* renderer, const SDL_Point* points, int count) = nullptr;
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
export inline int (*SDL_ConvertPixels)(int width, int height, std::uint32_t src_format, const void* src, int src_pitch, std::uint32_t dst_format, void* dst, int dst_pitch) = nullptr;
export inline int (*SDL_FillRect)(SDL_Surface* dst, const SDL_Rect* rect, std::uint32_t color) = nullptr;
export inline int (*SDL_FillRects)(SDL_Surface* dst, const SDL_Rect* rects, int count, std::uint32_t color) = nullptr;
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

export constexpr auto SDL_BUTTON(std::uint32_t X) noexcept -> std::uint32_t
{
    return 1U << (X - 1U);
}

export 
{
    constexpr std::uint32_t SDL_BUTTON_LEFT = 1;
    constexpr std::uint32_t SDL_BUTTON_MIDDLE = 2;
    constexpr std::uint32_t SDL_BUTTON_RIGHT = 3;
    constexpr std::uint32_t SDL_BUTTON_X1 = 4;
    constexpr std::uint32_t SDL_BUTTON_X2 = 5;

    constexpr std::uint32_t SDL_BUTTON_LMASK = SDL_BUTTON(SDL_BUTTON_LEFT);
    constexpr std::uint32_t SDL_BUTTON_MMASK = SDL_BUTTON(SDL_BUTTON_MIDDLE);
    constexpr std::uint32_t SDL_BUTTON_RMASK = SDL_BUTTON(SDL_BUTTON_RIGHT);
    constexpr std::uint32_t SDL_BUTTON_X1MASK = SDL_BUTTON(SDL_BUTTON_X1);
    constexpr std::uint32_t SDL_BUTTON_X2MASK = SDL_BUTTON(SDL_BUTTON_X2);
}

export 
{
    using SDL_Keycode = std::int32_t;

    constexpr std::int32_t SDLK_SCANCODE_MASK = (1 << 30);
}

export constexpr auto SDL_SCANCODE_TO_KEYCODE(std::int32_t X) noexcept -> std::int32_t 
{
    return X | SDLK_SCANCODE_MASK;
}

export enum : int
{
    SDL_SCANCODE_UNKNOWN = 0,

    SDL_SCANCODE_A = 4,
    SDL_SCANCODE_B = 5,
    SDL_SCANCODE_C = 6,
    SDL_SCANCODE_D = 7,
    SDL_SCANCODE_E = 8,
    SDL_SCANCODE_F = 9,
    SDL_SCANCODE_G = 10,
    SDL_SCANCODE_H = 11,
    SDL_SCANCODE_I = 12,
    SDL_SCANCODE_J = 13,
    SDL_SCANCODE_K = 14,
    SDL_SCANCODE_L = 15,
    SDL_SCANCODE_M = 16,
    SDL_SCANCODE_N = 17,
    SDL_SCANCODE_O = 18,
    SDL_SCANCODE_P = 19,
    SDL_SCANCODE_Q = 20,
    SDL_SCANCODE_R = 21,
    SDL_SCANCODE_S = 22,
    SDL_SCANCODE_T = 23,
    SDL_SCANCODE_U = 24,
    SDL_SCANCODE_V = 25,
    SDL_SCANCODE_W = 26,
    SDL_SCANCODE_X = 27,
    SDL_SCANCODE_Y = 28,
    SDL_SCANCODE_Z = 29,

    SDL_SCANCODE_1 = 30,
    SDL_SCANCODE_2 = 31,
    SDL_SCANCODE_3 = 32,
    SDL_SCANCODE_4 = 33,
    SDL_SCANCODE_5 = 34,
    SDL_SCANCODE_6 = 35,
    SDL_SCANCODE_7 = 36,
    SDL_SCANCODE_8 = 37,
    SDL_SCANCODE_9 = 38,
    SDL_SCANCODE_0 = 39,

    SDL_SCANCODE_RETURN = 40,
    SDL_SCANCODE_ESCAPE = 41,
    SDL_SCANCODE_BACKSPACE = 42,
    SDL_SCANCODE_TAB = 43,
    SDL_SCANCODE_SPACE = 44,

    SDL_SCANCODE_MINUS = 45,
    SDL_SCANCODE_EQUALS = 46,
    SDL_SCANCODE_LEFTBRACKET = 47,
    SDL_SCANCODE_RIGHTBRACKET = 48,
    SDL_SCANCODE_BACKSLASH = 49,
    SDL_SCANCODE_NONUSHASH = 50,
    SDL_SCANCODE_SEMICOLON = 51,
    SDL_SCANCODE_APOSTROPHE = 52,
    SDL_SCANCODE_GRAVE = 53,
    SDL_SCANCODE_COMMA = 54,
    SDL_SCANCODE_PERIOD = 55,
    SDL_SCANCODE_SLASH = 56,

    SDL_SCANCODE_CAPSLOCK = 57,

    SDL_SCANCODE_F1 = 58,
    SDL_SCANCODE_F2 = 59,
    SDL_SCANCODE_F3 = 60,
    SDL_SCANCODE_F4 = 61,
    SDL_SCANCODE_F5 = 62,
    SDL_SCANCODE_F6 = 63,
    SDL_SCANCODE_F7 = 64,
    SDL_SCANCODE_F8 = 65,
    SDL_SCANCODE_F9 = 66,
    SDL_SCANCODE_F10 = 67,
    SDL_SCANCODE_F11 = 68,
    SDL_SCANCODE_F12 = 69,

    SDL_SCANCODE_PRINTSCREEN = 70,
    SDL_SCANCODE_SCROLLLOCK = 71,
    SDL_SCANCODE_PAUSE = 72,
    SDL_SCANCODE_INSERT = 73,
    SDL_SCANCODE_HOME = 74,
    SDL_SCANCODE_PAGEUP = 75,
    SDL_SCANCODE_DELETE = 76,
    SDL_SCANCODE_END = 77,
    SDL_SCANCODE_PAGEDOWN = 78,
    SDL_SCANCODE_RIGHT = 79,
    SDL_SCANCODE_LEFT = 80,
    SDL_SCANCODE_DOWN = 81,
    SDL_SCANCODE_UP = 82,

    SDL_SCANCODE_NUMLOCKCLEAR = 83,
    SDL_SCANCODE_KP_DIVIDE = 84,
    SDL_SCANCODE_KP_MULTIPLY = 85,
    SDL_SCANCODE_KP_MINUS = 86,
    SDL_SCANCODE_KP_PLUS = 87,
    SDL_SCANCODE_KP_ENTER = 88,
    SDL_SCANCODE_KP_1 = 89,
    SDL_SCANCODE_KP_2 = 90,
    SDL_SCANCODE_KP_3 = 91,
    SDL_SCANCODE_KP_4 = 92,
    SDL_SCANCODE_KP_5 = 93,
    SDL_SCANCODE_KP_6 = 94,
    SDL_SCANCODE_KP_7 = 95,
    SDL_SCANCODE_KP_8 = 96,
    SDL_SCANCODE_KP_9 = 97,
    SDL_SCANCODE_KP_0 = 98,
    SDL_SCANCODE_KP_PERIOD = 99,

    SDL_SCANCODE_NONUSBACKSLASH = 100,
    SDL_SCANCODE_APPLICATION = 101,
    SDL_SCANCODE_POWER = 102,
    SDL_SCANCODE_KP_EQUALS = 103,
    SDL_SCANCODE_F13 = 104,
    SDL_SCANCODE_F14 = 105,
    SDL_SCANCODE_F15 = 106,
    SDL_SCANCODE_F16 = 107,
    SDL_SCANCODE_F17 = 108,
    SDL_SCANCODE_F18 = 109,
    SDL_SCANCODE_F19 = 110,
    SDL_SCANCODE_F20 = 111,
    SDL_SCANCODE_F21 = 112,
    SDL_SCANCODE_F22 = 113,
    SDL_SCANCODE_F23 = 114,
    SDL_SCANCODE_F24 = 115,
    SDL_SCANCODE_EXECUTE = 116,
    SDL_SCANCODE_HELP = 117,
    SDL_SCANCODE_MENU = 118,
    SDL_SCANCODE_SELECT = 119,
    SDL_SCANCODE_STOP = 120,
    SDL_SCANCODE_AGAIN = 121,
    SDL_SCANCODE_UNDO = 122,
    SDL_SCANCODE_CUT = 123,
    SDL_SCANCODE_COPY = 124,
    SDL_SCANCODE_PASTE = 125,
    SDL_SCANCODE_FIND = 126,
    SDL_SCANCODE_MUTE = 127,
    SDL_SCANCODE_VOLUMEUP = 128,
    SDL_SCANCODE_VOLUMEDOWN = 129,
    SDL_SCANCODE_KP_COMMA = 133,
    SDL_SCANCODE_KP_EQUALSAS400 = 134,

    SDL_SCANCODE_INTERNATIONAL1 = 135,
    SDL_SCANCODE_INTERNATIONAL2 = 136,
    SDL_SCANCODE_INTERNATIONAL3 = 137,
    SDL_SCANCODE_INTERNATIONAL4 = 138,
    SDL_SCANCODE_INTERNATIONAL5 = 139,
    SDL_SCANCODE_INTERNATIONAL6 = 140,
    SDL_SCANCODE_INTERNATIONAL7 = 141,
    SDL_SCANCODE_INTERNATIONAL8 = 142,
    SDL_SCANCODE_INTERNATIONAL9 = 143,
    SDL_SCANCODE_LANG1 = 144,
    SDL_SCANCODE_LANG2 = 145,
    SDL_SCANCODE_LANG3 = 146,
    SDL_SCANCODE_LANG4 = 147,
    SDL_SCANCODE_LANG5 = 148,
    SDL_SCANCODE_LANG6 = 149,
    SDL_SCANCODE_LANG7 = 150,
    SDL_SCANCODE_LANG8 = 151,
    SDL_SCANCODE_LANG9 = 152,

    SDL_SCANCODE_ALTERASE = 153,
    SDL_SCANCODE_SYSREQ = 154,
    SDL_SCANCODE_CANCEL = 155,
    SDL_SCANCODE_CLEAR = 156,
    SDL_SCANCODE_PRIOR = 157,
    SDL_SCANCODE_RETURN2 = 158,
    SDL_SCANCODE_SEPARATOR = 159,
    SDL_SCANCODE_OUT = 160,
    SDL_SCANCODE_OPER = 161,
    SDL_SCANCODE_CLEARAGAIN = 162,
    SDL_SCANCODE_CRSEL = 163,
    SDL_SCANCODE_EXSEL = 164,

    SDL_SCANCODE_KP_00 = 176,
    SDL_SCANCODE_KP_000 = 177,
    SDL_SCANCODE_THOUSANDSSEPARATOR = 178,
    SDL_SCANCODE_DECIMALSEPARATOR = 179,
    SDL_SCANCODE_CURRENCYUNIT = 180,
    SDL_SCANCODE_CURRENCYSUBUNIT = 181,
    SDL_SCANCODE_KP_LEFTPAREN = 182,
    SDL_SCANCODE_KP_RIGHTPAREN = 183,
    SDL_SCANCODE_KP_LEFTBRACE = 184,
    SDL_SCANCODE_KP_RIGHTBRACE = 185,
    SDL_SCANCODE_KP_TAB = 186,
    SDL_SCANCODE_KP_BACKSPACE = 187,
    SDL_SCANCODE_KP_A = 188,
    SDL_SCANCODE_KP_B = 189,
    SDL_SCANCODE_KP_C = 190,
    SDL_SCANCODE_KP_D = 191,
    SDL_SCANCODE_KP_E = 192,
    SDL_SCANCODE_KP_F = 193,
    SDL_SCANCODE_KP_XOR = 194,
    SDL_SCANCODE_KP_POWER = 195,
    SDL_SCANCODE_KP_PERCENT = 196,
    SDL_SCANCODE_KP_LESS = 197,
    SDL_SCANCODE_KP_GREATER = 198,
    SDL_SCANCODE_KP_AMPERSAND = 199,
    SDL_SCANCODE_KP_DBLAMPERSAND = 200,
    SDL_SCANCODE_KP_VERTICALBAR = 201,
    SDL_SCANCODE_KP_DBLVERTICALBAR = 202,
    SDL_SCANCODE_KP_COLON = 203,
    SDL_SCANCODE_KP_HASH = 204,
    SDL_SCANCODE_KP_SPACE = 205,
    SDL_SCANCODE_KP_AT = 206,
    SDL_SCANCODE_KP_EXCLAM = 207,
    SDL_SCANCODE_KP_MEMSTORE = 208,
    SDL_SCANCODE_KP_MEMRECALL = 209,
    SDL_SCANCODE_KP_MEMCLEAR = 210,
    SDL_SCANCODE_KP_MEMADD = 211,
    SDL_SCANCODE_KP_MEMSUBTRACT = 212,
    SDL_SCANCODE_KP_MEMMULTIPLY = 213,
    SDL_SCANCODE_KP_MEMDIVIDE = 214,
    SDL_SCANCODE_KP_PLUSMINUS = 215,
    SDL_SCANCODE_KP_CLEAR = 216,
    SDL_SCANCODE_KP_CLEARENTRY = 217,
    SDL_SCANCODE_KP_BINARY = 218,
    SDL_SCANCODE_KP_OCTAL = 219,
    SDL_SCANCODE_KP_DECIMAL = 220,
    SDL_SCANCODE_KP_HEXADECIMAL = 221,

    SDL_SCANCODE_LCTRL = 224,
    SDL_SCANCODE_LSHIFT = 225,
    SDL_SCANCODE_LALT = 226,
    SDL_SCANCODE_LGUI = 227,
    SDL_SCANCODE_RCTRL = 228,
    SDL_SCANCODE_RSHIFT = 229,
    SDL_SCANCODE_RALT = 230,
    SDL_SCANCODE_RGUI = 231,

    SDL_SCANCODE_MODE = 257,

    SDL_SCANCODE_AUDIONEXT = 258,
    SDL_SCANCODE_AUDIOPREV = 259,
    SDL_SCANCODE_AUDIOSTOP = 260,
    SDL_SCANCODE_AUDIOPLAY = 261,
    SDL_SCANCODE_AUDIOMUTE = 262,
    SDL_SCANCODE_MEDIASELECT = 263,
    SDL_SCANCODE_WWW = 264,
    SDL_SCANCODE_MAIL = 265,
    SDL_SCANCODE_CALCULATOR = 266,
    SDL_SCANCODE_COMPUTER = 267,
    SDL_SCANCODE_AC_SEARCH = 268,
    SDL_SCANCODE_AC_HOME = 269,
    SDL_SCANCODE_AC_BACK = 270,
    SDL_SCANCODE_AC_FORWARD = 271,
    SDL_SCANCODE_AC_STOP = 272,
    SDL_SCANCODE_AC_REFRESH = 273,
    SDL_SCANCODE_AC_BOOKMARKS = 274,

    SDL_SCANCODE_BRIGHTNESSDOWN = 275,
    SDL_SCANCODE_BRIGHTNESSUP = 276,
    SDL_SCANCODE_DISPLAYSWITCH = 277,
    SDL_SCANCODE_KBDILLUMTOGGLE = 278,
    SDL_SCANCODE_KBDILLUMDOWN = 279,
    SDL_SCANCODE_KBDILLUMUP = 280,
    SDL_SCANCODE_EJECT = 281,
    SDL_SCANCODE_SLEEP = 282,

    SDL_SCANCODE_APP1 = 283,
    SDL_SCANCODE_APP2 = 284,

    SDL_NUM_SCANCODES = 512
};

export enum : std::int32_t
{
    SDLK_UNKNOWN = 0,

    SDLK_RETURN = '\r',
    SDLK_ESCAPE = '\033',
    SDLK_BACKSPACE = '\b',
    SDLK_TAB = '\t',
    SDLK_SPACE = ' ',
    SDLK_EXCLAIM = '!',
    SDLK_QUOTEDBL = '"',
    SDLK_HASH = '#',
    SDLK_PERCENT = '%',
    SDLK_DOLLAR = '$',
    SDLK_AMPERSAND = '&',
    SDLK_QUOTE = '\'',
    SDLK_LEFTPAREN = '(',
    SDLK_RIGHTPAREN = ')',
    SDLK_ASTERISK = '*',
    SDLK_PLUS = '+',
    SDLK_COMMA = ',',
    SDLK_MINUS = '-',
    SDLK_PERIOD = '.',
    SDLK_SLASH = '/',
    SDLK_0 = '0',
    SDLK_1 = '1',
    SDLK_2 = '2',
    SDLK_3 = '3',
    SDLK_4 = '4',
    SDLK_5 = '5',
    SDLK_6 = '6',
    SDLK_7 = '7',
    SDLK_8 = '8',
    SDLK_9 = '9',
    SDLK_COLON = ':',
    SDLK_SEMICOLON = ';',
    SDLK_LESS = '<',
    SDLK_EQUALS = '=',
    SDLK_GREATER = '>',
    SDLK_QUESTION = '?',
    SDLK_AT = '@',
    /*
       Skip uppercase letters
     */
    SDLK_LEFTBRACKET = '[',
    SDLK_BACKSLASH = '\\',
    SDLK_RIGHTBRACKET = ']',
    SDLK_CARET = '^',
    SDLK_UNDERSCORE = '_',
    SDLK_BACKQUOTE = '`',
    SDLK_a = 'a',
    SDLK_b = 'b',
    SDLK_c = 'c',
    SDLK_d = 'd',
    SDLK_e = 'e',
    SDLK_f = 'f',
    SDLK_g = 'g',
    SDLK_h = 'h',
    SDLK_i = 'i',
    SDLK_j = 'j',
    SDLK_k = 'k',
    SDLK_l = 'l',
    SDLK_m = 'm',
    SDLK_n = 'n',
    SDLK_o = 'o',
    SDLK_p = 'p',
    SDLK_q = 'q',
    SDLK_r = 'r',
    SDLK_s = 's',
    SDLK_t = 't',
    SDLK_u = 'u',
    SDLK_v = 'v',
    SDLK_w = 'w',
    SDLK_x = 'x',
    SDLK_y = 'y',
    SDLK_z = 'z',

    SDLK_CAPSLOCK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK),

    SDLK_F1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1),
    SDLK_F2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2),
    SDLK_F3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3),
    SDLK_F4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4),
    SDLK_F5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5),
    SDLK_F6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6),
    SDLK_F7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7),
    SDLK_F8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8),
    SDLK_F9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9),
    SDLK_F10 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10),
    SDLK_F11 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11),
    SDLK_F12 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12),

    SDLK_PRINTSCREEN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN),
    SDLK_SCROLLLOCK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK),
    SDLK_PAUSE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE),
    SDLK_INSERT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT),
    SDLK_HOME = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME),
    SDLK_PAGEUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP),
    SDLK_DELETE = '\177',
    SDLK_END = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END),
    SDLK_PAGEDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN),
    SDLK_RIGHT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT),
    SDLK_LEFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT),
    SDLK_DOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN),
    SDLK_UP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP),

    SDLK_NUMLOCKCLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NUMLOCKCLEAR),
    SDLK_KP_DIVIDE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DIVIDE),
    SDLK_KP_MULTIPLY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MULTIPLY),
    SDLK_KP_MINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS),
    SDLK_KP_PLUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS),
    SDLK_KP_ENTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER),
    SDLK_KP_1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1),
    SDLK_KP_2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2),
    SDLK_KP_3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3),
    SDLK_KP_4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4),
    SDLK_KP_5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5),
    SDLK_KP_6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6),
    SDLK_KP_7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7),
    SDLK_KP_8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8),
    SDLK_KP_9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9),
    SDLK_KP_0 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0),
    SDLK_KP_PERIOD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD),

    SDLK_APPLICATION = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APPLICATION),
    SDLK_POWER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_POWER),
    SDLK_KP_EQUALS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALS),
    SDLK_F13 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F13),
    SDLK_F14 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F14),
    SDLK_F15 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F15),
    SDLK_F16 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F16),
    SDLK_F17 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F17),
    SDLK_F18 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F18),
    SDLK_F19 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F19),
    SDLK_F20 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F20),
    SDLK_F21 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F21),
    SDLK_F22 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F22),
    SDLK_F23 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F23),
    SDLK_F24 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F24),
    SDLK_EXECUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXECUTE),
    SDLK_HELP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HELP),
    SDLK_MENU = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MENU),
    SDLK_SELECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SELECT),
    SDLK_STOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_STOP),
    SDLK_AGAIN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AGAIN),
    SDLK_UNDO = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UNDO),
    SDLK_CUT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CUT),
    SDLK_COPY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COPY),
    SDLK_PASTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PASTE),
    SDLK_FIND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_FIND),
    SDLK_MUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MUTE),
    SDLK_VOLUMEUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEUP),
    SDLK_VOLUMEDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEDOWN),
    SDLK_KP_COMMA = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COMMA),
    SDLK_KP_EQUALSAS400 =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400),

    SDLK_ALTERASE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ALTERASE),
    SDLK_SYSREQ = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SYSREQ),
    SDLK_CANCEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CANCEL),
    SDLK_CLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEAR),
    SDLK_PRIOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRIOR),
    SDLK_RETURN2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RETURN2),
    SDLK_SEPARATOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SEPARATOR),
    SDLK_OUT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OUT),
    SDLK_OPER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OPER),
    SDLK_CLEARAGAIN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEARAGAIN),
    SDLK_CRSEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CRSEL),
    SDLK_EXSEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXSEL),

    SDLK_KP_00 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_00),
    SDLK_KP_000 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_000),
    SDLK_THOUSANDSSEPARATOR =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_THOUSANDSSEPARATOR),
    SDLK_DECIMALSEPARATOR =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DECIMALSEPARATOR),
    SDLK_CURRENCYUNIT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYUNIT),
    SDLK_CURRENCYSUBUNIT =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT),
    SDLK_KP_LEFTPAREN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTPAREN),
    SDLK_KP_RIGHTPAREN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTPAREN),
    SDLK_KP_LEFTBRACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTBRACE),
    SDLK_KP_RIGHTBRACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTBRACE),
    SDLK_KP_TAB = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_TAB),
    SDLK_KP_BACKSPACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BACKSPACE),
    SDLK_KP_A = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_A),
    SDLK_KP_B = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_B),
    SDLK_KP_C = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_C),
    SDLK_KP_D = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_D),
    SDLK_KP_E = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_E),
    SDLK_KP_F = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_F),
    SDLK_KP_XOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_XOR),
    SDLK_KP_POWER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_POWER),
    SDLK_KP_PERCENT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERCENT),
    SDLK_KP_LESS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LESS),
    SDLK_KP_GREATER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_GREATER),
    SDLK_KP_AMPERSAND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AMPERSAND),
    SDLK_KP_DBLAMPERSAND =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND),
    SDLK_KP_VERTICALBAR =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_VERTICALBAR),
    SDLK_KP_DBLVERTICALBAR =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLVERTICALBAR),
    SDLK_KP_COLON = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COLON),
    SDLK_KP_HASH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HASH),
    SDLK_KP_SPACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_SPACE),
    SDLK_KP_AT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AT),
    SDLK_KP_EXCLAM = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EXCLAM),
    SDLK_KP_MEMSTORE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSTORE),
    SDLK_KP_MEMRECALL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMRECALL),
    SDLK_KP_MEMCLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMCLEAR),
    SDLK_KP_MEMADD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMADD),
    SDLK_KP_MEMSUBTRACT =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT),
    SDLK_KP_MEMMULTIPLY =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY),
    SDLK_KP_MEMDIVIDE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMDIVIDE),
    SDLK_KP_PLUSMINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUSMINUS),
    SDLK_KP_CLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEAR),
    SDLK_KP_CLEARENTRY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEARENTRY),
    SDLK_KP_BINARY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BINARY),
    SDLK_KP_OCTAL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_OCTAL),
    SDLK_KP_DECIMAL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DECIMAL),
    SDLK_KP_HEXADECIMAL =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL),

    SDLK_LCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LCTRL),
    SDLK_LSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LSHIFT),
    SDLK_LALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LALT),
    SDLK_LGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LGUI),
    SDLK_RCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RCTRL),
    SDLK_RSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RSHIFT),
    SDLK_RALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RALT),
    SDLK_RGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RGUI),

    SDLK_MODE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MODE),

    SDLK_AUDIONEXT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIONEXT),
    SDLK_AUDIOPREV = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPREV),
    SDLK_AUDIOSTOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOSTOP),
    SDLK_AUDIOPLAY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPLAY),
    SDLK_AUDIOMUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOMUTE),
    SDLK_MEDIASELECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIASELECT),
    SDLK_WWW = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_WWW),
    SDLK_MAIL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MAIL),
    SDLK_CALCULATOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALCULATOR),
    SDLK_COMPUTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COMPUTER),
    SDLK_AC_SEARCH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_SEARCH),
    SDLK_AC_HOME = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_HOME),
    SDLK_AC_BACK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BACK),
    SDLK_AC_FORWARD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_FORWARD),
    SDLK_AC_STOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_STOP),
    SDLK_AC_REFRESH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_REFRESH),
    SDLK_AC_BOOKMARKS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BOOKMARKS),

    SDLK_BRIGHTNESSDOWN =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSDOWN),
    SDLK_BRIGHTNESSUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSUP),
    SDLK_DISPLAYSWITCH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DISPLAYSWITCH),
    SDLK_KBDILLUMTOGGLE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMTOGGLE),
    SDLK_KBDILLUMDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMDOWN),
    SDLK_KBDILLUMUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMUP),
    SDLK_EJECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EJECT),
    SDLK_SLEEP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SLEEP)
};
