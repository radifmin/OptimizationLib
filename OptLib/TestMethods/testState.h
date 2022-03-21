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
			static void testStateDirect()
			{
				std::cout << "******StateSimplex test start*****\n";

				SetOfPoints<2, Point<2>> matrix{ { { {1,2}} , { {4,1}} } };
				ConcreteFunc::Paraboloid<2> f{ matrix };

				ConcreteState::StateDirect<2> state{ {{{0.0,0.0},{1.0,0.0},{0.0,1.0}}} , &f };
				std::cout << "The state simplex is     " << state.GuessDomain() << "\n";
				std::cout << "The state is converged:  " << state.IsConverged(0.01, 0.01) << "\n";

				state.SetDomain({ {{0.0,0.3},{2.0,1.5},{1.0,2.0}} }, &f);
				std::cout << "The new state simplex is " << state.GuessDomain() << "\n";
				std::cout << "The state is converged:  " << state.IsConverged(0.01, 0.01) << "\n";

				std::cout << "******StateSimplex test end*******\n\n";
			}

			static void testStateSegment()
			{
				std::cout << "******StateSegment test start*****\n";

				ConcreteFunc::Function f{};

				ConcreteState::StateSegment state{ {{{0.0},{1.0}}} , &f };
				std::cout << "The state simplex is     " << state.GuessDomain() << "\n";
				std::cout << "The state is converged:  " << state.IsConverged(0.01, 0.01) << "\n";

			//	SetOfPoints<2, Point<1>> ss{ { {-1.5},{2.0} } };
				
				state.SetDomain({ { {-7},{2.0} } }, &f);
				std::cout << "The new state simplex is " << state.GuessDomain() << "\n";
				std::cout << "The state is converged:  " << state.IsConverged(0.01, 0.01) << "\n";

				std::cout << "******StateSegment test end*******\n\n";
			}
		};
	} // UnitTests
} // OptLib