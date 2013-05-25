/*
 * BFOL.h
 *
 *  Created on: May 25, 2013
 *      Author: bfoley
 */

#ifndef BFOL_H_
#define BFOL_H_

//This is the return type from each function call
typedef string RTN_MSG;

//This is the type which represents an entire system of particles/grains/etc...
typedef struct CONGLOMERATE
{
  2D_PARTICLE[N_MAX]
}

//This is the basic 2D particle type
typedef struct 2D_PARTICLE
{
  double x,y;
  double v_x, v_y;
  double m,r,j;
  int particleType;
  double coordNumber;
}

//This is the basic 3D particle type
typedef struct 3D_PARTICLE
{
  
}
#endif /* BFOL_H_ */
