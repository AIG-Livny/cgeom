#ifdef CGEOM_EXTENDED

#include "cgeom.h"
#include "iso646.h"
#include "c-vector/cvector.h"

/*
    WARNING: this functions are not finished
*/

line2d line2d_init_from_points_vec2d( vec2d v0, vec2d v1 ) {
    return (line2d){.point=v0, .direction=normalize(sub(v1,v0))};
}

void line_array2d_equidistant( cvector(vec2d)* output_points, cvector(vec2d) input_points, cgd_t distance ) {
    line2d l0;
    line2d l1;
    line2d* cur_line = NULL;
    line2d* prev_line = NULL;
    vec2d* prev_point = NULL;
    cvector_iterator(vec2d) cur_point;
    vec2d perpendicular;
    cvector_for_each_in(cur_point, input_points){
        if ( prev_point ){
            if(not cur_line){
                cur_line = &l0;
            }else{
                if(cur_line == &l0){
                    cur_line = &l1;
                }else{
                    cur_line = &l0;
                }
            }
            *cur_line = line2d_init_from_points_vec2d(*prev_point, *cur_point);
            perpendicular = vec2d_multiply_num(vec2d_tangent(cur_line->direction), distance);
            cur_line->point = vec2d_add(cur_line->point, perpendicular);

            if ( not *output_points ){
                cvector_push_back(*output_points, vec2d_add(*prev_point,perpendicular));
            }
        }

        if(prev_line){
            cvector_push_back(*output_points, line2d_intersection(*prev_line, *cur_line));
        }

        prev_point = cur_point;

        prev_line=cur_line;
    }
    cvector_push_back(*output_points, vec2d_add(*cvector_back(input_points), perpendicular) );
}

#define M_GEN_rect_extend struct rect3i* rect3i_extend(struct rect3i* result, mi_t f)
#ifdef M_GEN_rect_extend
#define M_GEN_IMPL_rect_extend \
M_GEN_rect_extend { \
    struct vec3i vct = {f,f,f}; \
    vec3i_subtract(result->min, vct); \
    vec3i_add(result->max, vct); \
    return result; \
}

M_GEN_IMPL_rect_extend;
#endif

#define M_GEN_triface_calc_norm(_char) struct triface3##_char* triface3##_char##_calc_norm(struct triface3##_char* t0)
#ifdef M_GEN_triface_calc_norm
#define M_GEN_IMPL_triface_calc_norm(_char) \
M_GEN_triface_calc_norm(_char) { \
    struct vec3##_char tmp_v1 = vec3##_char##_subtract(t0->p[0], t0->p[1]); \
    struct vec3##_char tmp_v2 = vec3##_char##_subtract(t0->p[1], t0->p[2]); \
    \
    t0->normal = VEC3_CAST(d,vec3##_char##_cross(tmp_v1, tmp_v2)); \
    return t0; \
}

M_GEN_IMPL_triface_calc_norm(i);
#endif

#define M_GEN_extremes_find struct extremes3i* extremes3i_find( struct extremes3i* result, cvector_vec3i points )
#ifdef M_GEN_extremes_find
M_GEN_extremes_find {
    *result = (struct extremes3i){.v = {points,points,points,points,points,points}};

    #define SET_MAX(axis) \
        if (it->axis > result->max_##axis->axis){ \
            result->max_##axis=it; \
        }
    #define SET_MIN(axis) \
        if (it->axis < result->min_##axis->axis){ \
            result->min_##axis=it; \
        }

    cvector_iterator(struct vec3i) it;
    cvector_for_each_in(it, points){
        SET_MIN(x);SET_MAX(x);
        SET_MIN(y);SET_MAX(y);
        SET_MIN(z);SET_MAX(z);
    }
    return result;
}

#endif

#define M_GEN_convex_hull_update void convex_hull3i_update( struct convex_hull3i* result, cvector_vec3i points, const struct extremes3i* extremes )
#ifdef M_GEN_convex_hull_update
struct convex_plane {
    struct triface3i triface;
    cvector(struct vec3i) outside_points;
};

// Calculating the horizon for an eye to make new faces
bool calc_horizon(
    cvector_vector_type(int) all_planes,
    cvector_vector_type(int) visited_planes,
    int current_plane,
    struct vec3i* eye_point,
    cvector_vector_type(struct segment3i) segments,
    cvector_vector_type(struct convex_plane) plane_storage
    )
{
    cvector_iterator(int) plane;
    double dist =  triface3i_distance_vec3i( plane_storage[current_plane].triface, *eye_point);

    if( dist > 0){
        cvector_push_back(visited_planes, current_plane);
        for(int i = 0; i < 3; i++){

            // Edge
            struct vec3i* e1 = &plane_storage[current_plane].triface.p[i];
            struct vec3i* e2;
            if (i < 2){e2 = &plane_storage[current_plane].triface.p[i+1];}else{e2 = &plane_storage[current_plane].triface.p[0];}

            // Finding adjacent planes to an edge
            int adjacent = -1;
            cvector_for_each_in(plane, all_planes){
                if (*plane == current_plane){
                    continue;
                }

                bool e1_found = false;
                bool e2_found = false;
                for(int i = 0; i < 3; i++){
                    if(not e1_found)
                    if(memcmp(e1,&plane_storage[*plane].triface.p[i],sizeof(struct vec3i)) == 0){
                        e1_found = true;

                    }
                    if(not e2_found)
                    if(memcmp(e2,&plane_storage[*plane].triface.p[i],sizeof(struct vec3i)) == 0){
                        e2_found = true;
                    }
                }

                if (e1_found and e2_found){
                    adjacent = *plane;
                    break;
                }
            }

            if(adjacent == -1){
                continue;
            }

            // If not adjacent in visited_planes
            cvector_iterator(int) it_vp;
            cvector_for_each_in(it_vp, visited_planes){
                if(adjacent == *it_vp){
                    break;
                }
            }
            if(it_vp == cvector_end(visited_planes)){
                bool result = calc_horizon(all_planes, visited_planes, adjacent, eye_point, segments, plane_storage);
                if (result){
                    cvector_push_back(segments, ((struct segment3i){.start=*e1, .end=*e2}) );
                }
            }
        }
        return false;
    }else{
        return true;
    }
}

M_GEN_convex_hull_update {
    // Delete old data
    cvector_free(result->tris);
    result->tris = NULL;

    // If no extremes then find them
    struct extremes3i tmp_extremes;
    struct extremes3i* pextremes = (struct extremes3i*)extremes;

    if ( not extremes ) {
        pextremes = &tmp_extremes;
        extremes3i_find(pextremes, points);
    }

    // Check if we have 3d structure
    if(pextremes->min_x == pextremes->max_x){return;}
    if(pextremes->min_y == pextremes->max_y){return;}
    if(pextremes->min_z == pextremes->max_z){return;}

    // From the extreme points calculate the 2 most distant points
    double max_dist = 0;
    const struct vec3i* start_points[4];
    for(int i = 0; i < 3*2; i++){
        for(int j = i+1; j < 3*2; j++){
            double dist = vec3i_distance_squared_vec3i(pextremes->v[i],pextremes->v[j]);
            if(dist > max_dist){
                max_dist = dist;
                start_points[0] = pextremes->v[i];
                start_points[1] = pextremes->v[j];
            }
        }
    }

    if (max_dist == 0){
        return;
    }

    // Let's find third point
    // Most distant from line
    max_dist = 0;
    cvector_iterator(struct vec3i) point;
    cvector_for_each_in(point, (cvector_vector_type(struct vec3i))points){
        if( (start_points[0] == point) or (start_points[1] == point) ){
            continue;
        }

        struct vec3i dir = vec3i_subtract(*start_points[1], *start_points[0]);
        error_code = 0;
        errorcb_t old_callback = error_callback;
        error_callback = NULL;
        double dist = line3i_distance_squared_vec3i((struct line3i){.direction = VEC3_CAST(d,dir), .point=*start_points[0]}, *point);
        error_callback = old_callback;

        if(error_code){continue;}
        if ( fabs(dist) > max_dist ){
            max_dist = dist;
            start_points[2] = point;
        }
    }

    // Make first plane
    cvector_vector_type(struct convex_plane) plane_storage = NULL;
    cvector_reserve(plane_storage, 40);

    cvector_push_back(plane_storage,
        ((struct convex_plane){
            .triface=(struct triface3i){.p={*start_points[0],*start_points[1],*start_points[2]}},
            .outside_points = NULL,
        }));
    cvector_init(cvector_back(plane_storage)->outside_points, 20, NULL);
    struct convex_plane* cp = cvector_back(plane_storage);
    triface3i_calc_norm(&cp->triface);

    // Fourth point
    max_dist = 0;
    cvector_for_each_in(point, (cvector_vector_type(struct vec3i))points){
        double dist = triface3i_distance_vec3i(cp->triface, *point);
        if ( fabs(dist) > max_dist ){
            max_dist = dist;
            start_points[3] = point;
        }
    }

    // Other 3 planes
    cvector_push_back(plane_storage,
        ((struct convex_plane){
            .triface=(struct triface3i){.p={*start_points[0],*start_points[1],*start_points[3]}},
            .outside_points = NULL,
        }));
    cvector_init(cvector_back(plane_storage)->outside_points, 20, NULL);
    triface3i_calc_norm(&cvector_back(plane_storage)->triface);

    cvector_push_back(plane_storage,
        ((struct convex_plane){
            .triface=(struct triface3i){.p={*start_points[0],*start_points[3],*start_points[2]}},
            .outside_points = NULL,
        }));
    cvector_init(cvector_back(plane_storage)->outside_points, 20, NULL);
    triface3i_calc_norm(&cvector_back(plane_storage)->triface);

    cvector_push_back(plane_storage,
        ((struct convex_plane){
            .triface=(struct triface3i){.p={*start_points[1],*start_points[2],*start_points[3]}},
            .outside_points = NULL,
        }));
    cvector_init(cvector_back(plane_storage)->outside_points, 20, NULL);
    triface3i_calc_norm(&cvector_back(plane_storage)->triface);


    cvector_iterator(struct convex_plane) stored_plane;
    cvector_for_each_in(stored_plane, plane_storage){
        // Correct normals
        for (int pi = 0; pi < 4; pi++){
            struct vec3i tmp_v = vec3i_subtract(*start_points[pi], stored_plane->triface.p[0]);
            struct vec3d tmp_vf = {.x=tmp_v.x, .y=tmp_v.y, .z=tmp_v.z};
            double dist = vec3d_dot(stored_plane->triface.normal, tmp_vf);
            if(dist > 0){
                stored_plane->triface.normal = vec3d_multiply_num(stored_plane->triface.normal, -1);
            }
        }

        // Find all outside points
        cvector_for_each_in(point, (cvector_vector_type(struct vec3i))points){
            double dist = triface3i_distance_vec3i(stored_plane->triface, *point);

            if (dist > 0){
                cvector_push_back(stored_plane->outside_points,*point);
            }
        }
    }

    cvector_vector_type(int) visited_planes         = NULL;
    cvector_vector_type(int) planes                 = NULL;
    cvector_vector_type(struct segment3i) segments  = NULL;

    cvector_reserve(visited_planes, 40);
    cvector_reserve(planes, 40);
    cvector_reserve(segments, 40);

    cvector_iterator(struct segment3i) segment;
    cvector_iterator(int) visited_plane;
    cvector_iterator(int) plane;
    cvector_iterator(int) plane2;

    // Add all plane indicies to vector
    cvector_for_each_in(stored_plane, plane_storage){
        cvector_push_back(planes, stored_plane - plane_storage);
    }

    bool any_left = true;
    while (any_left){
        any_left = false;
        cvector_for_each_in(plane, planes){
            if(cvector_size(plane_storage[*plane].outside_points)){
                any_left = true;

                // Calculate the eye point of the face
                struct vec3i eye_point;
                max_dist = 0;
                cvector_for_each_in(point, plane_storage[*plane].outside_points){
                    double dist = triface3i_distance_vec3i(plane_storage[*plane].triface, *point);
                    if(dist > max_dist){
                        max_dist = dist;
                        eye_point = *point;
                    }
                }

                calc_horizon(planes, visited_planes, *plane, &eye_point, segments, plane_storage);

                // Delete all visited indicies from planes
                cvector_for_each_in(visited_plane, visited_planes){
                    cvector_for_each_in(plane2, planes){
                        if(*plane2 == *visited_plane){
                            cvector_erase(planes,plane2-planes);
                            break;
                        }
                    }
                }

                cvector_for_each_in(segment, segments){
                    cvector_push_back(plane_storage, ((struct convex_plane){
                        .triface={.p={
                                segment->start,
                                segment->end,
                                eye_point
                            }
                        },
                        .outside_points = NULL
                    }));

                    struct convex_plane* new_plane;
                    new_plane = cvector_back(plane_storage);
                    cvector_push_back(planes, cvector_size(plane_storage)-1);

                    triface3i_calc_norm(&new_plane->triface);

                    // Correct normal new plane
                    for (int pi = 0; pi < 4; pi++){
                        struct vec3i tmp_v = vec3i_subtract(*start_points[pi], new_plane->triface.p[0]);
                        struct vec3d tmp_vf = {.x=tmp_v.x, .y=tmp_v.y, .z=tmp_v.z};
                        double dist = vec3d_dot(new_plane->triface.normal, tmp_vf);
                        if(dist > 0){
                            new_plane->triface.normal = vec3d_multiply_num(new_plane->triface.normal, -1);
                        }
                    }

                    // Find all outside points for new plane
                    cvector_for_each_in(visited_plane, visited_planes){
                        cvector_for_each_in(point, plane_storage[*visited_plane].outside_points){
                            double dist = triface3i_distance_vec3i(new_plane->triface, *point);
                            if (dist > 0){
                                cvector_push_back(new_plane->outside_points,*point);
                            }
                        }
                    }
                }

                cvector_clear(visited_planes);
                cvector_clear(segments);
            }
        }
    }

    // Copy planes to convex hull
    cvector_iterator(struct triface3i) tris;
    cvector_init(result->tris, cvector_size(planes), NULL);
    cvector_for_each_in(plane, planes){
        cvector_push_back(result->tris, plane_storage[*plane].triface);
    }

    // Free data
    cvector_free(planes);
    cvector_free(visited_planes);
    cvector_free(segments);
    cvector_for_each_in(stored_plane, stored_plane){
        cvector_free(stored_plane->outside_points);
    }
    cvector_free(plane_storage);
}

#endif

#define M_GEN_vec_inside_convex_hull bool vec3i_inside_convex_hull3i(const struct convex_hull3i* c0, const struct vec3i* v0)
#ifdef M_GEN_vec_inside_convex_hull
M_GEN_vec_inside_convex_hull {
    cvector_iterator(struct triface3i) it;
    cvector_for_each_in(it, c0->tris){
        double dist = triface3i_distance_vec3i(*it, *v0);
        if(dist > 0){
            return false;
        }
    }
    return true;
}

#endif

#endif // CGEOM_EXTENDED