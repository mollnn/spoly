#include <chrono>

// #define ENABLE_TIME_COUNT

#ifdef ENABLE_TIME_COUNT
#define CHRONO_NOW std::chrono::high_resolution_clock::now()
#define CHRONO_DIFF(x) (std::chrono::duration_cast<std::chrono::nanoseconds>(x).count())
#else
#define CHRONO_NOW 1
#define CHRONO_DIFF(x) (0)
#endif