/*
 * set_free_radii.h
 *
 *  Created on: May 23, 2013
 *      Author: bfoley
 */

#ifndef SET_FREE_RADII_H_
#define SET_FREE_RADII_H_

double set_free_radii(double free_particle[n_max][m_max][z_max])
{
     int i;
     double sigma = 0.1000000000000000;
     double mu = 0.5000000000000000;
     double u1, u2, v1, v2, s, temp1, temp2;
     double sumx = 0.0000000000000000;
     double sumxx = 0.0000000000000000;
     double mean;
     double std_dev;
#ifdef TRACE_ON
     char func_name[15] = "set_free_radii";
     char action_begin[10] = ">>>";
     char action_end[10] = "<<<";
     time_stamp();
     trace(func_name,action_begin);
#endif

     for (i=0; i < n_max; i += 2)
      {
       do
        {
         u1 = (double) rand()/RAND_MAX;
         u2 = (double) rand()/RAND_MAX;
         v1 = 2.0000000000000000*u1 - 1.0000000000000000;
         v2 = 2.0000000000000000*u2 - 1.0000000000000000;
         s = (v1*v1)+(v2*v2);
        }
       while (s>=1.0);

       temp1 = log(s);
       temp2 = sqrt(-2.0000000000000000*temp1/s);
       free_particle[i][9][0] = fabs((v1*temp2)*sigma + mu);
       free_particle[i+1][9][0] = fabs((v2*temp2)*sigma + mu);
      }

     for(i = 0; i < n_max; i++)
      {
       sumx += free_particle[i][9][0];
       sumxx += free_particle[i][9][0]*free_particle[i][9][0];
      }
     mean = sumx/n_max;
     std_dev = sqrt((sumxx - n_max * (mean * mean))/(n_max - 1));

#ifdef TRACE_ON
     time_stamp();
     trace(func_name,action_end);
#endif
     return(mean);
}

#endif /* SET_FREE_RADII_H_ */
