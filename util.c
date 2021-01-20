#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "util.h"

_Noreturn void err( const char* msg, ... ) {
    va_list args;
    va_start (args, msg);
    vfprintf(stderr, msg, args);
    va_end (args);
    exit(1);
}
enum fileformat get_fileformat( uint32_t number){
    if(number==0){return BMP;}else {return ERROR_FORMAT;}
}
void print_read_status(enum read_status readStatus){
    switch (readStatus) {
        case READ_OK:
            printf("the file was read successfully \n");
            break;
        case NO_FILE:
            printf("file was not found \n");
            break;
        case OPEN_FAIL:
            printf("error opening file \n");
            break;
        case READ_FAIL:
            printf("error reading file \n");
            break;
        case EMPTY_FILE:
            printf("file may be empty \n");
            break;
        default:
            break;

    }

};
void print_write_status(enum write_status writeStatus){
    switch (writeStatus) {
        case WRITE_OK:
            printf("the file was written successfully \n");
            break;
        case WRITE_ERROR:
            printf("an error occurred while writing the file \n");
            break;
        default:
            break;


    }

};