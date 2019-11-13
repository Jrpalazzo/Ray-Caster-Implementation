#ifndef VEC_H
#define VEC_H
 
/*
  @authors: Tim Davis, Joseph Palazzo
  CS304
*/

 typedef struct
 {
  double x;
  double y;
  double z;
 }
  VEC_T;
  
 VEC_T normalize (VEC_T v);
 
 #endif