#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace StateWithMemory
	{
		template<size_t dim,  typename state>
		class StateSimplexMemory : public state
		{
			state* State;

		public:
			StateSimplexMemory(state* State) : State{ State } 
			{
				a_Memory.push_back(*State); // copies ipdated state to a memory
			}
			const std::vector<state>& Memory() { return a_Memory; }

			void UpdateDomain(SetOfPoints<dim + 1, PointVal<dim>>&& newDomain) override
			{
				a_Memory.push_back(*State); // copies ipdated state to a memory
				(*State).UpdateDomain(std::move(newDomain));
			}

			bool IsConverged(double abs_tol, double rel_tol) const override
			{
				return (*State).IsConverged(abs_tol, rel_tol);
			}

		protected:
			std::vector<state> a_Memory;
		};


		template<size_t dim>
		class StatePointImproved : public ConcreteState::StatePoint<dim>
		{
			ConcreteState::StatePoint<dim>* State;

		public:
			StatePointImproved(ConcreteState::StatePoint<dim>* State) : State{ State }
			{
				a_Memory.push_back(new ConcreteState::StatePoint<dim>(*State)); // copies ipdated state to a memory
			}

			void UpdateState(const PointVal<dim>& v) override
			{
				(*State).UpdateState(v);
				a_Memory.push_back(new ConcreteState::StatePoint<dim>(*State));
			}

			const std::vector<ConcreteState::StatePoint<dim>*>& Memory() { return a_Memory; }

		protected:
			std::vector<ConcreteState::StatePoint<dim>*> a_Memory;
		};


	} // StateWithMemory
} // OptLib