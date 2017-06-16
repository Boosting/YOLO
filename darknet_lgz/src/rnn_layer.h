
<<<<<<< HEAD
#ifndef RNN_LAYER_H
#define RNN_LAYER_H
=======
#ifndef GRU_LAYER_H
#define GRU_LAYER_H
>>>>>>> b5b3d7367411302dd6e73c8fe583d6860a786445

#include "activations.h"
#include "layer.h"
#include "network.h"
<<<<<<< HEAD
#define USET

layer make_rnn_layer(int batch, int inputs, int hidden, int outputs, int steps, ACTIVATION activation, int batch_normalize, int log);

void forward_rnn_layer(layer l, network net);
void backward_rnn_layer(layer l, network net);
void update_rnn_layer(layer l, int batch, float learning_rate, float momentum, float decay);

#ifdef GPU
void forward_rnn_layer_gpu(layer l, network net);
void backward_rnn_layer_gpu(layer l, network net);
void update_rnn_layer_gpu(layer l, int batch, float learning_rate, float momentum, float decay);
void push_rnn_layer(layer l);
void pull_rnn_layer(layer l);
=======

layer make_gru_layer(int batch, int inputs, int outputs, int steps, int batch_normalize);

void forward_gru_layer(layer l, network_state state);
void backward_gru_layer(layer l, network_state state);
void update_gru_layer(layer l, int batch, float learning_rate, float momentum, float decay);

#ifdef GPU
void forward_gru_layer_gpu(layer l, network_state state);
void backward_gru_layer_gpu(layer l, network_state state);
void update_gru_layer_gpu(layer l, int batch, float learning_rate, float momentum, float decay);
void push_gru_layer(layer l);
void pull_gru_layer(layer l);
>>>>>>> b5b3d7367411302dd6e73c8fe583d6860a786445
#endif

#endif

