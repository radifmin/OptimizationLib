#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace RegInterface
	{
		/// <summary>
		/// Data for regression. A vector of {P, Val}
		/// </summary>
		template<size_t dimX, template<size_t dimX> typename point = PointVal>
		using DataSet = std::vector<point<dimX>>;

		template<size_t dimX, size_t dimP, typename funcP, typename bin_op>
		class ILikelihoodFunc : public FuncInterface::IFunc<dimP>
		{
		public:
			const funcP* f;
			const bin_op op;
		protected:

		public:
			const DataSet<dimX> Data;

			ILikelihoodFunc(DataSet<dimX>&& data, funcP* f_pointer) : Data{ std::move(data) }, f{ f_pointer } {}

			double operator() (const Point<dimP>& a) const override
			{
				double s = bin_op::zero();
				for (int i = 0; i < Data.size(); i++)
					s = op(s, Data[i].Val, f->operator()(Data[i].P, a));
				return s;
			}
		};

		template<size_t dimX, size_t dimP, 
			typename funcP, 
			template < size_t dimX, size_t dimP, typename funcP > typename concreteReg>
		class ILikelihoodFuncWithGrad : public FuncInterface::IFuncWithGrad<dimP>
		{
		public:
			const concreteReg<dimX, dimP, funcP>& L;
			const DataSet<dimX>& Data = L.Data;
			const funcP& f = *(L.f);

			ILikelihoodFuncWithGrad(DataSet<dimX>&& data, funcP* f_pointer) :
				L{ concreteReg< dimX, dimP, funcP>(std::move(data), f_pointer) } {}

			double operator() (const Point<dimP>& a) const override { return L(a); }

			Grad<dimP> grad(const Point<dimP>& a) const override
			{
				Grad<dimP> s{};
				for (int i = 0; i < Data.size(); i++)
				{
					auto& x = Data[i].P;
					auto df = f.GradP(x, a);
					auto val = f(x, a);
					s = s + L.op.Dterm(Data[i].Val, val, df);
				}
				return s;
			}
		};

		/// <summary>
		/// func template --- smotthness of Likelihood function
		/// </summary>
		template<size_t dimX, size_t dimP, // dimension of X, dimension of P
			typename funcP, // model to learn, f(x,a), whether it is with grad or hess
			template<size_t dimX, size_t dimP, typename funcP> typename LType, // the likelihood may or may not have grad...
			typename OptAlgoParamType // type of parameters for optimization algorithm
		>
			class IRegression
		{
		public:
			OptimizerParams prm;
			LType<dimX, dimP, funcP> LH; // Likelihood function
			Point<dimP> Optimum;
			double Val;

			const funcP& f = (*LH.f);

		public:

			IRegression(DataSet<dimX>&& data, funcP* f_pointer, OptAlgoParamType& ParamType, 
				OptimizerParams prm_ = OptimizerParams{ 0.001, 0.001, 101 }) 
				:
				prm{ prm_ }, LH{ std::move(data), f_pointer }
			{
				OptAlgoParamType::StateType State{ ParamType.CreateState(&LH) };

				Optimizer<1, OptAlgoParamType::StateType,
					FuncInterface::IFunc> opt{ &State, &LH, prm };
				opt.Optimize<OptAlgoParamType::OptAlgo>();

				Optimum = opt.CurrentGuess().P;
				Val = opt.CurrentGuess().Val;
#ifdef DEBUG_LIB
				std::cout << "Bestfit parameter values are: a = " << Optimum << '\n';
				std::cout << "Corresponding likelihood is:      " << Val << '\n';
#endif // DEBUG_LIB

			}

			double operator()(const Point<dimX>& x) { return f(x, Optimum); }

		};

	} // RegInterface
} // OptLib