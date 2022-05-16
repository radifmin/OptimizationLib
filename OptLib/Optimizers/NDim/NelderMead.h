#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteState
	{
		/// <summary>
		/// Simplexes for direct methods on segments (in 1D) must not be sorted with respect to f(x). Must be sorted with respect to x == x[0]
		/// </summary>
		template<size_t dim>
		class StateNelderMead : public StateDirect<dim>
		{
		public:
			const double alpha;
			const double beta;
			const double gamma;

		public:
			StateNelderMead(SetOfPoints<dim+1, Point<dim>>&& State, FuncInterface::IFunc<dim>* f,
				double alpha_, double beta_, double gamma_) : StateDirect<dim>(std::move(State), f),
				alpha{ alpha_ }, beta{ beta_ }, gamma{ gamma_ }{};
		};
	} // ConcreteOptimizer

	namespace ConcreteOptimizer
	{
		template<size_t dim>
		class NelderMead
		{
		public:

			static PointVal<dim> Proceed(ConcreteState::StateNelderMead<dim>& State, const FuncInterface::IFunc<dim>* f)
			{
				double alpha = State.alpha;
				double beta = State.beta;
				double gamma = State.gamma;

				SetOfPoints<dim + 1, PointVal<dim>> NewSimplex = State.GuessDomain().Points();

				// auxillary points
				// they MUST be aliases for the concrete points in NewSimplex
				PointVal<dim>& xl = NewSimplex[0];
				PointVal<dim>& xh = NewSimplex[dim];
				PointVal<dim>& xg = NewSimplex[dim - 1];

				// simplex center excluding the point with the largest Val
				Point<dim> XC = NewSimplex[0].P;
				for (int i = 1; i < dim; i++)
					XC = XC + NewSimplex[i].P;
				PointVal<dim> xc{ FuncInterface::CreateFromPoint<dim>(std::move(XC / (dim - 0.0)), f) };

				// another auxillary point
				PointVal<dim> xr{ FuncInterface::CreateFromPoint<dim>(std::move(xc.P * (1.0 + alpha) - xh.P * alpha), f) };

				if (xr.Val < xl.Val)
				{
					// try to slightly improve the xr value calculating xe
					PointVal<dim> xe{ FuncInterface::CreateFromPoint<dim>(std::move(xc * (1.0 - gamma) + xr * gamma), f) };
					if (xe.Val < xr.Val)
						xh = xe;
					else
						xh = xr;
					State.SetDomain(std::move(NewSimplex));
					return State.Guess();
				}

				if (xr.Val < xg.Val)
				{
					xh = xr;
					State.SetDomain(std::move(NewSimplex));
					return State.Guess();
				}

				if (xr.Val < xh.Val) xh = xr; // std::swap(xr, xh);

				PointVal<dim> xs{ FuncInterface::CreateFromPoint<dim>(std::move(xh.P * beta + xc.P * (1 - beta)), f) };
				if (xs.Val < xh.Val)
				{
					xh = xs;
					State.SetDomain(std::move(NewSimplex));
					return State.Guess();
				}

				State.UpdateDomain(SqueezeSimplex(xl.P, NewSimplex), f);
				return State.Guess();
				}
			    
		protected:
			static auto SqueezeSimplex(const Point<dim>& xl, const SetOfPoints<dim + 1, PointVal<dim>>& Simplex)
			{
				SetOfPoints<dim + 1, Point<dim>> NewSimplex;

				for (int i = 0; i < dim + 1; i++)
					NewSimplex[i] = Point<dim>{ std::move(xl + (Simplex[i].P - xl) / 2.0) };

				return NewSimplex;
			}
		};
	}//ConcreteOptimizer

	namespace StateParams
	{
		template< size_t dim>
		struct NelderMeadParams
		{
		public:
			using OptAlgo = OptLib::ConcreteOptimizer::NelderMead<dim>;
			using StateType = ConcreteState::StateNelderMead<dim>;

		public:
			SetOfPoints<dim + 1, Point<dim>> StartSimplex;
			NelderMeadParams(SetOfPoints<dim+1, Point<dim>>&& sop, double alpha_, double beta_, double gamma_)
				:StartSimplex{ std::move(sop) },
				alpha{ alpha_ }, beta{ beta_ }, gamma{ gamma_ }
			{}
			StateType CreateState(FuncInterface::IFunc<1>* f)
			{
				return { std::move(StartSimplex), f, alpha, beta, gamma };
			}

		protected:
			double alpha;
			double beta;
			double gamma;
		};
	} // StateParams
}//OptLib