#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace UnitTests
	{
		using namespace AuxMethods;
		class testOptimizer
		{
		public:
			static void testBicection()
			{
				std::cout << "******Direct Optimization test start*****\n";

				ConcreteFunc::FunctionWithHess f{};
				ConcreteState::StateSimplex<1> state{ Simplex<2, 1>{ { {-2}, { 5 }}} };

				ConcreteOptimizer::Bicection algo{ &f, &state };

				std::cout << "Current simplex is:\n" << "  " << algo.CurSimplex() << "\n";
				algo.proceed();
				std::cout << "Current simplex is:\n" << "  " << algo.CurSimplex() << "\n";
				algo.proceed();
				std::cout << "Current simplex is:\n" << "  " << algo.CurSimplex() << "\n";

				std::cout << "******Direct Optimization test end*******\n\n";
			}

			static void testOverallOptimizer_WithBicection()
			{

			}


			/*static void testDirect1DFuncAlongGrad()
			{
				std::cout << "******Optimization test start*****\n";
				FuncInterface::IFunc<1>* f = new ConcreteFunc::FunctionWithHess();
				ConcreteState::StateSimplex<1>* state = new ConcreteState::StateSimplex(Simplex<2, 1>{ { {-2}, { 5 }}});
				OptimizerInterface::IDirectAlgo<1>* algo = new ConcreteOptimizer::Bicection(f, state);

				Optimizer<1> Optimizer{ algo, OptimizerParams{0.001, 0.001, 100} };

				std::cout << "Initial simplex is:\n" << "  " << algo->CurSimplex() << "\n";
				Optimizer.Optimize();
				std::cout << "Final simplex is:\n" << "  " << algo->CurSimplex() << "\n";
				std::cout << "Guess value is:\n" << "  " << Optimizer.CurrentGuess() << "\n";
				std::cout << "Iter count is:\n" << "  " << Optimizer.cur_iter_count() << "\n";
				std::cout << "****** Optimization test end*******\n\n";
			}*/
		};

	} // UnitTests
} // OptLib