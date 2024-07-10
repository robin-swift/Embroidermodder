/*
 * Embroidermodder 2.
 *
 * Copyright 2011-2024 The Embroidermodder Team
 * Embroidermodder 2 is Open Source Software, see LICENSE.md for licensing terms.
 * Visit https://www.libembroidery.org/refman for advice on altering this file,
 * or read the markdown version in embroidermodder2/docs/refman.
 *
 * Script
 */

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

#include "core.h"

#include "toml.h"

string_table coverage_test;

string_table menubar_full_list;
string_table menubar_no_docs;
string_table file_menu;
string_table edit_menu;
string_table view_menu;
string_table zoom_menu;
string_table pan_menu;
string_table help_menu;
string_table draw_menu;
string_table tools_menu;
string_table modify_menu;
string_table dimension_menu;
string_table sandbox_menu;

string_table toolbars_when_docs;
string_table file_toolbar;
string_table edit_toolbar;
string_table view_toolbar;
string_table zoom_toolbar;
string_table pan_toolbar;
string_table icon_toolbar;
string_table help_toolbar;
string_table draw_toolbar;
string_table inquiry_toolbar;
string_table modify_toolbar;
string_table dimension_toolbar;
string_table sandbox_toolbar;

char settings_general_language[MAX_STRING_LENGTH];
char settings_general_icon_theme[MAX_STRING_LENGTH];
int settings_general_icon_size;
bool settings_general_mdi_bg_use_logo;
bool settings_general_mdi_bg_use_texture;
bool settings_general_mdi_bg_use_color;
char settings_general_mdi_bg_logo[MAX_STRING_LENGTH];
char settings_general_mdi_bg_texture[MAX_STRING_LENGTH];
int32_t settings_general_mdi_bg_color;
bool settings_general_tip_of_the_day;
uint16_t settings_general_current_tip;
bool settings_general_system_help_browser;
bool settings_general_check_for_updates;
bool settings_display_use_opengl;
bool settings_display_renderhint_aa;
bool settings_display_renderhint_text_aa;
bool settings_display_renderhint_smooth_pix;
bool settings_display_renderhint_high_aa;
bool settings_display_renderhint_noncosmetic;
bool settings_display_show_scrollbars;
int settings_display_scrollbar_widget_num;
int32_t settings_display_crosshair_color;
int32_t settings_display_bg_color;
int32_t settings_display_selectbox_left_color;
int32_t settings_display_selectbox_left_fill;
int32_t settings_display_selectbox_right_color;
int32_t settings_display_selectbox_right_fill;
uint8_t settings_display_selectbox_alpha;
double settings_display_zoomscale_in;
double settings_display_zoomscale_out;
uint8_t settings_display_crosshair_percent;
char settings_display_units[MAX_STRING_LENGTH];
int32_t settings_prompt_text_color;
int32_t settings_prompt_bg_color;
char settings_prompt_font_family[MAX_STRING_LENGTH];
char settings_prompt_font_style[MAX_STRING_LENGTH];
uint8_t settings_prompt_font_size;
bool settings_prompt_save_history;
bool settings_prompt_save_history_as_html;
char settings_prompt_save_history_filename[MAX_STRING_LENGTH];
char settings_opensave_custom_filter[MAX_STRING_LENGTH];
char settings_opensave_open_format[MAX_STRING_LENGTH];
bool settings_opensave_open_thumbnail;
char settings_opensave_save_format[MAX_STRING_LENGTH];
bool settings_opensave_save_thumbnail;
uint8_t settings_opensave_recent_max_files;
char settings_opensave_recent_list_of_files[MAX_FILES][MAX_STRING_LENGTH];
char settings_opensave_recent_directory[MAX_STRING_LENGTH];
uint8_t settings_opensave_trim_dst_num_jumps;
char settings_printing_default_device[MAX_STRING_LENGTH];
bool settings_printing_use_last_device;
bool settings_printing_disable_bg;
bool settings_grid_show_on_load;
bool settings_grid_show_origin;
bool settings_grid_color_match_crosshair;
int32_t settings_grid_color;
bool settings_grid_load_from_file;
char settings_grid_type[MAX_STRING_LENGTH];
bool settings_grid_center_on_origin;
double settings_grid_center_x;
double settings_grid_center_y;
double settings_grid_size_x;
double settings_grid_size_y;
double settings_grid_spacing_x;
double settings_grid_spacing_y;
double settings_grid_size_radius;
double settings_grid_spacing_radius;
double settings_grid_spacing_angle;
bool settings_ruler_show_on_load;
bool settings_ruler_metric;
int32_t settings_ruler_color;
uint8_t settings_ruler_pixel_size;
bool settings_qsnap_enabled;
int32_t settings_qsnap_locator_color;
uint8_t settings_qsnap_locator_size;
uint8_t settings_qsnap_aperture_size;
bool settings_qsnap_endpoint;
bool settings_qsnap_midpoint;
bool settings_qsnap_center;
bool settings_qsnap_node;
bool settings_qsnap_quadrant;
bool settings_qsnap_intersection;
bool settings_qsnap_extension;
bool settings_qsnap_insertion;
bool settings_qsnap_perpendicular;
bool settings_qsnap_tangent;
bool settings_qsnap_nearest;
bool settings_qsnap_apparent;
bool settings_qsnap_parallel;
bool settings_lwt_show_lwt;
bool settings_lwt_real_render;
double settings_lwt_default_lwt;
bool settings_selection_mode_pickfirst;
bool settings_selection_mode_pickadd;
bool settings_selection_mode_pickdrag;
int32_t settings_selection_coolgrip_color;
int32_t settings_selection_hotgrip_color;
uint8_t settings_selection_grip_size;
uint8_t settings_selection_pickbox_size;
char settings_text_font[MAX_STRING_LENGTH];
double settings_text_size;
double settings_text_angle;
bool settings_text_style_bold;
bool settings_text_style_italic;
bool settings_text_style_underline;
bool settings_text_style_overline;
bool settings_text_style_strikeout;

const char *index_name[] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven"
};

const char *index_th_name[] = {
    "first",
    "second",
    "third",
    "fourth",
    "fifth",
    "sixth",
    "seventh"
};

ScriptValue script_null = {
    .r = 0.0f,
    .i = 0,
    .b = false,
    .s = "",
    .label = "NULL",
    .type = SCRIPT_NULL
};

ScriptValue script_true = {
    .r = 0.0f,
    .i = 1,
    .b = true,
    .s = "",
    .label = "true",
    .type = SCRIPT_BOOL
};

ScriptValue script_false = {
    .r = 0.0f,
    .i = 0,
    .b = false,
    .s = "",
    .label = "false",
    .type = SCRIPT_BOOL
};

ScriptValue
test_command(ScriptEnv *context)
{
    return script_true;
}

/* TODO: remove args command, use the command_data table
 */
int
argument_checks(ScriptEnv *context, char *function, const char *args)
{
    char s[200];
    int i;
    if (context->argumentCount != strlen(args)) {
        sprintf(s, "%s() requires %d arguments.", function, context->argumentCount);
        prompt_output(s);
        return 0;
    }
    for (i=0; args[i]; i++) {
        if (args[i] == 'r') {
            if (context->argument[i].type != SCRIPT_REAL) {
                sprintf(s,
                    "TYPE_ERROR, %s(): %s argument is not a real number.",
                    function, index_th_name[i]);
                prompt_output(s);
                return 0;
            }
            float variable = context->argument[i].r;
            if (isnan(variable)) {
                sprintf(s,
                    "TYPE_ERROR, %s(): %s argument is not a real number.",
                    function, index_th_name[i]);
                prompt_output(s);
                return 0;
            }
        }
        if (args[i] == 'i') {
            if (context->argument[i].type != SCRIPT_INT) {
                sprintf(s,
                    "TYPE_ERROR, %s(): %s argument is not an integer.",
                    function, index_th_name[i]);
                prompt_output(s);
                return 0;
            }
        }
        if (args[i] == 'b') {
            if (context->argument[i].type != SCRIPT_BOOL) {
                sprintf(s,
                    "TYPE_ERROR, %s(): %s argument is not a boolean.",
                    function, index_th_name[i]);
                prompt_output(s);
                return 0;
            }
        }
        if (args[i] == 's') {
            if (context->argument[i].type != SCRIPT_STRING) {
                sprintf(s,
                    "TYPE_ERROR, %s(): %s argument is not a string.",
                    function, index_th_name[i]);
                prompt_output(s);
                return 0;
            }
        }
    }
    return 1;
}

char *
translate(char *msg)
{
    return msg;
}

ScriptEnv *
create_script_env()
{
    ScriptEnv *context = (ScriptEnv*)malloc(sizeof(ScriptEnv));
    context->argumentCount = 0;
    context->n_variables = 0;
    return context;
}

void
add_string_variable(ScriptEnv *context, const char *label, const char *s)
{
    strcpy(context->variable[context->n_variables].label, label);
    strcpy(context->variable[context->n_variables].s, s);
    context->variable[context->n_variables].type = SCRIPT_STRING;
    context->n_variables++;
}

void
add_int_variable(ScriptEnv *context, const char *label, int i)
{
    strcpy(context->variable[context->n_variables].label, label);
    context->variable[context->n_variables].i = i;
    context->variable[context->n_variables].type = SCRIPT_INT;
    context->n_variables++;
}

void
add_real_variable(ScriptEnv *context, const char *label, double r)
{
    strcpy(context->variable[context->n_variables].label, label);
    context->variable[context->n_variables].r = r;
    context->variable[context->n_variables].type = SCRIPT_REAL;
    context->n_variables++;
}

const char *
script_get_string(ScriptEnv *context, const char *label)
{
    int i;
    for (i=0; i<context->n_variables; i++) {
        if (!strcmp(context->variable[i].label, label)) {
            return context->variable[i].s;
        }
    }
    return "ERROR: string not found.";
}

int
script_get_int(ScriptEnv *context, const char *label)
{
    int i;
    for (i=0; i<context->n_variables; i++) {
        if (!strcmp(context->variable[i].label, label)) {
            return context->variable[i].i;
        }
    }
    return -1;
}

double
script_get_real(ScriptEnv *context, const char *label)
{
    int i;
    for (i=0; i<context->n_variables; i++) {
        if (!strcmp(context->variable[i].label, label)) {
            return context->variable[i].r;
        }
    }
    return -1.0;
}

int
script_set_string(ScriptEnv *context, const char *label, const char *s)
{
    int i;
    for (i=0; i<context->n_variables; i++) {
        if (!strcmp(context->variable[i].label, label)) {
            strcpy(context->variable[i].s, s);
            return 1;
        }
    }
    return 0;
}

int
script_set_int(ScriptEnv *context, const char *label, int x)
{
    int i;
    for (i=0; i<context->n_variables; i++) {
        if (!strcmp(context->variable[i].label, label)) {
            context->variable[i].i = x;
            return 1;
        }
    }
    return 0;
}

int
script_set_real(ScriptEnv *context, const char *label, double r)
{
    int i;
    for (i=0; i<context->n_variables; i++) {
        if (!strcmp(context->variable[i].label, label)) {
            context->variable[i].r = r;
            return 1;
        }
    }
    return 0;
}

void
free_script_env(ScriptEnv* context)
{
    free(context);
}

ScriptValue
script_bool(bool b)
{
    ScriptValue value;
    value.type = SCRIPT_BOOL;
    value.b = b;
    return value;
}

ScriptValue
script_int(int i)
{
    ScriptValue value;
    value.type = SCRIPT_INT;
    value.i = i;
    return value;
}

ScriptValue
script_real(double r)
{
    ScriptValue value;
    value.type = SCRIPT_REAL;
    value.r = r;
    return value;
}

ScriptValue
script_string(const char *s)
{
    ScriptValue value;
    value.type = SCRIPT_STRING;
    strcpy(value.s, s);
    return value;
}

/* These pack the arguments for function calls in the command environment. */
ScriptEnv *
add_string_argument(ScriptEnv *context, const char *s)
{
    strcpy(context->argument[context->argumentCount].s, s);
    context->argument[context->argumentCount].type = SCRIPT_STRING;
    context->argumentCount++;
    return context;
}

ScriptEnv *
add_real_argument(ScriptEnv *context, double r)
{
    context->argument[context->argumentCount].r = r;
    context->argument[context->argumentCount].type = SCRIPT_REAL;
    context->argumentCount++;
    return context;
}

ScriptEnv *
add_int_argument(ScriptEnv *context, int i)
{
    context->argument[context->argumentCount].i = i;
    context->argument[context->argumentCount].type = SCRIPT_INT;
    context->argumentCount++;
    return context;
}

int
parse_floats(char *line, float result[], int n)
{
    char substring[100];
    char *c;
    int i = 0;
    int pos = 0;
    for (c=line; *c; c++) {
        substring[pos] = *c;
        if (*c == ',' || *c == ' ') {
            substring[pos] = 0;
            result[i] = atof(substring);
            pos = 0;
            i++;
            if (i > n-1) {
                return -1;
            }
        }
        else {
            pos++;
        }
    }
    substring[pos] = 0;
    result[i] = atof(substring);
    return i+1;
}

int
parse_vector(char *line, EmbVector *v)
{
    float v_[2];
    if (parse_floats(line, v_, 2) == 2) {
        return 0;
    }
    v->x = v_[0];
    v->y = v_[1];
    return 1;
}

/* FIXME: parse strings arguments with quotes.
 *
 * There are 5 steps to the parsing algorithm:
 *     1. Split the string into string arguments in the style of "argc, argv".
 *     2. Identify the command by the first argument.
 *     3. Process arguments into ScriptValues.
 *     4. Check that the arguments parsed matched the required arguments for that
 *        commands.
 *     5. Call the main function.
 */
ScriptValue
command_prompt(ScriptEnv *context, const char *line)
{
    /* Split arguments into seperate strings. */
    int i;
    char args[10][MAX_STRING_LENGTH];
    char *c;
    int n_args = 0;
    int str_pos = 0;
    for (c=(char*)line; *c; c++) {
        args[n_args][str_pos] = *c;
        if (*c == ' ') {
            args[n_args][str_pos] = 0;
            n_args++;
            str_pos = 0;
        }
        else {
            str_pos++;
        }
    }
    args[n_args][str_pos] = 0;

    /* Identify function. */
    int function = -1;
    for (i=0; command_data[i].id != -2; i++) {
        if (!strcmp(command_data[i].icon, args[0])) {
            function = i;
            break;
        }
    }
    if (function < 0) {
        return script_false;
    }

    /* Check there are enough arguments. */
    if (strlen(command_data[function].arguments) != n_args) {
        return script_false;
    }

    /* Parse arguments into ScriptValues. */
    if (n_args > 1) {
        for (i=1; i<n_args; i++) {
            switch (command_data[function].arguments[i]) {
            case 'i':
            case 'b':
                context = add_int_argument(context, atoi(args[i-1]));
                break;
            case 's':
                context = add_string_argument(context, args[i-1]);
                break;
            case 'r':
                context = add_real_argument(context, atof(args[i-1]));
                break;
            default:
                break;
            }
        }
    }

    /* Call command's main. */
    return command_data[function].main(context);
}

bool
validRGB(float r, float g, float b)
{
    if (isnan(r)) {
        return false;
    }
    if (isnan(g)) {
        return false;
    }
    if (isnan(b)) {
        return false;
    }
    if (r < 0 || r > 255) {
        return false;
    }
    if (g < 0 || g > 255) {
        return false;
    }
    if (b < 0 || b > 255) {
        return false;
    }
    return true;
}

int
string_array_length(string_table s)
{
    int i;
    int max_length = 1000;
    for (i=0; i<max_length; i++) {
        if (!strncmp(s[i], "END", MAX_COMMAND_LENGTH)) {
            return i;
        }
    }
    prompt_output("END symbol missing from string array.");
    return max_length;
}

int
load_string_table(toml_table_t* conf, char *table_name, string_table table)
{
    toml_array_t* str_table = toml_array_in(conf, table_name);
    toml_datum_t str;
    for (int i=0; ; i++) {
        str = toml_string_at(str_table, i);
        if (!str.ok) {
            strncpy(table[i], "END", MAX_COMMAND_LENGTH);
            break;
        }
        else {
            strncpy(table[i], str.u.s, MAX_COMMAND_LENGTH);
        }
    }

    free(str.u.s);
    return 1;
}

toml_table_t *
load_data_file(char *fname)
{
    FILE* file;
    char error_buffer[200];
    toml_table_t *conf;

    file = fopen(fname, "r");
    if (!file) {
        printf("ERROR: Failed to open \"%s\".\n", fname);
        return NULL;
    }

    conf = toml_parse_file(file, error_buffer, sizeof(error_buffer));
    fclose(file);

    if (!conf) {
        printf("ERROR: Failed to parse \"%s\".\n", fname);
        printf("    %s\n", error_buffer);
        return NULL;
    }
    return conf;
}

int
load_data(void)
{
    toml_table_t *conf = load_data_file("data/menus.toml");
    if (!conf) {
        return 0;
    }
    if (!load_string_table(conf, "menubar_full_list", menubar_full_list)) {
        return 0;
    }
    if (!load_string_table(conf, "menubar_no_docs", menubar_no_docs)) {
        return 0;
    }
    if (!load_string_table(conf, "file_menu", file_menu)) {
        return 0;
    }
    if (!load_string_table(conf, "edit_menu", edit_menu)) {
        return 0;
    }
    if (!load_string_table(conf, "view_menu", view_menu)) {
        return 0;
    }
    if (!load_string_table(conf, "zoom_menu", zoom_menu)) {
        return 0;
    }
    if (!load_string_table(conf, "pan_menu", pan_menu)) {
        return 0;
    }
    if (!load_string_table(conf, "help_menu", help_menu)) {
        return 0;
    }
    if (!load_string_table(conf, "draw_menu", draw_menu)) {
        return 0;
    }
    if (!load_string_table(conf, "tools_menu", tools_menu)) {
        return 0;
    }
    if (!load_string_table(conf, "modify_menu", modify_menu)) {
        return 0;
    }
    if (!load_string_table(conf, "dimension_menu", dimension_menu)) {
        return 0;
    }
    if (!load_string_table(conf, "sandbox_menu", sandbox_menu)) {
        return 0;
    }
    toml_free(conf);

    conf = load_data_file("data/toolbars.toml");
    if (!conf) {
        return 0;
    }
    if (!load_string_table(conf, "toolbars_when_docs", toolbars_when_docs)) {
        return 0;
    }
    if (!load_string_table(conf, "file_toolbar", file_toolbar)) {
        return 0;
    }
    if (!load_string_table(conf, "edit_toolbar", edit_toolbar)) {
        return 0;
    }
    if (!load_string_table(conf, "view_toolbar", view_toolbar)) {
        return 0;
    }
    if (!load_string_table(conf, "zoom_toolbar", zoom_toolbar)) {
        return 0;
    }
    if (!load_string_table(conf, "pan_toolbar", pan_toolbar)) {
        return 0;
    }
    if (!load_string_table(conf, "icon_toolbar", icon_toolbar)) {
        return 0;
    }
    if (!load_string_table(conf, "help_toolbar", help_toolbar)) {
        return 0;
    }
    if (!load_string_table(conf, "draw_toolbar", draw_toolbar)) {
        return 0;
    }
    if (!load_string_table(conf, "inquiry_toolbar", inquiry_toolbar)) {
        return 0;
    }
    if (!load_string_table(conf, "modify_toolbar", modify_toolbar)) {
        return 0;
    }
    if (!load_string_table(conf, "dimension_toolbar", dimension_toolbar)) {
        return 0;
    }
    if (!load_string_table(conf, "sandbox_toolbar", sandbox_toolbar)) {
        return 0;
    }
    toml_free(conf);

    conf = load_data_file("data/testing.toml");
    if (!conf) {
        return 0;
    }
    if (!load_string_table(conf, "coverage_test", coverage_test)) {
        return 0;
    }
    toml_free(conf);

    conf = load_data_file("data/commands.toml");
    if (!conf) {
        return 0;
    }

    toml_free(conf);
    return 1;
}

int
load_settings(char *appDir, char *configDir)
{
    char fname[200];
    sprintf(fname, "%s/settings.toml", configDir);
    toml_table_t *conf = load_data_file(fname);
    if (!conf) {
        toml_free(conf);
        return 0;
    }

    toml_free(conf);
    return 1;
}

int
save_settings(char *appDir, char *configDir)
{
    char fname[200];
    sprintf(fname, "%s/settings.toml", configDir);
    FILE *f = fopen(fname, "w");
    if (!f) {
        return 0;
    }

    fclose(f);
    return 1;
}