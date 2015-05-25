#ifndef __DATA
#define __DATA

typedef struct __data{
    int n;
} _data;

int data_get_n(_data *d){
    return d->n;
}

#endif /* __DATA */
