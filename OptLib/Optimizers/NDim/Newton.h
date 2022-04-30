#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteState
	{
		template<size_t dim>
		class StateNewton :public ConcreteState::StatePoint<dim>
		{
		public:
			StateNewton(Point<dim>&& x0, const FuncInterface::IFuncWithHess<dim>* f)
			{
				ItsGuess = PointVal<dim>::CreateFromPoint(std::move(x0), f);
			}
		};

	} // ConcreteState

	namespace ConcreteOptimizer
	{
		template <size_t dim>
		class Newton
		{
		protected:
			static Point<dim> GaussSolver(Hess<dim> A, Grad<dim> B)
			{
				// forward loop
				for (int i = 0; i < dim; i++)
				{
					for (int j = i + 1; j < dim; j++)
					{
						double ratio = A[j][i] / A[i][i];
						A[j] = A[j] - ratio * A[i];
						B[j] = B[j] - ratio * B[i];
					}
				}
				// make diagonal of ones
				for (int i = 0; i < dim; i++)
				{
					B[i] = B[i] / A[i][i];
					A[i] = A[i] / A[i][i];
				}
				// backward loop
				for (int i = dim - 1; i > -1; i--)
				{
					for (int j = i + 1; j < dim; j++)
					{
						double ratio = A[i][j] / A[j][j];
						A[i] = A[i] - A[j] * ratio;
						B[i] = B[i] - ratio * B[j];
					}
				}
				return B;
			}
			
		public:
			static PointVal<dim> Proceed(ConcreteState::StateNewton<dim>& State, const FuncInterface::IFuncWithHess<dim>* f)
			{
				const auto& g = State.Guess();
				Point<dim> dx{ GaussSolver(f->hess(g.P), -1* f->grad(g.P)) };

				State.SetGuess(PointVal<dim>::CreateFromPoint(g.P + dx, f));
				return State.Guess();
			}
		};
	} // ConcreteOptimizer

	namespace StateParams
	{
		template< size_t dim>
		struct NewtonParams
		{
		public:
			using OptAlgo = OptLib::ConcreteOptimizer::Newton<dim>;
			using StateType = ConcreteState::StateNewton<dim>;

		public:
			Point<dim> StartPoint;
			NewtonParams(Point<dim>&& sop)
				:StartPoint{ std::move(sop) }
			{}
			StateType CreateState(FuncInterface::IFuncWithHess<1>* f)
			{
				return { std::move(StartPoint), f };
			}
		};
	} // StateParams
} // OptLib