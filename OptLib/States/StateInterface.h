#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace StateInterface
	{
		/// <summary>
		/// defines abstract basic functions, which are common for every type of state
		/// </summary>
		template<int dim>
		class IState
		{
		protected:
			Point<dim> its_guess;
		public:
			// concrete implementation depends on the order of optimization method
			virtual bool is_converged(double abs_tol, double rel_tol) const = 0;
			Point<dim> guess() const { return its_guess; };
		};
	} // StateInterface

} // OptLib