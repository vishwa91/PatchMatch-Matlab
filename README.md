# PatchMatch Stereo Matlab implementation
This code implementents [PatchMatch stereo](https://www.microsoft.com/en-us/research/wp-content/uploads/2011/01/PatchMatchStereo_BMVC2011_6MB.pdf) with a direct interface to Matlab. I just wrote the Matlab wrapper;
most of the heavy lifting was done by the [actual C++ implementation](https://github.com/ivanbergonzani/patch-match-stereo).

## Required packages:
0. **Linux**: I have only tested it on Linux 18.04, but other linux versions should work
1. **Matlab**: I tried on R2018a
2. **OpenCV**
3. **OpenMP**: For parallelization at some places

## Compiling
1. **From command-line**: Run make from command line to compile the program. The output should be `pm_mex.mexa64`.
2. **From matlab prompt**: Run make.m

## Testing
This repo has `left.png` and `right.png` from Middlebury dataset (Baby doll, 2009) for testing the code.
Run `test.m` to test the code with representative parameters.

## Usage:
`[left_disparity, right_disparity] = patchmatch_stereo(left_img, right_img, opts);` where,
1. `left_img`: Image captured with left camera (uint8, RGB)
2. `right_img`: Image captured with right camera (uint8, RGB)
3. opts (optional): Structure with options for patchmatch algorithm with the following entries:
  - `alpha` (0.9): Penalty term for balance between gradient and color fidelity
  - `gamma` (10.0): Controls how similar the colors should be in two views
  - `tau_c` (10.0): Tolerance term for color similarity
  - `tau_g` (2.0): Tolerance term for gradient similarity
  - `winsize`: Window size for computing disparity
  - `max_disparity`: Maximum allowable disparity
  - `niters`: Number of patchmatch iterations

# Some common problems:
1. When running the code, Matlab throws an error about libTiff. See [this]([200~https://groups.google.com/forum/#!topic/caffe-users/c1ZSm-nacEo) for a solution. Essentially you need to ask Matlab to look for libraries elsewhere.
