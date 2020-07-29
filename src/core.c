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
xra_status_t xra_create_report(const sgx_target_info_t* target_info, const sgx_report_data_t* report_data, xra_report_t* xra_report, sgx_report_t* sgx_report){
    sgx_status_t sgx_ret_val;
    sgx_report_data_t report_data_xra_hash;
    if(!target_info)
        return XRA_INVALID_PTR;
    if(!sgx_is_within_enclave((const void*)xra_report,sizeof(xra_report_t)) || !sgx_is_within_enclave((const void*)sgx_report, sizeof(sgx_report_t)))
        return XRA_PTR_NOT_INSIDE_ENCLAVE;
    if(report_data)
        memcpy(xra_report->report_data.d,report_data->d,sizeof(sgx_report_data_t));
    if((sgx_ret_val = sgx_sha256_msg((const uint8_t*)xra_report, sizeof(xra_report_t),(sgx_sha256_hash_t*)&report_data_xra_hash.d)) != SGX_SUCCESS){
        return XRA_SET_SGX_ERROR(XRA_SGX_SHA256_HASH_FAILED,sgx_ret_val);
    }
    if((sgx_ret_val = sgx_create_report(target_info,&report_data_xra_hash,sgx_report)) != SGX_SUCCESS){
        return XRA_SET_SGX_ERROR(XRA_SGX_CREATE_REPORT_FAILED,sgx_ret_val);
    }
    return XRA_SUCCESS;
}
#ifdef __cplusplus
};
#endif