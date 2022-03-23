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
			PointVal<dim> ItsGuess;
		public:
			// concrete implementation depends on the order of optimization method
			virtual bool IsConverged(double abs_tol, double rel_tol) const  = 0;
			PointVal<dim> Guess() const { return ItsGuess; };
		};

		/// <summary>
		/// State for methods of optimization in dim-dimensional space based on simplexes
		/// </summary>
		template<int dim, typename simplex>
		class IStateSimplex : public StateInterface::IState<dim>
		{
		public: // overriden from predecessor
			virtual bool IsConverged(double abs_tol, double rel_tol) const override
			{// is average and relative tolerance met?
				auto [avg, disp] = GuessDomain().Dispersion();
				PointVal<dim> var{ VarCoef<PointVal<dim>>(avg, disp) };

				for (int i = 0; i < dim; i++)
				{
					bool f = ((std::abs(avg[i]) < abs_tol) || (var[i] < rel_tol));
					if (!f) return false;
				}
				return true;
			}
		protected:
			simplex ItsGuessDomain; // unique for direct optimization methods
			std::array<double, dim + 1> FuncVals(const SetOfPoints<dim + 1, Point<dim>>& state, FuncInterface::IFunc<dim>* f)
			{
				std::array<double, dim + 1> funcVals;
				for (int i = 0; i < dim + 1; i++)
					funcVals[i] = f->operator()(state[i]);
				return funcVals;
			}
			void SetDomain(SetOfPoints<dim + 1, Point<dim>>&& state, std::array<double, dim + 1>&& funcVals)
			{
				// TODO : This line does not compile
//				ItsGuessDomain = simplex{ std::move(state), std::move(funcVals)};
				
				
				// combine Points and Vals together
				SetOfPoints<dim + 1, PointVal<dim>> stateVals{};
				for (size_t i = 0; i < dim + 1; i++)
					stateVals[i] = PointVal<dim>{state[i], funcVals[i]};

				UpdateDomain(std::move(stateVals));
			}
		public:
			IStateSimplex(SetOfPoints<dim + 1, Point<dim>>&& state, FuncInterface::IFunc<dim>* f)
			{
				SetDomain(std::move(state), f);
			}
			const simplex& GuessDomain() const { return ItsGuessDomain; } // unique for direct optimization methods
			void SetDomain(SetOfPoints<dim + 1, Point<dim>>&& state, FuncInterface::IFunc<dim>* f)
			{
				SetDomain(std::move(state), std::move(FuncVals(state, f)));
			}

			void UpdateDomain(SetOfPoints<dim + 1, PointVal<dim>>&& newDomain)
			{
				ItsGuessDomain = simplex{ std::move(newDomain) };
				ItsGuess = GuessDomain().Mean();
			}
		};
	} // StateInterface
} // OptLib