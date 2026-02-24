


#include <stdio.h>


#include <stdlib.h>

#include "c_block/pack_build_parser.h"
#include "c_block/log_signal.h"
#include "c_block/file.h"
#include "c_block/string/struct_operations.h"
#include "c_block/token/stream.h"


STRING wd_path = EMPTY_STR;

// If EMPTY_STR, means that the include precompilation directive will be disabled.
STRING include_directory_path = EMPTY_STR;

// If EMPTY_STR, means that no build directory statement was found on 'pack.build'.
STRING build_directory_path = EMPTY_STR;

size_t translation_units = 0;




static LOG_SIGNAL parse_include_directory(TOKEN_STREAM* _pack_build) {
    auto ptr = NULL_TOKEN_STREAM_PTR;

    auto file_struct = EMPTY_FILE_STRUCT;
    assg_tkn_ptr(&ptr, _pack_build);

    auto tkn = EMPTY_TOKEN;

    find_statement:
    while (gtkn(&ptr)._type != INVALID_STATE) {
        tkn = advance_tkn(&ptr);
        if (tkn._type != SHY_IDENTIFIER) continue;
        if (compare_strings(&tkn._str, &STATIC_STR("include_directory")) != OK) continue;
        goto found_statement;
    }

    return ERR_NOT_FOUND;

    found_statement:

    tkn = advance_tkn(&ptr);

    if (tkn._type != SINGLE_CHAR) {
        file_struct = get_file_struct(tkn._forigin);
        printf("[BUILD::WARN]\tMalformed definition statement for include directory:\n");
        printf("  [!]  Expected '=' symbol at %s:%zu:%zu. Ignoring malformed statement...\n\n",
            file_struct._f_name._str,
            tkn._fpos._line,
            tkn._fpos._column
        );
        (void) recoil_tkn(&ptr);
        goto find_statement;
    }

    tkn = advance_tkn(&ptr);
    if (tkn._type != DOUBLE_QUOTED_STRING) {
        file_struct = get_file_struct(tkn._forigin);
        printf("[BUILD::WARN]\tMalformed definition statement for include directory:\n");
        printf("  [!]  Expected a double quoted string at %s:%zu:%zu. Ignoring malformed statement...\n\n",
            file_struct._f_name._str,
            tkn._fpos._line,
            tkn._fpos._column
        );

        (void) recoil_tkn(&ptr);
        goto find_statement;
    }

    include_directory_path = get_absolute_path(&tkn._str);
    if (include_directory_path._str == nullptr) {
        file_struct = get_file_struct(tkn._forigin);
        printf("[BUILD::WARN]\t(Unique error to UNIX implementation) Couldn't open directory defined for the include directory.\n");
        printf("  [!]  Couldn't find directory declared at %s:%zu:%zu. Ignoring statement...\n\n",
            file_struct._f_name._str,
            tkn._fpos._line,
            tkn._fpos._column
        );
        (void) recoil_tkn(&ptr);
        goto find_statement;
    }

    return OK;
}



static LOG_SIGNAL parse_build_directory(TOKEN_STREAM* _pack_build) {
    auto ptr = NULL_TOKEN_STREAM_PTR;

    auto file_struct = EMPTY_FILE_STRUCT;
    assg_tkn_ptr(&ptr, _pack_build);

    auto tkn = EMPTY_TOKEN;

    find_statement:
    while (gtkn(&ptr)._type != INVALID_STATE) {
        tkn = advance_tkn(&ptr);
        if (tkn._type != SHY_IDENTIFIER) continue;
        if (compare_strings(&tkn._str, &STATIC_STR("build_directory")) != OK) continue;
        goto found_statement;
    }

    return ERR_NOT_FOUND;

    found_statement:

    tkn = advance_tkn(&ptr);

    if (tkn._type != SINGLE_CHAR) {
        file_struct = get_file_struct(tkn._forigin);
        printf("[BUILD::WARN]\tMalformed definition statement for build directory:\n");
        printf("  [!]  Expected '=' symbol at %s:%zu:%zu. Ignoring malformed statement...\n\n",
            file_struct._f_name._str,
            tkn._fpos._line,
            tkn._fpos._column
        );
        (void) recoil_tkn(&ptr);
        goto find_statement;
    }

    tkn = advance_tkn(&ptr);
    if (tkn._type != DOUBLE_QUOTED_STRING) {
        file_struct = get_file_struct(tkn._forigin);
        printf("[BUILD::WARN]\tMalformed definition statement for build directory:\n");
        printf("  [!]  Expected a double quoted string at %s:%zu:%zu. Ignoring malformed statement...\n\n",
            file_struct._f_name._str,
            tkn._fpos._line,
            tkn._fpos._column
        );

        (void) recoil_tkn(&ptr);
        goto find_statement;
    }

    build_directory_path = get_absolute_path(&tkn._str);
    if (build_directory_path._str == nullptr) {
        file_struct = get_file_struct(tkn._forigin);
        printf("[BUILD::WARN]\t(Unique error to UNIX implementation) Couldn't open directory defined for the build directory.\n");
        printf("  [!]  Couldn't find directory declared at %s:%zu:%zu. Ignoring statement...\n\n",
            file_struct._f_name._str,
            tkn._fpos._line,
            tkn._fpos._column
        );
        (void) recoil_tkn(&ptr);
        goto find_statement;
    }

    return OK;
}


static LOG_SIGNAL parse_source_files(TOKEN_STREAM* _pack_build) {
    auto ptr = NULL_TOKEN_STREAM_PTR;

    auto file_struct = EMPTY_FILE_STRUCT;
    auto file_id = NULL_FILE;

    assg_tkn_ptr(&ptr, _pack_build);

    auto tkn = EMPTY_TOKEN;

    find_statement:
    while (gtkn(&ptr)._type != INVALID_STATE) {
        tkn = advance_tkn(&ptr);
        if (tkn._type != SHY_IDENTIFIER) continue;
        if (compare_strings(&tkn._str, &STATIC_STR("source_files")) != OK) continue;
        goto found_statement;
    }

    return ERR_NOT_FOUND;

    found_statement:

    tkn = advance_tkn(&ptr);

    if (tkn._type != SINGLE_CHAR) {
        file_struct = get_file_struct(tkn._forigin);
        printf("[BUILD::WARN]\tMalformed definition statement for source files:\n");
        printf("  [!]  Expected '=' symbol at %s:%zu:%zu. Ignoring malformed statement...\n\n",
            file_struct._f_name._str,
            tkn._fpos._line,
            tkn._fpos._column
        );
        (void) recoil_tkn(&ptr);
        goto find_statement;
    }

    printf("[BUILD::INFO]\tFound a valid source_files statement...\n");

    parse_entry:
    tkn = advance_tkn(&ptr);
    if (tkn._type == INVALID_STATE) {
        if (translation_units > 0) return OK;
        return ERR_NOT_FOUND;
    }

    if (tkn._type != DOUBLE_QUOTED_STRING) {
        file_struct = get_file_struct(tkn._forigin);
        printf("[BUILD::WARN]\tMalformed definition statement for source files:\n");
        printf("  [!]  Expected a double quoted string at %s:%zu:%zu. Ignoring malformed entry...\n\n",
            file_struct._f_name._str,
            tkn._fpos._line,
            tkn._fpos._column
        );

        (void) recoil_tkn(&ptr);
        goto parse_entry;
    }

    file_id = process_file(&tkn._str);
    if (file_id == NULL_FILE) {
        file_struct = get_file_struct(tkn._forigin);
        printf("  [!]  Couldn't find file declared at %s:%zu:%zu. Ignoring entry...\n\n",
            file_struct._f_name._str,
            tkn._fpos._line,
            tkn._fpos._column
        );
        goto parse_entry;
    }

    printf("  [%%]  Added file %s to source files to be compiled.\n", get_file_struct(tkn._forigin)._f_name._str);

    ++translation_units;
    goto parse_entry;

}

void parse_pack_build() {

    initialise_file_allocator();

    wd_path = get_absolute_path(&STATIC_STR("."));
    printf("[BUILD::INFO]\tThe working directory for this build task is: %s\n", wd_path._str);

    const auto pack_build = process_file(&STATIC_STR("pack.build"));


    if (pack_build == NULL_FILE) {
        printf("[BUILD::ERROR]\tCould not find the required file 'pack.build' at location: %s\n", wd_path._str);
        printf(" * Possible reasons:\n");
        printf("    - The file does not exist.\n"                                               );
        printf("    - You do not have the required permissions to open it.\n"                   );
        printf("    - The file is being used by another program.\n"                             );
        printf("    - Your project is not located at %s.\n\n", wd_path._str                     );
        printf("[EXIT]\tCan't continue with build task :/\n"                                    );
        abort();
    }


    printf("[BUILD::INFO]\tFound 'pack.build' file on the expected location. Parsing...\n");

    auto pack_build_stream = get_token_stream(pack_build);

    if (parse_build_directory(&pack_build_stream) != OK) {
        printf("[BUILD::WARN]\tCould not find a valid 'build_directory' definition statement on 'pack.build'.\n");
        printf("[EXIT]\tCan't continue with build task :/\n"                                                    );
        abort();
    }

    printf("[BUILD::INFO]\tFound a valid 'build_directory' definition statement on 'pack.build', the build directory for this build task will be: %s\n", build_directory_path._str);


    if (parse_include_directory(&pack_build_stream) != OK) {
        printf("[BUILD::WARN]\tCould not find a valid 'include_directory' definition statement on 'pack.build', include precompilation directive will be disabled for this build task.\n");
    } else
        printf("[BUILD::INFO]\tFound a valid 'include_directory' definition statement on 'pack.build', the include directory for this build task will be: %s\n", include_directory_path._str);

    if (parse_source_files(&pack_build_stream) != OK) {

    }

}


