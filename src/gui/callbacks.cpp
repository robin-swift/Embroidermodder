/*
 * Embroidermodder 2 -- Callbacks
 * Copyright 2011-2026 The Embroidermodder Team
 */

#include "mainwindow.h"
#include "commands.h"
#include "object-data.h"
#include "commands.h"

#define NAN_CHECK(function, nth, A) \
    if (qIsNaN(A)) { \
        throwError(QJSValue::TypeError, function "(): " nth " argument failed isNaN check. There is an error in your code."); \
        return 1; \
    }

QtScriptEnv script_env;

int call(State *state, const char *txt)
{
    return script_env.mainWin->call(txt);
}

void set_prompt_prefix(const char *txt)
{
    script_env.mainWin->prompt->setPrefix(txt);
}

void append_prompt_history(const char *txt)
{
    script_env.mainWin->appendPromptHistory(txt);
}

void new_file(void)
{
    script_env.mainWin->newFile();
}

void open_file(void)
{
    script_env.mainWin->openFile();
}

void exit_program(void)
{
    script_env.mainWin->exit();
}

void undo_action(void)
{
    script_env.mainWin->undo();
}

void redo_action(void)
{
    script_env.mainWin->redo();
}

/* FIXME */
void repeat_action(void)
{

}

void about_dialog(void)
{
    script_env.mainWin->about();    
}

void help_dialog(void)
{
    script_env.mainWin->help();
}

void tip_of_the_day_dialog(void)
{
    script_env.mainWin->tipOfTheDay();
}

void window_cascade(void)
{
    script_env.mainWin->mdiArea->cascade();
}

void window_close(void)
{
    script_env.mainWin->onCloseWindow();
}

void window_close_all(void)
{
    script_env.mainWin->mdiArea->closeAllSubWindows();
}

void window_next(void)
{
    script_env.mainWin->mdiArea->activateNextSubWindow();
}

void window_previous(void)
{
    script_env.mainWin->mdiArea->activatePreviousSubWindow();
}

void window_tile(void)
{
    script_env.mainWin->mdiArea->tile();
}

void select_all(void)
{
    script_env.mainWin->selectAll();
}

void delete_selected(void)
{
    script_env.mainWin->deleteSelected();
}

/*
 * This action intentionally does nothing: it is present as a dummy function
 * or the "null" action.
 */
int do_nothing_cmd(State *state)
{
    return 0;
}

int save_cmd(State *state)
{
    script_env.mainWin->savefile();
    return 0;
}

int save_as_cmd(State *state)
{
    script_env.mainWin->saveasfile();
    return 0;
}

int print_cmd(State *state)
{
    script_env.mainWin->print();
    return 0;
}

int design_details_cmd(State *state)
{
    script_env.mainWin->designDetails();
    return 0;
}

int cut_cmd(State *state)
{
    script_env.mainWin->cut();
    return 0;
}

int copy_cmd(State *state)
{
    script_env.mainWin->copy();
    return 0;
}

int paste_cmd(State *state)
{
    script_env.mainWin->paste();
    return 0;
}

int changelog_cmd(State *state)
{
    script_env.mainWin->changelog();
    return 0;
}

int whats_this_cmd(State *state)
{
    script_env.mainWin->whatsThis();
    return 0;
}

int settingsdialog_cmd(State *state)
{
    script_env.mainWin->settingsDialog();
    return 0;
}

int makelayercurrent_cmd(State *state)
{
    script_env.mainWin->makeLayerActive();
    return 0;
}

int layers_cmd(State *state)
{
    script_env.mainWin->layerManager();
    return 0;
}

/* FIXME */
int layerselector_cmd(State *state)
{
    return 0;
}

int layerprevious_cmd(State *state)
{
    script_env.mainWin->layerPrevious();
    return 0;
}

/* FIXME */
int colorselector_cmd(State *state)
{
    return 0;
}

/* FIXME */
int linetypeselector_cmd(State *state)
{
    return 0;
}

/* FIXME */
int lineweightselector_cmd(State *state)
{
    return 0;
}

/* FIXME */
int hidealllayers_cmd(State *state)
{
    return 0;
}

/* FIXME */
int showalllayers_cmd(State *state)
{
    return 0;
}

/* FIXME */
int freezealllayers_cmd(State *state)
{
    return 0;
}

/* FIXME */
int thawalllayers_cmd(State *state)
{
    return 0;
}

/* FIXME */
int lockalllayers_cmd(State *state)
{
    return 0;
}

/* FIXME */
int unlockalllayers_cmd(State *state)
{
    return 0;
}

int text_bold_cmd(State *state)
{
    script_env.mainWin->textBold();
    return 0;
}

int text_italic_cmd(State *state)
{
    script_env.mainWin->textItalic();
    return 0;
}

int text_underline_cmd(State *state)
{
    script_env.mainWin->textUnderline();
    return 0;
}

int text_strikeout_cmd(State *state)
{
    script_env.mainWin->textStrikeOut();
    return 0;
}

int text_overline_cmd(State *state)
{
    script_env.mainWin->textOverline();
    return 0;
}

int zoom_real_time_cmd(State *state)
{
    zoom_real_time();
    return 0;
}

int zoom_previous_cmd(State *state)
{
    zoom_previous();
    return 0;
}

int zoom_window_cmd(State *state)
{
    zoom_window();
    return 0;
}

int zoom_dynamic_cmd(State *state)
{
    zoom_dynamic();
    return 0;
}

int zoom_scale_cmd(State *state)
{
    zoom_scale();
    return 0;
}

int zoom_center_cmd(State *state)
{
    zoom_center();
    return 0;
}

int zoom_selected_cmd(State *state)
{
    zoom_selected();
    return 0;
}

int zoom_all_cmd(State *state)
{
    zoom_all();
    return 0;
}

#if 0
void
JavaScriptEnv::throwError(const char *message)
{
    script_env.mainwin->engine.throwError(QJSValue::GenericError, message);
}

void
JavaScriptEnv::throwError(QJSValue::ErrorType type, const char *message)
{
    script_env.mainwin->engine.throwError(type, message);
}

void
JavaScriptEnv::debug(QString message)
{
    qDebug("%s", qPrintable(message));
}

void
JavaScriptEnv::error(QString cmd, QString err)
{
    script_env.mainwin->setPromptPrefix("ERROR: (" + cmd + ") " + err);
    script_env.mainwin->appendPromptHistory(QString());
    end_command();
}

void
JavaScriptEnv::todo(QString cmd, QString msg)
{
    script_env.mainwin->alert("TODO: (" + cmd + ") " + msg);
    // Why was this here?
    end_command();
}

void
JavaScriptEnv::messageBox(QString type, QString title, QString text)
{
    type  = type.toLower();

    if (type != "critical" && type != "information" && type != "question" && type != "warning") {
        throwError(QJSValue::GenericError, "messageBox(): first argument must be \"critical\", \"information\", \"question\" or \"warning\".");
        return;
    }

    script_env.mainwin->messageBox(type, title, text);
}

bool
JavaScriptEnv::isInt(float num)
{
    NAN_CHECK("isInt", "fisrst", num)

    return fmod(num, 1) == 0;
}

int printArea(float x, float y, float w, float h)
{
    NAN_CHECK("printArea", "first", x)
    NAN_CHECK("printArea", "second", y)
    NAN_CHECK("printArea", "third", w)
    NAN_CHECK("printArea", "fourth", h)

    script_env.mainwin->printArea(x, y, w, h);
    return 0;
}

int setBackgroundColor(float r, float g, float b)
{
    NAN_CHECK("setBackgroundColor", "first", r)
    NAN_CHECK("setBackgroundColor", "second", g)
    NAN_CHECK("setBackgroundColor", "third", b)

    if (r < 0 || r > 255) {
        throwError(QJSValue::GenericError, "setBackgroundColor(): r value must be in range 0-255");
        return 1;
    }
    if (g < 0 || g > 255) {
        throwError(QJSValue::GenericError, "setBackgroundColor(): g value must be in range 0-255");
        return 1;
    }
    if (b < 0 || b > 255) {
        throwError(QJSValue::GenericError, "setBackgroundColor(): b value must be in range 0-255");
        return 1;
    }

    script_env.mainwin->setBackgroundColor(r, g, b);
    return 0;
}

int setCrossHairColor(float r, float g, float b)
{
    NAN_CHECK("setCrossHairColor", "first", r)
    NAN_CHECK("setCrossHairColor", "second", g)
    NAN_CHECK("setCrossHairColor", "third", b)

    if (r < 0 || r > 255) {
        throwError(QJSValue::GenericError, "setCrossHairColor(): r value must be in range 0-255");
        return 1;
    }
    if (g < 0 || g > 255) {
        throwError(QJSValue::GenericError, "setCrossHairColor(): g value must be in range 0-255");
        return 1;
    }
    if (b < 0 || b > 255) {
        throwError(QJSValue::GenericError, "setCrossHairColor(): b value must be in range 0-255");
        return 1;
    }

    script_env.mainwin->setCrossHairColor(r, g, b);
    return 0;
}

int setGridColor(float r, float g, float b)
{
    NAN_CHECK("setGridColor", "first", r)
    NAN_CHECK("setGridColor", "second", g)
    NAN_CHECK("setGridColor", "third", b)

    if (r < 0 || r > 255) {
        throwError(QJSValue::GenericError, "setGridColor(): r value must be in range 0-255");
        return 1;
    }
    if (g < 0 || g > 255) {
        throwError(QJSValue::GenericError, "setGridColor(): g value must be in range 0-255");
        return 1;
    }
    if (b < 0 || b > 255) {
        throwError(QJSValue::GenericError, "setGridColor(): b value must be in range 0-255");
        return 1;
    }

    script_env.mainwin->setGridColor(r, g, b);
    return 0;
}

int setTextSize(float num)
{
    NAN_CHECK("setTextSize", "first", num)

    script_env.mainwin->setTextSize(num);
    return 0;
}

int setTextAngle(float num)
{
    NAN_CHECK("setTextAngle", "first", num)

    script_env.mainwin->setTextAngle(num);
    return 0;
}

int previewOn(QString cloneStr, QString modeStr, float x, float y, float data)
{
    cloneStr = cloneStr.toUpper();
    modeStr = modeStr.toUpper();

    int clone = PREVIEW_CLONE_NULL;
    int mode = PREVIEW_MODE_NULL;
    if (cloneStr == "SELECTED") {
        clone = PREVIEW_CLONE_SELECTED;
    }
    else if (cloneStr == "RUBBER") {
        clone = PREVIEW_CLONE_RUBBER;
    }
    else {
        throwError(QJSValue::GenericError, "previewOn(): first argument must be \"SELECTED\" or \"RUBBER\".");
        return 1;
    }

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
        throwError(QJSValue::GenericError, "previewOn(): second argument must be \"MOVE\", \"ROTATE\" or \"SCALE\".");
        return 1;
    }

    NAN_CHECK("previewOn", "third", x)
    NAN_CHECK("previewOn", "fourth", y)
    NAN_CHECK("previewOn", "fifth", data)

    script_env.mainwin->previewOn(clone, mode, x, y, data);
    return 0;
}

int setRubberMode(QString mode)
{
    mode = mode.toUpper();

    if (mode == "CIRCLE_1P_RAD") {
        script_env.mainwin->setRubberMode(OBJ_RUBBER_CIRCLE_1P_RAD);
    }
    else if (mode == "CIRCLE_1P_DIA")                     { script_env.mainwin->setRubberMode(OBJ_RUBBER_CIRCLE_1P_DIA); }
    else if (mode == "CIRCLE_2P")                         { script_env.mainwin->setRubberMode(OBJ_RUBBER_CIRCLE_2P); }
    else if (mode == "CIRCLE_3P")                         { script_env.mainwin->setRubberMode(OBJ_RUBBER_CIRCLE_3P); }
    else if (mode == "CIRCLE_TTR")                        { script_env.mainwin->setRubberMode(OBJ_RUBBER_CIRCLE_TTR); }
    else if (mode == "CIRCLE_TTR")                        { script_env.mainwin->setRubberMode(OBJ_RUBBER_CIRCLE_TTT); }

    else if (mode == "DIMLEADER_LINE")                    { script_env.mainwin->setRubberMode(OBJ_RUBBER_DIMLEADER_LINE); }

    else if (mode == "ELLIPSE_LINE")                      { script_env.mainwin->setRubberMode(OBJ_RUBBER_ELLIPSE_LINE); }
    else if (mode == "ELLIPSE_MAJORDIAMETER_MINORRADIUS") { script_env.mainwin->setRubberMode(OBJ_RUBBER_ELLIPSE_MAJORDIAMETER_MINORRADIUS); }
    else if (mode == "ELLIPSE_MAJORRADIUS_MINORRADIUS")   { script_env.mainwin->setRubberMode(OBJ_RUBBER_ELLIPSE_MAJORRADIUS_MINORRADIUS); }
    else if (mode == "ELLIPSE_ROTATION")                  { script_env.mainwin->setRubberMode(OBJ_RUBBER_ELLIPSE_ROTATION); }

    else if (mode == "LINE")                              { script_env.mainwin->setRubberMode(OBJ_RUBBER_LINE); }

    else if (mode == "POLYGON")                           { script_env.mainwin->setRubberMode(OBJ_RUBBER_POLYGON); }
    else if (mode == "POLYGON_INSCRIBE")                  { script_env.mainwin->setRubberMode(OBJ_RUBBER_POLYGON_INSCRIBE); }
    else if (mode == "POLYGON_CIRCUMSCRIBE")              { script_env.mainwin->setRubberMode(OBJ_RUBBER_POLYGON_CIRCUMSCRIBE); }

    else if (mode == "POLYLINE")                          { script_env.mainwin->setRubberMode(OBJ_RUBBER_POLYLINE); }

    else if (mode == "RECTANGLE")                         { script_env.mainwin->setRubberMode(OBJ_RUBBER_RECTANGLE); }

    else if (mode == "TEXTSINGLE")                        { script_env.mainwin->setRubberMode(OBJ_RUBBER_TEXTSINGLE); }

    else {
        throwError(QJSValue::GenericError, "setRubberMode(): unknown rubberMode value");
        return 1;
    }

    return 0;
}

int setRubberPoint(QString key, float x, float y)
{
    key = key.toUpper();
    NAN_CHECK("setRubberPoint", "second", x)
    NAN_CHECK("setRubberPoint", "third", y)

    script_env.mainwin->setRubberPoint(key, x, y);
    return 0;
}

int setRubberText(QString key, QString txt)
{
    key = key.toUpper();

    script_env.mainwin->setRubberText(key, txt);
    return 0;
}

int addRubber(QString objType)
{
    objType = objType.toUpper();

    if (!mainwin->allowRubber()) {
        throwError(QJSValue::GenericError, "addRubber(): You must use vulcanize() before you can add another rubber object.");
        return 1;
    }

    float mx = script_env.mainwin->mouseX();
    float my = script_env.mainwin->mouseY();

    if     (objType == "ARC")          {} //TODO: handle this type
    else if (objType == "BLOCK")        {} //TODO: handle this type
    else if (objType == "CIRCLE")       { script_env.mainwin->addCircle(mx, my, 0, false, OBJ_RUBBER_ON); }
    else if (objType == "DIMALIGNED")   {} //TODO: handle this type
    else if (objType == "DIMANGULAR")   {} //TODO: handle this type
    else if (objType == "DIMARCLENGTH") {} //TODO: handle this type
    else if (objType == "DIMDIAMETER")  {} //TODO: handle this type
    else if (objType == "DIMLEADER")    { script_env.mainwin->addDimLeader(mx, my, mx, my, 0, OBJ_RUBBER_ON); }
    else if (objType == "DIMLINEAR")    {} //TODO: handle this type
    else if (objType == "DIMORDINATE")  {} //TODO: handle this type
    else if (objType == "DIMRADIUS")    {} //TODO: handle this type
    else if (objType == "ELLIPSE")      { script_env.mainwin->addEllipse(mx, my, 0, 0, 0, 0, OBJ_RUBBER_ON); }
    else if (objType == "ELLIPSEARC")   {} //TODO: handle this type
    else if (objType == "HATCH")        {} //TODO: handle this type
    else if (objType == "IMAGE")        {} //TODO: handle this type
    else if (objType == "INFINITELINE") {} //TODO: handle this type
    else if (objType == "LINE")         { script_env.mainwin->addLine(mx, my, mx, my, 0, OBJ_RUBBER_ON); }
    else if (objType == "PATH")         {} //TODO: handle this type
    else if (objType == "POINT")        {} //TODO: handle this type
    else if (objType == "POLYGON")      { script_env.mainwin->addPolygon(mx, my, QPainterPath(), OBJ_RUBBER_ON); }
    else if (objType == "POLYLINE")     { script_env.mainwin->addPolyline(mx, my, QPainterPath(), OBJ_RUBBER_ON); }
    else if (objType == "RAY")          {} //TODO: handle this type
    else if (objType == "RECTANGLE")    { script_env.mainwin->addRectangle(mx, my, mx, my, 0, 0, OBJ_RUBBER_ON); }
    else if (objType == "SPLINE")       {} //TODO: handle this type
    else if (objType == "TEXTMULTI")    {} //TODO: handle this type
    else if (objType == "TEXTSINGLE")   { script_env.mainwin->addTextSingle("", mx, my, 0, false, OBJ_RUBBER_ON); }

    return 0;
}

int spareRubber(QString objID)
{
    objID = objID.toUpper();

    if (objID == "PATH")     { script_env.mainwin->spareRubber(SPARE_RUBBER_PATH);     }
    else if (objID == "POLYGON")  { script_env.mainwin->spareRubber(SPARE_RUBBER_POLYGON);  }
    else if (objID == "POLYLINE") { script_env.mainwin->spareRubber(SPARE_RUBBER_POLYLINE); }
    else {
        bool ok = false;
        qint64 id = objID.toLongLong(&ok);
        if (!ok) {
            throwError(QJSValue::TypeError, "spareRubber(): error converting object ID into an int64");
            return 1;
        }
        script_env.mainwin->spareRubber(id);
    }

    return 0;
}

int addTextMulti(QString str, float x, float y, float rot, bool fill)
{
    NAN_CHECK("addTextMulti", "second", x)
    NAN_CHECK("addTextMulti", "third", y)
    NAN_CHECK("addTextMulti", "fourth", rot)

    script_env.mainwin->addTextMulti(str, x, y, rot, fill, OBJ_RUBBER_OFF);
    return 0;
}

int addTextSingle(QString str, float x, float y, float rot, bool fill)
{
    NAN_CHECK("addTextSingle", "second", x)
    NAN_CHECK("addTextSingle", "third", y)
    NAN_CHECK("addTextSingle", "fourth", rot)

    script_env.mainwin->addTextSingle(str, x, y, rot, fill, OBJ_RUBBER_OFF);
    return 0;
}

int addInfiniteLine(void)
{
    //TODO: parameter error checking
    qDebug("TODO: finish addInfiniteLine command");
    return 0;
}

int addRay(void)
{
    //TODO: parameter error checking
    qDebug("TODO: finish addRay command");
    return 0;
}

int addLine(float x1, float y1, float x2, float y2, float rot)
{
    NAN_CHECK("addLine", "first", x1)
    NAN_CHECK("addLine", "second", y1)
    NAN_CHECK("addLine", "third", x2)
    NAN_CHECK("addLine", "fourth", y2)
    NAN_CHECK("addLine", "fifth", rot)

    script_env.mainwin->addLine(x1, y1, x2, y2, rot, OBJ_RUBBER_OFF);
    return 0;
}

int addTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float rot, bool fill)
{
    NAN_CHECK("addTriangle", "first", x1)
    NAN_CHECK("addTriangle", "second", y1)
    NAN_CHECK("addTriangle", "third", x2)
    NAN_CHECK("addTriangle", "fourth", y2)
    NAN_CHECK("addTriangle", "fifth", x3)
    NAN_CHECK("addTriangle", "sixth", y3)
    NAN_CHECK("addTriangle", "seventh", rot)

    script_env.mainwin->addTriangle(x1, y1, x2, y2, x3, y3, rot, fill);
    return 0;
}

int addRectangle(float x, float y, float w, float h, float rot, bool fill)
{
    NAN_CHECK("addRectangle", "first", x)
    NAN_CHECK("addRectangle", "second", y)
    NAN_CHECK("addRectangle", "third", w)
    NAN_CHECK("addRectangle", "fourth", h)
    NAN_CHECK("addRectangle", "fifth", rot)

    script_env.mainwin->addRectangle(x, y, w, h, rot, fill, OBJ_RUBBER_OFF);
    return 0;
}

int addRoundedRectangle(float x, float y, float w, float h, float rad, float rot, bool fill)
{
    NAN_CHECK("addRoundedRectangle", "first", x)
    NAN_CHECK("addRoundedRectangle", "second", y)
    NAN_CHECK("addRoundedRectangle", "third", w)
    NAN_CHECK("addRoundedRectangle", "fourth", h)
    NAN_CHECK("addRoundedRectangle", "fifth", rad)
    NAN_CHECK("addRoundedRectangle", "sixth", rot)

    script_env.mainwin->addRoundedRectangle(x, y, w, h, rad, rot, fill);
    return 0;
}

int addArc(float startX, float startY, float midX, float midY, float endX, float endY)
{
    NAN_CHECK("addArc", "first", startX)
    NAN_CHECK("addArc", "second", startY)
    NAN_CHECK("addArc", "third", midX)
    NAN_CHECK("addArc", "fourth", midY)
    NAN_CHECK("addArc", "fifth", endX)
    NAN_CHECK("addArc", "sixth", endY)

    script_env.mainwin->addArc(startX, startY, midX, midY, endX, endY, OBJ_RUBBER_OFF);
    return 0;
}

int addCircle(float centerX, float centerY, float radius, bool fill)
{
    NAN_CHECK("addCircle", "first", centerX)
    NAN_CHECK("addCircle", "second", centerY)
    NAN_CHECK("addCircle", "third", radius)

    script_env.mainwin->addCircle(centerX, centerY, radius, fill, OBJ_RUBBER_OFF);
    return 0;
}

int addSlot(float centerX, float centerY, float diameter, float length, float rot, bool fill)
{
    NAN_CHECK("addSlot", "first", centerX)
    NAN_CHECK("addSlot", "second", centerY)
    NAN_CHECK("addSlot", "third", diameter)
    NAN_CHECK("addSlot", "fourth", length)
    NAN_CHECK("addSlot", "fifth", rot)

    script_env.mainwin->addSlot(centerX, centerY, diameter, length, rot, fill, OBJ_RUBBER_OFF);
    return 0;
}

int addEllipse(float centerX, float centerY, float radX, float radY, float rot, bool fill)
{
    NAN_CHECK("addSlot", "first", centerX)
    NAN_CHECK("addSlot", "second", centerY)
    NAN_CHECK("addSlot", "third", radX)
    NAN_CHECK("addSlot", "fourth", radY)
    NAN_CHECK("addSlot", "fifth", rot)

    script_env.mainwin->addEllipse(centerX, centerY, radX, radY, rot, fill, OBJ_RUBBER_OFF);
    return 0;
}

int addPoint(float x, float y)
{
    NAN_CHECK("addPoint", "first", x)
    NAN_CHECK("addPoint", "second", y)

    script_env.mainwin->addPoint(x,y);
    return 0;
}

int addRegularPolygon(QJSValueList args)
{
    //TODO: parameter error checking
    qDebug("TODO: finish addRegularPolygon command");
    return 0;
}

int addPolygon(QJSValueList args)
{
    if (args.count() != 1) {
        throwError("addPolygon() requires one argument");
        return 1;
    }
    if (!args.at(0).isArray()) {
        throwError(QJSValue::TypeError, "addPolygon(): first argument is not an array");
        return 1;
    }

    QVariantList varList = args.at(0).toVariant().toList();
    int varSize = varList.size();
    if (varSize < 2) {
        throwError(QJSValue::TypeError, "addPolygon(): array must contain at least two elements");
        return 1;
    }
    if (varSize % 2) {
        throwError(QJSValue::TypeError, "addPolygon(): array cannot contain an odd number of elements");
        return 1;
    }

    bool lineTo = false;
    bool xCoord = true;
    float x = 0;
    float y = 0;
    float startX = 0;
    float startY = 0;
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
            throwError(QJSValue::TypeError, "addPolygon(): array contains one or more invalid elements");
            return 1;
        }
    }

    //Close the polygon
    path.closeSubpath();

    path.translate(-startX, -startY);

    script_env.mainwin->addPolygon(startX, startY, path, OBJ_RUBBER_OFF);
    return 0;
}

int addPolyline(QJSValueList args)
{
    if (args.count() != 1) {
        throwError("addPolyline() requires one argument");
        return 1;
    }
    if (!args.at(0).isArray()) {
        throwError(QJSValue::TypeError, "addPolyline(): first argument is not an array");
        return 1;
    }

    QVariantList varList = args.at(0).toVariant().toList();
    int varSize = varList.size();
    if (varSize < 2) {
        throwError(QJSValue::TypeError, "addPolyline(): array must contain at least two elements");
        return 1;
    }
    if (varSize % 2) {
        throwError(QJSValue::TypeError, "addPolyline(): array cannot contain an odd number of elements");
        return 1;
    }

    bool lineTo = false;
    bool xCoord = true;
    float x = 0;
    float y = 0;
    float startX = 0;
    float startY = 0;
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
            throwError(QJSValue::TypeError, "addPolyline(): array contains one or more invalid elements");
            return 1;
        }
    }

    path.translate(-startX, -startY);

    script_env.mainwin->addPolyline(startX, startY, path, OBJ_RUBBER_OFF);
    return 0;
}

int addPath(void)
{
    //TODO: parameter error checking
    qDebug("TODO: finish addPath command");
    return 0;
}

int addHorizontalDimension(void)
{
    //TODO: parameter error checking
    qDebug("TODO: finish addHorizontalDimension command");
    return 0;
}

int addVerticalDimension(void)
{
    //TODO: parameter error checking
    qDebug("TODO: finish addVerticalDimension command");
    return 0;
}

int addImage(void)
{
    //TODO: parameter error checking
    qDebug("TODO: finish addImage command");
    return 0;
}

int addDimLeader(float x1, float y1, float x2, float y2, float rot)
{
    NAN_CHECK("addDimLeader", "first", x1)
    NAN_CHECK("addDimLeader", "second", y1)
    NAN_CHECK("addDimLeader", "third", x2)
    NAN_CHECK("addDimLeader", "fourth", y2)
    NAN_CHECK("addDimLeader", "fifth", rot)

    script_env.mainwin->addDimLeader(x1, y1, x2, y2, rot, OBJ_RUBBER_OFF);
    return 0;
}

qreal
JavaScriptEnv::calculateAngle(float x1, float y1, float x2, float y2)
{
    NAN_CHECK("calculateAngle", "first", x1)
    NAN_CHECK("calculateAngle", "second", y1)
    NAN_CHECK("calculateAngle", "third", x2)
    NAN_CHECK("calculateAngle", "fourth", y2)

    return script_env.mainwin->calculateAngle(x1, y1, x2, y2);
}

qreal
JavaScriptEnv::calculateDistance(float x1, float y1, float x2, float y2)
{
    NAN_CHECK("calculateDistance", "first", x1)
    NAN_CHECK("calculateDistance", "second", y1)
    NAN_CHECK("calculateDistance", "third", x2)
    NAN_CHECK("calculateDistance", "fourth", y2)

    return script_env.mainwin->calculateDistance(x1, y1, x2, y2);
}

qreal
JavaScriptEnv::perpendicularDistance(float px, float py, float x1, float y1, float x2, float y2)
{
    NAN_CHECK("perpendicularDistance", "first", px)
    NAN_CHECK("perpendicularDistance", "second", py)
    NAN_CHECK("perpendicularDistance", "third", x1)
    NAN_CHECK("perpendicularDistance", "fourth", y1)
    NAN_CHECK("perpendicularDistance", "fifth", x2)
    NAN_CHECK("perpendicularDistance", "sixth", y2)

    return script_env.mainwin->perpendicularDistance(px, py, x1, y1, x2, y2);
}

int addToSelection(void)
{
    //TODO: finish
    return 0;
}

int cutSelected(float x, float y)
{
    NAN_CHECK("cutSelected", "first", x)
    NAN_CHECK("cutSelected", "second", y)

    script_env.mainwin->cutSelected(x, y);
    return 0;
}

int copySelected(float x, float y)
{
    NAN_CHECK("copySelected", "first", x)
    NAN_CHECK("copySelected", "second", y)

    script_env.mainwin->copySelected(x, y);
    return 0;
}

int pasteSelected(float x, float y)
{
    NAN_CHECK("pasteSelected", "first", x)
    NAN_CHECK("pasteSelected", "second", y)

    script_env.mainwin->pasteSelected(x, y);
    return 0;
}

int moveSelected(float dx, float dy)
{
    NAN_CHECK("moveSelected", "first", dx)
    NAN_CHECK("moveSelected", "second", dy)

    script_env.mainwin->moveSelected(dx, dy);
    return 0;
}

int scaleSelected( float x,  float y,  float factor)
{
    NAN_CHECK("mirrorSelected", "first", x)
    NAN_CHECK("mirrorSelected", "second", y)
    NAN_CHECK("mirrorSelected", "third", factor)

    if (factor <= 0.0) {
        throwError(QJSValue::GenericError, "scaleSelected(): scale factor must be greater than zero");
        return 1;
    }

    script_env.mainwin->scaleSelected(x, y, factor);
    return 0;
}

int rotateSelected(float x, float y, float rot)
{
    NAN_CHECK("mirrorSelected", "first", x)
    NAN_CHECK("mirrorSelected", "second", y)
    NAN_CHECK("mirrorSelected", "third", rot)

    script_env.mainwin->rotateSelected(x, y, rot);
    return 0;
}

int mirrorSelected(float x1, float y1, float x2, float y2)
{
    NAN_CHECK("mirrorSelected", "first", x1)
    NAN_CHECK("mirrorSelected", "second", y1)
    NAN_CHECK("mirrorSelected", "third", x2)
    NAN_CHECK("mirrorSelected", "fourth", y2)

    script_env.mainwin->mirrorSelected(x1, y1, x2, y2);
    return 0;
}
#endif

