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
		double tol_f() { return Prm.eps_f; }
		double tol_x() { return Prm.eps_x; }
		int MaxIterCount() { return Prm.max_iter; }
		int CurIterCount() { return s; }
		PointVal<dim> CurrentGuess() { return Algo->CurrentPointAndVal(); }

	public:
		Optimizer(OptimizerInterface::IOptimizerAlgorithm<dim, func, state>* algo_pointer, OptimizerParams prm) :
			Prm{ prm },
			s{ 0 },
			Algo{ algo_pointer }{	}

		Point<dim> Optimize()
		{
			// TODO : separate thread
			bool f = false;
			while (!f &&
				s < MaxIterCount())
			{
				Algo->Proceed();
				s++;
				f = Algo->IsConverged(tol_x(), tol_x());
			}
			return CurrentGuess();
		}

		Point<dim> Continue(double eps_x, double eps_f)
		{
			Prm.eps_f = eps_f;
			Prm.eps_x = eps_x;
			return Optimize();
		}

	protected:
		OptimizerInterface::IOptimizerAlgorithm<dim, func, state>* Algo;
		int s; // current number of iterations
		OptimizerParams Prm;
	};
} // OptLib