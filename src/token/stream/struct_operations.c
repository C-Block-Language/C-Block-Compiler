


#include <stdlib.h>

#include "c_block/log_signal.h"
#include "c_block/token.h"


LOG_SIGNAL tkn_stream_reserve(TOKEN_STREAM *_target_tkn_strm, const size_t _size) {
    if (_target_tkn_strm->_buff > _size && _size != 0) return OK;
    const size_t recv_buffer = _target_tkn_strm->_buff;

    while (_target_tkn_strm->_buff < _size + 1) _target_tkn_strm->_buff <<= 1;


    TOKEN* new_ptr = realloc(_target_tkn_strm->_toks, sizeof(TOKEN) * _target_tkn_strm->_buff);

    if (new_ptr == nullptr) {
        _target_tkn_strm->_buff = recv_buffer;
        return ERR_MEM;
    }

    _target_tkn_strm->_toks = new_ptr;
    if (_target_tkn_strm->_len == 0) _target_tkn_strm->_toks[0] = EMPTY_TOKEN;

    return OK;
}




LOG_SIGNAL appendt_tkn_stream(TOKEN_STREAM *_target_tkn_strm, const TOKEN _tkn) {
    const auto length = &_target_tkn_strm->_len;

    if (tkn_stream_reserve(_target_tkn_strm, *length + 1) == ERR_MEM) return ERR_MEM;
    _target_tkn_strm->_toks[*length] = _tkn;
    ++*length;

    return OK;
}

void op_on_all_tkns(const TOKEN_STREAM *_target_tkn_strm, void(*_tkn_op)(TOKEN *)) {
    for (size_t i = 0; i < _target_tkn_strm->_len; ++i) {
        _tkn_op(&_target_tkn_strm->_toks[i]);
    }
}


