//
// Created by joshua on 26.04.20.
//

#ifndef MY_ENCLAVE_XRA_INTERNAL_H
#define MY_ENCLAVE_XRA_INTERNAL_H
#ifndef _XRA_REPORT_ARRAY_INIT_LENGTH
#define _XRA_REPORT_ARRAY_INIT_LENGTH 0x2
#endif
#ifndef NULL
#define NULL 0x0
#endif
#ifndef XRA_DEBUG
#define XRA_DEBUG 0
#endif
#include <XRA.h>
#include <stdlib.h>
#include <string.h>
#include <sgx_thread.h>
#if(XRA_DEBUG == 1)
void(*_xra_printf)(char* format, ...) = NULL;
#endif
static xra_report_t** _xra_report_array = NULL;
static uint32_t _xra_report_array_length = 0;
static sgx_thread_mutex_t _xra_mutex_report_array = SGX_THREAD_MUTEX_INITIALIZER;
#endif //MY_ENCLAVE_XRA_INTERNAL_H
