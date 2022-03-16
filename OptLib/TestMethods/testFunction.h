#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace UnitTests
	{
		using namespace AuxMethods;

		class testFunction
		{
		public:
			static void testGradient()
			{
				std::cout << "******IFuncWithGrad test start*****\n";

				ConcreteFunc::Function f;
				Point<1> x{ 1.2 };
				std::cout << "It's value    at x = " << x << " is f = " << f(x) << "\n";
				std::cout << "It's gradient at x = " << x << " is grad[ f ] = " << f.grad(x) << "\n";

				std::cout << "******IFuncWithGrad test end*******\n\n";
			}

			static void testHessian()
			{
				std::cout << "******IFuncWithHess test start*****\n";

				ConcreteFunc::FunctionWithHess f;
				Point<1> x{ 1.2 };
				std::cout << "It's value    at x = " << x << " is f = " << f(x) << "\n";
				std::cout << "It's gradient at x = " << x << " is grad[ f ] = " << f.grad(x) << "\n";
				std::cout << "It's hessian  at x = " << x << " is hess[ f ] = " << f.hess(x) << "\n";

				std::cout << "******IFuncWithHess test end*******\n\n";
			}

			static void test2DHessian()
			{
				std::cout << "******IFunc2DWithGrad test start*****\n";

				ConcreteFunc::Paraboloid2D f{ Simplex<2, 2> { { {2.0, 0.0}, {0.0, 2.0}}} };
				Point<2> x{ 1.2, 1.2 };
				std::cout << "It's value at x = " << x << " is f = " << f(x) << ". Must be 5.76.\n";
				std::cout << "It's gradient is " << " grad[ f ] = " << f.grad(x) << ". Must be {4.8, 4.8}.\n";
				std::cout << "It's hessian is  " << " hess[ f ] = " << f.hess(x) << "\n";

				std::cout << "******IFunc2DWithGrad test end*******\n\n";
			}
			static void test2DWithHessNoGrad()
			{
				std::cout << "******IFuncWithHessNoGrad test start*****\n";

				ConcreteFunc::Function2DWithHessNoGrad f;
				Point<2> x{ 1.2 ,1.2 };
				std::cout << "It's value at x = " << x << " is f = " << f(x) << "\n";
				//	std::cout << "It's gradient is " << " grad[ f ] = " << f.grad(x) << "\n"; // error no grad is defined
				std::cout << "It's hessian is  " << " hess[ f ] = " << f.hess(x) << "\n";

				std::cout << "******IFuncWithHessNoGrad test end*******\n\n";
			}

			static void testParaboloid()
			{
				std::cout << "******Paraboloid test start*****\n";

				Simplex<2, 2> matrix{ { {1,2} , {4,1} } };
				ConcreteFunc::Paraboloid<2> f{ matrix };
				Point<2> x{ 1,1 };
				std::cout << "It's value at x = " << x << " is f = " << f(x) << "\n";
				std::cout << "It's gradient is " << " grad[ f ] = " << f.grad(x) << "\n";
				std::cout << "It's hessian is  " << " hess[ f ] = " << f.hess(x) << "\n";



				std::cout << "******Paraboloid test end*******\n\n";
			}


			static void testParaboloidAlongDirection()
			{
				std::cout << "******Paraboloid along direction test start*****\n";
				FuncInterface::IFuncWithGrad<2>* f = new ConcreteFunc::Paraboloid<2>{ { { {1,2} , {4,1} } } };
				Point<2> x{ 1,1 };


				ConcreteFunc::FuncAlongGradDirection<2> F{ f, x };

				Point<1> gamma{ 0.2 };
				std::cout << "It's value at gamma = " << gamma << " is f = " << F(gamma) << "\n";
				std::cout << "It's gradient is " << " grad[ f ] = " << F.grad(gamma) << "\n";



				std::cout << "******Paraboloid along direction test end*******\n\n";
			}
		};
	} // UnitTests
} // OptLib