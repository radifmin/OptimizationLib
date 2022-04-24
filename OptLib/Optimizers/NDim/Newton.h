#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace ConcreteState
	{
		template<size_t dim>
		class StateNewton :public ConcreteState::StatePoint<dim>
		{
		public:
			StateNewton(Point<dim>&& x0, const FuncInterface::IFunc<dim>* f)
			{
				ItsGuess = PointVal<dim>::CreateFromPoint(std::move(x0), f);
			}
		};

	} // ConcreteState

	namespace ConcreteOptimizer
	{
		template <size_t dim>
		class Newton
		{
		protected:
			static Point<dim> GaussSolver(SetOfPoints<dim, Point<dim>> A, Point<dim> B)
			{


#ifdef DEBUG_LIB
				auto A0 = A;
				auto B0 = B;
#endif


				// forward loop
				for (int i = 0; i < dim; i++)
				{
					for (int j = i + 1; j < dim; j++)
					{
						double ratio = A[j][i] / A[i][i];
						A[j] = A[j] - ratio * A[i];
						B[j] = B[j] - ratio * B[i];
					}
				}
#ifdef DEBUG_LIB
				std::cout << "A: " << A << '\n';
				std::cout << "B: " << B << '\n';
#endif // DEBUG_LIB

				//A[0] = A[0] / A[0][0];//надо с В или нет? надо
				/*for (int i = 1; i < dim; i++)
				{
					A[i] = A[i] / A[i][i];
					//B[i] = B[i] / A[i][i];
				}*/
				/*for (int i = 1; i < dim; i++)
				{
					int j = i;
					double ratio = A[j][i] / A[0][j];
					A[j] = A[j] - ratio * A[0];
				}*/
				SetOfPoints<dim, Point<dim>> A1 = A;
				Point<dim> B1 = B;

				for (int i = 0; i < dim; i++)
				{
					B[i] = B[i] / A[i][i];
					A[i] = A[i] / A[i][i];
				}
#ifdef DEBUG_LIB
				std::cout << "A: " << A << '\n';
				std::cout << "B: " << B << '\n';
#endif // DEBUG_LIB
				// backward loop
				for (int i = dim - 1; i > -1; i--)
				{
					for (int j = i + 1; j < dim; j++)
					{
						double ratio = A[i][j] / A[j][j];
						A[i] = A[i] - A[j] * ratio;
						//B[i] = B[i] - A[i][j] * B[j];
						B[i] = B[i] - ratio * B[j];
					}
					//B[i] = B[i] / A[i][i];
				}
#ifdef DEBUG_LIB
				std::cout << "A: " << A << '\n';
				std::cout << "B: " << B << '\n';
				std::cout << "A * B - B = " << A0 * B - B0 << '\n';
#endif // DEBUG_LIB

				return B;
			}
			
		public:
			static PointVal<dim> Proceed(ConcreteState::StateNewton<dim>& State, const FuncInterface::IFuncWithHess<dim>* f)
			{
				const auto& g = State.Guess();
				Point<dim> dx{ GaussSolver(f->hess(g.P), -1* f->grad(g.P)) };
#ifdef DEBUG_LIB
				std::cout << "Current state: " << State.Guess() << "\n";
#endif // DEBUG_LIB

				State.SetGuess(PointVal<dim>::CreateFromPoint(g.P + dx, f));
				return State.Guess();
			}
		};
	} // ConcreteOptimizer
} // OptLib