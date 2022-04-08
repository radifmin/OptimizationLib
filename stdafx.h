#pragma once

#ifdef __AVX__
#include <immintrin.h>
#else
//#warning No AVX support - will not compile
#endif


#define DEBUG_LIB

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <memory>
#include <numeric>
#include <tuple>
#include <iterator>
#include <immintrin.h>
#include <cmath>
//#include <type_traits>
#include <random>

#include "OptLib/AuxMethods/Simplex.h"

#include "OptLib/Functions/FuncParamInterface.h"
#include "OptLib/Functions/FunctionInterface.h"
#include "OptLib/Functions/Function.h"

#include "OptLib/States/StateInterface.h"
#include "OptLib/States/State.h"

#include "OptLib/Optimizers/OptimizerInterface.h"
#include "OptLib/Optimizers/OneDim/Bisection.h"
#include "OptLib/Optimizers/OneDim/Grid.h"
<<<<<<< HEAD
=======
#include "OptLib/Optimizers/OneDim/GoldenSection.h"
>>>>>>> 85765a26689e5c68622d1d0e3a8076ab5001a48e
#include "OptLib/Optimizers/OneDim/Dichotomy.h"

#include "OptLib/Optimizers/OverallOptimizer.h"

#include "OptLib/RegressionLib/RegressionInterface.h"
<<<<<<< HEAD
#include "OptLib/RegressionLib/Regression.h"
=======
#include "OptLib/RegressionLib/Regression.h"

>>>>>>> 85765a26689e5c68622d1d0e3a8076ab5001a48e
