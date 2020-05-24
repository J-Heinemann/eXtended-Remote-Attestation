//
// Created by joshua on 26.04.20.
//
#include <XRA_internal.h>
#if(XRA_DEBUG == 1)
void xra_debug_set_printf(void(*printf_fct)(char* msg, ...)){
    _xra_printf = printf_fct;
}
#endif
xra_status_t xra_create_report(xra_report_id_t* xra_report_id_ptr){
    xra_report_id_t _report_id;
    xra_report_t** _temp_report_array_ptr;
#if(XRA_DEBUG == 1)
    _xra_printf("########## XRA_CREATE_REPORT() ##########\n");
#endif
    if(sgx_thread_mutex_lock(&_xra_mutex_report_array)){
#if(XRA_DEBUG == 1)
        _xra_printf("[XRA][ERROR] Can't lock mutex.\n");
#endif
        return XRA_MUTEX_LOCK_FAILED;
    }
    if(!_xra_report_array && !_xra_report_array_length){
#if(XRA_DEBUG == 1)
        _xra_printf("[XRA][INFO] Initialize memory for xra_report_t* array.\n");
#endif
        if((_xra_report_array = calloc(_xra_report_array_length,sizeof(xra_report_t*))) == NULL){
#if(XRA_DEBUG == 1)
            _xra_printf("[XRA][ERROR] Unable to allocate memory for report ptr's.\n");
#endif
            if(sgx_thread_mutex_unlock(&_xra_mutex_report_array)){
#if(XRA_DEBUG == 1)
                _xra_printf("[XRA][ERROR] Can't unlock mutex.\n");
#endif
                return XRA_MUTEX_UNLOCK_FAILED;
            }
            return XRA_CALLOC_FAILED;
        }
        _xra_report_array_length = _XRA_REPORT_ARRAY_INIT_LENGTH;
        _report_id = 0;
    }else{
#if(XRA_DEBUG == 1)
            _xra_printf("[XRA][INFO] Looking for suitable pointer slot.\n");
#endif
        for(int i = 0; i < _xra_report_array_length; i++){
            if(_xra_report_array[i] == NULL){
                _report_id = i;
#if(XRA_DEBUG == 1)
                _xra_printf("[XRA][INFO] Found suitable pointer slot.\n");
#endif
                goto REPORT_SLOT_FOUND;
            }
        }
        _temp_report_array_ptr = _xra_report_array;
#if(XRA_DEBUG == 1)
        _xra_printf("[XRA][INFO] Reallocate xra_report_t pointer array.\n");
#endif
        if((_xra_report_array = realloc(_xra_report_array,2 * (_xra_report_array_length * sizeof(xra_report_t*)))) == NULL){
#if(XRA_DEBUG == 1)
            _xra_printf("[XRA][ERROR] Unable to reallocate memory for reports.\n");
#endif
            _xra_report_array = _temp_report_array_ptr;
            if(sgx_thread_mutex_unlock(&_xra_mutex_report_array)){
#if(XRA_DEBUG == 1)
                _xra_printf("[XRA][ERROR] Can't unlock mutex.\n");
#endif
                return XRA_MUTEX_UNLOCK_FAILED;
            }
            return XRA_REALLOC_FAILED;
        }
        memset(&_xra_report_array[_xra_report_array_length],0x0,_xra_report_array_length * sizeof(xra_report_t*));
        _report_id = _xra_report_array_length;
        _xra_report_array_length = 2 * _xra_report_array_length;
    }
    REPORT_SLOT_FOUND:
#if(XRA_DEBUG == 1)
    _xra_printf("[XRA][INFO] Create new xra_report_t on pointer slot %#02x.\n",_report_id);
#endif
    if((_xra_report_array[_report_id] = calloc(1,sizeof(xra_report_t))) == NULL){
#if(XRA_DEBUG == 1)
        _xra_printf("[XRA][ERROR] Unable to allocate memory for report.\n");
#endif
        if(sgx_thread_mutex_unlock(&_xra_mutex_report_array)){
#if(XRA_DEBUG == 1)
            _xra_printf("[XRA][ERROR] Can't unlock mutex.\n");
#endif
            return XRA_MUTEX_UNLOCK_FAILED;
        }
        return XRA_CALLOC_FAILED;
    }
    if(sgx_thread_mutex_unlock(&_xra_mutex_report_array)){
#if(XRA_DEBUG == 1)
        _xra_printf("[XRA][ERROR] Can't unlock mutex.\n");
#endif
        return XRA_MUTEX_UNLOCK_FAILED;
    }
#if(XRA_DEBUG ==  1)
    _xra_printf("[XRA][INFO] Initialize header area of xra_report.\n");
#endif
    _xra_report_array[_report_id]->size = sizeof(xra_report_t);
    *xra_report_id_ptr = _report_id;
#if(XRA_DEBUG == 1)
    _xra_printf("#########################################\n");
#endif
    return XRA_SUCCESS;
}
xra_status_t xra_gen_report(xra_report_id_t* xra_report_id_ptr){
    _xra_printf("ID: %#02x\n",*xra_report_id_ptr);
}