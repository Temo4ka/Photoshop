#pragma once

#include <cstdio>

#define catchNullptr(POINTER, RETURN_IN_CASE_OF_FAILURE) {                                                         \
    if ((POINTER) == nullptr) {                                                                                     \
        FILE *logFile = fopen("logFile.txt", "a");                                                                     \
        fprintf(logFile, "%s pointer at %s at %s(%d) is NULL\n", #POINTER, __PRETTY_FUNCTION__, __FILE__, __LINE__);  \
        fclose(logFile);                                                                                               \
        return RETURN_IN_CASE_OF_FAILURE;                                                                               \
    }                                                                                                                    \
}

#define EXECUTE_ERROR(ERROR) {                                                                                                   \
    if (ERROR) {                                                                                                                  \
        FILE *logFile = fopen("logFile.txt", "a");                                                                                 \
        fprintf(logFile, "%d error at %s at %s(%d) exceeded!\n", ERROR, __PRETTY_FUNCTION__, __FILE__, __LINE__);                   \
        fclose(logFile);                                                                                                             \
    }                                                                                                                                 \
}

#define MESSAGE(...) {                                                                                                     \
    char *message = (char *) calloc(256, sizeof(char));                                                                     \
    sprintf(message, __VA_ARGS__);                                                                                           \
    FILE *logFile = fopen("logFile.txt", "a");                                                                                \
    fprintf(logFile, "MESSAGE:%s from %s at %s(%d)\n", message, __PRETTY_FUNCTION__, __FILE__, __LINE__);                      \
    fclose(logFile);                                                                                                            \
}

#define POSITION this->getPosition()

#define SIZE this->getSize()

#define SQR(a) ((a) * (a))