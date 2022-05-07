#pragma once
#include "stdafx.h"

namespace OptLib
{
	namespace UnitTests
	{
		class testFunction
		{
		public:
			static void testGradient()
			{
				std::cout << "******IFuncWithGrad test start*****\n";

				ConcreteFunc::Function f;
				RawPoint<1> x{ {1.2} };
				std::cout << "It's value    at x = " << x << " is f = " << f(x) << "\n";
				std::cout << "It's gradient at x = " << x << " is grad[ f ] = " << f.grad(x) << "\n";

				std::cout << "******IFuncWithGrad test end*******\n\n";
			}

			static void testHessian()
			{
				std::cout << "******IFuncWithHess test start*****\n";

				ConcreteFunc::FunctionWithHess f;
				RawPoint<1> x{ {1.2} };
				std::cout << "It's value    at x = " << x << " is f = " << f(x) << "\n";
				std::cout << "It's gradient at x = " << x << " is grad[ f ] = " << f.grad(x) << "\n";
				std::cout << "It's hessian  at x = " << x << " is hess[ f ] = " << f.hess(x) << "\n";

				std::cout << "******IFuncWithHess test end*******\n\n";
			}

			static void test2DHessian()
			{
				std::cout << "******IFunc2DWithGrad test start*****\n";

				ConcreteFunc::Paraboloid2D f{ SetOfPoints<2, Point<2>> { { RawPoint<2>{ {2.0, 0.0}}, RawPoint<2>{ {0.0, 2.0}}}} };
				RawPoint<2> x{ {1.2, 1.2} };
				std::cout << "It's value at x = " << x << " is f = " << f(x) << ". Must be 5.76.\n";
				std::cout << "It's gradient is " << " grad[ f ] = " << f.grad(x) << ". Must be { 4.8, 4.8 }.\n";
				std::cout << "It's hessian is  " << " hess[ f ] = " << f.hess(x) << "\n";

				std::cout << '\n';

				f = ConcreteFunc::Paraboloid2D{ SetOfPoints<2, Point<2>> { { { {2.0, 1.0}}, { {1.0, 2.0}}}} };
				std::cout << "It's value at x = " << x << " is f = " << f(x) << ". Must be 8.64.\n";
				std::cout << "It's gradient is " << " grad[ f ] = " << f.grad(x) << ". Must be { 7.2, 7.2 }.\n";
				std::cout << "It's hessian is  " << " hess[ f ] = " << f.hess(x) << "\n";

				std::cout << "******IFunc2DWithGrad test end*******\n\n";
			}
			static void test2DWithHessNoGrad()
			{
				std::cout << "******IFuncWithHessNoGrad test start*****\n";

				ConcreteFunc::Function2DWithHessNoGrad f;
				Point<2> x{ { 1.2 ,1.2 } };
				std::cout << "It's value at x = " << x << " is f = " << f(x) << "\n";
				//	std::cout << "It's gradient is " << " grad[ f ] = " << f.grad(x) << "\n"; // error no grad is defined
				std::cout << "It's hessian is  " << " hess[ f ] = " << f.hess(x) << "\n";

				std::cout << "******IFuncWithHessNoGrad test end*******\n\n";
			}

			static void testParaboloid()
			{
				std::cout << "******Paraboloid test start*****\n";

				SetOfPoints<2, Point<2>> matrix{ { RawPoint<2>{ {1,2}} , RawPoint<2>{ {4,1}} } };
				ConcreteFunc::Paraboloid<2> f{ matrix };
				Point<2> x{ { 1,1 } };
				std::cout << "It's value at x = " << x << " is f = " << f(x) << ". Must be 8.\n";
				std::cout << "It's gradient is " << " grad[ f ] = " << f.grad(x) << ". Must be { 8, 8 }.\n";
				std::cout << "It's hessian is  " << " hess[ f ] = " << f.hess(x) << "\n";

				std::cout << "******Paraboloid test end*******\n\n";
			}


			static void testParaboloidAlongDirection()
			{
				std::cout << "******Paraboloid along direction test start*****\n";
				FuncInterface::IFuncWithGrad<2>* f = new ConcreteFunc::Paraboloid<2>{ { {  {1,2} , { 4,1}}  } };
				Point<2> x{ {1,1} };


				ConcreteFunc::FuncAlongGradDirection<2> F{ f, x };

				Point<1> gamma{ {0.2} };
				std::cout << "It's value at gamma = " << gamma << "\nand              x0 = " << x << "\nis                f = " << F(gamma) << ". Must be 2.88.\n";
				std::cout << "It's gradient is " << " grad[ f ] = " << F.grad(gamma) << ". Must be { 76.8 }.\n";

				std::cout << "******Paraboloid along direction test end*******\n\n";
			}

			static void testRozebrok()
			{
				std::cout << "******Rozebrok function test start*****\n";

				//SetOfPoints<2, Point<2>> matrix{ { RawPoint<2>{ {1,2}} , RawPoint<2>{ {4,1}} } };
				ConcreteFunc::Rozenbrok f{};
				Point<2> x{ { 1,1 } };
				std::cout << "It's value at x = " << x << " is f = " << f(x) << "\n";
				std::cout << "It's gradient is " << " grad[ f ] = " << f.grad(x) << "\n";
				std::cout << "It's hessian is  " << " hess[ f ] = " << f.hess(x) << "\n";

				std::cout << "******Rozebrok function test end*******\n\n";
			}
		};
	} // UnitTests
} // OptLib
