#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteState
	{
		/// <summary>
		/// Simplexes for direct methods on segments (in 1D) must not be sorted with respect to f(x). Must be sorted with respect to x == x[0]
		/// </summary>
		class StateGoldenSection : public StateSegment
		{
		public:
			SetOfPoints<4, PointVal<1>> AuxPoints{};
			double phi;
			double resphi;

			StateGoldenSection(SetOfPoints<2, Point<1>>&& State, FuncInterface::IFunc<1>* f)
				:
				StateSegment(std::move(State), f)
			{
				phi = (1 + std::sqrt(5)) / 2;
				resphi = 2 - phi;

				AuxPoints[0] = GuessDomain().Points()[0];
				AuxPoints[3] = GuessDomain().Points()[1];
				AuxPoints[1] = PointVal<1>::CreateFromPoint(AuxPoints[0].P + resphi * (AuxPoints[3].P - AuxPoints[0].P), f);
				AuxPoints[2] = PointVal<1>::CreateFromPoint(AuxPoints[3].P - resphi * (AuxPoints[3].P - AuxPoints[0].P), f);
			}
		};
	} // ConcreteOptimizer

	namespace ConcreteOptimizer
	{
		class GoldenSection
		{
		public:
			static PointVal<1> Proceed(ConcreteState::StateGoldenSection& State, const FuncInterface::IFunc<1>* f)
			{
				auto& AuxPoints = State.AuxPoints;

				if (AuxPoints[1].Val < AuxPoints[2].Val) {
					AuxPoints[3] = AuxPoints[2];
					AuxPoints[2] = AuxPoints[1];
					AuxPoints[1] = PointVal<1>::CreateFromPoint(AuxPoints[0].P + State.resphi * (AuxPoints[3].P - AuxPoints[0].P), f);
				}
				else {
					AuxPoints[0] = AuxPoints[1];
					AuxPoints[1] = AuxPoints[2];
					AuxPoints[2] = PointVal<1>::CreateFromPoint(AuxPoints[3].P - State.resphi * (AuxPoints[3].P - AuxPoints[0].P), f);
				}
				State.UpdateDomain({ AuxPoints[0], AuxPoints[3] });
				return State.Guess();
			}
		};
	} // Optimizer
} // OptLib
