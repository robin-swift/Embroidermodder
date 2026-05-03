/*
 * Embroidermodder 2 -- State Management
 * Copyright 2011-2026 The Embroidermodder Team
 */

#include <string.h>

#include "core.h"

void
state_create(char *settings_dir, char *app_dir)
{
    strcpy(state.settings_dir, settings_dir);
    sprintf(state.settings_path, "%ssettings.ini", settings_dir);
    strcpy(state.app_dir, app_dir);

    state.shift = false;
    state.num_docs = 0;
    state.doc_index = 0;

    /* Command */
    state.command_active = false;
    state.rapid_fire = false;
    state.is_blinking = false;
    state.blink_state = false;
    strcpy(state.command_line, "");
    strcpy(state.prefix, "> ");
    strcpy(state.current_command, "donothing");
    strcpy(state.last_command, "donothing");
    strcpy(state.arguments[0], "^END^");
    state.context = CONTEXT_MAIN;

    /* Note that these are created after state.settings_dir so the defaults are corrent. */
    settings_create(&state.settings);
    settings_create(&state.accept);
    settings_create(&state.preview);
    settings_create(&state.dialog);
}

void
state_free(void)
{
}

