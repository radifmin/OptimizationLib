#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace UnitTests
	{
		class testOptimizer
		{
		public:
			static void testBicection()
			{
				std::cout << "******Bicection test start*****\n";

				ConcreteFunc::FunctionWithHess f{};
				ConcreteState::StateBisection State{ std::move(SetOfPoints<2, Point<1>>{ {-2, 5} }), &f };

				std::cout << "Current simplex is:\n" << "  " << State.GuessDomain() << "\n";
				for (int i = 0; i < 10; i++)
				{
					OptimizerInterface::OptimizerAlgorithm<1>::
						Proceed<ConcreteOptimizer::Bisection, ConcreteState::StateBisection, FuncInterface::IFunc>(&State, &f);
					std::cout << "Current simplex is:\n" << "  " << State.GuessDomain() << "\n";
				}
				std::cout << "******Bicection test end*******\n\n";
			}
			static void testOverallOptimizerWithBicection()
			{
				std::cout << "******OverallOptimizer With Bicection test start*****\n";

				OptimizerParams prm{ 0.001, 0.001, 101 };
				ConcreteFunc::Function f{};
				ConcreteState::StateBisection State{ SetOfPoints<2, Point<1>>{ {-2, 5} }, &f };

				Optimizer<1, ConcreteState::StateBisection, FuncInterface::IFunc> opt{ &State, &f, prm };

				std::cout << "Optimization with Bicection started...\n";
				opt.Optimize<ConcreteOptimizer::Bisection>();
				std::cout << "Optimization with Bicection finalized.\n";

				std::cout << "Total number of iterations is s = " << opt.CurIterCount() << '\n';
				std::cout << "Final guess is x = " << State.Guess() << '\n';

				std::cout << "******OverallOptimizer With Bicection test end*******\n\n";
			}


			static void testDichotomy()
			{
				std::cout << "******Dichotomy test start*****\n";
				ConcreteFunc::FunctionWithHess f{};
				ConcreteState::StateDichotomy State{ std::move(SetOfPoints<2, Point<1>>{ {-2, 5} }), &f };

				std::cout << "Current simplex is:\n" << "  " << State.GuessDomain() << "\n";
				for (int i = 0; i < 10; i++)
				{
					OptimizerInterface::OptimizerAlgorithm<1>::
						Proceed<ConcreteOptimizer::Dichotomy, ConcreteState::StateDichotomy, FuncInterface::IFunc>(&State, &f);
					std::cout << "Current simplex is:\n" << "  " << State.GuessDomain() << "\n";
				}
				std::cout << "******Dichotomy test end*******\n\n";
			}
			
			static void testOverallOptimizerWithDichotomy()
			{
				std::cout << "******OverallOptimizer With Dichotomy test start*****\n";

				OptimizerParams prm{ 0.001, 0.001, 101 };
				ConcreteFunc::Function f{};
				ConcreteState::StateDichotomy State{ std::move(SetOfPoints<2, Point<1>>{ {-2, 5} }),& f };

				Optimizer<1, ConcreteState::StateDichotomy, FuncInterface::IFunc> opt{ &State, &f, prm };


				std::cout << "Optimization with Dichotomy started...\n";
				opt.Optimize<ConcreteOptimizer::Dichotomy>();
				std::cout << "Optimization with Dichotomy finalized.\n";

				std::cout << "Total number of iterations is s = " << opt.CurIterCount() << '\n';
				std::cout << "Final guess is x = " << State.Guess() << '\n';

				std::cout << "******OverallOptimizer With Dichotomy test end*****\n\n";
			}
			
			static void testGoldenSection()
			{
				std::cout << "******GoldenSection test start*****\n";

				ConcreteFunc::FunctionWithHess f{};
				ConcreteState::StateGoldenSection State{ std::move(SetOfPoints<2, Point<1>>{ {-2, 5} }),& f };
				std::cout << "Current simplex is:\n" << "  " << State.GuessDomain() << "\n";
				for (int i = 0; i < 10; i++)
				{
					OptimizerInterface::OptimizerAlgorithm<1>::
						Proceed<ConcreteOptimizer::GoldenSection, ConcreteState::StateGoldenSection, FuncInterface::IFunc>(&State, &f);
					std::cout << "Current simplex is:\n" << "  " << State.GuessDomain() << "\n";
				}
				std::cout << "******GoldenSection test end*******\n\n";
			}

			static void testOverallOptimizerWithGoldenSection()
			{
				std::cout << "******OverallOptimizer With GoldenSection test start*****\n";

				OptimizerParams prm{ 0.001, 0.001, 101 };
				ConcreteFunc::Function f{};
				ConcreteState::StateGoldenSection State{ std::move(SetOfPoints<2, Point<1>>{ {-2, 5} }),& f };

				Optimizer<1, ConcreteState::StateGoldenSection, FuncInterface::IFunc> opt{ &State, &f, prm };

				std::cout << "Optimization with GoldenSection started...\n";
				opt.Optimize<ConcreteOptimizer::GoldenSection>();
				std::cout << "Optimization with GoldenSection finalized.\n";

				std::cout << "Total number of iterations is s = " << opt.CurIterCount() << '\n';
				std::cout << "Final guess is x = " << State.Guess() << '\n';

				std::cout << "******OverallOptimizer With GoldenSection test end*******\n\n";
			}

			static void testGrid()
			{
				std::cout << "******Grid test start*****\n";
				ConcreteFunc::FunctionWithHess f{};
				ConcreteState::StateGrid State{SetOfPoints<2, Point<1>>{ {-2, 5} }, &f, 100 };

				std::cout << "Simplex is:\n" << "  " << State.GuessDomain() << "\n" << "n = " << State.n << "\n";

				auto result = OptimizerInterface::OptimizerAlgorithm<1>::
					Proceed<ConcreteOptimizer::Grid, ConcreteState::StateGrid, FuncInterface::IFunc>(&State, &f);

				std::cout << "Result is: " << result << "\n";
				std::cout << "******Grid test end*******\n\n";
			}

			static void testOverallOptimizerWithGrid()
			{
				std::cout << "******OverallOptimizer With Grid test start*****\n";

				ConcreteFunc::Function f{};
				ConcreteState::StateGrid State{ SetOfPoints<2, Point<1>>{ {-2, 5} }, &f, 200 };
				Optimizer1Step<1, ConcreteState::StateGrid, FuncInterface::IFunc> opt{ &State, &f };

				std::cout << "Optimization with Grid started...\n";
				opt.Optimize<ConcreteOptimizer::Grid>();
				std::cout << "Optimization with Grid finalized.\n";
				std::cout << "Final guess is x = " << State.Guess() << '\n';
				std::cout << "******OverallOptimizer With Grid test end*******\n\n";
			}

			static void testOverallOptimizerWithNelderMead()
			{
				std::cout << "******OverallOptimizer With Nelder Mead test start*****\n";

				OptimizerParams prm{ 0.001, 0.001, 500 };
				ConcreteFunc::Paraboloid2D f{ SetOfPoints<2,Point<2>>{ { {1,0}, {0,10}}} };
				SetOfPoints<3, Point<2>> P{ { {0, -1}, { -1,1 }, { 1,1 } } };
				ConcreteState::StateNelderMead<2> State{ std::move(P), &f, 1.0, 0.5, 2.0 };

				/*ConcreteOptimizer::NelderMead<1> Algo{ &f, {-9, 9},1.0,0.5,2.0 };*/
				Optimizer<2, ConcreteState::StateNelderMead<2>, FuncInterface::IFunc> opt{ &State, &f, prm };

				std::cout << "Optimization with Nelder Mead started...\n";
				opt.Optimize<ConcreteOptimizer::NelderMead<2>>();
				std::cout << "Optimization with Nelder Mead finalized.\n";

				std::cout << "Total number of iterations is s = " << opt.CurIterCount() << '\n';
				std::cout << "Final guess is x = " << opt.CurrentGuess() << '\n';
				std::cout << "******OverallOptimizer With Nelder Mead test end*******\n\n";
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
			static void testOverallOptimizerWithNewton()
			{
				std::cout << "******OverallOptimizer With Newton test start*****\n";

				OptimizerParams prm{ 0.001, 0.001, 10 };
				//ConcreteFunc::Paraboloid2D f{ SetOfPoints<5,Point<5>>{ { {1,1,1,0}, {0,1}}} };
				ConcreteFunc::Himmel f{};
				ConcreteState::StateNewton<2> State{ {3.8,2.3}, &f };

				Optimizer<2, ConcreteState::StateNewton<2>, FuncInterface::IFuncWithHess> opt{ &State, &f, prm };

				std::cout << "Optimization with Newton started...\n";
				opt.Optimize<ConcreteOptimizer::Newton<2>>();
				std::cout << "Optimization with Newton finalized.\n";

				std::cout << "Total number of iterations is s = " << opt.CurIterCount() << '\n';
				std::cout << "Final guess is x = " << opt.CurrentGuess() << '\n';
				std::cout << "******OverallOptimizer With Newton test end*******\n\n";
			}
		};

	} // UnitTests
} // OptLib