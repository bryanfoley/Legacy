/*
 * set_static_radii.h
 *
 *  Created on: May 23, 2013
 *      Author: bfoley
 */

#ifndef SET_STATIC_RADII_H_
#define SET_STATIC_RADII_H_

#include"../incl/errorCodes.h"

ERR_MSG set_static_radii(double wall_particle[44][m_max][z_max], double rad)
{
     ERR_MSG r = ERR_OK;
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
#ifdef TRACE_ON
     time_stamp();
     trace(func_name,action_end);
#endif

     return r;
}

#endif /* SET_STATIC_RADII_H_ */
