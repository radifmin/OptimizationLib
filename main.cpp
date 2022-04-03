#include "stdafx.h"

#ifdef DEBUG_LIB
	#include "OptLib/TestMethods/testSimplex.h"
	#include "OptLib/TestMethods/testFunction.h"
	#include "OptLib/TestMethods/testState.h"
	#include "OptLib/TestMethods/testOptimizer.h"
#endif // DEBUG_LIB



//using pp = std::array<double, 3>;
//
//struct P2 : public pp
//{
//	double Val;
//	P2(double val) :pp{  }, Val{ val }{}
//
//	auto arr() { return this->_Elems; }
//};




int main()
{
//	P2 tp{1};
//	auto tt = tp.data();





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
	OptLib::UnitTests::testOptimizer::testGrid();
	OptLib::UnitTests::testOptimizer::testOverallOptimizerWithGrid();
	//testOptimizer::testOptimizer_();

	// reset to previous version

#endif // DEBUG_LIB
}
