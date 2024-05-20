/*
 * Embroidermodder 2.
 *
 * Copyright 2013-2024 The Embroidermodder Team
 * Embroidermodder 2 is Open Source Software, see LICENSE for licensing terms.
 * Read CODE-STANDARDS.txt for advice on altering this file.
 *
 * Command: SELECTALL
 */

#include "../commands.h"

/* NOTE: main() is run every time the command is started.
 *       Use it to reset variables so they are ready to go.
 */
ScriptValue
selectall_command(ScriptEnv * context)
{
    return script_null;
}


#if 0
//Command: SelectAll

//NOTE: main() is run every time the command is started.
//      Use it to reset variables so they are ready to go.
function main()
{
    initCommand();
    selectAll();
    endCommand();
}

//NOTE: click() is run only for left clicks.
//      Middle clicks are used for panning.
//      Right clicks bring up the context menu.
function click(x, y)
{
    selectAll();
    endCommand();
}

//NOTE: context() is run when a context menu entry is chosen.
function context(str)
{
    selectAll();
    endCommand();
}

//NOTE: prompt() is run when Enter is pressed.
//      appendPromptHistory is automatically called before prompt()
//      is called so calling it is only needed for erroneous input.
//      Any text is in the command prompt is sent as an uppercase string.
function prompt(str)
{
    selectAll();
    endCommand();
}
[Menu]
Name=None
Position=0

[ToolBar]
Name=None
Position=0

[Tips]
ToolTip=&Select All
StatusTip=Selects all objects:  SELECTALL

[Prompt]
Alias=AI_SELALL, SELALL, SELECTALL
#endif
