//
// Created by Joshua Heinemann on 28.07.20.
// TU-Braunschweig (heineman@ibr.cs.tu-bs.de)
//

#ifndef FAASM_XRA_ERROR_H
#define FAASM_XRA_ERROR_H

#define XRA_ERROR(X) (0x00000000|(X))
typedef enum _error{
    XRA_SUCCESS = XRA_ERROR(0x0),
    XRA_INVALID_PTR = XRA_ERROR(0x1),
    XRA_OUT_OF_MEMORY = XRA_ERROR(0x2)
}xra_status_t;

#endif //FAASM_XRA_ERROR_H
