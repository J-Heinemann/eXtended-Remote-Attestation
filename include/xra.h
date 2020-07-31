//
// Created by Joshua Heinemann on 28.07.20.
// TU-Braunschweig (heineman@ibr.cs.tu-bs.de)
//

#ifndef FAASM_XRA_H
#define FAASM_XRA_H

#include <sgx.h>
#include <sgx_report.h>
#include <sgx_tcrypto.h>
#include <sgx_utils.h>
#include <xra_error.h>

typedef struct _xra_report{
    uint8_t wasm_opcode_hash[SGX_SHA256_HASH_SIZE];
    uint8_t whitelist_hash[SGX_SHA256_HASH_SIZE];
}xra_report_t;

#ifdef __cplusplus
extern "C"{
#endif
xra_status_t xra_create_report(const uint8_t* wasm_opcode_ptr, uint32_t wasm_opcode_len, const uint8_t* whitelist_ptr, xra_report_t* xra_report_ptr);
#ifdef __cplusplus
};
#endif
#endif //FAASM_XRA_H
