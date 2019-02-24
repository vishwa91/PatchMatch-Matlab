/* Generic utilities for various C-Mex functions */

#include <utils.h>

void check_args(int nrhs, int nlhs, int true_nrhs, int true_nlhs)
{
	if (nrhs != true_nrhs || nlhs != true_nlhs)
	{
		mexErrMsgIdAndTxt("Utils:InvalidInputs",
						  "Invalid number of inputs/outputs");
		return;
	}
}
void check_struct(mxArray *prhs)
{
	if (!mxIsStruct(prhs))
	{
		mexErrMsgIdAndTxt("Utils:NeedStruct", "params has to be a structure");
		return;
	}
}

mxArray *get_struct_field(const mxArray *prhs, std::string field_name,
	   					  std::string msg)
{
	/* Get the field variable */
	mxArray *struct_var;
	struct_var = mxGetField(prhs, 0, field_name.c_str());
	if (struct_var == NULL)
	{
		mexErrMsgIdAndTxt("Utils:StructParam", msg.c_str());
		return NULL;
	}

	return struct_var;
}
