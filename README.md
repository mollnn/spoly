# Specular Polynomials

A reformulation of specular constraints into polynomial systems that enables efficiently finding a complete set of all admissible specular paths connecting two arbitrary endpoints in a scene, by converting the problem into finding zeros of the determinant of univariate matrix polynomials.


## Standalone demo: constraint validator

We provide a minimalist demo: **a single** cpp source file `standalone.cpp` that only relies on the C++ standard libraries, which could help you understand how the method works without diving into the full project.

Just build it with any modern C++ compiler (g++, msvc, ...) and check how the vertex info of triangles are transformed into the coefficients of bivariate polynomials and univariate polynomial matrices.

## Build the complete project

The project is based on https://github.com/VicentChen/mitsuba. Please install the dependency first.

```
cd mts1
mkdir cbuild
cd cbuild
cmake ..
```

Then build the generated project in `cbuild`.

Tested on Windows 10, Visual Studio 2022.

The implementation builds upon [Mbglints](https://github.com/wangningbei/mbglints) and [CyPolynomials](http://codebase.cemyuksel.com/code.html). 

## Reproduce

We provide several experiments in the `test` dir. 

- Fig. 6: Plane (equal-time comparisons with stochastic methods).

- Fig. 8: Plane and Pool (ablation studies to compare with Newton's method using heuristic seeds).

- Table 4: Timing for single reflection. Please enable the timing macro in `chrono_def.h`.

- Fig. 5: Glints rendering for double reflections. Currently it is an unoptimized scalar CPU version. Faster ones will be available soon.

Please refer to any additional comments in the scripts. One may have to switch the macros `N_DEGREE, N_POLY` in `resultant_common.h` and `ENABLE_TIME_COUNT` in `chrono_def.h` to reproduce the performance.

## Available features

Currently, in this repo, only single reflection (R) and refraction (T) is completely supported. 

For double reflection (RR), a serial version without loop unroll or vectorization is available (though very slow). The CUDA source code is also contained (`.cu` and `.cuh` files), but not installed by default.

---

![repre](repre.jpg)

## Abstract

Finding valid light paths that involve specular vertices in Monte Carlo rendering requires solving many non-linear, transcendental equations in high-dimensional space. Existing approaches heavily rely on Newton iterations in path space, which are limited to obtaining at most a single solution each time and easily diverge when initialized with improper seeds.

We propose specular polynomials, a Newton iteration-free methodology for finding a complete set of admissible specular paths connecting two arbitrary endpoints in a scene. The core is a reformulation of specular constraints into polynomial systems, which makes it possible to reduce the task to a univariate root-finding problem. We first derive bivariate systems utilizing rational coordinate mapping between the coordinates of consecutive vertices. Subsequently, we adopt the hidden variable resultant method for variable elimination, converting the problem into finding zeros of the determinant of univariate matrix polynomials. This can be effectively solved through Laplacian expansion for one bounce and a bisection solver for more bounces.

Our solution is generic, completely deterministic, accurate for the case of one bounce, and GPU-friendly. We develop efficient CPU and GPU implementations and apply them to challenging glints and caustic rendering. Experiments on various scenarios demonstrate the superiority of specular polynomial-based solutions compared to Newton iteration-based counterparts.


## Acknowledgement

Some scenes are modified from [SMS](https://github.com/tizian/specular-manifold-sampling). The implementation builds upon [Mbglints](https://github.com/wangningbei/mbglints) and [CyPolynomials](http://codebase.cemyuksel.com/code.html). We sincerely thank the authors for kindly release their code and scenes, as well as their great works.
