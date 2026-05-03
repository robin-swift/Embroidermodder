/*
 * Embroidermodder 2 -- Loaders for TOML Files
 * Copyright 2011-2026 The Embroidermodder Team
 */

#include <stdlib.h>
#include <string.h>

#include "core.h"

int
table_length(const char *table[])
{
    for (int i=0; i<100; i++) {
        if (table[i][0] == '^') {
            return i;
        }
    }
    printf("ERROR: table longer than 100 entries or terminator symbol missing, capping length at 100.");
    return 100;
}

int
command_id(const char *str)
{
    for (int i=0; command_table[i].id != ACTION_null; i++) {
        if (!strncmp(command_table[i].label, str, 100)) {
            return command_table[i].id;
        }
    }
    printf("ERROR: command \"%s\" not found.", str);
    return ACTION_null;
}

/* FIXME: need to deal with  */
char *
toml_readstr(toml_table_t *table, const char *key, const char *default_value, char *result)
{
    toml_datum_t str = toml_string_in(table, key);
    if (str.ok) {
        strcpy(result, str.u.s);
        free(str.u.s);
    }
    else {
        strcpy(result, default_value);
    }
    return result;
}

int32_t
toml_readint(toml_table_t *table, const char *key, int32_t default_value)
{
    toml_datum_t i = toml_int_in(table, key);
    if (i.ok) {
        return i.u.i;
    }
    return default_value;
}

float
toml_readreal(toml_table_t *table, const char *key, float default_value)
{
    toml_datum_t r = toml_double_in(table, key);
    if (r.ok) {
        return r.u.d;
    }
    return default_value;
}

bool
toml_readbool(toml_table_t *table, const char *key, bool default_value)
{
    toml_datum_t i = toml_int_in(table, key);
    if (i.ok) {
        return i.u.i;
    }
    return default_value;
}

