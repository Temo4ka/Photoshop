#include <stdio.h>

#define catchNullptr(POINTER, RETURN_IN_CASE_OF_FAILURE) {                                                         \
    if ((POINTER) == nullptr) {                                                                                     \
        fprintf(stderr, "%s pointer at %s at %s(%d) is NULL\n", #POINTER, __PRETTY_FUNCTION__, __FILE__, __LINE__);	 \
        return RETURN_IN_CASE_OF_FAILURE;                                                                             \
    }                                                                                                                  \
}

#define SQR(a) ((a) * (a))