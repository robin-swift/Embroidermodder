/*
 * Embroidermodder 2.
 *
 * Copyright 2011-2024 The Embroidermodder Team
 * Embroidermodder 2 is Open Source Software, see LICENSE.md for licensing terms.
 *
 * Read the reference manual (https://www.libembroidery.org/downloads/emrm.pdf)
 * for advice on altering this file.
 *
 * Script
 *
 * Operating system-specific system calls like usleep go in this file:
 * see the block of system-specific headers below.
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <math.h>

/* Advice on safe C preprocessor directive use:
 * https://github.com/cpredef/predef
 */
#if defined(linux) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#elif defined(WINDOWS)
#include <windows.h>
#endif

#include "core.h"

char formatFilterOpen[MAX_LONG_STRING];
char formatFilterSave[MAX_LONG_STRING];
EmbString open_filesPath;
EmbString prompt_color_;
EmbString prompt_selection_bg_color_;
EmbString prompt_bg_color_;
EmbString prompt_selection_color_;

ScriptEnv *global;

bool document_memory[MAX_OPEN_FILES];

bool shiftKeyPressedState = false;
bool cmdActive;
bool rapidFireEnabled = false;
bool isBlinking = false;
int numOfDocs = 0;
int docIndex = 0;

EmbString end_symbol = "END";
EmbString settings_file = "settings.toml";
bool key_state[N_KEY_SEQUENCES] = {
    false, false, false, false, false,
    false, false, false, false, false,
    false, false, false, false, false,
    false, false, false, false, false,
    false, false, false, false
};
Setting setting[N_SETTINGS];
char recent_files[MAX_FILES][MAX_STRING_LENGTH] = {
    "END"
};

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

const ScriptValue script_null = {
    .r = 0.0F,
    .i = 0,
    .b = false,
    .s = "",
    .label = "NULL",
    .type = SCRIPT_NULL
};

const ScriptValue script_true = {
    .r = 0.0F,
    .i = 1,
    .b = true,
    .s = "",
    .label = "true",
    .type = SCRIPT_BOOL
};

const ScriptValue script_false = {
    .r = 0.0F,
    .i = 0,
    .b = false,
    .s = "",
    .label = "false",
    .type = SCRIPT_BOOL
};

EmbString _appName_ = "Embroidermodder";
EmbString _appVer_  = "v2.0 alpha";
bool exitApp = false;
int testing_mode = 0;

int chunk_size = 100;

/* EmbVectorList */
EmbVectorList *
create_vector_list(void)
{
    EmbVectorList *list;
    list = (EmbVectorList*)malloc(sizeof(EmbVectorList));
    list->data = (EmbVector*)malloc(chunk_size*sizeof(EmbVector));
    list->count = 0;
    list->size = chunk_size;
    return list;
}

/* Checks if there is room to append a vector to the list, if there isn't then
 * resize it, then append the vector.
 */
void
append_vector_to_list(EmbVectorList *list, EmbVector v)
{
    if (list->count >= list->size - 1) {
        list->size += chunk_size;
        list->data = (EmbVector*)realloc(list->data,
            (list->size)*sizeof(EmbVector));
    }
    list->data[list->count] = v;
    list->count++;
}

/* Test this */
void
remove_vector_from_list(EmbVectorList *list, int32_t position)
{
    if (list->size <= 0) {
        return;
    }
    memory_copy(list->data + position + 1, list->data + position,
        (list->size - position)*sizeof(EmbVector));
    list->size--;
}

/* . */
void
free_vector_list(EmbVectorList *v)
{
    free(v->data);
    free(v);
}

/* EmbIdList */
EmbIdList *
create_id_list(void)
{
    EmbIdList *list;
    list = (EmbIdList*)malloc(sizeof(EmbIdList));
    list->data = (int32_t*)malloc(chunk_size*sizeof(int32_t));
    list->count = 0;
    list->size = chunk_size;
    return list;
}

/* Checks if there is room to append an id to the list, if there isn't then
 * resize it, then append the id.
 */
void
append_id_to_list(EmbIdList *list, int32_t i)
{
    if (list->count >= list->size - 1) {
        list->size += chunk_size;
        list->data = (int32_t*)realloc(list->data,
            (list->size)*sizeof(EmbVector));
    }
    list->data[list->count] = i;
    list->count++;
}

bool
id_list_contains(EmbIdList *list, int32_t a)
{
    for (int i=0; i<list->count; i++) {
        if (list->data[i] == a) {
            return true;
        }
    }
    return false;
}

/* Test this. */
void
remove_id_from_list(EmbIdList *list, int32_t position)
{
    if (list->size <= 0) {
        return;
    }
    memory_copy(list->data + position + 1, list->data + position,
        (list->size - position)*sizeof(int32_t));
    list->size --;
}

/* . */
void
free_id_list(EmbIdList *list)
{
    free(list->data);
    free(list);
}

/* Find index of integer in IntMap.
 * IntMaps have terminator symbols.
 */
int
find_int_map(IntMap *map, int key)
{
    for (int i=0; map[i].value != -1; i++) {
        if (map[i].key == key) {
            return map[i].value;
        }
    }
    return -1;
}

/* Find index of string in StringMap. */
int
find_in_map(StringMap *hash, int length, const char *key)
{
    for (int i=0; i<length; i++) {
        if (string_equal(hash[i].key, key)) {
            return i;
        }
    }
    return -1;
}

/* . */
void
nanosleep_(int time)
{
#if defined(WINDOWS)
    if (time/1000000 == 0) {
        Sleep(1);
    }
    else {
        Sleep(time/1000000);
    }
#elif defined(unix) || defined(__unix__) || defined(__APPLE__)
    usleep(time/1000);
#endif
}

/* Print out version string and exit. */
void
version(void)
{
    fprintf(stdout, "%s %s\n", _appName_, _appVer_);
    exitApp = true;
}

/* . */
int
main(int argc, char* argv[])
{
    int n_files = 0;
    EmbStringTable files_to_open;
    for (int i = 1; i < argc; i++) {
        if (string_equal(argv[i], "-d") || string_equal(argv[i], "--debug")  ) {
            testing_mode = 1;
        }
        else if (string_equal(argv[i], "-h") || string_equal(argv[i], "--help")   ) {

    fprintf(stderr,
    " ___ _____ ___  ___   __  _ ___  ___ ___   _____  __  ___  ___  ___ ___    ___ "           "\n"
    "| __|     | _ \\| _ \\ /  \\| |   \\| __| _ \\ |     |/  \\|   \\|   \\| __| _ \\  |__ \\" "\n"
    "| __| | | | _ <|   /| () | | |) | __|   / | | | | () | |) | |) | __|   /  / __/"           "\n"
    "|___|_|_|_|___/|_|\\_\\\\__/|_|___/|___|_|\\_\\|_|_|_|\\__/|___/|___/|___|_|\\_\\ |___|"   "\n"
    " _____________________________________________________________________________ "           "\n"
    "|                                                                             | "          "\n"
    "|                   https://www.libembroidery.org                             | "          "\n"
    "|_____________________________________________________________________________| "          "\n"
    "                                                                               "           "\n"
    "Usage: embroidermodder [options] files ..."                                      "\n"
/*   80CHARS======================================================================MAX */
    "Options:"                                                                        "\n"
    "  -d, --debug      Print lots of debugging information."                         "\n"
    "  -h, --help       Print this message and exit."                                 "\n"
    "  -v, --version    Print the version number of embroidermodder and exit."        "\n"
    "\n"
           );
    exitApp = true;
    }
        else if (string_equal(argv[i], "-v") || string_equal(argv[i], "--version")) {
            version();
        }
        else if (1 /* FIXME: QFile::exists(argv[i]) && emb_valid_file_format(argv[i])*/) {
            if (n_files >= MAX_FILES) {
                printf("ERROR: More files to open than MAX_FILES.");
                continue;
            }
            string_copy(files_to_open[n_files], argv[i]);
            n_files++;
        }
        else {
            usage();
        }
    }

    if (exitApp) {
        return 1;
    }

    if (!init_glfw()) {
        puts("Failed to initialize.");
        return 2;
    }

    global = create_script_env();
    int result = make_application(n_files, files_to_open);

    free_script_env(global);

    return result;
}

/* . */
void
run_testing(void)
{
    int i;
    nanosleep_(2000);
    int n = string_array_length(state.coverage_test);
    for (i=0; i<n; i++) {
        run_command_main(state.coverage_test[i]);
        nanosleep_(1000);
    }        
}

/* . */
ScriptValue
test_command(ScriptEnv *context)
{
    return script_true;
}

/* TODO: remove args command, use the command_data table
 */
int
argument_checks(ScriptEnv *context, int id)
{
    char s[200];
    int i;
    const char *function = command_data[id].command;
    const char *args = command_data[id].arguments;
    if (context->argumentCount != string_length(args)) {
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

/* . */
void
set_int(int key, int value)
{
    if (settings_data[key].type != SCRIPT_INT) {
        printf("ERROR: failed to load key %d (%s) as an integer.\n", key,
            settings_data[key].key);
        return;
    }
    setting[key].setting.i = value;
}

/* . */
void
set_real(int key, EmbReal value)
{
    if (settings_data[key].type != SCRIPT_REAL) {
        printf("ERROR: failed to set key %d (%s) as a real number.\n", key,
            settings_data[key].key);
        return;
    }
    setting[key].setting.r = value;
}

/* . */
void
set_str(int key, const char *value)
{
    if (settings_data[key].type != SCRIPT_STRING) {
        printf("ERROR: failed to load key %d (%s) as a string.\n", key,
            settings_data[key].key);
        return;
    }
    string_copy(setting[key].setting.s, value);
}

/* . */
void
set_bool(int key, bool value)
{
    if (settings_data[key].type != SCRIPT_BOOL) {
        printf("ERROR: failed to set key %d (%s) as boolean.\n", key,
            settings_data[key].key);
        return;
    }
    setting[key].setting.b = value;
}

/* . */
int
get_int(int key)
{
    if (settings_data[key].type != SCRIPT_INT) {
        printf("ERROR: failed to load key %d (%s) as an integer.\n", key,
            settings_data[key].key);
        return 0;
    }
    return setting[key].setting.i;
}

/* . */
EmbReal
get_real(int key)
{
    if (settings_data[key].type != SCRIPT_REAL) {
        printf("ERROR: failed to get key %d (%s) as a real number.\n", key,
            settings_data[key].key);
        return 0.0;
    }
    return setting[key].setting.r;
}

/* . */
char *
get_str(int key)
{
    if (settings_data[key].type != SCRIPT_STRING) {
        printf("ERROR: failed to set key %d (%s) as a string.\n", key,
            settings_data[key].key);
        return "ERROR_STRLOAD";
    }
    return setting[key].setting.s;
}

/* . */
bool
get_bool(int key)
{
    if (settings_data[key].type != SCRIPT_BOOL) {
        printf("ERROR: failed to set key %d (%s) as a boolean.\n", key,
            settings_data[key].key);
        return false;
    }
    return setting[key].setting.b;
}

/* . */
char *
translate(const char *msg)
{
    return msg;
}

ScriptEnv *
create_script_env()
{
    ScriptEnv *context = (ScriptEnv*)malloc(sizeof(ScriptEnv));
    context->argumentCount = 0;
    return context;
}

/* . */
void
free_script_env(ScriptEnv* context)
{
    free(context);
}

/* . */
ScriptValue
script_bool(bool b)
{
    ScriptValue value;
    value.type = SCRIPT_BOOL;
    value.b = b;
    return value;
}

/* . */
ScriptValue
script_int(int i)
{
    ScriptValue value;
    value.type = SCRIPT_INT;
    value.i = i;
    return value;
}

/* . */
ScriptValue
script_real(EmbReal r)
{
    ScriptValue value;
    value.type = SCRIPT_REAL;
    value.r = r;
    return value;
}

/* . */
ScriptValue
script_string(EmbString s)
{
    ScriptValue value;
    value.type = SCRIPT_STRING;
    string_copy(value.s, s);
    return value;
}

/* These pack the arguments for function calls in the command environment. */
ScriptEnv *
add_string_argument(ScriptEnv *context, const char *s)
{
    string_copy(context->argument[context->argumentCount].s, s);
    context->argument[context->argumentCount].type = SCRIPT_STRING;
    context->argumentCount++;
    return context;
}

ScriptEnv *
add_real_argument(ScriptEnv *context, EmbReal r)
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

/* Using stdarg we can pack arguments into the context using the above functions.
 *
 * https://pubs.opengroup.org/onlinepubs/009695399/basedefs/stdarg.h.html
 */
ScriptEnv *
pack(ScriptEnv *context, const char *fmt, ...)
{
    va_list a;
    int argno;
    context->argumentCount = 0;
    va_start(a, fmt);
    for (argno = 0; fmt[argno]; argno++) {
        switch (fmt[argno]) {
        case 's':
            const char *s = va_arg(a, const char *);
            add_string_argument(context, s);
            break;
        case 'i':
            int i = va_arg(a, int);
            add_int_argument(context, i);
            break;
        case 'r':
            EmbReal r = va_arg(a, double);
            add_real_argument(context, r);
            break;
        default:
            break;
        }
    }
    va_end(a);
    return context;
}

/* . */
int
parse_floats(const char *line, float result[], int n)
{
    EmbString substring;
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
parse_vector(const char *line, EmbVector *v)
{
    float v_[2];
    if (parse_floats(line, v_, 2) == 2) {
        return 0;
    }
    v->x = v_[0];
    v->y = v_[1];
    return 1;
}

/* NOTE: translation is the repsonisbility of the caller, because some reports
 * include parts that aren't translated. For example:
 *
 *     char message[MAX_STRING_LENGTH];
 *     sprintf(message, "%s: x > %f", translate("Value of X is too small"), x);
 *     critical_box(translate("Out of Bounds"), message);
 */
void
critical_box(const char *title, const char *text)
{
    messagebox("critical", title, text);
}

/* See critical_box comment. */
void
information_box(const char *title, const char *text)
{
    messagebox("information", title, text);
}

/* See critical_box comment. */
void
question_box(const char *title, const char *text)
{
    messagebox("question", title, text);
}

/* See critical_box comment. */
void
warning_box(const char *title, const char *text)
{
    messagebox("warning", title, text);
}

/* . */
bool
valid_rgb(float r, float g, float b)
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

/* . */
int
string_array_length(EmbString s[])
{
    int i;
    for (i=0; i<MAX_TABLE_LENGTH; i++) {
        if (string_equal(s[i], end_symbol)) {
            return i;
        }
    }
    printf("ERROR: string array has no end_symbol. %s %s\n", s[0], end_symbol);
    return MAX_TABLE_LENGTH - 1;
}

/* Replace strlen to reduce crashes. Has -1 as an error code. */
int
string_length(char *src)
{
    for (int i=0; i<MAX_LONG_STRING; i++) {
        if (src[i] == 0) {
            return i;
        }
    }
    return -1;
}

/* . */
int
load_file(const char *fname)
{
    FILE* file;
    file = fopen(fname, "r");
    if (!file) {
        printf("ERROR: Failed to open \"%s\".\n", fname);
        return 0;
    }

/* FIXME:
    int i;
    EmbString error_buffer;
    toml_table_t *conf;

    conf = toml_parse_file(file, error_buffer, sizeof(error_buffer));
    fclose(file);

    if (!conf) {
        printf("ERROR: Failed to parse \"%s\".\n", fname);
        printf("    %s\n", error_buffer);
        return 0;
    }

    for (i=0; ; i++) {
        const char *key = toml_key_in(conf, i);
        if (!key) {
            break;
        }
        if (!load_string_table(conf, key)) {
            printf("ERROR: failed to load string table %s\n", key);
            return 0;
        }
    }
    toml_free(conf);
    */
    return 1;
}

/* Rather than loading necessary configuration data from file at load, it is
 * compiled into the program. However, the ability to change the UI as a
 * user, without re-compiling the program, can be preserved by overriding the string
 * tables from a custom "overrides.toml" file in the configuration directory.
 */
int
load_data(void)
{
    return 1;
}

/* . */
int
load_settings(const char *appDir, const char *fname)
{
    return 1;
}

/* The file fname needs to be read from the users home directory to ensure it is writable.
 */
int
save_settings(EmbString appDir, EmbString fname)
{
    FILE *file = fopen(fname, "w");
    if (!file) {
        return 0;
    }

    for (int i=0; i<N_SETTINGS; i++) {
        switch (setting[i].setting.type) {
        case SCRIPT_INT:
            fprintf(file, "%s = %d\r\n", settings_data[i].label, setting[i].setting.i);
            break;
        case SCRIPT_REAL:
            fprintf(file, "%s = %f\r\n", settings_data[i].label, setting[i].setting.r);
            break;
        case SCRIPT_STRING:
            fprintf(file, "%s = \"%s\"\r\n", settings_data[i].label, setting[i].setting.s);
            break;
        case SCRIPT_BOOL:
            fprintf(file, "%s = %d\r\n", settings_data[i].label, setting[i].setting.b);
            break;
        default:
            break;
        }
    }

    fclose(file);
    return 1;
}

/* . */
int
get_command_id(EmbString name)
{
    for (int i=0; i<MAX_COMMANDS; i++) {
        if (command_data[i].id == -2) {
            break;
        }
        if (string_equal(command_data[i].icon, name)) {
            return i;
        }
    }
    return -2;
}

/* . */
void
save_file(void)
{
    debug_message("MainWindow::savefile()");
}

/* TODO: Before saving to a stitch only format, Embroidermodder needs
 *       to calculate the optimal path to minimize jump stitches. Also
 *       based upon which layer needs to be stitched first,
 *       the path to the next object needs to be hidden beneath fills
 *       that will come later. When finding the optimal path, we need
 *       to take into account the color of the thread, as we do not want
 *       to try to hide dark colored stitches beneath light colored fills.
 */
bool
pattern_save(EmbPattern *pattern, EmbString fileName)
{
    EmbString message;
    sprintf(message, "SaveObject save(%s)", fileName);
    prompt_output(message);

    bool writeSuccessful = false;

    int formatType = emb_identify_format(fileName);
    if (formatType <= 0) { /* EMBFORMAT_UNSUPPORTED */
        return false;
    }

    if (!pattern) {
        prompt_output("The EmbPattern has not been allocated.");
        return false;
    }

    /* TODO: handle EMBFORMAT_STCHANDOBJ also */
    if (formatType == EMBFORMAT_STITCHONLY) {
        /* emb_pattern_movePolylinesToStitchList(pattern); */
        /* TODO: handle all objects like this */
    }

    writeSuccessful = emb_pattern_write(pattern, fileName, formatType);
    if (!writeSuccessful) {
        sprintf(message, "Writing file %s was unsuccessful", fileName);
        prompt_output(message);
    }

    /* TODO: check the embLog for errors and if any exist, report them. */

    emb_pattern_free(pattern);

    return writeSuccessful;
}

bool
int32_underflow(int64_t a, int64_t b)
{
    int64_t c;
    assert(LLONG_MAX>INT_MAX);
    c = (int64_t)a-b;
    if (c < INT_MIN || c > INT_MAX) {
        return true;
    }
    return false;
}

bool
int32_overflow(int64_t a, int64_t b)
{
    int64_t c;
    assert(LLONG_MAX>INT_MAX);
    c = (int64_t)a+b;
    if (c < INT_MIN || c > INT_MAX) {
        return true;
    }
    return false;
}

/* . */
int
round_to_multiple(bool roundUp, int numToRound, int multiple)
{
    if (multiple == 0) {
        return numToRound;
    }
    int remainder = numToRound % multiple;
    if (remainder == 0) {
        return numToRound;
    }

    if (numToRound < 0 && roundUp) {
        return numToRound - remainder;
    }
    if (roundUp) {
        return numToRound + multiple - remainder;
    }
    /* else round down */
    if (numToRound < 0 && !roundUp) {
        return numToRound - multiple - remainder;
    }
    return numToRound - remainder;
}

/* TODO: timestamp each message
 */
void
debug_message(const char *msg)
{
    EmbString buffer, fname;
    time_t t;
    struct tm* tm_info;
    sprintf(fname, "debug.log");
    FILE *f = fopen(fname, "a");
    if (!f) {
        printf("Failed to write to debug.log.");
        return;
    }
    t = time(NULL);
    tm_info = localtime(&t);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    fprintf(f, "%s %s\n", buffer, msg);
    fclose(f);
}

/* . */
void
todo(const char *txt)
{
    char message[MAX_STRING_LENGTH];
    sprintf(message, "TODO: %s", txt);
    debug_message(message);
}
 
/* . */
void
fixme(const char *msg)
{
    char outmsg[MAX_STRING_LENGTH];
    sprintf(outmsg, "FIXME: %s", msg);
    debug_message(outmsg);
}

/* . */
ScriptValue *
setting_ptr(int key, int mode)
{
    ScriptValue *set_mode;
    switch (mode) {
    case SETTING_DIALOG: {
        set_mode = &(setting[key].dialog);
        break;
    }
    case SETTING_PREVIEW: {
        set_mode = &(setting[key].preview);
        break;
    }
    case SETTING_ACCEPT: {
        set_mode = &(setting[key].dialog);
        break;
    }
    default:
    case SETTING_SETTING: {
        set_mode = &(setting[key].setting);
        break;
    }
    }
    return set_mode;
}

/* . */
void
copy_setting(int key, int dst, int src)
{
    ScriptValue *dst_set = setting_ptr(key, dst);
    ScriptValue *src_set = setting_ptr(key, src);
    switch (setting[src].setting.type) {
    case SCRIPT_INT:
        dst_set->i = src_set->i;
        break;
    case SCRIPT_REAL:
        dst_set->r = src_set->r;
        break;
    case SCRIPT_STRING:
        string_copy(dst_set->s, src_set->s);
        break;
    case SCRIPT_BOOL:
        dst_set->b = src_set->b;
        break;
    default:
        break;
    }
}

/* . */
void
emb_string(EmbString s, const char *str)
{
    for (int i=0; i<MAX_STRING_LENGTH; i++) {
        s[i] = str[i];
        if (!s[i]) {
            break;
        }
    }
    /* Reached end of string so we should ensure s is null-terminated. */
    s[MAX_STRING_LENGTH-1] = 0;
}

/* Tests if EmbString matches a fixed string, often from compiled-in program
 * data.
 */
bool
string_equal(EmbString a, const char *b)
{
    return (string_compare(a, b) == 0);
}

/* Compares two strings in a similar way to strcmp, however it is capped at
 * the MAX_STRING_LENGTH.
 */
int
string_compare(EmbString a, const char *b)
{
    for (int i=0; i<MAX_STRING_LENGTH; i++) {
        char c = a[i] - b[i];
        if (c) {
            return c;            
        }
        if (!a[i]) {
            return 0;
        }
    }
    /* Reached end of string so we should ensure that the variable string is
     * null-terminated.
     */
    a[MAX_STRING_LENGTH-1] = 0;
    return 1;
}

/* . */
int
string_list_contains(EmbStringTable list, EmbString entry)
{
    int n = string_array_length(list);
    EmbString s;
    emb_string(s, entry);
    for (int i=0; i<n; i++) {
        if (string_equal(list[i], s)) {
            return 1;
        }
    }
    return 0;
}

/* . */
const char *
platform_string(void)
{
    EmbString message;
    /* TODO: Append QSysInfo to string where applicable. */
    sprintf(message, "Platform: %s", state.os);
    debug_message(message);
    return state.os;
}

/* . */
void
hide_unimplemented(void)
{
    debug_message("hide_unimplemented()");
}

/* . */
bool
valid_file_format(EmbString fileName)
{
    if (emb_identify_format(fileName) >= 0) {
        return true;
    }
    return false;
}

/* . */
int
get_id(EmbStringTable data, EmbString label)
{
    int id;
    int n = string_array_length(data);
    for (id=0; id<n; id++) {
        if (string_equal(data[id], label)) {
            return id;
        }
    }
    return -1;
}

