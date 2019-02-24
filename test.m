%% Test patchmatch stereo mex version

%% Parameters
opts.alpha = 0.9;
opts.gamma = 10.0;
opts.tau_c = 10.0;
opts.tau_g = 2.0;
opts.winsize = int32(35);
opts.max_disparity = int32(60);
opts.niters = 1;

im1 = imread('left.png');
im2 = imread('right.png');

%[left_disparity, right_disparity] = pm_mex(im1(1:100, 100:200, :), ...
%										   im2(1:100, 100:200, :), opts);
[l, r] = pm_mex(im1, im2, opts);
