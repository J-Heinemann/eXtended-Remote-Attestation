//
// Created by Joshua Heinemann on 28.07.20.
// TU-Braunschweig (heineman@ibr.cs.tu-bs.de)
//

#ifndef FAASM_XRA_ERROR_H
#define FAASM_XRA_ERROR_H

#define XRA_ERROR(X) (0x00000000|(X))
typedef enum _xra_error{
    XRA_SUCCESS = XRA_ERROR(0x0),
    XRA_INVALID_PTR = XRA_ERROR(0x1),
    XRA_PTR_NOT_INSIDE_ENCLAVE = XRA_ERROR(0x2),
    XRA_SGX_SHA256_HASH_FAILED = XRA_ERROR(0x3),
    XRA_INVALID_WASM_OPCODE_LEN = XRA_ERROR(0x4)
}xra_status_t;
#define XRA_SET_SGX_ERROR(XRA_ERROR,SGX_ERROR) (xra_status_t) ((SGX_ERROR << 16)|XRA_ERROR)
#define XRA_GET_XRA_ERROR(X) (X & 0x0000FFFF)
#define XRA_GET_SGX_ERROR(X) (X >> 16)
#endif //FAASM_XRA_ERROR_H
