#pragma once
#include "stdafx.h"

namespace OptLib
{
	struct OptimizerParams
	{
		double eps_f, eps_x;
		int max_iter;
	};

	template<size_t dim, 
		typename state, 
		template<size_t dim> typename func>
	class Optimizer
	{
	public:
		double tol_f() { return Prm.eps_f; }
		double tol_x() { return Prm.eps_x; }
		int MaxIterCount() { return Prm.max_iter; }
		int CurIterCount() { return s; }
		PointVal<dim> CurrentGuess() { return State->Guess(); }

	public:
		Optimizer(state* State_, func<dim>* f_, OptimizerParams prm) :
			State{State_},
			f{f_},
			Prm{ prm },
			s{ 0 }{}

		template<typename algo>
		PointVal<dim> Optimize()
		{
			// TODO : separate thread
			bool g = false;
			while (!g &&
				s < MaxIterCount())
			{
				OptimizerInterface::OptimizerAlgorithm<dim>::Proceed<algo, state, func>(State, f);
				s++;
				g = OptimizerInterface::OptimizerAlgorithm<dim>::IsConverged(State, tol_x(), tol_x());
			}
			return CurrentGuess();
		}

		template<typename algo>
		PointVal<dim> Continue(double eps_x, double eps_f)
		{
			Prm.eps_f = eps_f;
			Prm.eps_x = eps_x;
			return Optimize<algo>();
		}

	protected:
		state* State;
		func<dim>* f;

		int s; // current number of iterations
		OptimizerParams Prm;
	};

	template<size_t dim,
		typename state,
		template<size_t dim> typename func>
	class Optimizer1Step
	{
	protected:
		state* State;
		func<dim>* f;
	public:
		Optimizer1Step(state* State_, func<dim>* f_) :
			State{ State_ },
			f{ f_ }{}
		PointVal<dim> CurrentGuess() { return State->Guess(); }

		template<typename algo>
		PointVal<dim> Optimize()
		{
			OptimizerInterface::OptimizerAlgorithm<dim>::Proceed<algo, state, func>(State, f);
			return CurrentGuess();
		}
	};
} // OptLib
