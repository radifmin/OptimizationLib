#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteState
	{
		/// <summary>
		/// Simplexes for direct methods on segments (in 1D) must not be sorted with respect to f(x). Must be sorted with respect to x == x[0]
		/// </summary>
		class StateGrid : public StateSegment
		{
		public:
			const int n;
			StateGrid(SetOfPoints<2, Point<1>>&& State, FuncInterface::IFunc<1>* f, int n_) : StateSegment(std::move(State), f), n{ n_ }{};

			void SetGuess(const PointVal<1>& v) { ItsGuess = v; }
		};
	} // ConcreteOptimizer

	namespace ConcreteOptimizer
	{
		class Grid 
		{
		public:
			static PointVal<1> Proceed(ConcreteState::StateGrid& State, const FuncInterface::IFunc<1>* f)
			{
				int n = State.n;
				Point<1> step = (State.GuessDomain().Points()[1] - State.GuessDomain().Points()[0]) / n;
				PointVal<1> res = State.GuessDomain().Points()[0];
				PointVal<1> currentPoint = res;
				for(int i = 1; i < n; i++)
				{
					currentPoint = PointVal<1>::CreateFromPoint(currentPoint.P + step, f);
					if(currentPoint < res )
						res = currentPoint;
				}

				State.SetGuess(res);
				return res;
			}
		};
	} // Optimizer
} // OptLib
