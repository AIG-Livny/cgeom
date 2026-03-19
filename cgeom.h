/*
 * cgeom
 * Copyright (C) 2026 Ivan Agibalov (AIG) (aig.livny@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef CGEOM_H
#define CGEOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifndef cg_memcmp
#define cg_memcmp memcmp
#endif

#ifndef cg_assert
#include <assert.h>
#define cg_assert assert
#endif

// Structures sizes
#define CG_VEC2_SIZE 2
#define CG_VEC3_SIZE 3
#define CG_VEC4_SIZE 4
#define CG_QUAT_SIZE 4
#define CG_MAT2_SIZE 4
#define CG_MAT3_SIZE 9
#define CG_MAT4_SIZE 16

// Element number in array
#define CG_X 0
#define CG_Y 1
#define CG_Z 2
#define CG_W 3

#define CG_R 0
#define CG_G 1
#define CG_B 2
#define CG_A 3

#define CG_LEFT 0
#define CG_TOP 1
#define CG_WIDTH 2
#define CG_HEIGHT 3

#define CG_MAT2_11 0
#define CG_MAT2_21 1
#define CG_MAT2_12 2
#define CG_MAT2_22 3

#define CG_MAT3_11 0
#define CG_MAT3_21 1
#define CG_MAT3_31 2
#define CG_MAT3_12 3
#define CG_MAT3_22 4
#define CG_MAT3_32 5
#define CG_MAT3_13 6
#define CG_MAT3_23 7
#define CG_MAT3_33 8

#define CG_MAT4_11 0
#define CG_MAT4_21 1
#define CG_MAT4_31 2
#define CG_MAT4_41 3
#define CG_MAT4_12 4
#define CG_MAT4_22 5
#define CG_MAT4_32 6
#define CG_MAT4_42 7
#define CG_MAT4_13 8
#define CG_MAT4_23 9
#define CG_MAT4_33 10
#define CG_MAT4_43 11
#define CG_MAT4_14 12
#define CG_MAT4_24 13
#define CG_MAT4_34 14
#define CG_MAT4_44 15

#if !defined( CG_INT_TYPE )
typedef int32_t cgi_t;
#else
typedef CG_INT_TYPE cgi_t;
#endif

#if !defined( CG_FLOAT_TYPE )
typedef float cgf_t;
#else
typedef CG_FLOAT_TYPE cgf_t;
#endif

#if !defined( CG_DOUBLE_TYPE )
typedef double cgd_t;
#else
typedef CG_DOUBLE_TYPE cgd_t;
#endif

#define CG_dPI (cgd_t)3.14159265358979323846
#define CG_dPI_2 (cgd_t)1.57079632679489661923
#define CG_dPI_4 (cgd_t)0.78539816339744830962
#define CG_fPI (cgf_t)3.1415926536
#define CG_fPI_2 (cgf_t)1.5707963268
#define CG_fPI_4 (cgf_t)0.7853981634

#define CG_iABS abs

#define CG_fABS fabsf
#define CG_fMIN fminf
#define CG_fMAX fmaxf
#define CG_fSQRT sqrtf
#define CG_fSIN sinf
#define CG_fCOS cosf
#define CG_fACOS acosf
#define CG_fASIN asinf
#define CG_fTAN tanf
#define CG_fATAN2 atan2f
#define CG_fPOW powf
#define CG_fFLOOR floorf
#define CG_fCEIL ceilf
#define CG_fROUND roundf

#define CG_dABS fabs
#define CG_dMIN fmin
#define CG_dMAX fmax
#define CG_dSQRT sqrt
#define CG_dSIN sin
#define CG_dCOS cos
#define CG_dACOS acos
#define CG_dASIN asin
#define CG_dTAN tan
#define CG_dATAN2 atan2
#define CG_dPOW pow
#define CG_dFLOOR floor
#define CG_dCEIL ceil
#define CG_dROUND round

#define CG_fEPSILON FLT_EPSILON
#define CG_dEPSILON DBL_EPSILON

// clang-format off

#define CG_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define CG_MIN(a, b) (((a) < (b)) ? (a) : (b))

// compare types of a and b values
#define types_match(a, b) _Generic((a), \
    __typeof__(b): 1, \
    default: 0 \
)

// can be placed at printf, sprintf fprintf as arguments to write vector data
#define print_vec2_args(vec) \
    "[x=%.2f y=%.2f]", (cgf_t)(vec).x, (cgf_t)(vec).y

#define print_vec3_args(vec) \
    "[x=%.2f y=%.2f z=%.2f]", (cgf_t)(vec).x, (cgf_t)(vec).y, (cgf_t)(vec).z

#define print_vec4_args(vec) \
    "[x=%.2f y=%.2f z=%.2f w=%.2f]", (cgf_t)(vec).x, (cgf_t)(vec).y, (cgf_t)(vec).z, (cgf_t)(vec).w

#define print_mat2_args(mat) \
    "| %5.2f | %5.2f |\n"\
    "| %5.2f | %5.2f |\n"\
    ,\
    (mat).m11, (mat).m12,\
    (mat).m21, (mat).m22\

#define print_mat3_args(mat) \
    "| %5.2f | %5.2f | %5.2f |\n"\
    "| %5.2f | %5.2f | %5.2f |\n"\
    "| %5.2f | %5.2f | %5.2f |\n"\
    ,\
    (mat).m11, (mat).m12, (mat).m13,\
    (mat).m21, (mat).m22, (mat).m23,\
    (mat).m31, (mat).m32, (mat).m33\

#define print_mat4_args(mat) \
    "| %5.2f | %5.2f | %5.2f | %5.2f |\n"\
    "| %5.2f | %5.2f | %5.2f | %5.2f |\n"\
    "| %5.2f | %5.2f | %5.2f | %5.2f |\n"\
    "| %5.2f | %5.2f | %5.2f | %5.2f |\n"\
    ,\
    (mat).m11, (mat).m12, (mat).m13, (mat).m14,\
    (mat).m21, (mat).m22, (mat).m23, (mat).m24,\
    (mat).m31, (mat).m32, (mat).m33, (mat).m34,\
    (mat).m41, (mat).m42, (mat).m43, (mat).m44\

// VEC2

typedef struct vec2i {
    union {
        struct { cgi_t x;    cgi_t y; };
        cgi_t v[2];
    };
} vec2i;

typedef struct vec2f {
    union {
        struct { cgf_t x; cgf_t y; };
        struct { cgf_t s; cgf_t t; };
        struct { cgf_t start; cgf_t end; };
        struct { cgf_t min; cgf_t max; };
        cgf_t v[2];
    };
} vec2f;

typedef struct vec2d {
    union {
        struct { cgd_t x; cgd_t y; };
        struct { cgd_t s; cgd_t t; };
        struct { cgd_t start; cgd_t end; };
        struct { cgd_t min; cgd_t max; };
        cgd_t v[2];
    };
} vec2d;

// END VEC2

// VEC3

typedef struct vec3i {
    union {
        struct { cgi_t x; cgi_t y; cgi_t z; };
        cgi_t v[3];
    };
} vec3i;

typedef struct vec3f {
    union {
        struct { cgf_t x; cgf_t y; cgf_t z; };
        struct { cgf_t r; cgf_t g; cgf_t b; };
        struct { cgf_t red; cgf_t green; cgf_t blue; };
        cgf_t v[3];
    };
} vec3f;

typedef struct vec3d {
    union {
        struct { cgd_t x; cgd_t y; cgd_t z; };
        struct { cgd_t r; cgd_t g; cgd_t b; };
        struct { cgd_t red; cgd_t green; cgd_t blue; };
        cgd_t v[3];
    };
} vec3d;

// END VEC3

// VEC4

typedef struct vec4i {
    union {
        struct { cgi_t x; cgi_t y; cgi_t z; cgi_t w; };
        struct { cgi_t left; cgi_t top; cgi_t width; cgi_t height; };
        struct { cgi_t vstart; cgi_t vcount; cgi_t istart; cgi_t icount; };
        cgi_t v[4];
    };
} vec4i;

typedef struct vec4f {
    union {
        struct { cgf_t x; cgf_t y; cgf_t z; cgf_t w; };
        struct { cgf_t left; cgf_t top; cgf_t width; cgf_t height; };
        struct { cgf_t r; cgf_t g; cgf_t b; cgf_t a; };
        struct { cgf_t red; cgf_t green; cgf_t blue; cgf_t alpha; };
        struct { cgf_t vstart; cgf_t vcount; cgf_t istart; cgf_t icount; };
        cgf_t v[4];
    };
} vec4f;

typedef struct vec4d {
    union {
        struct { cgd_t x; cgd_t y; cgd_t z; cgd_t w; };
        struct { cgd_t left; cgd_t top; cgd_t width; cgd_t height; };
        struct { cgd_t r; cgd_t g; cgd_t b; cgd_t a; };
        struct { cgd_t red; cgd_t green; cgd_t blue; cgd_t alpha; };
        struct { cgd_t vstart; cgd_t vcount; cgd_t istart; cgd_t icount; };
        cgd_t v[4];
    };
} vec4d;

// END VEC4

// QUAT

typedef struct quatf {
    union {
        struct { cgf_t x; cgf_t y; cgf_t z; cgf_t w; };
        cgf_t v[4];
    };

} quatf;

typedef struct quatd {
    union {
        struct { cgd_t x; cgd_t y; cgd_t z; cgd_t w; };
        cgd_t v[4];
    };
} quatd;

// END QUAT

// MAT2

typedef struct mat2f {
    union {
        struct {
            cgf_t m11; cgf_t m21;
            cgf_t m12; cgf_t m22;
        };
        cgf_t v[4];
    };
} mat2f;

typedef struct mat2d {
    union {
        struct {
            cgd_t m11; cgd_t m21;
            cgd_t m12; cgd_t m22;
        };
        cgd_t v[4];
    };
} mat2d;

// END MAT2

// MAT 3

typedef struct mat3f {
    union {
        struct {
            cgf_t m11; cgf_t m21; cgf_t m31;
            cgf_t m12; cgf_t m22; cgf_t m32;
            cgf_t m13; cgf_t m23; cgf_t m33;
        };
        cgf_t v[9];
    };
} mat3f;

typedef struct mat3d {
    union {
        struct {
            cgd_t m11; cgd_t m21; cgd_t m31;
            cgd_t m12; cgd_t m22; cgd_t m32;
            cgd_t m13; cgd_t m23; cgd_t m33;
        };
        cgd_t v[9];
    };
} mat3d;

// END MAT3

// MAT 4

typedef struct mat4f {
    union {
        struct {
            cgf_t m11; cgf_t m21; cgf_t m31; cgf_t m41;
            cgf_t m12; cgf_t m22; cgf_t m32; cgf_t m42;
            cgf_t m13; cgf_t m23; cgf_t m33; cgf_t m43;
            cgf_t m14; cgf_t m24; cgf_t m34; cgf_t m44;
        };
        cgf_t v[16];
    };
} mat4f;

typedef struct mat4d {
    union {
        struct {
            cgd_t m11; cgd_t m21; cgd_t m31; cgd_t m41;
            cgd_t m12; cgd_t m22; cgd_t m32; cgd_t m42;
            cgd_t m13; cgd_t m23; cgd_t m33; cgd_t m43;
            cgd_t m14; cgd_t m24; cgd_t m34; cgd_t m44;
        };
        cgd_t v[16];
    };
} mat4d;

// END MAT4

// RECT

typedef struct rect3i {
    vec3i min;
    vec3i max;
} rect3i;

// END RECT

// LINE

typedef struct line3i {
    vec3i point;
    vec3d direction;
} line3i;

typedef struct line2d {
    vec2d point;
    vec2d direction;
} line2d;

// END LINE

// SEGMENT

typedef struct segment3i {
    vec3i start;
    vec3i end;
} segment3i;

// END SEGMENT

// TRIFACE

typedef struct triface3i {
    vec3i p[3];
    vec3d normal;
} triface3i;

// END TRIFACE

// EXTREMES

typedef struct extremes3i {
    union {
        struct{
            vec3i* min_x; vec3i* min_y; vec3i* min_z;
            vec3i* max_x; vec3i* max_y; vec3i* max_z;
        };
        vec3i* v[6]; };
} extremes3i;

// END EXTREMES

// for vec3i rotating
static const cgi_t cg_ortho_bases[24][9] = {
    { 1, 0, 0, 0, 1, 0, 0, 0, 1},//0
    { 0,-1, 0, 1, 0, 0, 0, 0, 1},//1
    {-1, 0, 0, 0,-1, 0, 0, 0, 1},//2
    { 0, 1, 0,-1, 0, 0, 0, 0, 1},//3

    { 1, 0, 0, 0, 0,-1, 0, 1, 0},//4
    { 0, 0, 1, 1, 0, 0, 0, 1, 0},//5
    {-1, 0, 0, 0, 0, 1, 0, 1, 0},//6
    { 0, 0,-1,-1, 0, 0, 0, 1, 0},//7

    { 1, 0, 0, 0,-1, 0, 0, 0,-1},//8
    { 0, 1, 0, 1, 0, 0, 0, 0,-1},//9
    {-1, 0, 0, 0, 1, 0, 0, 0,-1},//10
    { 0,-1, 0,-1, 0, 0, 0, 0,-1},//11

    { 1, 0, 0, 0, 0, 1, 0,-1, 0},//12
    { 0, 0,-1, 1, 0, 0, 0,-1, 0},//13
    {-1, 0, 0, 0, 0,-1, 0,-1, 0},//14
    { 0, 0, 1,-1, 0, 0, 0,-1, 0},//15

    { 0, 0, 1, 0, 1, 0,-1, 0, 0},//16
    { 0,-1, 0, 0, 0, 1,-1, 0, 0},//17
    { 0, 0,-1, 0,-1, 0,-1, 0, 0},//18
    { 0, 1, 0, 0, 0,-1,-1, 0, 0},//19

    { 0, 0, 1, 0,-1, 0, 1, 0, 0},//20
    { 0, 1, 0, 0, 0, 1, 1, 0, 0},//21
    { 0, 0,-1, 0, 1, 0, 1, 0, 0},//22
    { 0,-1, 0, 0, 0,-1, 1, 0, 0},//23
};

// Rotating vec3i
enum cgcorner_vector {
    cvBackDownLeft     =0,
    cvFrontDownLeft    =1,
    cvFrontDownRight   =2,
    cvBackDownRight    =3,
    cvBackUpLeft       =4,
    cvBackUpRight      =7,
    cvFrontUpLeft      =8,
    cvFrontUpRight     =11,

    cvFrontUpRight2    =14,
    cvFrontUpRight3    =18,
    cvFrontUpLeft2     =13,
    cvFrontUpLeft3     =23,
    cvFrontDownRight2  =15,
    cvFrontDownRight3  =17,
    cvFrontDownLeft2   =12,
    cvFrontDownLeft3   =20,
    cvBackUpRight2     =10,
    cvBackUpRight3     =19,
    cvBackUpLeft2      =9,
    cvBackUpLeft3      =22,
    cvBackDownRight2   =6,
    cvBackDownRight3   =16,
    cvBackDownLeft2    =5,
    cvBackDownLeft3    =21,
};

// clang-format on

#ifdef CGEOM_PRECISE_TRIGONOMETRY
//  The following code (sincos1cos and float and double versions of
//  sncs1cs) is Copyright © 1985, 1995, 2000 Stephen L. Moshier and
//  Copyright © 2020 Neven Sajko. The intention is to get accurate
//  1-cosine, while also getting the sine and cosine as a bonus. The
//  implementation is derived from the Cephes Math Library's sin.c and
//  sinf.c. To be more specific, I took Stephen Moshier's sin, cos, sinf
//  and cosf (without changing the polynomials) and adapted them to give
//  all three required function values (in double and float versions),
//  without unnecessary accuracy losses.
//
//  sncs1cs is not correct for values of x of huge magnitude. That can
//  be fixed by more elaborate range reduction.

//  Sine, cosine, 1-cosine
typedef struct {
  cgd_t sin;
  cgd_t cos;
  cgd_t omc; // 1 - cos
} sincos1cosd;

const double sc[] = {
    1.58962301576546568060E-10, -2.50507477628578072866E-8,
    2.75573136213857245213E-6,  -1.98412698295895385996E-4,
    8.33333333332211858878E-3,  -1.66666666666666307295E-1,
};

const double cc[] = {
    -1.13585365213876817300E-11, 2.08757008419747316778E-9,
    -2.75573141792967388112E-7,  2.48015872888517045348E-5,
    -1.38888888888730564116E-3,  4.16666666666665929218E-2,
};

const double DP1 = 7.85398125648498535156E-1;
const double DP2 = 3.77489470793079817668E-8;
const double DP3 = 2.69515142907905952645E-15;

static sincos1cosf sncs1cs( cgd_t x ) {
  const cgd_t fourOverPi = 1.27323954473516268615;

  cgd_t y, z, zz;
  cgi_t j, sign = 1, csign = 1;
  sincos1cos##_char r;

  // Handle +-0.
  if( x == (cgd_t)0 ) {
    r.sin = x;
    r.cos = 1;
    r.omc = 0;
    return r;
  }
  if( isnan( x ) ) {
    r.sin = r.cos = r.omc = x;
    return r;
  }
  if( isinf( x ) ) {
    r.sin = r.cos = r.omc = x - x;
    return r;
  }
  if( x < 0 ) {
    sign = -1;
    x = -x;
  }
  j = (cgi_t)( x * fourOverPi );
  y = (cgd_t)j;
  // map zeros to origin
  if( ( j & 1 ) ) {
    j += 1;
    y += 1;
  }
  j = j & 7; // octant modulo one turn
  // reflect in x axis
  if( j > 3 ) {
    sign = -sign;
    csign = -csign;
    j -= 4;
  }
  if( j > 1 ) {
    csign = -csign;
  }

  // Extended precision modular arithmetic
  z = ( ( x - y * DP1 ) - y * DP2 ) - y * DP3;
  zz = z * z;
  r.sin =
      z +
      zz * z *
          ( ( ( ( ( sc[0] * zz + sc[1] ) * zz + sc[2] ) * zz + sc[3] ) * zz +
              sc[4] ) *
                zz +
            sc[5] );
  r.omc =
      (double)0.5 * zz -
      zz * zz *
          ( ( ( ( ( cc[0] * zz + cc[1] ) * zz + cc[2] ) * zz + cc[3] ) * zz +
              cc[4] ) *
                zz +
            cc[5] );

  if( j == 1 || j == 2 ) {
    if( csign < 0 ) {
      r.sin = -r.sin;
    }
    r.cos = r.sin;
    r.sin = 1 - r.omc;
    r.omc = 1 - r.cos;
  } else {
    if( csign < 0 ) {
      r.cos = r.omc - 1;
      r.omc = 1 - r.cos;
    } else {
      r.cos = 1 - r.omc;
    }
  }
  if( sign < 0 ) {
    r.sin = -r.sin;
  }
  return r;
}

#endif

// clang-format off

static inline bool equali(cgi_t a, cgi_t b) { return a == b; }
static inline bool equalf(cgf_t a, cgf_t b) { return a == b; }
static inline bool equald(cgd_t a, cgd_t b) { return a == b; }
static inline bool equal_vec2i(vec2i a, vec2i b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_vec2f(vec2f a, vec2f b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_vec2d(vec2d a, vec2d b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_vec3i(vec3i a, vec3i b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_vec3f(vec3f a, vec3f b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_vec3d(vec3d a, vec3d b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_vec4i(vec4i a, vec4i b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_vec4f(vec4f a, vec4f b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_vec4d(vec4d a, vec4d b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_quatf(quatf a, quatf b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_quatd(quatd a, quatd b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_mat2f(mat2f a, mat2f b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_mat2d(mat2d a, mat2d b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_mat3f(mat3f a, mat3f b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_mat3d(mat3d a, mat3d b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_mat4f(mat4f a, mat4f b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }
static inline bool equal_mat4d(mat4d a, mat4d b) { return cg_memcmp((void*)&(a), (void*)&(b), sizeof(a)) == 0; }

// compare values nearly with epsilon deviation
#define equal(a, b) _Generic((a), \
    cgi_t: equali, \
    cgf_t: equalf, \
    cgd_t: equald, \
    vec2i: equal_vec2i, \
    vec2f: equal_vec2f, \
    vec2d: equal_vec2d, \
    vec3i: equal_vec3i, \
    vec3f: equal_vec3f, \
    vec3d: equal_vec3d, \
    vec4i: equal_vec4i, \
    vec4f: equal_vec4f, \
    vec4d: equal_vec4d, \
    quatf: equal_quatf, \
    quatd: equal_quatd, \
    mat2f: equal_mat2f, \
    mat2d: equal_mat2d, \
    mat3f: equal_mat3f, \
    mat3d: equal_mat3d, \
    mat4f: equal_mat4f, \
    mat4d: equal_mat4d \
)((a),(b))

// clang-format on

static inline bool nearly_equali( cgi_t a, cgi_t b, cgi_t epsilon ) {
  return (
      ( ( a ) == ( b ) )
          ? true
          : ( ( CG_iABS( ( a ) - ( b ) ) <= ( epsilon ) ) ? true : false ) );
}

static inline bool nearly_equalf( cgf_t a, cgf_t b, cgf_t epsilon ) {
  return (
      ( ( a ) == ( b ) )
          ? true
          : ( ( CG_fABS( ( a ) - ( b ) ) <= ( epsilon ) ) ? true : false ) );
}

static inline bool nearly_equald( cgd_t a, cgd_t b, cgd_t epsilon ) {
  return (
      ( ( a ) == ( b ) )
          ? true
          : ( ( CG_dABS( ( a ) - ( b ) ) <= ( epsilon ) ) ? true : false ) );
}

static inline bool nearly_equal_vec2i( vec2i a, vec2i b, cgi_t epsilon ) {
  return nearly_equali( a.x, b.x, epsilon ) &&
         nearly_equali( a.y, b.y, epsilon );
}

static inline bool nearly_equal_vec2f( vec2f a, vec2f b, cgf_t epsilon ) {
  return nearly_equalf( a.x, b.x, epsilon ) &&
         nearly_equalf( a.y, b.y, epsilon );
}

static inline bool nearly_equal_vec2d( vec2d a, vec2d b, cgd_t epsilon ) {
  return nearly_equald( a.x, b.x, epsilon ) &&
         nearly_equald( a.y, b.y, epsilon );
}

static inline bool nearly_equal_vec3i( vec3i a, vec3i b, cgi_t epsilon ) {
  return nearly_equali( a.x, b.x, epsilon ) &&
         nearly_equali( a.y, b.y, epsilon ) &&
         nearly_equali( a.z, b.z, epsilon );
}

static inline bool nearly_equal_vec3f( vec3f a, vec3f b, cgf_t epsilon ) {
  return nearly_equalf( a.x, b.x, epsilon ) &&
         nearly_equalf( a.y, b.y, epsilon ) &&
         nearly_equalf( a.z, b.z, epsilon );
}

static inline bool nearly_equal_vec3d( vec3d a, vec3d b, cgd_t epsilon ) {
  return nearly_equald( a.x, b.x, epsilon ) &&
         nearly_equald( a.y, b.y, epsilon ) &&
         nearly_equald( a.z, b.z, epsilon );
}

static inline bool nearly_equal_vec4i( vec4i a, vec4i b, cgi_t epsilon ) {
  return nearly_equali( a.x, b.x, epsilon ) &&
         nearly_equali( a.y, b.y, epsilon ) &&
         nearly_equali( a.z, b.z, epsilon ) &&
         nearly_equali( a.w, b.w, epsilon );
}

static inline bool nearly_equal_vec4f( vec4f a, vec4f b, cgf_t epsilon ) {
  return nearly_equalf( a.x, b.x, epsilon ) &&
         nearly_equalf( a.y, b.y, epsilon ) &&
         nearly_equalf( a.z, b.z, epsilon ) &&
         nearly_equalf( a.w, b.w, epsilon );
}

static inline bool nearly_equal_vec4d( vec4d a, vec4d b, cgd_t epsilon ) {
  return nearly_equald( a.x, b.x, epsilon ) &&
         nearly_equald( a.y, b.y, epsilon ) &&
         nearly_equald( a.z, b.z, epsilon ) &&
         nearly_equald( a.w, b.w, epsilon );
}

static inline bool nearly_equal_quatf( quatf a, quatf b, cgf_t epsilon ) {
  return nearly_equalf( a.x, b.x, epsilon ) &&
         nearly_equalf( a.y, b.y, epsilon ) &&
         nearly_equalf( a.z, b.z, epsilon ) &&
         nearly_equalf( a.w, b.w, epsilon );
}

static inline bool nearly_equal_quatd( quatd a, quatd b, cgd_t epsilon ) {
  return nearly_equald( a.x, b.x, epsilon ) &&
         nearly_equald( a.y, b.y, epsilon ) &&
         nearly_equald( a.z, b.z, epsilon ) &&
         nearly_equald( a.w, b.w, epsilon );
}

static inline bool nearly_equal_mat2f( mat2f a, mat2f b, cgf_t epsilon ) {
  return nearly_equalf( a.m11, b.m11, epsilon ) &&
         nearly_equalf( a.m21, b.m21, epsilon ) &&
         nearly_equalf( a.m12, b.m12, epsilon ) &&
         nearly_equalf( a.m22, b.m22, epsilon );
}

static inline bool nearly_equal_mat2d( mat2d a, mat2d b, cgd_t epsilon ) {
  return nearly_equald( a.m11, b.m11, epsilon ) &&
         nearly_equald( a.m21, b.m21, epsilon ) &&
         nearly_equald( a.m12, b.m12, epsilon ) &&
         nearly_equald( a.m22, b.m22, epsilon );
}

static inline bool nearly_equal_mat3f( mat3f a, mat3f b, cgf_t epsilon ) {
  return nearly_equalf( a.m11, b.m11, epsilon ) &&
         nearly_equalf( a.m21, b.m21, epsilon ) &&
         nearly_equalf( a.m31, b.m31, epsilon ) &&
         nearly_equalf( a.m12, b.m12, epsilon ) &&
         nearly_equalf( a.m22, b.m22, epsilon ) &&
         nearly_equalf( a.m32, b.m32, epsilon ) &&
         nearly_equalf( a.m13, b.m13, epsilon ) &&
         nearly_equalf( a.m23, b.m23, epsilon ) &&
         nearly_equalf( a.m33, b.m33, epsilon );
}

static inline bool nearly_equal_mat3d( mat3d a, mat3d b, cgd_t epsilon ) {
  return nearly_equald( a.m11, b.m11, epsilon ) &&
         nearly_equald( a.m21, b.m21, epsilon ) &&
         nearly_equald( a.m31, b.m31, epsilon ) &&
         nearly_equald( a.m12, b.m12, epsilon ) &&
         nearly_equald( a.m22, b.m22, epsilon ) &&
         nearly_equald( a.m32, b.m32, epsilon ) &&
         nearly_equald( a.m13, b.m13, epsilon ) &&
         nearly_equald( a.m23, b.m23, epsilon ) &&
         nearly_equald( a.m33, b.m33, epsilon );
}

static inline bool nearly_equal_mat4f( mat4f a, mat4f b, cgf_t epsilon ) {
  return nearly_equalf( a.m11, b.m11, epsilon ) &&
         nearly_equalf( a.m21, b.m21, epsilon ) &&
         nearly_equalf( a.m31, b.m31, epsilon ) &&
         nearly_equalf( a.m41, b.m41, epsilon ) &&
         nearly_equalf( a.m12, b.m12, epsilon ) &&
         nearly_equalf( a.m22, b.m22, epsilon ) &&
         nearly_equalf( a.m32, b.m32, epsilon ) &&
         nearly_equalf( a.m42, b.m42, epsilon ) &&
         nearly_equalf( a.m13, b.m13, epsilon ) &&
         nearly_equalf( a.m23, b.m23, epsilon ) &&
         nearly_equalf( a.m33, b.m33, epsilon ) &&
         nearly_equalf( a.m43, b.m43, epsilon ) &&
         nearly_equalf( a.m14, b.m14, epsilon ) &&
         nearly_equalf( a.m24, b.m24, epsilon ) &&
         nearly_equalf( a.m34, b.m34, epsilon ) &&
         nearly_equalf( a.m44, b.m44, epsilon );
}

static inline bool nearly_equal_mat4d( mat4d a, mat4d b, cgd_t epsilon ) {
  return nearly_equald( a.m11, b.m11, epsilon ) &&
         nearly_equald( a.m21, b.m21, epsilon ) &&
         nearly_equald( a.m31, b.m31, epsilon ) &&
         nearly_equald( a.m41, b.m41, epsilon ) &&
         nearly_equald( a.m12, b.m12, epsilon ) &&
         nearly_equald( a.m22, b.m22, epsilon ) &&
         nearly_equald( a.m32, b.m32, epsilon ) &&
         nearly_equald( a.m42, b.m42, epsilon ) &&
         nearly_equald( a.m13, b.m13, epsilon ) &&
         nearly_equald( a.m23, b.m23, epsilon ) &&
         nearly_equald( a.m33, b.m33, epsilon ) &&
         nearly_equald( a.m43, b.m43, epsilon ) &&
         nearly_equald( a.m14, b.m14, epsilon ) &&
         nearly_equald( a.m24, b.m24, epsilon ) &&
         nearly_equald( a.m34, b.m34, epsilon ) &&
         nearly_equald( a.m44, b.m44, epsilon );
}

// compare values nearly with epsilon deviation
#define nearly_equal( a, b, epsilon ) \
  _Generic( ( a ), \
      cgi_t: nearly_equali, \
      cgf_t: nearly_equalf, \
      cgd_t: nearly_equald, \
      vec2i: nearly_equal_vec2i, \
      vec2f: nearly_equal_vec2f, \
      vec2d: nearly_equal_vec2d, \
      vec3i: nearly_equal_vec3i, \
      vec3f: nearly_equal_vec3f, \
      vec3d: nearly_equal_vec3d, \
      vec4i: nearly_equal_vec4i, \
      vec4f: nearly_equal_vec4f, \
      vec4d: nearly_equal_vec4d, \
      quatf: nearly_equal_quatf, \
      quatd: nearly_equal_quatd, \
      mat2f: nearly_equal_mat2f, \
      mat2d: nearly_equal_mat2d, \
      mat3f: nearly_equal_mat3f, \
      mat3d: nearly_equal_mat3d, \
      mat4f: nearly_equal_mat4f, \
      mat4d: nearly_equal_mat4d )( ( a ), ( b ), ( epsilon ) )

static inline cgi_t clampi( cgi_t value, cgi_t min, cgi_t max ) {
  return ( ( ( value ) < ( min ) )
               ? ( min )
               : ( ( ( value ) > ( max ) ) ? ( max ) : ( value ) ) );
}

static inline cgf_t clampf( cgf_t value, cgf_t min, cgf_t max ) {
  return ( ( ( value ) < ( min ) )
               ? ( min )
               : ( ( ( value ) > ( max ) ) ? ( max ) : ( value ) ) );
}

static inline cgd_t clampd( cgd_t value, cgd_t min, cgd_t max ) {
  return ( ( ( value ) < ( min ) )
               ? ( min )
               : ( ( ( value ) > ( max ) ) ? ( max ) : ( value ) ) );
}

static inline vec2i clamp_vec2i( vec2i v, vec2i min, vec2i max ) {
  return (vec2i){ .x = clampi( v.x, min.x, max.x ),
                  .y = clampi( v.y, min.y, max.y ) };
}

static inline vec2f clamp_vec2f( vec2f v, vec2f min, vec2f max ) {
  return (vec2f){ .x = clampf( v.x, min.x, max.x ),
                  .y = clampf( v.y, min.y, max.y ) };
}

static inline vec2d clamp_vec2d( vec2d v, vec2d min, vec2d max ) {
  return (vec2d){ .x = clampd( v.x, min.x, max.x ),
                  .y = clampd( v.y, min.y, max.y ) };
}

static inline vec3i clamp_vec3i( vec3i v, vec3i min, vec3i max ) {
  return (vec3i){ .x = clampi( v.x, min.x, max.x ),
                  .y = clampi( v.y, min.y, max.y ),
                  .z = clampi( v.z, min.z, max.z ) };
}

static inline vec3f clamp_vec3f( vec3f v, vec3f min, vec3f max ) {
  return (vec3f){ .x = clampf( v.x, min.x, max.x ),
                  .y = clampf( v.y, min.y, max.y ),
                  .z = clampf( v.z, min.z, max.z ) };
}

static inline vec3d clamp_vec3d( vec3d v, vec3d min, vec3d max ) {
  return (vec3d){ .x = clampd( v.x, min.x, max.x ),
                  .y = clampd( v.y, min.y, max.y ),
                  .z = clampd( v.z, min.z, max.z ) };
}

static inline vec4i clamp_vec4i( vec4i v, vec4i min, vec4i max ) {
  return (vec4i){ .x = clampi( v.x, min.x, max.x ),
                  .y = clampi( v.y, min.y, max.y ),
                  .z = clampi( v.z, min.z, max.z ),
                  .w = clampi( v.w, min.w, max.w ) };
}

static inline vec4f clamp_vec4f( vec4f v, vec4f min, vec4f max ) {
  return (vec4f){ .x = clampf( v.x, min.x, max.x ),
                  .y = clampf( v.y, min.y, max.y ),
                  .z = clampf( v.z, min.z, max.z ),
                  .w = clampf( v.w, min.w, max.w ) };
}

static inline vec4d clamp_vec4d( vec4d v, vec4d min, vec4d max ) {
  return (vec4d){ .x = clampd( v.x, min.x, max.x ),
                  .y = clampd( v.y, min.y, max.y ),
                  .z = clampd( v.z, min.z, max.z ),
                  .w = clampd( v.w, min.w, max.w ) };
}

// returns value that not less than min and not greater than max
#define clamp( value, min, max ) \
  _Generic( ( value ), \
      cgi_t: clampi, \
      cgf_t: clampf, \
      cgd_t: clampd, \
      vec2i: clamp_vec2i, \
      vec2f: clamp_vec2f, \
      vec2d: clamp_vec2d, \
      vec3i: clamp_vec3i, \
      vec3f: clamp_vec3f, \
      vec3d: clamp_vec3d, \
      vec4i: clamp_vec4i, \
      vec4f: clamp_vec4f, \
      vec4d: clamp_vec4d )( ( value ), ( min ), ( max ) )

static inline cgf_t to_radiansf( cgf_t degrees ) {
  return ( (degrees)*CG_fPI / (cgf_t)180.0 );
}
static inline cgd_t to_radiansd( cgd_t degrees ) {
  return ( (degrees)*CG_dPI / (cgd_t)180.0 );
}

// convert degrees to radians
#define to_radians( degrees ) \
  _Generic( ( degrees ), cgd_t: to_radiansd, cgf_t: to_radiansf )( degrees )

static inline cgf_t to_degreesf( cgf_t radians ) {
  return ( ( radians ) * (cgf_t)180.0 ) / CG_fPI;
}
static inline cgd_t to_degreesd( cgd_t radians ) {
  return ( ( radians ) * (cgd_t)180.0 ) / CG_dPI;
}

// convert radians to degrees
#define to_degrees( radians ) \
  _Generic( ( radians ), cgd_t: to_degreesd, cgf_t: to_degreesf )( radians )

static inline vec2i vec2i_to_vec2i( vec2i v ) { return v; }
static inline vec2i vec2f_to_vec2i( vec2f v ) {
  return (vec2i){ .x = v.x, .y = v.y };
}
static inline vec2i vec2d_to_vec2i( vec2d v ) {
  return (vec2i){ .x = v.x, .y = v.y };
}
static inline vec2i vec3i_to_vec2i( vec3i v ) {
  return (vec2i){ .x = v.x, .y = v.y };
}
static inline vec2i vec3f_to_vec2i( vec3f v ) {
  return (vec2i){ .x = v.x, .y = v.y };
}
static inline vec2i vec3d_to_vec2i( vec3d v ) {
  return (vec2i){ .x = v.x, .y = v.y };
}
static inline vec2i vec4i_to_vec2i( vec4i v ) {
  return (vec2i){ .x = v.x, .y = v.y };
}
static inline vec2i vec4f_to_vec2i( vec4f v ) {
  return (vec2i){ .x = v.x, .y = v.y };
}
static inline vec2i vec4d_to_vec2i( vec4d v ) {
  return (vec2i){ .x = v.x, .y = v.y };
}
static inline vec2f vec2i_to_vec2f( vec2i v ) {
  return (vec2f){ .x = v.x, .y = v.y };
}
static inline vec2f vec2f_to_vec2f( vec2f v ) { return v; }
static inline vec2f vec2d_to_vec2f( vec2d v ) {
  return (vec2f){ .x = v.x, .y = v.y };
}
static inline vec2f vec3i_to_vec2f( vec3i v ) {
  return (vec2f){ .x = v.x, .y = v.y };
}
static inline vec2f vec3f_to_vec2f( vec3f v ) {
  return (vec2f){ .x = v.x, .y = v.y };
}
static inline vec2f vec3d_to_vec2f( vec3d v ) {
  return (vec2f){ .x = v.x, .y = v.y };
}
static inline vec2f vec4i_to_vec2f( vec4i v ) {
  return (vec2f){ .x = v.x, .y = v.y };
}
static inline vec2f vec4f_to_vec2f( vec4f v ) {
  return (vec2f){ .x = v.x, .y = v.y };
}
static inline vec2f vec4d_to_vec2f( vec4d v ) {
  return (vec2f){ .x = v.x, .y = v.y };
}
static inline vec2d vec2i_to_vec2d( vec2i v ) {
  return (vec2d){ .x = v.x, .y = v.y };
}
static inline vec2d vec2f_to_vec2d( vec2f v ) {
  return (vec2d){ .x = v.x, .y = v.y };
}
static inline vec2d vec2d_to_vec2d( vec2d v ) { return v; }
static inline vec2d vec3i_to_vec2d( vec3i v ) {
  return (vec2d){ .x = v.x, .y = v.y };
}
static inline vec2d vec3f_to_vec2d( vec3f v ) {
  return (vec2d){ .x = v.x, .y = v.y };
}
static inline vec2d vec3d_to_vec2d( vec3d v ) {
  return (vec2d){ .x = v.x, .y = v.y };
}
static inline vec2d vec4i_to_vec2d( vec4i v ) {
  return (vec2d){ .x = v.x, .y = v.y };
}
static inline vec2d vec4f_to_vec2d( vec4f v ) {
  return (vec2d){ .x = v.x, .y = v.y };
}
static inline vec2d vec4d_to_vec2d( vec4d v ) {
  return (vec2d){ .x = v.x, .y = v.y };
}
static inline vec3i vec3i_to_vec3i( vec3i v ) { return v; }
static inline vec3i vec3f_to_vec3i( vec3f v ) {
  return (vec3i){ .x = v.x, .y = v.y, .z = v.z };
}
static inline vec3i vec3d_to_vec3i( vec3d v ) {
  return (vec3i){ .x = v.x, .y = v.y, .z = v.z };
}
static inline vec3i vec4i_to_vec3i( vec4i v ) {
  return (vec3i){ .x = v.x, .y = v.y, .z = v.z };
}
static inline vec3i vec4f_to_vec3i( vec4f v ) {
  return (vec3i){ .x = v.x, .y = v.y, .z = v.z };
}
static inline vec3i vec4d_to_vec3i( vec4d v ) {
  return (vec3i){ .x = v.x, .y = v.y, .z = v.z };
}
static inline vec3f vec3i_to_vec3f( vec3i v ) {
  return (vec3f){ .x = v.x, .y = v.y, .z = v.z };
}
static inline vec3f vec3f_to_vec3f( vec3f v ) { return v; }
static inline vec3f vec3d_to_vec3f( vec3d v ) {
  return (vec3f){ .x = v.x, .y = v.y, .z = v.z };
}
static inline vec3f vec4i_to_vec3f( vec4i v ) {
  return (vec3f){ .x = v.x, .y = v.y, .z = v.z };
}
static inline vec3f vec4f_to_vec3f( vec4f v ) {
  return (vec3f){ .x = v.x, .y = v.y, .z = v.z };
}
static inline vec3f vec4d_to_vec3f( vec4d v ) {
  return (vec3f){ .x = v.x, .y = v.y, .z = v.z };
}
static inline vec3d vec3i_to_vec3d( vec3i v ) {
  return (vec3d){ .x = v.x, .y = v.y, .z = v.z };
}
static inline vec3d vec3f_to_vec3d( vec3f v ) {
  return (vec3d){ .x = v.x, .y = v.y, .z = v.z };
}
static inline vec3d vec3d_to_vec3d( vec3d v ) { return v; }
static inline vec3d vec4i_to_vec3d( vec4i v ) {
  return (vec3d){ .x = v.x, .y = v.y, .z = v.z };
}
static inline vec3d vec4f_to_vec3d( vec4f v ) {
  return (vec3d){ .x = v.x, .y = v.y, .z = v.z };
}
static inline vec3d vec4d_to_vec3d( vec4d v ) {
  return (vec3d){ .x = v.x, .y = v.y, .z = v.z };
}

// cast higher vector to vec2 by ignoring other components
#define vec_to_vec2i( vec ) \
  _Generic( ( vec ), \
      vec2i: vec2i_to_vec2i, \
      vec2f: vec2f_to_vec2i, \
      vec2d: vec2d_to_vec2i, \
      vec3i: vec3i_to_vec2i, \
      vec3f: vec3f_to_vec2i, \
      vec3d: vec3d_to_vec2i, \
      vec4i: vec4i_to_vec2i, \
      vec4f: vec4f_to_vec2i, \
      vec4d: vec4d_to_vec2i )( vec )

// cast higher vector to vec2 by ignoring other components
#define vec_to_vec2f( vec ) \
  _Generic( ( vec ), \
      vec2i: vec2i_to_vec2f, \
      vec2f: vec2f_to_vec2f, \
      vec2d: vec2d_to_vec2f, \
      vec3i: vec3i_to_vec2f, \
      vec3f: vec3f_to_vec2f, \
      vec3d: vec3d_to_vec2f, \
      vec4i: vec4i_to_vec2f, \
      vec4f: vec4f_to_vec2f, \
      vec4d: vec4d_to_vec2f )( vec )

// cast higher vector to vec2 by ignoring other components
#define vec_to_vec2d( vec ) \
  _Generic( ( vec ), \
      vec2i: vec2i_to_vec2d, \
      vec2f: vec2f_to_vec2d, \
      vec2d: vec2d_to_vec2d, \
      vec3i: vec3i_to_vec2d, \
      vec3f: vec3f_to_vec2d, \
      vec3d: vec3d_to_vec2d, \
      vec4i: vec4i_to_vec2d, \
      vec4f: vec4f_to_vec2d, \
      vec4d: vec4d_to_vec2d )( vec )

// cast higher vector to vec2 by ignoring other components
#define vec_to_vec2i( vec ) \
  _Generic( ( vec ), \
      vec2i: vec2i_to_vec2i, \
      vec2f: vec2f_to_vec2i, \
      vec2d: vec2d_to_vec2i, \
      vec3i: vec3i_to_vec2i, \
      vec3f: vec3f_to_vec2i, \
      vec3d: vec3d_to_vec2i, \
      vec4i: vec4i_to_vec2i, \
      vec4f: vec4f_to_vec2i, \
      vec4d: vec4d_to_vec2i )( vec )

// cast higher vector to vec2 by ignoring other components
#define vec_to_vec2f( vec ) \
  _Generic( ( vec ), \
      vec2i: vec2i_to_vec2f, \
      vec2f: vec2f_to_vec2f, \
      vec2d: vec2d_to_vec2f, \
      vec3i: vec3i_to_vec2f, \
      vec3f: vec3f_to_vec2f, \
      vec3d: vec3d_to_vec2f, \
      vec4i: vec4i_to_vec2f, \
      vec4f: vec4f_to_vec2f, \
      vec4d: vec4d_to_vec2f )( vec )

// cast higher vector to vec2 by ignoring other components
#define vec_to_vec3i( vec ) \
  _Generic( ( vec ), \
      vec3i: vec3i_to_vec3i, \
      vec3f: vec3f_to_vec3i, \
      vec3d: vec3d_to_vec3i, \
      vec4i: vec4i_to_vec3i, \
      vec4f: vec4f_to_vec3i, \
      vec4d: vec4d_to_vec3i )( vec )

// cast higher vector to vec2 by ignoring other components
#define vec_to_vec3f( vec ) \
  _Generic( ( vec ), \
      vec3i: vec3i_to_vec3f, \
      vec3f: vec3f_to_vec3f, \
      vec3d: vec3d_to_vec3f, \
      vec4i: vec4i_to_vec3f, \
      vec4f: vec4f_to_vec3f, \
      vec4d: vec4d_to_vec3f )( vec )

// cast higher vector to vec2 by ignoring other components
#define vec_to_vec3d( vec ) \
  _Generic( ( vec ), \
      vec3i: vec3i_to_vec3d, \
      vec3f: vec3f_to_vec3d, \
      vec3d: vec3d_to_vec3d, \
      vec4i: vec4i_to_vec3d, \
      vec4f: vec4f_to_vec3d, \
      vec4d: vec4d_to_vec3d )( vec )

static inline bool vec2i_is_zero( vec2i val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool vec2f_is_zero( vec2f val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool vec2d_is_zero( vec2d val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool vec3i_is_zero( vec3i val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool vec3f_is_zero( vec3f val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool vec3d_is_zero( vec3d val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool vec4i_is_zero( vec4i val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool vec4f_is_zero( vec4f val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool vec4d_is_zero( vec4d val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool quatf_is_zero( quatf val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool quatd_is_zero( quatd val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool mat2f_is_zero( mat2f val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool mat2d_is_zero( mat2d val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool mat3f_is_zero( mat3f val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool mat3d_is_zero( mat3d val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool mat4f_is_zero( mat4f val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}
static inline bool mat4d_is_zero( mat4d val ) {
  return ( val ).v[0] == 0 &&
         cg_memcmp( &val, ( (void*)&val ) + 1, sizeof( val ) - 1 ) == 0;
}

#define is_zero( a ) \
  _Generic( ( a ), \
      vec2i: vec2i_is_zero, \
      vec2f: vec2f_is_zero, \
      vec2d: vec2d_is_zero, \
      vec3i: vec3i_is_zero, \
      vec3f: vec3f_is_zero, \
      vec3d: vec3d_is_zero, \
      vec4i: vec4i_is_zero, \
      vec4f: vec4f_is_zero, \
      vec4d: vec4d_is_zero, \
      quatf: quatf_is_zero, \
      quatd: quatd_is_zero, \
      mat2f: mat2f_is_zero, \
      mat2d: mat2d_is_zero, \
      mat3f: mat3f_is_zero, \
      mat3d: mat3d_is_zero, \
      mat4f: mat4f_is_zero, \
      mat4d: mat4d_is_zero )( a )

// get sign of value
#define sign( val ) ( ( val ) > 0 ? 1 : ( ( val ) < 0 ? -1 : 0 ) )

static inline vec2i vec2i_sign( vec2i vec ) {
  return ( (vec2i){ sign( ( vec ).x ), sign( ( vec ).y ) } );
}
static inline vec2f vec2f_sign( vec2f vec ) {
  return ( (vec2f){ sign( ( vec ).x ), sign( ( vec ).y ) } );
}
static inline vec2d vec2d_sign( vec2d vec ) {
  return ( (vec2d){ sign( ( vec ).x ), sign( ( vec ).y ) } );
}
static inline vec3i vec3i_sign( vec3i vec ) {
  return ( (vec3i){ sign( ( vec ).x ), sign( ( vec ).y ), sign( ( vec ).z ) } );
}
static inline vec3f vec3f_sign( vec3f vec ) {
  return ( (vec3f){ sign( ( vec ).x ), sign( ( vec ).y ), sign( ( vec ).z ) } );
}
static inline vec3d vec3d_sign( vec3d vec ) {
  return ( (vec3d){ sign( ( vec ).x ), sign( ( vec ).y ), sign( ( vec ).z ) } );
}
static inline vec4i vec4i_sign( vec4i vec ) {
  return ( (vec4i){ sign( ( vec ).x ), sign( ( vec ).y ), sign( ( vec ).z ),
                    sign( ( vec ).w ) } );
}
static inline vec4f vec4f_sign( vec4f vec ) {
  return ( (vec4f){ sign( ( vec ).x ), sign( ( vec ).y ), sign( ( vec ).z ),
                    sign( ( vec ).w ) } );
}
static inline vec4d vec4d_sign( vec4d vec ) {
  return ( (vec4d){ sign( ( vec ).x ), sign( ( vec ).y ), sign( ( vec ).z ),
                    sign( ( vec ).w ) } );
}

// get signs of each element of vector
#define vec_sign( vec ) \
  _Generic( ( vec ), \
      vec2i: vec2i_sign, \
      vec2f: vec2f_sign, \
      vec2d: vec2d_sign, \
      vec3i: vec3i_sign, \
      vec3f: vec3f_sign, \
      vec3d: vec3d_sign, \
      vec4i: vec4i_sign, \
      vec4f: vec4f_sign, \
      vec4d: vec4d_sign )( vec )

static inline vec2i vec2i_add( vec2i a, vec2i b ) {
  a.x += b.x;
  a.y += b.y;
  return a;
}
static inline vec2f vec2f_add( vec2f a, vec2f b ) {
  a.x += b.x;
  a.y += b.y;
  return a;
}
static inline vec2d vec2d_add( vec2d a, vec2d b ) {
  a.x += b.x;
  a.y += b.y;
  return a;
}
static inline vec3i vec3i_add( vec3i a, vec3i b ) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  return a;
}
static inline vec3f vec3f_add( vec3f a, vec3f b ) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  return a;
}
static inline vec3d vec3d_add( vec3d a, vec3d b ) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  return a;
}
static inline vec4i vec4i_add( vec4i a, vec4i b ) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  a.w += b.w;
  return a;
}
static inline vec4f vec4f_add( vec4f a, vec4f b ) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  a.w += b.w;
  return a;
}
static inline vec4d vec4d_add( vec4d a, vec4d b ) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  a.w += b.w;
  return a;
}
static inline quatf quatf_add( quatf a, quatf b ) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  a.w += b.w;
  return a;
}
static inline quatd quatd_add( quatd a, quatd b ) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  a.w += b.w;
  return a;
}
static inline mat2f mat2f_add( mat2f a, mat2f b ) {
  a.m11 += b.m11;
  a.m21 += b.m21;
  a.m12 += b.m12;
  a.m22 += b.m22;
  return a;
}
static inline mat2d mat2d_add( mat2d a, mat2d b ) {
  a.m11 += b.m11;
  a.m21 += b.m21;
  a.m12 += b.m12;
  a.m22 += b.m22;
  return a;
}

static inline mat3f mat3f_add( mat3f a, mat3f b ) {
  a.m11 += b.m11;
  a.m21 += b.m21;
  a.m31 += b.m31;
  a.m12 += b.m12;
  a.m22 += b.m22;
  a.m32 += b.m32;
  a.m13 += b.m13;
  a.m23 += b.m23;
  a.m33 += b.m33;
  return a;
}

static inline mat3d mat3d_add( mat3d a, mat3d b ) {
  a.m11 += b.m11;
  a.m21 += b.m21;
  a.m31 += b.m31;
  a.m12 += b.m12;
  a.m22 += b.m22;
  a.m32 += b.m32;
  a.m13 += b.m13;
  a.m23 += b.m23;
  a.m33 += b.m33;
  return a;
}

static inline mat4f mat4f_add( mat4f a, mat4f b ) {
  a.m11 += b.m11;
  a.m21 += b.m21;
  a.m31 += b.m31;
  a.m41 += b.m41;
  a.m12 += b.m12;
  a.m22 += b.m22;
  a.m32 += b.m32;
  a.m42 += b.m42;
  a.m13 += b.m13;
  a.m23 += b.m23;
  a.m33 += b.m33;
  a.m43 += b.m43;
  a.m14 += b.m14;
  a.m24 += b.m24;
  a.m34 += b.m34;
  a.m44 += b.m44;
  return a;
}

static inline mat4d mat4d_add( mat4d a, mat4d b ) {
  a.m11 += b.m11;
  a.m21 += b.m21;
  a.m31 += b.m31;
  a.m41 += b.m41;
  a.m12 += b.m12;
  a.m22 += b.m22;
  a.m32 += b.m32;
  a.m42 += b.m42;
  a.m13 += b.m13;
  a.m23 += b.m23;
  a.m33 += b.m33;
  a.m43 += b.m43;
  a.m14 += b.m14;
  a.m24 += b.m24;
  a.m34 += b.m34;
  a.m44 += b.m44;
  return a;
}

// sum a + b
#define add( a, b ) \
  _Generic( ( a ), \
      vec2i: vec2i_add, \
      vec2f: vec2f_add, \
      vec2d: vec2d_add, \
      vec3i: vec3i_add, \
      vec3f: vec3f_add, \
      vec3d: vec3d_add, \
      vec4i: vec4i_add, \
      vec4f: vec4f_add, \
      vec4d: vec4d_add, \
      quatf: quatf_add, \
      quatd: quatd_add, \
      mat2f: mat2f_add, \
      mat2d: mat2d_add, \
      mat3f: mat3f_add, \
      mat3d: mat3d_add, \
      mat4f: mat4f_add, \
      mat4d: mat4d_add )( ( a ), ( b ) )

static inline vec2i vec2i_sub( vec2i a, vec2i b ) {
  a.x -= b.x;
  a.y -= b.y;
  return a;
}
static inline vec2f vec2f_sub( vec2f a, vec2f b ) {
  a.x -= b.x;
  a.y -= b.y;
  return a;
}
static inline vec2d vec2d_sub( vec2d a, vec2d b ) {
  a.x -= b.x;
  a.y -= b.y;
  return a;
}
static inline vec3i vec3i_sub( vec3i a, vec3i b ) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  return a;
}
static inline vec3f vec3f_sub( vec3f a, vec3f b ) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  return a;
}
static inline vec3d vec3d_sub( vec3d a, vec3d b ) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  return a;
}
static inline vec4i vec4i_sub( vec4i a, vec4i b ) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  a.w -= b.w;
  return a;
}
static inline vec4f vec4f_sub( vec4f a, vec4f b ) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  a.w -= b.w;
  return a;
}
static inline vec4d vec4d_sub( vec4d a, vec4d b ) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  a.w -= b.w;
  return a;
}
static inline quatf quatf_sub( quatf a, quatf b ) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  a.w -= b.w;
  return a;
}
static inline quatd quatd_sub( quatd a, quatd b ) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  a.w -= b.w;
  return a;
}
static inline mat2f mat2f_sub( mat2f a, mat2f b ) {
  a.m11 -= b.m11;
  a.m21 -= b.m21;
  a.m12 -= b.m12;
  a.m22 -= b.m22;
  return a;
}
static inline mat2d mat2d_sub( mat2d a, mat2d b ) {
  a.m11 -= b.m11;
  a.m21 -= b.m21;
  a.m12 -= b.m12;
  a.m22 -= b.m22;
  return a;
}

static inline mat3f mat3f_sub( mat3f a, mat3f b ) {
  a.m11 -= b.m11;
  a.m21 -= b.m21;
  a.m31 -= b.m31;
  a.m12 -= b.m12;
  a.m22 -= b.m22;
  a.m32 -= b.m32;
  a.m13 -= b.m13;
  a.m23 -= b.m23;
  a.m33 -= b.m33;
  return a;
}

static inline mat3d mat3d_sub( mat3d a, mat3d b ) {
  a.m11 -= b.m11;
  a.m21 -= b.m21;
  a.m31 -= b.m31;
  a.m12 -= b.m12;
  a.m22 -= b.m22;
  a.m32 -= b.m32;
  a.m13 -= b.m13;
  a.m23 -= b.m23;
  a.m33 -= b.m33;
  return a;
}

static inline mat4f mat4f_sub( mat4f a, mat4f b ) {
  a.m11 -= b.m11;
  a.m21 -= b.m21;
  a.m31 -= b.m31;
  a.m41 -= b.m41;
  a.m12 -= b.m12;
  a.m22 -= b.m22;
  a.m32 -= b.m32;
  a.m42 -= b.m42;
  a.m13 -= b.m13;
  a.m23 -= b.m23;
  a.m33 -= b.m33;
  a.m43 -= b.m43;
  a.m14 -= b.m14;
  a.m24 -= b.m24;
  a.m34 -= b.m34;
  a.m44 -= b.m44;
  return a;
}

static inline mat4d mat4d_sub( mat4d a, mat4d b ) {
  a.m11 -= b.m11;
  a.m21 -= b.m21;
  a.m31 -= b.m31;
  a.m41 -= b.m41;
  a.m12 -= b.m12;
  a.m22 -= b.m22;
  a.m32 -= b.m32;
  a.m42 -= b.m42;
  a.m13 -= b.m13;
  a.m23 -= b.m23;
  a.m33 -= b.m33;
  a.m43 -= b.m43;
  a.m14 -= b.m14;
  a.m24 -= b.m24;
  a.m34 -= b.m34;
  a.m44 -= b.m44;
  return a;
}

// subtract a - b
#define sub( a, b ) \
  _Generic( ( a ), \
      vec2i: vec2i_sub, \
      vec2f: vec2f_sub, \
      vec2d: vec2d_sub, \
      vec3i: vec3i_sub, \
      vec3f: vec3f_sub, \
      vec3d: vec3d_sub, \
      vec4i: vec4i_sub, \
      vec4f: vec4f_sub, \
      vec4d: vec4d_sub, \
      quatf: quatf_sub, \
      quatd: quatd_sub, \
      mat2f: mat2f_sub, \
      mat2d: mat2d_sub, \
      mat3f: mat3f_sub, \
      mat3d: mat3d_sub, \
      mat4f: mat4f_sub, \
      mat4d: mat4d_sub )( ( a ), ( b ) )

static inline vec2i vec2i_add_num( vec2i a, cgi_t b ) {
  a.x += b;
  a.y += b;
  return a;
}
static inline vec2f vec2f_add_num( vec2f a, cgf_t b ) {
  a.x += b;
  a.y += b;
  return a;
}
static inline vec2d vec2d_add_num( vec2d a, cgd_t b ) {
  a.x += b;
  a.y += b;
  return a;
}
static inline vec3i vec3i_add_num( vec3i a, cgi_t b ) {
  a.x += b;
  a.y += b;
  a.z += b;
  return a;
}
static inline vec3f vec3f_add_num( vec3f a, cgf_t b ) {
  a.x += b;
  a.y += b;
  a.z += b;
  return a;
}
static inline vec3d vec3d_add_num( vec3d a, cgd_t b ) {
  a.x += b;
  a.y += b;
  a.z += b;
  return a;
}
static inline vec4i vec4i_add_num( vec4i a, cgi_t b ) {
  a.x += b;
  a.y += b;
  a.z += b;
  a.w += b;
  return a;
}
static inline vec4f vec4f_add_num( vec4f a, cgf_t b ) {
  a.x += b;
  a.y += b;
  a.z += b;
  a.w += b;
  return a;
}
static inline vec4d vec4d_add_num( vec4d a, cgd_t b ) {
  a.x += b;
  a.y += b;
  a.z += b;
  a.w += b;
  return a;
}
static inline quatf quatf_add_num( quatf a, cgf_t b ) {
  a.x += b;
  a.y += b;
  a.z += b;
  a.w += b;
  return a;
}
static inline quatd quatd_add_num( quatd a, cgd_t b ) {
  a.x += b;
  a.y += b;
  a.z += b;
  a.w += b;
  return a;
}
static inline mat2f mat2f_add_num( mat2f a, cgf_t b ) {
  a.m11 += b;
  a.m21 += b;
  a.m12 += b;
  a.m22 += b;
  return a;
}
static inline mat2d mat2d_add_num( mat2d a, cgd_t b ) {
  a.m11 += b;
  a.m21 += b;
  a.m12 += b;
  a.m22 += b;
  return a;
}

static inline mat3f mat3f_add_num( mat3f a, cgf_t b ) {
  a.m11 += b;
  a.m21 += b;
  a.m31 += b;
  a.m12 += b;
  a.m22 += b;
  a.m32 += b;
  a.m13 += b;
  a.m23 += b;
  a.m33 += b;
  return a;
}

static inline mat3d mat3d_add_num( mat3d a, cgd_t b ) {
  a.m11 += b;
  a.m21 += b;
  a.m31 += b;
  a.m12 += b;
  a.m22 += b;
  a.m32 += b;
  a.m13 += b;
  a.m23 += b;
  a.m33 += b;
  return a;
}

static inline mat4f mat4f_add_num( mat4f a, cgf_t b ) {
  a.m11 += b;
  a.m21 += b;
  a.m31 += b;
  a.m41 += b;
  a.m12 += b;
  a.m22 += b;
  a.m32 += b;
  a.m42 += b;
  a.m13 += b;
  a.m23 += b;
  a.m33 += b;
  a.m43 += b;
  a.m14 += b;
  a.m24 += b;
  a.m34 += b;
  a.m44 += b;
  return a;
}

static inline mat4d mat4d_add_num( mat4d a, cgd_t b ) {
  a.m11 += b;
  a.m21 += b;
  a.m31 += b;
  a.m41 += b;
  a.m12 += b;
  a.m22 += b;
  a.m32 += b;
  a.m42 += b;
  a.m13 += b;
  a.m23 += b;
  a.m33 += b;
  a.m43 += b;
  a.m14 += b;
  a.m24 += b;
  a.m34 += b;
  a.m44 += b;
  return a;
}

// sum a + b(scalar)
#define add_num( a, b ) \
  _Generic( ( a ), \
      vec2i: vec2i_add_num, \
      vec2f: vec2f_add_num, \
      vec2d: vec2d_add_num, \
      vec3i: vec3i_add_num, \
      vec3f: vec3f_add_num, \
      vec3d: vec3d_add_num, \
      vec4i: vec4i_add_num, \
      vec4f: vec4f_add_num, \
      vec4d: vec4d_add_num, \
      quatf: quatf_add_num, \
      quatd: quatd_add_num, \
      mat2f: mat2f_add_num, \
      mat2d: mat2d_add_num, \
      mat3f: mat3f_add_num, \
      mat3d: mat3d_add_num, \
      mat4f: mat4f_add_num, \
      mat4d: mat4d_add_num )( ( a ), ( b ) )

static inline vec2i vec2i_multiply( vec2i a, vec2i b ) {
  a.x *= b.x;
  a.y *= b.y;
  return a;
}
static inline vec2f vec2f_multiply( vec2f a, vec2f b ) {
  a.x *= b.x;
  a.y *= b.y;
  return a;
}
static inline vec2d vec2d_multiply( vec2d a, vec2d b ) {
  a.x *= b.x;
  a.y *= b.y;
  return a;
}
static inline vec3i vec3i_multiply( vec3i a, vec3i b ) {
  a.x *= b.x;
  a.y *= b.y;
  a.z *= b.z;
  return a;
}
static inline vec3f vec3f_multiply( vec3f a, vec3f b ) {
  a.x *= b.x;
  a.y *= b.y;
  a.z *= b.z;
  return a;
}
static inline vec3d vec3d_multiply( vec3d a, vec3d b ) {
  a.x *= b.x;
  a.y *= b.y;
  a.z *= b.z;
  return a;
}
static inline vec4i vec4i_multiply( vec4i a, vec4i b ) {
  a.x *= b.x;
  a.y *= b.y;
  a.z *= b.z;
  a.w *= b.z;
  return a;
}
static inline vec4f vec4f_multiply( vec4f a, vec4f b ) {
  a.x *= b.x;
  a.y *= b.y;
  a.z *= b.z;
  a.w *= b.z;
  return a;
}
static inline vec4d vec4d_multiply( vec4d a, vec4d b ) {
  a.x *= b.x;
  a.y *= b.y;
  a.z *= b.z;
  a.w *= b.z;
  return a;
}

static inline quatf quatf_multiply( quatf a, quatf b ) {
  return (quatf){ .x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
                  .y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
                  .z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
                  .w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z };
}

static inline quatd quatd_multiply( quatd a, quatd b ) {
  return (quatd){ .x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
                  .y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
                  .z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
                  .w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z };
}

static inline mat2f mat2f_multiply( mat2f a, mat2f b ) {
  return (mat2f){ .m11 = a.m11 * b.m11 + a.m21 * b.m12,
                  .m12 = a.m12 * b.m11 + a.m22 * b.m12,
                  .m21 = a.m11 * b.m21 + a.m21 * b.m22,
                  .m22 = a.m12 * b.m21 + a.m22 * b.m22 };
}

static inline mat2d mat2d_multiply( mat2d a, mat2d b ) {
  return (mat2d){ .m11 = a.m11 * b.m11 + a.m21 * b.m12,
                  .m12 = a.m12 * b.m11 + a.m22 * b.m12,
                  .m21 = a.m11 * b.m21 + a.m21 * b.m22,
                  .m22 = a.m12 * b.m21 + a.m22 * b.m22 };
}

static inline mat3f mat3f_multiply( mat3f a, mat3f b ) {
  return (mat3f){ .m11 = a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13,
                  .m12 = a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13,
                  .m13 = a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13,

                  .m21 = a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23,
                  .m22 = a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23,
                  .m23 = a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23,

                  .m31 = a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33,
                  .m32 = a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33,
                  .m33 = a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33 };
}

static inline mat3d mat3d_multiply( mat3d a, mat3d b ) {
  return (mat3d){ .m11 = a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13,
                  .m12 = a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13,
                  .m13 = a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13,

                  .m21 = a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23,
                  .m22 = a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23,
                  .m23 = a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23,

                  .m31 = a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33,
                  .m32 = a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33,
                  .m33 = a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33 };
}

static inline mat4f mat4f_multiply( mat4f a, mat4f b ) {
  return (mat4f){
      .m11 = a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13 + a.m41 * b.m14,
      .m12 = a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13 + a.m42 * b.m14,
      .m13 = a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13 + a.m43 * b.m14,
      .m14 = a.m14 * b.m11 + a.m24 * b.m12 + a.m34 * b.m13 + a.m44 * b.m14,

      .m21 = a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23 + a.m41 * b.m24,
      .m22 = a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23 + a.m42 * b.m24,
      .m23 = a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23 + a.m43 * b.m24,
      .m24 = a.m14 * b.m21 + a.m24 * b.m22 + a.m34 * b.m23 + a.m44 * b.m24,

      .m31 = a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33 + a.m41 * b.m34,
      .m32 = a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33 + a.m42 * b.m34,
      .m33 = a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33 + a.m43 * b.m34,
      .m34 = a.m14 * b.m31 + a.m24 * b.m32 + a.m34 * b.m33 + a.m44 * b.m34,

      .m41 = a.m11 * b.m41 + a.m21 * b.m42 + a.m31 * b.m43 + a.m41 * b.m44,
      .m42 = a.m12 * b.m41 + a.m22 * b.m42 + a.m32 * b.m43 + a.m42 * b.m44,
      .m43 = a.m13 * b.m41 + a.m23 * b.m42 + a.m33 * b.m43 + a.m43 * b.m44,
      .m44 = a.m14 * b.m41 + a.m24 * b.m42 + a.m34 * b.m43 + a.m44 * b.m44 };
}

static inline mat4d mat4d_multiply( mat4d a, mat4d b ) {
  return (mat4d){
      .m11 = a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13 + a.m41 * b.m14,
      .m12 = a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13 + a.m42 * b.m14,
      .m13 = a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13 + a.m43 * b.m14,
      .m14 = a.m14 * b.m11 + a.m24 * b.m12 + a.m34 * b.m13 + a.m44 * b.m14,

      .m21 = a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23 + a.m41 * b.m24,
      .m22 = a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23 + a.m42 * b.m24,
      .m23 = a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23 + a.m43 * b.m24,
      .m24 = a.m14 * b.m21 + a.m24 * b.m22 + a.m34 * b.m23 + a.m44 * b.m24,

      .m31 = a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33 + a.m41 * b.m34,
      .m32 = a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33 + a.m42 * b.m34,
      .m33 = a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33 + a.m43 * b.m34,
      .m34 = a.m14 * b.m31 + a.m24 * b.m32 + a.m34 * b.m33 + a.m44 * b.m34,

      .m41 = a.m11 * b.m41 + a.m21 * b.m42 + a.m31 * b.m43 + a.m41 * b.m44,
      .m42 = a.m12 * b.m41 + a.m22 * b.m42 + a.m32 * b.m43 + a.m42 * b.m44,
      .m43 = a.m13 * b.m41 + a.m23 * b.m42 + a.m33 * b.m43 + a.m43 * b.m44,
      .m44 = a.m14 * b.m41 + a.m24 * b.m42 + a.m34 * b.m43 + a.m44 * b.m44 };
}

// multiply a * b
#define multiply( a, b ) \
  _Generic( ( a ), \
      vec2i: vec2i_multiply, \
      vec2f: vec2f_multiply, \
      vec2d: vec2d_multiply, \
      vec3i: vec3i_multiply, \
      vec3f: vec3f_multiply, \
      vec3d: vec3d_multiply, \
      vec4i: vec4i_multiply, \
      vec4f: vec4f_multiply, \
      vec4d: vec4d_multiply, \
      quatf: quatf_multiply, \
      quatd: quatd_multiply, \
      mat2f: mat2f_multiply, \
      mat2d: mat2d_multiply, \
      mat3f: mat3f_multiply, \
      mat3d: mat3d_multiply, \
      mat4f: mat4f_multiply, \
      mat4d: mat4d_multiply )( ( a ), ( b ) )

static inline vec2i vec2i_multiply_num( vec2i a, cgi_t b ) {
  a.x *= b;
  a.y *= b;
  return a;
}
static inline vec2f vec2f_multiply_num( vec2f a, cgf_t b ) {
  a.x *= b;
  a.y *= b;
  return a;
}
static inline vec2d vec2d_multiply_num( vec2d a, cgd_t b ) {
  a.x *= b;
  a.y *= b;
  return a;
}
static inline vec3i vec3i_multiply_num( vec3i a, cgi_t b ) {
  a.x *= b;
  a.y *= b;
  a.z *= b;
  return a;
}
static inline vec3f vec3f_multiply_num( vec3f a, cgf_t b ) {
  a.x *= b;
  a.y *= b;
  a.z *= b;
  return a;
}
static inline vec3d vec3d_multiply_num( vec3d a, cgd_t b ) {
  a.x *= b;
  a.y *= b;
  a.z *= b;
  return a;
}
static inline vec4i vec4i_multiply_num( vec4i a, cgi_t b ) {
  a.x *= b;
  a.y *= b;
  a.z *= b;
  a.w *= b;
  return a;
}
static inline vec4f vec4f_multiply_num( vec4f a, cgf_t b ) {
  a.x *= b;
  a.y *= b;
  a.z *= b;
  a.w *= b;
  return a;
}
static inline vec4d vec4d_multiply_num( vec4d a, cgd_t b ) {
  a.x *= b;
  a.y *= b;
  a.z *= b;
  a.w *= b;
  return a;
}
static inline quatf quatf_multiply_num( quatf a, cgf_t b ) {
  a.x *= b;
  a.y *= b;
  a.z *= b;
  a.w *= b;
  return a;
}
static inline quatd quatd_multiply_num( quatd a, cgd_t b ) {
  a.x *= b;
  a.y *= b;
  a.z *= b;
  a.w *= b;
  return a;
}

static inline mat2f mat2f_multiply_num( mat2f a, cgf_t b ) {
  return (mat2f){
      .m11 = a.m11 * b, .m21 = a.m21 * b, .m12 = a.m12 * b, .m22 = a.m22 * b };
}

static inline mat2d mat2d_multiply_num( mat2d a, cgd_t b ) {
  return (mat2d){
      .m11 = a.m11 * b,
      .m21 = a.m21 * b,
      .m12 = a.m12 * b,
      .m22 = a.m22 * b,
  };
}

static inline mat3f mat3f_multiply_num( mat3f a, cgf_t b ) {
  return (mat3f){
      .m11 = a.m11 * b,
      .m21 = a.m21 * b,
      .m31 = a.m31 * b,
      .m12 = a.m12 * b,
      .m22 = a.m22 * b,
      .m32 = a.m32 * b,
      .m13 = a.m13 * b,
      .m23 = a.m23 * b,
      .m33 = a.m33 * b,
  };
}

static inline mat3d mat3d_multiply_num( mat3d a, cgd_t b ) {
  return (mat3d){
      .m11 = a.m11 * b,
      .m21 = a.m21 * b,
      .m31 = a.m31 * b,
      .m12 = a.m12 * b,
      .m22 = a.m22 * b,
      .m32 = a.m32 * b,
      .m13 = a.m13 * b,
      .m23 = a.m23 * b,
      .m33 = a.m33 * b,
  };
}

static inline mat4f mat4f_multiply_num( mat4f a, cgf_t b ) {
  return (mat4f){
      .m11 = a.m11 * b,
      .m21 = a.m21 * b,
      .m31 = a.m31 * b,
      .m41 = a.m41 * b,
      .m12 = a.m12 * b,
      .m22 = a.m22 * b,
      .m32 = a.m32 * b,
      .m42 = a.m42 * b,
      .m13 = a.m13 * b,
      .m23 = a.m23 * b,
      .m33 = a.m33 * b,
      .m43 = a.m43 * b,
      .m14 = a.m14 * b,
      .m24 = a.m24 * b,
      .m34 = a.m34 * b,
      .m44 = a.m44 * b,
  };
}

static inline mat4d mat4d_multiply_num( mat4d a, cgd_t b ) {
  return (mat4d){
      .m11 = a.m11 * b,
      .m21 = a.m21 * b,
      .m31 = a.m31 * b,
      .m41 = a.m41 * b,
      .m12 = a.m12 * b,
      .m22 = a.m22 * b,
      .m32 = a.m32 * b,
      .m42 = a.m42 * b,
      .m13 = a.m13 * b,
      .m23 = a.m23 * b,
      .m33 = a.m33 * b,
      .m43 = a.m43 * b,
      .m14 = a.m14 * b,
      .m24 = a.m24 * b,
      .m34 = a.m34 * b,
      .m44 = a.m44 * b,
  };
}

// multiply a * b(scalar)
#define multiply_num( a, b ) \
  _Generic( ( a ), \
      vec2i: vec2i_multiply_num, \
      vec2f: vec2f_multiply_num, \
      vec2d: vec2d_multiply_num, \
      vec3i: vec3i_multiply_num, \
      vec3f: vec3f_multiply_num, \
      vec3d: vec3d_multiply_num, \
      vec4i: vec4i_multiply_num, \
      vec4f: vec4f_multiply_num, \
      vec4d: vec4d_multiply_num, \
      quatf: quatf_multiply_num, \
      quatd: quatd_multiply_num, \
      mat2f: mat2f_multiply_num, \
      mat2d: mat2d_multiply_num, \
      mat3f: mat3f_multiply_num, \
      mat3d: mat3d_multiply_num, \
      mat4f: mat4f_multiply_num, \
      mat4d: mat4d_multiply_num )( ( a ), ( b ) )

static inline vec2i vec2i_divide_num( vec2i a, cgi_t b ) {
  a.x /= b;
  a.y /= b;
  return a;
}
static inline vec2f vec2f_divide_num( vec2f a, cgf_t b ) {
  a.x /= b;
  a.y /= b;
  return a;
}
static inline vec2d vec2d_divide_num( vec2d a, cgd_t b ) {
  a.x /= b;
  a.y /= b;
  return a;
}
static inline vec3i vec3i_divide_num( vec3i a, cgi_t b ) {
  a.x /= b;
  a.y /= b;
  a.z /= b;
  return a;
}
static inline vec3f vec3f_divide_num( vec3f a, cgf_t b ) {
  a.x /= b;
  a.y /= b;
  a.z /= b;
  return a;
}
static inline vec3d vec3d_divide_num( vec3d a, cgd_t b ) {
  a.x /= b;
  a.y /= b;
  a.z /= b;
  return a;
}
static inline vec4i vec4i_divide_num( vec4i a, cgi_t b ) {
  a.x /= b;
  a.y /= b;
  a.z /= b;
  a.w /= b;
  return a;
}
static inline vec4f vec4f_divide_num( vec4f a, cgf_t b ) {
  a.x /= b;
  a.y /= b;
  a.z /= b;
  a.w /= b;
  return a;
}
static inline vec4d vec4d_divide_num( vec4d a, cgd_t b ) {
  a.x /= b;
  a.y /= b;
  a.z /= b;
  a.w /= b;
  return a;
}
static inline quatf quatf_divide_num( quatf a, cgf_t b ) {
  a.x /= b;
  a.y /= b;
  a.z /= b;
  a.w /= b;
  return a;
}
static inline quatd quatd_divide_num( quatd a, cgd_t b ) {
  a.x /= b;
  a.y /= b;
  a.z /= b;
  a.w /= b;
  return a;
}

static inline mat2f mat2f_divide_num( mat2f a, cgf_t b ) {
  return (mat2f){
      .m11 = a.m11 / b, .m21 = a.m21 / b, .m12 = a.m12 / b, .m22 = a.m22 / b };
}

static inline mat2d mat2d_divide_num( mat2d a, cgd_t b ) {
  return (mat2d){
      .m11 = a.m11 / b,
      .m21 = a.m21 / b,
      .m12 = a.m12 / b,
      .m22 = a.m22 / b,
  };
}

static inline mat3f mat3f_divide_num( mat3f a, cgf_t b ) {
  return (mat3f){
      .m11 = a.m11 / b,
      .m21 = a.m21 / b,
      .m31 = a.m31 / b,
      .m12 = a.m12 / b,
      .m22 = a.m22 / b,
      .m32 = a.m32 / b,
      .m13 = a.m13 / b,
      .m23 = a.m23 / b,
      .m33 = a.m33 / b,
  };
}

static inline mat3d mat3d_divide_num( mat3d a, cgd_t b ) {
  return (mat3d){
      .m11 = a.m11 / b,
      .m21 = a.m21 / b,
      .m31 = a.m31 / b,
      .m12 = a.m12 / b,
      .m22 = a.m22 / b,
      .m32 = a.m32 / b,
      .m13 = a.m13 / b,
      .m23 = a.m23 / b,
      .m33 = a.m33 / b,
  };
}

static inline mat4f mat4f_divide_num( mat4f a, cgf_t b ) {
  return (mat4f){
      .m11 = a.m11 / b,
      .m21 = a.m21 / b,
      .m31 = a.m31 / b,
      .m41 = a.m41 / b,
      .m12 = a.m12 / b,
      .m22 = a.m22 / b,
      .m32 = a.m32 / b,
      .m42 = a.m42 / b,
      .m13 = a.m13 / b,
      .m23 = a.m23 / b,
      .m33 = a.m33 / b,
      .m43 = a.m43 / b,
      .m14 = a.m14 / b,
      .m24 = a.m24 / b,
      .m34 = a.m34 / b,
      .m44 = a.m44 / b,
  };
}

static inline mat4d mat4d_divide_num( mat4d a, cgd_t b ) {
  return (mat4d){
      .m11 = a.m11 / b,
      .m21 = a.m21 / b,
      .m31 = a.m31 / b,
      .m41 = a.m41 / b,
      .m12 = a.m12 / b,
      .m22 = a.m22 / b,
      .m32 = a.m32 / b,
      .m42 = a.m42 / b,
      .m13 = a.m13 / b,
      .m23 = a.m23 / b,
      .m33 = a.m33 / b,
      .m43 = a.m43 / b,
      .m14 = a.m14 / b,
      .m24 = a.m24 / b,
      .m34 = a.m34 / b,
      .m44 = a.m44 / b,
  };
}

// divide a / b(scalar)
#define divide_num( a, b ) \
  _Generic( ( a ), \
      vec2i: vec2i_divide_num, \
      vec2f: vec2f_divide_num, \
      vec2d: vec2d_divide_num, \
      vec3i: vec3i_divide_num, \
      vec3f: vec3f_divide_num, \
      vec3d: vec3d_divide_num, \
      vec4i: vec4i_divide_num, \
      vec4f: vec4f_divide_num, \
      vec4d: vec4d_divide_num, \
      quatf: quatf_divide_num, \
      quatd: quatd_divide_num, \
      mat2f: mat2f_divide_num, \
      mat2d: mat2d_divide_num, \
      mat3f: mat3f_divide_num, \
      mat3d: mat3d_divide_num, \
      mat4f: mat4f_divide_num, \
      mat4d: mat4d_divide_num )( ( a ), ( b ) )

static inline vec2f vec2f_snap( vec2f v, vec2f grid_size ) {
  return (vec2f){
      .x = CG_fROUND( v.x / grid_size.x ) * grid_size.x,
      .y = CG_fROUND( v.y / grid_size.y ) * grid_size.y,
  };
}

static inline vec2d vec2d_snap( vec2d v, vec2d grid_size ) {
  return (vec2d){
      .x = CG_dROUND( v.x / grid_size.x ) * grid_size.x,
      .y = CG_dROUND( v.y / grid_size.y ) * grid_size.y,
  };
}

static inline vec3f vec3f_snap( vec3f v, vec3f grid_size ) {
  return (vec3f){
      .x = CG_fROUND( v.x / grid_size.x ) * grid_size.x,
      .y = CG_fROUND( v.y / grid_size.y ) * grid_size.y,
      .z = CG_fROUND( v.z / grid_size.z ) * grid_size.z,
  };
}

static inline vec3d vec3d_snap( vec3d v, vec3d grid_size ) {
  return (vec3d){
      .x = CG_dROUND( v.x / grid_size.x ) * grid_size.x,
      .y = CG_dROUND( v.y / grid_size.y ) * grid_size.y,
      .z = CG_dROUND( v.z / grid_size.z ) * grid_size.z,
  };
}

static inline vec4f vec4f_snap( vec4f v, vec4f grid_size ) {
  return (vec4f){
      .x = CG_fROUND( v.x / grid_size.x ) * grid_size.x,
      .y = CG_fROUND( v.y / grid_size.y ) * grid_size.y,
      .z = CG_fROUND( v.z / grid_size.z ) * grid_size.z,
      .w = CG_fROUND( v.w / grid_size.w ) * grid_size.w,
  };
}

static inline vec4d vec4d_snap( vec4d v, vec4d grid_size ) {
  return (vec4d){
      .x = CG_dROUND( v.x / grid_size.x ) * grid_size.x,
      .y = CG_dROUND( v.y / grid_size.y ) * grid_size.y,
      .z = CG_dROUND( v.z / grid_size.z ) * grid_size.z,
      .w = CG_dROUND( v.w / grid_size.w ) * grid_size.w,
  };
}

// Round vector coordinates to snap a grid
#define snap( v, grid_size ) \
  _Generic( ( v ), \
      vec2f: vec2f_snap, \
      vec2d: vec2d_snap, \
      vec3f: vec3f_snap, \
      vec3d: vec3d_snap, \
      vec4f: vec4f_snap, \
      vec4d: vec4d_snap )( ( v ), ( grid_size ) )

static inline vec2f vec2f_snap_num( vec2f v, cgf_t num ) {
  return (vec2f){
      .x = CG_fROUND( v.x / num ) * num,
      .y = CG_fROUND( v.y / num ) * num,
  };
}

static inline vec2d vec2d_snap_num( vec2d v, cgd_t num ) {
  return (vec2d){
      .x = CG_dROUND( v.x / num ) * num,
      .y = CG_dROUND( v.y / num ) * num,
  };
}

static inline vec3f vec3f_snap_num( vec3f v, cgf_t num ) {
  return (vec3f){
      .x = CG_fROUND( v.x / num ) * num,
      .y = CG_fROUND( v.y / num ) * num,
      .z = CG_fROUND( v.z / num ) * num,
  };
}

static inline vec3d vec3d_snap_num( vec3d v, cgd_t num ) {
  return (vec3d){
      .x = CG_dROUND( v.x / num ) * num,
      .y = CG_dROUND( v.y / num ) * num,
      .z = CG_dROUND( v.z / num ) * num,
  };
}

static inline vec4f vec4f_snap_num( vec4f v, cgf_t num ) {
  return (vec4f){
      .x = CG_fROUND( v.x / num ) * num,
      .y = CG_fROUND( v.y / num ) * num,
      .z = CG_fROUND( v.z / num ) * num,
      .w = CG_fROUND( v.w / num ) * num,
  };
}

static inline vec4d vec4d_snap_num( vec4d v, cgd_t num ) {
  return (vec4d){
      .x = CG_dROUND( v.x / num ) * num,
      .y = CG_dROUND( v.y / num ) * num,
      .z = CG_dROUND( v.z / num ) * num,
      .w = CG_dROUND( v.w / num ) * num,
  };
}

// Round vector coordinates to num sized grid
#define snap_num( v, num ) \
  _Generic( ( v ), \
      vec2f: vec2f_snap_num, \
      vec2d: vec2d_snap_num, \
      vec3f: vec3f_snap_num, \
      vec3d: vec3d_snap_num, \
      vec4f: vec4f_snap_num, \
      vec4d: vec4d_snap_num )( ( v ), ( num ) )

static inline vec2i vec2i_negative( vec2i a ) {
  a.x *= -1;
  a.y *= -1;
  return a;
}
static inline vec2f vec2f_negative( vec2f a ) {
  a.x *= -1;
  a.y *= -1;
  return a;
}
static inline vec2d vec2d_negative( vec2d a ) {
  a.x *= -1;
  a.y *= -1;
  return a;
}
static inline vec3i vec3i_negative( vec3i a ) {
  a.x *= -1;
  a.y *= -1;
  a.z *= -1;
  return a;
}
static inline vec3f vec3f_negative( vec3f a ) {
  a.x *= -1;
  a.y *= -1;
  a.z *= -1;
  return a;
}
static inline vec3d vec3d_negative( vec3d a ) {
  a.x *= -1;
  a.y *= -1;
  a.z *= -1;
  return a;
}
static inline vec4i vec4i_negative( vec4i a ) {
  a.x *= -1;
  a.y *= -1;
  a.z *= -1;
  a.w *= -1;
  return a;
}
static inline vec4f vec4f_negative( vec4f a ) {
  a.x *= -1;
  a.y *= -1;
  a.z *= -1;
  a.w *= -1;
  return a;
}
static inline vec4d vec4d_negative( vec4d a ) {
  a.x *= -1;
  a.y *= -1;
  a.z *= -1;
  a.w *= -1;
  return a;
}
static inline quatf quatf_negative( quatf a ) {
  a.x *= -1;
  a.y *= -1;
  a.z *= -1;
  a.w *= -1;
  return a;
}
static inline quatd quatd_negative( quatd a ) {
  a.x *= -1;
  a.y *= -1;
  a.z *= -1;
  a.w *= -1;
  return a;
}

static inline mat2f mat2f_negative( mat2f a ) {
  return (mat2f){ .m11 = a.m11 * -1,
                  .m21 = a.m21 * -1,
                  .m12 = a.m12 * -1,
                  .m22 = a.m22 * -1 };
}

static inline mat2d mat2d_negative( mat2d a ) {
  return (mat2d){
      .m11 = a.m11 * -1,
      .m21 = a.m21 * -1,
      .m12 = a.m12 * -1,
      .m22 = a.m22 * -1,
  };
}

static inline mat3f mat3f_negative( mat3f a ) {
  return (mat3f){
      .m11 = a.m11 * -1,
      .m21 = a.m21 * -1,
      .m31 = a.m31 * -1,
      .m12 = a.m12 * -1,
      .m22 = a.m22 * -1,
      .m32 = a.m32 * -1,
      .m13 = a.m13 * -1,
      .m23 = a.m23 * -1,
      .m33 = a.m33 * -1,
  };
}

static inline mat3d mat3d_negative( mat3d a ) {
  return (mat3d){
      .m11 = a.m11 * -1,
      .m21 = a.m21 * -1,
      .m31 = a.m31 * -1,
      .m12 = a.m12 * -1,
      .m22 = a.m22 * -1,
      .m32 = a.m32 * -1,
      .m13 = a.m13 * -1,
      .m23 = a.m23 * -1,
      .m33 = a.m33 * -1,
  };
}

static inline mat4f mat4f_negative( mat4f a ) {
  return (mat4f){
      .m11 = a.m11 * -1,
      .m21 = a.m21 * -1,
      .m31 = a.m31 * -1,
      .m41 = a.m41 * -1,
      .m12 = a.m12 * -1,
      .m22 = a.m22 * -1,
      .m32 = a.m32 * -1,
      .m42 = a.m42 * -1,
      .m13 = a.m13 * -1,
      .m23 = a.m23 * -1,
      .m33 = a.m33 * -1,
      .m43 = a.m43 * -1,
      .m14 = a.m14 * -1,
      .m24 = a.m24 * -1,
      .m34 = a.m34 * -1,
      .m44 = a.m44 * -1,
  };
}

static inline mat4d mat4d_negative( mat4d a ) {
  return (mat4d){
      .m11 = a.m11 * -1,
      .m21 = a.m21 * -1,
      .m31 = a.m31 * -1,
      .m41 = a.m41 * -1,
      .m12 = a.m12 * -1,
      .m22 = a.m22 * -1,
      .m32 = a.m32 * -1,
      .m42 = a.m42 * -1,
      .m13 = a.m13 * -1,
      .m23 = a.m23 * -1,
      .m33 = a.m33 * -1,
      .m43 = a.m43 * -1,
      .m14 = a.m14 * -1,
      .m24 = a.m24 * -1,
      .m34 = a.m34 * -1,
      .m44 = a.m44 * -1,
  };
}

// invert sign of each element
#define negative( a ) \
  _Generic( ( a ), \
      vec2i: vec2i_negative, \
      vec2f: vec2f_negative, \
      vec2d: vec2d_negative, \
      vec3i: vec3i_negative, \
      vec3f: vec3f_negative, \
      vec3d: vec3d_negative, \
      vec4i: vec4i_negative, \
      vec4f: vec4f_negative, \
      vec4d: vec4d_negative, \
      quatf: quatf_negative, \
      quatd: quatd_negative, \
      mat2f: mat2f_negative, \
      mat2d: mat2d_negative, \
      mat3f: mat3f_negative, \
      mat3d: mat3d_negative, \
      mat4f: mat4f_negative, \
      mat4d: mat4d_negative )( a )

static inline vec2i vec2i_abs( vec2i vec ) {
  return (vec2i){
      .x = CG_iABS( vec.x ),
      .y = CG_iABS( vec.y ),
  };
}
static inline vec2f vec2f_abs( vec2f vec ) {
  return (vec2f){
      .x = CG_fABS( vec.x ),
      .y = CG_fABS( vec.y ),
  };
}
static inline vec2d vec2d_abs( vec2d vec ) {
  return (vec2d){
      .x = CG_dABS( vec.x ),
      .y = CG_dABS( vec.y ),
  };
}
static inline vec3i vec3i_abs( vec3i vec ) {
  return (vec3i){
      .x = CG_iABS( vec.x ), .y = CG_iABS( vec.y ), .z = CG_iABS( vec.z ) };
}
static inline vec3f vec3f_abs( vec3f vec ) {
  return (vec3f){
      .x = CG_fABS( vec.x ), .y = CG_fABS( vec.y ), .z = CG_fABS( vec.z ) };
}
static inline vec3d vec3d_abs( vec3d vec ) {
  return (vec3d){
      .x = CG_dABS( vec.x ), .y = CG_dABS( vec.y ), .z = CG_dABS( vec.z ) };
}
static inline vec4i vec4i_abs( vec4i vec ) {
  return (vec4i){ .x = CG_iABS( vec.x ),
                  .y = CG_iABS( vec.y ),
                  .z = CG_iABS( vec.z ),
                  .w = CG_iABS( vec.w ) };
}
static inline vec4f vec4f_abs( vec4f vec ) {
  return (vec4f){ .x = CG_fABS( vec.x ),
                  .y = CG_fABS( vec.y ),
                  .z = CG_fABS( vec.z ),
                  .w = CG_fABS( vec.w ) };
}
static inline vec4d vec4d_abs( vec4d vec ) {
  return (vec4d){ .x = CG_dABS( vec.x ),
                  .y = CG_dABS( vec.y ),
                  .z = CG_dABS( vec.z ),
                  .w = CG_dABS( vec.w ) };
}

// get each element by module
#define vec_abs( a ) \
  _Generic( ( a ), \
      vec2i: vec2i_abs, \
      vec2f: vec2f_abs, \
      vec2d: vec2d_abs, \
      vec3i: vec3i_abs, \
      vec3f: vec3f_abs, \
      vec3d: vec3d_abs, \
      vec4i: vec4i_abs, \
      vec4f: vec4f_abs, \
      vec4d: vec4d_abs )( a )

static inline vec2i vec2i_max( vec2i a, vec2i b ) {
  return (vec2i){
      .x = CG_MAX( a.x, b.x ),
      .y = CG_MAX( a.y, b.y ),
  };
}
static inline vec2f vec2f_max( vec2f a, vec2f b ) {
  return (vec2f){
      .x = CG_fMAX( a.x, b.x ),
      .y = CG_fMAX( a.y, b.y ),
  };
}
static inline vec2d vec2d_max( vec2d a, vec2d b ) {
  return (vec2d){
      .x = CG_dMAX( a.x, b.x ),
      .y = CG_dMAX( a.y, b.y ),
  };
}
static inline vec3i vec3i_max( vec3i a, vec3i b ) {
  return (vec3i){
      .x = CG_MAX( a.x, b.x ),
      .y = CG_MAX( a.y, b.y ),
      .z = CG_MAX( a.z, b.z ),
  };
}
static inline vec3f vec3f_max( vec3f a, vec3f b ) {
  return (vec3f){
      .x = CG_fMAX( a.x, b.x ),
      .y = CG_fMAX( a.y, b.y ),
      .z = CG_fMAX( a.z, b.z ),
  };
}
static inline vec3d vec3d_max( vec3d a, vec3d b ) {
  return (vec3d){
      .x = CG_dMAX( a.x, b.x ),
      .y = CG_dMAX( a.y, b.y ),
      .z = CG_dMAX( a.z, b.z ),
  };
}
static inline vec4i vec4i_max( vec4i a, vec4i b ) {
  return (vec4i){
      .x = CG_MAX( a.x, b.x ),
      .y = CG_MAX( a.y, b.y ),
      .z = CG_MAX( a.z, b.z ),
      .w = CG_MAX( a.w, b.w ),
  };
}
static inline vec4f vec4f_max( vec4f a, vec4f b ) {
  return (vec4f){
      .x = CG_fMAX( a.x, b.x ),
      .y = CG_fMAX( a.y, b.y ),
      .z = CG_fMAX( a.z, b.z ),
      .w = CG_fMAX( a.w, b.w ),
  };
}
static inline vec4d vec4d_max( vec4d a, vec4d b ) {
  return (vec4d){
      .x = CG_dMAX( a.x, b.x ),
      .y = CG_dMAX( a.y, b.y ),
      .z = CG_dMAX( a.z, b.z ),
      .w = CG_dMAX( a.w, b.w ),
  };
}

// compare and get max element from both. Returns type of input vec
#define vec_max( a, b ) \
  _Generic( ( a ), \
      vec2i: vec2i_max, \
      vec2f: vec2f_max, \
      vec2d: vec2d_max, \
      vec3i: vec3i_max, \
      vec3f: vec3f_max, \
      vec3d: vec3d_max, \
      vec4i: vec4i_max, \
      vec4f: vec4f_max, \
      vec4d: vec4d_max )( ( a ), ( b ) )

static inline vec2i vec2i_min( vec2i a, vec2i b ) {
  return (vec2i){
      .x = CG_MIN( a.x, b.x ),
      .y = CG_MIN( a.y, b.y ),
  };
}
static inline vec2f vec2f_min( vec2f a, vec2f b ) {
  return (vec2f){
      .x = CG_fMIN( a.x, b.x ),
      .y = CG_fMIN( a.y, b.y ),
  };
}
static inline vec2d vec2d_min( vec2d a, vec2d b ) {
  return (vec2d){
      .x = CG_dMIN( a.x, b.x ),
      .y = CG_dMIN( a.y, b.y ),
  };
}
static inline vec3i vec3i_min( vec3i a, vec3i b ) {
  return (vec3i){
      .x = CG_MIN( a.x, b.x ),
      .y = CG_MIN( a.y, b.y ),
      .z = CG_MIN( a.z, b.z ),
  };
}
static inline vec3f vec3f_min( vec3f a, vec3f b ) {
  return (vec3f){
      .x = CG_fMIN( a.x, b.x ),
      .y = CG_fMIN( a.y, b.y ),
      .z = CG_fMIN( a.z, b.z ),
  };
}
static inline vec3d vec3d_min( vec3d a, vec3d b ) {
  return (vec3d){
      .x = CG_dMIN( a.x, b.x ),
      .y = CG_dMIN( a.y, b.y ),
      .z = CG_dMIN( a.z, b.z ),
  };
}
static inline vec4i vec4i_min( vec4i a, vec4i b ) {
  return (vec4i){
      .x = CG_MIN( a.x, b.x ),
      .y = CG_MIN( a.y, b.y ),
      .z = CG_MIN( a.z, b.z ),
      .w = CG_MIN( a.w, b.w ),
  };
}
static inline vec4f vec4f_min( vec4f a, vec4f b ) {
  return (vec4f){
      .x = CG_fMIN( a.x, b.x ),
      .y = CG_fMIN( a.y, b.y ),
      .z = CG_fMIN( a.z, b.z ),
      .w = CG_fMIN( a.w, b.w ),
  };
}
static inline vec4d vec4d_min( vec4d a, vec4d b ) {
  return (vec4d){
      .x = CG_dMIN( a.x, b.x ),
      .y = CG_dMIN( a.y, b.y ),
      .z = CG_dMIN( a.z, b.z ),
      .w = CG_dMIN( a.w, b.w ),
  };
}

// compare and get min element from both. Returns type of input vec
#define vec_min( a, b ) \
  _Generic( ( a ), \
      vec2i: vec2i_min, \
      vec2f: vec2f_min, \
      vec2d: vec2d_min, \
      vec3i: vec3i_min, \
      vec3f: vec3f_min, \
      vec3d: vec3d_min, \
      vec4i: vec4i_min, \
      vec4f: vec4f_min, \
      vec4d: vec4d_min )( ( a ), ( b ) )

static inline vec2i vec2i_clamp( vec2i vec, vec2i min, vec2i max ) {
  return vec_min( vec_max( vec, min ), max );
}
static inline vec2f vec2f_clamp( vec2f vec, vec2f min, vec2f max ) {
  return vec_min( vec_max( vec, min ), max );
}
static inline vec2d vec2d_clamp( vec2d vec, vec2d min, vec2d max ) {
  return vec_min( vec_max( vec, min ), max );
}
static inline vec3i vec3i_clamp( vec3i vec, vec3i min, vec3i max ) {
  return vec_min( vec_max( vec, min ), max );
}
static inline vec3f vec3f_clamp( vec3f vec, vec3f min, vec3f max ) {
  return vec_min( vec_max( vec, min ), max );
}
static inline vec3d vec3d_clamp( vec3d vec, vec3d min, vec3d max ) {
  return vec_min( vec_max( vec, min ), max );
}
static inline vec4i vec4i_clamp( vec4i vec, vec4i min, vec4i max ) {
  return vec_min( vec_max( vec, min ), max );
}
static inline vec4f vec4f_clamp( vec4f vec, vec4f min, vec4f max ) {
  return vec_min( vec_max( vec, min ), max );
}
static inline vec4d vec4d_clamp( vec4d vec, vec4d min, vec4d max ) {
  return vec_min( vec_max( vec, min ), max );
}

// clamp
#define vec_clamp( vec, min, max ) \
  _Generic( ( vec ), \
      vec2i: vec2i_clamp, \
      vec2f: vec2f_clamp, \
      vec2d: vec2d_clamp, \
      vec3i: vec3i_clamp, \
      vec3f: vec3f_clamp, \
      vec3d: vec3d_clamp, \
      vec4i: vec4i_clamp, \
      vec4f: vec4f_clamp, \
      vec4d: vec4d_clamp )( ( vec ), ( min ), ( max ) )

static inline struct vec2i vec2i_tangent( vec2i vec ) {
  return (vec2i){ .x = -vec.y, .y = vec.x };
}
static inline struct vec2f vec2f_tangent( vec2f vec ) {
  return (vec2f){ .x = -vec.y, .y = vec.x };
}
static inline struct vec2d vec2d_tangent( vec2d vec ) {
  return (vec2d){ .x = -vec.y, .y = vec.x };
}

// tangent, normal vector, perpendicular
#define vec_tangent( vec ) \
  _Generic( ( vec ), \
      vec2i: vec2i_tangent, \
      vec2f: vec2f_tangent, \
      vec2d: vec2d_tangent )( vec )

static inline struct vec2i vec2i_cotangent( vec2i vec ) {
  return (vec2i){ .x = vec.y, .y = -vec.x };
}
static inline struct vec2f vec2f_cotangent( vec2f vec ) {
  return (vec2f){ .x = vec.y, .y = -vec.x };
}
static inline struct vec2d vec2d_cotangent( vec2d vec ) {
  return (vec2d){ .x = vec.y, .y = -vec.x };
}

// cotangent, other normal vector, second perpendicular
#define vec_cotangent( vec ) \
  _Generic( ( vec ), \
      vec2i: vec2i_cotangent, \
      vec2f: vec2f_cotangent, \
      vec2d: vec2d_cotangent )( vec )

static inline cgi_t vec2i_cross( vec2i a, vec2i b ) {
  return a.x * b.y - a.y * b.x;
}
static inline cgf_t vec2f_cross( vec2f a, vec2f b ) {
  return a.x * b.y - a.y * b.x;
}
static inline cgd_t vec2d_cross( vec2d a, vec2d b ) {
  return a.x * b.y - a.y * b.x;
}

static inline vec3i vec3i_cross( vec3i a, vec3i b ) {
  return (vec3i){ .x = a.y * b.z - a.z * b.y,
                  .y = a.z * b.x - a.x * b.z,
                  .z = a.x * b.y - a.y * b.x };
}
static inline vec3f vec3f_cross( vec3f a, vec3f b ) {
  return (vec3f){ .x = a.y * b.z - a.z * b.y,
                  .y = a.z * b.x - a.x * b.z,
                  .z = a.x * b.y - a.y * b.x };
}
static inline vec3d vec3d_cross( vec3d a, vec3d b ) {
  return (vec3d){ .x = a.y * b.z - a.z * b.y,
                  .y = a.z * b.x - a.x * b.z,
                  .z = a.x * b.y - a.y * b.x };
}

// vector multiplication of vectors or cross product
#define cross( a, b ) \
  _Generic( ( a ), \
      vec2i: vec2i_cross, \
      vec2f: vec2f_cross, \
      vec2d: vec2d_cross, \
      vec3i: vec3i_cross, \
      vec3f: vec3f_cross, \
      vec3d: vec3d_cross )( ( a ), ( b ) )

static inline cgi_t vec2i_length_squared( vec2i v ) {
  return v.x * v.x + v.y * v.y;
}
static inline cgf_t vec2f_length_squared( vec2f v ) {
  return v.x * v.x + v.y * v.y;
}
static inline cgd_t vec2d_length_squared( vec2d v ) {
  return v.x * v.x + v.y * v.y;
}
static inline cgi_t vec3i_length_squared( vec3i v ) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}
static inline cgf_t vec3f_length_squared( vec3f v ) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}
static inline cgd_t vec3d_length_squared( vec3d v ) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}
static inline cgi_t vec4i_length_squared( vec4i v ) {
  return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}
static inline cgf_t vec4f_length_squared( vec4f v ) {
  return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}
static inline cgd_t vec4d_length_squared( vec4d v ) {
  return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}
static inline cgf_t quatf_length_squared( quatf q ) {
  return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}
static inline cgd_t quatd_length_squared( quatd q ) {
  return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

// length squared. Is much faster than length
#define length_squared( v ) \
  _Generic( ( v ), \
      vec2i: vec2i_length_squared, \
      vec2f: vec2f_length_squared, \
      vec2d: vec2d_length_squared, \
      vec3i: vec3i_length_squared, \
      vec3f: vec3f_length_squared, \
      vec3d: vec3d_length_squared, \
      vec4i: vec4i_length_squared, \
      vec4f: vec4f_length_squared, \
      vec4d: vec4d_length_squared, \
      quatf: quatf_length_squared, \
      quatd: quatd_length_squared )( v )

static inline cgf_t vec2i_length( vec2i v ) {
  return CG_fSQRT( (cgf_t)vec2i_length_squared( v ) );
}
static inline cgf_t vec2f_length( vec2f v ) {
  return CG_fSQRT( vec2f_length_squared( v ) );
}
static inline cgd_t vec2d_length( vec2d v ) {
  return CG_dSQRT( vec2d_length_squared( v ) );
}
static inline cgf_t vec3i_length( vec3i v ) {
  return CG_fSQRT( (cgf_t)vec3i_length_squared( v ) );
}
static inline cgf_t vec3f_length( vec3f v ) {
  return CG_fSQRT( vec3f_length_squared( v ) );
}
static inline cgd_t vec3d_length( vec3d v ) {
  return CG_dSQRT( vec3d_length_squared( v ) );
}
static inline cgf_t vec4i_length( vec4i v ) {
  return CG_fSQRT( (cgf_t)vec4i_length_squared( v ) );
}
static inline cgf_t vec4f_length( vec4f v ) {
  return CG_fSQRT( vec4f_length_squared( v ) );
}
static inline cgd_t vec4d_length( vec4d v ) {
  return CG_dSQRT( vec4d_length_squared( v ) );
}
static inline cgf_t quatf_length( quatf q ) {
  return CG_fSQRT( quatf_length_squared( q ) );
}
static inline cgd_t quatd_length( quatd q ) {
  return CG_dSQRT( quatd_length_squared( q ) );
}

// length of vector
#define length( v ) \
  _Generic( ( v ), \
      vec2i: vec2i_length, \
      vec2f: vec2f_length, \
      vec2d: vec2d_length, \
      vec3i: vec3i_length, \
      vec3f: vec3f_length, \
      vec3d: vec3d_length, \
      vec4i: vec4i_length, \
      vec4f: vec4f_length, \
      vec4d: vec4d_length, \
      quatf: quatf_length, \
      quatd: quatd_length )( v )

static inline vec2f vec2f_normalize( vec2f v ) {
  cgf_t l = length( v );
  return ( l > 0.0f ) ? (vec2f){ .x = v.x / l, .y = v.y / l } : (vec2f){ 0 };
}
static inline vec2d vec2d_normalize( vec2d v ) {
  cgd_t l = length( v );
  return ( l > 0.0 ) ? (vec2d){ .x = v.x / l, .y = v.y / l } : (vec2d){ 0 };
}

static inline vec3f vec3f_normalize( vec3f v ) {
  cgf_t l = length( v );
  return ( l > 0.0f ) ? (vec3f){ .x = v.x / l, .y = v.y / l, .z = v.z / l }
                      : (vec3f){ 0 };
}

static inline vec3d vec3d_normalize( vec3d v ) {
  cgd_t l = length( v );
  return ( l > 0.0 ) ? (vec3d){ .x = v.x / l, .y = v.y / l, .z = v.z / l }
                     : (vec3d){ 0 };
}

static inline vec4f vec4f_normalize( vec4f v ) {
  cgf_t l = length( v );
  return ( l > 0.0f )
             ? (vec4f){ .x = v.x / l, .y = v.y / l, .z = v.z / l, .w = v.w / l }
             : (vec4f){ 0 };
}
static inline vec4d vec4d_normalize( vec4d v ) {
  cgd_t l = length( v );
  return ( l > 0.0 )
             ? (vec4d){ .x = v.x / l, .y = v.y / l, .z = v.z / l, .w = v.w / l }
             : (vec4d){ 0 };
}

static inline quatf quatf_normalize( quatf q ) {
  cgd_t l = length( q );
  return ( l > 0.0 )
             ? (quatf){ .x = q.x / l, .y = q.y / l, .z = q.z / l, .w = q.w / l }
             : (quatf){ 0 };
}

static inline quatd quatd_normalize( quatd q ) {
  cgd_t l = length( q );
  return ( l > 0.0 )
             ? (quatd){ .x = q.x / l, .y = q.y / l, .z = q.z / l, .w = q.w / l }
             : (quatd){ 0 };
}

// normalize, make length = 1
#define normalize( v ) \
  _Generic( ( v ), \
      vec2f: vec2f_normalize, \
      vec2d: vec2d_normalize, \
      vec3f: vec3f_normalize, \
      vec3d: vec3d_normalize, \
      vec4f: vec4f_normalize, \
      vec4d: vec4d_normalize, \
      quatf: quatf_normalize, \
      quatd: quatd_normalize )( v )

static inline cgi_t vec2i_dot( vec2i a, vec2i b ) {
  return a.x * b.x + a.y * b.y;
}
static inline cgf_t vec2f_dot( vec2f a, vec2f b ) {
  return a.x * b.x + a.y * b.y;
}
static inline cgd_t vec2d_dot( vec2d a, vec2d b ) {
  return a.x * b.x + a.y * b.y;
}
static inline cgi_t vec3i_dot( vec3i a, vec3i b ) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
static inline cgf_t vec3f_dot( vec3f a, vec3f b ) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
static inline cgd_t vec3d_dot( vec3d a, vec3d b ) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
static inline cgi_t vec4i_dot( vec4i a, vec4i b ) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
static inline cgf_t vec4f_dot( vec4f a, vec4f b ) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
static inline cgd_t vec4d_dot( vec4d a, vec4d b ) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
static inline cgf_t quatf_dot( quatf a, quatf b ) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
static inline cgd_t quatd_dot( quatd a, quatd b ) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// Scalar multiplication of vectors
#define dot( a, b ) \
  _Generic( ( a ), \
      vec2i: vec2i_dot, \
      vec2f: vec2f_dot, \
      vec2d: vec2d_dot, \
      vec3i: vec3i_dot, \
      vec3f: vec3f_dot, \
      vec3d: vec3d_dot, \
      vec4i: vec4i_dot, \
      vec4f: vec4f_dot, \
      vec4d: vec4d_dot, \
      quatf: quatf_dot, \
      quatd: quatd_dot )( ( a ), ( b ) )

static inline vec2f vec2f_project( vec2f a, vec2f b ) {
  cgf_t d = vec2f_dot( b, b );
  if( d < CG_fEPSILON )
    return (vec2f){ 0 };
  cgf_t s = vec2f_dot( a, b ) / d;
  return (vec2f){ .x = b.x * s, .y = b.y * s };
}

static inline vec2d vec2d_project( vec2d a, vec2d b ) {
  cgd_t d = vec2d_dot( b, b );
  if( d < CG_dEPSILON )
    return (vec2d){ 0 };
  cgd_t s = vec2d_dot( a, b ) / d;
  return (vec2d){ .x = b.x * s, .y = b.y * s };
}

static inline vec3f vec3f_project( vec3f a, vec3f b ) {
  cgf_t d = vec3f_dot( b, b );
  if( d < CG_fEPSILON )
    return (vec3f){ 0 };
  cgf_t s = vec3f_dot( a, b ) / d;
  return (vec3f){ .x = b.x * s, .y = b.y * s, .z = b.z * s };
}

static inline vec3d vec3d_project( vec3d a, vec3d b ) {
  cgd_t d = vec3d_dot( b, b );
  if( d < CG_dEPSILON )
    return (vec3d){ 0 };
  cgd_t s = vec3d_dot( a, b ) / d;
  return (vec3d){ .x = b.x * s, .y = b.y * s, .z = b.z * s };
}

static inline vec4f vec4f_project( vec4f a, vec4f b ) {
  cgf_t d = vec4f_dot( b, b );
  if( d < CG_fEPSILON )
    return (vec4f){ 0 };
  cgf_t s = vec4f_dot( a, b ) / d;
  return (vec4f){ .x = b.x * s, .y = b.y * s, .z = b.z * s, .w = b.w * s };
}

static inline vec4d vec4d_project( vec4d a, vec4d b ) {
  cgd_t d = vec4d_dot( b, b );
  if( d < CG_dEPSILON )
    return (vec4d){ 0 };
  cgd_t s = vec4d_dot( a, b ) / d;
  return (vec4d){ .x = b.x * s, .y = b.y * s, .z = b.z * s, .w = b.w * s };
}

// Project vector on vector
#define vec_project( a, b ) \
  _Generic( ( a ), \
      vec2f: vec2f_project, \
      vec2d: vec2d_project, \
      vec3f: vec3f_project, \
      vec3d: vec3d_project, \
      vec4f: vec4f_project, \
      vec4d: vec4d_project )( ( a ), ( b ) )

static inline vec2f vec2f_slide( vec2f v, vec2f normal ) {
  cgf_t d = dot( v, normal );
  return (vec2f){ .x = v.x - normal.x * d, .y = v.y - normal.y * d };
}
static inline vec2d vec2d_slide( vec2d v, vec2d normal ) {
  cgd_t d = dot( v, normal );
  return (vec2d){ .x = v.x - normal.x * d, .y = v.y - normal.y * d };
}

static inline vec3f vec3f_slide( vec3f v, vec3f normal ) {
  cgf_t d = dot( v, normal );
  return (vec3f){ .x = v.x - normal.x * d,
                  .y = v.y - normal.y * d,
                  .z = v.z - normal.z * d };
}
static inline vec3d vec3d_slide( vec3d v, vec3d normal ) {
  cgd_t d = dot( v, normal );
  return (vec3d){ .x = v.x - normal.x * d,
                  .y = v.y - normal.y * d,
                  .z = v.z - normal.z * d };
}

static inline vec4f vec4f_slide( vec4f v, vec4f normal ) {
  cgf_t d = dot( v, normal );
  return (vec4f){ .x = v.x - normal.x * d,
                  .y = v.y - normal.y * d,
                  .z = v.z - normal.z * d,
                  .w = v.w - normal.w * d };
}

static inline vec4d vec4d_slide( vec4d v, vec4d normal ) {
  cgd_t d = dot( v, normal );
  return (vec4d){ .x = v.x - normal.x * d,
                  .y = v.y - normal.y * d,
                  .z = v.z - normal.z * d,
                  .w = v.w - normal.w * d };
}

// slide along normal
#define vec_slide( v, normal ) \
  _Generic( ( v ), \
      vec2f: vec2f_slide, \
      vec2d: vec2d_slide, \
      vec3f: vec3f_slide, \
      vec3d: vec3d_slide, \
      vec4f: vec4f_slide, \
      vec4d: vec4d_slide )( ( v ), ( normal ) )

static inline vec2f vec2f_reflect( vec2f v, vec2f normal ) {
  cgf_t d2 = dot( v, normal ) * 2.0f;
  return (vec2f){ .x = v.x - normal.x * d2, .y = v.y - normal.y * d2 };
}

static inline vec2d vec2d_reflect( vec2d v, vec2d normal ) {
  cgd_t d2 = dot( v, normal ) * 2.0;
  return (vec2d){ .x = v.x - normal.x * d2, .y = v.y - normal.y * d2 };
}

static inline vec3f vec3f_reflect( vec3f v, vec3f normal ) {
  cgf_t d2 = dot( v, normal ) * 2.0f;
  return (vec3f){ .x = v.x - normal.x * d2,
                  .y = v.y - normal.y * d2,
                  .z = v.z - normal.z * d2 };
}
static inline vec3d vec3d_reflect( vec3d v, vec3d normal ) {
  cgd_t d2 = dot( v, normal ) * 2.0;
  return (vec3d){ .x = v.x - normal.x * d2,
                  .y = v.y - normal.y * d2,
                  .z = v.z - normal.z * d2 };
}

static inline vec4f vec4f_reflect( vec4f v, vec4f normal ) {
  cgf_t d2 = dot( v, normal ) * 2.0f;
  return (vec4f){ .x = v.x - normal.x * d2,
                  .y = v.y - normal.y * d2,
                  .z = v.z - normal.z * d2,
                  .w = v.w - d2 * normal.w };
}

static inline vec4d vec4d_reflect( vec4d v, vec4d normal ) {
  cgd_t d2 = dot( v, normal ) * 2.0f;
  return (vec4d){ .x = v.x - normal.x * d2,
                  .y = v.y - normal.y * d2,
                  .z = v.z - normal.z * d2,
                  .w = v.w - d2 * normal.w };
}

// vector of reflection
#define vec_reflect( v, normal ) \
  _Generic( ( v ), \
      vec2f: vec2f_reflect, \
      vec2d: vec2d_reflect, \
      vec3f: vec3f_reflect, \
      vec3d: vec3d_reflect, \
      vec4f: vec4f_reflect, \
      vec4d: vec4d_reflect )( ( v ), ( normal ) )

static inline vec2f vec2f_lerp( vec2f a, vec2f b, cgf_t t ) {
  return (vec2f){ .x = a.x + ( b.x - a.x ) * t, .y = a.y + ( b.y - a.y ) * t };
}
static inline vec2d vec2d_lerp( vec2d a, vec2d b, cgd_t t ) {
  return (vec2d){ .x = a.x + ( b.x - a.x ) * t, .y = a.y + ( b.y - a.y ) * t };
}

static inline vec3f vec3f_lerp( vec3f a, vec3f b, cgf_t t ) {
  return (vec3f){ .x = a.x + ( b.x - a.x ) * t,
                  .y = a.y + ( b.y - a.y ) * t,
                  .z = a.z + ( b.z - a.z ) * t };
}
static inline vec3d vec3d_lerp( vec3d a, vec3d b, cgd_t t ) {
  return (vec3d){ .x = a.x + ( b.x - a.x ) * t,
                  .y = a.y + ( b.y - a.y ) * t,
                  .z = a.z + ( b.z - a.z ) * t };
}

static inline vec4f vec4f_lerp( vec4f a, vec4f b, cgf_t t ) {
  return (vec4f){ .x = a.x + ( b.x - a.x ) * t,
                  .y = a.y + ( b.y - a.y ) * t,
                  .z = a.z + ( b.z - a.z ) * t,
                  .w = a.w + ( b.w - a.w ) * t };
}
static inline vec4d vec4d_lerp( vec4d a, vec4d b, cgd_t t ) {
  return (vec4d){ .x = a.x + ( b.x - a.x ) * t,
                  .y = a.y + ( b.y - a.y ) * t,
                  .z = a.z + ( b.z - a.z ) * t,
                  .w = a.w + ( b.w - a.w ) * t };
}

static inline quatf quatf_lerp( quatf a, quatf b, cgf_t t ) {
  return (quatf){ .x = a.x + ( b.x - a.x ) * t,
                  .y = a.y + ( b.y - a.y ) * t,
                  .z = a.z + ( b.z - a.z ) * t,
                  .w = a.w + ( b.w - a.w ) * t };
}
static inline quatd quatd_lerp( quatd a, quatd b, cgd_t t ) {
  return (quatd){ .x = a.x + ( b.x - a.x ) * t,
                  .y = a.y + ( b.y - a.y ) * t,
                  .z = a.z + ( b.z - a.z ) * t,
                  .w = a.w + ( b.w - a.w ) * t };
}

static inline mat2f mat2f_lerp( mat2f a, mat2f b, cgf_t t ) {
  return (mat2f){ .m11 = a.m11 + ( b.m11 - a.m11 ) * t,
                  .m12 = a.m12 + ( b.m12 - a.m12 ) * t,
                  .m21 = a.m21 + ( b.m21 - a.m21 ) * t,
                  .m22 = a.m22 + ( b.m22 - a.m22 ) * t };
}

static inline mat2d mat2d_lerp( mat2d a, mat2d b, cgd_t t ) {
  return (mat2d){ .m11 = a.m11 + ( b.m11 - a.m11 ) * t,
                  .m12 = a.m12 + ( b.m12 - a.m12 ) * t,
                  .m21 = a.m21 + ( b.m21 - a.m21 ) * t,
                  .m22 = a.m22 + ( b.m22 - a.m22 ) * t };
}

static inline mat3f mat3f_lerp( mat3f a, mat3f b, cgf_t t ) {
  return (mat3f){ .m11 = a.m11 + ( b.m11 - a.m11 ) * t,
                  .m12 = a.m12 + ( b.m12 - a.m12 ) * t,
                  .m13 = a.m13 + ( b.m13 - a.m13 ) * t,
                  .m21 = a.m21 + ( b.m21 - a.m21 ) * t,
                  .m22 = a.m22 + ( b.m22 - a.m22 ) * t,
                  .m23 = a.m23 + ( b.m23 - a.m23 ) * t,
                  .m31 = a.m31 + ( b.m31 - a.m31 ) * t,
                  .m32 = a.m32 + ( b.m32 - a.m32 ) * t,
                  .m33 = a.m33 + ( b.m33 - a.m33 ) * t };
}

static inline mat3d mat3d_lerp( mat3d a, mat3d b, cgd_t t ) {
  return (mat3d){ .m11 = a.m11 + ( b.m11 - a.m11 ) * t,
                  .m12 = a.m12 + ( b.m12 - a.m12 ) * t,
                  .m13 = a.m13 + ( b.m13 - a.m13 ) * t,
                  .m21 = a.m21 + ( b.m21 - a.m21 ) * t,
                  .m22 = a.m22 + ( b.m22 - a.m22 ) * t,
                  .m23 = a.m23 + ( b.m23 - a.m23 ) * t,
                  .m31 = a.m31 + ( b.m31 - a.m31 ) * t,
                  .m32 = a.m32 + ( b.m32 - a.m32 ) * t,
                  .m33 = a.m33 + ( b.m33 - a.m33 ) * t };
}

static inline mat4f mat4f_lerp( mat4f a, mat4f b, cgf_t t ) {
  return (mat4f){ .m11 = a.m11 + ( b.m11 - a.m11 ) * t,
                  .m12 = a.m12 + ( b.m12 - a.m12 ) * t,
                  .m13 = a.m13 + ( b.m13 - a.m13 ) * t,
                  .m14 = a.m14 + ( b.m14 - a.m14 ) * t,
                  .m21 = a.m21 + ( b.m21 - a.m21 ) * t,
                  .m22 = a.m22 + ( b.m22 - a.m22 ) * t,
                  .m23 = a.m23 + ( b.m23 - a.m23 ) * t,
                  .m24 = a.m24 + ( b.m24 - a.m24 ) * t,
                  .m31 = a.m31 + ( b.m31 - a.m31 ) * t,
                  .m32 = a.m32 + ( b.m32 - a.m32 ) * t,
                  .m33 = a.m33 + ( b.m33 - a.m33 ) * t,
                  .m34 = a.m34 + ( b.m34 - a.m34 ) * t,
                  .m41 = a.m41 + ( b.m41 - a.m41 ) * t,
                  .m42 = a.m42 + ( b.m42 - a.m42 ) * t,
                  .m43 = a.m43 + ( b.m43 - a.m43 ) * t,
                  .m44 = a.m44 + ( b.m44 - a.m44 ) * t };
}

static inline mat4d mat4d_lerp( mat4d a, mat4d b, cgd_t t ) {
  return (mat4d){ .m11 = a.m11 + ( b.m11 - a.m11 ) * t,
                  .m12 = a.m12 + ( b.m12 - a.m12 ) * t,
                  .m13 = a.m13 + ( b.m13 - a.m13 ) * t,
                  .m14 = a.m14 + ( b.m14 - a.m14 ) * t,
                  .m21 = a.m21 + ( b.m21 - a.m21 ) * t,
                  .m22 = a.m22 + ( b.m22 - a.m22 ) * t,
                  .m23 = a.m23 + ( b.m23 - a.m23 ) * t,
                  .m24 = a.m24 + ( b.m24 - a.m24 ) * t,
                  .m31 = a.m31 + ( b.m31 - a.m31 ) * t,
                  .m32 = a.m32 + ( b.m32 - a.m32 ) * t,
                  .m33 = a.m33 + ( b.m33 - a.m33 ) * t,
                  .m34 = a.m34 + ( b.m34 - a.m34 ) * t,
                  .m41 = a.m41 + ( b.m41 - a.m41 ) * t,
                  .m42 = a.m42 + ( b.m42 - a.m42 ) * t,
                  .m43 = a.m43 + ( b.m43 - a.m43 ) * t,
                  .m44 = a.m44 + ( b.m44 - a.m44 ) * t };
}

// linear interpolation
#define lerp( a, b, t ) \
  _Generic( ( a ), \
      vec2f: vec2f_lerp, \
      vec2d: vec2d_lerp, \
      vec3f: vec3f_lerp, \
      vec3d: vec3d_lerp, \
      vec4f: vec4f_lerp, \
      vec4d: vec4d_lerp, \
      quatf: quatf_lerp, \
      quatd: quatd_lerp, \
      mat2f: mat2f_lerp, \
      mat2d: mat2d_lerp, \
      mat3f: mat3f_lerp, \
      mat3d: mat3d_lerp, \
      mat4f: mat4f_lerp, \
      mat4d: mat4d_lerp )( ( a ), ( b ), ( t ) )

static inline vec2f vec2f_from_angle( cgf_t radians ) {
#ifdef CGEOM_PRECISE_TRIGONOMETRY
  sincos1cos sc1c = sncs1cs( radians );
  cgd_t c = sc1c.cos;
  cgd_t s = sc1c.sin;
#else
  cgf_t c = CG_fCOS( radians );
  cgf_t s = CG_fSIN( radians );
#endif

  return (vec2f){ .x = c, .y = s };
}

static inline vec2d vec2d_from_angle( cgd_t radians ) {
#ifdef CGEOM_PRECISE_TRIGONOMETRY
  sincos1cos sc1c = sncs1cs( radians );
  cgd_t c = sc1c.cos;
  cgd_t s = sc1c.sin;
#else
  cgd_t c = CG_dCOS( radians );
  cgd_t s = CG_dSIN( radians );
#endif
  return (vec2d){ .x = c, .y = s };
}

static inline vec2f vec2f_rotate( vec2f vec, cgf_t radians ) {
#ifdef CGEOM_PRECISE_TRIGONOMETRY
  sincos1cos sc1c = sncs1cs( radians );
  cgd_t c = sc1c.cos;
  cgd_t s = sc1c.sin;
#else
  cgf_t c = CG_fCOS( radians );
  cgf_t s = CG_fSIN( radians );
#endif
  return (vec2f){ .x = vec.x * c - vec.y * s, .y = vec.x * s + vec.y * c };
}

static inline vec2d vec2d_rotate( vec2d vec, cgd_t radians ) {
#ifdef CGEOM_PRECISE_TRIGONOMETRY
  sincos1cos sc1c = sncs1cs( radians );
  cgd_t c = sc1c.cos;
  cgd_t s = sc1c.sin;
#else
  cgd_t c = CG_dCOS( radians );
  cgd_t s = CG_dSIN( radians );
#endif
  return (vec2d){ .x = vec.x * c - vec.y * s, .y = vec.x * s + vec.y * c };
}

// vector2 rotate on radians angle
#define vec2_rotate( vec, radians ) \
  _Generic( ( vec ), vec2f: vec2f_rotate, vec2d: vec2d_rotate )( ( vec ), \
                                                                 ( radians ) )

static inline vec3f vec3f_rotate( vec3f v, vec3f axis, cgf_t radians ) {
#ifdef CGEOM_PRECISE_TRIGONOMETRY
  sincos1cos sc1c = sncs1cs( radians );
  cgd_t c = sc1c.cos;
  cgd_t s = sc1c.sin;
  cgd_t one_c = sc1c.omc;
#else
  cgf_t c = CG_fCOS( radians );
  cgf_t s = CG_fSIN( radians );
  cgf_t one_c = (cgd_t)( 1.0 ) - c;
#endif

  cgf_t dot = dot( v, axis );
  vec3f cross = cross( axis, v );

  return (vec3f){ .x = v.x * c + cross.x * s + axis.x * dot * one_c,
                  .y = v.y * c + cross.y * s + axis.y * dot * one_c,
                  .z = v.z * c + cross.z * s + axis.z * dot * one_c };
}

static inline vec3d vec3d_rotate( vec3d v, vec3d axis, cgd_t radians ) {
#ifdef CGEOM_PRECISE_TRIGONOMETRY
  sincos1cos sc1c = sncs1cs( radians );
  cgd_t c = sc1c.cos;
  cgd_t s = sc1c.sin;
  cgd_t one_c = sc1c.omc;
#else
  cgd_t c = CG_dCOS( radians );
  cgd_t s = CG_dSIN( radians );
  cgd_t one_c = (cgd_t)( 1.0 ) - c;
#endif

  cgd_t dot = dot( v, axis );
  vec3d cross = cross( axis, v );

  return (vec3d){ .x = v.x * c + cross.x * s + axis.x * dot * one_c,
                  .y = v.y * c + cross.y * s + axis.y * dot * one_c,
                  .z = v.z * c + cross.z * s + axis.z * dot * one_c };
}

// vector3 rotate on radians angle
#define vec3_rotate( vec, axis, radians ) \
  _Generic( ( vec ), vec3f: vec3f_rotate, vec3d: vec3d_rotate )( \
      ( vec ), ( axis ), ( radians ) )

static inline vec3i vec3i_rotate( vec3i vec, enum cgcorner_vector cv ) {
  const cgi_t* matrix = (const cgi_t*)&cg_ortho_bases[cv];

  vec.v[CG_X] = matrix[CG_X * 3 + CG_X] * vec.v[CG_X] +
                matrix[CG_Y * 3 + CG_X] * vec.v[CG_Y] +
                matrix[CG_Z * 3 + CG_X] * vec.v[CG_Z];
  vec.v[CG_Y] = matrix[CG_X * 3 + CG_Y] * vec.v[CG_X] +
                matrix[CG_Y * 3 + CG_Y] * vec.v[CG_Y] +
                matrix[CG_Z * 3 + CG_Y] * vec.v[CG_Z];
  vec.v[CG_Z] = matrix[CG_X * 3 + CG_Z] * vec.v[CG_X] +
                matrix[CG_Y * 3 + CG_Z] * vec.v[CG_Y] +
                matrix[CG_Z * 3 + CG_Z] * vec.v[CG_Z];
  return vec;
}

static inline vec2f vec2f_bezier3( vec2f v0, vec2f v1, vec2f v2, cgf_t f ) {
  return lerp( lerp( v0, v1, f ), lerp( v1, v2, f ), f );
}

static inline vec2d vec2d_bezier3( vec2d v0, vec2d v1, vec2d v2, cgd_t f ) {
  return lerp( lerp( v0, v1, f ), lerp( v1, v2, f ), f );
}

static inline vec3f vec3f_bezier3( vec3f v0, vec3f v1, vec3f v2, cgf_t f ) {
  return lerp( lerp( v0, v1, f ), lerp( v1, v2, f ), f );
}

static inline vec3d vec3d_bezier3( vec3d v0, vec3d v1, vec3d v2, cgd_t f ) {
  return lerp( lerp( v0, v1, f ), lerp( v1, v2, f ), f );
}

// bezier3
#define bezier3( v0, v1, v2, f ) \
  _Generic( ( v0 ), \
      vec2f: vec2f_bezier3, \
      vec2d: vec2d_bezier3, \
      vec3f: vec3f_bezier3, \
      vec3d: vec3d_bezier3 )( ( v0 ), ( v1 ), ( v2 ), ( f ) )

static inline vec2f vec2f_bezier4( vec2f v0, vec2f v1, vec2f v2, vec2f v3,
                                   cgf_t f ) {
  vec2f tmp0 = lerp( v0, v1, f );
  vec2f tmp1 = lerp( v1, v2, f );
  vec2f tmp2 = lerp( v2, v3, f );
  vec2f tmp3 = lerp( tmp0, tmp1, f );
  vec2f tmp4 = lerp( tmp1, tmp2, f );
  return lerp( tmp3, tmp4, f );
}

static inline vec2d vec2d_bezier4( vec2d v0, vec2d v1, vec2d v2, vec2d v3,
                                   cgd_t f ) {
  vec2d tmp0 = lerp( v0, v1, f );
  vec2d tmp1 = lerp( v1, v2, f );
  vec2d tmp2 = lerp( v2, v3, f );
  vec2d tmp3 = lerp( tmp0, tmp1, f );
  vec2d tmp4 = lerp( tmp1, tmp2, f );
  return lerp( tmp3, tmp4, f );
}

static inline vec3f vec3f_bezier4( vec3f v0, vec3f v1, vec3f v2, vec3f v3,
                                   cgf_t f ) {
  vec3f tmp0 = lerp( v0, v1, f );
  vec3f tmp1 = lerp( v1, v2, f );
  vec3f tmp2 = lerp( v2, v3, f );
  vec3f tmp3 = lerp( tmp0, tmp1, f );
  vec3f tmp4 = lerp( tmp1, tmp2, f );
  return lerp( tmp3, tmp4, f );
}

static inline vec3d vec3d_bezier4( vec3d v0, vec3d v1, vec3d v2, vec3d v3,
                                   cgd_t f ) {
  vec3d tmp0 = lerp( v0, v1, f );
  vec3d tmp1 = lerp( v1, v2, f );
  vec3d tmp2 = lerp( v2, v3, f );
  vec3d tmp3 = lerp( tmp0, tmp1, f );
  vec3d tmp4 = lerp( tmp1, tmp2, f );
  return lerp( tmp3, tmp4, f );
}

// bezier4
#define bezier4( v0, v1, v2, v3, f ) \
  _Generic( ( v0 ), \
      vec2f: vec2f_bezier4, \
      vec2d: vec2d_bezier4, \
      vec3f: vec3f_bezier4, \
      vec3d: vec3d_bezier4 )( ( v0 ), ( v1 ), ( v2 ), ( v3 ), ( f ) )

#define vec_distance_squared( a, b ) length_squared( sub( a, b ) )

#define vec_distance( a, b ) length( sub( a, b ) )

static inline cgf_t triface3i_distance_vec3i( triface3i t0, vec3i v0 ) {
  return dot( vec_to_vec3i( t0.normal ), sub( v0, t0.p[0] ) );
}

static inline cgf_t triface3i_distance_vec3f( triface3i t0, vec3f v0 ) {
  return dot( vec_to_vec3f( t0.normal ), sub( v0, vec_to_vec3f( t0.p[0] ) ) );
}

static inline cgd_t triface3i_distance_vec3d( triface3i t0, vec3d v0 ) {
  return dot( vec_to_vec3d( t0.normal ), sub( v0, vec_to_vec3d( t0.p[0] ) ) );
}

static inline cgd_t line3i_distance_squared_vec3i( line3i l0, vec3i v0 ) {
  cgd_t dir_len = length( l0.direction );
  if( dir_len == 0 ) {
    return -1;
  } else {
    vec3d dir_norm = divide_num( l0.direction, dir_len );
    vec3d vec_to_point = vec_to_vec3d( sub( v0, l0.point ) );

    cgd_t projection = vec3d_dot( vec_to_point, dir_norm );
    vec_to_point = sub( vec_to_point, multiply_num( dir_norm, projection ) );
    return length_squared( vec_to_point );
  }
}

static inline cgd_t line3i_distance_vec3i( line3i l0, vec3i v0 ) {
  cgd_t dist = line3i_distance_squared_vec3i( l0, v0 );
  if( dist == -1 ) {
    return -1;
  }
  return CG_dSQRT( dist );
}

static inline vec2d line2d_intersection( line2d l0, line2d l1 ) {
  vec2d perpendicular = vec2d_tangent( l0.direction );
  cgd_t dot_prod = vec2d_dot( perpendicular, l1.direction );

  if( CG_dABS( dot_prod ) < CG_dEPSILON ) {
    // Error
    return (vec2d){ NAN, NAN };
  }

  vec2d diff = { l1.point.x - l0.point.x, l1.point.y - l0.point.y };

  cgd_t t = -vec2d_dot( perpendicular, diff ) / dot_prod;

  return (vec2d){ .x = l1.point.x + t * l1.direction.x,
                  .y = l1.point.y + t * l1.direction.y };
}

static inline bool vec2i_linear_independent( vec2i a, struct vec2i b ) {
  return cross( a, b ) != 0;
}

static inline bool vec2f_linear_independent( vec2f a, struct vec2f b ) {
  return cross( a, b ) > CG_fEPSILON;
}

static inline bool vec2d_linear_independent( vec2d a, struct vec2d b ) {
  return cross( a, b ) > CG_dEPSILON;
}

// Check linear independency. Return true if vector direction is different,
// false if direction the same
#define vec2_linear_independent( a, b ) \
  _Generic( ( a ), \
      vec2i: vec2i_linear_independent, \
      vec2f: vec2f_linear_independent, \
      vec2d: vec2d_linear_independent )( ( a ), ( b ) )

static inline bool vec3i_linear_independent( vec3i a, vec3i b, vec3i c ) {
  return dot( cross( a, b ), c ) != 0;
}
static inline bool vec3f_linear_independent( vec3f a, vec3f b, vec3f c ) {
  return dot( cross( a, b ), c ) > CG_fEPSILON;
}
static inline bool vec3d_linear_independent( vec3d a, vec3d b, vec3d c ) {
  return dot( cross( a, b ), c ) > CG_dEPSILON;
}

// Check linear independency. Return true if all 3 vectors lay on same plane
#define vec3_linear_independent( a, b, c ) \
  _Generic( ( a ), \
      vec3i: vec3i_linear_independent, \
      vec3f: vec3f_linear_independent, \
      vec3d: vec3d_linear_independent )( ( a ), ( b ), ( c ) )

// Get null quaternion
#define quatf_null() \
  { \
    return (quatf){ 0, 0, 0, 1 }; \
  }

// Get null quaternion
#define quatd_null() \
  { \
    return (quatd){ 0, 0, 0, 1 }; \
  }

static inline quatf quatf_conjugate( quatf q ) {
  return (quatf){ .x = -q.x, .y = -q.y, .z = -q.z, .w = q.w };
}
static inline quatd quatd_conjugate( quatd q ) {
  return (quatd){ .x = -q.x, .y = -q.y, .z = -q.z, .w = q.w };
}

// conjugate quaternion for backward rotation
#define quat_conjugate( q ) \
  _Generic( ( q ), quatf: quatf_conjugate, quatd: quatd_conjugate )( q )

static inline quatf quatf_inverse( quatf q ) {
  cgf_t dot = dot( q, q );
  if( dot <= CG_fEPSILON )
    return (quatf){ 0, 0, 0, 0 };
  return multiply_num( quatf_conjugate( q ), 1.0f / dot );
}

static inline quatd quatd_inverse( quatd q ) {
  cgd_t dot = dot( q, q );
  if( dot < CG_dEPSILON )
    return (quatd){ 0, 0, 0, 0 };
  return multiply_num( quatd_conjugate( q ), 1.0f / dot );
}

static inline mat2f mat2f_inverse( mat2f m ) {
  cgf_t det = m.m11 * m.m22 - m.m12 * m.m21;
  if( det < CG_fEPSILON )
    return (mat2f){ 0 };
  cgf_t invDet = 1.0f / det;
  return (mat2f){ .m11 = m.m22 * invDet,
                  .m21 = -m.m21 * invDet,
                  .m12 = -m.m12 * invDet,
                  .m22 = m.m11 * invDet };
}

static inline mat2d mat2d_inverse( mat2d m ) {
  cgd_t det = m.m11 * m.m22 - m.m12 * m.m21;
  if( det < CG_dEPSILON )
    return (mat2d){ 0 };
  cgd_t invDet = 1.0f / det;
  return (mat2d){ .m11 = m.m22 * invDet,
                  .m21 = -m.m21 * invDet,
                  .m12 = -m.m12 * invDet,
                  .m22 = m.m11 * invDet };
}

static inline mat3f mat3f_inverse( mat3f m ) {
  cgf_t det = m.m11 * ( m.m22 * m.m33 - m.m23 * m.m32 ) -
              m.m12 * ( m.m21 * m.m33 - m.m23 * m.m31 ) +
              m.m13 * ( m.m21 * m.m32 - m.m22 * m.m31 );

  if( det < CG_fEPSILON )
    return (mat3f){ 0 };
  cgf_t invDet = 1.0f / det;

  return (mat3f){ .m11 = ( m.m22 * m.m33 - m.m23 * m.m32 ) * invDet,
                  .m21 = ( m.m23 * m.m31 - m.m21 * m.m33 ) * invDet,
                  .m31 = ( m.m21 * m.m32 - m.m22 * m.m31 ) * invDet,
                  .m12 = ( m.m13 * m.m32 - m.m12 * m.m33 ) * invDet,
                  .m22 = ( m.m11 * m.m33 - m.m13 * m.m31 ) * invDet,
                  .m32 = ( m.m12 * m.m31 - m.m11 * m.m32 ) * invDet,
                  .m13 = ( m.m12 * m.m23 - m.m13 * m.m22 ) * invDet,
                  .m23 = ( m.m13 * m.m21 - m.m11 * m.m23 ) * invDet,
                  .m33 = ( m.m11 * m.m22 - m.m12 * m.m21 ) * invDet };
}

static inline mat3d mat3d_inverse( mat3d m ) {
  cgd_t det = m.m11 * ( m.m22 * m.m33 - m.m23 * m.m32 ) -
              m.m12 * ( m.m21 * m.m33 - m.m23 * m.m31 ) +
              m.m13 * ( m.m21 * m.m32 - m.m22 * m.m31 );

  if( det < CG_dEPSILON )
    return (mat3d){ 0 };
  cgd_t invDet = 1.0f / det;

  return (mat3d){ .m11 = ( m.m22 * m.m33 - m.m23 * m.m32 ) * invDet,
                  .m21 = ( m.m23 * m.m31 - m.m21 * m.m33 ) * invDet,
                  .m31 = ( m.m21 * m.m32 - m.m22 * m.m31 ) * invDet,
                  .m12 = ( m.m13 * m.m32 - m.m12 * m.m33 ) * invDet,
                  .m22 = ( m.m11 * m.m33 - m.m13 * m.m31 ) * invDet,
                  .m32 = ( m.m12 * m.m31 - m.m11 * m.m32 ) * invDet,
                  .m13 = ( m.m12 * m.m23 - m.m13 * m.m22 ) * invDet,
                  .m23 = ( m.m13 * m.m21 - m.m11 * m.m23 ) * invDet,
                  .m33 = ( m.m11 * m.m22 - m.m12 * m.m21 ) * invDet };
}

static inline mat4f mat4f_inverse( mat4f m ) {
  cgf_t s0 = m.m11 * m.m22 - m.m21 * m.m12;
  cgf_t s1 = m.m11 * m.m32 - m.m31 * m.m12;
  cgf_t s2 = m.m11 * m.m42 - m.m41 * m.m12;
  cgf_t s3 = m.m21 * m.m32 - m.m31 * m.m22;
  cgf_t s4 = m.m21 * m.m42 - m.m41 * m.m22;
  cgf_t s5 = m.m31 * m.m42 - m.m41 * m.m32;

  cgf_t c5 = m.m33 * m.m44 - m.m43 * m.m34;
  cgf_t c4 = m.m23 * m.m44 - m.m43 * m.m24;
  cgf_t c3 = m.m23 * m.m34 - m.m33 * m.m24;
  cgf_t c2 = m.m13 * m.m44 - m.m43 * m.m14;
  cgf_t c1 = m.m13 * m.m34 - m.m33 * m.m14;
  cgf_t c0 = m.m13 * m.m24 - m.m23 * m.m14;

  cgf_t det = s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0;
  if( det < CG_fEPSILON )
    return (mat4f){ 0 };
  cgf_t invDet = 1.0f / det;

  return (mat4f){ .m11 = ( m.m22 * c5 - m.m32 * c4 + m.m42 * c3 ) * invDet,
                  .m21 = ( -m.m21 * c5 + m.m31 * c4 - m.m41 * c3 ) * invDet,
                  .m31 = ( m.m24 * s5 - m.m34 * s4 + m.m44 * s3 ) * invDet,
                  .m41 = ( -m.m23 * s5 + m.m33 * s4 - m.m43 * s3 ) * invDet,

                  .m12 = ( -m.m12 * c5 + m.m32 * c2 - m.m42 * c1 ) * invDet,
                  .m22 = ( m.m11 * c5 - m.m31 * c2 + m.m41 * c1 ) * invDet,
                  .m32 = ( -m.m14 * s5 + m.m34 * s2 - m.m44 * s1 ) * invDet,
                  .m42 = ( m.m13 * s5 - m.m33 * s2 + m.m43 * s1 ) * invDet,

                  .m13 = ( m.m12 * c4 - m.m22 * c2 + m.m42 * c0 ) * invDet,
                  .m23 = ( -m.m11 * c4 + m.m21 * c2 - m.m41 * c0 ) * invDet,
                  .m33 = ( m.m14 * s4 - m.m24 * s2 + m.m44 * s0 ) * invDet,
                  .m43 = ( -m.m13 * s4 + m.m23 * s2 - m.m43 * s0 ) * invDet,

                  .m14 = ( -m.m12 * c3 + m.m22 * c1 - m.m32 * c0 ) * invDet,
                  .m24 = ( m.m11 * c3 - m.m21 * c1 + m.m31 * c0 ) * invDet,
                  .m34 = ( -m.m14 * s3 + m.m24 * s1 - m.m34 * s0 ) * invDet,
                  .m44 = ( m.m13 * s3 - m.m23 * s1 + m.m33 * s0 ) * invDet };
}

static inline mat4d mat4d_inverse( mat4d m ) {
  cgd_t s0 = m.m11 * m.m22 - m.m21 * m.m12;
  cgd_t s1 = m.m11 * m.m32 - m.m31 * m.m12;
  cgd_t s2 = m.m11 * m.m42 - m.m41 * m.m12;
  cgd_t s3 = m.m21 * m.m32 - m.m31 * m.m22;
  cgd_t s4 = m.m21 * m.m42 - m.m41 * m.m22;
  cgd_t s5 = m.m31 * m.m42 - m.m41 * m.m32;

  cgd_t c5 = m.m33 * m.m44 - m.m43 * m.m34;
  cgd_t c4 = m.m23 * m.m44 - m.m43 * m.m24;
  cgd_t c3 = m.m23 * m.m34 - m.m33 * m.m24;
  cgd_t c2 = m.m13 * m.m44 - m.m43 * m.m14;
  cgd_t c1 = m.m13 * m.m34 - m.m33 * m.m14;
  cgd_t c0 = m.m13 * m.m24 - m.m23 * m.m14;

  cgd_t det = s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0;
  if( det < CG_dEPSILON )
    return (mat4d){ 0 };
  cgd_t invDet = 1.0f / det;

  return (mat4d){ .m11 = ( m.m22 * c5 - m.m32 * c4 + m.m42 * c3 ) * invDet,
                  .m21 = ( -m.m21 * c5 + m.m31 * c4 - m.m41 * c3 ) * invDet,
                  .m31 = ( m.m24 * s5 - m.m34 * s4 + m.m44 * s3 ) * invDet,
                  .m41 = ( -m.m23 * s5 + m.m33 * s4 - m.m43 * s3 ) * invDet,

                  .m12 = ( -m.m12 * c5 + m.m32 * c2 - m.m42 * c1 ) * invDet,
                  .m22 = ( m.m11 * c5 - m.m31 * c2 + m.m41 * c1 ) * invDet,
                  .m32 = ( -m.m14 * s5 + m.m34 * s2 - m.m44 * s1 ) * invDet,
                  .m42 = ( m.m13 * s5 - m.m33 * s2 + m.m43 * s1 ) * invDet,

                  .m13 = ( m.m12 * c4 - m.m22 * c2 + m.m42 * c0 ) * invDet,
                  .m23 = ( -m.m11 * c4 + m.m21 * c2 - m.m41 * c0 ) * invDet,
                  .m33 = ( m.m14 * s4 - m.m24 * s2 + m.m44 * s0 ) * invDet,
                  .m43 = ( -m.m13 * s4 + m.m23 * s2 - m.m43 * s0 ) * invDet,

                  .m14 = ( -m.m12 * c3 + m.m22 * c1 - m.m32 * c0 ) * invDet,
                  .m24 = ( m.m11 * c3 - m.m21 * c1 + m.m31 * c0 ) * invDet,
                  .m34 = ( -m.m14 * s3 + m.m24 * s1 - m.m34 * s0 ) * invDet,
                  .m44 = ( m.m13 * s3 - m.m23 * s1 + m.m33 * s0 ) * invDet };
}

// inverse
#define inverse( q ) \
  _Generic( ( q ), \
      quatf: quatf_inverse, \
      quatd: quatd_inverse, \
      mat2f: mat2f_inverse, \
      mat2d: mat2d_inverse, \
      mat3f: mat3f_inverse, \
      mat3d: mat3d_inverse, \
      mat4f: mat4f_inverse, \
      mat4d: mat4d_inverse )( q )

inline static quatf quatf_divide( quatf a, quatf b ) {
  return multiply( a, inverse( b ) );
}
inline static quatd quatd_divide( quatd a, quatd b ) {
  return multiply( a, inverse( b ) );
}

// quaternion division
#define quat_divide( q ) \
  _Generic( ( q ), quatf: quatf_divide, quatd: quatd_divide )( q )

static inline quatf quatf_pow( quatf q, cgf_t exponent ) {
  if( CG_fABS( q.w ) < 1.0f - CG_fEPSILON ) {
    cgf_t alpha = CG_fACOS( q.w );
    cgf_t new_alpha = alpha * exponent;

    cgf_t s = CG_fSIN( new_alpha ) / CG_fSIN( alpha );

    q.x *= s;
    q.y *= s;
    q.z *= s;
    q.w = CG_fCOS( new_alpha );
    return q;
  } else {
    return q;
  }
}

static inline quatd quatd_pow( quatd q, cgd_t exponent ) {
  if( CG_dABS( q.w ) < 1.0f - CG_dEPSILON ) {
    cgd_t alpha = CG_dACOS( q.w );
    cgd_t new_alpha = alpha * exponent;

    cgd_t s = CG_dSIN( new_alpha ) / CG_dSIN( alpha );

    q.x *= s;
    q.y *= s;
    q.z *= s;
    q.w = CG_dCOS( new_alpha );
    return q;
  } else {
    return q;
  }
}

// Power quaternion on exponent
#define quat_pow( q, exp ) \
  _Generic( ( q ), quatf: quatf_pow, quatd: quatd_pow, )( ( q ), ( exp ) )

static inline quatf quatf_from_axis_angle( vec3f axis, cgf_t angle ) {
  cgf_t half_angle = angle * (cgf_t)0.5;

#ifdef CGEOM_PRECISE_TRIGONOMETRY
  sincos1cos sc1c = sncs1cs( half_angle );
  cgd_t c = sc1c.cos;
  cgd_t s = sc1c.sin;
#else
  cgf_t c = CG_fCOS( half_angle );
  cgf_t s = CG_fSIN( half_angle );
#endif

  return (quatf){ .x = axis.x * s, .y = axis.y * s, .z = axis.z * s, .w = c };
}

static inline quatd quatd_from_axis_angle( vec3d axis, cgd_t angle ) {
  cgd_t half_angle = angle * (cgd_t)0.5;

#ifdef CGEOM_PRECISE_TRIGONOMETRY
  sincos1cos sc1c = sncs1cs( half_angle );
  cgd_t c = sc1c.cos;
  cgd_t s = sc1c.sin;
#else
  cgd_t c = CG_dCOS( half_angle );
  cgd_t s = CG_dSIN( half_angle );
#endif

  return (quatd){ .x = axis.x * s, .y = axis.y * s, .z = axis.z * s, .w = c };
}

// Quaternion from axis and angle
#define quat_from_axis_angle( axis, angle ) \
  _Generic( ( axis ), \
      quatf: quatf_from_axis_angle, \
      quatd: quatd_from_axis_angle, )( ( axis ), ( angle ) )

static inline quatf quatf_from_euler( vec3f euler ) {
#ifdef CGEOM_PRECISE_TRIGONOMETRY
  sincos1cos sc1cx = sncs1cs( euler.x * (cgf_t)0.5 );
  sincos1cos sc1cy = sncs1cs( euler.y * (cgf_t)0.5 );
  sincos1cos sc1cz = sncs1cs( euler.z * (cgf_t)0.5 );

  cgf_t sx = sc1cx.sin;
  cgf_t cx = sc1cx.cos;
  cgf_t sy = sc1cy.sin;
  cgf_t cy = sc1cy.cos;
  cgf_t sz = sc1cz.sin;
  cgf_t cz = sc1cz.cos
#else
  cgf_t sx = CG_fSIN( euler.x * (cgf_t)0.5 );
  cgf_t cx = CG_fCOS( euler.x * (cgf_t)0.5 );
  cgf_t sy = CG_fSIN( euler.y * (cgf_t)0.5 );
  cgf_t cy = CG_fCOS( euler.y * (cgf_t)0.5 );
  cgf_t sz = CG_fSIN( euler.z * (cgf_t)0.5 );
  cgf_t cz = CG_fCOS( euler.z * (cgf_t)0.5 );
#endif

             return (quatf){ .x = sx * cy * cz + cx * sy * sz,
                             .y = cx * sy * cz - sx * cy * sz,
                             .z = cx * cy * sz - sx * sy * cz,
                             .w = cx * cy * cz + sx * sy * sz };
}

static inline quatd quatd_from_euler( vec3d euler ) {
#ifdef CGEOM_PRECISE_TRIGONOMETRY
  sincos1cos sc1cx = sncs1cs( euler.x * (cgd_t)0.5 );
  sincos1cos sc1cy = sncs1cs( euler.y * (cgd_t)0.5 );
  sincos1cos sc1cz = sncs1cs( euler.z * (cgd_t)0.5 );

  cgd_t sx = sc1cx.sin;
  cgd_t cx = sc1cx.cos;
  cgd_t sy = sc1cy.sin;
  cgd_t cy = sc1cy.cos;
  cgd_t sz = sc1cz.sin;
  cgd_t cz = sc1cz.cos
#else
  cgd_t sx = CG_dSIN( euler.x * (cgd_t)0.5 );
  cgd_t cx = CG_dCOS( euler.x * (cgd_t)0.5 );
  cgd_t sy = CG_dSIN( euler.y * (cgd_t)0.5 );
  cgd_t cy = CG_dCOS( euler.y * (cgd_t)0.5 );
  cgd_t sz = CG_dSIN( euler.z * (cgd_t)0.5 );
  cgd_t cz = CG_dCOS( euler.z * (cgd_t)0.5 );
#endif

             return (quatd){ .x = sx * cy * cz + cx * sy * sz,
                             .y = cx * sy * cz - sx * cy * sz,
                             .z = cx * cy * sz - sx * sy * cz,
                             .w = cx * cy * cz + sx * sy * sz };
}

// Quaternion from euler angles
#define quat_from_euler( euler ) \
  _Generic( ( euler ), quatf: quatf_from_euler, quatd: quatd_from_euler )( \
      euler )

static inline quatf quatf_from_mat4( mat4f m ) {
  cgf_t trace = m.m11 + m.m22 + m.m33;
  quatf q;

  if( trace > 0.0f ) {
    cgf_t s = CG_fSQRT( trace + 1.0f ) * 2.0f;
    q.w = 0.25f * s;
    q.x = ( m.m23 - m.m32 ) / s;
    q.y = ( m.m31 - m.m13 ) / s;
    q.z = ( m.m12 - m.m21 ) / s;
  } else if( ( m.m11 > m.m22 ) && ( m.m11 > m.m33 ) ) {
    cgf_t s = CG_fSQRT( 1.0f + m.m11 - m.m22 - m.m33 ) * 2.0f;
    q.w = ( m.m23 - m.m32 ) / s;
    q.x = 0.25f * s;
    q.y = ( m.m12 + m.m21 ) / s;
    q.z = ( m.m31 + m.m13 ) / s;
  } else if( m.m22 > m.m33 ) {
    cgf_t s = CG_fSQRT( 1.0f + m.m22 - m.m11 - m.m33 ) * 2.0f;
    q.w = ( m.m31 - m.m13 ) / s;
    q.x = ( m.m12 + m.m21 ) / s;
    q.y = 0.25f * s;
    q.z = ( m.m23 + m.m32 ) / s;
  } else {
    cgf_t s = CG_fSQRT( 1.0f + m.m33 - m.m11 - m.m22 ) * 2.0f;
    q.w = ( m.m12 - m.m21 ) / s;
    q.x = ( m.m31 + m.m13 ) / s;
    q.y = ( m.m23 + m.m32 ) / s;
    q.z = 0.25f * s;
  }
  return q;
}

static inline quatd quatd_from_mat4( mat4d m ) {
  cgd_t trace = m.m11 + m.m22 + m.m33;
  quatd q;

  if( trace > 0.f ) {
    cgd_t s = CG_dSQRT( trace + 1.0 ) * 2.0;
    q.w = 0.25 * s;
    q.x = ( m.m23 - m.m32 ) / s;
    q.y = ( m.m31 - m.m13 ) / s;
    q.z = ( m.m12 - m.m21 ) / s;
  } else if( ( m.m11 > m.m22 ) && ( m.m11 > m.m33 ) ) {
    cgd_t s = CG_dSQRT( 1.0 + m.m11 - m.m22 - m.m33 ) * 2.0;
    q.w = ( m.m23 - m.m32 ) / s;
    q.x = 0.25 * s;
    q.y = ( m.m12 + m.m21 ) / s;
    q.z = ( m.m31 + m.m13 ) / s;
  } else if( m.m22 > m.m33 ) {
    cgd_t s = CG_dSQRT( 1.0 + m.m22 - m.m11 - m.m33 ) * 2.0;
    q.w = ( m.m31 - m.m13 ) / s;
    q.x = ( m.m12 + m.m21 ) / s;
    q.y = 0.25 * s;
    q.z = ( m.m23 + m.m32 ) / s;
  } else {
    cgd_t s = CG_dSQRT( 1.0f + m.m33 - m.m11 - m.m22 ) * 2.0;
    q.w = ( m.m12 - m.m21 ) / s;
    q.x = ( m.m31 + m.m13 ) / s;
    q.y = ( m.m23 + m.m32 ) / s;
    q.z = 0.25 * s;
  }
  return q;
}

// Quaternion from rotation matrix
#define quat_from_mat4( m ) \
  _Generic( ( m ), mat4f: quatf_from_mat4, mat4d: quatd_from_mat4 )( m )

static inline quatf quatf_nlerp( quatf q1, quatf q2, cgf_t t ) {
  cgf_t d = dot( q1, q2 );
  cgf_t t1 = (cgf_t)1.0 - t;
  cgf_t t2 = ( d < (cgf_t)0.0 ) ? -t : t;

  quatf res = { .x = q1.x * t1 + q2.x * t2,
                .y = q1.y * t1 + q2.y * t2,
                .z = q1.z * t1 + q2.z * t2,
                .w = q1.w * t1 + q2.w * t2 };
  return normalize( res );
}

static inline quatd quatd_nlerp( quatd q1, quatd q2, cgd_t t ) {
  cgd_t d = dot( q1, q2 );
  cgd_t t1 = (cgd_t)1.0 - t;
  cgd_t t2 = ( d < (cgd_t)0.0 ) ? -t : t;

  quatd res = { .x = q1.x * t1 + q2.x * t2,
                .y = q1.y * t1 + q2.y * t2,
                .z = q1.z * t1 + q2.z * t2,
                .w = q1.w * t1 + q2.w * t2 };
  return normalize( res );
}

// Quaternion normalized lerp. Easier than slerp
#define quat_nlerp( q1, q2, t ) \
  _Generic( ( q1 ), quatf: quatf_nlerp, quatd: quatd_nlerp )( ( q1 ), ( q2 ), \
                                                              ( t ) )

static inline quatf quatf_slerp( quatf q1, quatf q2, cgf_t t ) {
  cgf_t d = dot( q1, q2 );

  // short path
  if( d < (cgf_t)0.0 ) {
    d = -d;
    q2 = (quatf){ -q2.x, -q2.y, -q2.z, -q2.w };
  }

  // If quats mostly identical go to nlerp to omit 0 division
  if( d > (cgf_t)0.9995 ) {
    return quat_nlerp( q1, q2, t );
  }

  cgf_t theta_0 = CG_fACOS( d );
  cgf_t theta = theta_0 * t;
  cgf_t sin_theta = CG_fSIN( theta );
  cgf_t sin_theta_0 = CG_fSIN( theta_0 );

  cgf_t s2 = sin_theta / sin_theta_0;
  cgf_t s1 = CG_fCOS( theta ) - d * s2;

  return (quatf){ .x = q1.x * s1 + q2.x * s2,
                  .y = q1.y * s1 + q2.y * s2,
                  .z = q1.z * s1 + q2.z * s2,
                  .w = q1.w * s1 + q2.w * s2 };
}

static inline quatd quatd_slerp( quatd q1, quatd q2, cgd_t t ) {
  cgd_t d = dot( q1, q2 );

  // short path
  if( d < (cgd_t)0.0 ) {
    d = -d;
    q2 = (quatd){ -q2.x, -q2.y, -q2.z, -q2.w };
  }

  // If quats mostly identical go to nlerp to omit 0 division
  if( d > (cgd_t)0.9995 ) {
    return quat_nlerp( q1, q2, t );
  }

  cgd_t theta_0 = CG_dACOS( d );
  cgd_t theta = theta_0 * t;
  cgd_t sin_theta = CG_dSIN( theta );
  cgd_t sin_theta_0 = CG_dSIN( theta_0 );

  cgd_t s2 = sin_theta / sin_theta_0;
  cgd_t s1 = CG_dCOS( theta ) - d * s2;

  return (quatd){ .x = q1.x * s1 + q2.x * s2,
                  .y = q1.y * s1 + q2.y * s2,
                  .z = q1.z * s1 + q2.z * s2,
                  .w = q1.w * s1 + q2.w * s2 };
}

// Spherical linear interpolation
#define quat_slerp( q1, q2, t ) \
  _Generic( ( q1 ), quatd: quat_slerpd, quatf: quat_slerpf )( ( q1 ), ( q2 ), \
                                                              ( t ) )

static inline cgf_t quatf_angle( quatf q1, quatf q2 ) {
  cgf_t d = dot( q1, q2 );
  cgf_t s = CG_fSQRT( dot( q1, q1 ) * dot( q2, q2 ) );

  if( s < CG_fEPSILON )
    return (cgf_t)0.0;

  cgf_t cos_theta = d / s;

  cos_theta = clamp( cos_theta, (cgf_t)-1.0, (cgf_t)1.0 );

  return CG_fACOS( cos_theta );
}

static inline cgd_t quatd_angle( quatd q1, quatd q2 ) {
  cgd_t d = dot( q1, q2 );
  cgd_t s = CG_fSQRT( dot( q1, q1 ) * dot( q2, q2 ) );

  if( s < CG_dEPSILON )
    return (cgd_t)0.0;

  cgd_t cos_theta = d / s;

  cos_theta = clamp( cos_theta, (cgd_t)-1.0, (cgd_t)1.0 );

  return CG_dACOS( cos_theta );
}

// Angle between quaternions
#define quat_angle( q1, q2 ) \
  _Generic( ( q1 ), quatd: quat_angled, quatf: quat_anglef )( q1, q2 )

static inline mat2f mat2f_identity( void ) {
  return (mat2f){
      .m11 = 1.0f,
      .m22 = 1.0f,
  };
}
static inline mat2d mat2d_identity( void ) {
  return (mat2d){
      .m11 = 1.0,
      .m22 = 1.0,
  };
}
static inline mat3f mat3f_identity( void ) {
  return (mat3f){
      .m11 = 1.0f,
      .m22 = 1.0f,
      .m33 = 1.0f,
  };
}
static inline mat3d mat3d_identity( void ) {
  return (mat3d){
      .m11 = 1.0,
      .m22 = 1.0,
      .m33 = 1.0,
  };
}
static inline mat4f mat4f_identity( void ) {
  return (mat4f){ .m11 = 1.0f, .m22 = 1.0f, .m33 = 1.0f, .m44 = 1.0f };
}
static inline mat4d mat4d_identity( void ) {
  return (mat4d){ .m11 = 1.0, .m22 = 1.0, .m33 = 1.0, .m44 = 1.0 };
}

// Get identity matrix. m - your variable.
// Example:  mat3 myMat = mat_identity(myMat);
#define mat_identity( m ) \
  _Generic( ( m ), \
      mat2f: mat2f_identity(), \
      mat2d: mat2d_identity(), \
      mat3f: mat3f_identity(), \
      mat3d: mat3d_identity(), \
      mat4d: mat4f_identity(), \
      mat4f: mat4d_identity() )

static inline cgf_t mat2f_determinant( mat2f m ) {
  return m.m11 * m.m22 - m.m12 * m.m21;
}

static inline cgd_t mat2d_determinant( mat2d m ) {
  return m.m11 * m.m22 - m.m12 * m.m21;
}

static inline cgf_t mat3f_determinant( mat3f m ) {
  return m.m11 * ( m.m22 * m.m33 - m.m23 * m.m32 ) -
         m.m12 * ( m.m21 * m.m33 - m.m23 * m.m31 ) +
         m.m13 * ( m.m21 * m.m32 - m.m22 * m.m31 );
}

static inline cgd_t mat3d_determinant( mat3d m ) {
  return m.m11 * ( m.m22 * m.m33 - m.m23 * m.m32 ) -
         m.m12 * ( m.m21 * m.m33 - m.m23 * m.m31 ) +
         m.m13 * ( m.m21 * m.m32 - m.m22 * m.m31 );
}

static inline cgf_t mat4f_determinant( mat4f m ) {
  cgf_t f0 = m.m33 * m.m44 - m.m34 * m.m43;
  cgf_t f1 = m.m32 * m.m44 - m.m34 * m.m42;
  cgf_t f2 = m.m32 * m.m43 - m.m33 * m.m42;
  cgf_t f3 = m.m31 * m.m44 - m.m34 * m.m41;
  cgf_t f4 = m.m31 * m.m43 - m.m33 * m.m41;
  cgf_t f5 = m.m31 * m.m42 - m.m32 * m.m41;

  return m.m11 * ( m.m22 * f0 - m.m23 * f1 + m.m24 * f2 ) -
         m.m12 * ( m.m21 * f0 - m.m23 * f3 + m.m24 * f4 ) +
         m.m13 * ( m.m21 * f1 - m.m22 * f3 + m.m24 * f5 ) -
         m.m14 * ( m.m21 * f2 - m.m22 * f4 + m.m23 * f5 );
}

static inline cgd_t mat4d_determinant( mat4d m ) {
  cgd_t f0 = m.m33 * m.m44 - m.m34 * m.m43;
  cgd_t f1 = m.m32 * m.m44 - m.m34 * m.m42;
  cgd_t f2 = m.m32 * m.m43 - m.m33 * m.m42;
  cgd_t f3 = m.m31 * m.m44 - m.m34 * m.m41;
  cgd_t f4 = m.m31 * m.m43 - m.m33 * m.m41;
  cgd_t f5 = m.m31 * m.m42 - m.m32 * m.m41;

  return m.m11 * ( m.m22 * f0 - m.m23 * f1 + m.m24 * f2 ) -
         m.m12 * ( m.m21 * f0 - m.m23 * f3 + m.m24 * f4 ) +
         m.m13 * ( m.m21 * f1 - m.m22 * f3 + m.m24 * f5 ) -
         m.m14 * ( m.m21 * f2 - m.m22 * f4 + m.m23 * f5 );
}

// Get determinant of matrix
#define determinant( m ) \
  _Generic( ( m ), \
      mat2f: mat2f_determinant, \
      mat2d: mat2d_determinant, \
      mat3f: mat3f_determinant, \
      mat3d: mat3d_determinant, \
      mat4f: mat4f_determinant, \
      mat4d: mat4d_determinant )( m )

static inline mat2f mat2f_transpose( mat2f m ) {
  return (mat2f){ .m11 = m.m11, .m21 = m.m12, .m12 = m.m21, .m22 = m.m22 };
}

static inline mat2d mat2d_transpose( mat2d m ) {
  return (mat2d){ .m11 = m.m11, .m21 = m.m12, .m12 = m.m21, .m22 = m.m22 };
}

static inline mat3f mat3f_transpose( mat3f m ) {
  return (mat3f){ .m11 = m.m11,
                  .m21 = m.m12,
                  .m31 = m.m13,
                  .m12 = m.m21,
                  .m22 = m.m22,
                  .m32 = m.m23,
                  .m13 = m.m31,
                  .m23 = m.m32,
                  .m33 = m.m33 };
}

static inline mat3d mat3d_transpose( mat3d m ) {
  return (mat3d){ .m11 = m.m11,
                  .m21 = m.m12,
                  .m31 = m.m13,
                  .m12 = m.m21,
                  .m22 = m.m22,
                  .m32 = m.m23,
                  .m13 = m.m31,
                  .m23 = m.m32,
                  .m33 = m.m33 };
}

static inline mat4f mat4f_transpose( mat4f m ) {
  return (mat4f){ .m11 = m.m11,
                  .m21 = m.m12,
                  .m31 = m.m13,
                  .m41 = m.m14,
                  .m12 = m.m21,
                  .m22 = m.m22,
                  .m32 = m.m23,
                  .m42 = m.m24,
                  .m13 = m.m31,
                  .m23 = m.m32,
                  .m33 = m.m33,
                  .m43 = m.m34,
                  .m14 = m.m41,
                  .m24 = m.m42,
                  .m34 = m.m43,
                  .m44 = m.m44 };
}

static inline mat4d mat4d_transpose( mat4d m ) {
  return (mat4d){ .m11 = m.m11,
                  .m21 = m.m12,
                  .m31 = m.m13,
                  .m41 = m.m14,
                  .m12 = m.m21,
                  .m22 = m.m22,
                  .m32 = m.m23,
                  .m42 = m.m24,
                  .m13 = m.m31,
                  .m23 = m.m32,
                  .m33 = m.m33,
                  .m43 = m.m34,
                  .m14 = m.m41,
                  .m24 = m.m42,
                  .m34 = m.m43,
                  .m44 = m.m44 };
}

// Transpose matrix
#define transpose( m ) \
  _Generic( ( m ), \
      mat2f: mat2f_transpose, \
      mat2d: mat2d_transpose, \
      mat3f: mat3f_transpose, \
      mat3d: mat3d_transpose, \
      mat4f: mat4f_transpose, \
      mat4d: mat4d_transpose )( m )

static inline mat2f mat2f_cofactor( mat2f m ) {
  return (mat2f){ .m11 = m.m22, .m21 = -m.m12, .m12 = -m.m21, .m22 = m.m11 };
}

static inline mat2d mat2d_cofactor( mat2d m ) {
  return (mat2d){ .m11 = m.m22, .m21 = -m.m12, .m12 = -m.m21, .m22 = m.m11 };
}

static inline mat3f mat3f_cofactor( mat3f m ) {
  return (mat3f){ .m11 = ( m.m22 * m.m33 - m.m23 * m.m32 ),
                  .m21 = -( m.m12 * m.m33 - m.m13 * m.m32 ),
                  .m31 = ( m.m12 * m.m23 - m.m13 * m.m22 ),

                  .m12 = -( m.m21 * m.m33 - m.m23 * m.m31 ),
                  .m22 = ( m.m11 * m.m33 - m.m13 * m.m31 ),
                  .m32 = -( m.m11 * m.m23 - m.m13 * m.m21 ),

                  .m13 = ( m.m21 * m.m32 - m.m22 * m.m31 ),
                  .m23 = -( m.m11 * m.m32 - m.m12 * m.m31 ),
                  .m33 = ( m.m11 * m.m22 - m.m12 * m.m21 ) };
}

static inline mat3d mat3d_cofactor( mat3d m ) {
  return (mat3d){ .m11 = ( m.m22 * m.m33 - m.m23 * m.m32 ),
                  .m21 = -( m.m12 * m.m33 - m.m13 * m.m32 ),
                  .m31 = ( m.m12 * m.m23 - m.m13 * m.m22 ),

                  .m12 = -( m.m21 * m.m33 - m.m23 * m.m31 ),
                  .m22 = ( m.m11 * m.m33 - m.m13 * m.m31 ),
                  .m32 = -( m.m11 * m.m23 - m.m13 * m.m21 ),

                  .m13 = ( m.m21 * m.m32 - m.m22 * m.m31 ),
                  .m23 = -( m.m11 * m.m32 - m.m12 * m.m31 ),
                  .m33 = ( m.m11 * m.m22 - m.m12 * m.m21 ) };
}

static inline mat4f mat4f_cofactor( mat4f m ) {
  mat4f res;

  // Minors for row 3,4
  cgf_t s0 = m.m31 * m.m42 - m.m32 * m.m41;
  cgf_t s1 = m.m31 * m.m43 - m.m33 * m.m41;
  cgf_t s2 = m.m31 * m.m44 - m.m34 * m.m41;
  cgf_t s3 = m.m32 * m.m43 - m.m33 * m.m42;
  cgf_t s4 = m.m32 * m.m44 - m.m34 * m.m42;
  cgf_t s5 = m.m33 * m.m44 - m.m34 * m.m43;

  // Minors for row 1,2
  cgf_t c0 = m.m11 * m.m22 - m.m12 * m.m21;
  cgf_t c1 = m.m11 * m.m23 - m.m13 * m.m21;
  cgf_t c2 = m.m11 * m.m24 - m.m14 * m.m21;
  cgf_t c3 = m.m12 * m.m23 - m.m13 * m.m22;
  cgf_t c4 = m.m12 * m.m24 - m.m14 * m.m22;
  cgf_t c5 = m.m13 * m.m24 - m.m14 * m.m23;

  // 1 column
  res.m11 = ( m.m22 * s5 - m.m23 * s4 + m.m24 * s3 );
  res.m12 = -( m.m21 * s5 - m.m23 * s2 + m.m24 * s1 );
  res.m13 = ( m.m21 * s4 - m.m22 * s2 + m.m24 * s0 );
  res.m14 = -( m.m21 * s3 - m.m22 * s1 + m.m23 * s0 );

  // 2 column
  res.m21 = -( m.m12 * s5 - m.m13 * s4 + m.m14 * s3 );
  res.m22 = ( m.m11 * s5 - m.m13 * s2 + m.m14 * s1 );
  res.m23 = -( m.m11 * s4 - m.m12 * s2 + m.m14 * s0 );
  res.m24 = ( m.m11 * s3 - m.m12 * s1 + m.m13 * s0 );

  // 3 column
  res.m31 = ( m.m22 * c5 - m.m23 * c4 + m.m24 * c3 );
  res.m32 = -( m.m21 * c5 - m.m23 * c2 + m.m24 * c1 );
  res.m33 = ( m.m21 * c4 - m.m22 * c2 + m.m24 * c0 );
  res.m34 = -( m.m21 * c3 - m.m22 * c1 + m.m23 * c0 );

  // 4 column
  res.m41 = -( m.m12 * c5 - m.m13 * c4 + m.m14 * c3 );
  res.m42 = ( m.m11 * c5 - m.m13 * c2 + m.m14 * c1 );
  res.m43 = -( m.m11 * c4 - m.m12 * c2 + m.m14 * c0 );
  res.m44 = ( m.m11 * c3 - m.m12 * c1 + m.m13 * c0 );

  return res;
}

static inline mat4d mat4d_cofactor( mat4d m ) {
  mat4d res;

  // Minors for row 3,4
  cgd_t s0 = m.m31 * m.m42 - m.m32 * m.m41;
  cgd_t s1 = m.m31 * m.m43 - m.m33 * m.m41;
  cgd_t s2 = m.m31 * m.m44 - m.m34 * m.m41;
  cgd_t s3 = m.m32 * m.m43 - m.m33 * m.m42;
  cgd_t s4 = m.m32 * m.m44 - m.m34 * m.m42;
  cgd_t s5 = m.m33 * m.m44 - m.m34 * m.m43;

  // Minors for row 1,2
  cgd_t c0 = m.m11 * m.m22 - m.m12 * m.m21;
  cgd_t c1 = m.m11 * m.m23 - m.m13 * m.m21;
  cgd_t c2 = m.m11 * m.m24 - m.m14 * m.m21;
  cgd_t c3 = m.m12 * m.m23 - m.m13 * m.m22;
  cgd_t c4 = m.m12 * m.m24 - m.m14 * m.m22;
  cgd_t c5 = m.m13 * m.m24 - m.m14 * m.m23;

  // 1 column
  res.m11 = ( m.m22 * s5 - m.m23 * s4 + m.m24 * s3 );
  res.m12 = -( m.m21 * s5 - m.m23 * s2 + m.m24 * s1 );
  res.m13 = ( m.m21 * s4 - m.m22 * s2 + m.m24 * s0 );
  res.m14 = -( m.m21 * s3 - m.m22 * s1 + m.m23 * s0 );

  // 2 column
  res.m21 = -( m.m12 * s5 - m.m13 * s4 + m.m14 * s3 );
  res.m22 = ( m.m11 * s5 - m.m13 * s2 + m.m14 * s1 );
  res.m23 = -( m.m11 * s4 - m.m12 * s2 + m.m14 * s0 );
  res.m24 = ( m.m11 * s3 - m.m12 * s1 + m.m13 * s0 );

  // 3 column
  res.m31 = ( m.m22 * c5 - m.m23 * c4 + m.m24 * c3 );
  res.m32 = -( m.m21 * c5 - m.m23 * c2 + m.m24 * c1 );
  res.m33 = ( m.m21 * c4 - m.m22 * c2 + m.m24 * c0 );
  res.m34 = -( m.m21 * c3 - m.m22 * c1 + m.m23 * c0 );

  // 4 column
  res.m41 = -( m.m12 * c5 - m.m13 * c4 + m.m14 * c3 );
  res.m42 = ( m.m11 * c5 - m.m13 * c2 + m.m14 * c1 );
  res.m43 = -( m.m11 * c4 - m.m12 * c2 + m.m14 * c0 );
  res.m44 = ( m.m11 * c3 - m.m12 * c1 + m.m13 * c0 );

  return res;
}

#define cofactor( m ) \
  _Generic( ( m ), \
      mat2f: mat2f_cofactor, \
      mat2d: mat2d_cofactor, \
      mat3f: mat3f_cofactor, \
      mat3d: mat3d_cofactor, \
      mat4f: mat4f_cofactor, \
      mat4d: mat4d_cofactor )( m )

static inline mat2f mat2f_adjugate( mat2f m ) {
  return (mat2f){ .m11 = m.m22, .m21 = -m.m21, .m12 = -m.m12, .m22 = m.m11 };
}

static inline mat2d mat2d_adjugate( mat2d m ) {
  return (mat2d){ .m11 = m.m22, .m21 = -m.m21, .m12 = -m.m12, .m22 = m.m11 };
}

#define adjugate( m ) \
  _Generic( ( m ), mat2f: mat2f_adjugate, mat2d: mat2d_adjugate )( m )

static inline mat4f mat4f_set_scale( mat4f m, vec3f s ) {
  vec3f axis_x = { m.m11, m.m12, m.m13 };
  vec3f axis_y = { m.m21, m.m22, m.m23 };
  vec3f axis_z = { m.m31, m.m32, m.m33 };

  axis_x = normalize( axis_x );
  axis_y = normalize( axis_y );
  axis_z = normalize( axis_z );

  m.m11 = axis_x.x * s.x;
  m.m12 = axis_x.y * s.x;
  m.m13 = axis_x.z * s.x;
  m.m21 = axis_y.x * s.y;
  m.m22 = axis_y.y * s.y;
  m.m23 = axis_y.z * s.y;
  m.m31 = axis_z.x * s.z;
  m.m32 = axis_z.y * s.z;
  m.m33 = axis_z.z * s.z;

  return m;
}

static inline mat4d mat4d_set_scale( mat4d m, vec3d s ) {
  vec3d axis_x = { m.m11, m.m12, m.m13 };
  vec3d axis_y = { m.m21, m.m22, m.m23 };
  vec3d axis_z = { m.m31, m.m32, m.m33 };

  axis_x = normalize( axis_x );
  axis_y = normalize( axis_y );
  axis_z = normalize( axis_z );

  m.m11 = axis_x.x * s.x;
  m.m12 = axis_x.y * s.x;
  m.m13 = axis_x.z * s.x;
  m.m21 = axis_y.x * s.y;
  m.m22 = axis_y.y * s.y;
  m.m23 = axis_y.z * s.y;
  m.m31 = axis_z.x * s.z;
  m.m32 = axis_z.y * s.z;
  m.m33 = axis_z.z * s.z;

  return m;
}

// Set scale to transformation matrix
#define set_scale( m, s ) \
  _Generic( ( m ), mat4f: mat4_set_scalef, mat4d: mat4_set_scaled )( m, s )

static inline vec3f mat4f_get_position( mat4f m ) {
  return (vec3f){ .x = m.m41, .y = m.m42, .z = m.m43 };
}

static inline vec3d mat4d_get_position( mat4d m ) {
  return (vec3d){ .x = m.m41, .y = m.m42, .z = m.m43 };
}

// Get position from transformation matrix
#define get_position( m ) \
  _Generic( ( m ), mat4f: mat4f_get_position, mat4d: mat4d_get_position )( m )

static inline mat4f mat4f_set_position( mat4f m, vec3f pos ) {
  m.m41 = pos.x;
  m.m42 = pos.y;
  m.m43 = pos.z;
  return m;
}

static inline mat4d mat4d_set_position( mat4d m, vec3d pos ) {
  m.m41 = pos.x;
  m.m42 = pos.y;
  m.m43 = pos.z;
  return m;
}

// Set position to transformation matrix
#define set_position( m, pos ) \
  _Generic( ( m ), mat4f: mat4f_set_position, mat4d: mat4d_set_position )( \
      ( m ), ( pos ) )

static inline mat4f mat4f_translate( mat4f m, vec3f v ) {
  m.m41 += v.x;
  m.m42 += v.y;
  m.m43 += v.z;
  return m;
}

static inline mat4d mat4d_translate( mat4d m, vec3d v ) {
  m.m41 += v.x;
  m.m42 += v.y;
  m.m43 += v.z;
  return m;
}

// Translate transformation matrix. Move on vector
#define translate( m, v ) \
  _Generic( ( m ), mat4f: mat4f_translate, mat4d: mat4d_translate )( ( m ), \
                                                                     ( v ) )

static inline mat2f mat2f_rotation_matrix( cgf_t radians ) {
#ifdef CGEOM_PRECISE_TRIGONOMETRY
  sincos1cos sc1c = sncs1cs( radians );
  cgf_t c = sc1c.cos;
  cgf_t s = sc1c.sin;
#else
  cgf_t c = CG_fCOS( radians );
  cgf_t s = CG_fSIN( radians );
#endif

  return (mat2f){ .m11 = c, .m21 = s, .m12 = -s, .m22 = c };
}

static inline mat2d mat2d_rotation_matrix( cgd_t radians ) {
#ifdef CGEOM_PRECISE_TRIGONOMETRY
  sincos1cos sc1c = sncs1cs( radians );
  cgd_t c = sc1c.cos;
  cgd_t s = sc1c.sin;
#else
  cgd_t c = CG_dCOS( radians );
  cgd_t s = CG_dSIN( radians );
#endif

  return (mat2d){ .m11 = c, .m21 = s, .m12 = -s, .m22 = c };
}

static inline mat3f mat3f_rotation_matrix( cgf_t radians, vec3f axis ) {
#ifdef CGEOM_PRECISE_TRIGONOMETRY
  sincos1cos sc1c = sncs1cs( radians );
  cgf_t c = sc1c.cos;
  cgf_t s = sc1c.sin;
  cgf_t one_c = sc1c.omc;
#else
  cgf_t c = CG_fCOS( radians );
  cgf_t s = CG_fSIN( radians );
  cgf_t one_c = (cgf_t)( 1.0 ) - c;
#endif

  cgf_t inv_l = (cgf_t)1.0 /
                CG_fSQRT( axis.x * axis.x + axis.y * axis.y + axis.z * axis.z );
  axis.x *= inv_l;
  axis.y *= inv_l;
  axis.z *= inv_l;

  return (mat3f){ .m11 = one_c * axis.x * axis.x + c,
                  .m21 = one_c * axis.x * axis.y + s * axis.z,
                  .m31 = one_c * axis.x * axis.z - s * axis.y,
                  .m12 = one_c * axis.x * axis.y - s * axis.z,
                  .m22 = one_c * axis.y * axis.y + c,
                  .m32 = one_c * axis.y * axis.z + s * axis.x,
                  .m13 = one_c * axis.x * axis.z + s * axis.y,
                  .m23 = one_c * axis.y * axis.z - s * axis.x,
                  .m33 = one_c * axis.z * axis.z + c };
}

static inline mat3d mat3d_rotation_matrix( cgd_t radians, vec3d axis ) {
#ifdef CGEOM_PRECISE_TRIGONOMETRY
  sincos1cos sc1c = sncs1cs( radians );
  cgd_t c = sc1c.cos;
  cgd_t s = sc1c.sin;
  cgd_t one_c = sc1c.omc;
#else
  cgd_t c = CG_dCOS( radians );
  cgd_t s = CG_dSIN( radians );
  cgd_t one_c = (cgd_t)( 1.0 ) - c;
#endif

  cgd_t inv_l = (cgd_t)1.0 /
                CG_dSQRT( axis.x * axis.x + axis.y * axis.y + axis.z * axis.z );
  axis.x *= inv_l;
  axis.y *= inv_l;
  axis.z *= inv_l;

  return (mat3d){ .m11 = one_c * axis.x * axis.x + c,
                  .m21 = one_c * axis.x * axis.y + s * axis.z,
                  .m31 = one_c * axis.x * axis.z - s * axis.y,
                  .m12 = one_c * axis.x * axis.y - s * axis.z,
                  .m22 = one_c * axis.y * axis.y + c,
                  .m32 = one_c * axis.y * axis.z + s * axis.x,
                  .m13 = one_c * axis.x * axis.z + s * axis.y,
                  .m23 = one_c * axis.y * axis.z - s * axis.x,
                  .m33 = one_c * axis.z * axis.z + c };
}

static inline mat4f mat4f_rotation_matrix( cgf_t radians, vec3f axis ) {
  mat3f r = mat3f_rotation_matrix( radians, axis );
  return (mat4f){ .m11 = r.m11,
                  .m21 = r.m21,
                  .m31 = r.m31,
                  .m41 = 0.0f,
                  .m12 = r.m12,
                  .m22 = r.m22,
                  .m32 = r.m32,
                  .m42 = 0.0f,
                  .m13 = r.m13,
                  .m23 = r.m23,
                  .m33 = r.m33,
                  .m43 = 0.0f,
                  .m14 = 0.0f,
                  .m24 = 0.0f,
                  .m34 = 0.0f,
                  .m44 = 1.0f };
}

static inline mat4d mat4d_rotation_matrix( cgd_t radians, vec3d axis ) {
  mat3d r = mat3d_rotation_matrix( radians, axis );
  return (mat4d){ .m11 = r.m11,
                  .m21 = r.m21,
                  .m31 = r.m31,
                  .m41 = 0.0f,
                  .m12 = r.m12,
                  .m22 = r.m22,
                  .m32 = r.m32,
                  .m42 = 0.0f,
                  .m13 = r.m13,
                  .m23 = r.m23,
                  .m33 = r.m33,
                  .m43 = 0.0f,
                  .m14 = 0.0f,
                  .m24 = 0.0f,
                  .m34 = 0.0f,
                  .m44 = 1.0f };
}

static inline mat2f mat2f_rotate( mat2f m, cgf_t radians ) {
  return multiply( mat2f_rotation_matrix( radians ), m );
}

static inline mat2d mat2d_rotate( mat2d m, cgd_t radians ) {
  return multiply( mat2d_rotation_matrix( radians ), m );
}

// Rotate matrix 2x2
#define mat2_rotate( m, radians ) \
  _Generic( ( m ), mat2f: mat2f_rotate, mat2d: mat2d_rotate )( ( m ), \
                                                               ( radians ) )

static inline mat3f mat3f_rotate( mat3f m, cgf_t radians, vec3f axis ) {
  return multiply( mat3f_rotation_matrix( radians, axis ), m );
}

static inline mat3d mat3d_rotate( mat3d m, cgd_t radians, vec3d axis ) {
  return multiply( mat3d_rotation_matrix( radians, axis ), m );
}

static inline mat4f mat4f_rotate( mat4f m, cgf_t radians, vec3f axis ) {
  return multiply( mat4f_rotation_matrix( radians, axis ), m );
}

static inline mat4d mat4d_rotate( mat4d m, cgd_t radians, vec3d axis ) {
  return multiply( mat4d_rotation_matrix( radians, axis ), m );
}

// Rotate matrix 3x3 4x4
#define mat_rotate( m, radians, axis ) \
  _Generic( ( m ), \
      mat3f: mat3f_rotate, \
      mat3d: mat3d_rotate, \
      mat4f: mat4f_rotate, \
      mat4d: mat4d_rotate )( ( m ), ( radians ), ( axis ) )

static inline mat4f mat4f_lookat_matrix( vec3f eye, vec3f center, vec3f up ) {
  vec3f f = normalize( sub( center, eye ) );

  vec3f s = normalize( cross( f, up ) );
  vec3f u = cross( s, f );

  return (mat4f){ .m11 = s.x,
                  .m21 = u.x,
                  .m31 = -f.x,
                  .m41 = 0.0f,
                  .m12 = s.y,
                  .m22 = u.y,
                  .m32 = -f.y,
                  .m42 = 0.0f,
                  .m13 = s.z,
                  .m23 = u.z,
                  .m33 = -f.z,
                  .m43 = 0.0f,
                  .m14 = -dot( s, eye ),
                  .m24 = -dot( u, eye ),
                  .m34 = dot( f, eye ),
                  .m44 = 1.0f };
}

static inline mat4d mat4d_lookat_matrix( vec3d eye, vec3d center, vec3d up ) {
  vec3d f = normalize( sub( center, eye ) );

  vec3d s = normalize( cross( f, up ) );
  vec3d u = cross( s, f );

  return (mat4d){ .m11 = s.x,
                  .m21 = u.x,
                  .m31 = -f.x,
                  .m41 = 0.0,
                  .m12 = s.y,
                  .m22 = u.y,
                  .m32 = -f.y,
                  .m42 = 0.0,
                  .m13 = s.z,
                  .m23 = u.z,
                  .m33 = -f.z,
                  .m43 = 0.0,
                  .m14 = -dot( s, eye ),
                  .m24 = -dot( u, eye ),
                  .m34 = dot( f, eye ),
                  .m44 = 1.0 };
}

// Get "look at" matrix
#define lookat_matrix( eye, center, up ) \
  _Generic( ( eye ), vec3f: mat4f_lookat_matrix, vec3d: mat4d_lookat_matrix )( \
      ( eye ), ( center ), ( up ) )

static inline mat4f mat4f_look_at( mat4f m, vec3f eye, vec3f center,
                                   vec3f up ) {
  return multiply( lookat_matrix( eye, center, up ), m );
}

static inline mat4d mat4d_look_at( mat4d m, vec3d eye, vec3d center,
                                   vec3d up ) {
  return multiply( lookat_matrix( eye, center, up ), m );
}

// Rotate matrix to looking at
#define look_at( m, eye, center, up ) \
  _Generic( ( m ), vec3f: mat4f_look_at, vec3d: mat4d_look_at )( \
      ( m ), ( eye ), ( center ), ( up ) )

static inline mat4f mat4f_ortho_matrix( cgf_t left, cgf_t right, cgf_t bottom,
                                        cgf_t top, cgf_t near, cgf_t far ) {
  cgf_t rl = right - left;
  cgf_t tb = top - bottom;
  cgf_t fn = far - near;

  return (mat4f){ .m11 = (cgf_t)2.0 / rl,
                  .m21 = 0.0f,
                  .m31 = 0.0f,
                  .m41 = 0.0f,

                  .m12 = 0.0f,
                  .m22 = (cgf_t)2.0 / tb,
                  .m32 = 0.0f,
                  .m42 = 0.0f,

                  .m13 = 0.0f,
                  .m23 = 0.0f,
                  .m33 = (cgf_t)-2.0 / fn,
                  .m43 = 0.0f,

                  .m14 = -( right + left ) / rl,
                  .m24 = -( top + bottom ) / tb,
                  .m34 = -( far + near ) / fn,
                  .m44 = 1.0f };
}

static inline mat4d mat4d_ortho_matrix( cgd_t left, cgd_t right, cgd_t bottom,
                                        cgd_t top, cgd_t near, cgd_t far ) {
  cgd_t rl = right - left;
  cgd_t tb = top - bottom;
  cgd_t fn = far - near;

  return (mat4d){ .m11 = (cgd_t)2.0 / rl,
                  .m21 = 0.0,
                  .m31 = 0.0,
                  .m41 = 0.0,

                  .m12 = 0.0,
                  .m22 = (cgd_t)2.0 / tb,
                  .m32 = 0.0,
                  .m42 = 0.0,

                  .m13 = 0.0,
                  .m23 = 0.0,
                  .m33 = (cgd_t)-2.0 / fn,
                  .m43 = 0.0,

                  .m14 = -( right + left ) / rl,
                  .m24 = -( top + bottom ) / tb,
                  .m34 = -( far + near ) / fn,
                  .m44 = 1.0 };
}

static inline mat4f mat4f_ortho( mat4f m, cgf_t left, cgf_t right, cgf_t bottom,
                                 cgf_t top, cgf_t near, cgf_t far ) {
  return multiply( mat4f_ortho_matrix( left, right, bottom, top, near, far ),
                   m );
}

static inline mat4d mat4d_ortho( mat4d m, cgd_t left, cgd_t right, cgd_t bottom,
                                 cgd_t top, cgd_t near, cgd_t far ) {
  return multiply( mat4d_ortho_matrix( left, right, bottom, top, near, far ),
                   m );
}

// Set orthographic projection
#define ortho( m, left, fight, bottom, top, near, far ) \
  _Generic( ( m ), mat4f: mat4f_ortho, mat4d: mat4d_ortho )( \
      ( m ), ( left ), ( right ), ( bottom ), ( top ), ( near ), ( far ) )

static inline mat4f mat4f_frustum_matrix( cgf_t left, cgf_t right, cgf_t bottom,
                                          cgf_t top, cgf_t near, cgf_t far ) {
  cgf_t rl = right - left;
  cgf_t tb = top - bottom;
  cgf_t fn = far - near;
  cgf_t n2 = near * (cgf_t)2.0;

  return (mat4f){ .m11 = n2 / rl,
                  .m21 = 0.0f,
                  .m31 = 0.0f,
                  .m41 = 0.0f,

                  .m12 = 0.0f,
                  .m22 = n2 / tb,
                  .m32 = 0.0f,
                  .m42 = 0.0f,

                  .m13 = ( right + left ) / rl,
                  .m23 = ( top + bottom ) / tb,
                  .m33 = -( far + near ) / fn,
                  .m43 = -1.0f,

                  .m14 = 0.0f,
                  .m24 = 0.0f,
                  .m34 = -( n2 * far ) / fn,
                  .m44 = 0.0f };
}

static inline mat4d mat4d_frustum_matrix( cgd_t left, cgd_t right, cgd_t bottom,
                                          cgd_t top, cgd_t near, cgd_t far ) {
  cgd_t rl = right - left;
  cgd_t tb = top - bottom;
  cgd_t fn = far - near;
  cgd_t n2 = near * (cgf_t)2.0;

  return (mat4d){ .m11 = n2 / rl,
                  .m21 = 0.0,
                  .m31 = 0.0,
                  .m41 = 0.0,

                  .m12 = 0.0,
                  .m22 = n2 / tb,
                  .m32 = 0.0,
                  .m42 = 0.0,

                  .m13 = ( right + left ) / rl,
                  .m23 = ( top + bottom ) / tb,
                  .m33 = -( far + near ) / fn,
                  .m43 = -1.0,

                  .m14 = 0.0,
                  .m24 = 0.0,
                  .m34 = -( n2 * far ) / fn,
                  .m44 = 0.0 };
}

static inline mat4f mat4f_perspective_matrix( cgf_t fov_radians, cgf_t aspect,
                                              cgf_t near, cgf_t far ) {
  cgf_t half_h = CG_fTAN( fov_radians * (cgf_t)0.5 ) * near;
  cgf_t half_w = half_h * aspect;
  return mat4f_frustum_matrix( -half_w, half_w, -half_h, half_h, near, far );
}

static inline mat4d mat4d_perspective_matrix( cgd_t fov_radians, cgd_t aspect,
                                              cgd_t near, cgd_t far ) {
  cgd_t half_h = CG_dTAN( fov_radians * (cgd_t)0.5 ) * near;
  cgd_t half_w = half_h * aspect;
  return mat4d_frustum_matrix( -half_w, half_w, -half_h, half_h, near, far );
}

static inline mat4f mat4f_frustum( mat4f m, cgf_t left, cgf_t right,
                                   cgf_t bottom, cgf_t top, cgf_t near,
                                   cgf_t far ) {
  return multiply( mat4f_frustum_matrix( left, right, bottom, top, near, far ),
                   m );
}

static inline mat4d mat4d_frustum( mat4d m, cgd_t left, cgd_t right,
                                   cgd_t bottom, cgd_t top, cgd_t near,
                                   cgd_t far ) {
  return multiply( mat4d_frustum_matrix( left, right, bottom, top, near, far ),
                   m );
}

// Set perspective projection from frustum
#define frustum( m, left, fight, bottom, top, near, far ) \
  _Generic( ( m ), mat4f: mat4f_frustum, mat4d: mat4d_frustum )( \
      ( m ), ( left ), ( right ), ( bottom ), ( top ), ( near ), ( far ) )

static inline mat4f mat4f_perspective_fov( mat4f m, cgf_t fov, cgf_t aspect,
                                           cgf_t near, cgf_t far ) {
  return multiply( mat4f_perspective_matrix( fov, aspect, near, far ), m );
}

static inline mat4d mat4d_perspective_fov( mat4d m, cgd_t fov, cgd_t aspect,
                                           cgd_t near, cgd_t far ) {
  return multiply( mat4d_perspective_matrix( fov, aspect, near, far ), m );
}

// Set perspective projection from field of view
#define perspective_fov( m, fov_radians, aspect, near, far ) \
  _Generic( ( m ), \
      mat4f: mat4f_perspective_fov, \
      mat4d: mat4d_perspective_fov )( ( m ), ( fov_radians ), ( aspect ), \
                                      ( near ), ( far ) )

static inline mat4f mat4f_perspective_infinite( cgf_t fov_radians, cgf_t aspect,
                                                cgf_t near ) {
  cgf_t f = (cgf_t)1.0 / CG_fTAN( fov_radians * (cgf_t)0.5 );
  return (mat4f){ .m11 = f / aspect,
                  .m21 = 0.0f,
                  .m31 = 0.0f,
                  .m41 = 0.0f,
                  .m12 = 0.0f,
                  .m22 = f,
                  .m32 = 0.0f,
                  .m42 = 0.0f,
                  .m13 = 0.0f,
                  .m23 = 0.0f,
                  .m33 = -1.0f,
                  .m43 = -1.0f,
                  .m14 = 0.0f,
                  .m24 = 0.0f,
                  .m34 = -(cgf_t)2.0 * near,
                  .m44 = 0.0f };
}

static inline mat4d mat4d_perspective_infinite( cgd_t fov_radians, cgd_t aspect,
                                                cgd_t near ) {
  cgd_t f = (cgd_t)1.0 / CG_dTAN( fov_radians * (cgd_t)0.5 );
  return (mat4d){ .m11 = f / aspect,
                  .m21 = 0.0,
                  .m31 = 0.0,
                  .m41 = 0.0,
                  .m12 = 0.0,
                  .m22 = f,
                  .m32 = 0.0,
                  .m42 = 0.0,
                  .m13 = 0.0,
                  .m23 = 0.0,
                  .m33 = -1.0,
                  .m43 = -1.0,
                  .m14 = 0.0,
                  .m24 = 0.0,
                  .m34 = -(cgf_t)2.0 * near,
                  .m44 = 0.0 };
}

static inline mat4f mat4f_apply_perspective_infinite( mat4f m, cgf_t fov,
                                                      cgf_t aspect,
                                                      cgf_t near ) {
  return multiply( mat4f_perspective_infinite( fov, aspect, near ), m );
}

static inline mat4d mat4d_apply_perspective_infinite( mat4d m, cgd_t fov,
                                                      cgd_t aspect,
                                                      cgd_t near ) {
  return multiply( mat4d_perspective_infinite( fov, aspect, near ), m );
}

// Set perspective infinite
#define apply_perspective_infinite( m, fov_radians, aspect, near ) \
  _Generic( ( m ), \
      mat4f: mat4f_apply_perspective_infinite, \
      mat4d: mat4d_apply_perspective_infinite )( ( m ), ( fov_radians ), \
                                                 ( aspect ), ( near ) )

#ifdef CGEOM_EASES

static inline cgf_t quadratic_ease_out( cgf_t f ) {
  return -f * ( f - (cgf_t)( 2.0 ) );
}

static inline cgf_t quadratic_ease_in( cgf_t f ) { return f * f; }

static inline cgf_t quadratic_ease_in_out( cgf_t f ) {
  cgf_t a = (cgf_t)( 0.0 );
  if( f < (cgf_t)( 0.5 ) ) {
    a = (cgf_t)( 2.0 ) * f * f;
  } else {
    a = -(cgf_t)( 2.0 ) * f * f + (cgf_t)( 4.0 ) * f - (cgf_t)( 1.0 );
  }
  return a;
}

static inline cgf_t cubic_ease_out( cgf_t f ) {
  cgf_t a = f - (cgf_t)( 1.0 );
  return a * a * a + (cgf_t)( 1.0 );
}

static inline cgf_t cubic_ease_in( cgf_t f ) { return f * f * f; }

static inline cgf_t cubic_ease_in_out( cgf_t f ) {
  cgf_t a = (cgf_t)( 0.0 );
  if( f < (cgf_t)( 0.5 ) ) {
    a = (cgf_t)( 4.0 ) * f * f * f;
  } else {
    a = (cgf_t)( 2.0 ) * f - (cgf_t)( 2.0 );
    a = (cgf_t)( 0.5 ) * a * a * a + (cgf_t)( 1.0 );
  }
  return a;
}

static inline cgf_t quartic_ease_out( cgf_t f ) {
  cgf_t a = f - (cgf_t)( 1.0 );
  return a * a * a * ( (cgf_t)( 1.0 ) - f ) + (cgf_t)( 1.0 );
}

static inline cgf_t quartic_ease_in( cgf_t f ) { return f * f * f * f; }

static inline cgf_t quartic_ease_in_out( cgf_t f ) {
  cgf_t a = (cgf_t)( 0.0 );
  if( f < (cgf_t)( 0.5 ) ) {
    a = (cgf_t)( 8.0 ) * f * f * f * f;
  } else {
    a = f - (cgf_t)( 1.0 );
    a = -(cgf_t)( 8.0 ) * a * a * a * a + (cgf_t)( 1.0 );
  }
  return a;
}

static inline cgf_t quintic_ease_out( cgf_t f ) {
  cgf_t a = f - (cgf_t)( 1.0 );
  return a * a * a * a * a + (cgf_t)( 1.0 );
}

static inline cgf_t quintic_ease_in( cgf_t f ) { return f * f * f * f * f; }

static inline cgf_t quintic_ease_in_out( cgf_t f ) {
  cgf_t a = (cgf_t)( 0.0 );
  if( f < (cgf_t)( 0.5 ) ) {
    a = (cgf_t)( 16.0 ) * f * f * f * f * f;
  } else {
    a = (cgf_t)( 2.0 ) * f - (cgf_t)( 2.0 );
    a = (cgf_t)( 0.5 ) * a * a * a * a * a + (cgf_t)( 1.0 );
  }
  return a;
}

static inline cgf_t sine_ease_out( cgf_t f ) { return CG_fSIN( f * CG_fPI_2 ); }

static inline cgf_t sine_ease_in( cgf_t f ) {
  return CG_fSIN( ( f - (cgf_t)( 1.0 ) ) * CG_fPI_2 ) + (cgf_t)( 1.0 );
}

static inline cgf_t sine_ease_in_out( cgf_t f ) {
  return (cgf_t)( 0.5 ) * ( (cgf_t)( 1.0 ) - CG_fCOS( f * CG_fPI ) );
}

static inline cgf_t circular_ease_out( cgf_t f ) {
  return CG_fSQRT( ( (cgf_t)( 2.0 ) - f ) * f );
}

static inline cgf_t circular_ease_in( cgf_t f ) {
  return (cgf_t)( 1.0 ) - CG_fSQRT( (cgf_t)( 1.0 ) - ( f * f ) );
}

static inline cgf_t circular_ease_in_out( cgf_t f ) {
  cgf_t a = (cgf_t)( 0.0 );
  if( f < (cgf_t)( 0.5 ) ) {
    a = (cgf_t)( 0.5 ) *
        ( (cgf_t)( 1.0 ) -
          CG_fSQRT( (cgf_t)( 1.0 ) - (cgf_t)( 4.0 ) * f * f ) );
  } else {
    a = (cgf_t)( 0.5 ) * ( CG_fSQRT( -( (cgf_t)( 2.0 ) * f - (cgf_t)( 3.0 ) ) *
                                     ( (cgf_t)( 2.0 ) * f - (cgf_t)( 1.0 ) ) ) +
                           (cgf_t)( 1.0 ) );
  }
  return a;
}

static inline cgf_t exponential_ease_out( cgf_t f ) {
  cgf_t a = f;
  if( CG_fABS( a ) > CG_fEPSILON ) {
    a = (cgf_t)( 1.0 ) - CG_fPOW( (cgf_t)( 2.0 ), -(cgf_t)( 10.0 ) * f );
  }
  return a;
}

static inline cgf_t exponential_ease_in( cgf_t f ) {
  cgf_t a = f;
  if( CG_fABS( a ) > CG_fEPSILON ) {
    a = CG_fPOW( (cgf_t)( 2.0 ), (cgf_t)( 10.0 ) * ( f - (cgf_t)( 1.0 ) ) );
  }
  return a;
}

static inline cgf_t exponential_ease_in_out( cgf_t f ) {
  cgf_t a = f;
  if( f < (cgf_t)( 0.5 ) ) {
    a = (cgf_t)( 0.5 ) *
        CG_fPOW( (cgf_t)( 2.0 ), ( (cgf_t)( 20.0 ) * f ) - (cgf_t)( 10.0 ) );
  } else {
    a = -(cgf_t)( 0.5 ) *
            CG_fPOW( (cgf_t)( 2.0 ), -(cgf_t)( 20.0 ) * f + (cgf_t)( 10.0 ) ) +
        (cgf_t)( 1.0 );
  }
  return a;
}

static inline cgf_t elastic_ease_out( cgf_t f ) {
  return CG_fSIN( -(cgf_t)( 13.0 ) * CG_fPI_2 * ( f + (cgf_t)( 1.0 ) ) ) *
             CG_fPOW( (cgf_t)( 2.0 ), -(cgf_t)( 10.0 ) * f ) +
         (cgf_t)( 1.0 );
}

static inline cgf_t elastic_ease_in( cgf_t f ) {
  return CG_fSIN( (cgf_t)( 13.0 ) * CG_fPI_2 * f ) *
         CG_fPOW( (cgf_t)( 2.0 ), (cgf_t)( 10.0 ) * ( f - (cgf_t)( 1.0 ) ) );
}

static inline cgf_t elastic_ease_in_out( cgf_t f ) {
  cgf_t a = (cgf_t)( 0.0 );
  if( f < (cgf_t)( 0.5 ) ) {
    a = (cgf_t)( 0.5 ) *
        CG_fSIN( (cgf_t)( 13.0 ) * CG_fPI_2 * ( (cgf_t)( 2.0 ) * f ) ) *
        CG_fPOW( (cgf_t)( 2.0 ), (cgf_t)( 10.0 ) * ( ( (cgf_t)( 2.0 ) * f ) -
                                                     (cgf_t)( 1.0 ) ) );
  } else {
    a = (cgf_t)( 0.5 ) *
        ( CG_fSIN(
              -(cgf_t)( 13.0 ) * CG_fPI_2 *
              ( ( (cgf_t)( 2.0 ) * f - (cgf_t)( 1.0 ) ) + (cgf_t)( 1.0 ) ) ) *
              CG_fPOW( (cgf_t)( 2.0 ), -(cgf_t)( 10.0 ) * ( (cgf_t)( 2.0 ) * f -
                                                            (cgf_t)( 1.0 ) ) ) +
          (cgf_t)( 2.0 ) );
  }
  return a;
}

static inline cgf_t back_ease_out( cgf_t f ) {
  cgf_t a = (cgf_t)( 1.0 ) - f;
  return (cgf_t)( 1.0 ) - ( a * a * a - a * CG_fSIN( a * CG_fPI ) );
}

static inline cgf_t back_ease_in( cgf_t f ) {
  return f * f * f - f * CG_fSIN( f * CG_fPI );
}

static inline cgf_t back_ease_in_out( cgf_t f ) {
  cgf_t a = (cgf_t)( 0.0 );
  if( f < (cgf_t)( 0.5 ) ) {
    a = (cgf_t)( 2.0 ) * f;
    a = (cgf_t)( 0.5 ) * ( a * a * a - a * CG_fSIN( a * CG_fPI ) );
  } else {
    a = ( (cgf_t)( 1.0 ) - ( (cgf_t)( 2.0 ) * f - (cgf_t)( 1.0 ) ) );
    a = (cgf_t)( 0.5 ) *
            ( (cgf_t)( 1.0 ) - ( a * a * a - a * CG_fSIN( f * CG_fPI ) ) ) +
        (cgf_t)( 0.5 );
  }
  return a;
}

static inline cgf_t bounce_ease_out( cgf_t f ) {
  cgf_t a = (cgf_t)( 0.0 );
  if( f < (cgf_t)( 4.0 ) / (cgf_t)( 11.0 ) ) {
    a = ( (cgf_t)( 121.0 ) * f * f ) / (cgf_t)( 16.0 );
  } else if( f < (cgf_t)( 8.0 ) / (cgf_t)( 11.0 ) ) {
    a = ( (cgf_t)( 363.0 ) / (cgf_t)( 40.0 ) * f * f ) -
        ( (cgf_t)( 99.0 ) / (cgf_t)( 10.0 ) * f ) +
        (cgf_t)( 17.0 ) / (cgf_t)( 5.0 );
  } else if( f < (cgf_t)( 9.0 ) / (cgf_t)( 10.0 ) ) {
    a = ( (cgf_t)( 4356.0 ) / (cgf_t)( 361.0 ) * f * f ) -
        ( (cgf_t)( 35442.0 ) / (cgf_t)( 1805.0 ) * f ) +
        (cgf_t)( 16061.0 ) / (cgf_t)( 1805.0 );
  } else {
    a = ( (cgf_t)( 54.0 ) / (cgf_t)( 5.0 ) * f * f ) -
        ( (cgf_t)( 513.0 ) / (cgf_t)( 25.0 ) * f ) +
        (cgf_t)( 268.0 ) / (cgf_t)( 25.0 );
  }
  return a;
}

static inline cgf_t bounce_ease_in( cgf_t f ) {
  return (cgf_t)( 1.0 ) - bounce_ease_out( (cgf_t)( 1.0 ) - f );
}

static inline cgf_t bounce_ease_in_out( cgf_t f ) {
  cgf_t a = (cgf_t)( 0.0 );
  if( f < (cgf_t)( 0.5 ) ) {
    a = (cgf_t)( 0.5 ) * bounce_ease_in( f * (cgf_t)( 2.0 ) );
  } else {
    a = (cgf_t)( 0.5 ) *
            bounce_ease_out( f * (cgf_t)( 2.0 ) - (cgf_t)( 1.0 ) ) +
        (cgf_t)( 0.5 );
  }
  return a;
}

#endif // CGEOM_EASES

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CGEOM_H