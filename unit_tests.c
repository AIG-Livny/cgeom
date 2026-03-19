#include "utest.h/utest.h"
#include "cgeom.h"

UTEST(test, nearly_equal) {
    float a,b;

    a = 0.3;
    b = 0.3;
    ASSERT_TRUE(nearly_equal(a,b,CG_fEPSILON));

    a = 0.3000001;
    b = 0.3;
    ASSERT_TRUE(nearly_equal(a,b,CG_fEPSILON));

    a = 0.4;
    b = 0.3;
    ASSERT_TRUE(!nearly_equal(a,b,CG_fEPSILON));

    double c;
    double d;

    c = 0.3000001;
    d = 0.3;
    ASSERT_TRUE(!nearly_equal(a,b,CG_dEPSILON));

    c = 0.3000000000000001;
    d = 0.3;
    ASSERT_TRUE(nearly_equal(c,d,CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(((vec2f){0.0000001,1.0000001}),((vec2f){0,1}),CG_fEPSILON));
    ASSERT_TRUE(nearly_equal(((vec3f){0.0000001,1.0000001,0}),((vec3f){0,1,0}),CG_fEPSILON));
    ASSERT_TRUE(nearly_equal(((vec4f){0.0000001,1.0000001,0,0}),((vec4f){0,1,0,0}),CG_fEPSILON));
}


UTEST(test, clamp_value) {
    ASSERT_EQ(clamp(10,1,9), 9);
    ASSERT_EQ(clamp(0,1,9), 1);
    ASSERT_EQ(clamp(-1,1,9), 1);
    ASSERT_EQ(clamp(5,1,9), 5);
}

UTEST(test, to_radians) {
    ASSERT_EQ(to_radians((float)180),CG_fPI);
    ASSERT_EQ(to_radians((float)90),CG_fPI_2);
    ASSERT_EQ(to_radians((float)270),CG_fPI_2 + CG_fPI);
    ASSERT_EQ(to_radians((float)45),CG_fPI_4);

    ASSERT_EQ(to_radians((double)180),CG_dPI);
    ASSERT_EQ(to_radians((double)90),CG_dPI_2);
    ASSERT_EQ(to_radians((double)270),CG_dPI_2 + CG_dPI);
    ASSERT_EQ(to_radians((double)45),CG_dPI_4);
}

UTEST(test, to_degrees) {
    ASSERT_EQ(to_degrees(CG_fPI),180);
    ASSERT_EQ(to_degrees(CG_fPI_2),90);
    ASSERT_EQ(to_degrees(CG_fPI_2 + CG_fPI),270);
    ASSERT_EQ(to_degrees(CG_fPI_4),45);

    ASSERT_EQ(to_degrees(CG_dPI),180);
    ASSERT_EQ(to_degrees(CG_dPI_2),90);
    ASSERT_EQ(to_degrees(CG_dPI_2 + CG_dPI),270);
    ASSERT_EQ(to_degrees(CG_dPI_4),45);
}

UTEST(test, vec_to_vec_cast) {
    ASSERT_TRUE( equal(vec_to_vec2i(((vec3f){1,2,3})),     ((vec2i){1,2})) );
    ASSERT_TRUE( equal(vec_to_vec2i(((vec4f){1,2,3,4})),   ((vec2i){1,2})) );
    ASSERT_TRUE( equal(vec_to_vec3i(((vec4f){1,2,3,4})),   ((vec3i){1,2,3})) );
}

UTEST(test, is_zero_) {
    ASSERT_TRUE(is_zero(((vec2i){0,0})));
    ASSERT_TRUE(is_zero(((vec3f){0,0,0})));
    ASSERT_TRUE(is_zero(((vec4f){0,0,0,0})));
    ASSERT_FALSE(is_zero(((vec3f){1,0,0})));
    ASSERT_FALSE(is_zero(((vec3f){0,0,1})));
}

UTEST(test, equal_) {
    ASSERT_TRUE(equal(((vec3i){1,2,3}),((vec3i){1,2,3})));
    ASSERT_FALSE(equal(((vec3i){1,2,3}),((vec3i){2,2,2})));
}

UTEST(test, sign) {
    ASSERT_TRUE(equal(vec_sign(((vec2d){-2.3, 2.3})),     ((vec2d){-1,1})));
    ASSERT_TRUE(equal(vec_sign(((vec3f){0,-1.3,0.002})),  ((vec3f){0,-1,1})));
    ASSERT_TRUE(equal(vec_sign(((vec4i){0,-1,100,-2})),   ((vec4i){0,-1,1,-1})));
}

UTEST(test, add_) {
    ASSERT_TRUE(equal(add(((vec2i){1,3}), ((vec2i){1,3})),     ((vec2i){2,6})));
    ASSERT_TRUE(equal(add(((vec3f){1,3,5}), ((vec3f){1,3,3})),     ((vec3f){2,6,8})));
}

UTEST(test, multiply_) {
    mat2f ma = {
        0,1,
        2,3,
    };

    mat2f mb = {
        4,5,
        6,7,
    };

    mat2f mexpect = {
        6,7,
        26,31,
    };

    mat2f mexpect_num = {
        8,10,
        12,14,
    };

    ASSERT_TRUE(equal(multiply(((vec2i){1,3}), ((vec2i){1,3})), ((vec2i){1,9})));
    ASSERT_TRUE(equal(multiply(ma, mb), mexpect));
    ASSERT_TRUE(equal(multiply_num(mb, 2), mexpect_num));
    ASSERT_TRUE(equal(divide_num(mexpect_num, 2), mb));
}

UTEST(test, snap_) {
    vec3f grid_size = {2,3,4};
    vec3f v = {2.2, 4.6, 4.1};

    vec3f g = snap_num(v,2);

    ASSERT_TRUE(equal(snap(v,grid_size), ((vec3f){2,6,4})));
    ASSERT_TRUE(equal(snap_num(v,2), ((vec3f){2,4,4})));
}

UTEST(test, negative) {
    ASSERT_TRUE(equal(negative(((vec2i){1,3})), ((vec2i){-1,-3})));
}

UTEST(test, vec_abs) {
    ASSERT_TRUE(equal(vec_abs(((vec2d){-5.5, 2.3})),      ((vec2d){5.5, 2.3})));
    ASSERT_TRUE(equal(vec_abs(((vec3f){0.0f, -10.2f, -0.1f})), ((vec3f){0.0f, 10.2f, 0.1f})));
    ASSERT_TRUE(equal(vec_abs(((vec4i){-1, -2, 3, 0})),   ((vec4i){1, 2, 3, 0})));
}

UTEST(test, vec_max) {
    ASSERT_TRUE(equal(vec_max(((vec2d){1.0, -5.0}), ((vec2d){0.5, 2.0})),     ((vec2d){1.0, 2.0})));
    ASSERT_TRUE(equal(vec_max(((vec3f){-1.0f, 0.0f, 5.5f}), ((vec3f){-2.0f, -1.0f, 3.0f})), ((vec3f){-1.0f, 0.0f, 5.5f})));
    ASSERT_TRUE(equal(vec_max(((vec4i){10, 20, 30, 40}), ((vec4i){5, 25, 15, 45})), ((vec4i){10, 25, 30, 45})));
}

UTEST(test, vec_min) {
    ASSERT_TRUE(equal(vec_min(((vec2d){1.0, -5.0}), ((vec2d){0.5, 2.0})),     ((vec2d){0.5, -5.0})));
    ASSERT_TRUE(equal(vec_min(((vec3f){-1.0f, 0.0f, 5.5f}), ((vec3f){-2.0f, -1.0f, 3.0f})), ((vec3f){-2.0f, -1.0f, 3.0f})));
    ASSERT_TRUE(equal(vec_min(((vec4i){10, 20, 30, 40}), ((vec4i){5, 25, 15, 45})), ((vec4i){5, 20, 15, 40})));
}

UTEST(test, vec_clamp) {
    ASSERT_TRUE(equal(vec_clamp(((vec2d){-10.5, 20.5}), ((vec2d){0.0, 0.0}), ((vec2d){10.0, 10.0})),
                      ((vec2d){0.0, 10.0})));

    ASSERT_TRUE(equal(vec_clamp(((vec3f){-1.0f, 0.5f, 5.0f}), ((vec3f){-2.0f, 0.0f, 1.0f}), ((vec3f){2.0f, 1.0f, 3.0f})),
                      ((vec3f){-1.0f, 0.5f, 3.0f})));

    ASSERT_TRUE(equal(vec_clamp(((vec4i){10, -10, 50, 5}), ((vec4i){0, 0, 0, 0}), ((vec4i){20, 20, 20, 20})),
                      ((vec4i){10, 0, 20, 5})));
}

UTEST(test, vec_tangent) {
    ASSERT_TRUE(nearly_equal(vec_tangent(((vec2d){1.0, 0.0})),  ((vec2d){0.0, 1.0}), CG_fEPSILON));
    ASSERT_TRUE(nearly_equal(vec_tangent(((vec2d){0.0, 1.0})),  ((vec2d){-1.0, 0.0}), CG_fEPSILON));

    ASSERT_TRUE(nearly_equal(vec_tangent(((vec2f){1.0f, 2.0f})), ((vec2f){-2.0f, 1.0f}), CG_fEPSILON));

    ASSERT_TRUE(nearly_equal(vec_tangent(((vec2i){10, 5})),     ((vec2i){-5, 10}), CG_fEPSILON));
}

UTEST(test, vec_cotangent) {
    ASSERT_TRUE(nearly_equal(vec_cotangent(((vec2d){1.0, 0.0})),  ((vec2d){0.0, -1.0}),CG_fEPSILON));
    ASSERT_TRUE(nearly_equal(vec_cotangent(((vec2d){0.0, 1.0})),  ((vec2d){1.0, 0.0}), CG_fEPSILON));

    ASSERT_TRUE(nearly_equal(vec_cotangent(((vec2f){1.0f, 2.0f})), ((vec2f){2.0f, -1.0f}), CG_fEPSILON));

    ASSERT_TRUE(nearly_equal(vec_cotangent(((vec2i){10, 5})),     ((vec2i){5, -10}), CG_fEPSILON));
}

UTEST(test, cross) {
    ASSERT_EQ(cross(((vec2d){1.0, 0.0}), ((vec2d){0.0, 1.0})), 1.0);
    ASSERT_EQ(cross(((vec2f){1.0f, 2.0f}), ((vec2f){3.0f, 4.0f})), -2.0f);

    ASSERT_TRUE(equal(cross(((vec3f){1.0f, 0.0f, 0.0f}), ((vec3f){0.0f, 1.0f, 0.0f})),
                      ((vec3f){0.0f, 0.0f, 1.0f})));
    ASSERT_TRUE(equal(cross(((vec3d){0.0, 0.0, 1.0}), ((vec3d){0.0, 1.0, 0.0})),
                      ((vec3d){-1.0, 0.0, 0.0})));

    ASSERT_TRUE(equal(cross(((vec3i){1, 0, 0}), ((vec3i){0, 1, 0})),
                      ((vec3i){0, 0, 1})));
}

UTEST(test, length) {
    ASSERT_NEAR(length(((vec2d){3.0, 4.0})), 5.0, CG_dEPSILON);
    ASSERT_NEAR(length(((vec3f){0.0f, 0.0f, 10.0f})), 10.0f, CG_fEPSILON);

    ASSERT_NEAR(length(((vec4i){1, 1, 1, 1})), 2.0, CG_dEPSILON);
}

UTEST(test, normalize) {
    ASSERT_TRUE(nearly_equal(normalize(((vec2d){3.0, 4.0})),
                             ((vec2d){0.6, 0.8}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(normalize(((vec3f){0.0f, 10.0f, 0.0f})),
                             ((vec3f){0.0f, 1.0f, 0.0f}), CG_fEPSILON));

    ASSERT_NEAR(length(normalize(((vec4f){1.0f, 2.0f, 3.0f, 4.0f}))), 1.0f, CG_fEPSILON);
}

UTEST(test, dot) {
    ASSERT_NEAR(dot(((vec2d){1.0, 2.0}), ((vec2d){3.0, 4.0})), 11.0, CG_dEPSILON);

    ASSERT_NEAR(dot(((vec3f){1.0f, 0.0f, 0.0f}), ((vec3f){0.0f, 1.0f, 0.0f})), 0.0f, CG_fEPSILON);

    ASSERT_EQ(dot(((vec4i){1, 2, 3, 4}), ((vec4i){-1, -1, -1, -1})), -10);
}

UTEST(test, vec_project) {
    ASSERT_TRUE(nearly_equal(vec_project(((vec2d){5.0, 5.0}), ((vec2d){1.0, 0.0})),
                             ((vec2d){5.0, 0.0}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(vec_project(((vec3f){1.0f, 1.0f, 1.0f}), ((vec3f){0.0f, 1.0f, 0.0f})),
                             ((vec3f){0.0f, 1.0f, 0.0f}), CG_fEPSILON));
}

UTEST(test, vec_slide) {
    ASSERT_TRUE(nearly_equal(vec_slide(((vec2d){1.0, 1.0}), ((vec2d){0.0, 1.0})),
                             ((vec2d){1.0, 0.0}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(vec_slide(((vec3f){1.0f, -1.0f, 0.0f}), ((vec3f){0.0f, 1.0f, 0.0f})),
                             ((vec3f){1.0f, 0.0f, 0.0f}), CG_fEPSILON));
}

UTEST(test, vec_reflect) {
    ASSERT_TRUE(nearly_equal(vec_reflect(((vec2d){1.0, -1.0}), ((vec2d){0.0, 1.0})),
                             ((vec2d){1.0, 1.0}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(vec_reflect(((vec3f){0.0f, -5.0f, 0.0f}), ((vec3f){0.0f, 1.0f, 0.0f})),
                             ((vec3f){0.0f, 5.0f, 0.0f}), CG_fEPSILON));

    ASSERT_TRUE(nearly_equal(vec_reflect(((vec4d){1.0, 1.0, 1.0, 0.0}), ((vec4d){-1.0, 0.0, 0.0, 0.0})),
                             ((vec4d){-1.0, 1.0, 1.0, 0.0}), CG_dEPSILON));
}

UTEST(test, lerp) {

    ASSERT_TRUE(nearly_equal(lerp(((vec2d){0.0, 0.0}), ((vec2d){10.0, 10.0}), 0.5),
                             ((vec2d){5.0, 5.0}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(lerp(((vec3f){1.0f, 2.0f, 3.0f}), ((vec3f){2.0f, 4.0f, 6.0f}), 0.1f),
                             ((vec3f){1.1f, 2.2f, 3.3f}), CG_fEPSILON));

    ASSERT_TRUE(nearly_equal(lerp(((vec4d){0.0, 0.0, 0.0, 0.0}), ((vec4d){1.0, 1.0, 1.0, 1.0}), 1.0),
                             ((vec4d){1.0, 1.0, 1.0, 1.0}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(lerp(((quatf){0.0f, 0.0f, 0.0f, 1.0f}), ((quatf){0.0f, 0.0f, 0.0f, 0.0f}), 0.5f),
                             ((quatf){0.0f, 0.0f, 0.0f, 0.5f}), CG_fEPSILON));

    ASSERT_TRUE(nearly_equal(lerp(((quatd){1.0, 0.0, 0.0, 0.0}), ((quatd){0.0, 2.0, 4.0, 6.0}), 0.25),
                             ((quatd){0.75, 0.5, 1.0, 1.5}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(lerp( ((mat3f){
                                     .m11 = 0.0f, .m12 = 0.0f, .m13 = 0.0f,
                                     .m21 = 0.0f, .m22 = 0.0f, .m23 = 0.0f,
                                     .m31 = 0.0f, .m32 = 0.0f, .m33 = 0.0f}),
                                    ((mat3f){
                                     .m11 = 2.0f, .m12 = 2.0f, .m13 = 2.0f,
                                     .m21 = 2.0f, .m22 = 2.0f, .m23 = 2.0f,
                                     .m31 = 2.0f, .m32 = 2.0f, .m33 = 2.0f}), 0.5f),
                                    ((mat3f){
                                     .m11 = 1.0f, .m12 = 1.0f, .m13 = 1.0f,
                                     .m21 = 1.0f, .m22 = 1.0f, .m23 = 1.0f,
                                     .m31 = 1.0f, .m32 = 1.0f, .m33 = 1.0f}), CG_fEPSILON));

    ASSERT_TRUE(nearly_equal(lerp( ((mat3d){
                                     .m11 = 1.0, .m12 = 0.0, .m13 = 0.0,
                                     .m21 = 0.0, .m22 = 1.0, .m23 = 0.0,
                                     .m31 = 0.0, .m32 = 0.0, .m33 = 1.0}),
                                    ((mat3d){
                                     .m11 = 3.0, .m12 = 0.0, .m13 = 0.0,
                                     .m21 = 0.0, .m22 = 3.0, .m23 = 0.0,
                                     .m31 = 0.0, .m32 = 0.0, .m33 = 3.0}), 0.5),
                                    ((mat3d){
                                     .m11 = 2.0, .m12 = 0.0, .m13 = 0.0,
                                     .m21 = 0.0, .m22 = 2.0, .m23 = 0.0,
                                     .m31 = 0.0, .m32 = 0.0, .m33 = 2.0}), CG_dEPSILON));
}

UTEST(test, vec2f_from_angle) {
    ASSERT_TRUE(nearly_equal(vec2f_from_angle(0.0f),
                             ((vec2f){1.0f, 0.0f}), CG_fEPSILON));

    ASSERT_TRUE(nearly_equal(vec2d_from_angle(CG_dPI_2),
                             ((vec2d){0.0f, 1.0f}), CG_dEPSILON));
}

UTEST(test, vec2_rotate) {
    ASSERT_TRUE(nearly_equal(vec2_rotate(((vec2f){1.0f, 0.0f}), CG_fPI_2),
                             ((vec2f){0.0f, 1.0f}), CG_fEPSILON));

    ASSERT_TRUE(nearly_equal(vec2_rotate(((vec2d){0.0, 1.0}), CG_dPI_2),
                             ((vec2d){-1.0, 0.0}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(vec2_rotate(((vec2f){1.0f, 1.0f}), CG_fPI),
                             ((vec2f){-1.0f, -1.0f}), CG_fEPSILON));

    ASSERT_TRUE(nearly_equal(vec2_rotate(((vec2d){1.0, 0.0}), CG_dPI_4),
                             ((vec2d){0.7071067811865476, 0.7071067811865476}), CG_dEPSILON));
}

UTEST(test, vec3_rotate) {
    ASSERT_TRUE(nearly_equal(vec3_rotate(((vec3f){1.0f, 0.0f, 0.0f}), ((vec3f){0.0f, 0.0f, 1.0f}), CG_fPI_2),
                             ((vec3f){0.0f, 1.0f, 0.0f}), CG_fEPSILON));

    ASSERT_TRUE(nearly_equal(vec3_rotate(((vec3d){0.0, 1.0, 0.0}), ((vec3d){1.0, 0.0, 0.0}), CG_dPI_2),
                             ((vec3d){0.0, 0.0, 1.0}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(vec3_rotate(((vec3f){0.0f, 0.0f, 1.0f}), ((vec3f){0.0f, 1.0f, 0.0f}), CG_fPI),
                             ((vec3f){0.0f, 0.0f, -1.0f}), CG_fEPSILON));

    ASSERT_TRUE(nearly_equal(vec3_rotate(((vec3d){1.0, 0.0, 0.0}), ((vec3d){0.0, 1.0, 0.0}), -CG_dPI_2),
                             ((vec3d){0.0, 0.0, 1.0}), CG_dEPSILON));
}

UTEST(test, bezier3) {
    ASSERT_TRUE(nearly_equal(bezier3(((vec2d){0.0, 0.0}), ((vec2d){5.0, 10.0}), ((vec2d){10.0, 0.0}), 0.0),
                             ((vec2d){0.0, 0.0}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(bezier3(((vec2d){0.0, 0.0}), ((vec2d){5.0, 10.0}), ((vec2d){10.0, 0.0}), 0.5),
                             ((vec2d){5.0, 5.0}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(bezier3(((vec2d){0.0, 0.0}), ((vec2d){5.0, 10.0}), ((vec2d){10.0, 0.0}), 1.0),
                             ((vec2d){10.0, 0.0}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(bezier3(((vec3f){0.0f, 0.0f, 0.0f}), ((vec3f){0.0f, 2.0f, 0.0f}), ((vec3f){0.0f, 0.0f, 2.0f}), 0.5f),
                             ((vec3f){0.0f, 1.0f, 0.5f}), CG_fEPSILON));
}

UTEST(test, bezier4) {
    ASSERT_TRUE(nearly_equal(bezier4(((vec2d){0.0, 0.0}), ((vec2d){0.0, 10.0}), ((vec2d){10.0, 10.0}), ((vec2d){10.0, 0.0}), 0.0),
                             ((vec2d){0.0, 0.0}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(bezier4(((vec2d){0.0, 0.0}), ((vec2d){0.0, 10.0}), ((vec2d){10.0, 10.0}), ((vec2d){10.0, 0.0}), 0.5),
                             ((vec2d){5.0, 7.5}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(bezier4(((vec2d){0.0, 0.0}), ((vec2d){0.0, 10.0}), ((vec2d){10.0, 10.0}), ((vec2d){10.0, 0.0}), 1.0),
                             ((vec2d){10.0, 0.0}), CG_dEPSILON));

    ASSERT_TRUE(nearly_equal(bezier4(((vec3f){0.0f, 0.0f, 0.0f}), ((vec3f){1.0f, 1.0f, 1.0f}), ((vec3f){2.0f, 1.0f, 1.0f}), ((vec3f){3.0f, 0.0f, 0.0f}), 0.5f),
                             ((vec3f){1.5f, 0.75f, 0.75f}), CG_fEPSILON));
}

UTEST(test, line2d_intersection) {
    line2d l1 = { .point = {0.0, 0.0}, .direction = {1.0, 1.0} };
    line2d l2 = { .point = {0.0, 10.0}, .direction = {1.0, -1.0} };

    vec2d result = line2d_intersection(l1, l2);
    ASSERT_TRUE(nearly_equal(result, ((vec2d){5.0, 5.0}), CG_dEPSILON));

    line2d l3 = { .point = {0.0, 0.0}, .direction = {1.0, 0.0} };
    line2d l4 = { .point = {0.5, -1.0}, .direction = {0.0, 1.0} };

    vec2d result2 = line2d_intersection(l3, l4);
    ASSERT_TRUE(nearly_equal(result2, ((vec2d){0.5, 0.0}), CG_dEPSILON));

    line2d l5 = { .point = {1.0, 2.0}, .direction = {1.0, 0.0} };
    line2d l6 = { .point = {3.0, 0.0}, .direction = {0.0, 1.0} };

    vec2d result3 = line2d_intersection(l5, l6);
    ASSERT_TRUE(nearly_equal(result3, ((vec2d){3.0, 2.0}), CG_dEPSILON));
}

UTEST(test, vec2_linear_independent) {
    ASSERT_TRUE(vec2_linear_independent(((vec2d){1.0, 0.0}), ((vec2d){0.0, 1.0})));

    ASSERT_FALSE(vec2_linear_independent(((vec2f){1.0f, 2.0f}), ((vec2f){2.0f, 4.0f})));

    ASSERT_FALSE(vec2_linear_independent(((vec2d){1.0, 1.0}), ((vec2d){-1.0, -1.0})));

    ASSERT_FALSE(vec2_linear_independent(((vec2d){0.0, 0.0}), ((vec2d){1.0, 1.0})));
}

UTEST(test, vec3_linear_independent) {
    ASSERT_TRUE(vec3_linear_independent(((vec3f){1.0f, 0.0f, 0.0f}),
                                        ((vec3f){0.0f, 1.0f, 0.0f}),
                                        ((vec3f){0.0f, 0.0f, 1.0f})));

    ASSERT_FALSE(vec3_linear_independent(((vec3d){1.0, 0.0, 0.0}),
                                         ((vec3d){0.0, 1.0, 0.0}),
                                         ((vec3d){1.0, 1.0, 0.0})));

    ASSERT_FALSE(vec3_linear_independent(((vec3f){1.0f, 2.0f, 3.0f}),
                                         ((vec3f){2.0f, 4.0f, 6.0f}),
                                         ((vec3f){0.0f, 0.0f, 1.0f})));

    ASSERT_FALSE(vec3_linear_independent(((vec3d){0.0, 0.0, 0.0}),
                                         ((vec3d){1.0, 5.0, 2.0}),
                                         ((vec3d){3.0, 1.0, 4.0})));
}

UTEST(test, quat_conjugate) {
    ASSERT_TRUE(equal(quat_conjugate(((quatf){1.0f, 2.0f, 3.0f, 4.0f})),
                      ((quatf){-1.0f, -2.0f, -3.0f, 4.0f})));

    ASSERT_TRUE(equal(quat_conjugate(((quatd){-0.5, 0.5, -0.5, 1.0})),
                      ((quatd){0.5, -0.5, 0.5, 1.0})));

    ASSERT_TRUE(nearly_equal(quat_conjugate(((quatf){0.0f, 0.0f, 0.0f, 1.0f})),
                      ((quatf){0.0f, 0.0f, 0.0f, 1.0f}), CG_fEPSILON));
}

UTEST(test, quatf_inverse) {
    ASSERT_TRUE(nearly_equal(quatf_inverse(((quatf){0.0f, 0.0f, 0.0f, 1.0f})),
                             ((quatf){0.0f, 0.0f, 0.0f, 1.0f}), CG_fEPSILON));

    ASSERT_TRUE(nearly_equal(quatf_inverse(((quatf){1.0f, 0.0f, 0.0f, 1.0f})),
                             ((quatf){-0.5f, 0.0f, 0.0f, 0.5f}), CG_fEPSILON));

    quatf q = {1.0f, 2.0f, 3.0f, 4.0f};
    quatf inv = quatf_inverse(q);
    float sq_norm = 1.0f*1.0f + 2.0f*2.0f + 3.0f*3.0f + 4.0f*4.0f;
    ASSERT_NEAR(inv.x, -1.0f / sq_norm, CG_fEPSILON);
    ASSERT_NEAR(inv.y, -2.0f / sq_norm, CG_fEPSILON);
    ASSERT_NEAR(inv.z, -3.0f / sq_norm, CG_fEPSILON);
    ASSERT_NEAR(inv.w,  4.0f / sq_norm, CG_fEPSILON);
}

UTEST(test, mat2f_inverse) {
    mat2f m = {
        .m11 = 4.0f, .m21 = 7.0f,
        .m12 = 2.0f, .m22 = 6.0f
    };
    mat2f expected = {
        .m11 = 0.6f,  .m21 = -0.7f,
        .m12 = -0.2f, .m22 = 0.4f
    };
    ASSERT_TRUE(nearly_equal(inverse(m), expected, CG_fEPSILON));

    mat2f identity = {
        .m11 = 1.0f, .m21 = 0.0f,
        .m12 = 0.0f, .m22 = 1.0f
    };
    ASSERT_TRUE(nearly_equal(inverse(identity), identity, CG_fEPSILON));
}

UTEST(test, mat3d_inverse) {
    mat3d m = {
        .m11 = 1.0, .m21 = 0.0, .m31 = 1.0,
        .m12 = 0.0, .m22 = 2.0, .m32 = 1.0,
        .m13 = 0.0, .m23 = 0.0, .m33 = 2.5
    };

    mat3d expected = {
        .m11 = 1.0,  .m21 = 0.0,  .m31 = -0.4,
        .m12 = 0.0,  .m22 = 0.5,  .m32 = -0.2,
        .m13 = 0.0,  .m23 = 0.0,  .m33 = 0.4
    };

    mat3d result = mat3d_inverse(m);
    ASSERT_TRUE(nearly_equal(result, expected, CG_dEPSILON));

    mat3d singular = {
        .m11 = 1.0, .m21 = 2.0, .m31 = 3.0,
        .m12 = 1.0, .m22 = 2.0, .m32 = 3.0,
        .m13 = 0.0, .m23 = 0.0, .m33 = 0.0
    };
    mat3d zero_res = mat3d_inverse(singular);
    ASSERT_EQ(zero_res.m11, 0.0);
}

UTEST_MAIN();