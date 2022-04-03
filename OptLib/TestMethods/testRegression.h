#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace UnitTests
	{
		class testLikelihood
		{
			std::cout << "******LikelihoodLinear test start*****\n";


			ConcreteOptimizer::Bisection Algo{ new ConcreteFunc::FunctionWithHess{}, {{{-2}, {5}}} };
			std::cout << "Current simplex is:\n" << "  " << Algo.GuessDomain() << "\n";
			for (int i = 0; i < 10; i++)
			{
				Algo.Proceed();
				std::cout << "Current simplex is:\n" << "  " << Algo.GuessDomain() << "\n";
			}
			std::cout << "******LikelihoodLinear test end*******\n\n";
		};

		class testRegression
		{

		};
	} // UnitTests
} // OptLib