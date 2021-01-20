#ifndef _UTIL_H_
#define _UTIL_H_
#define BMP_TYPE 0x4d42

_Noreturn void err( const char* msg, ... );
enum fileformat  {
    BMP = 0,
    ERROR_FORMAT
   /*другие форматы файлов*/

};
enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    NO_FILE,
    OPEN_FAIL,
    READ_FAIL,
    EMPTY_FILE,

};
enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
    /* коды других ошибок  */
};
void print_read_status(enum read_status readStatus);
void print_write_status(enum write_status writeStatus);
#endif
