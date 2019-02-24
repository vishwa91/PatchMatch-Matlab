function disp = sl_patchmatch(pattern, im)
	% Function to compute disparity for structured light system
	% 
	% Inputs:
	% 	Pattern: Displayed pattern
	% 	im: Captured image
	%
	% Outputs:
	% 	disp: Computed disparity as seen from 'im' perspective

	% TODO: Move code to mex instead of doing system calls. That you we can
	% also pass additional parameters

	% First save images
	imwrite(uint8(pattern*255), 'tmp/pat.png')
	imwrite(uint8(im*255), 'tmp/im.png')

	% Then do a system call
	[status, cmdout] = system('tools/extern/patchmatch/pm tmp/pat.png tmp/im.png')

end
