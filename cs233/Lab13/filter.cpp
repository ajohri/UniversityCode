#include <stdio.h>
#include <stdlib.h>
#include "filter.h"

// modify this code by fusing loops together
void
filter_fusion(pixel_t **image1, pixel_t **image2) {
    for (int i = 1; i < SIZE - 1; i ++) {
        if(i > 0 && i < SIZE - 1; i++)
          filter1(image1, image2, i);
        if(i > 1 && i < SIZE - 2)
          filter2(image1, image2, i);
        if(i > 5)
          filter3(image2, i-5);
    }
}

// modify this code by adding software prefetching
void
filter_prefetch(pixel_t **image1, pixel_t **image2) {
  for (int i = 1 ; i < SIZE-1 ; i++)
  {
    __builtin_prefetch(&image2[i+3]->x);
    __builtin_prefetch(&image2[i+3]->y);
    __builtin_prefetch(&image2[i+3]->z);
    __builtin_prefetch(&image1[i+5]->x);
    __builtin_prefetch(&image1[i+5]->y);
    __builtin_prefetch(&image1[i+5]->z);
    filter1(image1, image2, i);
  }

  for (int i = 2 ; i < SIZE-2 ; i ++)
  {
    __builtin_prefetch(&image2[i-1]->r);
    __builtin_prefetch(&image2[i-1]->g);
    __builtin_prefetch(&image2[i-1]->b);
    __builtin_prefetch(&image1[i+3]->r);
    __builtin_prefetch(&image1[i+3]->g);
    __builtin_prefetch(&image1[i+3]->b);
    filter2(image1, image2, i);
  }

  for (int i = 1 ; i < SIZE-5 ; i ++)
  {
    __builtin_prefetch(&image2[i+1]->x);
    __builtin_prefetch(&image2[i+1]->y);
    __builtin_prefetch(&image2[i+1]->z);
    __builtin_prefetch(&image2[i+6]->x);
    __builtin_prefetch(&image2[i+6]->y);
    __builtin_prefetch(&image2[i+6]->z);
    filter3(image2, i);
  }
}

// modify this code by adding software prefetching and fusing loops together
void
filter_all(pixel_t **image1, pixel_t **image2) {
    for (int i = 1 ; i < SIZE ; i++) {
      if(i < SIZE-1){
        __builtin_prefetch(&image2[i+3]->x);
        __builtin_prefetch(&image2[i+3]->y);
        __builtin_prefetch(&image2[i+3]->z);
        __builtin_prefetch(&image1[i+5]->x);
        __builtin_prefetch(&image1[i+5]->y);
        __builtin_prefetch(&image1[i+5]->z);
        filter1(image1, image2, i);
      }

    if(i >= 2 && i < SIZE-2){
        __builtin_prefetch(&image2[i-1]->r);
        __builtin_prefetch(&image2[i-1]->g);
        __builtin_prefetch(&image2[i-1]->b);
        __builtin_prefetch(&image1[i+3]->r);
        __builtin_prefetch(&image1[i+3]->g);
        __builtin_prefetch(&image1[i+3]->b);
        filter2(image1, image2, i);
    }
    if(i >= 6 && i < SIZE){
      __builtin_prefetch(&image2[i+1]->x);
      __builtin_prefetch(&image2[i+1]->y);
      __builtin_prefetch(&image2[i+1]->z);
      __builtin_prefetch(&image2[i+6]->x);
      __builtin_prefetch(&image2[i+6]->y);
      __builtin_prefetch(&image2[i+6]->z);
      filter3(image2, i-5);
    }
  }

}
