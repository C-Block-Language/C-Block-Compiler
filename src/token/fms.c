




static TOKEN return_tkn(const TKN_TYPE type, STR_PTR* s_pos, const STR_PTR e_pos) {
    auto tkn = EMPTY_TOKEN;
    auto str = EMPTY_STR;
    (void) str_ptrt_struct(&str, s_pos, &e_pos);

    tkn._fpos = *s_pos;
    tkn._type = type;
    tkn._str = str;

    *s_pos = e_pos;

    return tkn;
}



TOKEN reserved_word_state(STR_PTR *_spos) {
    auto e_pos = *_spos;

    char c = advance_char(&e_pos);
    if (('a' > c || c > 'z') && ('A' > c || c > 'Z') && c != '_') return EMPTY_TOKEN;

    while (true) {
        c = advance_char(&e_pos);
        // cries in Sensei senseisness wisdom
        if (c == '_' || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9')) continue;
        break;
    }

    (void) recoil_char(&e_pos);


    auto tkn = EMPTY_TOKEN;
    auto str = EMPTY_STR;
    (void) str_ptrt_struct(&str, _spos, &e_pos);

    for (size_t i = 0; i < reserved_words_count; ++i) {
        if (compare_strings(&str, &reserved_words[i]) == OK) goto success;
    }

 // fail:
    free_string(&str);
    return EMPTY_TOKEN;

    success:
    tkn._fpos = *_spos;
    tkn._type = RESERVED_WORD;
    tkn._str = str;

    *_spos = e_pos;

    return tkn;
}



static TOKEN shy_identifier_state(STR_PTR *_spos) {
    auto e_pos = *_spos;

    char c = advance_char(&e_pos);
    // cries in Sensei senseisness wisdom
    // according to crec, it is the wrong equality :pepelaugh:
    // amount of lapsus brutus crec had today: 3 (2026/feb/14)
    if (('a' > c || c > 'z') && c != '_') return EMPTY_TOKEN;


    while (true) {
        c = advance_char(&e_pos);
        // cries in Sensei senseisness wisdom
        if (c == '_' || ('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) continue;
        break;
    }

    // cries in Sensei senseisness wisdom
    if ('A' <= c && c <= 'Z') return EMPTY_TOKEN;
    (void) recoil_char(&e_pos);
    return return_tkn(SHY_IDENTIFIER, _spos, e_pos);

}



static TOKEN loud_identifier_state(STR_PTR *_spos) {
    auto e_pos = *_spos;

    char c = advance_char(&e_pos);
    if (('A' > c || c > 'Z') && c != '_') return EMPTY_TOKEN;

    while (true) {
        c = advance_char(&e_pos);
        // cries in Sensei senseisness wisdom
        if (c == '_' || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9')) continue;
        break;
    }

    // cries in Sensei senseisness wisdom
    if ('a' <= c && c <= 'z') return EMPTY_TOKEN;

    recoil_char(&e_pos);
    return return_tkn(LOUD_IDENTIFIER, _spos, e_pos);
}



static TOKEN literal_state(STR_PTR *_spos) {
    auto e_pos = *_spos;

    char c = advance_char(&e_pos);
    if (('a' > c || c > 'z') && ('A' > c || c > 'Z') && c != '_') return EMPTY_TOKEN;

    while (true) {
        c = advance_char(&e_pos);
        // cries in Sensei senseisness wisdom
        if (c == '_' || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9')) continue;
        break;
    }

    (void) recoil_char(&e_pos);
    return return_tkn(LITERAL, _spos, e_pos);
}



static TOKEN single_char_state(STR_PTR* _spos) {
    auto e_pos = *_spos;

    switch (advance_char(&e_pos)) {
        default:
            return EMPTY_TOKEN;

        case '\\': case '#':                                // macro linebreak, hashtag
        case ':': case ';': case '.': case ',':             // colon, semicolon, dot & comma
        case '+': case '-': case '*': case '/': case '%':   // arithmetic operators
        case '=':                                           // equal sign
        case '@':                                           // for selectors & inline starters
        case '^': case '~':                                 // relative & local position symbols
        case '!':                                           // negation symbol
        case '<': case '>':                                 // basic comparisons
            break;
    }

    return return_tkn(SINGLE_CHAR, _spos, e_pos);

}



static TOKEN bracket_open_state(STR_PTR* _spos) {
    auto e_pos = *_spos;

    switch (advance_char(&e_pos)) {
        default:
            return EMPTY_TOKEN;

        case '{': case '[': case '(':
            break;
    }

    return return_tkn(BRACKET_OPEN, _spos, e_pos);

}



static TOKEN bracket_close_state(STR_PTR* _spos) {
    auto e_pos = *_spos;

    switch (advance_char(&e_pos)) {
        default:
            return EMPTY_TOKEN;

        case '}': case ']': case ')':
            break;
    }

    return return_tkn(BRACKET_CLOSE, _spos, e_pos);

}



static TOKEN single_quoted_string_state(STR_PTR* _spos) {
    auto e_pos = *_spos;

    if (advance_char(&e_pos) != '\'') return EMPTY_TOKEN;

    bool end_quote_found = false;
    do {
        switch (advance_char(&e_pos)) {
            case '\\':
                if (process_escaping_sequence(&e_pos) == false) end_quote_found = true;
                break;
            case '\0':
            case '\n':
            default:
                // TODO add logger to signalise malformed single quoted string
            case '\'':
                end_quote_found = true;
        }
    } while (end_quote_found == false);

    (void) recoil_char(&e_pos);         // advance once on start
    (void) advance_char(_spos);         // & recoil on end to crop the quotation marks

    auto tkn = return_tkn(SINGLE_QUOTED_STRING, _spos, e_pos);

    (void) recoil_char(&tkn._fpos);     //
    (void) advance_char(_spos);         // advance the pointer to skip the ending quote mark

    return tkn;

}



static TOKEN double_quoted_string_state(STR_PTR* _spos) {
    auto e_pos = *_spos;

    if (advance_char(&e_pos) != '"') return EMPTY_TOKEN;

    bool end_quote_found = false;
    do {
        jump_n_seek(&e_pos, 2, '\\', '"');
        switch (advance_char(&e_pos)) {
            case '\\':
                (void) advance_char(&e_pos);
                continue;

            default:
                assert(false);                  /* Should never happen! */

            case '\0': case '"':
                end_quote_found = true;
        }
    } while (end_quote_found == false);


    (void) recoil_char(&e_pos);             // advance once on start pointer
    (void) advance_char(_spos);             // & recoil on end to crop the quotation marks.

    auto tkn = return_tkn(DOUBLE_QUOTED_STRING, _spos, e_pos);

    (void) recoil_char(&tkn._fpos);         // recoil the pointer to the tkn file pos to start on the quotation mark
    (void) advance_char(_spos);             // & advance the arg pointer to skip the ending quote mark.

    return tkn;

}



