#include "stdafx.h"
#include <conio.h>
//#include <Python.h>
//#include <matplotlibcpp.h>

#ifdef DEBUG_LIB
	#include "OptLib/TestMethods/testSimplex.h"
	#include "OptLib/TestMethods/testFunction.h"
	#include "OptLib/TestMethods/testState.h"
	#include "OptLib/TestMethods/testOptimizer.h"
	#include "OptLib/TestMethods/testRegression.h"
#endif // DEBUG_LIB

//namespace plt = matplotlibcpp;


int main()
{
	/*std::vector<double> y = { 1, 3, 2, 4 };
	plt::plot(y);
	plt::savefig("minimal.pdf");*/

#ifdef DEBUG_LIB
	// test Simplex
	OptLib::UnitTests::testSimplex::testPointOperations();
	OptLib::UnitTests::testSimplex::testSimplexVal();
	
	// test functions
	OptLib::UnitTests::testFunction::testGradient();
	OptLib::UnitTests::testFunction::testHessian();
	OptLib::UnitTests::testFunction::test2DHessian();
	OptLib::UnitTests::testFunction::test2DWithHessNoGrad();
	OptLib::UnitTests::testFunction::testParaboloid();
	OptLib::UnitTests::testFunction::testParaboloidAlongDirection();

	// test states
	OptLib::UnitTests::testState::testStateDirect();
	OptLib::UnitTests::testState::testStateSegment();
	//OptLib::UnitTests::testState::testStatePoint(); // TODO
	//OptLib::UnitTests::testState::testStateStochastic(); // TODO

	// test optimizers
	OptLib::UnitTests::testOptimizer::testBicection();
	OptLib::UnitTests::testOptimizer::testOverallOptimizerWithBicection(); 
	OptLib::UnitTests::testOptimizer::testDichotomy();
	OptLib::UnitTests::testOptimizer::testOverallOptimizerWithDichotomy(); 
	OptLib::UnitTests::testOptimizer::testGoldenSection();
	OptLib::UnitTests::testOptimizer::testOverallOptimizerWithGoldenSection();
	OptLib::UnitTests::testOptimizer::testGrid();
	OptLib::UnitTests::testOptimizer::testOverallOptimizerWithGrid();
	OptLib::UnitTests::testOptimizer::testOverallOptimizerWithNelderMead();
	OptLib::UnitTests::testOptimizer::testOverallOptimizerWithNewton();

	// test regression

	OptLib::UnitTests::testLikelihood::GenerateDataSet<1,1>({1.0}, new OptLib::ConcreteFuncParam::LinearFunc());
	OptLib::UnitTests::testLikelihood::testLikelihoodLinear();
	OptLib::UnitTests::testLikelihood::testLikelihoodLinearWithGrad();
	OptLib::UnitTests::testLikelihood::LikelihoodMinimization();

#endif // DEBUG_LIB
}
