#pragma once
#include "stdafx.h"


namespace OptLib
{
	namespace UnitTests
	{
		class testState
		{
		public:
			static void testStateDirect()
			{
				std::cout << "******StateSimplex test start*****\n";

				SetOfPoints<2, Point<2>> matrix{ { { {1,2}} , { {4,1}} } };
				ConcreteFunc::Paraboloid<2> f{ matrix };

				ConcreteState::StateDirect<2> State{ {{{0.0,0.0},{1.0,0.0},{0.0,1.0}}} , &f };
				std::cout << "The state simplex is     " << State.GuessDomain() << "\n";
				std::cout << "The state is converged:  " << State.IsConverged(0.01, 0.01) << "\n";

				State.UpdateDomain({ {{0.0,0.3},{2.0,1.5},{1.0,2.0}} }, &f);
				std::cout << "The new state simplex is " << State.GuessDomain() << "\n";
				std::cout << "The state is converged:  " << State.IsConverged(0.01, 0.01) << "\n";

				std::cout << "******StateSimplex test end*******\n\n";
			}

			static void testStateSegment()
			{
				std::cout << "******StateSegment test start*****\n";

				ConcreteFunc::Function f{};

				ConcreteState::StateSegment State{ {0.0,1.0} , &f };
				std::cout << "The state simplex is     " << State.GuessDomain() << "\n";
				std::cout << "The state is converged:  " << State.IsConverged(0.01, 0.01) << "\n";

				State.UpdateDomain({ -7,2.0 }, &f);
				std::cout << "The new state simplex is " << State.GuessDomain() << "\n";
				std::cout << "The state is converged:  " << State.IsConverged(0.01, 0.01) << "\n";

				std::cout << "******StateSegment test end*******\n\n";
			}

			static void testStatePointImproved()
			{
				std::cout << "******StatePointImproved test start*****\n";

				SetOfPoints<2, Point<2>> matrix{ { { {1,2}} , { {4,1}} } };
				ConcreteFunc::Paraboloid<2> f{ matrix };

				Point<2> x{ 0.0, 0.0 }, y;
				y = x + Point<2>{0.1, 0.1};
				ConcreteState::StateNewton<2> State{ std::move(x) , &f };

				StateWithMemory::StatePointImproved<2> mState{ &State };
				mState.UpdateState(FuncInterface::CreateFromPoint<2>(std::move(y), &f));

				std::cout << "******StatePointImproved test end*******\n\n";
			}

			static void testStateSimplexImproved()
			{
				std::cout << "******StateSimplexImproved test start*****\n";

				SetOfPoints<2, Point<2>> matrix{ { { {1,2}} , { {4,1}} } };
				ConcreteFunc::Paraboloid<2> f{ matrix };

				Point<2> x{ 0.0, 0.0 }, y{ 1.1, 1.2 }, z{ 2 * x - 3 * y };
				ConcreteState::StateDirect<2> State{ SetOfPoints<3, Point<2>>{ x,y,z } ,& f };

				StateWithMemory::StateSimplexMemory<2, ConcreteState::StateDirect<2>> 
					mState{ &State, &f };

				mState.UpdateDomain(SetOfPoints<3, Point<2>>{ x, 1.5 * y, z }, &f);

				std::cout << "******StateSimplexImproved test end*******\n\n";
			}
		};
	} // UnitTests
} // OptLib