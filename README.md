# pdp-scripts
This repository is going to be used to store scripts optimized by appling parallelism in code by using OpenMP standards

# Quick resume of each folder
- aula03_pdp: We made a speedup of mandelbrot sequence using dynamic parallelism with OpenMP with Block x Block approach
The idea here is define private variables in the pragma directive to avoid threads misread values during the calculation procedure
and take advantage of matrix format of the plane to divide the plane in zones to computing the fractals by area
