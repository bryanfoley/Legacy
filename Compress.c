/*Non-Dimensionalised*/
/*Array Adressing*/
/*Determine the Coordination Number as a function of Packing Density*/
/*________________________________Header files________________________________*/
#include<float.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

  /*Open the tracing file*/
    FILE *fptr_trace;
#include"intf/trace.h"
#include"incl/defines.h"
/*----------------------------------------------------------------------------*/
/*----------------------------------Schemata----------------------------------*/
/*free_particle[n][m][z] wall_particle[n][m][z]                               */
/*image_free_particle[n][m][z]                                                */
/*m |                                                                         */
/*0 |Velocity in the x-direction                                              */
/*1 |Velocity in the y-direction                                              */
/*2 |x-position                                                               */
/*3 |y-position                                                               */
/*4 |Acceleration in the x-direction                                          */
/*5 |Acceleration in the y-direction                                          */
/*6 |Force in the x-direction                                                 */
/*7 |Force in the y-direction                                                 */
/*8 |Mass of free_particle                                                    */
/*9 |Radius of free_particle                                                  */
/*10|Coordination number                                                      */
/*11|Potential energy                                                         */
/*12|Initial momentum in the x-direction                                      */
/*13|Initial momentum in the y-direction                                      */
/*14|Final momentum in the x-direction                                        */
/*15|Final momentum in the y-direction                                        */
/*16|If the free_particle is out of bounds                                    */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*_______________________________Function headers_____________________________*/
/*_______________________________Main function________________________________*/
void main(void);
/*_________________________________Main body__________________________________*/
void main(void)
{
     double free_particle[n_max][m_max][z_max];
     /*This is the array which holds*/
     /*the properties of all of the */
     /*free_particles in the system */
     
     double image_free_particle[n_max][m_max][z_max];
     /*This is the array which holds*/
     /*the properties of all of the */
     /*images of the free_particles */
     /*in the system                */
     
     double wall_particle[44][m_max][z_max];
     /*This is the array which holds */
     /*the properties of all of the  */
     /*wall_particles in the system  */
     
     double free_forces[n_max][n_max][z_max];
     /*Contains values of forces  */
     /*between free_particle pairs*/
     
     double image_free_forces[n_max][n_max][z_max];
     /*Contains values of forces*/
     /*between free and image   */
     /*particle pairs           */
     
     double image_image_forces[n_max][n_max][z_max];
     /*Contains values of forces*/
     /*between image particle   */
     /*pairs                    */
     
     double wall_free_forces[n_max][44][z_max];
     /*Contains values of forces between*/
     /*wall and free particle pairs     */
     
     double wall_image_forces[n_max][44][z_max];
     /*Contains values of forces between*/
     /*wall and image particle pairs    */
     
     double x[n_max][n_max];
     /*Contains the overlap dist*/
     /*between free_particle pairs*/

     double image_x[n_max][n_max];
     /*Contains the overlap dist*/
     /*between free and image   */
     /*particle pairs           */

     double wall_x[n_max][44];
     /*Contains the overlap dist*/
     /*between wall and free    */
     /*particle pairs           */
     
     double image_image_x[n_max][n_max];
     /*Contains the overlap dist*/
     /*between two image        */
     /*particle pairs           */
     
     double wall_image_x[n_max][44];
     /*Contains the overlap dist*/
     /*between wall and image   */
     /*particle pairs           */
     
     double t = t_min;
     /*Timer for simulation*/
     
     /*Energy Variables*/
     double kinetic_energy,potential_energy,total_energy;
     
     /*Counters*/
     int i,k;
     int j = 0;
     int l = 0;
     
     /*Average Radius*/
     double rad;
     
     /*Packing density*/
     double packing;
     
     /*Average Coordiantion Number*/
     double coord_number;
     
     /*Average Velocity*/
     double average_vel_x;
     double average_vel_y;
     
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
     
#include"incl/includes.h"
/*____________________________________________________________________________*/     
/*_____________________________Execute the program____________________________*/
/*____________________________________________________________________________*/               
     /*Set the initial properties of the free_particles*/
     initiate(free_particle,image_free_particle,wall_particle,
              free_forces,image_free_forces,wall_free_forces,
              image_image_forces,wall_image_forces,x,image_x,
              wall_x,image_image_x,wall_image_x);
     printf("Initialising\n");
/*____________________________________________________________________________*/          
     /*Assign free particles radii randomly*/
     printf("Assigning");
     rad = set_free_radii(free_particle);
     fprintf(fptr3,"%lf\n",rad);
     printf("Setting free particle radii\n");
/*____________________________________________________________________________*/
     /*Assign free particles their ND mass*/
     set_free_mass(free_particle,rad);
     printf("Setting free particle masses\n");
/*____________________________________________________________________________*/
     /*Assign static particles the average radii*/
     set_static_radii(wall_particle,rad);
     printf("Setting static particle radii\n");
/*____________________________________________________________________________*/
     /*Assign image particles their radii*/
     for(i = 0; i < n_max; i++)
      {
       image_free_particle[i][9][0] = free_particle[i][9][0];
      }
/*____________________________________________________________________________*/          
     /*Assign static particles the average mass*/
     set_static_mass(wall_particle,rad);
     printf("Setting static particle mass\n");
     for(i = 0; i < 44; i++)
      {
           fprintf(fptr3,"%lf\t%lf\t",wall_particle[i][9][0],wall_particle[i][8][0]);
      }
      fprintf(fptr3,"\n");   
/*____________________________________________________________________________*/     
     /*Assign static particles positions*/
     set_static_positions(wall_particle,rad);
     printf("Setting static particle positions\n");
/*____________________________________________________________________________*/
     /*Assign free_particles random positions*/
     set_free_positions(free_particle);
     printf("Setting free particle positions\n");

/*____________________________________________________________________________*/
     /*Initiate Boundary Check on all free_particles*/
     bnd_check(free_particle,wall_particle);
     printf("Initiating boundary check\n");
/*____________________________________________________________________________*/
     /*Assign image_free_particles where necessary*/
     assign_image(free_particle,image_free_particle,wall_particle);
     printf("Assigning Images\n");         

/*____________________________________________________________________________*/     
     /*Print the free_particle masses to 'sys_props.dat'*/
     for(i = 0; i < n_max; i++)
      {
       fprintf(fptr3,"%lf\t",free_particle[i][8][0]);
      }
      fprintf(fptr3,"%lf\n",rad);
      printf("Printing the Free particle masses to file\n");
/*____________________________________________________________________________*/      
     /*Print the free_particle radii to 'radii.dat'*/
     for(i = 0; i < n_max; i++)
      {
       fprintf(fptr8,"%lf\n",free_particle[i][9][0]);
      }
      fprintf(fptr8,"\n");
      printf("Printing the Free particle radii to file\n");
/*____________________________________________________________________________*/                    
/*____________________________________________________________________________*/      
      calculate(free_particle,image_free_particle,wall_particle,free_forces,
                image_free_forces,wall_free_forces,image_image_forces,
                wall_image_forces,x,image_x,wall_x,image_image_x,wall_image_x);
      printf("Calculating\n");
      
      coord_number = coordination_number(free_particle);
      printf("\t %lf\n", coord_number);
      
      sum_forces(free_particle,image_free_particle,free_forces,image_free_forces,wall_free_forces,image_image_forces,wall_image_forces);
      printf("Summing\n");
/*____________________________________________________________________________*/          
/*____________________________________________________________________________*/           
/*____________________________________________________________________________*/          
/*____________________________________________________________________________*/          
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*____________________________________________________________________________*/
/*___________________________________Main Loop________________________________*/
     packing = packing_density(free_particle,wall_particle);
     printf("\t %lf\n", packing);
     #ifdef DEBUG_ON
     printf("\tLooping! It takes 3.5 minutes to boil a kettle and make some coffee.\n");
     printf("\t\tAnd another 15 minutes maximum to drink that coffee.\n");
     printf("\tYou should have made and drank approx 45.405 cups of coffee\n \t\t\tby the time this simulation finishes.\n");
     printf("\n\n\n\t\t\t\t\tGet brewin'.\n");
     #endif
     
     for(packing = min_packing; packing <= max_packing;)       /*BEGIN LOOP*/
      {            
       j = j+1;
       old_acc(free_particle,image_free_particle);               /*Calculate Accelerations*/
       new_pos(free_particle,wall_particle,image_free_particle); /*Calculate new positions*/
       bnd_check(free_particle,wall_particle);
       assign_image(free_particle,image_free_particle,wall_particle);
       calculate(free_particle,image_free_particle,wall_particle,free_forces,
       image_free_forces,wall_free_forces,image_image_forces,
       wall_image_forces,x,image_x,wall_x,image_image_x,wall_image_x);/*Calculate Force*/
       sum_forces(free_particle,image_free_particle,free_forces,image_free_forces,wall_free_forces,image_image_forces,wall_image_forces);/*Sum Forces on each free_particle*/
       new_acc(free_particle,image_free_particle);               /*Calculate the new Accelerations*/
       new_vel(free_particle,image_free_particle);               /*Calculate new Velocities*/
       kinetic_energy = kinetic(free_particle);    /*Calculate Kinetic Energies*/
       printf("\t %lf\n", kinetic_energy);
       if((kinetic_energy) <= max_energy)
        {
          packing = packing_density(free_particle,wall_particle);/*Calculate the packing density*/
          if((fmod((packing*factor),divisor)<=tolerance))
           {
            printf("Packing Density = %lf\n",packing);
            coord_number = coordination_number(free_particle);/*Coordination Number*/
            potential_energy = potential(x,image_x,wall_x);/*Calculate Potential Energy*/
            fprintf(fptr11,"%lf\t%lf\n",packing,coord_number);
            fprintf(fptr5,"%lf\t%lf\n",packing,potential_energy); /*Print Packing vs Potential Energy to file*/
            print(free_particle,packing); /*Print Particle positions for different Packing densities*/
           }
          translate_wall(wall_particle);     /*Move the top wall down*/ 
        }
/*____________________________________________________________________________*/                
       update(free_particle,image_free_particle);                  /*Update Pos, Vel, Acc*/  
       bnd_check(free_particle,wall_particle);
       assign_image(free_particle,image_free_particle,wall_particle);
      
      }                                       /*END LOOP*/  
      printf("End of loop\n");
/*____________________________________________________________________________*/          
/*____________________________________________________________________________*/          
     /*Print free_particle masses to file 'sys_props.dat'*/
      for(i = 0; i < n_max; i++)
      {
       fprintf(fptr3,"%lf\t",free_particle[i][8][0]);
      }
      fprintf(fptr3,"\n");

     #ifdef DEBUG_ON
     printf("Closing the files, the ouput files\n");
     #endif
     /*End the program*/
     fclose(fptr1);
     fclose(fptr2);
     fclose(fptr3);
     fclose(fptr4);
     fclose(fptr5);
     fclose(fptr6);
     fclose(fptr8);
     fclose(fptr9);
     fclose(fptr10);
     fclose(fptr11);
     fclose(fptr12);
     fclose(fptr_trace);
     #ifdef DEBUG_ON
     printf("All closed!\n");
     #endif

     #ifdef DEBUG_ON
     printf("Closing the last file, the input file!\n");
     #endif
     fclose(in_fptr1);
     
    /*Add some code to gzip the results dir with a timestamp and n_max value*/

}
