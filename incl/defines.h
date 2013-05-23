/*
 * defines.h
 *
 *  Created on: May 23, 2013
 *      Author: bfoley
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define TRACE_ON		/*Trace function calls to file*/
#undef TRACE_ON
#define DEBUG_ON		/*Switch on Debugging statements*/
/*#undef DEBUG_ON*/
#define wall_speed -(1e-3)      /*Speed that the compressing wall moves downwards with*/
#define wall_step 0.00001      	/*wall_step = wall_speed*dt*/
#ifdef DEBUG_ON
#define wall_step 0.001
#endif
#define dt 1e-3                 /*Time step*/
#ifdef DEBUG_ON
#define dt 1e-1
#endif
#define t_min 0.0               /*Start time of simulation*/
#define t_max 3000.0            /*End time of simulation*/
#ifdef DEBUG_ON
#define t_max 3.00
#endif
#define n_max 100               /*Max number of free_particles in the simulation*/
#ifdef DEBUG_ON
#define extern n_max 3
#endif
#define m_max 17                /*Max number of parameters per free_particle*/
#define z_max 2                 /*Max number of time phases*/
#define kn 1.0                  /*Spring Constant*/
#define PI 3.14159265           /*PI*/
#define gamma 1.0               /*Dissipation Constant*/
#define max_energy 1e-4         /*This is the maximum allowed value of the    */
                                /*total kinetic energy of all of the          */
                                /*free_particles required to translate the    */
                                /*wall downwards                              */
#ifdef DEBUG_ON
#define max_energy 1e-4
#endif
#define factor 100.0            /*This is the multiplication factor used when */
                                /*calculating the mod of packing/divisor      */
#define divisor 1.0             /*This is the divisor used when calculating   */
                                /*the mod of packing/divisor                  */
#define tolerance 1e-4          /*This is the maximum allowed value of the    */
                                /*fmod((packing_density*factor),divisor)      */
                                /*i.e, modulus of packing divided by 0.001,   */
                                /*required to print coordination_number and   */
                                /*potential to file as functions of packing   */
#define max_packing 0.96	/*This is the maximum 2D packing density of   */
				/*the simulation			      */
#ifdef DEBUG_ON
#define max_packing 0.40
#endif
#define min_packing 0.00	/*This is the minimum 2D packing density of   */
				/*the simulation			      */

#endif /* DEFINES_H_ */
