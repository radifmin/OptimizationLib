#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteOptimizer
	{
		class Grid : public OptimizerInterface::
			ISimplexAlgo<1,StateInterface::IStateSimplex<1,SimplexValNoSort<1>>,SimplexValNoSort<1>>
		{
		public:
			int n;
			Grid(FuncInterface::IFunc<1>* f_pointer, SetOfPoints<1 + 1, Point<1>>&& setOfPoints, int n_):
				OptimizerInterface::ISimplexAlgo<1,StateInterface::IStateSimplex<1,SimplexValNoSort<1>>,SimplexValNoSort<1>>
				(f_pointer,std::move(setOfPoints)),n{n_}{}

			virtual PointVal<1> Proceed() override
			{
				double lengthOfStep = (state.GuessDomain().Points()[1][0] - state.GuessDomain().Points()[0][0])/ n;
				PointVal<1> res = state.GuessDomain().Points()[0];
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
