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

#include <GL/glew.h>

#define GLFW_INCLUDE_GLEXT
#include "GLFW/glfw3.h"

#include "nanovg.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_gl.h"

#include "core.h"

typedef struct Button_ {
    EmbRect rect;
    EmbColor color;
    EmbColor highlight_color;
    EmbString text;
    EmbString font;
    EmbColor text_color;
    int state;
} Button;

typedef struct Tab_ {
    int state;
} Tab;

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
Button tool_buttons[100];

/* FIXME: this is very system-dependant. Could compile in somehow? */
char *sans_font = "/usr/share/fonts/truetype/open-sans/OpenSans-Regular.ttf";
char *mono_font = "/usr/share/fonts/truetype/freefont/FreeMono.ttf";
char *icon_font = "/usr/share/fonts/truetype/open-sans/OpenSans-Regular.ttf";

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
float prompt_divider = 405.0;
float statusbar_depth = 40.0;

char prompt_text[50][MAX_STRING_LENGTH] = {
    "prompt> ",
    "",
    "",
    ""
};

int n_prompt_lines = 3;

void
iconResize(int size)
{
    icon_size = size;
}

int32_t
activeDocument(void)
{
    return 0;
}

/* Dummy Functions so GLFW version compiles. */
#define DUMMY_COMMAND(name) \
    ScriptValue \
    name(ScriptEnv *context) \
    { \
        return script_false; \
    }

#define BASIC_DOC_F(name) \
    void name(int32_t doc) {}

#define NO_ARG_F(name) \
    void name(void) {}

BASIC_DOC_F(doc_clear_selection)
BASIC_DOC_F(doc_select_all)
BASIC_DOC_F(doc_preview_off)
BASIC_DOC_F(doc_vulcanize_rubber_room)
BASIC_DOC_F(doc_pan_left)
BASIC_DOC_F(doc_pan_right)
BASIC_DOC_F(doc_pan_up)
BASIC_DOC_F(doc_pan_down)
BASIC_DOC_F(doc_clear_rubber_room)
BASIC_DOC_F(doc_cut)
BASIC_DOC_F(doc_copy)
BASIC_DOC_F(doc_paste)

void doc_show_scroll_bars(int32_t doc, bool) {}
void doc_set_select_box_colors(int32_t doc, uint32_t, uint32_t, uint32_t, uint32_t, int) {}

DUMMY_COMMAND(add_circle_command)
DUMMY_COMMAND(add_dimleader_command)
DUMMY_COMMAND(add_ellipse_command)
DUMMY_COMMAND(add_line_command)
DUMMY_COMMAND(add_point_command)
DUMMY_COMMAND(add_rectangle_command)
DUMMY_COMMAND(add_slot_command)
DUMMY_COMMAND(add_textsingle_command)
DUMMY_COMMAND(previewon_command)

uint32_t create_arc(EmbArc arc, uint32_t) {return 0;}
void doc_undoable_add_obj(int32_t doc_index, uint32_t id, int rubberMode) {}

NO_ARG_F(undo_command)
NO_ARG_F(redo_command)
NO_ARG_F(new_file)
NO_ARG_F(help)
NO_ARG_F(about_dialog)
NO_ARG_F(tipOfTheDay)
NO_ARG_F(whats_this_mode)
NO_ARG_F(window_close_all)
NO_ARG_F(window_cascade)
NO_ARG_F(window_tile)
NO_ARG_F(window_next)
NO_ARG_F(window_previous)
NO_ARG_F(restore_cursor)
NO_ARG_F(wait_cursor)

void nanosleep_(int) {}

DocumentData* doc_data(int32_t) {return NULL;}

EmbRect obj_rect(ObjectCore *) {return emb_rect(0.0,0.0,1.0,1.0);}

ObjectCore *get_obj_core(uint32_t) {return NULL;}

void doc_set_bool(int32_t doc, const char *key, bool) {}
bool doc_get_bool(int32_t doc, const char *key) { return true; }
double doc_width(int32_t doc) {return 0.0;}
double doc_height(int32_t doc) {return 0.0;}
EmbVector doc_map_to_scene(int32_t doc, EmbVector v) {return v;}
EmbVector doc_map_from_scene(int32_t doc, EmbVector v) {return v;}
void doc_set_background_color(int doc_index, uint32_t color) {}
void settingsDialog(EmbString s) {}
void doc_move_selected(int32_t doc, double x, double y) {}
void doc_delete_selected(int32_t doc) {}
void doc_rotate_selected(int32_t doc, double, double, double) {}
void doc_mirror_selected(int32_t doc, double, double, double, double) {}
void doc_set_rubber_point(int32_t doc, EmbString key, EmbVector point) {}
void doc_set_rubber_text(int32_t doc, EmbString key, EmbString value) {}
void setPromptFontFamily(char *) {}
void setPromptFontStyle(char *) {}
void setPromptFontSize(int) {}
void doc_spare_rubber(int32_t doc, int64_t mode) {}
void doc_set_rubber_mode(int32_t doc, int32_t mode) {}
void doc_scale_selected(int32_t doc, double, double, double) {}
int doc_num_selected(int32_t doc) { return 0; }
void doc_preview_on(int32_t doc, int clone, int mode, double x, double y, double data) {}
void create_details_dialog(void) {}
void onCloseWindow(void) {}
void doc_center_on(int32_t doc, EmbVector v) {}
EmbVector scene_get_point(EmbString key) { return emb_vector(0.0, 0.0); }
void doc_zoom_extents(int doc_index) {}
void updatePickAddMode(bool val) {}
void clear_selection(void) {}
void doc_create_grid(int doc, char*) {}
void end_command(void) {}
void start_blinking(void) {}
void doc_update(int32_t) {}
void set_CursorShape(char *) {}
uint32_t rgb(uint8_t r, uint8_t g, uint8_t b) {return 0;}
void question_box(const char *, const char *) {}
void warning_box(const char *, const char *) {}
void critical_box(const char *, const char *) {}
void information_box(const char *, const char *) {}
void obj_set_text(ObjectCore *obj, const char *text) {}

/* TODO: Clear up memory. */
void
exit_program(void)
{
    exit(0);
}

EmbVector
doc_center(int32_t doc)
{
    return emb_vector(0.0, 0.0);
}

void
openFile(bool recent, EmbString recentFile)
{
}

/* check this */
uint32_t
qRgb(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t result = 0xFF000000;
    result += 0x10000 * r;
    result += 0x100 * g;
    result += b;
    return result;
}

/* . */
void
prompt_output(const char *line)
{
    printf("%s\n", line);
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
        button.rect.x + 3.0,
        button.rect.y + button.rect.h * 0.5,
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
    nvgFontSize(vg, 14.0f);
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
    double w = bounds[2] - bounds[0] + button_padding;
    button.rect = emb_rect(x, y, w, 30);
    button.color = toolbar_button_color;
    button.text_color = toolbar_text;
    strcpy(button.text, text);
    strcpy(button.font, "sans");
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
    strcpy(button.text, text);
    strcpy(button.font, "icons");
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

    float bounds[4] = {0.0, 0.0, 0.0, 0.0};
    float x_offset = -button_padding;
    for (int i=0; menubar_full_list[i] != TERMINATOR_SYMBOL; i++) {
        x_offset += (bounds[2] - bounds[0]) + 2*button_padding;
        menu_buttons[i] = make_menubar_button(vg, x_offset, 3,
            menu_list[menubar_full_list[i]], bounds);
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

    float bounds[4] = {0.0, 0.0, 0.0, 0.0};
    for (int i=0; i<10; i++) {
        tool_buttons[i] = make_toolbar_button(5+5*i+16*i, 50, "Test");
        draw_button(vg, tool_buttons[i], bounds);
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

/* . */
int
make_application(int argc, char *argv[])
{
    GLFWwindow* window;
    GLFWvidmode vidmode;

    if (!load_data()) {
        return 1;
    }

    if (!glfwInit()) {
        return 2;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(640, 480, "Embroidermodder 2 (GLFW)", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return 3;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return 4;
    }

    NVGcontext *vg = nvgCreateGL2(NVG_STENCIL_STROKES | NVG_DEBUG);
    if (!vg) {
        puts("Failed to initialize NanoVG.");
        return 5;
    }

    double prevt = glfwGetTime();

    /* FIXME: only works on linux and only works if adobe fonts are installed. */
    int font = nvgCreateFont(vg, "sans", sans_font);
    if (font == -1) {
        puts("Font failed to load.");
        return 6;
    }
    font = nvgCreateFont(vg, "icons", icon_font);
    if (font == -1) {
        puts("Font failed to load.");
        return 6;
    }
    font = nvgCreateFont(vg, "mono", mono_font);
    if (font == -1) {
        puts("Font failed to load.");
        return 6;
    }

    while (!glfwWindowShouldClose(window)) {
        double t = glfwGetTime();
        double dt = t - prevt;
        printf("%f %f\n", t, dt);

        /* Cap at 120 updates a second. */
        if (dt < 1.0/120) {
            continue;
        }
        prevt = t;

        glfwGetWindowSize(window, &window_width, &window_height);

        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, window_width, window_height);

        nvgBeginFrame(vg, window_width, window_height, 1.0);

        draw_interface(vg);
        
        nvgEndFrame(vg);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    nvgDeleteGL2(vg);
    glfwTerminate();
    return 0;
}

