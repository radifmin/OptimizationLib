#pragma once
#include "stdafx.h"

namespace OptLib
{
	struct OptimizerParams
	{
		double eps_f, eps_x;
		int max_iter;
	};

	template<int dim, typename func, typename state>
	class Optimizer
	{
	public:
		double tol_f() { return prm.eps_f; }
		double tol_x() { return prm.eps_x; }
		int max_iter_count() { return prm.max_iter; }
		int cur_iter_count() { return s; }
		Point<dim> CurrentGuess() { return algo->CurrentGuess(); }

	public:
		Optimizer(IOptimizerAlgorithm<dim>* algo_pointer, OptimizerParams _prm) :
			prm{ _prm },
			s{ 0 },
			algo{ algo_pointer }{	}

		Point<dim> Optimize()
		{
			// TODO : separate thread
			bool f = false;
			while (!f &&
				s < max_iter_count())
			{
				algo->proceed();
				s++;
				f = algo->is_converged(tol_x(), tol_x());
			}
			return CurrentGuess();
		}

		Point<dim> Continue(double eps_x, double eps_f)
		{
			prm.eps_f = eps_f;
			prm.eps_x = eps_x;
			return Optimize();
		}

	protected:
		std::unique_ptr<IOptimizerAlgorithm<dim>, func, state> algo;
		int s; // current number of iterations
		OptimizerParams prm;
	};

} // OptLib