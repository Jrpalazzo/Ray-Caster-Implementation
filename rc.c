#include "rc.h"
#include "vec.h"
#include "rc.h"
#include "stdlib.h"
#include "stdio.h"
#include <math.h>
/*
  @authors: Tim Davis, Joseph Palazzo
  CS304
  
  Ray Caster Program:
  Uses a ppm file header to produce an image size that is 1000 by 1000.
  A sphere's center x, y, and z coordinates are inputed, along with the radius and RGB values.
  This information is stored in an OBJ_T type, the cast method then stores a color 
  type that has RGB values that are printed at a certain coordinate on the screen, determined by 
  the intersect_sphere method.


*/

void read_objs(OBJ_T **list);

void read_objs (OBJ_T **list)
{
 double ctr_x, ctr_y, ctr_z;
 double col_r, col_g, col_b;
 double rad;
 
 OBJ_T *obj;
 
 *list = NULL;
 
 //Reads in center x, y, z, radius, and RBG values. Stores them in a obj pointer.
 while (scanf("%lf %lf %lf %lf %lf %lf %lf", &ctr_x, &ctr_y, &ctr_z, &rad, &col_r, &col_g, &col_b) == 7) {
	 
	 obj = (OBJ_T*)(malloc(sizeof(OBJ_T)));
	 
	 obj -> sphere.center.x = ctr_x;
	 obj -> sphere.center.y = ctr_y;
	 obj -> sphere.center.z = ctr_z;
	 
	 obj -> sphere.radius = rad;
	 
	 obj -> color.R = col_r;
	 obj -> color.G = col_g;
	 obj -> color.B = col_b;
	 
	 
	 obj -> next = *list;
	 
	 *list = obj;
 }

} 

//Determines where on the screen a ray will be, if it intersects return 1 otherwise it returns 0.
int intersect_sphere (RAY_T ray, SPHERE_T sphere, double *t) 
{
  VEC_T direction = ray.direction;
  VEC_T origin = ray.origin;
  VEC_T center = sphere.center;
  
  double A,B,C, discrim, t1, t2;
  A = 1.0;
  B = 2*((direction.x * ( origin.x - center.x)) + (direction.y * (origin.y - center.y)) + (direction.z * (origin.z - center.z)));
  C = pow((origin.x - center.x),2) + pow((origin.y - center.y),2) + pow((origin.z - center.z),2) - pow(sphere.radius, 2);
  discrim =   (pow(B, 2) - (4 * C));
  
  if(discrim <= 0)
  {
	 return 0; 
	  
  }
  
  t1 = ((-B) + sqrt(discrim)) / 2;
  t2 = ((-B) - sqrt(discrim)) / 2;
  
	if(t1 <= 0 && t2 > 0)
	{
      *t = t2;
	  
	  return 1;
		
	}
	
	if(t1 > 0 && t2 <= 0)
	{
	  *t = t1;
	  
	  return 1;
	
	}
	
	if(t1 > 0 && t2 > 0)
	{
	  if (t1 < t2){
	  *t = t1;
	  
	  return 1;
	  }
	  else 
	  {
	   *t = t2;
	 
	   return 1;
		
	}
	
	if (t1 <= 0 && t2 <= 0) {
        return 0;
    }
  
	
	}
	

}

//Checks if a ray intersects a sphere changes that sphere to the 
//appropriate color.
COLOR_T cast (RAY_T ray, OBJ_T *list) 
{
 COLOR_T ret_color;
 
 ret_color.R = 1.0;
 ret_color.G = 1.0;
 ret_color.B = 1.0;
 
 double t, closest_t;
 closest_t = 2500.0;
 OBJ_T *curr;
 
 for(curr = list; curr != NULL; curr = curr->next)
 {
	if(intersect_sphere(ray, curr->sphere, &t))
	{
	  if( t < closest_t)
	  {
		ret_color = curr->color;
        closest_t = t;		
	  }
		
	}
	 
	 
 }

 return ret_color;
}

int main(void)
{

 OBJ_T *list;
 read_objs(&list);

 printf("P6\n");
 printf("1000 1000\n");
 printf("255\n");
 
 double screen_x, screen_y;
 double z = 1;
 
 //Cycles though each pixel on the screen and calls each method
 //to determine if a sphere is present. RBG values are then output
 //to the ppm file.
 for(screen_y = 0; screen_y < 1000; screen_y++){
	 for(screen_x =0; screen_x < 1000; screen_x++){
		
		double x = -0.5 + (screen_x / 1000.0);
        double y = 0.5 - (screen_y / 1000.0);
		
		VEC_T loc;
        loc.x = x;
        loc.y = y;
        loc.z = z;
        loc = normalize(loc);

        RAY_T ray;
        VEC_T zero_vector;
        zero_vector.x = 0;
        zero_vector.y = 0;
        zero_vector.z = 0;
        ray.origin = zero_vector;
        ray.direction = loc;
	
        COLOR_T color = cast (ray, list);
		
        printf("%c%c%c", (unsigned char)(color.R * 255), (unsigned char)(color.G * 255), (unsigned char)(color.B * 255));		
	
	
	 }
		 
 }
 
    OBJ_T *header;
    while (list != NULL) {
        header = list;
        list = list->next;
        free(header);
    }

 return 0;
}