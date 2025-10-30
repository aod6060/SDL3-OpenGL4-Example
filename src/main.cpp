#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


static std::string g_caption = "SDL3/GL4 Example Window";
static uint32_t g_width = 1280;
static uint32_t g_height = 720;
SDL_Window* g_window = nullptr;
SDL_GLContext g_context = nullptr;
bool g_running = true;
void game_init();
void game_handleEvent(SDL_Event* e);
void game_update(float delta);
void game_render();
void game_release();

enum InputState {
    IS_RELEASED = 0,
    IS_PRESSED_ONCE,
    IS_PRESSED,
    IS_RELEASED_ONCE,
    IS_MAX_SIZE
};

// lookat SDL3/SDL_scancode.h
enum Keyboard {
    KB_UNKNOWN = 0,
    KB_A = 4,
    KB_B = 5,
    KB_C = 6,
    KB_D = 7,
    KB_E = 8,
    KB_F = 9,
    KB_G = 10,
    KB_H = 11,
    KB_I = 12,
    KB_J = 13,
    KB_K = 14,
    KB_L = 15,
    KB_M = 16,
    KB_N = 17,
    KB_O = 18,
    KB_P = 19,
    KB_Q = 20,
    KB_R = 21,
    KB_S = 22,
    KB_T = 23,
    KB_U = 24,
    KB_V = 25,
    KB_W = 26,
    KB_X = 27,
    KB_Y = 28,
    KB_Z = 29,
    KB_1 = 30,
    KB_2 = 31,
    KB_3 = 32,
    KB_4 = 33,
    KB_5 = 34,
    KB_6 = 35,
    KB_7 = 36,
    KB_8 = 37,
    KB_9 = 38,
    KB_0 = 39,
    KB_RETURN = 40,
    KB_ESCAPE = 41,
    KB_BACKSPACE = 42,
    KB_TAB = 43,
    KB_SPACE = 44,
    KB_MINUS = 45,
    KB_EQUALS = 46,
    KB_LEFTBRACKET = 47,
    KB_RIGHTBRACKET = 48,
    KB_BACKSLASH = 49,
    KB_NONUSHASH = 50,
    KB_SEMICOLON = 51,
    KB_APOSTROPHE = 52,
    KB_GRAVE = 53,
    KB_COMMA = 54,
    KB_PERIOD = 55,
    KB_SLASH = 56,
    KB_CAPSLOCK = 57,
    KB_F1 = 58,
    KB_F2 = 59,
    KB_F3 = 60,
    KB_F4 = 61,
    KB_F5 = 62,
    KB_F6 = 63,
    KB_F7 = 64,
    KB_F8 = 65,
    KB_F9 = 66,
    KB_F10 = 67,
    KB_F11 = 68,
    KB_F12 = 69,
    KB_PRINTSCREEN = 70,
    KB_SCROLLLOCK = 71,
    KB_PAUSE = 72,
    KB_INSERT = 73,
    KB_HOME = 74,
    KB_PAGEUP = 75,
    KB_DELETE = 76,
    KB_END = 77,
    KB_PAGEDOWN = 78,
    KB_RIGHT = 79,
    KB_LEFT = 80,
    KB_DOWN = 81,
    KB_UP = 82,
    KB_NUMLOCKCLEAR = 83,
    KB_KP_DIVIDE = 84,
    KB_KP_MULTIPLY = 85,
    KB_KP_MINUS = 86,
    KB_KP_PLUS = 87,
    KB_KP_ENTER = 88,
    KB_KP_1 = 89,
    KB_KP_2 = 90,
    KB_KP_3 = 91,
    KB_KP_4 = 92,
    KB_KP_5 = 93,
    KB_KP_6 = 94,
    KB_KP_7 = 95,
    KB_KP_8 = 96,
    KB_KP_9 = 97,
    KB_KP_0 = 98,
    KB_KP_PERIOD = 99,
    KB_NONUSBACKSLASH = 100,
    KB_APPLICATION = 101,
    KB_POWER = 102,
    KB_KP_EQUALS = 103,
    KB_F13 = 104,
    KB_F14 = 105,
    KB_F15 = 106,
    KB_F16 = 107,
    KB_F17 = 108,
    KB_F18 = 109,
    KB_F19 = 110,
    KB_F20 = 111,
    KB_F21 = 112,
    KB_F22 = 113,
    KB_F23 = 114,
    KB_F24 = 115,
    KB_EXECUTE = 116,
    KB_HELP = 117,    /**< AL Integrated Help Center */
    KB_MENU = 118,    /**< Menu (show menu) */
    KB_SELECT = 119,
    KB_STOP = 120,    /**< AC Stop */
    KB_AGAIN = 121,   /**< AC Redo/Repeat */
    KB_UNDO = 122,    /**< AC Undo */
    KB_CUT = 123,     /**< AC Cut */
    KB_COPY = 124,    /**< AC Copy */
    KB_PASTE = 125,   /**< AC Paste */
    KB_FIND = 126,    /**< AC Find */
    KB_MUTE = 127,
    KB_VOLUMEUP = 128,
    KB_VOLUMEDOWN = 129,
    KB_KP_COMMA = 133,
    KB_KP_EQUALSAS400 = 134,
    KB_INTERNATIONAL1 = 135,
    KB_INTERNATIONAL2 = 136,
    KB_INTERNATIONAL3 = 137, /**< Yen */
    KB_INTERNATIONAL4 = 138,
    KB_INTERNATIONAL5 = 139,
    KB_INTERNATIONAL6 = 140,
    KB_INTERNATIONAL7 = 141,
    KB_INTERNATIONAL8 = 142,
    KB_INTERNATIONAL9 = 143,
    KB_LANG1 = 144, /**< Hangul/English toggle */
    KB_LANG2 = 145, /**< Hanja conversion */
    KB_LANG3 = 146, /**< Katakana */
    KB_LANG4 = 147, /**< Hiragana */
    KB_LANG5 = 148, /**< Zenkaku/Hankaku */
    KB_LANG6 = 149, /**< reserved */
    KB_LANG7 = 150, /**< reserved */
    KB_LANG8 = 151, /**< reserved */
    KB_LANG9 = 152, /**< reserved */
    KB_ALTERASE = 153,    /**< Erase-Eaze */
    KB_SYSREQ = 154,
    KB_CANCEL = 155,      /**< AC Cancel */
    KB_CLEAR = 156,
    KB_PRIOR = 157,
    KB_RETURN2 = 158,
    KB_SEPARATOR = 159,
    KB_OUT = 160,
    KB_OPER = 161,
    KB_CLEARAGAIN = 162,
    KB_CRSEL = 163,
    KB_EXSEL = 164,
    KB_KP_00 = 176,
    KB_KP_000 = 177,
    KB_THOUSANDSSEPARATOR = 178,
    KB_DECIMALSEPARATOR = 179,
    KB_CURRENCYUNIT = 180,
    KB_CURRENCYSUBUNIT = 181,
    KB_KP_LEFTPAREN = 182,
    KB_KP_RIGHTPAREN = 183,
    KB_KP_LEFTBRACE = 184,
    KB_KP_RIGHTBRACE = 185,
    KB_KP_TAB = 186,
    KB_KP_BACKSPACE = 187,
    KB_KP_A = 188,
    KB_KP_B = 189,
    KB_KP_C = 190,
    KB_KP_D = 191,
    KB_KP_E = 192,
    KB_KP_F = 193,
    KB_KP_XOR = 194,
    KB_KP_POWER = 195,
    KB_KP_PERCENT = 196,
    KB_KP_LESS = 197,
    KB_KP_GREATER = 198,
    KB_KP_AMPERSAND = 199,
    KB_KP_DBLAMPERSAND = 200,
    KB_KP_VERTICALBAR = 201,
    KB_KP_DBLVERTICALBAR = 202,
    KB_KP_COLON = 203,
    KB_KP_HASH = 204,
    KB_KP_SPACE = 205,
    KB_KP_AT = 206,
    KB_KP_EXCLAM = 207,
    KB_KP_MEMSTORE = 208,
    KB_KP_MEMRECALL = 209,
    KB_KP_MEMCLEAR = 210,
    KB_KP_MEMADD = 211,
    KB_KP_MEMSUBTRACT = 212,
    KB_KP_MEMMULTIPLY = 213,
    KB_KP_MEMDIVIDE = 214,
    KB_KP_PLUSMINUS = 215,
    KB_KP_CLEAR = 216,
    KB_KP_CLEARENTRY = 217,
    KB_KP_BINARY = 218,
    KB_KP_OCTAL = 219,
    KB_KP_DECIMAL = 220,
    KB_KP_HEXADECIMAL = 221,
    KB_LCTRL = 224,
    KB_LSHIFT = 225,
    KB_LALT = 226, /**< alt, option */
    KB_LGUI = 227, /**< windows, command (apple), meta */
    KB_RCTRL = 228,
    KB_RSHIFT = 229,
    KB_RALT = 230, /**< alt gr, option */
    KB_RGUI = 231, /**< windows, command (apple), meta */
    KB_MODE = 257,
    KB_SLEEP = 258,                   /**< Sleep */
    KB_WAKE = 259,                    /**< Wake */
    KB_CHANNEL_INCREMENT = 260,       /**< Channel Increment */
    KB_CHANNEL_DECREMENT = 261,       /**< Channel Decrement */
    KB_MEDIA_PLAY = 262,          /**< Play */
    KB_MEDIA_PAUSE = 263,         /**< Pause */
    KB_MEDIA_RECORD = 264,        /**< Record */
    KB_MEDIA_FAST_FORWARD = 265,  /**< Fast Forward */
    KB_MEDIA_REWIND = 266,        /**< Rewind */
    KB_MEDIA_NEXT_TRACK = 267,    /**< Next Track */
    KB_MEDIA_PREVIOUS_TRACK = 268, /**< Previous Track */
    KB_MEDIA_STOP = 269,          /**< Stop */
    KB_MEDIA_EJECT = 270,         /**< Eject */
    KB_MEDIA_PLAY_PAUSE = 271,    /**< Play / Pause */
    KB_MEDIA_SELECT = 272,        /* Media Select */
    KB_AC_NEW = 273,              /**< AC New */
    KB_AC_OPEN = 274,             /**< AC Open */
    KB_AC_CLOSE = 275,            /**< AC Close */
    KB_AC_EXIT = 276,             /**< AC Exit */
    KB_AC_SAVE = 277,             /**< AC Save */
    KB_AC_PRINT = 278,            /**< AC Print */
    KB_AC_PROPERTIES = 279,       /**< AC Properties */
    KB_AC_SEARCH = 280,           /**< AC Search */
    KB_AC_HOME = 281,             /**< AC Home */
    KB_AC_BACK = 282,             /**< AC Back */
    KB_AC_FORWARD = 283,          /**< AC Forward */
    KB_AC_STOP = 284,             /**< AC Stop */
    KB_AC_REFRESH = 285,          /**< AC Refresh */
    KB_AC_BOOKMARKS = 286,
    KB_SOFTLEFT = 287,
    KB_SOFTRIGHT = 288,
    KB_CALL = 289,
    KB_ENDCALL = 290,
    KB_RESERVED = 400,
    KB_MAX_SIZE = 512 
};

std::vector<InputState> input_keys;

void input_init();
void input_handleEvnet(SDL_Event* e);
void input_update();
void input_release();
bool input_isKeyReleased(Keyboard key);
bool input_isKeyPressedOnce(Keyboard key);
bool input_isKeyPressed(Keyboard key);
bool input_isKeyReleasedOnce(Keyboard key);

// Shaders
uint32_t main_vertex_shader = 0;
uint32_t main_fragment_shader = 0;
// Program
uint32_t main_program = 0;
// Vertex Array
uint32_t main_vertex_array = 0;
// Uniforms
uint32_t main_u_proj = 0;
uint32_t main_u_view = 0;
uint32_t main_u_model = 0;
// Attribute
const uint32_t MAIN_A_VERTICES = 0;
const uint32_t MAIN_A_COLORS = 1;
// Vertex Buffer
uint32_t vertices_buffer = 0;
std::vector<glm::vec3> vertices_list;
// Color Buffer
uint32_t colors_buffer = 0;
std::vector<glm::vec4> colors_list;

void rend_init();
void rend_release();
void rend_clear(const glm::vec4& color);
void rend_bind();
void rend_unbind();
void rend_setProjection(const glm::mat4& m);
void rend_setView(const glm::mat4& m);
void rend_setModel(const glm::mat4& m);
void rend_draw();
uint32_t rend_create_shader(GLenum type, std::string path);
uint32_t rend_create_program(std::vector<uint32_t> shaders);
void rend_delete_program(uint32_t id, std::vector<uint32_t> shaders);

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    g_window = SDL_CreateWindow(
        g_caption.c_str(),
        g_width,
        g_height,
        SDL_WINDOW_OPENGL
    );
    g_context = SDL_GL_CreateContext(g_window);
    glewInit();
    input_init();
    rend_init();
    SDL_Event event;
    uint32_t pre_time = SDL_GetTicks();
    uint32_t curr_time = 0;
    float delta = 0.0f;
    game_init();
    while(g_running) {
        curr_time = SDL_GetTicks();
        delta = (curr_time - pre_time) / 1000.0f;
        pre_time = curr_time;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_EVENT_QUIT) {
                g_running = false;
            }
            input_handleEvnet(&event);
            game_handleEvent(&event);
        }
        game_update(delta);
        game_render();
        input_update();
        SDL_GL_SwapWindow(g_window);
    }
    game_release();
    rend_release();
    input_release();
    SDL_GL_DestroyContext(g_context);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
    return 0;
}


void game_init() {

}

void game_handleEvent(SDL_Event* e) {

}

float yrot = 0.0f;

void game_update(float delta) {
    yrot += 32.0f * delta;
    if(yrot > 360.0f) {
        yrot -= 360.0f;
    }
}

void game_render() {
    rend_clear(glm::vec4(glm::vec3(100.0f, 149.0f, 237.0f) / 255.0f, 1.0f));
    rend_bind();
    rend_setProjection(glm::perspective(glm::radians(45.0f), (float)g_width / (float)g_height, 1.0f, 1024.0f));
    // Set view to Identity
    rend_setView(glm::mat4(1.0f));
    rend_setModel(
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(yrot), glm::vec3(0.0, 1.0, 0.0))
    );
    rend_draw();
    rend_unbind();
}

void game_release() {

}

void input_init() {
    input_keys.resize(Keyboard::KB_MAX_SIZE);
    std::for_each(input_keys.begin(), input_keys.end(), [&](InputState& state) {
        state = InputState::IS_RELEASED;
    });
}

void input_handleEvnet(SDL_Event* e) {
    if(e->type == SDL_EVENT_KEY_DOWN) {
        if(input_keys[e->key.scancode] == InputState::IS_RELEASED) {
            input_keys[e->key.scancode] = InputState::IS_PRESSED_ONCE;
        }
    } else if(e->type == SDL_EVENT_KEY_UP) {
        if(input_keys[e->key.scancode] == InputState::IS_PRESSED) {
            input_keys[e->key.scancode] = InputState::IS_RELEASED_ONCE;
        }
    }

}

void input_update() {
    std::for_each(input_keys.begin(), input_keys.end(), [&](InputState& state) {
        if(state == InputState::IS_PRESSED_ONCE) {
            state = InputState::IS_PRESSED;
        }
        if(state == InputState::IS_RELEASED_ONCE) {
            state = InputState::IS_RELEASED;
        }
    });

}

void input_release() {
    input_keys.clear();
}

bool input_isKeyReleased(Keyboard key) {
    return input_keys[key] == InputState::IS_RELEASED || input_keys[key] == InputState::IS_RELEASED_ONCE;
}

bool input_isKeyPressedOnce(Keyboard key) {
    return input_keys[key] == InputState::IS_PRESSED_ONCE;
}

bool input_isKeyPressed(Keyboard key) {
    return input_keys[key] == InputState::IS_PRESSED || input_keys[key] == InputState::IS_PRESSED_ONCE;
}

bool input_isKeyReleasedOnce(Keyboard key) {
    return input_keys[key] == InputState::IS_RELEASED_ONCE;
}



// Render
void rend_init() {
    glEnable(GL_DEPTH_TEST);
    // shader
    main_vertex_shader = rend_create_shader(GL_VERTEX_SHADER, "main.vs.glsl");
    main_fragment_shader = rend_create_shader(GL_FRAGMENT_SHADER, "main.fs.glsl");
    // program
    main_program = rend_create_program({main_vertex_shader, main_fragment_shader});
    // vertex array
    glGenVertexArrays(1, &main_vertex_array);
    // Setup Program
    rend_bind();
    main_u_proj = glGetUniformLocation(main_program, "proj");
    main_u_view = glGetUniformLocation(main_program, "view");
    main_u_model = glGetUniformLocation(main_program, "model");
    glBindVertexArray(main_vertex_array);
    glEnableVertexAttribArray(MAIN_A_VERTICES);
    glEnableVertexAttribArray(MAIN_A_COLORS);
    glBindVertexArray(0);
    rend_unbind();
    // Create Triangle Buffer
    vertices_list.clear();
    vertices_list.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    vertices_list.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
    vertices_list.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
    glGenBuffers(1, &vertices_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices_list.size() * sizeof(glm::vec3), vertices_list.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Create Colors
    colors_list.clear();
    colors_list.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    colors_list.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors_list.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    glGenBuffers(1, &colors_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, colors_buffer);
    glBufferData(GL_ARRAY_BUFFER, colors_list.size() * sizeof(glm::vec4), colors_list.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void rend_release() {
    glDeleteBuffers(1, &colors_buffer);
    glDeleteBuffers(1, &vertices_buffer);
    vertices_list.clear();
    glDeleteVertexArrays(1, &main_vertex_array);
    rend_delete_program(main_program, {main_vertex_shader, main_fragment_shader});
    glDeleteShader(main_fragment_shader);
    glDeleteShader(main_vertex_shader);
}

void rend_clear(const glm::vec4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void rend_bind() {
    glUseProgram(main_program);
}

void rend_unbind() {
    glUseProgram(0);
}

void rend_setProjection(const glm::mat4& m) {
    glUniformMatrix4fv(main_u_proj, 1, GL_FALSE, &m[0][0]);
}

void rend_setView(const glm::mat4& m) {
    glUniformMatrix4fv(main_u_view, 1, GL_FALSE, &m[0][0]);
}

void rend_setModel(const glm::mat4& m) {
    glUniformMatrix4fv(main_u_model, 1, GL_FALSE, &m[0][0]);
}

void rend_draw() {
    glBindVertexArray(main_vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
    glVertexAttribPointer(MAIN_A_VERTICES, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, colors_buffer);
    glVertexAttribPointer(MAIN_A_COLORS, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawArrays(GL_TRIANGLES, 0, vertices_list.size());
    glBindVertexArray(0);
}

uint32_t rend_create_shader(GLenum type, std::string path) {
    uint32_t temp = glCreateShader(type);
    // Grab Shader source
    std::ifstream in(path);
    in.seekg(0, std::ios::end);
    size_t size = in.tellg();
    in.seekg(0, std::ios::beg);
    std::string src;
    src.resize(size);
    in.read(src.data(), src.size());
    in.close();
    std::cout << src << "\n";
    const char* c_src = src.c_str();
    glShaderSource(temp, 1, &c_src, nullptr);
    glCompileShader(temp);
    int len = 0;
    glGetShaderiv(temp, GL_INFO_LOG_LENGTH, &len);
    if(len > 0) {
        std::string log;
        log.resize(len);
        glGetShaderInfoLog(temp, log.size(), nullptr, log.data());
        std::cout << log << "\n";
    }
    return temp;
}

uint32_t rend_create_program(std::vector<uint32_t> shaders) {
    uint32_t temp = glCreateProgram();
    std::for_each(shaders.begin(), shaders.end(), [&](uint32_t shader) {
        glAttachShader(temp, shader);
    });
    glLinkProgram(temp);
    int len = 0;
    glGetProgramiv(temp, GL_INFO_LOG_LENGTH, &len);
    if(len > 0) {
        std::string log;
        log.resize(len);
        glGetProgramInfoLog(temp, log.size(), nullptr, log.data());
        std::cout << log << "\n";
    }
    return temp;
}

void rend_delete_program(uint32_t id, std::vector<uint32_t> shaders) {
    std::for_each(shaders.begin(), shaders.end(), [&](uint32_t shader) {
        glDetachShader(id, shader);
    });
    glDeleteProgram(id);
}
