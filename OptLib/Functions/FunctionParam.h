#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteFuncParam
	{
		class LinearFunc : public FuncParamInterface::IFuncParam<1, 1>
		{
		public:
			double operator() (const Point<1>& x, const Point<1>& a) const override
			{
				return x[0] * a[0];
			}
		};

		class LinearFuncWithGrad : public FuncParamInterface::IFuncParamWithGrad<1, 1>
		{
		public:
			double operator() (const Point<1>& x, const Point<1>& a) const override
			{
				return x[0] * a[0];
			}
			Grad<1> GradP(const Point<1>& x, const Point<1>& a) const override
			{
				return a;
			}
		};
	} // ConcreteFuncParam
} // OptLib