#include "vec.h"
#include "math.h"

/*
  @authors: Tim Davis, Joseph Palazzo
  CS304
*/

//normalize the vectors by using vector normalization formula 
VEC_T normalize (VEC_T v)
{
 double length;
 length = sqrt((pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
 
 v.x = v.x/length;
 v.y = v.y/length;
 v.z = v.z/length;
 
 return v;
}