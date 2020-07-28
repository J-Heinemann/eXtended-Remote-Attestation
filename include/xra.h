//
// Created by Joshua Heinemann on 28.07.20.
// TU-Braunschweig (heineman@ibr.cs.tu-bs.de)
//

#ifndef FAASM_XRA_H
#define FAASM_XRA_H

#include <sgx.h>
#include <sgx_report.h>
#include <sgx_utils.h>
#include <xra_error.h>

typedef struct _report{
    sgx_report_data_t report_data;
}xra_report_t;

xra_status_t xra_create_report(const sgx_target_info_t* target_info, const sgx_report_data_t* report_data, xra_report_t* xra_report, sgx_report_t* sgx_report);

#endif //FAASM_XRA_H
