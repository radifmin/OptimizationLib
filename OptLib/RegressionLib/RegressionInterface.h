#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace RegInterface
	{
		/// <summary>
		/// Operations for linear regression
		/// </summary>
		struct Linear
		{
			static double zero() { return 0.0; }
			double operator()(double prev, double y, double f) { return prev + std::pow(f - y, 2.0); }
		};

		/// <summary>
		/// Operations for logistic regression
		/// </summary>
		struct Logistic
		{
			static double zero() { return 1.0; }
			double operator()(double prev, double y, double f)
			{
				double term;
				if (y == 1.0) term = Sigmoid(f);
				else term = 1 - Sigmoid(f);
				return prev * term;
			}
		private:
			static double Sigmoid(double x) { return 1.0 / (1.0 + std::exp(-x)); }
		};

		/// <summary>
		/// Data for regression. A vector of {P, Val}
		/// </summary>
		template<size_t dimX, template<size_t dimX> typename point = PointVal>
		using DataSet = std::vector<point<dimX>>;

		template<size_t dimX, size_t dimP, template <size_t dimP> typename func, template <size_t dimX, size_t dimP> typename funcP, typename bin_op>
		class ILikelihoodFunc : public func<dimP>
		{
		protected:
			DataSet<dimX, Point> Data;
			funcP<dimX, dimP>* f;
		//	bin_op op;

		public:
			ILikelihoodFunc(DataSet<dimX, Point>&& data, FuncParamInterface::IFuncParam<dimX, dimP>* f_pointer) : Data<dimX, Point>{ std::move(data), f{f_pointer} } {}

			double operator() (const Point<dimP>& a) const override
			{
				double s = bin_op::zero();
				for (int i = 0; i < Data.size(); i++)
					s = bin_op(s, Data[i].Val, f->operator()(Data[i].P, a));
				return s;
			}
		};

		template<size_t dimX, size_t dimP, template <size_t dimP> typename func, template <size_t dimX, size_t dimP> typename funcP>
		using LikelihoodLinear = ILikelihoodFunc<dimX, dimP, func, funcP, Linear>;

		template<size_t dimX, size_t dimP, template <size_t dimP> typename func, template <size_t dimX, size_t dimP> typename funcP>
		using LikelihoodLogistic = ILikelihoodFunc<dimX, dimP, func, funcP, Logistic>;



		/// <summary>
		/// func template --- smotthness of Likelihood function
		/// </summary>
	/*	template<size_t dimX, size_t dimP, template <size_t dimP> typename func, template <size_t dimX, size_t dimP> typename funcP>
		class IRegression
		{
		protected:
			ILikelihoodFunc<dimX, dimP, func, funcP> L;

		public:

			double Likelihood(const Point<dimP>& a) { return L(a); }


		};*/

	} // RegInterface
} // OptLib