#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace FuncParamInterface
	{
		template<size_t dimX, size_t dimP>
		class IFuncParam
		{
		public:
			virtual double operator() (const Point<dimX>& x, const Point<dimP>& a) const = 0;

			template<size_t count>
			Point<count> operator() (const SetOfPoints<count, Point<dimX>>& x, const Point<dimP>& a) const
			{
				std::array<double, count> out;
				for (int i = 0; i < count; i++)
					out[i] = this->operator()(x[i], a);
				return out;
			}
		};

		template<size_t dimX, size_t dimP>
		class IFuncParamWithGrad : public IFuncParam<dimX, dimP>
		{
		public:
			virtual Grad<dimX> GradP(const Point<dimX>& x, const Point<dimP>& a) const = 0;
		};
	} // FuncParamInterface
} // OptLib