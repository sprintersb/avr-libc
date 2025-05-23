/* Copyright (c) 2007  Dmitry Xmelkov
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE. */

/* Test of cosh() function. 500 random cases. */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "progmem.h"

union lofl_u {
    long lo;
    float fl;
};

volatile union lofl_u v = { .lo = 1 };

PROGMEM const struct {		/* Table of test cases.	*/
    long x;		/* argument	*/
    long z;		/* cosh(x)	*/
} t[] = {

    /* x, cosh(x)	*/
    { 0x3bd4fd3e,0x3f8000b1 }, /*   1:  6.4999154e-03  1.0000211e+00 */
    { 0xbf087c11,0x3f92a060 }, /*   2: -5.3314310e-01  1.1455193e+00 */
    { 0x3af4b529,0x3f80000f }, /*   3:  1.8669713e-03  1.0000018e+00 */
    { 0xc148d777,0x480a19d6 }, /*   4: -1.2552604e+01  1.4141534e+05 */
    { 0x3f661849,0x3fb74751 }, /*   5:  8.9880806e-01  1.4318639e+00 */
    { 0x41489dce,0x48082ba4 }, /*   6:  1.2538527e+01  1.3943856e+05 */
    { 0xbfdb4eb0,0x40374972 }, /*   7: -1.7133389e+00  2.8638577e+00 */
    { 0xbf38945e,0x3fa2bcd9 }, /*   8: -7.2101390e-01  1.2713882e+00 */
    { 0x3f70963d,0x3fbccf68 }, /*   9:  9.3979245e-01  1.4750795e+00 */
    { 0x3fdd8cfe,0x403a534b }, /*  10:  1.7308652e+00  2.9113338e+00 */
    { 0xbf66dcb3,0x3fb7ac2b }, /*  11: -9.0180510e-01  1.4349416e+00 */
    { 0x3f2442b5,0x3f9b4402 }, /*  12:  6.4164287e-01  1.2130129e+00 */
    { 0xba89cc87,0x3f800005 }, /*  13: -1.0513224e-03  1.0000006e+00 */
    { 0xbece4a5d,0x3f8a87e9 }, /*  14: -4.0291110e-01  1.0822726e+00 */
    { 0x40263327,0x40d7f06c }, /*  15:  2.5968721e+00  6.7480984e+00 */
    { 0xbf67fddd,0x3fb8416b }, /*  16: -9.0621740e-01  1.4394964e+00 */
    { 0x4040ce4c,0x41231d17 }, /*  17:  3.0125914e+00  1.0194602e+01 */
    { 0x3edf38ab,0x3f8c5be1 }, /*  18:  4.3597922e-01  1.0965539e+00 */
    { 0x408ab796,0x4218a996 }, /*  19:  4.3349104e+00  3.8165611e+01 */
    { 0xc0aeaf89,0x42ead986 }, /*  20: -5.4589276e+00  1.1742485e+02 */
    { 0x3f6ce357,0x3fbad30a }, /*  21:  9.2534393e-01  1.4595654e+00 */
    { 0xc1ada9bc,0x4e9f8c54 }, /*  22: -2.1707878e+01  1.3383869e+09 */
    { 0xbe54c0bc,0x3f82c5cb }, /*  23: -2.0776647e-01  1.0216612e+00 */
    { 0xbed282ff,0x3f8af8f0 }, /*  24: -4.1115567e-01  1.0857220e+00 */
    { 0x3ec7ed6d,0x3f89e217 }, /*  25:  3.9048329e-01  1.0772122e+00 */
    { 0xbef0f5f1,0x3f8e705b }, /*  26: -4.7062638e-01  1.1128038e+00 */
    { 0x3e3a101d,0x3f821e6b }, /*  27:  1.8170209e-01  1.0165533e+00 */
    { 0x3fa4d9a0,0x3ff9a9c3 }, /*  28:  1.2878914e+00  1.9504932e+00 */
    { 0x3f4406bd,0x3fa7653e }, /*  29:  7.6572782e-01  1.3077772e+00 */
    { 0xc01c51c1,0x40b96ada }, /*  30: -2.4424899e+00  5.7942934e+00 */
    { 0x40060313,0x4083d719 }, /*  31:  2.0939376e+00  4.1200070e+00 */
    { 0x421f0694,0x5ba3de5d }, /*  32:  3.9756424e+01  9.2249824e+16 */
    { 0x3f9acd18,0x3fe99655 }, /*  33:  1.2093840e+00  1.8249003e+00 */
    { 0xbecc0b14,0x3f8a4cba }, /*  34: -3.9852202e-01  1.0804665e+00 */
    { 0xc004c46d,0x408160a8 }, /*  35: -2.0744889e+00  4.0430489e+00 */
    { 0xbf66896c,0x3fb7815b }, /*  36: -9.0053439e-01  1.4336351e+00 */
    { 0x3f2cc200,0x3f9e44cf }, /*  37:  6.7483521e-01  1.2364749e+00 */
    { 0x3fdc2bf8,0x4038736f }, /*  38:  1.7200918e+00  2.8820455e+00 */
    { 0x3fe61cd7,0x404674c1 }, /*  39:  1.7977551e+00  3.1008761e+00 */
    { 0x3ff7a7fd,0x40622692 }, /*  40:  1.9348141e+00  3.5336041e+00 */
    { 0x3edbbe7e,0x3f8bf894 }, /*  41:  4.2918772e-01  1.0935235e+00 */
    { 0x3f9f387c,0x3ff07969 }, /*  42:  1.2439113e+00  1.8787051e+00 */
    { 0x3f14847f,0x3f9626c7 }, /*  43:  5.8014673e-01  1.1730584e+00 */
    { 0xbfbd6c7c,0x4013d77e }, /*  44: -1.4798732e+00  2.3100276e+00 */
    { 0x3fec1aad,0x404f784f }, /*  45:  1.8445641e+00  3.2417181e+00 */
    { 0xc070d1dd,0x41ac5ead }, /*  46: -3.7628090e+00  2.1546228e+01 */
    { 0x3f5cc689,0x3fb29fab }, /*  47:  8.6240441e-01  1.3954977e+00 */
    { 0xbe4bd790,0x3f828b64 }, /*  48: -1.9906449e-01  1.0198789e+00 */
    { 0x3f1a60e3,0x3f97fcf1 }, /*  49:  6.0304087e-01  1.1874067e+00 */
    { 0x3fa133ce,0x3ff3a7b0 }, /*  50:  1.2593935e+00  1.9035549e+00 */
    { 0xbfa01f57,0x3ff1ea1b }, /*  51: -1.2509564e+00  1.8899568e+00 */
    { 0x3fe37fb6,0x4042a944 }, /*  52:  1.7773349e+00  3.0415812e+00 */
    { 0xbe2565cb,0x3f81ac60 }, /*  53: -1.6152112e-01  1.0130730e+00 */
    { 0x41a09477,0x4d78bd09 }, /*  54:  2.0072493e+01  2.6082114e+08 */
    { 0xbf8f3cc2,0x3fd8dd5e }, /*  55: -1.1190417e+00  1.6942556e+00 */
    { 0x3f216a9a,0x3f9a4c81 }, /*  56:  6.3053286e-01  1.2054597e+00 */
    { 0xbeb52a7d,0x3f8818d0 }, /*  57: -3.5383978e-01  1.0632572e+00 */
    { 0x3f6a3778,0x3fb96a1a }, /*  58:  9.1490889e-01  1.4485505e+00 */
    { 0x3ffae25a,0x4067b177 }, /*  59:  1.9600327e+00  3.6202066e+00 */
    { 0x3f9b4e9a,0x3fea5c7f }, /*  60:  1.2133362e+00  1.8309478e+00 */
    { 0x41b0a9fd,0x4ee82b84 }, /*  61:  2.2083002e+01  1.9475830e+09 */
    { 0xbf580683,0x3fb057b2 }, /*  62: -8.4384936e-01  1.3776762e+00 */
    { 0xc03f7128,0x411fb0f5 }, /*  63: -2.9912815e+00  9.9807024e+00 */
    { 0x3fa5f5d5,0x3ffb881d }, /*  64:  1.2965647e+00  1.9650913e+00 */
    { 0x3f800000,0x3fc583ab }, /*  65:  1.0000000e+00  1.5430807e+00 */
    { 0xb75654e4,0x3f800000 }, /*  66: -1.2775159e-05  1.0000000e+00 */
    { 0xbf9470e6,0x3fe029ac }, /*  67: -1.1596954e+00  1.7512717e+00 */
    { 0x3f200056,0x3f99d32d }, /*  68:  6.2500513e-01  1.2017571e+00 */
    { 0xbf44d94d,0x3fa7be32 }, /*  69: -7.6894075e-01  1.3104918e+00 */
    { 0xbf694305,0x3fb8ea57 }, /*  70: -9.1117889e-01  1.4446515e+00 */
    { 0xbeaf8843,0x3f8798a9 }, /*  71: -3.4283647e-01  1.0593463e+00 */
    { 0x3d4b1c4d,0x3f80284c }, /*  72:  4.9587537e-02  1.0012298e+00 */
    { 0x3f33ef53,0x3fa0f0e7 }, /*  73:  7.0287055e-01  1.2573518e+00 */
    { 0x3f1deb87,0x3f9922eb }, /*  74:  6.1687511e-01  1.1963781e+00 */
    { 0xbfd7f756,0x4032dd98 }, /*  75: -1.6872356e+00  2.7947750e+00 */
    { 0x3ea3019f,0x3f868ac4 }, /*  76:  3.1837174e-01  1.0511098e+00 */
    { 0xbf418e32,0x3fa65cb0 }, /*  77: -7.5607598e-01  1.2997036e+00 */
    { 0xbf9cd74c,0x3fecbb1c }, /*  78: -1.2253203e+00  1.8494601e+00 */
    { 0xbd062a3c,0x3f801194 }, /*  79: -3.2755122e-02  1.0005364e+00 */
    { 0xbf40fed5,0x3fa62147 }, /*  80: -7.5388843e-01  1.2978905e+00 */
    { 0xbf31a2f0,0x3fa01254 }, /*  81: -6.9389248e-01  1.2505593e+00 */
    { 0x3d91d080,0x3f805317 }, /*  82:  7.1198463e-02  1.0025357e+00 */
    { 0x3f6e8948,0x3fbbb454 }, /*  83:  9.3178225e-01  1.4664407e+00 */
    { 0x3f1c9b79,0x3f98b515 }, /*  84:  6.1174732e-01  1.1930262e+00 */
    { 0x3f1d900c,0x3f9904eb }, /*  85:  6.1547923e-01  1.1954626e+00 */
    { 0xbf24865f,0x3f9b5b42 }, /*  86: -6.4267534e-01  1.2137225e+00 */
    { 0xbf6780dd,0x3fb800ca }, /*  87: -9.0431005e-01  1.4375241e+00 */
    { 0xbedce0d7,0x3f8c18c9 }, /*  88: -4.3140289e-01  1.0945064e+00 */
    { 0xc23d19d2,0x611369b0 }, /*  89: -4.7275215e+01  1.6995544e+20 */
    { 0x3db08590,0x3f8079cb }, /*  90:  8.6192250e-02  1.0037168e+00 */
    { 0xbfa24d35,0x3ff571ca }, /*  91: -1.2679812e+00  1.9175351e+00 */
    { 0xbf0e075b,0x3f9435bb }, /*  92: -5.5479974e-01  1.1578897e+00 */
    { 0xbeb42723,0x3f880175 }, /*  93: -3.5186109e-01  1.0625445e+00 */
    { 0x3c5ae288,0x3f8002ed }, /*  94:  1.3359673e-02  1.0000893e+00 */
    { 0x3f3f73d0,0x3fa57ea4 }, /*  95:  7.4786091e-01  1.2929273e+00 */
    { 0x4115ec51,0x45b75596 }, /*  96:  9.3701944e+00  5.8666982e+03 */
    { 0xbf8e6911,0x3fd7bd00 }, /*  97: -1.1125814e+00  1.6854553e+00 */
    { 0xbefb8a0f,0x3f8fc2af }, /*  98: -4.9128768e-01  1.1231288e+00 */
    { 0xc0abf70c,0x42d7b569 }, /*  99: -5.3739071e+00  1.0785432e+02 */
    { 0xbfbc088e,0x40126721 }, /* 100: -1.4690111e+00  2.2875445e+00 */
    { 0xc069b6b2,0x419a46a7 }, /* 101: -3.6517758e+00  1.9284498e+01 */
    { 0xc01678f0,0x40a97bb5 }, /* 102: -2.3511314e+00  5.2963510e+00 */
    { 0xbed17c2a,0x3f8add3a }, /* 103: -4.0915042e-01  1.0848763e+00 */
    { 0x3f10e17d,0x3f950d2e }, /* 104:  5.6594068e-01  1.1644647e+00 */
    { 0x3f35ea69,0x3fa1b362 }, /* 105:  7.1060807e-01  1.2632868e+00 */
    { 0xbff198eb,0x4058220d }, /* 106: -1.8874792e+00  3.3770783e+00 */
    { 0x3f71b11d,0x3fbd693a }, /* 107:  9.4410878e-01  1.4797738e+00 */
    { 0xbf994447,0x3fe742f9 }, /* 108: -1.1973962e+00  1.8067313e+00 */
    { 0x4010ff4c,0x409bd919 }, /* 109:  2.2655821e+00  4.8702512e+00 */
    { 0xbf09ce7f,0x3f92ff6d }, /* 110: -5.3830713e-01  1.1484200e+00 */
    { 0x405d95fc,0x417f5e15 }, /* 111:  3.4622793e+00  1.5960469e+01 */
    { 0x3f08d761,0x3f92b9ec }, /* 112:  5.3453642e-01  1.1462989e+00 */
    { 0x4196f625,0x4c957e00 }, /* 113:  1.8870188e+01  7.8376960e+07 */
    { 0xbf655f2c,0x3fb6e8a6 }, /* 114: -8.9598346e-01  1.4289749e+00 */
    { 0x3f5c3ef1,0x3fb25dc7 }, /* 115:  8.6033541e-01  1.3934869e+00 */
    { 0xbf94e607,0x3fe0d26f }, /* 116: -1.1632699e+00  1.7564219e+00 */
    { 0x3d997ada,0x3f805c0f }, /* 117:  7.4941352e-02  1.0028094e+00 */
    { 0xbef1a80e,0x3f8e8621 }, /* 118: -4.7198528e-01  1.1134683e+00 */
    { 0xbfa08c1b,0x3ff298e1 }, /* 119: -1.2542757e+00  1.8952905e+00 */
    { 0x3f20802a,0x3f99fdda }, /* 120:  6.2695563e-01  1.2030594e+00 */
    { 0xbf7863d6,0x3fc12119 }, /* 121: -9.7027338e-01  1.5088226e+00 */
    { 0xbed18ff8,0x3f8adf4f }, /* 122: -4.0930152e-01  1.0849398e+00 */
    { 0x3f675e88,0x3fb7ef11 }, /* 123:  9.0378618e-01  1.4369832e+00 */
    { 0x400b6d11,0x408f2503 }, /* 124:  2.1785319e+00  4.4732680e+00 */
    { 0xc1465816,0x47ec48a6 }, /* 125: -1.2396505e+01  1.2097730e+05 */
    { 0xbf9e5072,0x3fef09e8 }, /* 126: -1.2368300e+00  1.8674898e+00 */
    { 0xbf9b9db6,0x3fead601 }, /* 127: -1.2157505e+00  1.8346559e+00 */
    { 0x3fc534e2,0x401c3933 }, /* 128:  1.5406764e+00  2.4409912e+00 */
    { 0xbfe20c0d,0x404096aa }, /* 129: -1.7659928e+00  3.0091958e+00 */
    { 0xbf9d7d18,0x3fedbdd6 }, /* 130: -1.2303801e+00  1.8573558e+00 */
    { 0xbf080f51,0x3f92820b }, /* 131: -5.3148371e-01  1.1445936e+00 */
    { 0x3f9eac7b,0x3fef9b4d }, /* 132:  1.2396387e+00  1.8719269e+00 */
    { 0x3af637a6,0x3f80000f }, /* 133:  1.8784895e-03  1.0000018e+00 */
    { 0x3f9a77b8,0x3fe91435 }, /* 134:  1.2067785e+00  1.8209292e+00 */
    { 0xbf64de38,0x3fb6a6ed }, /* 135: -8.9401579e-01  1.4269692e+00 */
    { 0xbecdc625,0x3f8a7a40 }, /* 136: -4.0190235e-01  1.0818558e+00 */
    { 0x3f68d38a,0x3fb8b04b }, /* 137:  9.0947783e-01  1.4428800e+00 */
    { 0xbfca72ef,0x40223160 }, /* 138: -1.5816325e+00  2.5342636e+00 */
    { 0xbf71fb4b,0x3fbd91b7 }, /* 139: -9.4524068e-01  1.4810094e+00 */
    { 0xbf2d3f0b,0x3f9e7259 }, /* 140: -6.7674321e-01  1.2378646e+00 */
    { 0x4017035b,0x40aae538 }, /* 141:  2.3595798e+00  5.3404808e+00 */
    { 0xbf9a5ee8,0x3fe8ee77 }, /* 142: -1.2060213e+00  1.8197774e+00 */
    { 0xbf99d2f9,0x3fe81a41 }, /* 143: -1.2017509e+00  1.8133012e+00 */
    { 0xc015a983,0x40a763c0 }, /* 144: -2.3384712e+00  5.2309265e+00 */
    { 0x3f9b0084,0x3fe9e4e7 }, /* 145:  1.2109532e+00  1.8272980e+00 */
    { 0x3ef0c177,0x3f8e69f4 }, /* 146:  4.7022602e-01  1.1126084e+00 */
    { 0xbf707f8b,0x3fbcc31b }, /* 147: -9.3944615e-01  1.4747041e+00 */
    { 0x3e97b4db,0x3f85a8fc }, /* 148:  2.9630169e-01  1.0442195e+00 */
    { 0x3f685ee7,0x3fb873b5 }, /* 149:  9.0769809e-01  1.4410311e+00 */
    { 0xbf657204,0x3fb6f245 }, /* 150: -8.9627099e-01  1.4292685e+00 */
    { 0xbed0f635,0x3f8acf28 }, /* 151: -4.0812841e-01  1.0844469e+00 */
    { 0x3f3f7254,0x3fa57e08 }, /* 152:  7.4783826e-01  1.2929087e+00 */
    { 0xbef26971,0x3f8e9dd8 }, /* 153: -4.7346070e-01  1.1141920e+00 */
    { 0x3f995c0e,0x3fe766c4 }, /* 154:  1.1981218e+00  1.8078237e+00 */
    { 0xbf613863,0x3fb4d05a }, /* 155: -8.7976664e-01  1.4126084e+00 */
    { 0xbfc652ac,0x401d78eb }, /* 156: -1.5493979e+00  2.4605052e+00 */
    { 0x40b1be60,0x4301330c }, /* 157:  5.5544891e+00  1.2919940e+02 */
    { 0x42a32de3,0x79d13acd }, /* 158:  8.1589622e+01  1.3579783e+35 */
    { 0x3c94a335,0x3f800565 }, /* 159:  1.8144229e-02  1.0001646e+00 */
    { 0xc0106c4c,0x409a7c5c }, /* 160: -2.2566099e+00  4.8276806e+00 */
    { 0xbf6d40e9,0x3fbb04d4 }, /* 161: -9.2677170e-01  1.4610848e+00 */
    { 0x3f1962dc,0x3f97abea }, /* 162:  5.9916472e-01  1.1849339e+00 */
    { 0xbf389656,0x3fa2bd9e }, /* 163: -7.2104394e-01  1.2714117e+00 */
    { 0xbfe0f6cb,0x403f0ef8 }, /* 164: -1.7575315e+00  2.9852886e+00 */
    { 0xbf2376a4,0x3f9afe26 }, /* 165: -6.3852906e-01  1.2108810e+00 */
    { 0xc02de3ab,0x40f33842 }, /* 166: -2.7170208e+00  7.6006174e+00 */
    { 0xc0757f21,0x41b96c83 }, /* 167: -3.8358843e+00  2.3177984e+01 */
    { 0x3f91a2e9,0x3fdc2f1f }, /* 168:  1.1377841e+00  1.7201880e+00 */
    { 0x3ee171e5,0x3f8c9c3f }, /* 169:  4.4032207e-01  1.0985183e+00 */
    { 0xbff13d4a,0x40578e7d }, /* 170: -1.8846829e+00  3.3680718e+00 */
    { 0xbf67f43c,0x3fb83c6f }, /* 171: -9.0607047e-01  1.4393443e+00 */
    { 0x3ed5a995,0x3f8b4ee0 }, /* 172:  4.1730943e-01  1.0883446e+00 */
    { 0xbb46ec0c,0x3f800027 }, /* 173: -3.0353097e-03  1.0000046e+00 */
    { 0xbfe767e9,0x40485d3d }, /* 174: -1.8078586e+00  3.1306908e+00 */
    { 0x3f241ffd,0x3f9b3819 }, /* 175:  6.4111310e-01  1.2126495e+00 */
    { 0xbf90b395,0x3fdae1a5 }, /* 176: -1.1304804e+00  1.7100111e+00 */
    { 0xbe92079a,0x3f853dda }, /* 177: -2.8521425e-01  1.0409501e+00 */
    { 0x403b7003,0x41160e4e }, /* 178:  2.9287117e+00  9.3784924e+00 */
    { 0xbfc12059,0x4017c25d }, /* 179: -1.5087997e+00  2.3712380e+00 */
    { 0x3f0f0b85,0x3f9481f5 }, /* 180:  5.5876952e-01  1.1602160e+00 */
    { 0x3f96ef65,0x3fe3ca95 }, /* 181:  1.1791807e+00  1.7796198e+00 */
    { 0xbeee2152,0x3f8e1879 }, /* 182: -4.6509796e-01  1.1101218e+00 */
    { 0x3f644795,0x3fb65a60 }, /* 183:  8.9171726e-01  1.4246330e+00 */
    { 0x3ee16552,0x3f8c9ad1 }, /* 184:  4.4022614e-01  1.0984746e+00 */
    { 0xbd113c42,0x3f80149a }, /* 185: -3.5457857e-02  1.0006287e+00 */
    { 0xbf979a25,0x3fe4c6bc }, /* 186: -1.1843916e+00  1.7873149e+00 */
    { 0xbfd930c4,0x403478ae }, /* 187: -1.6968007e+00  2.8198657e+00 */
    { 0xc05e4421,0x41810ba4 }, /* 188: -3.4729083e+00  1.6130684e+01 */
    { 0x3fa13837,0x3ff3aed5 }, /* 189:  1.2595280e+00  1.9037730e+00 */
    { 0x3f9bf9c8,0x3feb63dc }, /* 190:  1.2185602e+00  1.8389850e+00 */
    { 0x3f6b2f91,0x3fb9ec72 }, /* 191:  9.1869456e-01  1.4525282e+00 */
    { 0xbf4579bf,0x3fa80245 }, /* 192: -7.7138895e-01  1.3125693e+00 */
    { 0xc25b7ab4,0x668f0e1f }, /* 193: -5.4869827e+01  3.3777945e+23 */
    { 0xbec48f60,0x3f898c8c }, /* 194: -3.8390636e-01  1.0746017e+00 */
    { 0x3f39005e,0x3fa2e74d }, /* 195:  7.2266185e-01  1.2726837e+00 */
    { 0xbf3fe677,0x3fa5adb0 }, /* 196: -7.4961036e-01  1.2943630e+00 */
    { 0x3fe3f2c0,0x40434ecc }, /* 197:  1.7808456e+00  3.0516844e+00 */
    { 0x3f1f6696,0x3f99a00c }, /* 198:  6.2265909e-01  1.2001967e+00 */
    { 0x3f6cec31,0x3fbad7bf }, /* 199:  9.2547899e-01  1.4597090e+00 */
    { 0x3f64a4a5,0x3fb689a3 }, /* 200:  8.9313728e-01  1.4260753e+00 */
    { 0x4000cebb,0x4073ba86 }, /* 201:  2.0126178e+00  3.8082595e+00 */
    { 0xbe5b8372,0x3f82f3cc }, /* 202: -2.1436861e-01  1.0230651e+00 */
    { 0x3f3b2eb7,0x3fa3c497 }, /* 203:  7.3118156e-01  1.2794369e+00 */
    { 0x4076f836,0x41bdbca9 }, /* 204:  3.8588996e+00  2.3717119e+01 */
    { 0xbed9e954,0x3f8bc4e9 }, /* 205: -4.2560828e-01  1.0919467e+00 */
    { 0xbf9d38a8,0x3fed52da }, /* 206: -1.2282915e+00  1.8540909e+00 */
    { 0x3f709291,0x3fbccd6a }, /* 207:  9.3973643e-01  1.4750187e+00 */
    { 0x41887f41,0x4b441a0c }, /* 208:  1.7062136e+01  1.2851724e+07 */
    { 0x3fd73a99,0x4031e813 }, /* 209:  1.6814758e+00  2.7797897e+00 */
    { 0x3f91dbda,0x3fdc7ee7 }, /* 210:  1.1395218e+00  1.7226228e+00 */
    { 0xbf3be719,0x3fa40e55 }, /* 211: -7.3399502e-01  1.2816874e+00 */
    { 0x3fe4a4d4,0x40445041 }, /* 212:  1.7862802e+00  3.0673983e+00 */
    { 0x3f0022e3,0x3f905f24 }, /* 213:  5.0053233e-01  1.1279035e+00 */
    { 0x3eb3bb54,0x3f87f7c9 }, /* 214:  3.5103858e-01  1.0622493e+00 */
    { 0xbff6b1b8,0x406086e1 }, /* 215: -1.9272985e+00  3.5082324e+00 */
    { 0xbefe720c,0x3f902260 }, /* 216: -4.9696386e-01  1.1260490e+00 */
    { 0x3f98ccc6,0x3fe68f8a }, /* 217:  1.1937492e+00  1.8012555e+00 */
    { 0xbb7b058b,0x3f80003e }, /* 218: -3.8302864e-03  1.0000074e+00 */
    { 0x3f0a2bed,0x3f9319d8 }, /* 219:  5.3973275e-01  1.1492262e+00 */
    { 0x3f97cab4,0x3fe50ebc }, /* 220:  1.1858735e+00  1.7895122e+00 */
    { 0x3f687417,0x3fb87eb4 }, /* 221:  9.0802139e-01  1.4413667e+00 */
    { 0xbffe46c7,0x406dad40 }, /* 222: -1.9865350e+00  3.7136993e+00 */
    { 0x3f9ecfec,0x3fefd36c }, /* 223:  1.2407203e+00  1.8736396e+00 */
    { 0x3da7988c,0x3f806dc8 }, /* 224:  8.1833929e-02  1.0033503e+00 */
    { 0xc01940bf,0x40b0e055 }, /* 225: -2.3945768e+00  5.5273843e+00 */
    { 0xbfc89ea2,0x40201459 }, /* 226: -1.5673411e+00  2.5012419e+00 */
    { 0x400dc754,0x40945f04 }, /* 227:  2.2152910e+00  4.6365986e+00 */
    { 0x3f99be63,0x3fe7fb21 }, /* 228:  1.2011226e+00  1.8123513e+00 */
    { 0xbfc88bd0,0x401ffec8 }, /* 229: -1.5667667e+00  2.4999256e+00 */
    { 0xbeb7adf9,0x3f885359 }, /* 230: -3.5874918e-01  1.0650436e+00 */
    { 0x3f3290b3,0x3fa06bde }, /* 231:  6.9752043e-01  1.2532918e+00 */
    { 0x3f630117,0x3fb5b550 }, /* 232:  8.8673538e-01  1.4195957e+00 */
    { 0x3f223676,0x3f9a914f }, /* 233:  6.3364351e-01  1.2075595e+00 */
    { 0xbf745310,0x3fbedb5a }, /* 234: -9.5439243e-01  1.4910691e+00 */
    { 0xbf90d966,0x3fdb1623 }, /* 235: -1.1316345e+00  1.7116131e+00 */
    { 0x404e9694,0x414a2368 }, /* 236:  3.2279406e+00  1.2633644e+01 */
    { 0x3f026727,0x3f90f7f4 }, /* 237:  5.0938648e-01  1.1325669e+00 */
    { 0xbf71f868,0x3fbd9023 }, /* 238: -9.4519663e-01  1.4809612e+00 */
    { 0x407341b4,0x41b30d70 }, /* 239:  3.8008852e+00  2.2381561e+01 */
    { 0xc13ef65f,0x4794f5be }, /* 240: -1.1935149e+01  7.6267484e+04 */
    { 0xc2a87abf,0x7bb91c9e }, /* 241: -8.4239738e+01  1.9223107e+36 */
    { 0x3fe35e93,0x404279b3 }, /* 242:  1.7763237e+00  3.0386779e+00 */
    { 0xbf939c63,0x3fdef95a }, /* 243: -1.1532100e+00  1.7419846e+00 */
    { 0x3f93682d,0x3fdeaef3 }, /* 244:  1.1516167e+00  1.7397140e+00 */
    { 0x3fcdacd1,0x40260040 }, /* 245:  1.6068364e+00  2.5937653e+00 */
    { 0x3fd6f313,0x40318b6d }, /* 246:  1.6792930e+00  2.7741349e+00 */
    { 0x40b5f02e,0x43134b5c }, /* 247:  5.6855688e+00  1.4729437e+02 */
    { 0x3f10a9c9,0x3f94fc93 }, /* 248:  5.6509072e-01  1.1639580e+00 */
    { 0x3ff0fb88,0x405724da }, /* 249:  1.8826761e+00  3.3616242e+00 */
    { 0xbd0fecbf,0x3f80143b }, /* 250: -3.5137888e-02  1.0006174e+00 */
    { 0xbd62f844,0x3f803252 }, /* 251: -5.5412546e-02  1.0015357e+00 */
    { 0xbf15944f,0x3f967a73 }, /* 252: -5.8429426e-01  1.1756119e+00 */
    { 0x42398574,0x6070f66c }, /* 253:  4.6380325e+01  6.9452737e+19 */
    { 0xbf694fb2,0x3fb8f0f3 }, /* 254: -9.1137230e-01  1.4448532e+00 */
    { 0x402854d2,0x40df2c34 }, /* 255:  2.6301770e+00  6.9741459e+00 */
    { 0x402dc6db,0x40f2cbcf }, /* 256:  2.7152622e+00  7.5873790e+00 */
    { 0x3e75e32f,0x3f83b53f }, /* 257:  2.4012445e-01  1.0289687e+00 */
    { 0xbf9bb313,0x3feaf6e0 }, /* 258: -1.2164024e+00  1.8356590e+00 */
    { 0x3fc4dd5a,0x401bd7e3 }, /* 259:  1.5380051e+00  2.4350517e+00 */
    { 0x3e54bb18,0x3f82c5a6 }, /* 260:  2.0774496e-01  1.0216568e+00 */
    { 0x3efa94f8,0x3f8fa36b }, /* 261:  4.8941779e-01  1.1221746e+00 */
    { 0xbeff8feb,0x3f904776 }, /* 262: -4.9914488e-01  1.1271808e+00 */
    { 0x3ed4f250,0x3f8b3b3b }, /* 263:  4.1591120e-01  1.0877451e+00 */
    { 0x3ffb17ed,0x40680ebf }, /* 264:  1.9616677e+00  3.6259000e+00 */
    { 0xbf36a05d,0x3fa1f9c6 }, /* 265: -7.1338445e-01  1.2654350e+00 */
    { 0x3f2b0ae6,0x3f9da60d }, /* 266:  6.6813505e-01  1.2316300e+00 */
    { 0x3f62e9be,0x3fb5a98d }, /* 267:  8.8637912e-01  1.4192368e+00 */
    { 0x3fdec0a5,0x403bf9fe }, /* 268:  1.7402540e+00  2.9371333e+00 */
    { 0x3cd03e15,0x3f800a96 }, /* 269:  2.5420228e-02  1.0003231e+00 */
    { 0x3d9fd739,0x3f8063da }, /* 270:  7.8047223e-02  1.0030472e+00 */
    { 0x42072aff,0x57577f9e }, /* 271:  3.3791988e+01  2.3694311e+14 */
    { 0xbf4a61d6,0x3faa202b }, /* 272: -7.9055536e-01  1.3291067e+00 */
    { 0xbfa283f1,0x3ff5cb6e }, /* 273: -1.2696515e+00  1.9202707e+00 */
    { 0x3f938035,0x3fded12d }, /* 274:  1.1523501e+00  1.7407585e+00 */
    { 0x3f1d8d17,0x3f9903f3 }, /* 275:  6.1543411e-01  1.1954330e+00 */
    { 0xbfdb8dc2,0x40379e29 }, /* 276: -1.7152636e+00  2.8690283e+00 */
    { 0xbf5d8b54,0x3fb2ffa6 }, /* 277: -8.6540723e-01  1.3984268e+00 */
    { 0xbe9679b5,0x3f859165 }, /* 278: -2.9389730e-01  1.0434996e+00 */
    { 0xbf5d2df6,0x3fb2d20f }, /* 279: -8.6398256e-01  1.3970355e+00 */
    { 0x402dab89,0x40f26528 }, /* 280:  2.7135947e+00  7.5748482e+00 */
    { 0x3744a3e9,0x3f800000 }, /* 281:  1.1720674e-05  1.0000000e+00 */
    { 0xbe558cba,0x3f82cb24 }, /* 282: -2.0854464e-01  1.0218244e+00 */
    { 0xc0748214,0x41b695ad }, /* 283: -3.8204393e+00  2.2823084e+01 */
    { 0xbf9d5037,0x3fed77a6 }, /* 284: -1.2290105e+00  1.8552139e+00 */
    { 0x41df8cd3,0x531f28c0 }, /* 285:  2.7943762e+01  6.8358347e+11 */
    { 0xbf220fb5,0x3f9a8433 }, /* 286: -6.3305217e-01  1.2071594e+00 */
    { 0x3f436c80,0x3fa7245e }, /* 287:  7.6337433e-01  1.3057973e+00 */
    { 0x3f0c2adb,0x3f93abaa }, /* 288:  5.4752892e-01  1.1536763e+00 */
    { 0xbf0ccc32,0x3f93da30 }, /* 289: -5.4999077e-01  1.1550961e+00 */
    { 0xbfeb629e,0x404e5d5c }, /* 290: -1.8389471e+00  3.2244482e+00 */
    { 0xbf30c1bd,0x3f9fbe04 }, /* 291: -6.9045621e-01  1.2479863e+00 */
    { 0x40338b91,0x4104c0a4 }, /* 292:  2.8053935e+00  8.2970314e+00 */
    { 0x404eb25c,0x414a7af3 }, /* 293:  3.2296362e+00  1.2655017e+01 */
    { 0xbdc0f259,0x3f809188 }, /* 294: -9.4212241e-02  1.0044413e+00 */
    { 0xbf1378b7,0x3f95d4fd }, /* 295: -5.7606071e-01  1.1705624e+00 */
    { 0x3fba0285,0x401056e4 }, /* 296:  1.4532019e+00  2.2553034e+00 */
    { 0x3efa7c40,0x3f8fa046 }, /* 297:  4.8922920e-01  1.1220787e+00 */
    { 0xbf9a947e,0x3fe94004 }, /* 298: -1.2076566e+00  1.8222661e+00 */
    { 0xbf37638a,0x3fa245a2 }, /* 299: -7.1636260e-01  1.2677500e+00 */
    { 0x3fd54624,0x402f6458 }, /* 300:  1.6662030e+00  2.7404995e+00 */
    { 0xbe67b3e0,0x3f834a6e }, /* 301: -2.2627211e-01  1.0257089e+00 */
    { 0xbf6665e0,0x3fb76f1b }, /* 302: -8.9999199e-01  1.4330782e+00 */
    { 0x3f9d6db0,0x3feda5ba }, /* 303:  1.2299099e+00  1.8566201e+00 */
    { 0x3fe42a3a,0x40439ed8 }, /* 304:  1.7825387e+00  3.0565701e+00 */
    { 0x3eb30057,0x3f87e713 }, /* 305:  3.4961197e-01  1.0617393e+00 */
    { 0x3fe77e7b,0x40487eba }, /* 306:  1.8085474e+00  3.1327348e+00 */
    { 0x3ffbb769,0x4069255f }, /* 307:  1.9665347e+00  3.6429060e+00 */
    { 0xbf8dc0d3,0x3fd6d977 }, /* 308: -1.1074470e+00  1.6785115e+00 */
    { 0x3f5a2791,0x3fb15b84 }, /* 309:  8.5216624e-01  1.3856053e+00 */
    { 0x4063a722,0x418c5b30 }, /* 310:  3.5570760e+00  1.7544525e+01 */
    { 0x3f61afcd,0x3fb50c00 }, /* 311:  8.8158876e-01  1.4144287e+00 */
    { 0x3f6b84ed,0x3fba1972 }, /* 312:  9.1999704e-01  1.4539015e+00 */
    { 0x3f6b8df5,0x3fba1e37 }, /* 313:  9.2013484e-01  1.4540471e+00 */
    { 0x1be37817,0x3f800000 }, /* 314:  3.7631606e-22  1.0000000e+00 */
    { 0xbfc5e7be,0x401d00ef }, /* 315: -1.5461347e+00  2.4531820e+00 */
    { 0x4008fc7b,0x4089edb2 }, /* 316:  2.1404102e+00  4.3102655e+00 */
    { 0x3f9a5b9d,0x3fe8e975 }, /* 317:  1.2059208e+00  1.8196245e+00 */
    { 0xbb14328e,0x3f800015 }, /* 318: -2.2613141e-03  1.0000025e+00 */
    { 0x3f44774d,0x3fa794bd }, /* 319:  7.6744539e-01  1.3092266e+00 */
    { 0xc012c35c,0x40a01dcb }, /* 320: -2.2931738e+00  5.0036368e+00 */
    { 0x400e66fb,0x4095ca3d }, /* 321:  2.2250354e+00  4.6809373e+00 */
    { 0xbf744dfa,0x3fbed88a }, /* 322: -9.5431483e-01  1.4909832e+00 */
    { 0xc079391f,0x41c487f1 }, /* 323: -3.8941114e+00  2.4566378e+01 */
    { 0xbf2713bb,0x3f9c3df1 }, /* 324: -6.5264481e-01  1.2206403e+00 */
    { 0x3ef7ebfa,0x3f8f4d3a }, /* 325:  4.8422223e-01  1.1195443e+00 */
    { 0x3f205f16,0x3f99f2cb }, /* 326:  6.2645090e-01  1.2027220e+00 */
    { 0xbc0869d0,0x3f800123 }, /* 327: -8.3260089e-03  1.0000347e+00 */
    { 0xbff9b6f2,0x4065ab10 }, /* 328: -1.9508955e+00  3.5885658e+00 */
    { 0xbfcfbd3b,0x40287e1d }, /* 329: -1.6229624e+00  2.6326973e+00 */
    { 0xbf68322c,0x3fb85c84 }, /* 330: -9.0701556e-01  1.4403234e+00 */
    { 0xbf09ee01,0x3f930853 }, /* 331: -5.3878790e-01  1.1486915e+00 */
    { 0xbf696bfb,0x3fb8ffb4 }, /* 332: -9.1180390e-01  1.4453034e+00 */
    { 0xc00dbe6d,0x40944adf }, /* 333: -2.2147477e+00  4.6341395e+00 */
    { 0xbeacf672,0x3f875f9b }, /* 334: -3.3781773e-01  1.0576051e+00 */
    { 0x3fd76423,0x40321dfb }, /* 335:  1.6827434e+00  2.7830799e+00 */
    { 0x3f698baa,0x3fb9103d }, /* 336:  9.1228735e-01  1.4458081e+00 */
    { 0xbf26e9be,0x3f9c2f41 }, /* 337: -6.5200412e-01  1.2201921e+00 */
    { 0xbfee5e16,0x4052fe00 }, /* 338: -1.8622463e+00  3.2967529e+00 */
    { 0xbf41d65f,0x3fa67aac }, /* 339: -7.5717729e-01  1.3006186e+00 */
    { 0x400bf024,0x409043ef }, /* 340:  2.1865320e+00  4.5082927e+00 */
    { 0xbe83f53c,0x3f844658 }, /* 341: -2.5773036e-01  1.0333967e+00 */
    { 0xbf618319,0x3fb4f5a7 }, /* 342: -8.8090664e-01  1.4137467e+00 */
    { 0xbf990d95,0x3fe6f0c0 }, /* 343: -1.1957270e+00  1.8042221e+00 */
    { 0xbec8d518,0x3f89f957 }, /* 344: -3.9225078e-01  1.0779217e+00 */
    { 0xc1e994af,0x540b69fd }, /* 345: -2.9197599e+01  2.3951146e+12 */
    { 0xbf97ac7c,0x3fe4e1ea }, /* 346: -1.1849513e+00  1.7881444e+00 */
    { 0xbf9824a4,0x3fe5946d }, /* 347: -1.1886182e+00  1.7935921e+00 */
    { 0x3fa198b4,0x3ff44b6a }, /* 348:  1.2624726e+00  1.9085515e+00 */
    { 0x3f39210f,0x3fa2f42c }, /* 349:  7.2316068e-01  1.2730765e+00 */
    { 0xbf94ba54,0x3fe09362 }, /* 350: -1.1619363e+00  1.7544978e+00 */
    { 0xbf6921f7,0x3fb8d91d }, /* 351: -9.1067451e-01  1.4441258e+00 */
    { 0x3b7aa869,0x3f80003d }, /* 352:  3.8247353e-03  1.0000073e+00 */
    { 0xbf3958ad,0x3fa30a19 }, /* 353: -7.2400934e-01  1.2737457e+00 */
    { 0x3ca5d22c,0x3f8006b7 }, /* 354:  2.0241819e-02  1.0002049e+00 */
    { 0xbfe51681,0x4044f560 }, /* 355: -1.7897493e+00  3.0774765e+00 */
    { 0x3f96c051,0x3fe38557 }, /* 356:  1.1777440e+00  1.7775067e+00 */
    { 0x40795bf1,0x41c4f2e4 }, /* 357:  3.8962367e+00  2.4618599e+01 */
    { 0xbf13d93f,0x3f95f266 }, /* 358: -5.7753366e-01  1.1714599e+00 */
    { 0xbfdc4c31,0x40389f01 }, /* 359: -1.7210752e+00  2.8847048e+00 */
    { 0x4021ffc7,0x40ca60a8 }, /* 360:  2.5312364e+00  6.3242989e+00 */
    { 0x3fcaecd5,0x4022bf97 }, /* 361:  1.5853525e+00  2.5429437e+00 */
    { 0x3f1d5c6c,0x3f98f405 }, /* 362:  6.1469150e-01  1.1949469e+00 */
    { 0xc1f22ee3,0x54cc4d1c }, /* 363: -3.0272894e+01  7.0197361e+12 */
    { 0x3f70d75a,0x3fbcf2bc }, /* 364:  9.4078600e-01  1.4761577e+00 */
    { 0x3f1d4cf9,0x3f98eef8 }, /* 365:  6.1445576e-01  1.1947927e+00 */
    { 0x3f968211,0x3fe329f8 }, /* 366:  1.1758443e+00  1.7747183e+00 */
    { 0x3fb91d7a,0x400f704a }, /* 367:  1.4462121e+00  2.2412286e+00 */
    { 0x40e5e6d2,0x4424d777 }, /* 368:  7.1844263e+00  6.5936664e+02 */
    { 0xbfbf0d02,0x40158c3d }, /* 369: -1.4925845e+00  2.3366845e+00 */
    { 0x3e4108d8,0x3f8247f3 }, /* 370:  1.8851030e-01  1.0178207e+00 */
    { 0xbf2f7eb3,0x3f9f45ea }, /* 371: -6.8552703e-01  1.2443211e+00 */
    { 0x3f979d7e,0x3fe4cbb2 }, /* 372:  1.1844938e+00  1.7874663e+00 */
    { 0xc1bebb81,0x502870b1 }, /* 373: -2.3841555e+01  1.1303831e+10 */
    { 0x3fd3e203,0x402da0a6 }, /* 374:  1.6553348e+00  2.7129302e+00 */
    { 0xbf65ccf6,0x3fb720c0 }, /* 375: -8.9765871e-01  1.4306870e+00 */
    { 0x403a1109,0x4112e4d7 }, /* 376:  2.9072897e+00  9.1808691e+00 */
    { 0x3f6182dd,0x3fb4f589 }, /* 377:  8.8090307e-01  1.4137431e+00 */
    { 0xbf6a5250,0x3fb9782c }, /* 378: -9.1531849e-01  1.4489799e+00 */
    { 0x3e3af081,0x3f82238e }, /* 379:  1.8255807e-01  1.0167100e+00 */
    { 0xbf9e2616,0x3feec726 }, /* 380: -1.2355373e+00  1.8654525e+00 */
    { 0xbf98f794,0x3fe6cfb8 }, /* 381: -1.1950555e+00  1.8032141e+00 */
    { 0xbf874ed8,0x3fce6de9 }, /* 382: -1.0570936e+00  1.6127292e+00 */
    { 0x3fa199db,0x3ff44d49 }, /* 383:  1.2625078e+00  1.9086086e+00 */
    { 0xc08ab6db,0x4218a61a }, /* 384: -4.3348212e+00  3.8162209e+01 */
    { 0xbfc0c713,0x40176289 }, /* 385: -1.5060753e+00  2.3653891e+00 */
    { 0xbf640dde,0x3fb63d1d }, /* 386: -8.9083660e-01  1.4237400e+00 */
    { 0xc031ec0b,0x410173dc }, /* 387: -2.7800319e+00  8.0907860e+00 */
    { 0xbf9857db,0x3fe5e0c1 }, /* 388: -1.1901811e+00  1.7959214e+00 */
    { 0x3f238a95,0x3f9b04f5 }, /* 389:  6.3883334e-01  1.2110888e+00 */
    { 0x3c63753f,0x3f800328 }, /* 390:  1.3882934e-02  1.0000963e+00 */
    { 0x3f8db58f,0x3fd6ca48 }, /* 391:  1.1071032e+00  1.6780481e+00 */
    { 0xc065646b,0x41903788 }, /* 392: -3.5842540e+00  1.8027115e+01 */
    { 0x3fe5a8a9,0x4045ca92 }, /* 393:  1.7942096e+00  3.0904889e+00 */
    { 0xbfe51813,0x4044f7a9 }, /* 394: -1.7897972e+00  3.0776160e+00 */
    { 0x3fc884c8,0x401ff6ba }, /* 395:  1.5665522e+00  2.4994340e+00 */
    { 0x4000a577,0x40732316 }, /* 396:  2.0100992e+00  3.7990165e+00 */
    { 0xbfffaea4,0x40703477 }, /* 397: -1.9975171e+00  3.7532022e+00 */
    { 0xc04dba79,0x4147730d }, /* 398: -3.2145064e+00  1.2465589e+01 */
    { 0xbfb2afa4,0x40092b57 }, /* 399: -1.3959851e+00  2.1432703e+00 */
    { 0x3f12c978,0x3f959fd0 }, /* 400:  5.7338667e-01  1.1689396e+00 */
    { 0x37faa236,0x3f800000 }, /* 401:  2.9877858e-05  1.0000000e+00 */
    { 0x3fa34d21,0x3ff7166f }, /* 402:  1.2757913e+00  1.9303721e+00 */
    { 0x4013065d,0x40a0c263 }, /* 403:  2.2972634e+00  5.0237288e+00 */
    { 0xbf68a702,0x3fb89925 }, /* 404: -9.0879834e-01  1.4421736e+00 */
    { 0x3f100a1e,0x3f94cd23 }, /* 405:  5.6265438e-01  1.1625103e+00 */
    { 0x3f75bb0c,0x3fbfa32b }, /* 406:  9.5988536e-01  1.4971670e+00 */
    { 0xc184e4b5,0x4af9f6e2 }, /* 407: -1.6611673e+01  8.1908330e+06 */
    { 0xbf1ed7fb,0x3f9970d2 }, /* 408: -6.2048310e-01  1.1987555e+00 */
    { 0x3f8b5c56,0x3fd3a953 }, /* 409:  1.0887554e+00  1.6536049e+00 */
    { 0x3ec492c4,0x3f898ce1 }, /* 410:  3.8393223e-01  1.0746118e+00 */
    { 0x39dcbfb4,0x3f800001 }, /* 411:  4.2104500e-04  1.0000001e+00 */
    { 0xbfc7b7ee,0x401f0ce7 }, /* 412: -1.5603006e+00  2.4851625e+00 */
    { 0xc11481d7,0x45a7cea9 }, /* 413: -9.2816992e+00  5.3698325e+03 */
    { 0xc03201ec,0x41019fce }, /* 414: -2.7813673e+00  8.1015148e+00 */
    { 0xbea7029e,0x3f86deca }, /* 415: -3.2619184e-01  1.0536740e+00 */
    { 0xbf382767,0x3fa29221 }, /* 416: -7.1935123e-01  1.2700845e+00 */
    { 0x3f800000,0x3fc583ab }, /* 417:  1.0000000e+00  1.5430807e+00 */
    { 0xbcf9902d,0x3f800f35 }, /* 418: -3.0464256e-02  1.0004641e+00 */
    { 0x4032c61f,0x41032c88 }, /* 419:  2.7933424e+00  8.1983719e+00 */
    { 0x3f728987,0x3fbddf85 }, /* 420:  9.4741100e-01  1.4833838e+00 */
    { 0x3fc11489,0x4017b5aa }, /* 421:  1.5084392e+00  2.3704629e+00 */
    { 0x3f9e99cf,0x3fef7dc4 }, /* 422:  1.2390689e+00  1.8710256e+00 */
    { 0x405c53a2,0x417a66f6 }, /* 423:  3.4426045e+00  1.5650137e+01 */
    { 0xbe3b81f8,0x3f8226e6 }, /* 424: -1.8311298e-01  1.0168121e+00 */
    { 0xbf23130e,0x3f9adc32 }, /* 425: -6.3700950e-01  1.2098448e+00 */
    { 0xbf0831de,0x3f928bab }, /* 426: -5.3201091e-01  1.1448873e+00 */
    { 0xbf270a61,0x3f9c3aac }, /* 427: -6.5250212e-01  1.2205405e+00 */
    { 0xbf6548af,0x3fb6dd2d }, /* 428: -8.9564031e-01  1.4286247e+00 */
    { 0xbfdb82a8,0x40378f3d }, /* 429: -1.7149248e+00  2.8681176e+00 */
    { 0x3f9c3f75,0x3febcf87 }, /* 430:  1.2206866e+00  1.8422707e+00 */
    { 0x3f69e654,0x3fb93f9f }, /* 431:  9.1367078e-01  1.4472541e+00 */
    { 0xbfc2b83b,0x40197bdf }, /* 432: -1.5212473e+00  2.3981855e+00 */
    { 0x3f27b654,0x3f9c76f9 }, /* 433:  6.5512586e-01  1.2223808e+00 */
    { 0x41801924,0x4a89441a }, /* 434:  1.6012276e+01  4.4979330e+06 */
    { 0x3f3d4e34,0x3fa49ee9 }, /* 435:  7.3947453e-01  1.2860996e+00 */
    { 0xbdd1d99a,0x3f80ac2c }, /* 436: -1.0246582e-01  1.0052543e+00 */
    { 0x408d2d0f,0x4224d9f8 }, /* 437:  4.4117503e+00  4.1212860e+01 */
    { 0xbf62bd3f,0x3fb59328 }, /* 438: -8.8570017e-01  1.4185534e+00 */
    { 0xbf177b0b,0x3f9711f1 }, /* 439: -5.9172124e-01  1.1802350e+00 */
    { 0xbf25d06d,0x3f9bcd47 }, /* 440: -6.4771158e-01  1.2172021e+00 */
    { 0x3f657ab5,0x3fb6f6b5 }, /* 441:  8.9640361e-01  1.4294039e+00 */
    { 0x40052a20,0x4082287e }, /* 442:  2.0806961e+00  4.0674429e+00 */
    { 0x3ee52553,0x3f8d08e2 }, /* 443:  4.4755039e-01  1.1018336e+00 */
    { 0xbfc1c2c3,0x40187171 }, /* 444: -1.5137562e+00  2.3819239e+00 */
    { 0xc0130935,0x40a0c963 }, /* 445: -2.2974370e+00  5.0245833e+00 */
    { 0xc008389f,0x408855a0 }, /* 446: -2.1284559e+00  4.2604523e+00 */
    { 0x3f9718fd,0x3fe407dc }, /* 447:  1.1804501e+00  1.7814898e+00 */
    { 0x400fbe2d,0x4098e367 }, /* 448:  2.2459824e+00  4.7777591e+00 */
    { 0xbec69d29,0x3f89c08a }, /* 449: -3.8791779e-01  1.0761883e+00 */
    { 0xbed8302f,0x3f8b94be }, /* 450: -4.2224261e-01  1.0904768e+00 */
    { 0xbfdeab30,0x403bdc60 }, /* 451: -1.7395992e+00  2.9353256e+00 */
    { 0xbeca3b7d,0x3f8a1d87 }, /* 452: -3.9498511e-01  1.0790261e+00 */
    { 0x3fd44925,0x402e22ea }, /* 453:  1.6584822e+00  2.7208810e+00 */
    { 0xbfe8669b,0x4049d897 }, /* 454: -1.8156313e+00  3.1538446e+00 */
    { 0xbf65226e,0x3fb6c9ab }, /* 455: -8.9505661e-01  1.4280294e+00 */
    { 0x3e6b3833,0x3f836450 }, /* 456:  2.2970657e-01  1.0264988e+00 */
    { 0x3bdc158c,0x3f8000bd }, /* 457:  6.7164358e-03  1.0000225e+00 */
    { 0xbf87f30e,0x3fcf3e59 }, /* 458: -1.0621049e+00  1.6190902e+00 */
    { 0xbf2d115d,0x3f9e61b2 }, /* 459: -6.7604619e-01  1.2373564e+00 */
    { 0x3f9c2e01,0x3febb489 }, /* 460:  1.2201539e+00  1.8414470e+00 */
    { 0x3f3d6345,0x3fa4a76e }, /* 461:  7.3979598e-01  1.2863595e+00 */
    { 0xbf6abdc2,0x3fb9b091 }, /* 462: -9.1695797e-01  1.4507009e+00 */
    { 0x3f0e7423,0x3f945588 }, /* 463:  5.5645961e-01  1.1588602e+00 */
    { 0x40056382,0x408299d1 }, /* 464:  2.0841985e+00  4.0812764e+00 */
    { 0xbf9b787b,0x3fea9cc6 }, /* 465: -1.2146143e+00  1.8329093e+00 */
    { 0x4217660d,0x5a42c13c }, /* 466:  3.7849659e+01  1.3704652e+16 */
    { 0xbf9dc994,0x3fee35b6 }, /* 467: -1.2327142e+00  1.8610141e+00 */
    { 0x3fe294ef,0x40415958 }, /* 468:  1.7701701e+00  3.0210781e+00 */
    { 0x3fe5ad6a,0x4045d185 }, /* 469:  1.7943547e+00  3.0909131e+00 */
    { 0xbfe59b65,0x4045b72d }, /* 470: -1.7938048e+00  3.0893052e+00 */
    { 0xc023b708,0x40cfcef4 }, /* 471: -2.5580463e+00  6.4940128e+00 */
    { 0x3f606111,0x3fb46530 }, /* 472:  8.7648112e-01  1.4093380e+00 */
    { 0xbf65bf94,0x3fb719e7 }, /* 473: -8.9745450e-01  1.4304780e+00 */
    { 0xbe7af0d7,0x3f83dcdc }, /* 474: -2.4505936e-01  1.0301776e+00 */
    { 0xbe3ea095,0x3f82396f }, /* 475: -1.8615945e-01  1.0173777e+00 */
    { 0x3f63b7d5,0x3fb6118f }, /* 476:  8.8952380e-01  1.4224108e+00 */
    { 0xbefce547,0x3f8fef32 }, /* 477: -4.9393675e-01  1.1244872e+00 */
    { 0x3f99f99d,0x3fe854bf }, /* 478:  1.2029301e+00  1.8150862e+00 */
    { 0x3fdb6d0f,0x40377238 }, /* 479:  1.7142657e+00  2.8663464e+00 */
    { 0x3f6ef2e2,0x3fbbed07 }, /* 480:  9.3339360e-01  1.4681710e+00 */
    { 0xc01c8c2f,0x40ba11e5 }, /* 481: -2.4460561e+00  5.8146844e+00 */
    { 0xbf057b8b,0x3f91cc3d }, /* 482: -5.2141637e-01  1.1390454e+00 */
    { 0xbfd33fbe,0x402cd494 }, /* 483: -1.6503828e+00  2.7004747e+00 */
    { 0x3f66e29a,0x3fb7af35 }, /* 484:  9.0189517e-01  1.4350344e+00 */
    { 0x3f97048d,0x3fe3e9bd }, /* 485:  1.1798264e+00  1.7805706e+00 */
    { 0xc03e63bf,0x411d199d }, /* 486: -2.9748380e+00  9.8187532e+00 */
    { 0xbf9e66fe,0x3fef2d7b }, /* 487: -1.2375181e+00  1.8685755e+00 */
    { 0xbfe2be3e,0x40419443 }, /* 488: -1.7714307e+00  3.0246742e+00 */
    { 0xbecf98ee,0x3f8aaaa6 }, /* 489: -4.0546364e-01  1.0833328e+00 */
    { 0x3eb0dbdd,0x3f87b675 }, /* 490:  3.4542742e-01  1.0602556e+00 */
    { 0x3fcd02cb,0x4025355e }, /* 491:  1.6016477e+00  2.5813823e+00 */
    { 0x3f655cac,0x3fb6e760 }, /* 492:  8.9594531e-01  1.4289360e+00 */
    { 0x3f800000,0x3fc583ab }, /* 493:  1.0000000e+00  1.5430807e+00 */
    { 0x4055141b,0x415fa605 }, /* 494:  3.3293521e+00  1.3978032e+01 */
    { 0xbf99cbe6,0x3fe80f8e }, /* 495: -1.2015350e+00  1.8129747e+00 */
    { 0x405cd0b3,0x417c5129 }, /* 496:  3.4502380e+00  1.5769814e+01 */
    { 0x3f6451d3,0x3fb65f93 }, /* 497:  8.9187354e-01  1.4247917e+00 */
    { 0xbf377422,0x3fa24c19 }, /* 498: -7.1661580e-01  1.2679473e+00 */
    { 0xbff77bf1,0x4061dbfb }, /* 499: -1.9334699e+00  3.5290515e+00 */
    { 0x3fe29abb,0x4041619b }, /* 500:  1.7703470e+00  3.0215824e+00 */
};

void x_exit (int index)
{
#ifndef	__AVR__
    fprintf (stderr, "t[%d]:  %#lx\n", index - 1, v.lo);
#endif
    exit (index ? index : -1);
}

int main ()
{
    union lofl_u x, z;
    unsigned long v1, z1, r;
    int i;
    
    for (i = 0; i < (int) (sizeof(t) / sizeof(t[0])); i++) {
	x.lo = pgm_read_dword (& t[i].x);
	z.lo = pgm_read_dword (& t[i].z);
	v.fl = cosh (x.fl);
	
	v1 = (v.lo < 0) ? (unsigned long)~(v.lo) : v.lo + 0x80000000;
	z1 = (z.lo < 0) ? (unsigned long)~(z.lo) : z.lo + 0x80000000;
	r = (v1 >= z1) ? v1 - z1 : z1 - v1;
	
	if (r > 72) x_exit (i+1);
    }
    return 0;
}
