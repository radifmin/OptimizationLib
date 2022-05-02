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

				ConcreteReg::LikelihoodLinear<1, 1, ConcreteFuncParam::LinearFunc> L{std::move(data), f};
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

				ConcreteReg::LikelihoodLinearWithGrad<1, 1, ConcreteFuncParam::LinearFuncWithGrad> L{ std::move(data), f };
		//		std::cout << std::sqrt(L(a) / data1.size()) << "  " << '\n';

				std::cout << "******LikelihoodLinearWithGrad test end*******\n\n";
			}

			static const int nrolls = 1001; // number of correlation points

			template<size_t dimX, size_t dimP>
			static RegInterface::DataSet<dimX> GenerateDataSet(const Point<dimP>& a, const FuncParamInterface::IFuncParam<dimX, dimP>* f)
			{
				std::default_random_engine generatorX;
				std::uniform_real_distribution<double> Xdistrib(0.0, 1.0); // generate x-values

				double eps = 0.0001; // small noise to y-values
				std::default_random_engine generatorY;
				std::uniform_real_distribution<double> Ynoise(-eps, eps); // generate x-values


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
				ConcreteReg::LikelihoodLinear<1, 1, ConcreteFuncParam::LinearFunc> L{ GenerateDataSet(a, &f), &f };

				OptimizerParams prm{ 0.001, 0.001, 101 };

				ConcreteState::StateBisection State{ SetOfPoints<2, Point<1>>{ {-2, 5} },&L };
				Optimizer<1, ConcreteState::StateBisection, FuncInterface::IFunc> opt{ &State, &L, prm };

				opt.Optimize<ConcreteOptimizer::Bisection>();

				std::cout << "Total number of iterations is s = " << opt.CurIterCount() << '\n';
				std::cout << "Final guess is x = " << State.Guess() << '\n';

				std::cout << "******Likelihood minimization With Bisection test end*****\n\n";
			}
		};

		struct testRegression
		{
			static void testRegressionInterface()
			{
				using namespace FuncParamInterface;
				using namespace ConcreteFuncParam;
				using namespace FunctWithCounter;

				SetOfPoints<2, Point<1>> Points{ {1.0, 3.5} };
				Point<1> a{ 2.5438 };
				LinearFunc f{};
				ICounterFuncParam<1,1> FCounter{ &f };

				RegInterface::DataSet<1> Data{ testLikelihood::GenerateDataSet(a, &f) };

				auto data = Data;
				auto points = Points;
				auto fCounter = FCounter;

				std::cout << "******IRegression With Dichotomy test start*****\n";
				data = Data;
				points = Points;
				fCounter = FCounter;
				StateParams::DichotomyParams par{ std::move(points) };

				RegInterface::IRegression<1, 1, IFuncParam<1, 1>,
					ConcreteReg::LikelihoodLinear,
					StateParams::DichotomyParams> reg{ std::move(data), &fCounter, par };
				std::cout << "Overall function calls count: " << fCounter.Counter / (float)testLikelihood::nrolls << '\n';

				std::cout << "******IRegression With Dichotomy test end*****\n\n";


				std::cout << "******IRegression With NelderMead test start*****\n";
				data = Data;
				points = Points;
				fCounter = FCounter;
				StateParams::NelderMeadParams<1> par0{ std::move(points), 1.0, 0.5, 2.0 };

				RegInterface::IRegression<1, 1, IFuncParam<1, 1>,
					ConcreteReg::LikelihoodLinear,
					StateParams::NelderMeadParams<1>> reg0{ std::move(data), &fCounter, par0 };
				std::cout << "Overall function calls count: " << fCounter.Counter / (float)testLikelihood::nrolls << '\n';

				std::cout << "******IRegression With NelderMead test end*****\n\n";
			}

		};

	} // UnitTests
} // OptLib