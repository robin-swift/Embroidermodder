/*
 * Embroidermodder 2 -- Settings
 * Copyright 2011-2026 The Embroidermodder Team
 */

#include <string.h>

#include "core.h"

uint32_t
rgb(uint8_t r, uint8_t g, uint8_t b)
{
    return 0xFF000000 + 0x10000 * r + 0x100 * g + b;
}

/*
 * This allocates any memory needed for settings and sets reasonable default values.
 * FIXME: Switch over to the returning a pointer convention. (See the style section of CONTRIBUTING.md)
 */
void
settings_create(Settings *settings)
{
    char buffer[2000];

    /* General */
    strcpy(settings->general_language, "default");
    strcpy(settings->general_icon_theme, "default");
    settings->general_icon_size = 16;
    settings->general_mdi_bg_use_logo = true;
    settings->general_mdi_bg_use_texture = true;
    settings->general_mdi_bg_use_color = true;
    sprintf(settings->general_mdi_bg_logo,
        "%s/images/logo-spirals.png", state.app_dir);
    sprintf(settings->general_mdi_bg_texture,
        "%s/images/texture-spirals.png", state.app_dir);
    settings->general_mdi_bg_color = rgb(192, 192, 192);
    settings->general_tip_of_the_day = true;
    settings->general_current_tip = 0;
    settings->general_system_help_browser = true;

    /* Display */
    settings->display_use_opengl = false;
    settings->display_renderhint_aa = false;
    settings->display_renderhint_text_aa = false;
    settings->display_renderhint_smooth_pix = false;
    settings->display_renderhint_high_aa = false;
    settings->display_renderhint_noncosmetic = false;
    settings->display_show_scrollbars = true;
    settings->display_scrollbar_widget_num = 0;
    settings->display_crosshair_color = rgb(0, 0, 0);
    settings->display_bg_color = rgb(235, 235, 235);
    settings->display_selectbox_left_color = rgb(0, 128, 0);
    settings->display_selectbox_left_fill = rgb(0, 255, 0);
    settings->display_selectbox_right_color = rgb(0, 0, 128);
    settings->display_selectbox_right_fill = rgb(0, 0, 255);
    settings->display_selectbox_alpha = 32;
    settings->display_zoomscale_in = 2.0;
    settings->display_zoomscale_out = 0.5;
    settings->display_crosshair_percent = 5;
    strcpy(settings->display_units, "mm");

    /* Prompt */
    settings->prompt_text_color = rgb(  0,  0,  0);
    settings->prompt_bg_color = rgb(255,255,255);
    strcpy(settings->prompt_font_family, "Monospace");
    strcpy(settings->prompt_font_style, "normal");
    settings->prompt_font_size = 12;
    settings->prompt_save_history = true;
    settings->prompt_save_history_as_html = false;
    sprintf(settings->prompt_save_history_filename, "%sprompt.log",
        state.settings_dir);

    /* OpenSave */
    strcpy(settings->opensave_custom_filter, "supported");
    strcpy(settings->opensave_open_format, "*.*");
    settings->opensave_open_thumbnail = false;
    strcpy(settings->opensave_save_format, "*.*");
    settings->opensave_save_thumbnail = false;

    /* Recent */
    settings->opensave_recent_max_files = 10;
    strcpy(settings->opensave_recent_list_of_files[0], "^END^");
    sprintf(settings->opensave_recent_directory, "%s/samples",
        state.app_dir);

    /* Trimming */
    settings->opensave_trim_dst_num_jumps = 5;

    /* Printing */
    strcpy(settings->printing_default_device, "");
    settings->printing_use_last_device = false;
    settings->printing_disable_bg = true;

    /* Grid */
    settings->grid_show_on_load = true;
    settings->grid_show_origin = true;
    settings->grid_color_match_crosshair = true;
    settings->grid_color = rgb(0, 0, 0);
    settings->grid_load_from_file = true;
    strcpy(settings->grid_type, "Rectangular");
    settings->grid_center_on_origin = true;
    settings->grid_center_x = 0.0;
    settings->grid_center_y = 0.0;
    settings->grid_size_x = 100.0;
    settings->grid_size_y = 100.0;
    settings->grid_spacing_x = 25.0;
    settings->grid_spacing_y = 25.0;
    settings->grid_size_radius = 50.0;
    settings->grid_spacing_radius = 25.0;
    settings->grid_spacing_angle = 45.0;

    /* Ruler */
    settings->ruler_show_on_load = true;
    settings->ruler_metric = true;
    settings->ruler_color = rgb(210, 210, 50);
    settings->ruler_pixel_size = 20;

    /* Quick Snap */
    settings->qsnap_enabled = true;
    settings->qsnap_locator_color = rgb(255, 255, 0);
    settings->qsnap_locator_size = 4;
    settings->qsnap_aperture_size = 10;
    settings->qsnap_endpoint = true;
    settings->qsnap_midpoint = true;
    settings->qsnap_center = true;
    settings->qsnap_node = true;
    settings->qsnap_quadrant = true;
    settings->qsnap_intersection = true;
    settings->qsnap_extension = true;
    settings->qsnap_insertion = false;
    settings->qsnap_perpendicular = true;
    settings->qsnap_tangent = true;
    settings->qsnap_nearest = false;
    settings->qsnap_apparent = false;
    settings->qsnap_parallel = false;

    /* LineWeight */
    settings->lwt_show_lwt = false;
    settings->lwt_real_render = true;
    settings->lwt_default_lwt = 0;

    /* Selection */
    settings->selection_mode_pickfirst = true;
    settings->selection_mode_pickadd = true;
    settings->selection_mode_pickdrag = false;
    settings->selection_coolgrip_color = rgb(0, 0, 255);
    settings->selection_hotgrip_color = rgb(255, 0, 0);
    settings->selection_grip_size = 4;
    settings->selection_pickbox_size = 4;

    /* Text */
    strcpy(settings->text_font, "Arial");
    settings->text_size = 12;
    settings->text_angle = 0;
    settings->text_style_bold = false;
    settings->text_style_italic = false;
    settings->text_style_underline = false;
    settings->text_style_strikeout = false;
    settings->text_style_overline = false;
}

int
settings_load(Settings *settings, int *window_pos, int *window_size)
{
    char errbuffer[200];
    FILE *fp = fopen(state.settings_path, "r");
    if (!fp) {
        printf("ERROR: failed to open file \"%s\".", state.settings_path);
        return 0;
    }

    toml_table_t* table = toml_parse_file(fp, errbuffer, sizeof(errbuffer));
    if (!table) {
        printf("ERROR: failed to parse file \"%s\".", state.settings_path);
        printf("ERROR: %s", errbuffer);
        return 0;
    }

    char result[1000];

    /* General */
    toml_table_t* general = toml_table_in(table, "General");
    /*
    layoutState = toml_readint("LayoutState").toByteArray();
    if (!restoreState(layoutState)) {
        printf("LayoutState NOT restored! Setting Default Layout..."); */
        /* someToolBar->setVisible(true); */
        /*
    }
    */
    toml_readstr(general, "Language", "default", settings->general_language);
    toml_readstr(general, "IconTheme", "default", settings->general_icon_theme);
    settings->general_icon_size = toml_readint(general, "IconSize", 16);
    settings->general_mdi_bg_use_logo = toml_readbool(general, "MdiBGUseLogo", true);
    settings->general_mdi_bg_use_texture = toml_readbool(general, "MdiBGUseTexture", true);
    settings->general_mdi_bg_use_color = toml_readbool(general, "MdiBGUseColor", true);
    toml_readstr(general, "MdiBGLogo",
        settings->general_mdi_bg_logo, settings->general_mdi_bg_logo);
    toml_readstr(general, "MdiBGTexture",
        settings->general_mdi_bg_texture, settings->general_mdi_bg_texture);
    settings->general_mdi_bg_color = toml_readint(general, "MdiBGColor", rgb(192, 192, 192));
    settings->general_tip_of_the_day = toml_readbool(general, "TipOfTheDay", true);
    settings->general_current_tip = toml_readint(general, "CurrentTip", 0);
    settings->general_system_help_browser = toml_readbool(general, "SystemHelpBrowser", true);

    /* Display */
    toml_table_t* display = toml_table_in(table, "Display");
    settings->display_use_opengl = toml_readint(display, "UseOpenGL", false);
    settings->display_renderhint_aa = toml_readint(display, "RenderHintAntiAlias", false);
    settings->display_renderhint_text_aa = toml_readint(display, "RenderHintTextAntiAlias", false);
    settings->display_renderhint_smooth_pix = toml_readint(display, "RenderHintSmoothPixmap", false);
    settings->display_renderhint_high_aa = toml_readint(display, "RenderHintHighQualityAntiAlias", false);
    settings->display_renderhint_noncosmetic = toml_readint(display, "RenderHintNonCosmetic", false);
    settings->display_show_scrollbars = toml_readint(display, "ShowScrollBars", true);
    settings->display_scrollbar_widget_num = toml_readint(display, "ScrollBarWidgetNum", 0);
    settings->display_crosshair_color = toml_readint(display, "CrossHairColor", rgb(  0,  0,  0));
    settings->display_bg_color = toml_readint(display, "BackgroundColor", rgb(235,235,235));
    settings->display_selectbox_left_color = toml_readint(display, "SelectBoxLeftColor", rgb(  0,128,  0));
    settings->display_selectbox_left_fill = toml_readint(display, "SelectBoxLeftFill", rgb(  0,255,  0));
    settings->display_selectbox_right_color = toml_readint(display, "SelectBoxRightColor", rgb(  0,  0,128));
    settings->display_selectbox_right_fill = toml_readint(display, "SelectBoxRightFill", rgb(  0,  0,255));
    settings->display_selectbox_alpha = toml_readint(display, "SelectBoxAlpha", 32);
    settings->display_zoomscale_in = toml_readreal(display, "ZoomScaleIn", 2.0);
    settings->display_zoomscale_out = toml_readreal(display, "ZoomScaleOut", 0.5);
    settings->display_crosshair_percent = toml_readint(display, "CrossHairPercent", 5);
    toml_readstr(display, "Units", "mm", settings->display_units);

    /* Prompt */
    toml_table_t* prompt = toml_table_in(table, "Prompt");
    settings->prompt_text_color = toml_readint(prompt, "TextColor", rgb(0, 0, 0));
    settings->prompt_bg_color = toml_readint(prompt, "BackgroundColor", rgb(255, 255, 255));
    toml_readstr(prompt, "FontFamily", "Monospace", settings->prompt_font_family);
    toml_readstr(prompt, "FontStyle", "normal", settings->prompt_font_style);
    settings->prompt_font_size = toml_readint(prompt, "FontSize", 12);
    settings->prompt_save_history = toml_readint(prompt, "SaveHistory", true);
    settings->prompt_save_history_as_html = toml_readint(prompt, "SaveHistoryAsHtml", false);
    toml_readstr(prompt, "SaveHistoryFilename", settings->prompt_save_history_filename, settings->prompt_save_history_filename);

    /* OpenSave */
    toml_table_t* opensave = toml_table_in(table, "OpenSave");
    toml_readstr(opensave, "CustomFilter", "supported", settings->opensave_custom_filter);
    toml_readstr(opensave, "OpenFormat", "*.*", settings->opensave_open_format);
    settings->opensave_open_thumbnail = toml_readbool(opensave, "OpenThumbnail", false);
    toml_readstr(opensave, "SaveFormat", "*.*", settings->opensave_save_format);
    settings->opensave_save_thumbnail = toml_readbool(opensave, "SaveThumbnail", false);
    settings->opensave_recent_max_files = toml_readint(opensave, "RecentMax", 10);
    /* FIXME: 
    settings->opensave_recent_list_of_files = toml_readint(opensave, "RecentFiles");
    */
    toml_readstr(opensave, "RecentDirectory",
        settings->opensave_recent_directory, settings->opensave_recent_directory);
    settings->opensave_trim_dst_num_jumps = toml_readint(opensave, "TrimDstNumJumps", 5);

    /* Printing */
    toml_table_t* printing = toml_table_in(table, "Printing");
    toml_readstr(printing, "DefaultDevice", "", settings->printing_default_device);
    settings->printing_use_last_device = toml_readbool(printing, "UseLastDevice", false);
    settings->printing_disable_bg = toml_readbool(printing, "DisableBG", true);

    /* Grid */
    toml_table_t* grid = toml_table_in(table, "Grid");
    settings->grid_show_on_load = toml_readint(grid, "ShowOnLoad", true);
    settings->grid_show_origin = toml_readint(grid, "ShowOrigin", true);
    settings->grid_color_match_crosshair = toml_readint(grid, "ColorMatchCrossHair", true);
    settings->grid_color = toml_readint(grid, "Color", rgb(  0,  0,  0));
    settings->grid_load_from_file = toml_readbool(grid, "LoadFromFile", true);
    toml_readstr(grid, "Type", "Rectangular", settings->grid_type);
    settings->grid_center_on_origin = toml_readbool(grid, "CenterOnOrigin", true);
    settings->grid_center_x = toml_readreal(grid, "CenterX", 0.0);
    settings->grid_center_y = toml_readreal(grid, "CenterY", 0.0);
    settings->grid_size_x = toml_readreal(grid, "SizeX", 100.0);
    settings->grid_size_y = toml_readreal(grid, "SizeY", 100.0);
    settings->grid_spacing_x = toml_readreal(grid, "SpacingX", 25.0);
    settings->grid_spacing_y = toml_readreal(grid, "SpacingY", 25.0);
    settings->grid_size_radius = toml_readreal(grid, "SizeRadius", 50.0);
    settings->grid_spacing_radius = toml_readreal(grid, "SpacingRadius", 25.0);
    settings->grid_spacing_angle = toml_readreal(grid, "SpacingAngle", 45.0);

    /* Ruler */
    toml_table_t* ruler = toml_table_in(table, "Ruler");
    settings->ruler_show_on_load = toml_readbool(ruler, "ShowOnLoad", true);
    settings->ruler_metric = toml_readbool(ruler, "Metric", true);
    settings->ruler_color = toml_readint(ruler, "Color", rgb(210,210, 50));
    settings->ruler_pixel_size = toml_readint(ruler, "PixelSize", 20);

    /* Quick Snap */
    toml_table_t* quicksnap = toml_table_in(table, "QuickSnap");
    settings->qsnap_enabled = toml_readint(quicksnap, "Enabled", true);
    settings->qsnap_locator_color = toml_readint(quicksnap, "LocatorColor", rgb(255,255,  0));
    settings->qsnap_locator_size = toml_readint(quicksnap, "LocatorSize", 4);
    settings->qsnap_aperture_size = toml_readint(quicksnap, "ApertureSize", 10);
    settings->qsnap_endpoint = toml_readbool(quicksnap, "EndPoint", true);
    settings->qsnap_midpoint = toml_readbool(quicksnap, "MidPoint", true);
    settings->qsnap_center = toml_readbool(quicksnap, "Center", true);
    settings->qsnap_node = toml_readbool(quicksnap, "Node", true);
    settings->qsnap_quadrant = toml_readbool(quicksnap, "Quadrant", true);
    settings->qsnap_intersection = toml_readbool(quicksnap, "Intersection", true);
    settings->qsnap_extension = toml_readbool(quicksnap, "Extension", true);
    settings->qsnap_insertion = toml_readbool(quicksnap, "Insertion", false);
    settings->qsnap_perpendicular = toml_readbool(quicksnap, "Perpendicular", true);
    settings->qsnap_tangent = toml_readbool(quicksnap, "Tangent", true);
    settings->qsnap_nearest = toml_readbool(quicksnap, "Nearest", false);
    settings->qsnap_apparent = toml_readbool(quicksnap, "Apparent", false);
    settings->qsnap_parallel = toml_readbool(quicksnap, "Parallel", false);

    /* LineWeight */
    toml_table_t* lineweight = toml_table_in(table, "LineWeight");
    settings->lwt_show_lwt = toml_readbool(lineweight, "ShowLineWeight", false);
    settings->lwt_real_render = toml_readbool(lineweight, "RealRender", true);
    settings->lwt_default_lwt = toml_readint(lineweight, "DefaultLineWeight", 0);

    /* Selection */
    toml_table_t* selection = toml_table_in(table, "Selection");
    settings->selection_mode_pickfirst = toml_readbool(selection, "PickFirst", true);
    settings->selection_mode_pickadd = toml_readbool(selection, "PickAdd", true);
    settings->selection_mode_pickdrag = toml_readbool(selection, "PickDrag", false);
    settings->selection_coolgrip_color = toml_readint(selection, "CoolGripColor", rgb(  0,  0,255));
    settings->selection_hotgrip_color = toml_readint(selection, "HotGripColor", rgb(255,  0,  0));
    settings->selection_grip_size = toml_readint(selection, "GripSize", 4);
    settings->selection_pickbox_size = toml_readint(selection, "PickBoxSize", 4);

    /* Text */
    toml_table_t* text = toml_table_in(table, "Text");
    toml_readstr(text, "Font", "Arial", settings->text_font);
    settings->text_size = toml_readint(text, "Size", 12);
    settings->text_angle = toml_readint(text, "Angle", 0);
    settings->text_style_bold = toml_readbool(text, "StyleBold", false);
    settings->text_style_italic = toml_readbool(text, "StyleItalic", false);
    settings->text_style_underline = toml_readbool(text, "StyleUnderline", false);
    settings->text_style_strikeout = toml_readbool(text, "StyleStrikeOut", false);
    settings->text_style_overline = toml_readbool(text, "StyleOverline", false);

    fclose(fp);
    return 1;
}

/* Make sure that a section header is styled correctly. */
void
section_header(FILE *fp, const char *label)
{
    fprintf(fp, "[%s]\n", label);
}

/* Make sure that a string setting is styled correctly. */
void
write_str(FILE *fp, const char *key, char *value)
{
    fprintf(fp, "%s=%s\n", key, value);
}

/* Make sure that a string setting is styled correctly. */
void
write_strarray(FILE *fp, const char *key, char value[MAXTABLE][MAXSTR])
{
    fprintf(fp, "%s=", key);
    for (int i=0; value[i][0] != '^'; i++) {
        fprintf(fp, "%s ", key);
    }
    fprintf(fp, "\n");
}

/* Make sure that an integer setting is styled correctly. */
void
write_int(FILE *fp, const char *key, int32_t value)
{
    fprintf(fp, "%s=%d\n", key, value);
}

/* Make sure that a floating point setting is styled correctly. */
void
write_real(FILE *fp, const char *key, float value)
{
    fprintf(fp, "%s=%f\n", key, value);
}

int
settings_save(Settings *settings, int window_pos[2], int window_size[2])
{
    FILE *fp = fopen(state.settings_path, "w");

    section_header(fp, "General");
    /* write_str(fp, "LayoutState", layoutState); */
    write_str(fp, "Language", settings->general_language);
    write_str(fp, "IconTheme", settings->general_icon_theme);
    write_int(fp, "IconSize", settings->general_icon_size);
    write_int(fp, "MdiBGUseLogo", settings->general_mdi_bg_use_logo);
    write_int(fp, "MdiBGUseTexture", settings->general_mdi_bg_use_texture);
    write_int(fp, "MdiBGUseColor", settings->general_mdi_bg_use_color);
    write_str(fp, "MdiBGLogo", settings->general_mdi_bg_logo);
    write_str(fp, "MdiBGTexture", settings->general_mdi_bg_texture);
    write_int(fp, "MdiBGColor", settings->general_mdi_bg_color);
    write_int(fp, "TipOfTheDay", settings->general_tip_of_the_day);
    write_int(fp, "CurrentTip", settings->general_current_tip + 1);
    write_int(fp, "SystemHelpBrowser", settings->general_system_help_browser);

    section_header(fp, "Display");
    write_int(fp, "UseOpenGL", settings->display_use_opengl);
    write_int(fp, "RenderHintAntiAlias", settings->display_renderhint_aa);
    write_int(fp, "RenderHintTextAntiAlias", settings->display_renderhint_text_aa);
    write_int(fp, "RenderHintSmoothPixmap", settings->display_renderhint_smooth_pix);
    write_int(fp, "RenderHintHighQualityAntiAlias", settings->display_renderhint_high_aa);
    write_int(fp, "RenderHintNonCosmetic", settings->display_renderhint_noncosmetic);
    write_int(fp, "ShowScrollBars", settings->display_show_scrollbars);
    write_int(fp, "ScrollBarWidgetNum", settings->display_scrollbar_widget_num);
    write_int(fp, "CrossHairColor", settings->display_crosshair_color);
    write_int(fp, "BackgroundColor", settings->display_bg_color);
    write_int(fp, "SelectBoxLeftColor", settings->display_selectbox_left_color);
    write_int(fp, "SelectBoxLeftFill", settings->display_selectbox_left_fill);
    write_int(fp, "SelectBoxRightColor", settings->display_selectbox_right_color);
    write_int(fp, "SelectBoxRightFill", settings->display_selectbox_right_fill);
    write_int(fp, "SelectBoxAlpha", settings->display_selectbox_alpha);
    write_int(fp, "ZoomScaleIn", settings->display_zoomscale_in);
    write_int(fp, "ZoomScaleOut", settings->display_zoomscale_out);
    write_int(fp, "CrossHairPercent", settings->display_crosshair_percent);
    write_str(fp, "Units", settings->display_units);

    section_header(fp, "Window");
    write_int(fp, "PositionX", window_pos[0]);
    write_int(fp, "PositionY", window_pos[1]);
    write_int(fp, "SizeX", window_size[0]);
    write_int(fp, "SizeY", window_size[1]);

    section_header(fp, "Prompt");
    write_int(fp, "Prompt/TextColor", settings->prompt_text_color);
    write_int(fp, "Prompt/BackgroundColor", settings->prompt_bg_color);
    write_str(fp, "Prompt/FontFamily", settings->prompt_font_family);
    write_str(fp, "Prompt/FontStyle", settings->prompt_font_style);
    write_int(fp, "Prompt/FontSize", settings->prompt_font_size);
    write_int(fp, "Prompt/SaveHistory", settings->prompt_save_history);
    write_int(fp, "Prompt/SaveHistoryAsHtml", settings->prompt_save_history_as_html);
    write_str(fp, "Prompt/SaveHistoryFilename", settings->prompt_save_history_filename);

    section_header(fp, "OpenSave");
    write_str(fp, "OpenSave/CustomFilter", settings->opensave_custom_filter);
    write_str(fp, "OpenSave/OpenFormat", settings->opensave_open_format);
    write_int(fp, "OpenSave/OpenThumbnail", settings->opensave_open_thumbnail);
    write_str(fp, "OpenSave/SaveFormat", settings->opensave_save_format);
    write_int(fp, "OpenSave/SaveThumbnail", settings->opensave_save_thumbnail);
    write_int(fp, "OpenSave/RecentMax", settings->opensave_recent_max_files);
    write_strarray(fp, "OpenSave/RecentFiles", settings->opensave_recent_list_of_files);
    write_str(fp, "OpenSave/RecentDirectory", settings->opensave_recent_directory);
    write_int(fp, "OpenSave/TrimDstNumJumps", settings->opensave_trim_dst_num_jumps);

    section_header(fp, "Printing");
    write_str(fp, "DefaultDevice=%s\n", settings->printing_default_device);
    write_int(fp, "UseLastDevice=%d\n", settings->printing_use_last_device);
    write_int(fp, "DisableBG=%d\n", settings->printing_disable_bg);

    section_header(fp, "Grid");
    write_int(fp, "ShowOnLoad", settings->grid_show_on_load);
    write_int(fp, "ShowOrigin", settings->grid_show_origin);
    write_int(fp, "ColorMatchCrossHair", settings->grid_color_match_crosshair);
    write_int(fp, "Color", settings->grid_color);
    write_int(fp, "LoadFromFile", settings->grid_load_from_file);
    write_str(fp, "Type", settings->grid_type);
    write_int(fp, "CenterOnOrigin", settings->grid_center_on_origin);
    write_real(fp, "CenterX", settings->grid_center_x);
    write_real(fp, "CenterY", settings->grid_center_y);
    write_real(fp, "SizeX", settings->grid_size_x);
    write_real(fp, "SizeY", settings->grid_size_y);
    write_real(fp, "SpacingX", settings->grid_spacing_x);
    write_real(fp, "SpacingY", settings->grid_spacing_y);
    write_real(fp, "SizeRadius", settings->grid_size_radius);
    write_real(fp, "SpacingRadius", settings->grid_spacing_radius);
    write_real(fp, "SpacingAngle", settings->grid_spacing_angle);

    section_header(fp, "Ruler");
    write_int(fp, "ShowOnLoad", settings->ruler_show_on_load);
    write_int(fp, "Metric", settings->ruler_metric);
    write_int(fp, "Color", settings->ruler_color);
    write_int(fp, "PixelSize", settings->ruler_pixel_size);

    section_header(fp, "QuickSnap");
    write_int(fp, "QuickSnap/Enabled", settings->qsnap_enabled);
    write_int(fp, "QuickSnap/LocatorColor", settings->qsnap_locator_color);
    write_int(fp, "QuickSnap/LocatorSize", settings->qsnap_locator_size);
    write_int(fp, "QuickSnap/ApertureSize", settings->qsnap_aperture_size);
    write_int(fp, "QuickSnap/EndPoint", settings->qsnap_endpoint);
    write_int(fp, "QuickSnap/MidPoint", settings->qsnap_midpoint);
    write_int(fp, "QuickSnap/Center", settings->qsnap_center);
    write_int(fp, "QuickSnap/Node", settings->qsnap_node);
    write_int(fp, "QuickSnap/Quadrant", settings->qsnap_quadrant);
    write_int(fp, "QuickSnap/Intersection", settings->qsnap_intersection);
    write_int(fp, "QuickSnap/Extension", settings->qsnap_extension);
    write_int(fp, "QuickSnap/Insertion", settings->qsnap_insertion);
    write_int(fp, "QuickSnap/Perpendicular", settings->qsnap_perpendicular);
    write_int(fp, "QuickSnap/Tangent", settings->qsnap_tangent);
    write_int(fp, "QuickSnap/Nearest", settings->qsnap_nearest);
    write_int(fp, "QuickSnap/Apparent", settings->qsnap_apparent);
    write_int(fp, "QuickSnap/Parallel", settings->qsnap_parallel);

    section_header(fp, "LineWeight");
    write_int(fp, "ShowLineWeight", settings->lwt_show_lwt);
    write_int(fp, "RealRender", settings->lwt_real_render);
    write_int(fp, "DefaultLineWeight", settings->lwt_default_lwt);

    section_header(fp, "Selection");
    write_int(fp, "PickFirst", settings->selection_mode_pickfirst);
    write_int(fp, "PickAdd", settings->selection_mode_pickadd);
    write_int(fp, "PickDrag", settings->selection_mode_pickdrag);
    write_int(fp, "CoolGripColor", settings->selection_coolgrip_color);
    write_int(fp, "HotGripColor", settings->selection_hotgrip_color);
    write_int(fp, "GripSize", settings->selection_grip_size);
    write_int(fp, "PickBoxSize", settings->selection_pickbox_size);

    section_header(fp, "Text");
    write_str(fp, "Font", settings->text_font);
    write_int(fp, "Size", settings->text_size);
    write_int(fp, "Angle", settings->text_angle);
    write_int(fp, "StyleBold", settings->text_style_bold);
    write_int(fp, "StyleItalic", settings->text_style_italic);
    write_int(fp, "StyleUnderline", settings->text_style_underline);
    write_int(fp, "StyleStrikeOut", settings->text_style_strikeout);
    write_int(fp, "StyleOverline", settings->text_style_overline);

    fclose(fp);
    return 1;
}

/* Make sure that all the settings are within acceptable parameters. */
void
settings_validate(Settings *settings)
{
    /* FIXME: settings->general_language = settings->general_language.toLower(); */
    if (settings->grid_color_match_crosshair) {
        settings->grid_color = settings->display_crosshair_color;
    }
}

void
settings_copy(Settings *dest, Settings *src)
{
    /* We only want to copy valid settings, so validate them first. */
    settings_validate(src);

    /* No settings memory has indirection so we may copy it as a
     * contiguous chunk.
     */
    memcpy(dest, src, sizeof(Settings));
}

/* FIXME: This is currently unused */
void
settings_free(Settings *settings)
{
}

