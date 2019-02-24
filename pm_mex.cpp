/* Mex file for patch match stereo */

/* Include utilities */
#include <utils.h>

/* OpenCV includes */
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/* PatchMatch includes */
#include <pm.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	/* Declare all variables apriori */
	double alpha, gamma, tau_c, tau_g;
	int winsize, max_disparity, niters;

	/* Image and dimensions */
	int h1, w1, h2, w2;

	/* Counting variables */
	int idx1, idx2, idx3;

	/* Images */
	uint8_t *left_img;
	uint8_t *right_img;

	/* Output variables */
	double *left_disparity;
	double *right_disparity;

	/*Structure for parameters */
	mxArray *struct_var;

	/* Sanity check */

	/* Number of parameters */
	check_args(nrhs, nlhs, 3, 2);

	/* Make sure last input is structure */
	//check_struct(prhs[2]);

	/* Parse the structure */
	struct_var = get_struct_field(prhs[2], "alpha", "Need alpha");
	alpha = (double)mxGetScalar(struct_var);

	struct_var = get_struct_field(prhs[2], "gamma", "Need gamma");
	gamma = (double)mxGetScalar(struct_var);
	
	struct_var = get_struct_field(prhs[2], "tau_c", "Need tau_c");
	tau_c = (double)mxGetScalar(struct_var);
	
	struct_var = get_struct_field(prhs[2], "tau_g", "Need tau_g");
	tau_g = (double)mxGetScalar(struct_var);

	struct_var = get_struct_field(prhs[2], "winsize", "Need window size");
	winsize = (int)mxGetScalar(struct_var);

	struct_var = get_struct_field(prhs[2], "max_disparity", "Need max disparity");
	max_disparity = (int)mxGetScalar(struct_var);

	struct_var = get_struct_field(prhs[2], "niters", "Need #iterations");
	niters = (int)mxGetScalar(struct_var);

	/* Extract both images */
	left_img = (uint8_t *)mxGetData(prhs[0]);
	h1 = (mxGetDimensions(prhs[0]))[0];
	w1 = (mxGetDimensions(prhs[0]))[1];

	right_img = (uint8_t *)mxGetData(prhs[1]);
	h2 = (mxGetDimensions(prhs[1]))[0];
	w2 = (mxGetDimensions(prhs[1]))[1];

	if ((h1 != h2) || (w1 != w2))
	{
		mexErrMsgIdAndTxt("PM:ErrHandle", "Image dimensions need to be same");
	}

	/* Create outputs */
	plhs[0] = mxCreateDoubleMatrix((mwSize)h1, (mwSize)w1, mxREAL);
	plhs[1] = mxCreateDoubleMatrix((mwSize)h2, (mwSize)w2, mxREAL);

	left_disparity = (double *)mxGetPr(plhs[0]);
	right_disparity = (double *)mxGetPr(plhs[1]);

	/* Okay so data is good and loaded. Convert to CV matrices */
	cv::Mat img1(w1, h1, CV_8UC3, left_img);
	cv::Mat img2(w2, h2, CV_8UC3, right_img);

	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE );
	cv::imshow("Display window", img1);
	cv::waitKey(1000);
	cv::destroyAllWindows();

	/* Manually copy data for now 
	for (idx3 = 0; idx3 < 3; idx3++)
	{
		for (idx2 = 0; idx2 < w1; idx2++)
		{
			for (idx1 = 0; idx1 < h1; idx1++)
			{
				img1(idx1, idx2, idx3) = left_img[idx1 + h1*idx2 + h1*w1*idx3];
				img2(idx1, idx2, idx3) = right_img[idx1 + h1*idx2 + h1*w1*idx3];
			}
		}
	}*/

	/* Now run PatchMatch */
	pm::PatchMatch patch_match(alpha, gamma, tau_c, tau_g, winsize,
		   					   max_disparity);
	patch_match.set(img1, img2);
	patch_match.process(niters);
	patch_match.postProcess();
	
	printf("Computing disparity\n");
	cv::Mat1f disp1 = patch_match.getLeftDisparityMap();
	cv::Mat1f disp2 = patch_match.getRightDisparityMap();

	cv::normalize(disp1, disp1, 0, 255, cv::NORM_MINMAX);
	cv::imwrite("disparity1.png", disp1);

	/* Manually copy data just to be sure */
	printf("Copying data\n");
	try
	{
		#pragma omp parallel for
		for (idx2 = 0; idx2 < w1; idx2++)
		{
			for (idx1 = 0; idx1 < h1; idx1++)
			{
				left_disparity[h1*idx2 + idx1] = (double)disp1.at<float>(idx2, idx1);
				right_disparity[h1*idx2 + idx1] = (double)disp2.at<float>(idx2, idx1);
			}
		}
		printf("Completed copying\n");
	}
	catch (const std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << "\n";
	}

}

