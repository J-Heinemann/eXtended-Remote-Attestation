//
// Created by joshua on 26.04.20.
//

#ifndef MY_ENCLAVE_XRA_H
#define MY_ENCLAVE_XRA_H
#include <XRA_error.h>
#include <stdint.h>
typedef uint8_t xra_report_id_t;
typedef struct{
    uint8_t section_number;
    uint16_t size;
}xra_report_t;
typedef struct{
    uint8_t type;
    uint8_t name;
    uint16_t offset;
}xra_report_section_hdr_t;
typedef struct{

}xra_report_section_wasm_code_t;
#if defined(__cplusplus)
extern "C" {
#endif
#if(XRA_DEBUG == 1)
void xra_debug_set_printf(void(*printf_fct)(char *msg, ...));
#endif
xra_status_t xra_create_report(xra_report_id_t* report_id_ptr);
xra_status_t xra_gen_report(xra_report_id_t* report_id_ptr);
#if defined(__cplusplus)
}
#endif
#endif //MY_ENCLAVE_XRA_H