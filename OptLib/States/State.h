#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteState
	{
		/// <summary>
		/// Direct methods require sorted simplex points with respect to f(x)
		/// </summary>
		template<size_t dim>
		using StateDirect =  StateInterface::IStateSimplex<dim, SimplexValSort<dim>>;

		/// <summary>
		/// Simplexes for direct methods on segments (in 1D) must not be sorted with respect to f(x). Must be sorted with respect to x == x[0]
		/// </summary>
		class StateSegment : public StateInterface::IStateSimplex<1, SimplexValNoSort<1>>
		{
		public:
			StateSegment(const StateSegment&) = default;
			StateSegment(SetOfPoints<2, Point<1>>&& State, FuncInterface::IFunc<1>* f)
				:
				StateInterface::IStateSimplex<1, SimplexValNoSort<1>>(std::move(OrderPointsInSegment(State)), f)
			{}

		protected:
			SetOfPoints<2, Point<1>> OrderPointsInSegment(SetOfPoints<2, Point<1>>& setOfPoints)
			{
				if (setOfPoints[0][0] > setOfPoints[1][0])
					std::swap(setOfPoints[0], setOfPoints[1]);
				return setOfPoints;
			}
		};

		/// <summary>
		/// First and second order methods require only a point rather than entire simplex for optimization
		/// </summary>
		template<size_t dim>
		class StatePoint : public StateInterface::IState<dim>
		{

		};

		/// <summary>
		/// Stochastic methods require multiple initial points
		/// </summary>
		template<size_t dim>
		class StateStochastic : public StateInterface::IState<dim>
		{

		};
	} // ConcreteState
} // OptLib