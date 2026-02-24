

#include "c_block/token/stream/ptr_operations.h"

#include <assert.h>


void assg_tkn_ptr(TKN_STREAM_PTR *_target_ptr, TOKEN_STREAM *_tkn_strm) {
    assert(_target_ptr != nullptr);                 /* Can't operate on the null pointer.                   */
    assert(_tkn_strm != nullptr);                   /* Can't operate on the null pointer.                   */
    assert(_target_ptr->_tkn_strm == nullptr);      /* Can't operate on non-null token stream pointers.     */

    _target_ptr->_tkn_strm = _tkn_strm;
    _target_ptr->_index = 0;
}




TOKEN gtkn(const TKN_STREAM_PTR *_target_ptr) {
    assert(_target_ptr != nullptr);                 /* Can't operate on the null pointer.                   */
    assert(_target_ptr->_tkn_strm != nullptr);      /* Can't operate on non-null token stream pointers.     */

    if (_target_ptr->_index >= _target_ptr->_tkn_strm->_len) return EMPTY_TOKEN;
    return _target_ptr->_tkn_strm->_toks[_target_ptr->_index];
}




TOKEN advance_tkn(TKN_STREAM_PTR *_target_ptr) {
    assert(_target_ptr != nullptr);                 /* Can't operate on the null pointer.                   */
    assert(_target_ptr->_tkn_strm != nullptr);      /* Can't operate on non-null token stream pointers.     */

    const size_t stream_max_index = _target_ptr->_tkn_strm->_len;
    const size_t index = _target_ptr->_index;

    if (index >= stream_max_index) return EMPTY_TOKEN;

    const TOKEN c = gtkn(_target_ptr);

    _target_ptr->_index += 1;


    return c;

}




TOKEN recoil_tkn(TKN_STREAM_PTR *_target_ptr) {
    assert(_target_ptr != nullptr);                 /* Can't operate on the null pointer.                   */
    assert(_target_ptr->_tkn_strm != nullptr);      /* Can't operate on non-null token stream pointers.     */


    const auto toks = _target_ptr->_tkn_strm->_toks;    // pointers to avoid a '->' hell
    const auto index = &_target_ptr->_index;


    if (*index == 0) return toks[0];

    --*index;

    const TOKEN tkn = toks[*index];                         // same here xd
    return tkn;

}

