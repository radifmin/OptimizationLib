#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace OptimizerInterface
	{
		template<int dim, typename func, typename stateT>
		class IOptimizerAlgorithm
		{
		public:
			IOptimizerAlgorithm(func* f_pointer, SetOfPoints<dim + 1, Point<dim>>&& setOfPoints) :
				f{ f_pointer }, state{ std::move(setOfPoints), f_pointer }{}

			virtual Point<dim> CurrentGuess() const { return state.Guess(); }; // returns current guess
			PointVal<dim> CurrentPointAndVal() // returns the guess and the function value
			{
				Point<dim> p = CurrentGuess();
				return PointVal<dim>{std::move(p), f->operator()(p)};
			}

			virtual bool IsConverged(double abs_tol, double rel_tol) const
			{
				return state.IsConverged(abs_tol, rel_tol);
			}

			virtual PointVal<dim> Proceed() = 0; // continue to next guess

		protected:
			const func* f; // function to optimize
			stateT state; // state of the method
		};

		/// <summary>
		/// Optimization using simplex methods in N-dim space. Common interface for Direct and 1D segment optimization methods.
		/// state must implement GuessDomain method
		/// </summary>
		template<int dim, typename stateT, typename simplex>
		class ISimplexAlgo : public IOptimizerAlgorithm<dim, FuncInterface::IFunc<dim>, stateT>
		{
		public:
			ISimplexAlgo(
				FuncInterface::IFunc<dim>* f_pointer, 
				SetOfPoints<dim + 1, Point<dim>>&& setOfPoints) 
				:
				IOptimizerAlgorithm<dim, FuncInterface::IFunc<dim>, stateT>{ f_pointer, std::move(setOfPoints) } {}
			const simplex& GuessDomain() const { return this->state.GuessDomain(); } // unique for direct methods
		};


		/// <summary>
		/// Direct optimization in N-dim space with simplex points sorting according to f(x)
		/// </summary>
	//	template<int dim>
	//	using IDirectAlgo = ISimplexAlgo<dim, ConcreteState::StateDirect<dim>, SimplexValSort<dim>>;

		/// <summary>
		/// Algorithms for 1D optimization on a segment. Segment [x1; x2], where it is guaranteed that x1 < x2
		/// </summary>
		class ISegmentAlgo : public ISimplexAlgo<1, ConcreteState::StateSegment, SimplexValNoSort<1>>
		{
		public:
			ISegmentAlgo(FuncInterface::IFunc<1>* f_pointer, SetOfPoints<2, Point<1>>&& setOfPoints) :
				ISimplexAlgo<1, ConcreteState::StateSegment, SimplexValNoSort<1>>{ f_pointer, std::move(OrderPointsInSegment(setOfPoints)) } {}
		protected:
			SetOfPoints<2, Point<1>> OrderPointsInSegment(SetOfPoints<2, Point<1>>& setOfPoints)
			{
				if (setOfPoints[0][0] > setOfPoints[1][0])
					std::swap(setOfPoints[0], setOfPoints[1]);
				return setOfPoints;
			}
		};

		template<int dim>
		class IGradAlgo : public IOptimizerAlgorithm<dim, FuncInterface::IFuncWithGrad<dim>, ConcreteState::StatePoint<dim>>
		{

		};

		template<int dim>
		class IHessAlgo : public IOptimizerAlgorithm<dim, FuncInterface::IFuncWithHess<dim>, ConcreteState::StatePoint<dim>>
		{

		};

		template<int dim>
		class IStochasticAlgo : public IOptimizerAlgorithm<dim, FuncInterface::IFuncWithHess<dim>, ConcreteState::StateStochastic<dim>>
		{

		};
	} // OptimizerInterface
} // OptLib