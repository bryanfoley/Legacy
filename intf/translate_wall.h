void translate_wall(double wall_particle[44][m_max][z_max])
{
	int i;
#ifdef TRACE_ON
     char func_name[30] = "translate_wall";
     char action_begin[10] = ">>>";
     char action_end[10] = "<<<";
     time_stamp();
     trace(func_name,action_begin);
#endif
     for(i = 22; i < 44; i++)
      {
       wall_particle[i][3][0] = ((wall_particle[i][3][0]) - wall_step);
      }
#ifdef TRACE_ON
     time_stamp();
     trace(func_name,action_end);
#endif
}
