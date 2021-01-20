#include <stdbool.h>
#include <stdio.h>
#include <accctrl.h>


#include "bmp.h"
#include "util.h"


void usage() {
    fprintf(stderr, "Usage: ./rotate_bmp BMP_FILE_NAME \n");
}

int main( int argc, char** argv ) {
    if (argc != 2) usage();
    if (argc < 2) printf("Not enough arguments \n" );
    if (argc > 2) printf("Too many arguments \n" );

   // enum fileformat fileformat=get_fileformat(atoi(argv[2]));
    struct image* image = malloc(sizeof (struct image));
    enum fileformat fileformat=read_format(argv[1]);
    if(fileformat!=ERROR_FORMAT){
    enum read_status readStatus=open_file(argv[1],image,fileformat);
    print_read_status(readStatus);
    struct image rotated_image=rotate(*image);
    printf("image was rotated \n");
    enum write_status writeStatus=save_file(argv[1],&rotated_image);
    print_write_status(writeStatus);
    } else {
        if(argc==2){
        printf("this format is not supported");}
    }




    //open_bmp_from_file(argv[1], img);

    //out("rotating image...\n");

    //struct image rotated_img = rotate(*img);
    //out("created image\n");

    // out("image rotated\n");

    // save_as_bmp(argv[2], &rotated_img);
    //save_as_bmp(argv[2], img);

    return 0;
}

