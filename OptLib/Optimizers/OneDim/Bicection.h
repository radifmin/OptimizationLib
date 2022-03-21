#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteOptimizer
	{
		using namespace AuxMethods;
		class Bicection : public OptimizerInterface::ISegmentAlgo
		{
			SetOfPoints<5, PointVal<1>> AuxPoints;
		public:
			Bicection(FuncInterface::IFunc<1>* f_pointer, SetOfPoints<2, Point<1>>&& setOfPoints) :
				OptimizerInterface::ISegmentAlgo{ f_pointer, std::move(setOfPoints) }
			{
				AuxPoints[0] = state.GuessDomain().Simplex()[0];
				AuxPoints[4] = state.GuessDomain().Simplex()[1];

				double step = (AuxPoints[4].P[0] - AuxPoints[0].P[0]) / 4.0;

				for (int i = 1; i < 4; i++)
				{
					Point<1> x{ AuxPoints[i - 1].P[0] + step };
					AuxPoints[i] = PointVal{ std::move(x), f->operator()(x) };
				}
			}
		public:
			virtual PointVal<1> Proceed() override
			{
				SetOfPoints<5, PointVal<1>>::iterator min = std::min_element(AuxPoints.begin(), AuxPoints.end());
				size_t pos = std::distance(AuxPoints.begin(), min);

				if (pos == 0)
				{// keep AuxPoints[0]
					AuxPoints[4] = AuxPoints[1];
					temp2();
				}
				else if (pos == AuxPoints.size() - 1)
				{// keep AuxPoints[4]
					AuxPoints[0] = AuxPoints[3];
					temp2();
				}
				else if(pos == 1)
				{
					AuxPoints[4] = AuxPoints[2];
					AuxPoints[2] = AuxPoints[1];
				//	AuxPoints[0] = AuxPoints[0];
					temp1();
				}
				else if (pos == 2)
				{
					AuxPoints[0] = AuxPoints[1];
				//	AuxPoints[2] = AuxPoints[2];
					AuxPoints[4] = AuxPoints[3];
					temp1();
				}
				else
				{
					AuxPoints[0] = AuxPoints[2];
					AuxPoints[2] = AuxPoints[3];
				//	AuxPoints[4] = AuxPoints[4];
					temp1();
				}

				SetOfPoints<2, PointVal<1>> D{ AuxPoints[0], AuxPoints.back() };

				state.UpdateDomain({ AuxPoints[0], AuxPoints.back() });
				//			state = new ConcreteState::StateSimplex<1>{new_simplex};
				return state.Guess();
			}

		protected:
			void temp1()
			{
				double step = (AuxPoints[4].P[0] - AuxPoints[0].P[0]) / 4.0;
				Point<1> x{ AuxPoints[0].P[0] + step };
				AuxPoints[1] = PointVal{ std::move(x), f->operator()(x) };
				x = Point<1>{ AuxPoints[2].P[0] + step };
				AuxPoints[3] = PointVal{ std::move(x), f->operator()(x) };
			}
			void temp2()
			{
				double step = (AuxPoints[4].P[0] - AuxPoints[0].P[0]) / 4.0;
				for (int i = 1; i < 4; i++)
				{
					Point<1> x{ AuxPoints[i - 1].P[0] + step };
					AuxPoints[i] = PointVal{ std::move(x), f->operator()(x) };
				}
			}
		};
	} // Optimizer
} // OptLib