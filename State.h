#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteState
	{
		/// <summary>
		/// State for direct methods of optimization
		/// </summary>
		template<int dim>
		class StateSimplex : public StateInterface::IState<dim>
		{
			using StateInterface::IState<dim>::its_guess;
		public: // overriden from predecessor
			virtual bool is_converged(double abs_tol, double rel_tol) const override
			{// ie average and relative tolerance met?
				auto [avg, disp] = AuxMethods::dispersion(GuessDomain());
				Point<dim> var{ AuxMethods::var_coef(avg, disp) };
				for (int i = 0; i < dim; i++)
				{
					bool f = ((abs(avg[i]) < abs_tol) || (var[i] < rel_tol));
					if (!f) return false;
				}
				return true;
			}

		protected:
			Simplex<dim + 1, dim> its_guess_domain; // unique for direct optimization methods
		public:
			StateSimplex(const Simplex<dim + 1, dim>& state) : its_guess_domain{ state }
			{
				its_guess = AuxMethods::mean(GuessDomain());
			}
			const Simplex<dim + 1, dim>& GuessDomain() const { return its_guess_domain; } // unique for direct optimization methods
			void SetDomain(Simplex<dim + 1, dim>&& state) { its_guess_domain = state; its_guess = AuxMethods::mean(GuessDomain()); }
		};

		/// <summary>
		/// First and second order methods require only a point rather than entire simplex for optimization
		/// </summary>
		template<int dim>
		class StatePoint : public StateInterface::IState<dim>
		{

		};

		/// <summary>
		/// Stochastic methods require multiple initial points
		/// </summary>
		template<int dim>
		class StateStochastic : public StateInterface::IState<dim>
		{

		};
	} // ConcreteState

} // OptLib