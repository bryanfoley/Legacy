/*
 * set_free_mass.h
 *
 *  Created on: May 23, 2013
 *      Author: bfoley
 */

#ifndef SET_FREE_MASS_H_
#define SET_FREE_MASS_H_

void set_free_mass(double free_particle[n_max][m_max][z_max], double rad)
{
     int i,j;
#ifdef TRACE_ON
     char func_name[15] = "set_free_mass";
     char action_begin[10] = ">>>";
     char action_end[10] = "<<<";
     time_stamp();
     trace(func_name,action_begin);
#endif

     for(i = 0; i < n_max; i++)
      {
       for(j = 0; j < z_max; j++)
        {
         free_particle[i][8][0] = (free_particle[i][9][0])/0.5;
        }
      }

#ifdef TRACE_ON
     time_stamp();
     trace(func_name,action_end);
#endif
}

#endif /* SET_FREE_MASS_H_ */
