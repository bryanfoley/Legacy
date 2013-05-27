/*
 * files.h
 *
 *  Created on: May 27, 2013
 *      Author: bfoley
 */

#ifndef FILES_H_
#define FILES_H_

     /*Output Files*/
     FILE *fptr1;
     FILE *fptr2;
     FILE *fptr3;
     FILE *fptr4;
     FILE *fptr5;
     FILE *fptr6;
     FILE *fptr7;
     FILE *fptr8;
     FILE *fptr9;
     FILE *fptr10;
     FILE *fptr11;
     FILE *fptr12;

     /*Input Files*/
     FILE *in_fptr1;

     /*Open files to be written to*/
     printf("Opening the output files\n");
     fptr1 = fopen("results/positions.dat","w");
     fptr2 = fopen("results/velocities.dat","w");
     fptr3 = fopen("results/sys_props.dat","w");
     fptr4 = fopen("results/kinetic.dat","w");
     fptr5 = fopen("results/potential.dat","w");
     fptr6 = fopen("results/energy.dat","w");
     fptr8 = fopen("results/radii.dat","w");
     fptr9 = fopen("results/wall_positions.dat","w");
     fptr10 = fopen("results/image_positions.dat","w");
     fptr11 = fopen("results/coordination_number.dat","w");
     fptr12 = fopen("results/average_velocity.dat","w");
     fptr_trace = fopen("results/trace","w");

     /*Inputs from files*/
     in_fptr1 = fopen("config1.dat","r");

#endif /* FILES_H_ */
