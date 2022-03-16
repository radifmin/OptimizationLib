#pragma once
#include "stdafx.h"


namespace OptLib
{
	namespace UnitTests
	{
		using namespace AuxMethods;

		class testState
		{
		public:
			static void testStateSimplex()
			{
				std::cout << "******StateSimplex test start*****\n";

				ConcreteState::StateSimplex<2> state{ {{{0.0,0.0},{1.0,0.0},{0.0,1.0}}} };
				std::cout << "The state simplex is     " << state.GuessDomain() << "\n";
				std::cout << "The state is converged:  " << state.is_converged(0.01, 0.01) << "\n";
				state.SetDomain({ {{0.0,0.0},{2.0,0.0},{0.0,2.0}} });
				std::cout << "The new state simplex is " << state.GuessDomain() << "\n";
				std::cout << "The state is converged:  " << state.is_converged(0.01, 0.01) << "\n";

				std::cout << "******StateSimplex test end*******\n\n";
			}

		};
	} // UnitTests
} // OptLib