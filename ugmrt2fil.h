#ifndef _ugmrt2fil_h_
#define _ugmrt2fil_h_

#include "filhead.h"

template<typename T>
void correct_stokes(T *data, int nchan){
    
    for(int c=0; c<nchan; c++){
        T tmp = data[4*c + 1];
        data[4*c + 1] = data[4*c + 2];
        data[4*c + 2] = tmp;
    }
}

template <typename T>
void reverse_channels(T *data, int nchan){
    T tmp;
    
    for(int i=0; i<nchan/2; i++){
        int j = nchan-i-1;
        tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }
}


#endif
