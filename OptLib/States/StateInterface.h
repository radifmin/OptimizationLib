#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace StateInterface
	{
		/// <summary>
		/// defines abstract basic functions, which are common for every type of state
		/// </summary>
		template<size_t dim>
		class IState
		{
		protected:
			PointVal<dim> ItsGuess;
		public:
			// concrete implementation depends on the order of optimization method
			virtual bool IsConverged(double abs_tol, double rel_tol) const  = 0;
			PointVal<dim> Guess() const { return ItsGuess; };
		};

		/// <summary>
		/// State for methods of optimization in dim-dimensional space based on simplexes
		/// </summary>
		template<size_t dim, typename simplex>
		class IStateSimplex : public StateInterface::IState<dim>
		{
		public: // overriden from predecessor
			virtual bool IsConverged(double abs_tol, double rel_tol) const override
			{// is average and relative tolerance met?
				auto [avg, disp] = GuessDomain().Dispersion();
				auto [var,std]{ VarCoef<PointVal<dim>>(avg, disp) };

				for (int i = 0; i < dim; i++)
				{
					bool f = (((std[i]) < abs_tol) || (var[i] < rel_tol)) && (((std.Val) < abs_tol) || (var.Val < rel_tol));
					if (!f) return false;
				}
				return true;
			}
		protected:
			simplex ItsGuessDomain; // the field is unique for direct optimization methods
			std::array<double, dim + 1> FuncVals(const SetOfPoints<dim + 1, Point<dim>>& State, const FuncInterface::IFunc<dim>* f) 
			{
				return f->operator()(State);
			}
			void SetDomain(SetOfPoints<dim + 1, Point<dim>>&& State, std::array<double, dim + 1>&& funcVals)
			{
				ItsGuessDomain = simplex{ std::move(State), std::move(funcVals)};
				ItsGuess = GuessDomain().Mean();
			}
		public:
			IStateSimplex(SetOfPoints<dim + 1, Point<dim>>&& State, FuncInterface::IFunc<dim>* f)
			{
				SetDomain(std::move(State), f);
			}
			const simplex& GuessDomain() const { return ItsGuessDomain; } // unique for direct optimization methods
			void SetDomain(SetOfPoints<dim + 1, Point<dim>>&& State, const FuncInterface::IFunc<dim>* f)
			{
				SetDomain(std::move(State), std::move(FuncVals(State, f)));
			}

			void UpdateDomain(SetOfPoints<dim + 1, PointVal<dim>>&& newDomain)
			{
				ItsGuessDomain = simplex{ std::move(newDomain) };
				ItsGuess = GuessDomain().Mean();
			}
		};
	} // StateInterface
} // OptLib