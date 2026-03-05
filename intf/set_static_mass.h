/*
 * set_static_mass.h
 *
 *  Created on: May 23, 2013
 *      Author: bfoley
 */

#ifndef SET_STATIC_MASS_H_
#define SET_STATIC_MASS_H_

void set_static_mass(double wall_particle[44][m_max][z_max],double rad)
{
     int i,j;
#ifdef TRACE_ON
     char func_name[15] = "set_static_mass";
     char action_begin[10] = ">>>";
     char action_end[10] = "<<<";
     time_stamp();
     trace(func_name,action_begin);
#endif
     for(i = 0; i < 44; i++)
      {
       for(j = 0; j < z_max; j++)
        {
         wall_particle[i][8][j] = (wall_particle[i][9][j])/0.5;
        }
      }

#ifdef TRACE_ON
     time_stamp();
     trace(func_name,action_end);
#endif
}

#endif /* SET_STATIC_MASS_H_ */
