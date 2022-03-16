#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace FuncInterface
	{
		template <int dim>
		class IFunc
		{ // direct methods only call the function calculation
		public:
			virtual double operator () (const Point<dim>& x) const = 0;
		};

		template <int dim>
		class IGrad
		{
		public:
			virtual Point<dim> grad(const Point<dim>& x) const = 0;
		};

		template <int dim>
		class IHess
		{
		public:
			virtual std::array<Point<dim>, dim> hess(const std::array<double, dim>& x) const = 0;
		};

		template <int dim>
		class IFuncWithGrad :public IFunc<dim>, public IGrad<dim>
		{ }; // 1st order optimization methods require the function itself and the gradient

		template <int dim>
		class IFuncWithHess :public IFuncWithGrad<dim>, public IHess<dim>
		{ }; // 2nd order methods --- function, gradient, and hessian

	} // FuncInterface
} // OptLib