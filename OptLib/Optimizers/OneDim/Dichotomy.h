#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteState
	{
		/// <summary>
		/// Simplexes for direct methods on segments (in 1D) must not be sorted with respect to f(x). Must be sorted with respect to x == x[0]
		/// </summary>
		using  StateDichotomy = StateSegment;

	} // ConcreteOptimizer

	namespace ConcreteOptimizer
	{
		class Dichotomy
		{
		public:
			static PointVal<1> Proceed(ConcreteState::StateDichotomy& State, const FuncInterface::IFunc<1>* f)
			{
				const PointVal<1>& a = State.GuessDomain().Points()[0];
				const PointVal<1>& b = State.GuessDomain().Points()[1];

				Point<1> _e{ (b.P - a.P) / 4 };

				Point<1> c{ State.GuessDomain().Mean().P };

				PointVal<1> x1{ FuncInterface::CreateFromPoint<1>(c - _e, f) };
				PointVal<1> x2{ FuncInterface::CreateFromPoint<1>(c + _e, f) };

				SetOfPoints<2, PointVal<1>> newSet;
				if (x1.Val < x2.Val)
				{
					newSet[0] = a;
					newSet[1] = x2;
				}
				else
				{
					newSet[0] = x1;
					newSet[1] = b;
				}
				State.UpdateDomain(std::move(newSet));
				return State.Guess();
			}
		};
	} // ConcreteOptimizer

	namespace StateParams
	{
		struct DichotomyParams
		{
		public:
			using OptAlgo = OptLib::ConcreteOptimizer::Dichotomy;
			using StateType = ConcreteState::StateDichotomy;

		public:
			SetOfPoints<2, Point<1>> StartSegment;
			DichotomyParams(SetOfPoints<2, Point<1>>&& sop)
				:StartSegment{ std::move(sop) }
			{}
			StateType CreateState(FuncInterface::IFunc<1>* f)
			{
				return { std::move(StartSegment), f };
			}
		};
	} // StateParams
} // OptLib
