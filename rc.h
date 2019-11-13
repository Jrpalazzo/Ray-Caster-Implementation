#ifndef RC_H
#define RC_H

#include "vec.h"

/*
  @authors: Tim Davis, Joseph Palazzo
  CS304
*/

typedef struct{
  VEC_T origin;
  VEC_T direction; 

}RAY_T;

typedef struct
{
 VEC_T center;
 double radius;

}
SPHERE_T;

typedef struct
{
 double R;
 double G;
 double B;

}
COLOR_T;

typedef struct OBJ_T{
	
    SPHERE_T sphere;
	COLOR_T color;
	struct OBJ_T *next;
	
}OBJ_T;

void read_objs (OBJ_T **list); //reads spheres from stdin; creates linked list using dynamic memory 
 
int intersect_sphere (RAY_T ray, SPHERE_T sphere, double *t);
//computes intersection of ray and sphere; returns 1 if intersection, 0 otherwise; t is set to distance from camera to sphere intersection 
 
COLOR_T cast (RAY_T ray, OBJ_T *list);
//iterates through linked list; finds closest intersection using intersect_sphere; returns color of closest sphere 

#endif
 