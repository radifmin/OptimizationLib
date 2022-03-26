#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteOptimizer
	{
		template<int dim>
		class Grid : public OptimizerInterface::
			ISimplexAlgo<dim,StateInterface::IStateSimplex<dim,SimplexValNoSort<dim>>,SimplexValNoSort<dim>>
		{
		public:
			int n;
			Grid(FuncInterface::IFunc<dim>* f_pointer, SetOfPoints<dim + 1, Point<dim>>&& setOfPoints, int n_):
				OptimizerInterface::ISimplexAlgo<dim,StateInterface::IStateSimplex<dim,SimplexValNoSort<dim>>,SimplexValNoSort<dim>>
				(f_pointer,std::move(setOfPoints)),n{n_}{}

			virtual PointVal<dim> Proceed() override
			{
				double lengthOfStep = dist(state.GuessDomain().Points()[0], state.GuessDomain().Points()[1])/ n;
				PointVal<dim> res = state.GuessDomain().Points()[0];
				PointVal<dim> currentPoint = res;
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