/*
 * BFOL.h
 *
 *  Created on: May 25, 2013
 *      Author: bfoley
 */

#ifndef BFOL_H_
#define BFOL_H_

/*
 * This is the typedef for real numbers
 */
typedef float REAL;

/*
 * This is the type which represents a 2 Dimensional Vector class
 */
typedef struct
{
	REAL x,y; //2D coordinates
	REAL ang;   //Angle
}_2VECTOR;

/*
 * This is the type which represents a 3 Dimensional Vector class
 */
typedef struct
{
	REAL x,y,z; //3D coordinates
	REAL ang;   //Angle
}_3VECTOR;

/*
 * This is the basic 2D particle type
 */
typedef struct
{
    //Public member variables
	_2VECTOR pos;  //Position vector
	_2VECTOR vel;  //Velocity vector
	_2VECTOR acc;  //Acceleration vector
	_2VECTOR force;//Force vector
	_2VECTOR momen;//Momentum vector
	REAL kineticEnergy; //Kinetic Energy of the particle
	REAL potentialEnergy; //Potential energy of the particle
	REAL m,r,j;  //Mass, Radius and angular momentum
	int particleType;  //Particle type number
	REAL coordNumber;  //Coordinate number of a particle

}TWO_D_PARTICLE;

/*
 * This is the basic 3D particle type
 */
typedef struct
{
    //Public member variables
	_3VECTOR pos;  //Position vector
	_3VECTOR vel;  //Velocity vector
	_3VECTOR acc;  //Acceleration vector
	_3VECTOR force;//Force vector
	_3VECTOR momen;//Momentun vector
	REAL kineticEnergy; //Kinetic Energy of the particle
	REAL potentialEnergy; //Potential energy of the particle

	REAL m,r,j;  //Mass, Radius and angular momentum
	int particleType;  //Particle type number
	REAL coordNumber;  //Coordinate number of a particle

}THREE_D_PARTICLE;

/*
 * This is the type which represents an entire system of particles/grains/etc...
 */
typedef struct
{
	TWO_D_PARTICLE system;
}CONGLOMERATE;
#endif /* BFOL_H_ */

/*
 * This is a vector specific operation
 */
ERR_MSG vectorFill(struct vector *arg)
{
	ERR_MSG r = ERR_OK;

	return r;
}
