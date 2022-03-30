#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteOptimizer
	{
		class Grid : public OptimizerInterface::ISegmentAlgo
		{
		public:
			int n;
			Grid(FuncInterface::IFunc<1>* f_pointer, SetOfPoints<2, Point<1>>&& setOfPoints, int n_):
				OptimizerInterface::ISegmentAlgo(f_pointer,std::move(setOfPoints)),n{n_}{}

			virtual PointVal<1> Proceed() override
			{
				double lengthOfStep = (State.GuessDomain().Points()[1][0] - State.GuessDomain().Points()[0][0])/ n;
				PointVal<1> res = State.GuessDomain().Points()[0];
				PointVal<1> currentPoint = res;
				for(int i = 0; i < n; i++)
				{
					currentPoint = currentPoint + lengthOfStep;
					currentPoint.Val = f->operator()(currentPoint);
					if(currentPoint < res )
					{
						res = currentPoint;
					}
				}
				return res;
			}
		};
	} // Optimizer
} // OptLib
