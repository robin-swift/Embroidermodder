/*
 * Embroidermodder 2 (GLFW version)
 *
 * Copyright 2011-2024 The Embroidermodder Team
 * Embroidermodder 2 is Open Source Software, see LICENSE.md for licensing terms.
 *
 * Read the reference manual (https://www.libembroidery.org/downloads/emrm.pdf)
 * for advice on altering this file.
 *
 * Main window wrangling and drawing functions.
 */

#include <stdio.h>

#include "glad/glad.h"

#include <GLFW/glfw3.h>

#include "nanovg.h"
#define NANOVG_GLES2_IMPLEMENTATION
#include "nanovg_gl.h"

#include "core.h"

NVGcontext *vg;

GLFWwindow* create_window(int32_t width, int32_t height, const char *title);

void draw_rect(NVGcontext *vg, EmbRect rect, EmbColor color);
void draw_button(NVGcontext *vg, Button button, float *bounds);
void draw_text(NVGcontext *vg, int x, int y, char *font, char *txt, EmbColor color, float *bounds);
void draw_view(NVGcontext *vg, EmbRect container);
void draw_mdiarea(NVGcontext *vg, EmbRect container);
void draw_dockarea(NVGcontext *vg, EmbRect container);
void draw_nvg_toolbar(NVGcontext *vg, EmbRect container);
void draw_prompt(NVGcontext *vg, EmbRect container);
void draw_statusbar(NVGcontext *vg, EmbRect container);

int icon_size = 16;

Button menu_buttons[10];
Button tool_buttons_a[100];

/* FIXME: this is very system-dependant. Could compile in somehow? */
const char *sans_font = "/usr/share/fonts/truetype/open-sans/OpenSans-Regular.ttf";
const char *mono_font = "/usr/share/fonts/truetype/freefont/FreeMono.ttf";
const char *icon_font = "/usr/share/fonts/truetype/open-sans/OpenSans-Regular.ttf";

EmbColor toolbar_bg_color = {.r=128, .g=128, .b=128};
EmbColor toolbar_button_color = {.r=208, .g=208, .b=208};
EmbColor toolbar_text = {.r=0, .g=0, .b=0};
EmbColor prompt_bg_color = {.r=255, .g=255, .b=255};
EmbColor prompt_color = {.r=0, .g=0, .b=0};
EmbColor scrollbar_color = {.r=100, .g=100, .b=100};
int window_width = 640;
int window_height = 480;
int toolbar_height = 40;
float button_padding = 5.0;
float prompt_divider = 405.0F;
float statusbar_depth = 40.0F;

char prompt_text[50][MAX_STRING_LENGTH] = {
    "prompt> ",
    "",
    "",
    ""
};

int n_prompt_lines = 3;

/* . */
int
init_glfw(void)
{
    if (!load_data()) {
        puts("Failed to load data.");
        return 0;
    }

    if (!glfwInit()) {
        puts("Failed to run glfwInit.");
        return 0;
    }
    return 1;
}

/* Check this. */
uint32_t
RGB(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t result = 0xFF000000;
    result += 0x10000 * r;
    result += 0x100 * g;
    result += b;
    return result;
}

/* . */
void
update_all_background_color(uint32_t color)
{
    setBackgroundColor(color);
}

void
preview_update(void)
{
    useBackgroundLogo(setting[GENERAL_MDI_BG_USE_LOGO].preview.b);
    useBackgroundColor(setting[GENERAL_MDI_BG_USE_COLOR].preview.b);
    useBackgroundTexture(setting[GENERAL_MDI_BG_USE_TEXTURE].preview.b);
    update_all_view_scroll_bars(setting[DISPLAY_SHOW_SCROLLBARS].preview.b);
}

/* . */
void
update_view(void)
{
    useBackgroundLogo(setting[GENERAL_MDI_BG_USE_LOGO].dialog.b);
    useBackgroundTexture(setting[GENERAL_MDI_BG_USE_TEXTURE].dialog.b);
    useBackgroundColor(setting[GENERAL_MDI_BG_USE_COLOR].dialog.b);
    setBackgroundLogo(setting[GENERAL_MDI_BG_LOGO].dialog.s);
    setBackgroundTexture(setting[GENERAL_MDI_BG_TEXTURE].dialog.s);
    setBackgroundColor(setting[GENERAL_MDI_BG_COLOR].dialog.i);

    icon_resize(setting[GENERAL_ICON_SIZE].dialog.i);

    update_all_view_scroll_bars(setting[DISPLAY_SHOW_SCROLLBARS].dialog.b);
    update_all_view_cross_hair_colors(setting[DISPLAY_CROSSHAIR_COLOR].dialog.i);
    update_all_view_background_colors(setting[DISPLAY_BG_COLOR].dialog.i);
    update_all_view_select_box_colors(
        setting[DISPLAY_SELECTBOX_LEFT_COLOR].dialog.i,
        setting[DISPLAY_SELECTBOX_LEFT_FILL].dialog.i,
        setting[DISPLAY_SELECTBOX_RIGHT_COLOR].dialog.i,
        setting[DISPLAY_SELECTBOX_RIGHT_FILL].dialog.i,
        setting[DISPLAY_SELECTBOX_ALPHA].dialog.i);
    update_all_view_grid_colors(setting[GRID_COLOR].dialog.i);
    update_all_view_ruler_colors(setting[RULER_COLOR].dialog.i);

    set_prompt_text_color(setting[PROMPT_TEXT_COLOR].dialog.i);
    set_prompt_background_color(setting[PROMPT_BG_COLOR].dialog.i);
    set_prompt_font_family(setting[PROMPT_FONT_FAMILY].dialog.s);
    set_prompt_font_style(setting[PROMPT_FONT_STYLE].dialog.s);
    set_prompt_font_size(setting[PROMPT_FONT_SIZE].dialog.i);

    if (setting[LWT_SHOW_LWT].dialog.b) {
        enable_lwt();
    }
    else {
        disable_lwt();
    }
    if (setting[LWT_REAL_RENDER].dialog.b) {
        enable_real();
    }
    else {
        disable_real();
    }

    update_pick_add_mode(setting[SELECTION_MODE_PICKADD].dialog.b);
}

/* . */
void
mdiarea_set_bg(uint32_t color)
{
    setBackgroundColor(color);
}

/* . */
void
draw_rect(NVGcontext *vg, EmbRect rect, EmbColor color)
{
    nvgFillColor(vg, nvgRGBA(color.r, color.g, color.b, 255));

    nvgBeginPath(vg);
    nvgRect(vg, rect.x, rect.y, rect.w, rect.h);
    nvgFill(vg);
}

/* . */
void
draw_button(NVGcontext *vg, Button button, float *bounds)
{
    draw_rect(vg, button.rect, button.color);
    draw_text(vg,
        button.rect.x + 3.0F,
        button.rect.y + button.rect.h * 0.5F,
        button.font,
        button.text,
        button.text_color,
        bounds);
}

/* . */
void
draw_text(NVGcontext *vg, int x, int y, char *font, char *txt, EmbColor text_color, float *bounds)
{
    nvgBeginPath(vg);
    nvgFontSize(vg, 14.0F);
    nvgFontFace(vg, font);
    nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
    nvgFillColor(vg, nvgRGBA(text_color.r, text_color.g, text_color.b, 255));
    nvgTextBounds(vg, x, y, txt, NULL, bounds);
    nvgTextAlign(vg, NVG_ALIGN_LEFT);
    nvgText(vg, x, y, txt, NULL);
    nvgFill(vg);
}

/* . */
Button
make_menubar_button(NVGcontext *vg, int x, int y, char *text, float *bounds)
{
    Button button;
    nvgTextBounds(vg, x, y, text, NULL, bounds);
    EmbReal w = bounds[2] - bounds[0] + button_padding;
    button.rect = emb_rect(x, y, w, 30);
    button.color = toolbar_button_color;
    button.text_color = toolbar_text;
    string_copy(button.text, text);
    string_copy(button.font, "sans");
    button.state = 0;
    return button;
}

/* . */
Button
make_toolbar_button(int x, int y, char *text)
{
    Button button;
    button.rect = emb_rect(x, y, icon_size, icon_size);
    button.color = toolbar_button_color;
    button.text_color = toolbar_text;
    string_copy(button.text, text);
    string_copy(button.font, "icons");
    button.state = 0;
    return button;
}

/* . */
void
draw_menubar(NVGcontext *vg, EmbRect container)
{
    EmbRect rect = emb_rect(0, 0, window_width, toolbar_height);
    if (window_height > 1000) {
        rect.h = 50;
    }

    draw_rect(vg, rect, toolbar_bg_color);

    float bounds[4] = {0.0F, 0.0F, 0.0F, 0.0F};
    float x_offset = -button_padding;
    for (int i=0; state.menubar_full_list[i] != TERMINATOR_SYMBOL; i++) {
        x_offset += (bounds[2] - bounds[0]) + 2*button_padding;
        menu_buttons[i] = make_menubar_button(vg, x_offset, 3,
            state.menu_list[state.menubar_full_list[i]], bounds);
        draw_button(vg, menu_buttons[i], bounds);
    }
}

/* . */
void
draw_nvg_toolbar(NVGcontext *vg, EmbRect container)
{
    EmbRect rect = emb_rect(toolbar_height + button_padding, 0,
        window_width, toolbar_height);

    //draw_rect(vg, rect, toolbar_bg_color);

    float bounds[4] = {0.0F, 0.0F, 0.0F, 0.0F};
    for (int i=0; i<10; i++) {
        tool_buttons_a[i] = make_toolbar_button(5+5*i+16*i, 50, "Test");
        draw_button(vg, tool_buttons_a[i], bounds);
    }
}

/* . */
void
draw_view(NVGcontext *vg, EmbRect container)
{
    EmbRect rect = emb_rect(0, 405, window_width, 75);
    draw_rect(vg, rect, prompt_bg_color);

}

/* . */
void
draw_mdiarea(NVGcontext *vg, EmbRect container)
{
    if (numOfDocs == 0) {
    }
    else {
    }
}

/* . */
void
draw_dockarea(NVGcontext *vg, EmbRect container)
{

}

/* . */
void
draw_prompt(NVGcontext *vg, EmbRect container)
{
    float bounds[5];
    EmbRect rect = container;
    draw_rect(vg, rect, prompt_bg_color);
    EmbRect sb_rect = emb_rect(window_width - 20, 405, 20, 75);
    draw_rect(vg, sb_rect, scrollbar_color);
    for (int i=0; i<n_prompt_lines; i++) {
        draw_text(vg, 10, 425+i*3, "mono", prompt_text[i], prompt_color, bounds);
    }
}

/* . */
void
draw_statusbar(NVGcontext *vg, EmbRect container)
{

}

/* . */
void
draw_interface(NVGcontext *vg)
{
    draw_menubar(vg, emb_rect(0, 405, window_width, 75));
    draw_nvg_toolbar(vg, emb_rect(0, 405, window_width, 75));
    draw_mdiarea(vg, emb_rect(0, prompt_divider, window_width, 75));
    draw_prompt(vg, emb_rect(0, prompt_divider, window_width, 75));
    draw_statusbar(vg, emb_rect(0, 405, window_width, 75));
}

/* Set delta time, clear frame and resize. */
int
start_frame(GLFWwindow *window, EmbReal *prevt)
{
    EmbReal t = glfwGetTime();
    EmbReal dt = t - *prevt;
    printf("%f %f\n", t, dt);

    /* Cap at 120 updates a second. */
    if (dt < 1.0/120) {
        return 0;
    }
    *prevt = t;

    glfwGetWindowSize(window, &window_width, &window_height);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, window_width, window_height);
    nvgBeginFrame(vg, window_width, window_height, 1.0);
    return 1;
}

/* Swap buffers and poll events. */
void
end_frame(GLFWwindow *window)
{
    nvgEndFrame(vg);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

/* . */
void
render_messagebox(const char *logo, const char *title, const char *text)
{
    float bounds[5];
    EmbRect sb_rect = emb_rect(0, 0, window_width, window_height);
    draw_rect(vg, sb_rect, prompt_bg_color);
    draw_text(vg, 10, 40, "sans", title, prompt_color, bounds);
    draw_text(vg, 10, 80, "sans", text, prompt_color, bounds);
}

/* FIXME: error code */
void
messagebox(const char *logo, const char *title, const char *text)
{
    GLFWwindow* window = create_window(480, 200, title);

    EmbReal prevt = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        if (!start_frame(window, &prevt)) {
            continue;
        }
        render_messagebox(logo, title, text);
        end_frame(window);
    }
}

/* . */
GLFWwindow*
create_window(int32_t width, int32_t height, const char *title)
{
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        puts("Failed load GL function pointers with glad.");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_SAMPLES, 4);

    vg = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (!vg) {
        puts("Failed to initialize NanoVG.");
        return NULL;
    }

    /* FIXME: only works on linux and only works if adobe fonts are installed. */
    int font = nvgCreateFont(vg, "sans", sans_font);
    if (font == -1) {
        puts("Font failed to load.");
        return NULL;
    }
    font = nvgCreateFont(vg, "icons", icon_font);
    if (font == -1) {
        puts("Font failed to load.");
        return NULL;
    }
    font = nvgCreateFont(vg, "mono", mono_font);
    if (font == -1) {
        puts("Font failed to load.");
        return NULL;
    }
    return window;
}

int32_t
free_glfw(void)
{
    nvgDeleteGLES2(vg);
    glfwTerminate();
    return 0;
}

/* . */
int
glfw_application(int argc, char *argv[])
{
    GLFWwindow* window = create_window(640, 480, "Embroidermodder 2 (GLFW)");

    EmbReal prevt = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        if (!start_frame(window, &prevt)) {
            continue;
        }
        draw_interface(vg);
        end_frame(window);
    }
    return 0;
}
