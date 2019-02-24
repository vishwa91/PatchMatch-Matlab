/* C header file for generic utilities */

#include <mex.h>
#include <iostream>
#include <stdlib.h>

/* Min, max functions */
#define MIN(X, Y)           (((X) < (Y)) ?  (X):(Y))
#define MAX(X, Y)           (((X) > (Y)) ?  (X):(Y))

/* Error handling routines */
void check_args(int nrhs, int nlhs, int nrhs_true, int nlhs_true);
void check_struct(const mxArray *prhs);

/* Struct parsing utility */
mxArray *get_struct_field(const mxArray *prhs, std::string field_name,
	   					  std::string msg);
