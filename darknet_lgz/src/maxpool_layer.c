#include "maxpool_layer.h"
#include "cuda.h"
#include <stdio.h>

image get_maxpool_image(maxpool_layer l)
{
    int h = l.out_h;
    int w = l.out_w;
    int c = l.c;
    return float_to_image(w,h,c,l.output);
}

image get_maxpool_delta(maxpool_layer l)
{
    int h = l.out_h;
    int w = l.out_w;
    int c = l.c;
    return float_to_image(w,h,c,l.delta);
}

<<<<<<< HEAD
<<<<<<< HEAD
maxpool_layer make_maxpool_layer(int batch, int h, int w, int c, int size, int stride, int padding)
{
=======
maxpool_layer make_maxpool_layer(int batch, int h, int w, int c, int size, int stride)
{
    fprintf(stderr, "Maxpool Layer: %d x %d x %d image, %d size, %d stride\n", h,w,c,size,stride);
>>>>>>> b5b3d7367411302dd6e73c8fe583d6860a786445
=======
maxpool_layer make_maxpool_layer(int batch, int h, int w, int c, int size, int stride)
{
    fprintf(stderr, "Maxpool Layer: %d x %d x %d image, %d size, %d stride\n", h,w,c,size,stride);
>>>>>>> 07267f401b3d9c82c5f695f932c9f504d2b6a592
    maxpool_layer l = {0};
    l.type = MAXPOOL;
    l.batch = batch;
    l.h = h;
    l.w = w;
    l.c = c;
<<<<<<< HEAD
<<<<<<< HEAD
    l.pad = padding;
    l.out_w = (w + 2*padding)/stride;
    l.out_h = (h + 2*padding)/stride;
=======
    l.out_w = (w-1)/stride + 1;
    l.out_h = (h-1)/stride + 1;
>>>>>>> b5b3d7367411302dd6e73c8fe583d6860a786445
=======
    l.out_w = (w-1)/stride + 1;
    l.out_h = (h-1)/stride + 1;
>>>>>>> 07267f401b3d9c82c5f695f932c9f504d2b6a592
    l.out_c = c;
    l.outputs = l.out_h * l.out_w * l.out_c;
    l.inputs = h*w*c;
    l.size = size;
    l.stride = stride;
    int output_size = l.out_h * l.out_w * l.out_c * batch;
    l.indexes = calloc(output_size, sizeof(int));
    l.output =  calloc(output_size, sizeof(float));
    l.delta =   calloc(output_size, sizeof(float));
<<<<<<< HEAD
<<<<<<< HEAD
    l.forward = forward_maxpool_layer;
    l.backward = backward_maxpool_layer;
    #ifdef GPU
    l.forward_gpu = forward_maxpool_layer_gpu;
    l.backward_gpu = backward_maxpool_layer_gpu;
    l.indexes_gpu = cuda_make_int_array(0, output_size);
    l.output_gpu  = cuda_make_array(l.output, output_size);
    l.delta_gpu   = cuda_make_array(l.delta, output_size);
    #endif
    fprintf(stderr, "max          %d x %d / %d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n", size, size, stride, w, h, c, l.out_w, l.out_h, l.out_c);
=======
=======
>>>>>>> 07267f401b3d9c82c5f695f932c9f504d2b6a592
    #ifdef GPU
    l.indexes_gpu = cuda_make_int_array(output_size);
    l.output_gpu  = cuda_make_array(l.output, output_size);
    l.delta_gpu   = cuda_make_array(l.delta, output_size);
    #endif
<<<<<<< HEAD
>>>>>>> b5b3d7367411302dd6e73c8fe583d6860a786445
=======
>>>>>>> 07267f401b3d9c82c5f695f932c9f504d2b6a592
    return l;
}

void resize_maxpool_layer(maxpool_layer *l, int w, int h)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
    int stride = l->stride;
>>>>>>> b5b3d7367411302dd6e73c8fe583d6860a786445
=======
    int stride = l->stride;
>>>>>>> 07267f401b3d9c82c5f695f932c9f504d2b6a592
    l->h = h;
    l->w = w;
    l->inputs = h*w*l->c;

<<<<<<< HEAD
<<<<<<< HEAD
    l->out_w = (w + 2*l->pad)/l->stride;
    l->out_h = (h + 2*l->pad)/l->stride;
=======
    l->out_w = (w-1)/stride + 1;
    l->out_h = (h-1)/stride + 1;
>>>>>>> b5b3d7367411302dd6e73c8fe583d6860a786445
=======
    l->out_w = (w-1)/stride + 1;
    l->out_h = (h-1)/stride + 1;
>>>>>>> 07267f401b3d9c82c5f695f932c9f504d2b6a592
    l->outputs = l->out_w * l->out_h * l->c;
    int output_size = l->outputs * l->batch;

    l->indexes = realloc(l->indexes, output_size * sizeof(int));
    l->output = realloc(l->output, output_size * sizeof(float));
    l->delta = realloc(l->delta, output_size * sizeof(float));

    #ifdef GPU
    cuda_free((float *)l->indexes_gpu);
    cuda_free(l->output_gpu);
    cuda_free(l->delta_gpu);
<<<<<<< HEAD
<<<<<<< HEAD
    l->indexes_gpu = cuda_make_int_array(0, output_size);
=======
    l->indexes_gpu = cuda_make_int_array(output_size);
>>>>>>> b5b3d7367411302dd6e73c8fe583d6860a786445
=======
    l->indexes_gpu = cuda_make_int_array(output_size);
>>>>>>> 07267f401b3d9c82c5f695f932c9f504d2b6a592
    l->output_gpu  = cuda_make_array(l->output, output_size);
    l->delta_gpu   = cuda_make_array(l->delta,  output_size);
    #endif
}

<<<<<<< HEAD
<<<<<<< HEAD
void forward_maxpool_layer(const maxpool_layer l, network net)
{
    int b,i,j,k,m,n;
    int w_offset = -l.pad;
    int h_offset = -l.pad;

    int h = l.out_h;
    int w = l.out_w;
=======
=======
>>>>>>> 07267f401b3d9c82c5f695f932c9f504d2b6a592
void forward_maxpool_layer(const maxpool_layer l, network_state state)
{
    int b,i,j,k,m,n;
    int w_offset = (-l.size-1)/2 + 1;
    int h_offset = (-l.size-1)/2 + 1;

    int h = (l.h-1)/l.stride + 1;
    int w = (l.w-1)/l.stride + 1;
<<<<<<< HEAD
>>>>>>> b5b3d7367411302dd6e73c8fe583d6860a786445
=======
>>>>>>> 07267f401b3d9c82c5f695f932c9f504d2b6a592
    int c = l.c;

    for(b = 0; b < l.batch; ++b){
        for(k = 0; k < c; ++k){
            for(i = 0; i < h; ++i){
                for(j = 0; j < w; ++j){
                    int out_index = j + w*(i + h*(k + c*b));
                    float max = -FLT_MAX;
                    int max_i = -1;
                    for(n = 0; n < l.size; ++n){
                        for(m = 0; m < l.size; ++m){
                            int cur_h = h_offset + i*l.stride + n;
                            int cur_w = w_offset + j*l.stride + m;
                            int index = cur_w + l.w*(cur_h + l.h*(k + b*l.c));
                            int valid = (cur_h >= 0 && cur_h < l.h &&
                                         cur_w >= 0 && cur_w < l.w);
<<<<<<< HEAD
<<<<<<< HEAD
                            float val = (valid != 0) ? net.input[index] : -FLT_MAX;
=======
                            float val = (valid != 0) ? state.input[index] : -FLT_MAX;
>>>>>>> b5b3d7367411302dd6e73c8fe583d6860a786445
=======
                            float val = (valid != 0) ? state.input[index] : -FLT_MAX;
>>>>>>> 07267f401b3d9c82c5f695f932c9f504d2b6a592
                            max_i = (val > max) ? index : max_i;
                            max   = (val > max) ? val   : max;
                        }
                    }
                    l.output[out_index] = max;
                    l.indexes[out_index] = max_i;
                }
            }
        }
    }
}

<<<<<<< HEAD
<<<<<<< HEAD
void backward_maxpool_layer(const maxpool_layer l, network net)
{
    int i;
    int h = l.out_h;
    int w = l.out_w;
    int c = l.c;
    for(i = 0; i < h*w*c*l.batch; ++i){
        int index = l.indexes[i];
        net.delta[index] += l.delta[i];
=======
=======
>>>>>>> 07267f401b3d9c82c5f695f932c9f504d2b6a592
void backward_maxpool_layer(const maxpool_layer l, network_state state)
{
    int i;
    int h = (l.h-1)/l.stride + 1;
    int w = (l.w-1)/l.stride + 1;
    int c = l.c;
    for(i = 0; i < h*w*c*l.batch; ++i){
        int index = l.indexes[i];
        state.delta[index] += l.delta[i];
<<<<<<< HEAD
>>>>>>> b5b3d7367411302dd6e73c8fe583d6860a786445
=======
>>>>>>> 07267f401b3d9c82c5f695f932c9f504d2b6a592
    }
}

