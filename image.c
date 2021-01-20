
#include <stdio.h>
#include <inttypes.h>
#include "image.h"
#include "util.h"

struct image rotate( struct image const image ){
    uint64_t width = image.width;
    uint64_t height = image.height;

    struct image rotated_image = {
            height,
            width,
            malloc(sizeof (struct pixel) *height*width)
    };

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            rotated_image.data[j*height + (height-1-i)] = image.data[i*width+j];
        }
    }



    return rotated_image;
}

