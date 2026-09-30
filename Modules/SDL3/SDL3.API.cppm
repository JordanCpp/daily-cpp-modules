// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

export module SDL3.API;

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
export struct SDL_Gamepad;
export struct SDL_Haptic;
export struct SDL_HapticEffect;
export struct SDL_AudioSpec;
export struct SDL_AudioStream;
export struct SDL_RWops;
export struct SDL_Cursor;
export struct SDL_PropertiesID;
export struct SDL_Environment;

// ============================================================
// BASIC TYPES
// ============================================================

export struct SDL_Rect {
    float x, y;
    float w, h;
};

export struct SDL_FRect {
    float x, y;
    float w, h;
};

export struct SDL_Point {
    int x, y;
};

export struct SDL_FPoint {
    float x, y;
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
// AUDIO (SDL3 style)
// ============================================================

export typedef std::uint32_t SDL_AudioDeviceID;

export constexpr SDL_AudioDeviceID SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK = 0xFFFFFFFF;
export constexpr SDL_AudioDeviceID SDL_AUDIO_DEVICE_DEFAULT_RECORDING = 0xFFFFFFFE;

export struct SDL_AudioSpec {
    int freq;
    std::uint16_t format;
    int channels;
};

// ============================================================
// TIMER
// ============================================================

export typedef std::uint64_t SDL_TimerID;

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
// EVENTS (SDL3: names use SDL_EVENT_ prefix)
// ============================================================

export struct SDL_CommonEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
};

export struct SDL_DisplayEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::uint32_t displayID;
    std::uint8_t event;
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint8_t padding3;
    std::int32_t data1;
    std::int32_t data2;
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
    float x;
    float y;
    float xrel;
    float yrel;
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
    float x;
    float y;
};

export struct SDL_MouseWheelEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::uint32_t windowID;
    std::uint32_t which;
    float x;
    float y;
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

export struct SDL_JoyBatteryEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::int32_t which;
    std::uint8_t state;
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint8_t padding3;
    int percent;
};

// SDL3: Gamepad events (renamed from Controller)
export struct SDL_GamepadAxisEvent {
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

export struct SDL_GamepadButtonEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    std::int32_t which;
    std::uint8_t button;
    std::uint8_t state;
    std::uint8_t padding1;
    std::uint8_t padding2;
};

export struct SDL_GamepadDeviceEvent {
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

export struct SDL_DropEvent {
    std::uint32_t type;
    std::uint32_t timestamp;
    char* file;
    std::uint32_t windowID;
};

// SDL3: SDL_SYSWMEVENT removed — use hooks instead

export union SDL_Event {
    std::uint32_t type;
    SDL_CommonEvent common;
    SDL_DisplayEvent display;
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
    SDL_JoyBatteryEvent jbattery;
    SDL_GamepadAxisEvent gaxis;
    SDL_GamepadButtonEvent gbutton;
    SDL_GamepadDeviceEvent gdevice;
    SDL_AudioDeviceEvent adevice;
    SDL_QuitEvent quit;
    SDL_UserEvent user;
    SDL_DropEvent drop;
    std::uint8_t padding[128];
};

// ============================================================
// CONSTANTS (SDL3)
// ============================================================

// Initialization flags
export constexpr std::uint32_t SDL_INIT_TIMER = 0x00000001;
export constexpr std::uint32_t SDL_INIT_AUDIO = 0x00000010;
export constexpr std::uint32_t SDL_INIT_VIDEO = 0x00000020;
export constexpr std::uint32_t SDL_INIT_JOYSTICK = 0x00000200;
export constexpr std::uint32_t SDL_INIT_HAPTIC = 0x00001000;
export constexpr std::uint32_t SDL_INIT_GAMEPAD = 0x00002000;
export constexpr std::uint32_t SDL_INIT_EVENTS = 0x00004000;
export constexpr std::uint32_t SDL_INIT_SENSOR = 0x00008000;
export constexpr std::uint32_t SDL_INIT_CAMERA = 0x00010000;
export constexpr std::uint32_t SDL_INIT_EVERYTHING = 0x0000FFFF;

// Window flags (SDL3)
export constexpr std::uint64_t SDL_WINDOW_FULLSCREEN = 0x0000000000000001ULL;
export constexpr std::uint64_t SDL_WINDOW_OPENGL = 0x0000000000000002ULL;
export constexpr std::uint64_t SDL_WINDOW_HIDDEN = 0x0000000000000008ULL;
export constexpr std::uint64_t SDL_WINDOW_BORDERLESS = 0x0000000000000010ULL;
export constexpr std::uint64_t SDL_WINDOW_RESIZABLE = 0x0000000000000020ULL;
export constexpr std::uint64_t SDL_WINDOW_MINIMIZED = 0x0000000000000040ULL;
export constexpr std::uint64_t SDL_WINDOW_MAXIMIZED = 0x0000000000000080ULL;
export constexpr std::uint64_t SDL_WINDOW_MOUSE_GRABBED = 0x0000000000000100ULL;
export constexpr std::uint64_t SDL_WINDOW_INPUT_FOCUS = 0x0000000000000200ULL;
export constexpr std::uint64_t SDL_WINDOW_MOUSE_FOCUS = 0x0000000000000400ULL;
export constexpr std::uint64_t SDL_WINDOW_FULLSCREEN_DESKTOP = 0x0000000000001001ULL;
export constexpr std::uint64_t SDL_WINDOW_FOREIGN = 0x0000000000000800ULL;
export constexpr std::uint64_t SDL_WINDOW_HIGH_PIXEL_DENSITY = 0x0000000000002000ULL;
export constexpr std::uint64_t SDL_WINDOW_MOUSE_CAPTURE = 0x0000000000004000ULL;
export constexpr std::uint64_t SDL_WINDOW_ALWAYS_ON_TOP = 0x0000000000008000ULL;
export constexpr std::uint64_t SDL_WINDOW_UTILITY = 0x0000000000020000ULL;
export constexpr std::uint64_t SDL_WINDOW_TOOLTIP = 0x0000000000040000ULL;
export constexpr std::uint64_t SDL_WINDOW_POPUP_MENU = 0x0000000000080000ULL;
export constexpr std::uint64_t SDL_WINDOW_VULKAN = 0x0000000010000000ULL;
export constexpr std::uint64_t SDL_WINDOW_METAL = 0x0000000020000000ULL;

// Renderer flags
export constexpr std::uint32_t SDL_RENDERER_SOFTWARE = 0x00000001;
export constexpr std::uint32_t SDL_RENDERER_ACCELERATED = 0x00000002;
export constexpr std::uint32_t SDL_RENDERER_PRESENTVSYNC = 0x00000004;
export constexpr std::uint32_t SDL_RENDERER_TARGETTEXTURE = 0x00000008;

// Texture access
export constexpr int SDL_TEXTUREACCESS_STATIC = 0;
export constexpr int SDL_TEXTUREACCESS_STREAMING = 1;
export constexpr int SDL_TEXTUREACCESS_TARGET = 2;

// Event types (SDL3: SDL_EVENT_ prefix)
export constexpr std::uint32_t SDL_EVENT_FIRST = 0;
export constexpr std::uint32_t SDL_EVENT_QUIT = 0x100;
export constexpr std::uint32_t SDL_EVENT_TERMINATING = 0x101;
export constexpr std::uint32_t SDL_EVENT_LOW_MEMORY = 0x102;
export constexpr std::uint32_t SDL_EVENT_WILL_ENTER_BACKGROUND = 0x103;
export constexpr std::uint32_t SDL_EVENT_DID_ENTER_BACKGROUND = 0x104;
export constexpr std::uint32_t SDL_EVENT_WILL_ENTER_FOREGROUND = 0x105;
export constexpr std::uint32_t SDL_EVENT_DID_ENTER_FOREGROUND = 0x106;
export constexpr std::uint32_t SDL_EVENT_LOCALE_CHANGED = 0x107;
export constexpr std::uint32_t SDL_EVENT_DISPLAY_ORIENTATION = 0x108;
export constexpr std::uint32_t SDL_EVENT_DISPLAY_ADDED = 0x109;
export constexpr std::uint32_t SDL_EVENT_DISPLAY_REMOVED = 0x10A;
export constexpr std::uint32_t SDL_EVENT_DISPLAY_MOVED = 0x10B;
export constexpr std::uint32_t SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED = 0x10C;
export constexpr std::uint32_t SDL_EVENT_WINDOW_SHOWN = 0x200;
export constexpr std::uint32_t SDL_EVENT_WINDOW_HIDDEN = 0x201;
export constexpr std::uint32_t SDL_EVENT_WINDOW_EXPOSED = 0x202;
export constexpr std::uint32_t SDL_EVENT_WINDOW_MOVED = 0x203;
export constexpr std::uint32_t SDL_EVENT_WINDOW_RESIZED = 0x204;
export constexpr std::uint32_t SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED = 0x205;
export constexpr std::uint32_t SDL_EVENT_WINDOW_MINIMIZED = 0x206;
export constexpr std::uint32_t SDL_EVENT_WINDOW_MAXIMIZED = 0x207;
export constexpr std::uint32_t SDL_EVENT_WINDOW_RESTORED = 0x208;
export constexpr std::uint32_t SDL_EVENT_WINDOW_ENTER_FULLSCREEN = 0x209;
export constexpr std::uint32_t SDL_EVENT_WINDOW_LEAVE_FULLSCREEN = 0x20A;
export constexpr std::uint32_t SDL_EVENT_WINDOW_DESTROYED = 0x20B;
export constexpr std::uint32_t SDL_EVENT_WINDOW_HIT_TEST = 0x20C;
export constexpr std::uint32_t SDL_EVENT_WINDOW_MOUSE_ENTER = 0x20D;
export constexpr std::uint32_t SDL_EVENT_WINDOW_MOUSE_LEAVE = 0x20E;
export constexpr std::uint32_t SDL_EVENT_WINDOW_FOCUS_GAINED = 0x20F;
export constexpr std::uint32_t SDL_EVENT_WINDOW_FOCUS_LOST = 0x210;
export constexpr std::uint32_t SDL_EVENT_WINDOW_CLOSE_REQUESTED = 0x211;
export constexpr std::uint32_t SDL_EVENT_WINDOW_TAKE_FOCUS = 0x212;
export constexpr std::uint32_t SDL_EVENT_WINDOW_DISPLAY_CHANGED = 0x213;
export constexpr std::uint32_t SDL_EVENT_KEY_DOWN = 0x300;
export constexpr std::uint32_t SDL_EVENT_KEY_UP = 0x301;
export constexpr std::uint32_t SDL_EVENT_TEXT_EDITING = 0x302;
export constexpr std::uint32_t SDL_EVENT_TEXT_INPUT = 0x303;
export constexpr std::uint32_t SDL_EVENT_KEYMAP_CHANGED = 0x304;
export constexpr std::uint32_t SDL_EVENT_MOUSE_MOTION = 0x400;
export constexpr std::uint32_t SDL_EVENT_MOUSE_BUTTON_DOWN = 0x401;
export constexpr std::uint32_t SDL_EVENT_MOUSE_BUTTON_UP = 0x402;
export constexpr std::uint32_t SDL_EVENT_MOUSE_WHEEL = 0x403;
export constexpr std::uint32_t SDL_EVENT_JOYSTICK_AXIS_MOTION = 0x600;
export constexpr std::uint32_t SDL_EVENT_JOYSTICK_BALL_MOTION = 0x601;
export constexpr std::uint32_t SDL_EVENT_JOYSTICK_HAT_MOTION = 0x602;
export constexpr std::uint32_t SDL_EVENT_JOYSTICK_BUTTON_DOWN = 0x603;
export constexpr std::uint32_t SDL_EVENT_JOYSTICK_BUTTON_UP = 0x604;
export constexpr std::uint32_t SDL_EVENT_JOYSTICK_ADDED = 0x605;
export constexpr std::uint32_t SDL_EVENT_JOYSTICK_REMOVED = 0x606;
export constexpr std::uint32_t SDL_EVENT_JOYSTICK_BATTERY_UPDATED = 0x607;
export constexpr std::uint32_t SDL_EVENT_GAMEPAD_AXIS_MOTION = 0x650;
export constexpr std::uint32_t SDL_EVENT_GAMEPAD_BUTTON_DOWN = 0x651;
export constexpr std::uint32_t SDL_EVENT_GAMEPAD_BUTTON_UP = 0x652;
export constexpr std::uint32_t SDL_EVENT_GAMEPAD_ADDED = 0x653;
export constexpr std::uint32_t SDL_EVENT_GAMEPAD_REMOVED = 0x654;
export constexpr std::uint32_t SDL_EVENT_GAMEPAD_REMAPPED = 0x655;
export constexpr std::uint32_t SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN = 0x656;
export constexpr std::uint32_t SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION = 0x657;
export constexpr std::uint32_t SDL_EVENT_GAMEPAD_TOUCHPAD_UP = 0x658;
export constexpr std::uint32_t SDL_EVENT_GAMEPAD_SENSOR_UPDATE = 0x659;
export constexpr std::uint32_t SDL_EVENT_FINGER_DOWN = 0x700;
export constexpr std::uint32_t SDL_EVENT_FINGER_UP = 0x701;
export constexpr std::uint32_t SDL_EVENT_FINGER_MOTION = 0x702;
export constexpr std::uint32_t SDL_EVENT_CLIPBOARD_UPDATE = 0x900;
export constexpr std::uint32_t SDL_EVENT_DROP_FILE = 0x1000;
export constexpr std::uint32_t SDL_EVENT_DROP_TEXT = 0x1001;
export constexpr std::uint32_t SDL_EVENT_DROP_BEGIN = 0x1002;
export constexpr std::uint32_t SDL_EVENT_DROP_COMPLETE = 0x1003;
export constexpr std::uint32_t SDL_EVENT_AUDIO_DEVICE_ADDED = 0x1100;
export constexpr std::uint32_t SDL_EVENT_AUDIO_DEVICE_REMOVED = 0x1101;
export constexpr std::uint32_t SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED = 0x1102;
export constexpr std::uint32_t SDL_EVENT_SENSOR_UPDATE = 0x1200;
export constexpr std::uint32_t SDL_EVENT_RENDER_TARGETS_RESET = 0x2000;
export constexpr std::uint32_t SDL_EVENT_RENDER_DEVICE_RESET = 0x2001;
export constexpr std::uint32_t SDL_EVENT_USER = 0x8000;
export constexpr std::uint32_t SDL_EVENT_LAST = 0xFFFF;

// ============================================================
// FUNCTION POINTERS FOR DYNAMIC LOADING
// ============================================================

// --- Initialization, Errors, and Lifecycles ---
export inline bool (*SDL_Init)(std::uint32_t flags) = nullptr;
export inline bool (*SDL_InitSubSystem)(std::uint32_t flags) = nullptr;
export inline void (*SDL_QuitSubSystem)(std::uint32_t flags) = nullptr;
export inline std::uint32_t(*SDL_WasInit)(std::uint32_t flags) = nullptr;
export inline void (*SDL_Quit)() = nullptr;
export inline const char* (*SDL_GetError)() = nullptr;
export inline bool (*SDL_SetError)(const char* fmt) = nullptr;

// --- Window management ---
export inline SDL_Window* (*SDL_CreateWindow)(const char* title, int w, int h, std::uint64_t flags) = nullptr;
export inline void (*SDL_DestroyWindow)(SDL_Window* window) = nullptr;
export inline bool (*SDL_SetWindowTitle)(SDL_Window* window, const char* title) = nullptr;
export inline const char* (*SDL_GetWindowTitle)(SDL_Window* window) = nullptr;
export inline bool (*SDL_SetWindowSize)(SDL_Window* window, int w, int h) = nullptr;
export inline bool (*SDL_GetWindowSize)(SDL_Window* window, int* w, int* h) = nullptr;
export inline bool (*SDL_ShowWindow)(SDL_Window* window) = nullptr;
export inline bool (*SDL_HideWindow)(SDL_Window* window) = nullptr;
export inline bool (*SDL_RaiseWindow)(SDL_Window* window) = nullptr;
export inline bool (*SDL_MaximizeWindow)(SDL_Window* window) = nullptr;
export inline bool (*SDL_MinimizeWindow)(SDL_Window* window) = nullptr;
export inline bool (*SDL_RestoreWindow)(SDL_Window* window) = nullptr;
export inline bool (*SDL_SetWindowFullscreen)(SDL_Window* window, bool fullscreen) = nullptr;
export inline SDL_Surface* (*SDL_GetWindowSurface)(SDL_Window* window) = nullptr;
export inline bool (*SDL_UpdateWindowSurface)(SDL_Window* window) = nullptr;
export inline bool (*SDL_UpdateWindowSurfaceRects)(SDL_Window* window, const SDL_Rect* rects, int numrects) = nullptr;
export inline bool (*SDL_SyncWindow)(SDL_Window* window) = nullptr;

// --- Renderer ---
export inline SDL_Renderer* (*SDL_CreateRenderer)(SDL_Window* window, const char* name) = nullptr;
export inline void (*SDL_DestroyRenderer)(SDL_Renderer* renderer) = nullptr;
export inline bool (*SDL_SetRenderDrawColor)(SDL_Renderer* renderer, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) = nullptr;
export inline bool (*SDL_GetRenderDrawColor)(SDL_Renderer* renderer, std::uint8_t* r, std::uint8_t* g, std::uint8_t* b, std::uint8_t* a) = nullptr;
export inline bool (*SDL_RenderClear)(SDL_Renderer* renderer) = nullptr;
export inline bool (*SDL_RenderPresent)(SDL_Renderer* renderer) = nullptr;
export inline bool (*SDL_RenderFillRect)(SDL_Renderer* renderer, const SDL_FRect* rect) = nullptr;
export inline bool (*SDL_RenderRect)(SDL_Renderer* renderer, const SDL_FRect* rect) = nullptr;
export inline bool (*SDL_RenderLine)(SDL_Renderer* renderer, float x1, float y1, float x2, float y2) = nullptr;
export inline bool (*SDL_RenderPoint)(SDL_Renderer* renderer, float x, float y) = nullptr;
export inline bool (*SDL_RenderCopy)(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_FRect* srcrect, const SDL_FRect* dstrect) = nullptr;
export inline bool (*SDL_RenderCopyEx)(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_FRect* srcrect, const SDL_FRect* dstrect, double angle, const SDL_FPoint* center, int flip) = nullptr;
export inline bool (*SDL_SetRenderClipRect)(SDL_Renderer* renderer, const SDL_Rect* rect) = nullptr;
export inline bool (*SDL_GetRenderClipRect)(SDL_Renderer* renderer, SDL_Rect* rect) = nullptr;
export inline bool (*SDL_SetRenderLogicalPresentation)(SDL_Renderer* renderer, int w, int h, int mode) = nullptr;
export inline bool (*SDL_GetRenderLogicalPresentation)(SDL_Renderer* renderer, int* w, int* h, int* mode) = nullptr;
export inline bool (*SDL_SetRenderViewport)(SDL_Renderer* renderer, const SDL_Rect* rect) = nullptr;
export inline bool (*SDL_GetRenderViewport)(SDL_Renderer* renderer, SDL_Rect* rect) = nullptr;
export inline bool (*SDL_SetRenderScale)(SDL_Renderer* renderer, float scaleX, float scaleY) = nullptr;
export inline bool (*SDL_GetRenderScale)(SDL_Renderer* renderer, float* scaleX, float* scaleY) = nullptr;
export inline bool (*SDL_SetRenderTarget)(SDL_Renderer* renderer, SDL_Texture* texture) = nullptr;
export inline SDL_Texture* (*SDL_GetRenderTarget)(SDL_Renderer* renderer) = nullptr;

// --- Textures ---
export inline SDL_Texture* (*SDL_CreateTexture)(SDL_Renderer* renderer, std::uint32_t format, int access, int w, int h) = nullptr;
export inline SDL_Texture* (*SDL_CreateTextureFromSurface)(SDL_Renderer* renderer, SDL_Surface* surface) = nullptr;
export inline void (*SDL_DestroyTexture)(SDL_Texture* texture) = nullptr;
export inline bool (*SDL_QueryTexture)(SDL_Texture* texture, std::uint32_t* format, int* access, int* w, int* h) = nullptr;
export inline bool (*SDL_SetTextureColorMod)(SDL_Texture* texture, std::uint8_t r, std::uint8_t g, std::uint8_t b) = nullptr;
export inline bool (*SDL_GetTextureColorMod)(SDL_Texture* texture, std::uint8_t* r, std::uint8_t* g, std::uint8_t* b) = nullptr;
export inline bool (*SDL_SetTextureAlphaMod)(SDL_Texture* texture, std::uint8_t alpha) = nullptr;
export inline bool (*SDL_GetTextureAlphaMod)(SDL_Texture* texture, std::uint8_t* alpha) = nullptr;
export inline bool (*SDL_SetTextureBlendMode)(SDL_Texture* texture, int blendMode) = nullptr;
export inline bool (*SDL_GetTextureBlendMode)(SDL_Texture* texture, int* blendMode) = nullptr;
export inline bool (*SDL_UpdateTexture)(SDL_Texture* texture, const SDL_Rect* rect, const void* pixels, int pitch) = nullptr;
export inline bool (*SDL_LockTexture)(SDL_Texture* texture, const SDL_Rect* rect, void** pixels, int* pitch) = nullptr;
export inline void (*SDL_UnlockTexture)(SDL_Texture* texture) = nullptr;

// --- Surface management ---
export inline SDL_Surface* (*SDL_CreateSurface)(int width, int height, std::uint32_t format) = nullptr;
export inline SDL_Surface* (*SDL_CreateSurfaceFrom)(int width, int height, std::uint32_t format, void* pixels, int pitch) = nullptr;
export inline void (*SDL_DestroySurface)(SDL_Surface* surface) = nullptr;
export inline bool (*SDL_LockSurface)(SDL_Surface* surface) = nullptr;
export inline void (*SDL_UnlockSurface)(SDL_Surface* surface) = nullptr;
export inline bool (*SDL_SaveBMP)(SDL_Surface* surface, const char* file) = nullptr;
export inline SDL_Surface* (*SDL_LoadBMP)(const char* file) = nullptr;
export inline bool (*SDL_SetSurfacePalette)(SDL_Surface* surface, SDL_Palette* palette) = nullptr;
export inline bool (*SDL_SetSurfaceRLE)(SDL_Surface* surface, bool flag) = nullptr;
export inline bool (*SDL_SetSurfaceColorKey)(SDL_Surface* surface, bool flag, std::uint32_t key) = nullptr;
export inline bool (*SDL_GetSurfaceColorKey)(SDL_Surface* surface, std::uint32_t* key) = nullptr;
export inline bool (*SDL_SetSurfaceColorMod)(SDL_Surface* surface, std::uint8_t r, std::uint8_t g, std::uint8_t b) = nullptr;
export inline bool (*SDL_GetSurfaceColorMod)(SDL_Surface* surface, std::uint8_t* r, std::uint8_t* g, std::uint8_t* b) = nullptr;
export inline bool (*SDL_SetSurfaceAlphaMod)(SDL_Surface* surface, std::uint8_t alpha) = nullptr;
export inline bool (*SDL_GetSurfaceAlphaMod)(SDL_Surface* surface, std::uint8_t* alpha) = nullptr;
export inline bool (*SDL_SetSurfaceBlendMode)(SDL_Surface* surface, int blendMode) = nullptr;
export inline bool (*SDL_GetSurfaceBlendMode)(SDL_Surface* surface, int* blendMode) = nullptr;
export inline bool (*SDL_SetSurfaceClipRect)(SDL_Surface* surface, const SDL_Rect* rect) = nullptr;
export inline bool (*SDL_GetSurfaceClipRect)(SDL_Surface* surface, SDL_Rect* rect) = nullptr;
export inline bool (*SDL_ConvertPixels)(int width, int height, std::uint32_t src_format, const void* src, int src_pitch, std::uint32_t dst_format, void* dst, int dst_pitch) = nullptr;
export inline bool (*SDL_FillSurfaceRect)(SDL_Surface* dst, const SDL_Rect* rect, std::uint32_t color) = nullptr;
export inline bool (*SDL_FillSurfaceRects)(SDL_Surface* dst, const SDL_Rect* rects, int count, std::uint32_t color) = nullptr;
export inline bool (*SDL_BlitSurface)(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) = nullptr;
export inline bool (*SDL_BlitSurfaceScaled)(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect, int scaleMode) = nullptr;

// --- Pixel operations ---
export inline std::uint32_t(*SDL_MapRGB)(const SDL_PixelFormat* format, std::uint8_t r, std::uint8_t g, std::uint8_t b) = nullptr;
export inline std::uint32_t(*SDL_MapRGBA)(const SDL_PixelFormat* format, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) = nullptr;
export inline void (*SDL_GetRGB)(std::uint32_t pixel, const SDL_PixelFormat* format, std::uint8_t* r, std::uint8_t* g, std::uint8_t* b) = nullptr;
export inline void (*SDL_GetRGBA)(std::uint32_t pixel, const SDL_PixelFormat* format, std::uint8_t* r, std::uint8_t* g, std::uint8_t* b, std::uint8_t* a) = nullptr;
export inline SDL_PixelFormat* (*SDL_CreatePixelFormat)(std::uint32_t pixel_format) = nullptr;
export inline void (*SDL_DestroyPixelFormat)(SDL_PixelFormat* format) = nullptr;
export inline SDL_Palette* (*SDL_CreatePalette)(int ncolors) = nullptr;
export inline bool (*SDL_SetPaletteColors)(SDL_Palette* palette, const SDL_Color* colors, int firstcolor, int ncolors) = nullptr;
export inline void (*SDL_DestroyPalette)(SDL_Palette* palette) = nullptr;

// --- Events ---
export inline void (*SDL_PumpEvents)() = nullptr;
export inline bool (*SDL_PollEvent)(SDL_Event* event) = nullptr;
export inline bool (*SDL_WaitEvent)(SDL_Event* event) = nullptr;
export inline bool (*SDL_WaitEventTimeout)(SDL_Event* event, std::int32_t timeout) = nullptr;
export inline bool (*SDL_PushEvent)(SDL_Event* event) = nullptr;
export inline void (*SDL_SetEventFilter)(bool (*filter)(void* userdata, SDL_Event* event), void* userdata) = nullptr;
export inline bool (*SDL_GetEventFilter)(bool (**filter)(void* userdata, SDL_Event* event), void** userdata) = nullptr;
export inline void (*SDL_AddEventWatch)(bool (*filter)(void* userdata, SDL_Event* event), void* userdata) = nullptr;
export inline void (*SDL_DelEventWatch)(bool (*filter)(void* userdata, SDL_Event* event), void* userdata) = nullptr;
export inline void (*SDL_SetEventEnabled)(std::uint32_t type, bool enabled) = nullptr;
export inline bool (*SDL_EventEnabled)(std::uint32_t type) = nullptr;
export inline std::uint32_t(*SDL_RegisterEvents)(int numevents) = nullptr;

// --- Keyboard ---
export inline const bool* (*SDL_GetKeyboardState)(int* numkeys) = nullptr;
export inline std::int32_t(*SDL_GetKeyFromScancode)(std::int32_t scancode, std::uint16_t modstate, bool key_event) = nullptr;
export inline std::int32_t(*SDL_GetScancodeFromKey)(std::int32_t key, std::uint16_t* modstate) = nullptr;
export inline const char* (*SDL_GetScancodeName)(std::int32_t scancode) = nullptr;
export inline std::int32_t(*SDL_GetScancodeFromName)(const char* name) = nullptr;
export inline const char* (*SDL_GetKeyName)(std::int32_t key) = nullptr;
export inline std::int32_t(*SDL_GetKeyFromName)(const char* name) = nullptr;
export inline bool (*SDL_StartTextInput)(SDL_Window* window) = nullptr;
export inline bool (*SDL_TextInputActive)(SDL_Window* window) = nullptr;
export inline bool (*SDL_StopTextInput)(SDL_Window* window) = nullptr;
export inline bool (*SDL_SetTextInputArea)(SDL_Window* window, const SDL_Rect* rect, int cursor) = nullptr;

// --- Mouse ---
export inline std::uint32_t(*SDL_GetMouseState)(float* x, float* y) = nullptr;
export inline std::uint32_t(*SDL_GetGlobalMouseState)(float* x, float* y) = nullptr;
export inline std::uint32_t(*SDL_GetRelativeMouseState)(float* x, float* y) = nullptr;
export inline bool (*SDL_WarpMouseInWindow)(SDL_Window* window, float x, float y) = nullptr;
export inline bool (*SDL_SetRelativeMouseMode)(bool enabled) = nullptr;
export inline bool (*SDL_GetRelativeMouseMode)() = nullptr;
export inline bool (*SDL_ShowCursor)() = nullptr;
export inline bool (*SDL_HideCursor)() = nullptr;
export inline bool (*SDL_CursorVisible)() = nullptr;

// --- Joystick ---
export inline SDL_Joystick* (*SDL_OpenJoystick)(std::uint32_t instance_id) = nullptr;
export inline void (*SDL_CloseJoystick)(SDL_Joystick* joystick) = nullptr;
export inline const char* (*SDL_GetJoystickName)(SDL_Joystick* joystick) = nullptr;
export inline int (*SDL_GetNumJoystickAxes)(SDL_Joystick* joystick) = nullptr;
export inline int (*SDL_GetNumJoystickBalls)(SDL_Joystick* joystick) = nullptr;
export inline int (*SDL_GetNumJoystickHats)(SDL_Joystick* joystick) = nullptr;
export inline int (*SDL_GetNumJoystickButtons)(SDL_Joystick* joystick) = nullptr;
export inline std::int16_t(*SDL_GetJoystickAxis)(SDL_Joystick* joystick, int axis) = nullptr;
export inline std::uint8_t(*SDL_GetJoystickHat)(SDL_Joystick* joystick, int hat) = nullptr;
export inline bool (*SDL_GetJoystickBall)(SDL_Joystick* joystick, int ball, int* dx, int* dy) = nullptr;
export inline bool (*SDL_GetJoystickButton)(SDL_Joystick* joystick, int button) = nullptr;
export inline std::uint32_t* (*SDL_GetJoysticks)(int* count) = nullptr;
export inline void (*SDL_UpdateJoysticks)() = nullptr;
export inline bool (*SDL_JoystickEventsEnabled)() = nullptr;
export inline void (*SDL_SetJoystickEventsEnabled)(bool enabled) = nullptr;

// --- Gamepad (SDL3: replaces Controller) ---
export inline SDL_Gamepad* (*SDL_OpenGamepad)(std::uint32_t instance_id) = nullptr;
export inline void (*SDL_CloseGamepad)(SDL_Gamepad* gamepad) = nullptr;
export inline const char* (*SDL_GetGamepadName)(SDL_Gamepad* gamepad) = nullptr;
export inline std::int16_t(*SDL_GetGamepadAxis)(SDL_Gamepad* gamepad, int axis) = nullptr;
export inline bool (*SDL_GetGamepadButton)(SDL_Gamepad* gamepad, int button) = nullptr;
export inline bool (*SDL_GamepadEventsEnabled)() = nullptr;
export inline void (*SDL_SetGamepadEventsEnabled)(bool enabled) = nullptr;
export inline void (*SDL_UpdateGamepads)() = nullptr;
export inline bool (*SDL_IsGamepad)(std::uint32_t instance_id) = nullptr;
export inline const char* (*SDL_GetGamepadNameForID)(std::uint32_t instance_id) = nullptr;
export inline std::uint32_t* (*SDL_GetGamepads)(int* count) = nullptr;

// --- Timer ---
export inline std::uint64_t(*SDL_GetTicks)() = nullptr;
export inline std::uint64_t(*SDL_GetTicksNS)() = nullptr;
export inline std::uint64_t(*SDL_GetPerformanceCounter)() = nullptr;
export inline std::uint64_t(*SDL_GetPerformanceFrequency)() = nullptr;
export inline void (*SDL_Delay)(std::uint32_t ms) = nullptr;
export inline void (*SDL_DelayNS)(std::uint64_t ns) = nullptr;
export inline SDL_TimerID(*SDL_AddTimer)(std::uint32_t interval, std::uint32_t(*callback)(void* userdata, SDL_TimerID timerID, std::uint32_t interval), void* userdata) = nullptr;
export inline bool (*SDL_RemoveTimer)(SDL_TimerID id) = nullptr;

// --- Audio (SDL3: Stream API) ---
export inline SDL_AudioDeviceID(*SDL_OpenAudioDevice)(SDL_AudioDeviceID devid, const SDL_AudioSpec* spec) = nullptr;
export inline SDL_AudioStream* (*SDL_OpenAudioDeviceStream)(SDL_AudioDeviceID devid, const SDL_AudioSpec* spec, void (*callback)(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount), void* userdata) = nullptr;
export inline void (*SDL_CloseAudioDevice)(SDL_AudioDeviceID devid) = nullptr;
export inline void (*SDL_PauseAudioDevice)(SDL_AudioDeviceID devid) = nullptr;
export inline void (*SDL_ResumeAudioDevice)(SDL_AudioDeviceID devid) = nullptr;
export inline bool (*SDL_AudioDevicePaused)(SDL_AudioDeviceID devid) = nullptr;
export inline bool (*SDL_GetAudioDeviceFormat)(SDL_AudioDeviceID devid, SDL_AudioSpec* spec, int* sample_frames) = nullptr;
export inline char* (*SDL_GetAudioDeviceName)(SDL_AudioDeviceID devid) = nullptr;
export inline SDL_AudioDeviceID* (*SDL_GetAudioPlaybackDevices)(int* count) = nullptr;
export inline SDL_AudioDeviceID* (*SDL_GetAudioRecordingDevices)(int* count) = nullptr;

// --- Audio Stream ---
export inline SDL_AudioStream* (*SDL_CreateAudioStream)(const SDL_AudioSpec* src_spec, const SDL_AudioSpec* dst_spec) = nullptr;
export inline void (*SDL_DestroyAudioStream)(SDL_AudioStream* stream) = nullptr;
export inline bool (*SDL_BindAudioStream)(SDL_AudioDeviceID devid, SDL_AudioStream* stream) = nullptr;
export inline void (*SDL_UnbindAudioStream)(SDL_AudioStream* stream) = nullptr;
export inline bool (*SDL_PutAudioStreamData)(SDL_AudioStream* stream, const void* buf, int len) = nullptr;
export inline int (*SDL_GetAudioStreamData)(SDL_AudioStream* stream, void* buf, int len) = nullptr;
export inline int (*SDL_GetAudioStreamAvailable)(SDL_AudioStream* stream) = nullptr;
export inline int (*SDL_GetAudioStreamQueued)(SDL_AudioStream* stream) = nullptr;
export inline bool (*SDL_FlushAudioStream)(SDL_AudioStream* stream) = nullptr;
export inline bool (*SDL_ClearAudioStream)(SDL_AudioStream* stream) = nullptr;
export inline bool (*SDL_PauseAudioStreamDevice)(SDL_AudioStream* stream) = nullptr;
export inline bool (*SDL_ResumeAudioStreamDevice)(SDL_AudioStream* stream) = nullptr;

// --- Haptic ---
export inline SDL_Haptic* (*SDL_OpenHaptic)(std::uint32_t instance_id) = nullptr;
export inline void (*SDL_CloseHaptic)(SDL_Haptic* haptic) = nullptr;
export inline int (*SDL_GetMaxHapticEffects)(SDL_Haptic* haptic) = nullptr;
export inline int (*SDL_GetMaxHapticEffectsPlaying)(SDL_Haptic* haptic) = nullptr;
export inline std::uint32_t(*SDL_GetHapticFeatures)(SDL_Haptic* haptic) = nullptr;
export inline bool (*SDL_HapticEffectSupported)(SDL_Haptic* haptic, SDL_HapticEffect* effect) = nullptr;
export inline int (*SDL_CreateHapticEffect)(SDL_Haptic* haptic, SDL_HapticEffect* effect) = nullptr;
export inline bool (*SDL_RunHapticEffect)(SDL_Haptic* haptic, int effect, std::uint32_t iterations) = nullptr;
export inline bool (*SDL_StopHapticEffect)(SDL_Haptic* haptic, int effect) = nullptr;
export inline void (*SDL_DestroyHapticEffect)(SDL_Haptic* haptic, int effect) = nullptr;
export inline bool (*SDL_GetHapticEffectStatus)(SDL_Haptic* haptic, int effect) = nullptr;
export inline bool (*SDL_SetHapticGain)(SDL_Haptic* haptic, int gain) = nullptr;
export inline bool (*SDL_SetHapticAutocenter)(SDL_Haptic* haptic, int autocenter) = nullptr;
export inline SDL_Haptic* (*SDL_OpenHapticFromJoystick)(SDL_Joystick* joystick) = nullptr;

// --- Clipboard ---
export inline bool (*SDL_SetClipboardText)(const char* text) = nullptr;
export inline char* (*SDL_GetClipboardText)() = nullptr;
export inline bool (*SDL_HasClipboardText)() = nullptr;

// --- CPU Info ---
export inline int (*SDL_GetCPUCount)() = nullptr;
export inline int (*SDL_GetCPUCacheLineSize)() = nullptr;
export inline bool (*SDL_HasRDTSC)() = nullptr;
export inline bool (*SDL_HasAltiVec)() = nullptr;
export inline bool (*SDL_HasMMX)() = nullptr;
export inline bool (*SDL_Has3DNow)() = nullptr;
export inline bool (*SDL_HasSSE)() = nullptr;
export inline bool (*SDL_HasSSE2)() = nullptr;
export inline bool (*SDL_HasSSE3)() = nullptr;
export inline bool (*SDL_HasSSE41)() = nullptr;
export inline bool (*SDL_HasSSE42)() = nullptr;
export inline bool (*SDL_HasAVX)() = nullptr;
export inline bool (*SDL_HasAVX2)() = nullptr;
export inline bool (*SDL_HasAVX512F)() = nullptr;
export inline bool (*SDL_HasARMSIMD)() = nullptr;
export inline bool (*SDL_HasNEON)() = nullptr;

// --- Power management ---
export inline int (*SDL_GetPowerInfo)(int* seconds, int* percent) = nullptr;

// --- Platform ---
export inline const char* (*SDL_GetPlatform)() = nullptr;

// --- Properties API (new in SDL3) ---
export inline SDL_PropertiesID(*SDL_CreateProperties)() = nullptr;
export inline void (*SDL_DestroyProperties)(SDL_PropertiesID props) = nullptr;
export inline bool (*SDL_SetProperty)(SDL_PropertiesID props, const char* name, void* value) = nullptr;
export inline void* (*SDL_GetProperty)(SDL_PropertiesID props, const char* name, void* default_value) = nullptr;
export inline bool (*SDL_SetStringProperty)(SDL_PropertiesID props, const char* name, const char* value) = nullptr;
export inline const char* (*SDL_GetStringProperty)(SDL_PropertiesID props, const char* name, const char* default_value) = nullptr;
export inline bool (*SDL_SetNumberProperty)(SDL_PropertiesID props, const char* name, std::int64_t value) = nullptr;
export inline std::int64_t(*SDL_GetNumberProperty)(SDL_PropertiesID props, const char* name, std::int64_t default_value) = nullptr;
export inline bool (*SDL_SetBooleanProperty)(SDL_PropertiesID props, const char* name, bool value) = nullptr;
export inline bool (*SDL_GetBooleanProperty)(SDL_PropertiesID props, const char* name, bool default_value) = nullptr;

// --- Filesystem API (new in SDL3) ---
export inline char* (*SDL_GetBasePath)() = nullptr;
export inline char* (*SDL_GetPrefPath)(const char* org, const char* app) = nullptr;
export inline char* (*SDL_GetCurrentDirectory)() = nullptr;
export inline bool (*SDL_CreateDirectory)(const char* path) = nullptr;
export inline bool (*SDL_EnumerateDirectory)(const char* path, bool (*callback)(void* userdata, const char* dirname, const char* fname), void* userdata) = nullptr;
export inline bool (*SDL_RemovePath)(const char* path) = nullptr;
export inline bool (*SDL_RenamePath)(const char* oldpath, const char* newpath) = nullptr;

// --- Dialog API (new in SDL3) ---
export inline void (*SDL_ShowOpenFileDialog)(void (*callback)(void* userdata, const char* const* filelist, int filter), void* userdata, SDL_Window* window, const void* filters, int nfilters, const char* default_location, bool allow_many) = nullptr;
export inline void (*SDL_ShowSaveFileDialog)(void (*callback)(void* userdata, const char* const* filelist, int filter), void* userdata, SDL_Window* window, const void* filters, int nfilters, const char* default_location) = nullptr;
export inline void (*SDL_ShowOpenFolderDialog)(void (*callback)(void* userdata, const char* const* filelist, int filter), void* userdata, SDL_Window* window, const char* default_location, bool allow_many) = nullptr;

// --- Camera API (new in SDL3) ---
export inline std::uint32_t* (*SDL_GetCameras)(int* count) = nullptr;
export inline bool (*SDL_GetCameraFormat)(std::uint32_t instance_id, SDL_AudioSpec* spec) = nullptr;
export inline char* (*SDL_GetCameraName)(std::uint32_t instance_id) = nullptr;

// --- Time API (new in SDL3) ---
export inline bool (*SDL_GetCurrentTime)(std::uint64_t* ticks) = nullptr;
export inline bool (*SDL_TimeToDateTime)(std::uint64_t ticks, void* dt, bool local) = nullptr;

// --- System theme ---
export inline int (*SDL_GetSystemTheme)() = nullptr;
