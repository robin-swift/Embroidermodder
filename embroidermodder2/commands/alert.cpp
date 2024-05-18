/*
 * Embroidermodder 2.
 *
 * Copyright 2013-2024 The Embroidermodder Team
 * Embroidermodder 2 is Open Source Software.
 * See LICENSE for licensing terms.
 *
 * Command: about
 */

#include "../commands.h"

/* ACTION_ALERT is a prompt-only command. */
ScriptValue
alert_generic(ScriptEnv *context)
{
    if (!argument_checks(context, "alert", "s")) {
        return script_false;
    }

    _main->nativeInitCommand();
    _main->nativeAlert(QSTR(0));
    _main->nativeEndCommand();
    return script_null;
}

Command alert_cmd = {
    .id = ACTION_ALERT,
    .main = do_nothing,
    .click = do_nothing,
    .context = do_nothing,
    .prompt = alert_generic,
    .icon = "warning",
    .menu_name = "None",
    .menu_position = 0,
    .toolbar_name = "None",
    .toolbar_position = 0,
    .tooltip = "&Alert",
    .statustip = "Creates a dialog to alert the user.",
    .alias = "ALERT"
};
