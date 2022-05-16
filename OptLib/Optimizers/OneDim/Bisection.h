#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteState
	{
		/// <summary>
		/// Simplexes for direct methods on segments (in 1D) must not be sorted with respect to f(x). Must be sorted with respect to x == x[0]
		/// </summary>
		class StateBisection : public StateSegment
		{
		public:
			SetOfPoints<5, PointVal<1>> AuxPoints;

			StateBisection(SetOfPoints<2, Point<1>>&& State, FuncInterface::IFunc<1>* f)
				:
				StateSegment(std::move(State), f)
			{
				AuxPoints[0] = this->GuessDomain().Points()[0];
				AuxPoints[4] = this->GuessDomain().Points()[1];

				double step = (AuxPoints[4].P[0] - AuxPoints[0].P[0]) / 4.0;

				for (size_t i = 1; i < 4; i++)
				{
					Point<1> x{ AuxPoints[i - 1].P[0] + step };
					AuxPoints[i] = PointVal{ x, f->operator()(x) };
				}
			}
		};
	} // ConcreteOptimizer

	namespace ConcreteOptimizer
	{
		class Bisection
		{
		public:
			static PointVal<1> Proceed(ConcreteState::StateBisection& State, const FuncInterface::IFunc<1>* f)
			{
				SetOfPoints<5, PointVal<1>>& AuxPoints = State.AuxPoints;

				SetOfPoints<5, PointVal<1>>::iterator min = std::min_element(AuxPoints.begin(), AuxPoints.end());
				size_t pos = std::distance(AuxPoints.begin(), min);

				if (pos == 0)
				{// keep AuxPoints[0]
					AuxPoints[4] = AuxPoints[1];
					temp2(State, f);
				}
				else if (pos == AuxPoints.size() - 1)
				{// keep AuxPoints[4]
					AuxPoints[0] = AuxPoints[3];
					temp2(State, f);
				}
				else if(pos == 1)
				{
					AuxPoints[4] = AuxPoints[2];
					AuxPoints[2] = AuxPoints[1];
				//	AuxPoints[0] = AuxPoints[0];
					temp1(State, f);
				}
				else if (pos == 2)
				{
					AuxPoints[0] = AuxPoints[1];
				//	AuxPoints[2] = AuxPoints[2];
					AuxPoints[4] = AuxPoints[3];
					temp1(State, f);
				}
				else
				{
					AuxPoints[0] = AuxPoints[2];
					AuxPoints[2] = AuxPoints[3];
				//	AuxPoints[4] = AuxPoints[4];
					temp1(State, f);
				}
				State.SetDomain({ AuxPoints[0], AuxPoints[4]});
				return State.Guess();
			}

		protected:
			static void temp1(ConcreteState::StateBisection& State, const FuncInterface::IFunc<1>* f)
			{
				SetOfPoints<5, PointVal<1>>& AuxPoints = State.AuxPoints;

				double step = (AuxPoints[4].P[0] - AuxPoints[0].P[0]) / 4.0;
				Point<1> x{ AuxPoints[0].P[0] + step };
				AuxPoints[1] = PointVal{ x, (*f)(x) };
				x = Point<1>{ AuxPoints[2].P[0] + step };
				AuxPoints[3] = PointVal{ x, (*f)(x) };
			}
			static void temp2(ConcreteState::StateBisection& State, const FuncInterface::IFunc<1>* f)
			{
				SetOfPoints<5, PointVal<1>>& AuxPoints = State.AuxPoints;

				double step = (AuxPoints[4].P[0] - AuxPoints[0].P[0]) / 4.0;
				for (size_t i = 1; i < 4; i++)
				{
					Point<1> x{ AuxPoints[i - 1].P[0] + step };
					AuxPoints[i] = PointVal{ x, (*f)(x) };
				}
			}
		};
	} // Optimizer

	namespace StateParams
	{
		struct BisectionParams
		{
		public:
			using OptAlgo = OptLib::ConcreteOptimizer::Bisection;
			using StateType = OptLib::ConcreteState::StateBisection;

		public:
			SetOfPoints<2, Point<1>> StartSegment;
			BisectionParams(SetOfPoints<2, Point<1>>&& sop)
				:StartSegment{ std::move(sop) }
			{}
			StateType CreateState(FuncInterface::IFunc<1>* f)
			{
				return { std::move(StartSegment), f };
			}
		};
	} // StateParams

} // OptLib