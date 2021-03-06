/*
 * This is the return type from each function call
 */
#ifndef ERRORCODES_H_
#define ERRORCODES_H_
 
typedef enum ERR_MSG
{
  ERR_OK,
  ERR_OK_BUSY,
  ERR_OK_FINISHED,
	ERR_NOK,
	ERR_NOK_FILE_NOT_FOUND,
	ERR_NOK_OUT_OF_BOUNDS,
	ERR_NOK_ENERGY_NOT_CONSERVED,
	ERR_NOK_INCORRECT_TIMESTEP
} ERR_MSG;

#endif /* ERRORCODES_H_ */
