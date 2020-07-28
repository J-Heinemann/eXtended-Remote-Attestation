//
// Created by Joshua Heinemann on 28.07.20.
// TU-Braunschweig (heineman@ibr.cs.tu-bs.de)
//

#include <xra.h>

xra_status_t xra_create_report(const sgx_target_info_t* target_info, const sgx_report_data_t* report_data, xra_report_t* xra_report, sgx_report_t* sgx_report){
    if(!target_info || !report_data)
        return XRA_INVALID_PTR;
    return XRA_SUCCESS;
}