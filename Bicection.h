#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteOptimizer
	{
		using namespace AuxMethods;
		class Bicection : public OptimizerInterface::IDirectAlgo<1>
		{
		//	using OptimizerInterface::IDirectAlgo<1>::f;

			void set_end_vals(double lval, double rval)
			{
				val_left = lval; val_right = rval;
				val_center = this->f->operator()(this->CurrentGuess());
			}

		public:
			Bicection(FuncInterface::IFunc<1>* f, ConcreteState::StateSimplex<1>* state_pointer) :IDirectAlgo<1>{ f, state_pointer }
			{
				set_end_vals(f->operator()(CurSimplex()[0]), f->operator()(CurSimplex()[1]));
			}
		public:
			Point<1> left() { return CurSimplex()[0]; }
			Point<1> right() { return CurSimplex()[1]; }

			virtual PointAndVal<1> proceed() override
			{
				Point<1> step = (right() - left()) / 4.0;

				std::array<Point<1>, 5> mesh{
					left(),
					left() + step,
					CurrentGuess(),
					right() - step,
					right() };
				std::array<double, 5> vals{
					val_left,
					f->operator()(mesh[1]),
					val_center,
					f->operator()(mesh[3]),
					val_right };

				std::array<double, 5>::iterator min = std::min_element(vals.begin(), vals.end());
				size_t pos = std::distance(vals.begin(), min);

				Simplex<2, 1> new_simplex;
				if (pos == 0)
				{
					new_simplex = Simplex<2, 1>{ { mesh[0], mesh[1] } };
					set_end_vals(vals[0], vals[1]);
				}
				else if (pos == vals.size() - 1)
				{
					new_simplex = Simplex<2, 1>{ { mesh[3], mesh[4] } };
					set_end_vals(vals[3], vals[4]);
				}
				else
				{
					new_simplex = Simplex<2, 1>{ { mesh[pos - 1], mesh[pos + 1] } };
					set_end_vals(vals[pos - 1], vals[pos + 1]);
				}
				state = new ConcreteState::StateSimplex<1>{new_simplex};
				return PointAndVal<1> { CurrentGuess(), f->operator()(CurrentGuess()) };
			}

		protected:
			double val_left, val_right, val_center;
		};

	} // Optimizer
} // OptLib