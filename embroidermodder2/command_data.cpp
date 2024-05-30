/*
 * Embroidermodder 2.
 *
 * Copyright 2011-2024 The Embroidermodder Team
 * Embroidermodder 2 is Open Source Software, see LICENSE.md for licensing terms.
 * Visit https://www.libembroidery.org/refman for advice on altering this file,
 * or read the markdown version in embroidermodder2/docs/refman.
 *
 * Command Data
 */

#include "embroidermodder.h"

ScriptValue about_command(ScriptEnv*);
ScriptValue alert_command(ScriptEnv*);
ScriptValue angle_command(ScriptEnv*);
ScriptValue circle_command(ScriptEnv*);
ScriptValue changelog_command(ScriptEnv*);
ScriptValue clear_command(ScriptEnv*);
ScriptValue copy_command(ScriptEnv*);
ScriptValue cut_command(ScriptEnv*);
ScriptValue day_command(ScriptEnv *);
ScriptValue debug_command(ScriptEnv *);
ScriptValue design_details_command(ScriptEnv *);
ScriptValue disable_command(ScriptEnv*);
ScriptValue distance_command(ScriptEnv*);
ScriptValue dolphin_command(ScriptEnv*);
ScriptValue ellipse_command(ScriptEnv *);
ScriptValue enable_command(ScriptEnv *);
ScriptValue erase_command(ScriptEnv *);
ScriptValue error_command(ScriptEnv *);
ScriptValue exit_command(ScriptEnv *);
ScriptValue heart_command(ScriptEnv *);
ScriptValue heart_command(ScriptEnv*);
ScriptValue help_command(ScriptEnv*);
ScriptValue icon128_command(ScriptEnv*);
ScriptValue icon16_command(ScriptEnv*);
ScriptValue icon24_command(ScriptEnv*);
ScriptValue icon32_command(ScriptEnv*);
ScriptValue icon48_command(ScriptEnv*);
ScriptValue icon64_command(ScriptEnv*);
ScriptValue get_command(ScriptEnv*);
ScriptValue line_command(ScriptEnv*);
ScriptValue locatepoint_command(ScriptEnv*);
ScriptValue mirrorselected_command(ScriptEnv*);
ScriptValue move_command(ScriptEnv*);
ScriptValue moveselected_command(ScriptEnv*);
ScriptValue new_command(ScriptEnv*);
ScriptValue night_command(ScriptEnv*);
ScriptValue open_command(ScriptEnv*);
ScriptValue paste_command(ScriptEnv*);
ScriptValue print_command(ScriptEnv*);
ScriptValue redo_command(ScriptEnv*);

ScriptValue pandown_command(ScriptEnv*);
ScriptValue panleft_command(ScriptEnv*);
ScriptValue panright_command(ScriptEnv*);
ScriptValue panup_command(ScriptEnv*);

ScriptValue path_command(ScriptEnv*);
ScriptValue platform_command(ScriptEnv*);
ScriptValue previewoff_command(ScriptEnv*);
ScriptValue previewon_command(ScriptEnv*);
ScriptValue point_command(ScriptEnv*);
ScriptValue polygon_command(ScriptEnv*);
ScriptValue polyline_command(ScriptEnv*);
ScriptValue rectangle_command(ScriptEnv*);
ScriptValue rotate_command(ScriptEnv*);
ScriptValue rgb_command(ScriptEnv*);
ScriptValue quickleader_command(ScriptEnv*);
ScriptValue save_command(ScriptEnv*);
ScriptValue sandbox_command(ScriptEnv*);
ScriptValue scale_command(ScriptEnv*);
ScriptValue scaleselected_command(ScriptEnv*);
ScriptValue selectall_command(ScriptEnv*);
ScriptValue settings_dialog_command(ScriptEnv*);
ScriptValue singlelinetext_command(ScriptEnv*);
ScriptValue set_command(ScriptEnv*);
ScriptValue snowflake_command(ScriptEnv*);
ScriptValue star_command(ScriptEnv*);
ScriptValue syswindows_command(ScriptEnv*);

ScriptValue text_bold_command(ScriptEnv*);
ScriptValue text_italic_command(ScriptEnv*);
ScriptValue text_underline_command(ScriptEnv*);
ScriptValue text_overline_command(ScriptEnv*);
ScriptValue text_strikeout_command(ScriptEnv*);

ScriptValue tipoftheday_command(ScriptEnv*);
ScriptValue todo_command(ScriptEnv*);
ScriptValue undo_command(ScriptEnv*);
ScriptValue vulcanize_command(ScriptEnv*);

ScriptValue whats_this_command(ScriptEnv*);

ScriptValue windowcascade_command(ScriptEnv*);
ScriptValue windowclose_command(ScriptEnv*);
ScriptValue windowcloseall_command(ScriptEnv*);
ScriptValue windownext_command(ScriptEnv*);
ScriptValue windowprevious_command(ScriptEnv*);
ScriptValue windowtile_command(ScriptEnv*);

ScriptValue zoom_all_command(ScriptEnv*);
ScriptValue zoom_center_command(ScriptEnv*);
ScriptValue zoom_dynamic_command(ScriptEnv*);
ScriptValue zoom_extents_command(ScriptEnv*);
ScriptValue zoom_in_command(ScriptEnv*);
ScriptValue zoom_out_command(ScriptEnv*);
ScriptValue zoom_previous_command(ScriptEnv*);
ScriptValue zoom_real_time_command(ScriptEnv*);
ScriptValue zoom_scale_command(ScriptEnv*);
ScriptValue zoom_selected_command(ScriptEnv*);
ScriptValue zoom_window_command(ScriptEnv*);

#if 0
    createAction("windowtile", tr("&Tile"), tr("Tile the windows.")));
    createAction("windownext", tr("Ne&xt"), tr("Move the focus to the next window.")));
    createAction("windowprevious", tr("Pre&vious"), tr("Move the focus to the previous window.")));

    createAction("print", tr("&Print"), tr("Print the design.")));
    createAction("exit", tr("E&xit"), tr("Exit the application.")));

    createAction("makelayercurrent", tr("&Make Layer Active"), tr("Makes the layer of a selected object the active layer")));
    createAction("layers", tr("&Layers"), tr("Manages layers and layer properties:  LAYER")));
    createAction("layerselector", tr("&Layer Selector"), tr("Dropdown selector for changing the current layer")));
    createAction("layerprevious", tr("&Layer Previous"), tr("Restores the previous layer settings:  LAYERP")));
    createAction("colorselector", tr("&Color Selector"), tr("Dropdown selector for changing the current thread color")));
    createAction("linetypeselector", tr("&Stitchtype Selector"), tr("Dropdown selector for changing the current stitch type")));
    createAction("lineweightselector", tr("&Threadweight Selector"), tr("Dropdown selector for changing the current thread weight")));
    createAction("hidealllayers", tr("&Hide All Layers"), tr("Turns the visibility off for all layers in the current drawing:  HIDEALL")));
    createAction("showalllayers", tr("&Show All Layers"), tr("Turns the visibility on for all layers in the current drawing:  SHOWALL")));
    createAction("freezealllayers", tr("&Freeze All Layers"), tr("Freezes all layers in the current drawing:  FREEZEALL")));
    createAction("thawalllayers", tr("&Thaw All Layers"), tr("Thaws all layers in the current drawing:  THAWALL")));
    createAction("lockalllayers", tr("&Lock All Layers"), tr("Locks all layers in the current drawing:  LOCKALL")));
    createAction("unlockalllayers", tr("&Unlock All Layers"), tr("Unlocks all layers in the current drawing:  UNLOCKALL")));

    createAction("panrealtime", tr("&Pan Realtime"), tr("Moves the view in the current viewport.")));
    createAction("panpoint", tr("&Pan Point"), tr("Moves the view by the specified distance.")));
#endif

Command command_data[] = {
    {
        .id = ACTION_ABOUT,
        .main = about_command,
        .icon = "about",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&About Embroidermodder 2",
        .statustip = "Displays information about this product. Command: ABOUT.",
        .alias = "ABOUT"
    },
    {
        .id = ACTION_ALERT,
        .main = alert_command,
        .icon = "warning",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Alert",
        .statustip = "Creates a dialog to alert the user. Command: ALERT.",
        .alias = "ALERT"
    },
    {
        .id = ACTION_ANGLE,
        .main = angle_command,
        .icon = "angle",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Angle",
        .statustip = "Calculate the angle between two lines and display it. Command: ANGLE, CALCANGLE",
        .alias = "ANGLE, CALCANGLE"
    },
    {
        .id = ACTION_CIRCLE,
        .main = circle_command,
        .icon = "circle",
        .menu_name = "Draw",
        .menu_position = 8,
        .toolbar_name = "Draw",
        .toolbar_position = 8,
        .tooltip = "&Circle",
        .statustip = "Creates a circle. Command: CIRCLE.",
        .alias = "C, CIRCLE"
    },
    {
        .id = ACTION_CHANGELOG,
        .main = changelog_command,
        .icon = "changelog",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Changelog",
        .statustip = "Describes new features in this product. Command: CHANGELOG.",
        .alias = "CHANGELOG"
    },
    {
        .id = ACTION_CLEAR,
        .main = clear_command,
        .icon = "clear",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Do Nothing",
        .statustip = "Does Nothing. Command: DONOTHING.",
        .alias = "DONOTHING"
    },
    {
        .id = ACTION_COPY,
        .main = copy_command,
        .icon = "copy",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Copy",
        .statustip = "Copy the current selection's contents to the clipboard. Command: COPY.",
        .alias = "COPY"
    },
    {
        .id = ACTION_CUT,
        .main = cut_command,
        .icon = "cut",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Cu&t",
        .statustip = "Cut the current selection's contents to the clipboard. Command: CUT.",
        .alias = "CUT"
    },
    {
        .id = ACTION_DAY,
        .main = day_command,
        .icon = "day",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Day",
        .statustip = "Updates the current view using day vision settings. Command: DAY",
        .alias = "DAY"
    },
    {
        .id = ACTION_DEBUG,
        .main = debug_command,
        .icon = "about",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Debug",
        .statustip = "Displays information about this product:  ABOUT",
        .alias = "DEBUG"
    },
    {
        .id = ACTION_DESIGN_DETAILS,
        .main = design_details_command,
        .icon = "designdetails",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Details",
        .statustip = "Details of the current design. Command: DETAILS",
        .alias = "DESIGNDETAILS, DETAILS"
    },
    {
        .id = ACTION_DISABLE,
        .main = disable_command,
        .icon = "disable",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Disable",
        .statustip = "Disable one of the pre-defined global boolean variables.",
        .alias = "DISABLE"
    },
    {
        .id = ACTION_DISTANCE,
        .main = distance_command,
        .icon = "distance",
        .menu_name = "Tools",
        .menu_position = 7,
        .toolbar_name = "Inquiry",
        .toolbar_position = 0,
        .tooltip = "&Distance",
        .statustip = "Measures the distance and angle between two points. Command: DIST",
        .alias = "DI, DIST, DISTANCE"
    },
    {
        .id = ACTION_DOLPHIN,
        .main = dolphin_command,
        .icon = "dolphin",
        .menu_name = "Draw",
        .menu_position = 100,
        .toolbar_name = "Draw",
        .toolbar_position = 100,
        .tooltip = "&Dolphin",
        .statustip = "Creates a dolphin. Command: DOLPHIN.",
        .alias = "DOLPHIN"
    },
    {
        .id = ACTION_DO_NOTHING,
        .main = do_nothing,
        .icon = "donothing",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Do Nothing",
        .statustip = "Does Nothing. Command: DONOTHING.",
        .alias = "DONOTHING"
    },
    {
        .id = ACTION_ELLIPSE,
        .main = ellipse_command,
        .icon = "ellipse",
        .menu_name = "Draw",
        .menu_position = 8,
        .toolbar_name = "Draw",
        .toolbar_position = 8,
        .tooltip = "&Ellipse",
        .statustip = "Creates an ellipse. Command: ELLIPSE.",
        .alias = "EL, ELLIPSE"
    },
    {
        .id = ACTION_ENABLE,
        .main = enable_command,
        .icon = "enable",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Enable",
        .statustip = "Enable a pre-defined global variables.",
        .alias = "ENABLE"
    },
    {
        .id = ACTION_ERASE,
        .main = erase_command,
        .icon = "erase",
        .menu_name = "Modify",
        .menu_position = 5,
        .toolbar_name = "Modify",
        .toolbar_position = 0,
        .tooltip = "D&elete",
        .statustip = "Removes objects from a drawing. Command: DELETE.",
        .alias = "E, ERASE, DEL, DELETE"
    },
    {
        .id = ACTION_ERROR,
        .main = error_command,
        .icon = "error",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Error",
        .statustip = "Sends an error message to the user. Command: ERROR",
        .alias = "ERROR"
    },
    {
        .id = ACTION_EXIT,
        .main = exit_command,
        .icon = "exit",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "E&xit",
        .statustip = "Exit the application:  EXIT",
        .alias = "EXIT, QUIT"
    },
    {
        .id = ACTION_GET,
        .main = get_command,
        .icon = "get",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Get",
        .statustip = "Print a value to one of the pre-defined global variables.",
        .alias = "SET"
    },
    {
        .id = ACTION_HEART,
        .main = heart_command,
        .icon = "heart",
        .menu_name = "Draw",
        .menu_position = 100,
        .toolbar_name = "Draw",
        .toolbar_position = 100,
        .tooltip = "&Heart",
        .statustip = "Creates a heart:  HEART",
        .alias = "HEART"
    },
    {
        .id = ACTION_HELP,
        .main = help_command,
        .icon = "help",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Help",
        .statustip = "Displays help. Command: HELP",
        .alias = "?, HELP"
    },
    {
        .id = ACTION_ICON_128,
        .main = icon128_command,
        .icon = "icon128",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon12&8",
        .statustip = "Sets the toolbar icon size to 128x128:  ICON128",
        .alias = "ICON128"
    },
    {
        .id = ACTION_ICON_16,
        .main = icon16_command,
        .icon = "icon16",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&16",
        .statustip = "Sets the toolbar icon size to 16x16:  ICON16",
        .alias = "ICON16"
    },
    {
        .id = ACTION_ICON_24,
        .main = icon24_command,
        .icon = "icon24",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&24",
        .statustip = "Sets the toolbar icon size to 24x24:  ICON24",
        .alias = "ICON24"
    },
    {
        .id = ACTION_ICON_32,
        .main = icon32_command,
        .icon = "icon32",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&32",
        .statustip = "Sets the toolbar icon size to 32x32:  ICON32",
        .alias = "ICON32"
    },
    {
        .id = ACTION_ICON_48,
        .main = icon48_command,
        .icon = "icon48",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&48",
        .statustip = "Sets the toolbar icon size to 48x48:  ICON48",
        .alias = "ICON48"
    },
    {
        .id = ACTION_ICON_64,
        .main = icon64_command,
        .icon = "icon64",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&64",
        .statustip = "Sets the toolbar icon size to 64x64:  ICON64",
        .alias = "ICON64"
    },
    {
        .id = ACTION_LINE,
        .main = line_command,
        .icon = "line",
        .menu_name = "Draw",
        .menu_position = 0,
        .toolbar_name = "Draw",
        .toolbar_position = 0,
        .tooltip = "&Line",
        .statustip = "Creates straight line segments:  LINE",
        .alias = "L, LINE"
    },
    {
        .id = ACTION_LOCATE_POINT,
        .main = locatepoint_command,
        .icon = "locatepoint",
        .menu_name = "Tools",
        .menu_position = 11,
        .toolbar_name = "Inquiry",
        .toolbar_position = 0,
        .tooltip = "&Locate Point",
        .statustip = "Displays the coordinate values of a location:  ID",
        .alias = "ID, LOCATEPOINT"
    },
    {
        .id = ACTION_MIRROR_SELECTED,
        .main = mirrorselected_command,
        .icon = "mirror",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Mirror Selected",
        .statustip = "Command: MIRRORSELECTED.",
        .alias = "MIRRORSELECTED"
    },
    {
        .id = ACTION_MOVE,
        .main = move_command,
        .icon = "move",
        .menu_name = "Modify",
        .menu_position = 10,
        .toolbar_name = "Modify",
        .toolbar_position = 5,
        .tooltip = "&Move",
        .statustip = "Displaces objects a specified distance in a specified direction:  MOVE",
        .alias = "M, MOVE"
    },
    {
        .id = ACTION_MOVE_SELECTED,
        .main = moveselected_command,
        .icon = "moveselected",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Do Nothing",
        .statustip = "Does Nothing.",
        .alias = "DONOTHING"
    },
    {
        .id = ACTION_NEW,
        .main = new_command,
        .icon = "new",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&New",
        .statustip = "Create a new file. Command: NEW.",
        .alias = "NEW"
    },
    {
        .id = ACTION_NIGHT,
        .main = night_command,
        .icon = "night",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Night",
        .statustip = "Updates the current view using night vision settings. Command: NIGHT.",
        .alias = "NIGHT"
    },
    {
        .id = ACTION_OPEN,
        .main = open_command,
        .icon = "open",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Open",
        .statustip = "Open an existing file. Command: OPEN.",
        .alias = "OPEN"
    },
    {
        .id = ACTION_PAN_DOWN,
        .main = pandown_command,
        .icon = "pandown",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Pan Down",
        .statustip = "Moves the view down:  PANDOWN",
        .alias = "PANDOWN"
    },
    {
        .id = ACTION_PAN_LEFT,
        .main = panleft_command,
        .icon = "panleft",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Pan Left",
        .statustip = "Moves the view to the left:  PANLEFT",
        .alias = "PANLEFT"
    },
    {
        .id = ACTION_PAN_RIGHT,
        .main = panright_command,
        .icon = "panright",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Pan Right",
        .statustip = "Moves the view to the right:  PANRIGHT",
        .alias = "PANRIGHT"
    },
    {
        .id = ACTION_PAN_UP,
        .main = panup_command,
        .icon = "panup",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Pan Up",
        .statustip = "Moves the view up:  PANUP",
        .alias = "PANUP"
    },
    {
        .id = ACTION_PASTE,
        .main = paste_command,
        .icon = "paste",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Paste",
        .statustip = "Paste the clipboard's contents into the current selection. Command: PASTE.",
        .alias = "PASTE"
    },
    {
        .id = ACTION_PATH,
        .main = path_command,
        .icon = "path",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&24",
        .statustip = "Sets the toolbar icon size to 24x24:  ICON24",
        .alias = "PATH"
    },
    {
        .id = ACTION_PLATFORM,
        .main = platform_command,
        .icon = "platform",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Platform",
        .statustip = "List which platform is in use. Command: PLATFORM.",
        .alias = "PLATFORM"
    },
    {
        .id = ACTION_POINT,
        .main = point_command,
        .icon = "point",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&24",
        .statustip = "Sets the toolbar icon size to 24x24:  ICON24",
        .alias = "ICON24"
    },
    {
        .id = ACTION_POLYGON,
        .main = polygon_command,
        .icon = "polygon",
        .menu_name = "Draw",
        .menu_position = 4,
        .toolbar_name = "Draw",
        .toolbar_position = 4,
        .tooltip = "Pol&ygon",
        .statustip = "Creates a regular polygon. Command: POLYGON.",
        .alias = "POL, POLYGON"
    },
    {
        .id = ACTION_POLYLINE,
        .main = polyline_command,
        .icon = "polyline",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&24",
        .statustip = "Sets the toolbar icon size to 24x24:  ICON24",
        .alias = "ICON24"
    },
    {
        .id = ACTION_PREVIEW_OFF,
        .main = previewoff_command,
        .icon = "previewoff",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Do Nothing",
        .statustip = "Does Nothing.",
        .alias = "DONOTHING"
    },
    {
        .id = ACTION_PREVIEW_ON,
        .main = previewon_command,
        .icon = "previewon",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Do Nothing",
        .statustip = "Does Nothing.",
        .alias = "DONOTHING"
    },
    {
        .id = ACTION_PRINT,
        .main = print_command,
        .icon = "print",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Print",
        .statustip = "Displays information about this product:  ABOUT",
        .alias = "ABOUT"
    },
    {
        .id = ACTION_QUICKLEADER,
        .main = quickleader_command,
        .icon = "quickleader",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&24",
        .statustip = "Sets the toolbar icon size to 24x24:  ICON24",
        .alias = "ICON24"
    },
    {
        .id = ACTION_RECTANGLE,
        .main = rectangle_command,
        .icon = "rectangle",
        .menu_name = "Draw",
        .menu_position = 6,
        .toolbar_name = "Draw",
        .toolbar_position = 6,
        .tooltip = "&Rectangle",
        .statustip = "Creates a rectangular polyline. Command: RECTANGLE.",
        .alias = "REC, RECT, RECTANG, RECTANGLE"
    },
    {
        .id = ACTION_REDO,
        .main = redo_command,
        .icon = "redo",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Redo",
        .statustip = "Reverses the effects of the previous undo action. Command: REDO.",
        .alias = "REDO"
    },
    {
        .id = ACTION_RGB,
        .main = rgb_command,
        .icon = "rgb",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&24",
        .statustip = "Sets the toolbar icon size to 24x24:  ICON24",
        .alias = "ICON24"
    },
    {
        .id = ACTION_ROTATE,
        .main = rotate_command,
        .icon = "rotate",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&24",
        .statustip = "Sets the toolbar icon size to 24x24:  ICON24",
        .alias = "ICON24"
    },
    {
        .id = ACTION_SANDBOX,
        .main = sandbox_command,
        .icon = "sandbox",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&24",
        .statustip = "Sets the toolbar icon size to 24x24:  ICON24",
        .alias = "ICON24"
    },
    {
        .id = ACTION_SAVE,
        .main = save_command,
        .icon = "save",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Save",
        .statustip = "Save the design to disk. Command: SAVE.",
        .alias = "SAVE"
    },
    {
        .id = ACTION_SAVE_AS,
        .main = save_command,
        .icon = "saveas",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Save &As",
        .statustip = "Save the design under a new name. Command: SAVEAS.",
        .alias = "SAVEAS"
    },
    {
        .id = ACTION_SCALE,
        .main = scale_command,
        .icon = "scale",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&24",
        .statustip = "Sets the toolbar icon size to 24x24:  ICON24",
        .alias = "SCALE"
    },
    {
        .id = ACTION_SCALE_SELECTED,
        .main = scaleselected_command,
        .icon = "scaleselected",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Do Nothing",
        .statustip = "Does Nothing.",
        .alias = "SCALESELECTED"
    },
    {
        .id = ACTION_SELECT_ALL,
        .main = selectall_command,
        .icon = "selectall",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&24",
        .statustip = "Sets the toolbar icon size to 24x24:  ICON24",
        .alias = "SELECTALL, SELALL"
    },
    {
        .id = ACTION_SET,
        .main = set_command,
        .icon = "set",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Set",
        .statustip = "Assign a value to one of the pre-defined global variables.",
        .alias = "SET"
    },
    {
        .id = ACTION_SETTINGS_DIALOG,
        .main = settings_dialog_command,
        .icon = "settingsdialog",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Settings",
        .statustip = "Configure settings specific to this product. Command: SETTINGS.",
        .alias = "SETTINGS"
    },
    {
        .id = ACTION_SINGLE_LINE_TEXT,
        .main = singlelinetext_command,
        .icon = "singlelinetext",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&24",
        .statustip = "Sets the toolbar icon size to 24x24:  ICON24",
        .alias = "SINGLELINETEXT"
    },
    {
        .id = ACTION_SNOWFLAKE,
        .main = snowflake_command,
        .icon = "snowflake",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&24",
        .statustip = "Sets the toolbar icon size to 24x24:  ICON24",
        .alias = "SNOWFLAKE"
    },
    {
        .id = ACTION_STAR,
        .main = star_command,
        .icon = "star",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Icon&24",
        .statustip = "Sets the toolbar icon size to 24x24:  ICON24",
        .alias = "STAR"
    },
    {
        .id = ACTION_SYSWINDOWS,
        .main = syswindows_command,
        .icon = "syswindows",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&SysWindows",
        .statustip = "Arrange the windows. Command: SYSWINDOWS",
        .alias = "WINDOWS, SYSWINDOWS"
    },
    {
        .id = ACTION_TEXT_BOLD,
        .main = text_bold_command,
        .icon = "textbold",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Bold Text",
        .statustip = "Sets text to be bold. Command: BOLD.",
        .alias = "BOLD"
    },
    {
        .id = ACTION_TEXT_ITALIC,
        .main = text_italic_command,
        .icon = "textitalic",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Italic Text",
        .statustip = "Sets text to be italic. Command: ITALIC.",
        .alias = "ITALIC"
    },
    {
        .id = ACTION_TEXT_UNDERLINE,
        .main = text_underline_command,
        .icon = "textunderline",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Underline Text",
        .statustip = "Sets text to be underlined. Command: UNDERLINE.",
        .alias = "UNDERLINE"
    },
    {
        .id = ACTION_TEXT_STRIKEOUT,
        .main = text_strikeout_command,
        .icon = "textstrikeout",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&StrikeOut Text",
        .statustip = "Sets text to be striked out. Command: STRIKEOUT.",
        .alias = "STRIKEOUT"
    },
    {
        .id = ACTION_TEXT_OVERLINE,
        .main = text_overline_command,
        .icon = "textoverline",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Overline Text",
        .statustip = "Sets text to be overlined. Command: OVERLINE.",
        .alias = "OVERLINE"
    },
    {
        .id = ACTION_TIP_OF_THE_DAY,
        .main = tipoftheday_command,
        .icon = "tipoftheday",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Tip Of The Day",
        .statustip = "Displays a dialog with useful tips:  TIPS",
        .alias = "TIPS, TIPOFTHEDAY"
    },
    {
        .id = ACTION_TODO,
        .main = todo_command,
        .icon = "todo",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&About",
        .statustip = "Displays information about this product:  ABOUT",
        .alias = "TODO"
    },
    {
        .id = ACTION_UNDO,
        .main = undo_command,
        .icon = "undo",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Undo",
        .statustip = "Reverses the most recent action. Command: UNDO.",
        .alias = "U, UNDO"
    },
    {
        .id = ACTION_VULCANIZE,
        .main = vulcanize_command,
        .icon = "vulcanize",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Undo",
        .statustip = "Reverses the most recent action:  UNDO",
        .alias = "VULCANIZE"
    },
    {
        .id = ACTION_WINDOW_CASCADE,
        .main = windowcascade_command,
        .icon = "windowcascade",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Cascade",
        .statustip = "Cascade the windows. Command: CASCADE.",
        .alias = "CASCADE, WINDOWCASCADE"
    },
    {
        .id = ACTION_WHATS_THIS,
        .main = whats_this_command,
        .icon = "whatsthis",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&What's This?",
        .statustip = "What's This? Context Help! Command: WHATSTHIS.",
        .alias = "WHATSTHIS"
    },
    {
        .id = ACTION_WINDOW_CLOSE,
        .main = windowclose_command,
        .icon = "windowcascade",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Cl&ose",
        .statustip = "Close the active window. Command: CLOSE.",
        .alias = "CLOSE, WINDOWCLOSE"
    },
    {
        .id = ACTION_WINDOW_CLOSE_ALL,
        .main = windowcloseall_command,
        .icon = "windowcloseall",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Close &All",
        .statustip = "Close all the windows. Command: CLOSEALL",
        .alias = "CLOSEALL, WINDOWCLOSEALL"
    },
    {
        .id = ACTION_WINDOW_NEXT,
        .main = windownext_command,
        .icon = "windownext",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Ne&xt",
        .statustip = "Move the focus to the next window:  NEXT",
        .alias = "NEXT, WINDOWNEXT"
    },
    {
        .id = ACTION_WINDOW_PREVIOUS,
        .main = windowprevious_command,
        .icon = "windowprevious",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Pre&vious",
        .statustip = "Move the focus to the previous window:  PREVIOUS",
        .alias = "PREV, PREVIOUS, WINDOWPREVIOUS"
    },
    {
        .id = ACTION_WINDOW_TILE,
        .main = windowtile_command,
        .icon = "windowtile",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "&Tile",
        .statustip = "Tile the windows:  TILE",
        .alias = "TILE, WINDOWTILE"
    },
    {
        .id = ACTION_ZOOM_ALL,
        .main = zoom_all_command,
        .icon = "zoomall",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Zoom &All",
        .statustip = "Zooms to display the drawing extents or the grid limits. Command: ZOOMALL.",
        .alias = "ZOOMALL"
    },
    {
        .id = ACTION_ZOOM_CENTER,
        .main = zoom_center_command,
        .icon = "zoomcenter",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Zoom &Center",
        .statustip = "Zooms to display a view specified by a center point and magnification or height. Command: ZOOMCENTER.",
        .alias = "ZOOMCENTER"
    },
    {
        .id = ACTION_ZOOM_DYNAMIC,
        .main = zoom_dynamic_command,
        .icon = "zoomdynamic",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Zoom &Dynamic",
        .statustip = "Zooms to display the generated portion of the drawing. Command: ZOOMDYNAMIC.",
        .alias = "ZOOMDYNAMIC"
    },
    {
        .id = ACTION_ZOOM_EXTENTS,
        .main = zoom_extents_command,
        .icon = "zoomextents",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Zoom &Extents",
        .statustip = "Zooms to display the drawing extents. Command: ZOOMEXTENTS",
        .alias = "ZOOMEXTENTS"
    },
    {
        .id = ACTION_ZOOM_IN,
        .main = zoom_in_command,
        .icon = "zoomin",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Zoom &In",
        .statustip = "Zooms to increase the apparent size of objects. Command: ZOOMIN",
        .alias = "ZOOMIN"
    },
    {
        .id = ACTION_ZOOM_OUT,
        .main = zoom_out_command,
        .icon = "zoomout",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Zoom &Out",
        .statustip = "Zooms to decrease the apparent size of objects. Command: ZOOMOUT",
        .alias = "ZOOMOUT"
    },
    {
        .id = ACTION_ZOOM_PREVIOUS,
        .main = zoom_previous_command,
        .icon = "zoomprevious",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Zoom &Previous",
        .statustip = "Zooms to display the previous view. Command: ZOOMPREVIOUS.",
        .alias = "ZOOMPREVIOUS"
    },
    {
        .id = ACTION_ZOOM_REAL_TIME,
        .main = zoom_real_time_command,
        .icon = "zoomrealtime",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Zoom &Real Time",
        .statustip = "Zooms to increase or decrease the apparent size of objects in the current viewport. Command: ZOOMREALTIME",
        .alias = "ZOOMREALTIME"
    },
    {
        .id = ACTION_ZOOM_SCALE,
        .main = zoom_scale_command,
        .icon = "zoomscale",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Zoom &Scale",
        .statustip = "Zooms the display using a specified scale factor. Command: ZOOMSCALE.",
        .alias = "ZOOMSCALE"
    },
    {
        .id = ACTION_ZOOM_SELECTED,
        .main = zoom_selected_command,
        .icon = "zoomselected",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Zoom Selec&ted",
        .statustip = "Zooms to display the selected objects. Command: ZOOMSELECTED.",
        .alias = "ZOOMSELECTED"
    },
    {
        .id = ACTION_ZOOM_WINDOW,
        .main = zoom_window_command,
        .icon = "zoomwindow",
        .menu_name = "None",
        .menu_position = 0,
        .toolbar_name = "None",
        .toolbar_position = 0,
        .tooltip = "Zoom &Window",
        .statustip = "Zooms to display an area specified by a rectangular window. Command: ZOOMIN",
        .alias = "ZOOMWINDOW"
    },
    {
        .id = ACTION_DO_NOTHING,
        .main = do_nothing,
        .icon = "blank",
        .menu_name = "None",
        .menu_position = -1,
        .toolbar_name = "None",
        .toolbar_position = -1,
        .tooltip = "NULL",
        .statustip = "NULL",
        .alias = "NULL"
    }
};
