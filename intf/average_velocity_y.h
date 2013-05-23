double average_velocity_y(double free_particle[n_max][m_max][z_max])
{
       double sumy = 0.0;
       double ans = 0.0;
       int n_max;
#ifdef TRACE_ON
       char func_name[30] = "average_velocity_y";
       char action_begin[10] = ">>>";
       char action_end[10] = "<<<";
       time_stamp();
       trace(func_name,action_begin);
#endif
       
       for(i = 0; i < n_max; i++)
        {
         sumy += free_particle[i][1][0];
        }
       
       ans = (sumy)/n_max;
#ifdef TRACE_ON
       time_stamp();
       trace(func_name,action_end);
#endif
       
       return(ans);
}
