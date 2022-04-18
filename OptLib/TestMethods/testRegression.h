#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace UnitTests
	{
		struct testLikelihood
		{
			static void testLikelihoodLinear()
			{
				std::cout << "******LikelihoodLinear test start*****\n";

				Point<1> a{ 1.0 };
				auto* f = new OptLib::ConcreteFuncParam::LinearFunc();

				 auto data = GenerateDataSet<1, 1>(a, f );
				 auto data1 = data;

				ConcreteReg::LikelihoodLinear<1, 1, FuncParamInterface::IFuncParam> L{std::move(data), f};
				std::cout << std::sqrt(L(a)/data1.size()) << "  " << '\n';

				std::cout << "******LikelihoodLinear test end*******\n\n";
			}

			static void testLikelihoodLinearWithGrad()
			{
				std::cout << "******LikelihoodLinearWithGrad test start*****\n";

				Point<1> a{ 1.0 };
				auto* f = new OptLib::ConcreteFuncParam::LinearFuncWithGrad();

				auto data = GenerateDataSet<1, 1>(a, f);
				auto data1 = data;

				ConcreteReg::LikelihoodLinearWithGrad<1, 1, FuncParamInterface::IFuncParamWithGrad> L{ std::move(data), f };
		//		std::cout << std::sqrt(L(a) / data1.size()) << "  " << '\n';

				std::cout << "******LikelihoodLinearWithGrad test end*******\n\n";
			}


			template<size_t dimX, size_t dimP>
			static RegInterface::DataSet<dimX> GenerateDataSet(const Point<dimP>& a, const FuncParamInterface::IFuncParam<dimX, dimP>* f)
			{
				std::default_random_engine generatorX;
				std::uniform_real_distribution<double> Xdistrib(0.0, 1.0); // generate x-values

				double eps = 0.0001; // small noise to y-values
				std::default_random_engine generatorY;
				std::uniform_real_distribution<double> Ynoise(-eps, eps); // generate x-values

				int nrolls = 1001; // number of correlation points

				RegInterface::DataSet<dimX> out;

				for (int i = 0; i < nrolls; ++i) {
					Point<dimX> x;
					for (int k = 0; k < dimX; k++)
						x[k] = Xdistrib(generatorX);
					double val = f->operator()(x, a) + Ynoise(generatorY);
					out.emplace_back(x, val);
				}

				return out;
			}

			static void LikelihoodMinimization()
			{
				std::cout << "******Likelihood minimization With Bisection test start*****\n";
				Point<1> a{ 2.5438 };
				ConcreteFuncParam::LinearFunc f{};
				ConcreteReg::LikelihoodLinear<1, 1, FuncParamInterface
					::IFuncParam> L{ GenerateDataSet(a, &f), &f };

				OptimizerParams prm{ 0.001, 0.001, 101 };

				ConcreteState::StateBisection State{ SetOfPoints<2, Point<1>>{ {-2, 5} },&L };
				Optimizer<1, ConcreteState::StateBisection, FuncInterface::IFunc> opt{ &State, &L, prm };

				std::cout << "Optimization with Bisection started...\n";
				opt.Optimize<ConcreteOptimizer::Bisection>();
				std::cout << "Optimization with Bisection finalized.\n";

				std::cout << "Total number of iterations is s = " << opt.CurIterCount() << '\n';
				std::cout << "Final guess is x = " << State.Guess() << '\n';

				std::cout << "******Likelihood minimization With Bisection test end*****\n";
			}
		};




		class testRegression
		{

		};

	} // UnitTests
} // OptLib