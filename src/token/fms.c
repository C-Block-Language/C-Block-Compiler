




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


