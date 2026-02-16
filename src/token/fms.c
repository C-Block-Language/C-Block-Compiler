




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



