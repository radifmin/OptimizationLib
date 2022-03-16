#pragma once
#include "stdafx.h"

namespace OptLib
{
	template<int dim>
	using PointAndVal = std::pair<Point<dim>, double>;

	namespace OptimizerInterface
	{
		template<int dim, typename func, typename state>
		class IOptimizerAlgorithm
		{
		public:
			IOptimizerAlgorithm(func* f_pointer, state* state_pointer) :
				f{ f_pointer }, state{ state_pointer } {	}

			virtual Point<dim> CurrentGuess() const { return state->guess(); }; // returns current guess
			PointAndVal<dim> CurrentPointAndVal() // returns the guess and the function value
			{
				Point<dim> p = CurrentGuess();
				return PointAndVal<dim>{p, f->operator()(p)};
			}

			virtual bool is_converged(double abs_tol, double rel_tol) const
			{
				return state->is_converged(abs_tol, rel_tol);
			}

			virtual PointAndVal<dim> proceed() = 0; // continue to next guess

		protected:
			func*  f; // function to optimize
			state* state; // state of the method
		};

		template<int dim>
		class IDirectAlgo : public IOptimizerAlgorithm<dim, FuncInterface::IFunc<dim>, ConcreteState::StateSimplex<dim>>
		{
		public:
			IDirectAlgo(FuncInterface::IFunc<dim>* f_pointer, ConcreteState::StateSimplex<dim>* state_pointer) :
				IOptimizerAlgorithm<dim, FuncInterface::IFunc<dim>, ConcreteState::StateSimplex<dim>>{ f_pointer, state_pointer } {}
			const Simplex<dim + 1, dim>& CurSimplex() const { return this->state->GuessDomain(); } // unique for direct methods
		};

		template<int dim>
		class IGradAlgo : public IOptimizerAlgorithm<dim, FuncInterface::IFuncWithGrad<dim>, ConcreteState::StatePoint<dim>>
		{

		};

		template<int dim>
		class IHessAlgo : public IOptimizerAlgorithm<dim, FuncInterface::IFuncWithHess<dim>, ConcreteState::StatePoint<dim>>
		{

		};

		template<int dim>
		class IStochasticAlgo : public IOptimizerAlgorithm<dim, FuncInterface::IFuncWithHess<dim>, ConcreteState::StateStochastic<dim>>
		{

		};
	} // OptimizerInterface
} // OptLib