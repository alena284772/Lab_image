#include "bmp.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>

#define PRI_SPECIFIER(e) (_Generic( (e), uint16_t : "%" PRIu16, uint32_t: "%" PRIu32, default: "NOT IMPLEMENTED" ))

#define PRINT_FIELD( t, name ) \
    fprintf( f, "%-17s: ",  # name ); \
    fprintf( f, PRI_SPECIFIER( header-> name ) , header-> name );\
    fprintf( f, "\n");


void bmp_header_print( struct bmp_header const* header, FILE* f ) {
    FOR_BMP_HEADER( PRINT_FIELD )
}

static bool read_header( FILE* f, struct bmp_header* header ) {
    return fread( header, sizeof( struct bmp_header ), 1, f );
}

bool read_header_from_file( const char* filename, struct bmp_header* header ) {
    if (!filename) return false;
    FILE* f = fopen( filename, "rb" );
    if (!f) return false;
    if (read_header( f, header ) ) {

        fclose( f );
        return true;
    }

    fclose( f );
    return false;
}
enum fileformat read_format(const char * filename){
    struct bmp_header* header=malloc(sizeof (struct bmp_header));
    if(read_header_from_file(filename,header)){
        if(header->bfType==BMP_TYPE){return BMP;}
    } else{return ERROR_FORMAT;}
}

enum read_status open_file(const char* filename,struct image* image,enum fileformat fileformat){
    printf("OPENING: \n");
    if (!filename) return NO_FILE;
    FILE* input = fopen(filename, "rb");
    if(!input) {
        fclose(input);
        return OPEN_FAIL;
    }
    enum read_status readStatus;
    switch (fileformat) {
        case BMP:
            readStatus=from_bmp(input, image);
            return readStatus;
            break;
        default:
            break;
    }


}
enum read_status from_bmp( FILE* input, struct image* image ){

    struct bmp_header* header = malloc(sizeof (struct bmp_header));
    if(!read_header(input, header)){
        return READ_FAIL;
    }
    uint32_t height = header->biHeight;
    uint32_t width = header->biWidth;

    image->width=width;
    image->height=height;
    image->data=malloc(sizeof (struct pixel)*height*width);

    size_t padding = (4 - (width * 3 % 4))%4;

    for(size_t i=0;i<height;i++){
        if(fread(&(image->data[i * width]), sizeof (struct pixel), width, input) < 1){
            return EMPTY_FILE;
        }
        fseek(input, padding, SEEK_CUR);
    }


    return READ_OK;
}

enum  write_status save_file( const char* filename, struct image* image){
    FILE* output;

    output = fopen(filename, "wb");
    if(!output){
        fclose(output);
        return WRITE_ERROR;
    }
printf( "START OF WRITING: \n");
    enum write_status status = to_bmp(output, image);
    fclose(output);
    return status;
}
enum write_status to_bmp( FILE* output, struct image const* image ){
    const uint8_t empty_byte = 0;
    size_t padding = (4 - (image->width * 3 % 4))%4;

    struct bmp_header header = create_bmp_header(image);
    if(fwrite(&header, sizeof(struct bmp_header), 1, output)<1){
        fclose(output);
        return WRITE_ERROR;
    }

    for (size_t i = 0; i < image->height; i++) {
        if(fwrite(&image->data[i * image->width], sizeof(struct pixel), image->width, output) < 1){
            fclose(output);
            return WRITE_ERROR;
        }
        fwrite(&empty_byte, 1, padding, output);
    }
    fclose(output);
    return WRITE_OK;
}
struct bmp_header create_bmp_header(struct image const* image) {
    struct bmp_header header;

    header.bfType = BMP_TYPE;
    header.bfileSize = sizeof(struct bmp_header) + (sizeof(struct pixel) * image->width + image->width % 4) * image->height;
    header.bfReserved = 0;
    header.bOffBits = sizeof(struct bmp_header);
    header.biSize = 40;
    header.biWidth = image->width;
    header.biHeight = image->height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biSizeImage = image->width * image->height * sizeof(struct pixel);
    header.biXPelsPerMeter = 0;
    header.biYPelsPerMeter = 0;
    header.biClrUsed = 0;
    header.biClrImportant = 0;

    return header;
}
