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

			static void test()
			{
				std::cout << "******Likelihood With Bisection test start*****\n";
				Point<1> a{ 2.5438 };
				auto* f = new ConcreteFuncParam::LinearFunc{};
				RegInterface::DataSet<1> data = GenerateDataSet(a, f);
				ConcreteReg::LikelihoodLinear<1, 1, FuncParamInterface
					::IFuncParam> L{ std::move(data),f };
				//ConcreteOptimizer::Grid Algo{ &L, {-15, 25} ,5000 };
				//Optimizer1Step<1, FuncInterface::IFunc<1>, ConcreteState::StateSegment> opt{ &Algo };

				ConcreteOptimizer::Bisection Algo{ &L, {-10, 18}};
				//ConcreteOptimizer::Dichotomy Algo{ &L, {-15, 25}};
				//ConcreteOptimizer::GoldenSection Algo{ &L, {-15, 25}};
				Optimizer<1, FuncInterface::IFunc<1>, ConcreteState::StateSegment> opt{ &Algo, OptimizerParams{0.001, 0.001, 25} };

				std::cout << "Optimization with Grid started...\n";
				opt.Optimize();
				std::cout << "Optimization with Grid finalized.\n";

				std::cout << "Total number of iterations is s = " << opt.CurIterCount() << '\n';
				std::cout << "Final guess is x = " << opt.CurrentGuess() << '\n';

				std::cout << "******Likelihood With Bisection test end*****\n";
			}
		};




		class testRegression
		{

		};

	} // UnitTests
} // OptLib