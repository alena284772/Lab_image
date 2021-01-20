#ifndef _BMP_H_
#define _BMP_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "image.h"
#include "util.h"

#define FOR_BMP_HEADER( FOR_FIELD ) \
        FOR_FIELD( uint16_t,bfType)\
        FOR_FIELD( uint32_t,bfileSize)\
        FOR_FIELD( uint32_t,bfReserved)\
        FOR_FIELD( uint32_t,bOffBits)\
        FOR_FIELD( uint32_t,biSize)\
        FOR_FIELD( uint32_t,biWidth)\
        FOR_FIELD( uint32_t,biHeight)\
        FOR_FIELD( uint16_t,biPlanes)\
        FOR_FIELD( uint16_t,biBitCount)\
        FOR_FIELD( uint32_t,biCompression)\
        FOR_FIELD( uint32_t,biSizeImage)\
        FOR_FIELD( uint32_t,biXPelsPerMeter)\
        FOR_FIELD( uint32_t,biYPelsPerMeter)\
        FOR_FIELD( uint32_t,biClrUsed)\
        FOR_FIELD( uint32_t,biClrImportant)

#define DECLARE_FIELD( t, n ) t n ;


struct __attribute__((packed)) bmp_header
{
    FOR_BMP_HEADER( DECLARE_FIELD )
};



bool read_header_from_file( const char* filename, struct bmp_header* header );
enum read_status from_bmp( FILE* input, struct image* image );
enum read_status open_file(const char* filename,struct image* image,enum fileformat fileformat);
enum write_status save_file( const char* filename, struct image* image);
enum write_status to_bmp( FILE* output, struct image const* image );
struct bmp_header create_bmp_header(struct image const* image);
enum fileformat read_format(const char * filename);
#endif
