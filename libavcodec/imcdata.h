/*
 * IMC compatible decoder
 * Copyright (c) 2002-2004 Maxim Poliakovski
 * Copyright (c) 2006 Benjamin Larsson
 * Copyright (c) 2006 Konstantin Shishkov
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVCODEC_IMCDATA_H
#define AVCODEC_IMCDATA_H

#include <stdint.h>

static const uint16_t band_tab[33] = {
      0,   3,   6,   9,  12,  16,  20,  24,  29,  34,  40,
     46,  53,  60,  68,  76,  84,  93, 102, 111, 121, 131,
    141, 151, 162, 173, 184, 195, 207, 219, 231, 243, 256,
};


static const int8_t cyclTab[32] = {
    1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
   12, 13, 14, 15, 16, 17, 18, 20, 21, 22, 23,
   24, 25, 26, 27, 28, 29, 30, 31, 32, 32,
};

static const int8_t cyclTab2[32] = {
   -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
 12, 13, 14, 15, 16, 17, 17, 18, 19, 20, 21, 22,
23, 24, 25, 26, 27, 28, 29};

static const float imc_weights1[31] = {
    0.119595, 0.123124, 0.129192, 9.97377e-2, 8.1923e-2, 9.61153e-2, 8.77885e-2, 8.61174e-2,
    9.00882e-2, 9.91658e-2, 0.112991, 0.131126, 0.152886, 0.177292, 0.221782, 0.244917, 0.267386,
    0.306816, 0.323046, 0.33729, 0.366773, 0.392557, 0.398076, 0.403302, 0.42451, 0.444777,
    0.449188, 0.455445, 0.477853, 0.500669, 0.510395};

static const float imc_weights2[31] = {
    3.23466e-3, 3.49886e-3, 3.98413e-3, 1.98116e-3, 1.16465e-3, 1.79283e-3, 1.40372e-3, 1.33274e-3,
    1.50523e-3, 1.95064e-3, 2.77472e-3, 4.14725e-3, 6.2776e-3, 9.36401e-3, 1.71397e-2, 2.24052e-2,
    2.83971e-2, 4.11689e-2, 4.73165e-2, 5.31631e-2, 6.66614e-2, 8.00824e-2, 8.31588e-2, 8.61397e-2,
    9.89229e-2, 0.112197, 0.115227, 0.119613, 0.136174, 0.15445, 0.162685};

static const float imc_quantizer1[4][8] = {
    { 8.4431201e-1, 4.7358301e-1, 1.448354, 2.7073899e-1, 7.4449003e-1, 1.241991,  1.845484,  0.0},
    { 8.6876702e-1, 4.7659001e-1, 1.478224, 2.5672799e-1, 7.55777e-1,   1.3229851, 2.03438,   0.0},
    { 7.5891501e-1, 6.2272799e-1, 1.271322, 3.47904e-1,   7.5317699e-1, 1.150767,  1.628476,  0.0},
    { 7.65257e-1,   6.44647e-1,   1.263824, 3.4548101e-1, 7.6384902e-1, 1.214466,  1.7638789, 0.0},
};

static const float imc_quantizer2[2][56] = {
    { 1.39236e-1, 3.50548e-1, 5.9547901e-1, 8.5772401e-1, 1.121545, 1.3882281, 1.695882, 2.1270809,
      7.2221003e-2, 1.85177e-1, 2.9521701e-1, 4.12568e-1, 5.4068601e-1, 6.7679501e-1, 8.1196898e-1, 9.4765198e-1,
      1.0779999, 1.203415, 1.337265, 1.481871, 1.639982, 1.814766, 2.0701399, 2.449862,
      3.7533998e-2, 1.02722e-1, 1.6021401e-1, 2.16043e-1, 2.7231601e-1, 3.3025399e-1, 3.9022601e-1, 4.52849e-1,
      5.1794899e-1, 5.8529502e-1, 6.53956e-1, 7.2312802e-1, 7.9150802e-1, 8.5891002e-1, 9.28141e-1, 9.9706203e-1,
      1.062153, 1.12564, 1.189834, 1.256122, 1.324469, 1.3955311, 1.468906, 1.545084,
      1.6264729, 1.711524, 1.802705, 1.91023, 2.0533991, 2.22333, 2.4830019, 3.253329 },
    { 1.11654e-1, 3.54469e-1, 6.4232099e-1, 9.6128798e-1, 1.295053, 1.61777, 1.989839, 2.51107,
      5.7721999e-2, 1.69879e-1, 2.97589e-1, 4.3858799e-1, 5.9039903e-1, 7.4934798e-1, 9.1628098e-1, 1.087297,
      1.262751, 1.4288321, 1.6040879, 1.79067, 2.000668, 2.2394669, 2.649332, 5.2760072,
      2.9722e-2, 8.7316997e-2, 1.4445201e-1, 2.04247e-1, 2.6879501e-1, 3.3716801e-1, 4.08811e-1, 4.8306999e-1,
      5.6049401e-1, 6.3955498e-1, 7.2044599e-1, 8.0427998e-1, 8.8933599e-1, 9.7537601e-1, 1.062461, 1.1510431,
      1.240236, 1.326715, 1.412513, 1.500502, 1.591749, 1.686413, 1.785239, 1.891233,
      2.0051291, 2.127681, 2.2709141, 2.475826, 2.7219379, 3.101985, 4.686213, 6.2287788},
};


static const float xTab[14] = {7.6, 3.6, 4.4, 3.7, 6.1, 5.1, 2.3, 1.6, 6.2, 1.5, 1.8, 1.2, 0, 0}; //10014048

/* precomputed table for 10^(i/4), i=-15..16 */
static const float imc_exp_tab[32] = {
    1.778280e-4, 3.162278e-4, 5.623413e-4, 1.000000e-3,
    1.778280e-3, 3.162278e-3, 5.623413e-3, 1.000000e-2,
    1.778280e-2, 3.162278e-2, 5.623413e-2, 1.000000e-1,
    1.778280e-1, 3.162278e-1, 5.623413e-1, 1.000000e00,
    1.778280e00, 3.162278e00, 5.623413e00, 1.000000e01,
    1.778280e01, 3.162278e01, 5.623413e01, 1.000000e02,
    1.778280e02, 3.162278e02, 5.623413e02, 1.000000e03,
    1.778280e03, 3.162278e03, 5.623413e03, 1.000000e04
};
static const float * const imc_exp_tab2 = imc_exp_tab + 8;


static const uint8_t imc_cb_select[4][32] = {
    { 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2 },
    { 0, 2, 0, 3, 2, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2 },
    { 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

static const uint8_t imc_huffman_sizes[4] = {
    17,  17,  18,  18
};

static const uint8_t imc_huffman_lens[4][4][18] = {
    {
        { 1,  2,  5,  6, 11, 12, 15, 16, 16, 14, 13, 10,  9,  8,  7,  4,  3 },
        { 2,  3,  3,  4,  4,  4,  6,  6,  7,  7,  7,  8,  9, 10, 11, 11,  2 },
        { 1,  4,  4,  7,  9, 10, 12, 15, 15, 14, 13, 11,  8,  6,  5,  4,  2 },
        { 2,  2,  4,  8,  9, 14, 15, 15, 13, 12, 11, 10,  7,  6,  5,  3,  2 },
    },
    {
        { 2,  2,  3,  4,  7,  7, 10, 11, 12, 14, 14, 13,  9,  8,  7,  5,  2 },
        { 2,  3, 14, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  3,  2 },
        { 2,  3,  3,  4,  4,  5,  7,  9, 11, 12, 13, 13, 10,  8,  6,  4,  2 },
        { 2,  3,  3,  4,  4,  5,  7,  9, 11, 12, 13, 13, 10,  8,  6,  4,  2 },
    },
    {
        { 3,  5,  8,  9, 12, 15, 17, 17, 16, 14, 13, 11, 10,  7,  6,  4,  2,  1 },
        { 4,  7,  8, 10, 11, 12, 15, 16, 16, 14, 13,  9,  6,  5,  3,  2,  2,  2 },
        { 4,  5,  6,  7, 12, 13, 17, 17, 16, 15, 14, 11, 10,  9,  8,  3,  2,  1 },
        { 2,  5,  7,  8, 14, 15, 16, 16, 13, 12, 11, 10,  9,  6,  4,  3,  2,  2 },
    },
    {
        { 2,  4,  7,  9, 10, 12, 13, 15, 16, 16, 14, 11,  8,  6,  5,  3,  2,  2 },
        { 3,  5,  5,  7, 10, 11, 11,  9,  8,  6,  5,  4,  4,  3,  3,  3,  3,  3 },
        { 5,  8,  9,  9,  7,  6,  6,  6,  5,  5,  5,  4,  4,  4,  3,  3,  3,  2 },
        { 2,  3,  5,  7,  8, 11, 12, 13, 15, 15, 14, 10,  9,  6,  4,  3,  3,  2 },
    }
};

static const uint8_t imc_huffman_syms[4][4][18] = {
    {
        {  7,  8,  5, 10,  3, 13,  1,  0, 15, 14,  2, 12, 11,  4, 16,  9,  6 },
        {  8,  9,  6, 10,  5,  4, 11,  3, 16, 12,  2,  1, 13,  0, 14, 15,  7 },
        {  8,  6,  9, 11, 12, 13, 14,  1,  0,  2, 15,  3,  4,  5, 10, 16,  7 },
        {  8,  6,  5,  3, 12, 16, 15, 14,  0, 13,  1,  2, 11,  4, 10,  9,  7 },
    },
    {
        {  8,  7,  9,  5, 16,  4,  2, 13,  1, 15,  0, 14, 12,  3, 11, 10,  6 },
        {  8, 16,  0, 15,  1, 14,  2, 13, 12,  3, 11,  4, 10,  5,  6,  9,  7 },
        {  8,  6,  9, 10, 16,  4,  3, 13, 14,  1,  0, 15,  2, 12, 11,  5,  7 },
        {  8,  6,  9, 10, 16,  4,  3, 13, 14,  1,  0, 15,  2, 12, 11,  5,  7 },
    },
    {
        {  6,  5,  4, 11,  2, 14, 15, 17,  0,  1, 13, 12,  3, 10, 16,  9,  8,  7 },
        {  5, 11,  3, 12,  2, 13,  0, 17, 15, 14,  1, 16,  4, 10,  9,  6,  7,  8 },
        { 16,  9,  5, 10,  1, 12, 15, 17, 14, 13,  0,  2, 11,  3,  4,  6,  8,  7 },
        {  8,  5,  4, 12,  1, 15,  0, 17, 14,  2, 13, 16,  3, 11, 10,  9,  6,  7 },
    },
    {
        {  7,  9,  4, 11,  2, 12,  0, 14, 17, 15, 13,  1,  3, 10,  5, 16,  8,  6 },
        {  8, 17, 15,  5,  2,  1,  0,  3,  4, 16,  6,  7, 14, 13,  9, 10, 12, 11 },
        {  4, 16,  0,  1,  2,  3, 17, 15, 14, 13, 11,  5, 12, 10,  9,  7,  6,  8 },
        {  7,  9,  4, 11,  3, 13,  1,  0, 15, 17, 14,  2, 12, 16, 10,  6,  5,  8 },
    }
};

#endif /* AVCODEC_IMCDATA_H */
