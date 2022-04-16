#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteReg
	{
		/// <summary>
		/// Operations for linear regression
		/// </summary>
		struct Linear
		{
			static double zero() { return 0.0; }
			double operator()(double prev, double y, double f) const { return prev + term(y, f); }

			template<size_t dimP>
			Point<dimP> Dterm(double y, double f, const Point<dimP>& df) const
			{
				return 2.0 * (f - y) * df;
			}

		protected:
			double term(double y, double f) const
			{
				return std::pow(f - y, 2.0);
			}

			/*template<size_t dimP>
			Hess<dimP> DDterm(double y, double f, const Point<dimP>& df, const Hess<dimP>& ddf) const
			{
				return 2.0 * (f - y) * df;
			}*/
		};

		/// <summary>
		/// Operations for logistic regression
		/// </summary>
		struct Logistic
		{
			static double zero() { return 1.0; }
			double operator()  (double prev, double y, double f) const
			{
				return prev * term(y, f);
			}
		protected:
			double term(double y, double f) const
			{
				double t = Sigmoid(f);
				if (y == 0.0) t = 1 - t;
				return t;
			}
			static double Sigmoid(double x) { return 1.0 / (1.0 + std::exp(-x)); }
		};

		/// <summary>
		/// Operations for log-logistic regression
		/// </summary>
		struct LogLogistic : public Logistic
		{
			static double zero() { return 0.0; }
			double operator()  (double prev, double y, double f) const
			{
				return prev + std::log(term(y,f));
			}

		};

		template<size_t dimX, size_t dimP, template <size_t dimX, size_t dimP> typename funcP>
		using LikelihoodLinear = RegInterface::ILikelihoodFunc<dimX, dimP, funcP, Linear>;

		template<size_t dimX, size_t dimP, template <size_t dimX, size_t dimP> typename funcP>
		using LikelihoodLinearWithGrad = RegInterface::ILikelihoodFuncWithGrad<dimX, dimP, funcP, LikelihoodLinear>;

		template<size_t dimX, size_t dimP, template <size_t dimX, size_t dimP> typename funcP>
		using LikelihoodLogistic = RegInterface::ILikelihoodFunc<dimX, dimP, funcP, LogLogistic>;

	} // ConcreteReg
} // OptLib