/*
 * Embroidermodder 2.
 *
 * Copyright 2011-2024 The Embroidermodder Team
 * Embroidermodder 2 is Open Source Software, see LICENSE.md for licensing terms.
 * Visit https://www.libembroidery.org/refman for advice on altering this file,
 * or read the markdown version in embroidermodder2/docs/refman.
 *
 * Commands
 */

#include <QString>
#include <QDebug>
#include <QWidget>

#include "view.h"
#include "undo-commands.h"
#include "embroidermodder.h"

/* Simple Commands (other commands, like circle_command are housed in their
 * own file with their associated functions)
 * ------------------------------------------------------------------------
 */

/* TODO: QTabWidget for about dialog
 */
ScriptValue
about_command(ScriptEnv *context)
{
    if (!argument_checks(context, "about", "")) {
        return script_false;
    }

    _main->nativeInitCommand();

    QApplication::setOverrideCursor(Qt::ArrowCursor);
    qDebug("about()");

    QString appDir = qApp->applicationDirPath();
    QString appName = QApplication::applicationName();
    QString title = "About " + appName;

    QDialog dialog(_main);
    QLabel image_label;
    QPixmap img(appDir + "/images/logo-small.png");
    image_label.setPixmap(img);
    QLabel text(appName + "\n\n" +
        _main->tr("http://www.libembroidery.org") +
        "\n\n" +
        _main->tr("Available Platforms: GNU/Linux, Windows, Mac OSX, Raspberry Pi") +
        "\n\n" +
        _main->tr("Embroidery formats by Josh Varga.") +
        "\n" +
        _main->tr("User Interface by Jonathan Greig.") +
        "\n\n" +
        _main->tr("Free under the zlib/libpng license.")
        #if defined(BUILD_GIT_HASH)
        + "\n\n" +
        _main->tr("Build Hash: ") + qPrintable(BUILD_GIT_HASH)
        #endif
        );
    text.setWordWrap(true);

    QDialogButtonBox buttonbox(Qt::Horizontal, &dialog);
    QPushButton button(&dialog);
    button.setText("Oh, Yeah!");
    buttonbox.addButton(&button, QDialogButtonBox::AcceptRole);
    buttonbox.setCenterButtons(true);
    _main->connect(&buttonbox, SIGNAL(accepted()), &dialog, SLOT(accept()));

    QVBoxLayout layout;
    layout.setAlignment(Qt::AlignCenter);
    layout.addWidget(&image_label);
    layout.addWidget(&text);
    layout.addWidget(&buttonbox);

    dialog.setWindowTitle(title);
    dialog.setMinimumWidth(image_label.minimumWidth()+30);
    dialog.setMinimumHeight(image_label.minimumHeight()+50);
    dialog.setLayout(&layout);
    dialog.exec();

    QApplication::restoreOverrideCursor();
    _main->nativeEndCommand();
}

/* ACTION_ALERT is a prompt-only command. */
ScriptValue
alert_command(ScriptEnv *context)
{
    if (!argument_checks(context, "alert", "s")) {
        return script_false;
    }

    _main->nativeInitCommand();
    _main->prompt->alert(QSTR(0));
    _main->nativeEndCommand();
    return script_null;
}

/* . */
ScriptValue
angle_command(ScriptEnv *context)
{
    _main->nativeInitCommand();
    _main->nativeClearSelection();

    _main->nativeEndCommand();
    return script_null;
}

/* WINDOWTILE is not context-dependant */
ScriptValue
changelog_command(ScriptEnv *context)
{
    if (!argument_checks(context, "whats_this_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->nativeEndCommand();
    return script_null;
}

/* CLEAR is not context-dependant. */
ScriptValue
clear_command(ScriptEnv* context)
{
    if (!argument_checks(context, "clear_command", "")) {
        return script_false;
    }

    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->nativeEndCommand();
    return script_null;
}

/* WINDOWTILE is not context-dependant */
ScriptValue
copy_command(ScriptEnv *context)
{
    if (!argument_checks(context, "whats_this_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->nativeEndCommand();
    return script_null;
}

/* WINDOWTILE is not context-dependant */
ScriptValue
cut_command(ScriptEnv *context)
{
    if (!argument_checks(context, "whats_this_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->nativeEndCommand();
    return script_null;
}

/* . */
ScriptValue
colorselector_command(ScriptEnv*)
{
    return script_null;
}

/* . */
ScriptValue
hidealllayers_command(ScriptEnv*)
{
    return script_null;
}

/* . */
ScriptValue
freezealllayers_command(ScriptEnv*)
{
    return script_null;
}

/* . */
ScriptValue
layers_command(ScriptEnv*)
{
    /* layerManager(); */
    return script_null;
}

/* . */
ScriptValue
layerprevious_command(ScriptEnv*)
{
    return script_null;
}

/* . */
ScriptValue
layerselector_command(ScriptEnv*)
{
    return script_null;
}

/* . */
ScriptValue
linetypeselector_command(ScriptEnv*)
{
    return script_null;
}

/* . */
ScriptValue
lineweightselector_command(ScriptEnv*)
{
    return script_null;
}

/* . */
ScriptValue
lockalllayers_command(ScriptEnv*)
{
    return script_null;
}

/* . */
ScriptValue
makelayercurrent_command(ScriptEnv*)
{
    /* makeLayerActive(); */
    return script_null;
}

/* . */
ScriptValue
panpoint_command(ScriptEnv*)
{
    return script_null;
}

/* . */
ScriptValue
panrealtime_command(ScriptEnv*)
{
    return script_null;
}

/* . */
ScriptValue
showalllayers_command(ScriptEnv*)
{
    return script_null;
}

/* . */
ScriptValue
thawalllayers_command(ScriptEnv*)
{
    return script_null;
}

/* . */
ScriptValue
unlockalllayers_command(ScriptEnv*)
{
    return script_null;
}

/* DAY is not context-dependant. */
ScriptValue
day_command(ScriptEnv *context)
{
    if (!argument_checks(context, "day_command", "")) {
        return script_false;
    }

    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->dayVision();
    _main->nativeEndCommand();
    return script_null;
}

/* . */
ScriptValue
debug_command(ScriptEnv *context)
{
    if (!argument_checks(context, "about", "s")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->nativeAppendPromptHistory(QSTR(0));
    _main->nativeEndCommand();
    return script_null;
}

/* DONOTHING is not context-dependant. */
ScriptValue
design_details_command(ScriptEnv *context)
{
    if (!argument_checks(context, "design_details_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->nativeEndCommand();
    return script_true;
}

/* DISABLE is a prompt-only Command. */
ScriptValue
disable_command(ScriptEnv* context)
{
    if (!argument_checks(context, "disable_prompt", "s")) {
        return script_false;
    }

    QString value = QSTR(0);

    _main->nativeInitCommand();

    if (value == "RAPIDFIRE") {
        _main->disablePromptRapidFire();
    }

    _main->nativeEndCommand();
    return script_null;
}

/* DONOTHING is not context-dependant. */
ScriptValue
do_nothing(ScriptEnv *context)
{
    if (!argument_checks(context, "do_nothing", "")) {
        return script_false;
    }
    return script_true;
}

/* ENABLE is a prompt-only Command. */
ScriptValue
enable_command(ScriptEnv* context)
{
    if (context->argumentCount != 2) {
        return script_false;
    }

    QString value = QSTR(0);

    _main->nativeInitCommand();

    if (value == "RAPIDFIRE") {
        _main->enablePromptRapidFire();
    }

    _main->nativeEndCommand();
    return script_null;
}

/* Erase is not context-dependant. */
ScriptValue
erase_command(ScriptEnv * /* context */)
{
    _main->nativeInitCommand();
    if (_main->nativeNumSelected() <= 0) {
        //TODO: Prompt to select objects if nothing is preselected
        _main->prompt->alert(translate("Preselect objects before invoking the delete command."));
        _main->nativeEndCommand();
        _main->messageBox("information", translate("Delete Preselect"), translate("Preselect objects before invoking the delete command."));
    }
    else {
        _main->nativeDeleteSelected();
        _main->nativeEndCommand();
    }
    _main->nativeEndCommand();
    return script_null;
}

/* Error is not context-dependant. */
ScriptValue
error_command(ScriptEnv *context)
{
    if (!argument_checks(context, "error_command", "ss")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    QString s = "ERROR: (" + QSTR(0) + ") " + QSTR(1);
    _main->nativeSetPromptPrefix(s);
    _main->nativeAppendPromptHistory(QString());
    _main->nativeEndCommand();
    return script_null;
}

/* . */
ScriptValue
exit_command(ScriptEnv * /* context */)
{
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->exit();
    _main->nativeEndCommand();
    return script_null;
}

/* GET is a prompt-only Command. */
ScriptValue
get_command(ScriptEnv* context)
{
    if (!argument_checks(context, "get_prompt", "s")) {
        return script_false;
    }

    QString value = QSTR(0);

    _main->nativeInitCommand();

    if (value == "MOUSEX") {
        QGraphicsScene* scene = activeScene();
        if (!scene) {
            _main->nativeEndCommand();
            return script_false;
        }
        ScriptValue r = script_real(scene->property(SCENE_MOUSE_POINT).toPointF().x());
        //_main->qDebug("mouseY: %.50f", r.r);
        _main->nativeEndCommand();
        return r;
    }
    else if (value == "MOUSEY") {
        QGraphicsScene* scene = activeScene();
        if (!scene) {
            _main->nativeEndCommand();
            return script_false;
        }
        ScriptValue r = script_real(-scene->property(SCENE_MOUSE_POINT).toPointF().y());
        //_main->qDebug("mouseY: %.50f", r.r);
        _main->nativeEndCommand();
        return r;
    }
    else if (value == "TEXTANGLE") {
        return script_real(_main->textAngle());
    }
    else if (value == "TEXTBOLD") {
        return script_bool(_main->textBold());
    }
    else if (value == "TEXTITALIC") {
        return script_bool(_main->textItalic());
    }
    else if (value == "TEXTFONT") {
        return script_string(qPrintable(_main->textFont()));
    }
    else if (value == "TEXTOVERLINE") {
        return script_real(_main->textOverline());
    }
    else if (value == "TEXTSIZE") {
        return script_real(_main->textSize());
    }
    else if (value == "TEXTSTRIKEOUT") {
        return script_real(_main->textStrikeOut());
    }
    else if (value == "TEXTUNDERLINE") {
        return script_bool(_main->textUnderline());
    }
    else if (value == "QSNAPX") {
        return script_bool(_main->nativeQSnapX());
    }
    else if (value == "QSNAPY") {
        return script_bool(_main->nativeQSnapY());
    }

    _main->nativeEndCommand();
    return script_null;
}

/* HELP is not context-dependent. */
ScriptValue
help_command(ScriptEnv * /* context */)
{
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->help();
    _main->nativeEndCommand();
    return script_null;
}

ScriptValue
icon128_command(ScriptEnv *context)
{
    if (!argument_checks(context, "icon128_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->iconResize(128);
    _main->nativeEndCommand();
    return script_null;
}

ScriptValue
icon16_command(ScriptEnv * context)
{
    if (!argument_checks(context, "icon16_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->iconResize(16);
    _main->nativeEndCommand();
    return script_null;
}

ScriptValue
icon24_command(ScriptEnv * context)
{
    if (!argument_checks(context, "icon24_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->iconResize(24);
    _main->nativeEndCommand();
    return script_null;
}

ScriptValue
icon32_command(ScriptEnv * context)
{
    if (!argument_checks(context, "icon32_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->iconResize(32);
    _main->nativeEndCommand();
    return script_null;
}

ScriptValue
icon48_command(ScriptEnv * context)
{
    if (!argument_checks(context, "icon48_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->iconResize(48);
    _main->nativeEndCommand();
    return script_null;
}

ScriptValue
icon64_command(ScriptEnv * context)
{
    if (!argument_checks(context, "icon64_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->iconResize(64);
    _main->nativeEndCommand();
    return script_null;
}

/* MIRRORSELECTED */
ScriptValue
mirrorselected_command(ScriptEnv *context)
{
    if (!argument_checks(context, "mirrorSelected", "rrrr")) {
        return script_false;
    }

    _main->nativeInitCommand();
    _main->nativeMirrorSelected(REAL(0), REAL(1), REAL(2), REAL(3));
    _main->nativeEndCommand();
    return script_null;
}

/* MOVESELECTED */
ScriptValue
moveselected_command(ScriptEnv *context)
{
    _main->nativeEndCommand();
    return script_null;
}

/* NEW is not context-dependant. */
ScriptValue
new_command(ScriptEnv * context)
{
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->newFile();
    _main->nativeEndCommand();
    return script_null;
}

/* NIGHT is not context-sensitive. */
ScriptValue
night_command(ScriptEnv * context)
{
    _main->nativeInitCommand();
    _main->nightVision();
    _main->nativeEndCommand();
    return script_null;
}

/* OPEN is not context-sensitive. */
ScriptValue
open_command(ScriptEnv * context)
{
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->openFile();
    _main->nativeEndCommand();
    return script_null;
}

/* PANDOWN is context-independant. */
ScriptValue
pandown_command(ScriptEnv * context)
{
    _main->nativeInitCommand();
    _main->panDown();
    _main->nativeEndCommand();
    return script_null;
}

/* NOTE: main() is run every time the command is started.
 *       Use it to reset variables so they are ready to go.
 */
ScriptValue
panleft_command(ScriptEnv * context)
{
    _main->nativeInitCommand();
    _main->panLeft();
    _main->nativeEndCommand();
    return script_null;
}

/* NOTE: main() is run every time the command is started.
 *       Use it to reset variables so they are ready to go.
 */
ScriptValue
panright_command(ScriptEnv * context)
{
    _main->nativeInitCommand();
    _main->panRight();
    _main->nativeEndCommand();
    return script_null;
}

/* PANUP */
ScriptValue
panup_command(ScriptEnv * context)
{
    _main->debug_message("panUp()");
    if (!argument_checks(context, "panup_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    View* gview = activeView();
    QUndoStack* stack = gview->getUndoStack();
    if (gview && stack) {
        UndoableNavCommand* cmd = new UndoableNavCommand("PanUp", gview, 0);
        stack->push(cmd);
    }
    _main->nativeEndCommand();
    return script_null;
}

/* WINDOWTILE is not context-dependant */
ScriptValue
paste_command(ScriptEnv *context)
{
    if (!argument_checks(context, "whats_this_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->nativeEndCommand();
    return script_null;
}

/* PLATFORM is not context-sensitive.
 * Should this display in the command prompt or just return like GET?
 */
ScriptValue
platform_command(ScriptEnv *context)
{
    if (!argument_checks(context, "debug", "")) {
        return script_false;
    }

    _main->nativeInitCommand();
//  setPromptPrefix(qsTr("Platform") + " = " + _main->platformString());
//  appendPromptHistory();
    _main->nativeEndCommand();
    return script_null;
}

/* PREVIEWOFF . */
ScriptValue
previewoff_command(ScriptEnv *context)
{
    if (!argument_checks(context, "PreviewOff", "")) {
        return script_false;
    }

    View* gview = activeView();
    if (gview) {
        gview->previewOff();
    }
    _main->nativeEndCommand();
    return script_null;
}

/* PREVIEWON . */
ScriptValue
previewon_command(ScriptEnv *context)
{
    if (!argument_checks(context, "previewon_command", "ssrrr")) {
        return script_false;
    }

    QString cloneStr = QSTR(0).toUpper();
    int clone = PREVIEW_CLONE_NULL;
    if (cloneStr == "SELECTED") {
        clone = PREVIEW_CLONE_SELECTED;
    }
    else if (cloneStr == "RUBBER") {
        clone = PREVIEW_CLONE_RUBBER;
    }
    else {
        debug_message("UNKNOWN_ERROR previewOn(): first argument must be \"SELECTED\" or \"RUBBER\".");
        return script_false;
    }

    QString modeStr  = QSTR(1).toUpper();
    int mode = PREVIEW_MODE_NULL;
    if (modeStr == "MOVE") {
        mode = PREVIEW_MODE_MOVE;
    }
    else if (modeStr == "ROTATE") {
        mode = PREVIEW_MODE_ROTATE;
    }
    else if (modeStr == "SCALE") {
        mode = PREVIEW_MODE_SCALE;
    }
    else {
        debug_message("UNKNOWN_ERROR previewOn(): second argument must be \"MOVE\", \"ROTATE\" or \"SCALE\".");
        return script_false;
    }

    View* gview = activeView();
    if (gview) {
        gview->previewOn(clone, mode, REAL(2), -REAL(3), REAL(4));
    }
    else {
        debug_message("Preview on requires an active view.");
    }
    _main->nativeEndCommand();
    return script_null;
}

/* PRINT . */
ScriptValue
print_command(ScriptEnv *context)
{
    _main->nativeInitCommand();
    _main->nativeClearSelection();

    _main->nativeEndCommand();
    return script_null;
}

/* REDO is not context-sensitive. */
ScriptValue
redo_command(ScriptEnv * context)
{
    if (!argument_checks(context, "redo_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->redo();
    _main->nativeEndCommand();
    return script_null;
}

/* SAVE. */
ScriptValue
save_command(ScriptEnv *context)
{
    if (!argument_checks(context, "redo_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->nativeEndCommand();
    return script_null;
}

/* SCALESELECTED . */
ScriptValue
scaleselected_command(ScriptEnv *context)
{
    _main->nativeEndCommand();
    return script_null;
}

/* SET is a prompt-only Command.
 *
 * We can't use the argument_checks function because the 2nd argument is a wildcard.
 */
ScriptValue
set_command(ScriptEnv* context)
{
    if (context->argumentCount != 2) {
        return script_false;
    }

    QString value = QSTR(0);

    _main->nativeInitCommand();

    if (value == "TEXTANGLE") {
        if (context->argument[1].type != SCRIPT_REAL) {
            return script_false;
        }
        _main->setSettingsTextAngle(REAL(1));
    }
    else if (value == "TEXTBOLD") {
        if (context->argument[1].type != SCRIPT_BOOL) {
            return script_false;
        }
        _main->setSettingsTextStyleBold(BOOL(1));
    }
    else if (value == "TEXTITALIC") {
        if (context->argument[1].type != SCRIPT_BOOL) {
            return script_false;
        }
        _main->setSettingsTextStyleItalic(BOOL(1));
    }
    else if (value == "TEXTFONT") {
        if (context->argument[1].type != SCRIPT_STRING) {
            return script_false;
        }
        _main->setSettingsTextFont(context->argument[1].s);
    }
    else if (value == "TEXTOVERLINE") {
        if (context->argument[1].type != SCRIPT_BOOL) {
            return script_false;
        }
        _main->setSettingsTextStyleOverline(BOOL(1));
    }
    else if (value == "TEXTSIZE") {
        if (context->argument[1].type != SCRIPT_REAL) {
            return script_false;
        }
        _main->setSettingsTextSize(REAL(1));
    }
    else if (value == "TEXTSTRIKEOUT") {
        if (context->argument[1].type != SCRIPT_BOOL) {
            return script_false;
        }
        _main->setSettingsTextStyleStrikeOut(BOOL(1));
    }
    else if (value == "TEXTUNDERLINE") {
        if (context->argument[1].type != SCRIPT_BOOL) {

            return script_false;
        }
        _main->setSettingsTextStyleUnderline(BOOL(1));
    }

    _main->nativeEndCommand();
    return script_null;
}

/* WINDOWTILE is not context-dependant */
ScriptValue
settings_dialog_command(ScriptEnv *context)
{
    if (!argument_checks(context, "settings_dialog_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->settingsDialog();
    _main->nativeEndCommand();
    return script_null;
}

/* NOTE: main() is run every time the command is started.
 *       Use it to reset variables so they are ready to go.
 */
ScriptValue
syswindows_command(ScriptEnv * context)
{
    /*
    initCommand();
    clearSelection();
    setPromptPrefix(qsTr("Enter an option [Cascade/Tile]: "));
    */

    // Do nothing for click, context
    
    #if 0
    if (str == "C" || str == "CASCADE") {
        //TODO: Probably should add additional qsTr calls here.
        _main->windowCascade();
        _main->endCommand();
    }
    else if (str == "T" || str == "TILE") {
        //TODO: Probably should add additional qsTr calls here.
        _main->windowTile();
        _main->endCommand();
    }
    else {
        alert(qsTr("Invalid option keyword."));
        setPromptPrefix(qsTr("Enter an option [Cascade/Tile]: "));
    }
    #endif
    return script_null;
}

/* ZOOMIN is not context-dependant */
ScriptValue
text_bold_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomin_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    /* _main->setSettingsTextStyleBold(); */
    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMIN is not context-dependant */
ScriptValue
text_italic_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomin_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    /* _main->setSettingsTextStyleItalic(); */
    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMIN is not context-dependant */
ScriptValue
text_underline_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomin_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    /* _main->setSettingsTextStyleUnderline(); */
    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMIN is not context-dependant */
ScriptValue
text_overline_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomin_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    /* _main->setSettingsTextStyleOverline(); */
    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMIN is not context-dependant */
ScriptValue
text_strikeout_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomin_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    /* _main->setSettingsTextStyleStrikeOut(); */
    _main->nativeEndCommand();
    return script_null;
}


/* TIPOFTHEDAY is not context-sensitive. */
ScriptValue
tipoftheday_command(ScriptEnv * context)
{
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->tipOfTheDay();
    _main->nativeEndCommand();
    return script_null;
}

/* TODO is not context-sensitive. */
ScriptValue
todo_command(ScriptEnv *context)
{
    if (!argument_checks(context, "todo", "ss")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->prompt->alert("TODO: (" + QSTR(0) + ") " + QSTR(1));
    _main->nativeEndCommand();
    return script_null;
}

/* NOTE: main() is run every time the command is started.
 *       Use it to reset variables so they are ready to go.
 */
ScriptValue
undo_command(ScriptEnv * context)
{
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->undo();
    _main->nativeEndCommand();
    return script_null;
}

/* VULCANIZE is not context-sensitve. */
ScriptValue
vulcanize_command(ScriptEnv * context)
{
    if (!argument_checks(context, "vulcanize", "")) {
        return script_false;
    }

    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->nativeVulcanize();
    _main->nativeEndCommand();
    return script_null;
}

/* WINDOWTILE is not context-dependant */
ScriptValue
whats_this_command(ScriptEnv *context)
{
    if (!argument_checks(context, "whats_this_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->nativeEndCommand();
    return script_null;
}

/* WINDOWCASCADE is not context-dependant. */
ScriptValue
windowcascade_command(ScriptEnv * context)
{
    if (!argument_checks(context, "windowcascade_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->mdiArea->cascade();
    _main->nativeEndCommand();
    return script_null;
}

/* WINDOWCLOSE is not context-dependant. */
ScriptValue
windowclose_command(ScriptEnv * context)
{
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->onCloseWindow();
    _main->nativeEndCommand();
    return script_null;
}

/* WINDOWCLOSEALL is not context-dependant. */
ScriptValue
windowcloseall_command(ScriptEnv * context)
{
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->mdiArea->closeAllSubWindows();
    _main->nativeEndCommand();
    return script_null;
}

/* */
ScriptValue
windownext_command(ScriptEnv * context)
{
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->mdiArea->activateNextSubWindow();
    _main->nativeEndCommand();
    return script_null;
}

/* WINDOWPREVIOUS is not context-sensitive. */
ScriptValue
windowprevious_command(ScriptEnv * context)
{
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->mdiArea->activatePreviousSubWindow();
    _main->nativeEndCommand();
    return script_null;
}

/* WINDOWTILE is not context-dependant */
ScriptValue
windowtile_command(ScriptEnv *context)
{
    if (!argument_checks(context, "windowtile_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->mdiArea->tile();
    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMEXTENTS is not context-dependant */
ScriptValue
zoom_all_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomextents_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->zoomExtents();
    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMEXTENTS is not context-dependant */
ScriptValue
zoom_dynamic_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomextents_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->zoomExtents();
    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMEXTENTS is not context-dependant */
ScriptValue
zoom_center_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomextents_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->zoomExtents();
    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMEXTENTS is not context-dependant */
ScriptValue
zoom_extents_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomextents_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    _main->zoomExtents();
    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMIN is not context-dependant */
ScriptValue
zoom_in_command(ScriptEnv *context)
{
    _main->debug_message("zoomIn()");
    if (!argument_checks(context, "zoom_in_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();

    View* gview = activeView();
    if (gview) {
        gview->zoomIn();
    }

    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMIN is not context-dependant */
ScriptValue
zoom_previous_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomin_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();

    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMIN is not context-dependant */
ScriptValue
zoom_real_time_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomin_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();

    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMOUT is not context-dependant */
ScriptValue
zoom_out_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomout_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();

    View* gview = activeView();
    if (gview) {
        gview->zoomOut();
    }

    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMIN is not context-dependant */
ScriptValue
zoom_scale_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomin_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();

    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMIN is not context-dependant */
ScriptValue
zoom_selected_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomin_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();

    _main->nativeEndCommand();
    return script_null;
}

/* ZOOMIN is not context-dependant */
ScriptValue
zoom_window_command(ScriptEnv *context)
{
    if (!argument_checks(context, "zoomin_command", "")) {
        return script_false;
    }
    _main->nativeInitCommand();
    _main->nativeClearSelection();

    _main->nativeEndCommand();
    return script_null;
}

/* --------------------------------------------------------------------------
 */

ScriptValue
javaBlinkPrompt(ScriptEnv* context)
{
    if (!argument_checks(context, "debug", "")) {
        return script_false;
    }

    _main->nativeBlinkPrompt();
    return script_null;
}

ScriptValue
javaSetPromptPrefix(ScriptEnv* context)
{
    if (!argument_checks(context, "debug", "s")) {
        return script_false;
    }
    _main->nativeSetPromptPrefix(QSTR(0));
    return script_null;
}

ScriptValue
javaAppendPromptHistory(ScriptEnv* context)
{
    int args = context->argumentCount;
    if (args == 0) {
        _main->nativeAppendPromptHistory(QString());
    }
    else if (args == 1) {
        _main->nativeAppendPromptHistory(QSTR(0));
    }
    else {
        debug_message("appendPromptHistory() requires one or zero arguments");
        return script_false;
    }
    return script_null;
}

ScriptValue
javaEnablePromptRapidFire(ScriptEnv* context)
{
    if (!argument_checks(context, "debug", "")) {
        return script_false;
    }

    _main->nativeEnablePromptRapidFire();
    return script_null;
}

ScriptValue
javaDisablePromptRapidFire(ScriptEnv* context)
{
    if (!argument_checks(context, "debug", "")) {
        return script_false;
    }

    _main->nativeDisablePromptRapidFire();
    return script_null;
}

ScriptValue
javaEnableMoveRapidFire(ScriptEnv* context)
{
    if (!argument_checks(context, "debug", "")) {
        return script_false;
    }

    _main->nativeEnableMoveRapidFire();
    return script_null;
}

ScriptValue
javaDisableMoveRapidFire(ScriptEnv* context)
{
    if (!argument_checks(context, "debug", "")) {
        return script_false;
    }

    _main->nativeDisableMoveRapidFire();
    return script_null;
}

ScriptValue
javaMessageBox(ScriptEnv* context)
{
    if (!argument_checks(context, "debug", "sss")) {
        return script_false;
    }

    QString type  = QSTR(0).toLower();
    QString title = QSTR(1);
    QString text  = QSTR(2);

    if (type != "critical" && type != "information" && type != "question" && type != "warning") {
        debug_message("UNKNOWN_ERROR messageBox(): first argument must be \"critical\", \"information\", \"question\" or \"warning\".");
        return script_false;
    }

    _main->messageBox(type, title, text);
    return script_null;
}

ScriptValue
javaIsInt(ScriptEnv* context)
{
    if (!argument_checks(context, "debug", "i")) {
        return script_false;
    }
    return script_true;
}

ScriptValue
javaPrintArea(ScriptEnv* context)
{
    if (!argument_checks(context, "printArea", "rrrr")) {
        return script_false;
    }
    _main->nativePrintArea(REAL(0), REAL(1), REAL(2), REAL(3));
    return script_null;
}

ScriptValue
javaSetBackgroundColor(ScriptEnv* context)
{
    if (!argument_checks(context, "debug", "rrr")) {
        return script_false;
    }
    if (REAL(0) < 0 || REAL(0) > 255) {
        debug_message("UNKNOWN_ERROR setBackgroundColor(): r value must be in range 0-255");
        return script_false;
    }
    if (REAL(1) < 0 || REAL(1) > 255) {
        debug_message("UNKNOWN_ERROR setBackgroundColor(): g value must be in range 0-255");
        return script_false;
    }
    if (REAL(2) < 0 || REAL(2) > 255) {
        debug_message("UNKNOWN_ERROR setBackgroundColor(): b value must be in range 0-255");
        return script_false;
    }

    _main->nativeSetBackgroundColor(REAL(0), REAL(1), REAL(2));
    return script_null;
}

ScriptValue
javaSetCrossHairColor(ScriptEnv* context)
{
    if (!argument_checks(context, "debug", "rrr")) {
        return script_false;
    }

    if (REAL(0) < 0 || REAL(0) > 255) {
        debug_message("UNKNOWN_ERROR setCrossHairColor(): r value must be in range 0-255");
        return script_false;
    }
    if (REAL(1) < 0 || REAL(1) > 255) {
        debug_message("UNKNOWN_ERROR setCrossHairColor(): g value must be in range 0-255");
        return script_false;
    }
    if (REAL(2) < 0 || REAL(2) > 255) {
        debug_message("UNKNOWN_ERROR setCrossHairColor(): b value must be in range 0-255");
        return script_false;
    }

    _main->nativeSetCrossHairColor(REAL(0), REAL(1), REAL(2));
    return script_null;
}

ScriptValue
javaSetGridColor(ScriptEnv* context)
{
    if (!argument_checks(context, "debug", "rrr")) {
        return script_false;
    }

    if (REAL(0) < 0 || REAL(0) > 255) {
        debug_message("UNKNOWN_ERROR setGridColor(): r value must be in range 0-255");
        return script_false;
    }
    if (REAL(1) < 0 || REAL(1) > 255) {
        debug_message("UNKNOWN_ERROR setGridColor(): g value must be in range 0-255");
        return script_false;
    }
    if (REAL(2) < 0 || REAL(2) > 255) {
        debug_message("UNKNOWN_ERROR setGridColor(): b value must be in range 0-255");
        return script_false;
    }

    _main->nativeSetGridColor(REAL(0), REAL(1), REAL(2));
    return script_null;
}

ScriptValue
add_TextMulti(ScriptEnv* context)
{
    if (!argument_checks(context, "mouseX", "srrrb")) {
        return script_false;
    }
    _main->nativeAddTextMulti(QSTR(0), REAL(1), REAL(2), REAL(3), BOOL(4), OBJ_RUBBER_OFF);
    return script_null;
}

ScriptValue
add_TextSingle(ScriptEnv* context)
{
    if (!argument_checks(context, "mouseX", "srrrb")) {
        return script_false;
    }
    _main->nativeAddTextSingle(QSTR(0), REAL(1), REAL(2), REAL(3), BOOL(4), OBJ_RUBBER_OFF);
    return script_null;
}

ScriptValue
add_InfiniteLine(ScriptEnv* context)
{
    //TODO: parameter error checking
    debug_message("TODO: finish addInfiniteLine command");
    return script_null;
}

ScriptValue
add_Ray(ScriptEnv* context)
{
    //TODO: parameter error checking
    debug_message("TODO: finish addRay command");
    return script_null;
}

ScriptValue
add_line_command(ScriptEnv* context)
{
    if (!argument_checks(context, "add_line_command", "rrrrr")) {
        return script_false;
    }
    _main->nativeAddLine(REAL(0), REAL(1), REAL(2), REAL(3), REAL(4), OBJ_RUBBER_OFF);
    return script_null;
}

ScriptValue
add_triangle_command(ScriptEnv* context)
{
    if (!argument_checks(context, "add_triangle_command", "rrrrrrrb")) {
        return script_false;
    }
    _main->nativeAddTriangle(REAL(0), REAL(1), REAL(2), REAL(3), REAL(4), REAL(5), REAL(6), BOOL(7));
    return script_null;
}

ScriptValue
add_rectangle_command(ScriptEnv* context)
{
    if (!argument_checks(context, "add_rectangle_command", "rrrrrb")) {
        return script_false;
    }
    _main->nativeAddRectangle(REAL(0), REAL(1), REAL(2), REAL(3), REAL(4), BOOL(5), OBJ_RUBBER_OFF);
    return script_null;
}

ScriptValue
add_rounded_rectangle_command(ScriptEnv* context)
{
    if (!argument_checks(context, "add_rounded_rectangle", "rrrrrrb")) {
        return script_false;
    }
    _main->nativeAddRoundedRectangle(REAL(0), REAL(1), REAL(2), REAL(3), REAL(4), REAL(5), BOOL(6));
    return script_null;
}

ScriptValue
add_arc_command(ScriptEnv* context)
{
    if (!argument_checks(context, "mouseX", "rrrrrr")) {
        return script_false;
    }
    _main->nativeAddArc(REAL(0), REAL(1), REAL(2), REAL(3), REAL(4), REAL(5), OBJ_RUBBER_OFF);
    return script_null;
}

ScriptValue
add_circle_command(ScriptEnv* context)
{
    if (!argument_checks(context, "mouseX", "rrrb")) {
        return script_false;
    }
    _main->nativeAddCircle(REAL(0), REAL(1), REAL(2), BOOL(4), OBJ_RUBBER_OFF);
    return script_null;
}

ScriptValue
add_slot_command(ScriptEnv* context)
{
    if (!argument_checks(context, "mouseX", "rrrrrb")) {
        return script_false;
    }
    _main->nativeAddSlot(REAL(0), REAL(1), REAL(2), REAL(3), REAL(4), BOOL(5), OBJ_RUBBER_OFF);
    return script_null;
}

ScriptValue
add_Ellipse(ScriptEnv* context)
{
    if (!argument_checks(context, "mouseX", "rrrrrb")) {
        return script_false;
    }
    _main->nativeAddEllipse(REAL(0), REAL(1), REAL(2), REAL(3), REAL(4), BOOL(5), OBJ_RUBBER_OFF);
    return script_null;
}

ScriptValue
add_Point(ScriptEnv* context)
{
    if (!argument_checks(context, "mouseX", "rr")) {
        return script_false;
    }
    _main->nativeAddPoint(REAL(0), REAL(1));
    return script_null;
}

ScriptValue
add_RegularPolygon(ScriptEnv* context)
{
    //TODO: parameter error checking
    debug_message("TODO: finish addRegularPolygon command");
    return script_null;
}

ScriptValue
add_Polygon(ScriptEnv* context)
{
    #if 0
    if (context->argumentCount != 1) {
        debug_message("addPolygon() requires one argument");
        return script_false;
    }
    if (!context->argument[0].isArray()) {
        debug_message("TYPE_ERROR, addPolygon(): first argument is not an array");
        return script_false;
    }

    QVariantList varList = context->argument[0].toVariant().toList();
    int varSize = varList.size();
    if (varSize < 2) {
        debug_message("TYPE_ERROR, addPolygon(): array must contain at least two elements");
        return script_false;
    }
    if (varSize % 2) {
        debug_message("TYPE_ERROR, addPolygon(): array cannot contain an odd number of elements");
        return script_false;
    }

    bool lineTo = false;
    bool xCoord = true;
    qreal x = 0;
    qreal y = 0;
    qreal startX = 0;
    qreal startY = 0;
    QPainterPath path;
    foreach(QVariant var, varList)
    {
        if (var.canConvert(QVariant::Double))
        {
            if (xCoord)
            {
                xCoord = false;
                x = var.toReal();
            }
            else
            {
                xCoord = true;
                y = -var.toReal();

                if (lineTo) { path.lineTo(x,y); }
                else       { path.moveTo(x,y); lineTo = true; startX = x; startY = y; }
            }
        }
        else {
            debug_message("TYPE_ERROR, addPolygon(): array contains one or more invalid elements");
            return script_false;
        }
    }

    //Close the polygon
    path.closeSubpath();

    path.translate(-startX, -startY);

    _main->nativeAddPolygon(startX, startY, path, OBJ_RUBBER_OFF);
    #endif
    return script_null;
}

ScriptValue
add_Polyline(ScriptEnv* context)
{
    #if 0
    if (context->argumentCount != 1) {
        debug_message("addPolyline() requires one argument");
        return script_false;
    }
    if (!context->argument[0].isArray()) {
        debug_message("TYPE_ERROR, addPolyline(): first argument is not an array");
        return script_false;
    }

    QVariantList varList = context->argument[0].toVariant().toList();
    int varSize = varList.size();
    if (varSize < 2) {
        debug_message("TYPE_ERROR, addPolyline(): array must contain at least two elements");
        return script_false;
    }
    if (varSize % 2) {
        debug_message("TYPE_ERROR, addPolyline(): array cannot contain an odd number of elements");
        return script_false;
    }

    bool lineTo = false;
    bool xCoord = true;
    qreal x = 0;
    qreal y = 0;
    qreal startX = 0;
    qreal startY = 0;
    QPainterPath path;
    foreach(QVariant var, varList) {
        if (var.canConvert(QVariant::Double)) {
            if (xCoord) {
                xCoord = false;
                x = var.toReal();
            }
            else {
                xCoord = true;
                y = -var.toReal();

                if (lineTo) { path.lineTo(x,y); }
                else       { path.moveTo(x,y); lineTo = true; startX = x; startY = y; }
            }
        }
        else {
            debug_message("TYPE_ERROR, addPolyline(): array contains one or more invalid elements");
            return script_false;
        }
    }

    path.translate(-startX, -startY);

    _main->nativeAddPolyline(startX, startY, path, OBJ_RUBBER_OFF);
    #endif
    return script_null;
}

ScriptValue
add_Path(ScriptEnv* context)
{
    //TODO: parameter error checking
    debug_message("TODO: finish addPath command");
    return script_null;
}

ScriptValue
add_HorizontalDimension(ScriptEnv* context)
{
    //TODO: parameter error checking
    debug_message("TODO: finish addHorizontalDimension command");
    return script_null;
}

ScriptValue
add_VerticalDimension(ScriptEnv* context)
{
    //TODO: parameter error checking
    debug_message("TODO: finish addVerticalDimension command");
    return script_null;
}

ScriptValue
add_Image(ScriptEnv* context)
{
    //TODO: parameter error checking
    debug_message("TODO: finish addImage command");
    return script_null;
}

ScriptValue
add_DimLeader(ScriptEnv* context)
{
    if (!argument_checks(context, "calculateAngle", "rrrrr")) {
        return script_false;
    }

    _main->nativeAddDimLeader(REAL(0), REAL(1), REAL(2), REAL(3), REAL(4), OBJ_RUBBER_OFF);
    return script_null;
}

ScriptValue
javaSetCursorShape(ScriptEnv* context)
{
    if (!argument_checks(context, "calculateAngle", "s")) {
        return script_false;
    }

    _main->nativeSetCursorShape(QSTR(0));
    return script_null;
}

ScriptValue
javaCalculateAngle(ScriptEnv* context)
{
    if (!argument_checks(context, "calculateAngle", "rrrr")) {
        return script_false;
    }

    qreal r = _main->nativeCalculateAngle(REAL(0), REAL(1), REAL(2), REAL(3));
    return script_real(r);
}

ScriptValue
javaCalculateDistance(ScriptEnv* context)
{
    if (!argument_checks(context, "numSelected", "rrrr")) {
        return script_false;
    }

    qreal r = _main->nativeCalculateDistance(REAL(0), REAL(1), REAL(2), REAL(3));
    return script_real(r);
}

ScriptValue
javaPerpendicularDistance(ScriptEnv* context)
{
    if (!argument_checks(context, "numSelected", "rrrrrr")) {
        return script_false;
    }

    qreal r = _main->nativePerpendicularDistance(REAL(0), REAL(1), REAL(2), REAL(3), REAL(4), REAL(5));
    return script_real(r);
}

ScriptValue
javaNumSelected(ScriptEnv* context)
{
    if (!argument_checks(context, "numSelected", "")) {
        return script_false;
    }

    return script_int(_main->nativeNumSelected());
}

ScriptValue
javaSelectAll(ScriptEnv* context)
{
    if (!argument_checks(context, "selectAll", "")) {
        return script_false;
    }

    _main->nativeSelectAll();
    return script_null;
}

/* TODO: finish
 */
ScriptValue
add_ToSelection(ScriptEnv* context)
{
    return script_null;
}

ScriptValue
javaDeleteSelected(ScriptEnv* context)
{
    if (!argument_checks(context, "deleteSelected", "")) {
        return script_false;
    }

    _main->nativeDeleteSelected();
    return script_null;
}

ScriptValue
javaCutSelected(ScriptEnv* context)
{
    if (!argument_checks(context, "scaleSelected", "rr")) {
        return script_false;
    }

    _main->nativeCutSelected(REAL(0), REAL(1));
    return script_null;
}

ScriptValue
javaCopySelected(ScriptEnv* context)
{
    if (!argument_checks(context, "scaleSelected", "rr")) {
        return script_false;
    }

    _main->nativeCopySelected(REAL(0), REAL(1));
    return script_null;
}

ScriptValue
javaPasteSelected(ScriptEnv* context)
{
    if (!argument_checks(context, "scaleSelected", "rr")) {
        return script_false;
    }

    _main->nativePasteSelected(REAL(0), REAL(1));
    return script_null;
}

ScriptValue
javaMoveSelected(ScriptEnv* context)
{
    if (!argument_checks(context, "scaleSelected", "rr")) {
        return script_false;
    }

    _main->nativeMoveSelected(REAL(0), REAL(1));
    return script_null;
}

ScriptValue
scale_selected_command(ScriptEnv* context)
{
    if (!argument_checks(context, "scaleSelected", "rrr")) {
        return script_false;
    }

    if (REAL(2) <= 0.0) {
        debug_message("UNKNOWN_ERROR scaleSelected(): scale factor must be greater than zero");
        return script_false;
    }

    _main->nativeScaleSelected(REAL(0), REAL(1), REAL(2));
    return script_null;
}

ScriptValue
rotate_selected_command(ScriptEnv* context)
{
    if (!argument_checks(context, "rotate_selected_command", "rrr")) {
        return script_false;
    }

    _main->nativeRotateSelected(REAL(0), REAL(1), REAL(2));
    return script_null;
}
