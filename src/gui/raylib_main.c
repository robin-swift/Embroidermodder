/*
 * Embroidermodder 2 -- Command Prompt
 * Copyright 2011-2026 The Embroidermodder Team
 */

#include <stdio.h>

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#undef PI
#include "core.h"

static Texture2D new_icon;

static int window_width = 840;
static int window_height = 600;
static int menu_depth = 30;
static int icon_size = 16;
static int statusbar_depth = 10;
static int padding_width = 10;
static int padding_height = 10;
static int icon_padding = 3;
static bool check = false;
static bool show_menu = false;
static int row_height = 40;
static int padding = 10;

static Rectangle menu_rect;
static Rectangle top_tb_rect;
static Rectangle prompt_rect;
static Rectangle left_tb_rect;
static Rectangle widgets_rect;
static Rectangle view_rect;
static Rectangle statusbar_rect;

void
render_menu(void)
{

}

void
render_menubar(void)
{
    int cursor_x = padding;
    int cursor_y = padding;
    DrawRectangleRec(menu_rect, GRAY);
    if (GuiButton((Rectangle){cursor_x, cursor_y, 40, menu_depth},
        "File")) {
        show_menu = !show_menu;
    }
    cursor_x += 40;
    if (GuiButton((Rectangle){cursor_x, cursor_y, 40, menu_depth},
        "Edit")) {
        show_menu = !show_menu;
    }
    cursor_x += 40;
    if (GuiButton((Rectangle){cursor_x, cursor_y, 40, menu_depth},
        "View")) {
        show_menu = !show_menu;
    }
    cursor_x += 40;
    if (GuiButton((Rectangle){cursor_x, cursor_y, 40, menu_depth},
        "Draw")) {
        show_menu = !show_menu;
    }
    cursor_x += 40;
    if (GuiButton((Rectangle){cursor_x, cursor_y, 40, menu_depth},
        "Tools")) {
        show_menu = !show_menu;
    }
    cursor_x += 40;
    if (GuiButton((Rectangle){cursor_x, cursor_y, 40, menu_depth},
        "Modify")) {
        show_menu = !show_menu;
    }
    cursor_x += 40;
    if (GuiButton((Rectangle){cursor_x, cursor_y, 60, menu_depth},
        "Dimension")) {
        show_menu = !show_menu;
    }
    cursor_x += 60;
    if (GuiButton((Rectangle){cursor_x, cursor_y, 40, menu_depth},
        "Window")) {
        show_menu = !show_menu;
    }
    cursor_x += 40;
    if (GuiButton((Rectangle){cursor_x, cursor_y, 40, menu_depth},
        "Help")) {
        show_menu = !show_menu;
    }
}

void
render_toolbars(void)
{
    DrawTexture(new_icon, 100 + icon_size/2, 100 + icon_size/2, WHITE);
    for (int i=0; file_toolbar_data[i][0] != '^'; i++) {
        int x_pos = top_tb_rect.x + (padding + icon_size) * i;
        int y_pos = top_tb_rect.y + padding;
    }
}

void
render_widgets(void)
{

}

void
render_view(void)
{

}

/* We don't have a widget packing algorithm so we manually calculate
 * every rectangle on screen here based on the current dimensions.
 */
void
calculate_window_areas(void)
{
    int window_width = GetRenderWidth();
    int window_height = GetRenderHeight();

    menu_rect.x = 0;
    menu_rect.y = 0;
    menu_rect.width = window_width;
    menu_rect.height = menu_depth;

    top_tb_rect.x = menu_rect.height;
    top_tb_rect.y = 100;
    top_tb_rect.width = window_width;
    top_tb_rect.height = menu_depth; /* TODO: calculate the number of icons deep the top toolbar will be. */

    /* FIXME */
    prompt_rect.x = 0;
    prompt_rect.y = 0;
    prompt_rect.width = 0;
    prompt_rect.height = 0;

    /* FIXME */
    view_rect.x = 0;
    view_rect.y = 0;
    view_rect.width = 0;
    view_rect.height = 0;

    left_tb_rect.x = top_tb_rect.x + top_tb_rect.height;
    left_tb_rect.y = 0;
    left_tb_rect.width = menu_depth; /* TODO: calculate the number of icons deep the left toolbar will be. */
    left_tb_rect.height = prompt_rect.x;

    statusbar_rect.x = 0;
    statusbar_rect.y = window_width - statusbar_depth;
    statusbar_rect.width = window_width;
    statusbar_rect.height = statusbar_depth;
}

int
raylib_main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(window_width, window_height, "Embroidermodder (raylib)");

    Image image = LoadImage("icons/defaults/new.png");    
    Texture2D new_icon = LoadTextureFromImage(image);
    UnloadImage(image);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        calculate_window_areas();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        int cursor_x = padding;
        int cursor_y = padding;

/*
        if (show_menu) {
            if (FocussedGuiRect(menu_rect)) {
            }
        }
        */

        DrawRectangleRec(top_tb_rect, GRAY);
        DrawRectangleRec(prompt_rect, GRAY);
        DrawRectangleRec(view_rect, WHITE);
        DrawRectangleRec(left_tb_rect, GRAY);
        DrawRectangleRec(statusbar_rect, GRAY);

        render_menubar();
        render_toolbars();

        /*
        DrawText("Hello, World.", cursor_x, cursor_y+100, 20, RED);
        cursor_y += 20 + padding;
        */

        if (GuiButton((Rectangle){cursor_x, cursor_y, 30, 30},
            GuiIconText(ICON_FILE_SAVE, "Save File"))) {
            show_menu = !show_menu;
        }
        cursor_y += 30 + padding;

        if (show_menu) {
            GuiCheckBox((Rectangle){cursor_x, cursor_y, icon_size, icon_size},
                "CHECK", &check);
            cursor_y += icon_size + padding;
        }

        EndDrawing();
    }

    UnloadTexture(new_icon);
    CloseWindow();
    return 1;
}

