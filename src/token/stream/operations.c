

#include "operations.h"
#include <stdlib.h>




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
