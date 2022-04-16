#pragma once
#include "stdafx.h"
namespace OptLib
{
	namespace ConcreteOptimizer
	{
		template<size_t dim>
		class NelderMead : public OptimizerInterface::IDirectAlgo<dim>
		{
		protected:
			double alpha;
			double beta;
			double gamma;
		public:
			NelderMead(FuncInterface::IFunc<dim>* f_pointer, SetOfPoints<dim + 1, Point<dim>>&& setOfPoints,
				double alpha_, double beta_, double gamma_) :
				OptimizerInterface::IDirectAlgo<dim>
			{ f_pointer, std::move(setOfPoints) }, alpha{ alpha_ }, beta{ beta_ }, gamma{ gamma_ } {}

			virtual PointVal<dim> Proceed() override
			{
				SetOfPoints<dim + 1, PointVal<dim>> NewSimplex = State.GuessDomain().Points();

				// auxillary points
				// they MUST be aliases for the concrete points in NewSimplex
				PointVal<dim>& xl = NewSimplex[0];
				PointVal<dim>& xh = NewSimplex[dim];
				PointVal<dim>& xg = NewSimplex[dim - 1];
				Point<dim> XC = NewSimplex[0].P;

				// simplex center excluding the point with the largest Val
				for (int i = 1; i < dim; i++)
					XC = XC + NewSimplex[i].P;
				PointVal<dim> xc{ PointVal<dim>::CreateFromPoint(std::move(XC / (dim - 0.0)), f) };

				// another auxillary point
				PointVal<dim> xr{ PointVal<dim>::CreateFromPoint(std::move(xc.P * (1.0 + alpha) - xh.P * alpha), f) };

				if (xr.Val < xl.Val)
				{
					// try to slightly improve the xr value calculating xe
					PointVal<dim> xe{ PointVal<dim>::CreateFromPoint(std::move(xc * (1.0 - gamma) + xr * gamma), f) };
					if (xe.Val < xr.Val)
						xh = xe;
					else
						xh = xr;

					State.UpdateDomain(std::move(NewSimplex));
					return State.Guess();
				}

				if (xr.Val < xg.Val)
				{
					xh = xr;
					State.UpdateDomain(std::move(NewSimplex));
					return State.Guess();
				}

				if (xr.Val < xh.Val) std::swap(xr, xh);

				PointVal<dim> xs = PointVal<dim>::CreateFromPoint(std::move(xh.P * beta + xc.P * (1 - beta)), f);
				if (xs.Val < xh.Val)
				{
					xh = xs;
					State.UpdateDomain(std::move(NewSimplex));
					return State.Guess();
				}

				SqueeseSimplex(xl.P, NewSimplex);
				return State.Guess();
			}

		protected:
			void SqueeseSimplex(const Point<dim>& xl, const SetOfPoints<dim + 1, PointVal<dim>>& Simplex)
			{
				SetOfPoints<dim + 1, Point<dim>> NewSimplex;

				for (int i = 0; i < dim + 1; i++)
					NewSimplex[i] = Point<dim>{ std::move(xl + (Simplex[i].P - xl) / 2.0) };

				State.SetDomain(std::move(NewSimplex), this->f);
			}
		};
	}//ConcreteOptimizer
}//OptLib