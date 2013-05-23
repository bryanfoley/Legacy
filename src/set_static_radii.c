/*
 * set_static_radii.c
 *
 *  Created on: May 23, 2013
 *      Author: bfoley
 */
#include"intf/set_static_radii.h"
{
     int i,j;
#ifdef TRACE_ON
     char func_name[20] = "set_static_radii";
     char action_begin[10] = ">>>";
     char action_end[10] = "<<<";
     time_stamp();
     trace(func_name,action_begin);
#endif
     for(i = 0; i < 44; i++)
      {
       for(j = 0; j < z_max; j++)
        {
         wall_particle[i][9][j] = 0.5;
        }
      }

     time_stamp();
     trace(func_name,action_end);
}

