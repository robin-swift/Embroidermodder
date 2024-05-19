/*
 * Embroidermodder 2.
 *
 * Copyright 2013-2024 The Embroidermodder Team
 * Embroidermodder 2 is Open Source Software.
 * See LICENSE for licensing terms.
 *
 * Command: HELP
 */

#include "../commands.h"

/* HELP is not context-dependent. */
ScriptValue
help_generic(ScriptEnv * /* context */)
{
    _main->nativeHelp();
    _main->nativeEndCommand();
    return script_null;
}

/* NOTE: main() is run every time the command is started.
 *       Use it to reset variables so they are ready to go.
 */
ScriptValue
help_main(ScriptEnv *context)
{
    _main->nativeInitCommand();
    _main->nativeClearSelection();
    return help_generic(context);
}