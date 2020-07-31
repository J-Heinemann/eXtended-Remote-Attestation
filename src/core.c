//
// Created by Joshua Heinemann on 28.07.20.
// TU-Braunschweig (heineman@ibr.cs.tu-bs.de)
//

#include <sgx_tcrypto.h>
#include <sgx_trts.h>
#include <string.h>
#include <xra.h>
#ifdef __cplusplus
extern "C"{
#endif
xra_status_t xra_create_report(const uint8_t* wasm_opcode_ptr, uint32_t wasm_opcode_len, const uint8_t* whitelist_ptr, xra_report_t* xra_report_ptr){
    sgx_status_t sgx_ret_val;
    if(!xra_report_ptr)
        return XRA_INVALID_PTR;
    if(!sgx_is_within_enclave((const void*)xra_report_ptr,sizeof(xra_report_t)))
        return XRA_PTR_NOT_INSIDE_ENCLAVE;
    if(wasm_opcode_ptr && !wasm_opcode_len)
        return XRA_INVALID_WASM_OPCODE_LEN;
    if(wasm_opcode_ptr){
        if(!sgx_is_within_enclave(wasm_opcode_ptr, wasm_opcode_len * sizeof(uint8_t)))
            return XRA_PTR_NOT_INSIDE_ENCLAVE;
        if((sgx_ret_val = sgx_sha256_msg(wasm_opcode_ptr,wasm_opcode_len,(sgx_sha256_hash_t*)xra_report_ptr->wasm_opcode_hash)) != SGX_SUCCESS)
            return XRA_SET_SGX_ERROR(XRA_SGX_SHA256_HASH_FAILED,sgx_ret_val);
    } else
        memset((void*)xra_report_ptr->wasm_opcode_hash,0x0, SGX_SHA256_HASH_SIZE * sizeof(uint8_t));
    if(whitelist_ptr){
        uint32_t whitelist_len = strlen((const char*)whitelist_ptr) + 1;
        if(!sgx_is_within_enclave((void*) whitelist_ptr,whitelist_len))
            return XRA_PTR_NOT_INSIDE_ENCLAVE;
        if((sgx_ret_val = sgx_sha256_msg(whitelist_ptr, whitelist_len, (sgx_sha256_hash_t*) xra_report_ptr->whitelist_hash)) != SGX_SUCCESS)
            return XRA_SET_SGX_ERROR(XRA_SGX_SHA256_HASH_FAILED,sgx_ret_val);
    } else
        memset((void*)xra_report_ptr->whitelist_hash,0x0,SGX_SHA256_HASH_SIZE * sizeof(uint8_t));
    return XRA_SUCCESS;
}
#ifdef __cplusplus
};
#endif