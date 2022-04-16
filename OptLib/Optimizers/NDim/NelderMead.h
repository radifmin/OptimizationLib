#pragma once
#include "stdafx.h"
namespace OptLib
{
	namespace ConcreteOptimizer
	{
		template<size_t dim>
		class NelderMead : public OptimizerInterface::IDirectAlgo<dim>
		{
		protected:
			double alpha;
			double betta;
			double gamma;
		public:
			NelderMead(FuncInterface::IFunc<dim>* f_pointer, SetOfPoints<dim+ 1, Point<dim>>&& setOfPoints,
				double alpha_,double betta_,double gamma_) :
				OptimizerInterface::IDirectAlgo<dim>
			{f_pointer, std::move(setOfPoints)}, alpha{ alpha_ }, betta{ betta_ }, gamma{gamma_} {}

			virtual PointVal<dim> Proceed() override
			{

		PointVal<dim> xl = State.GuessDomain().Points()[0];
		PointVal<dim> xh = State.GuessDomain().Points()[dim];
		PointVal<dim> xg = State.GuessDomain().Points()[dim - 1];
		//		/*Point<dim> xc{ 0.0 };*/
		PointVal<dim> xc=State.GuessDomain().Points()[0];

		SetOfPoints<dim+1, PointVal<dim>> NewSimplex = State.GuessDomain().Points();

				for (int i = 0; i < dim; i++)
				{
					xc.P[i] = 0.0;
				}//////v2
				for(int i = 0;i<dim;i++)
			{
					if(State.GuessDomain().Points()[i]!=xh)
					{
						xc = xc + State.GuessDomain().Points()[i];
					}
			}
				xc = xc / (dim - 1.0);
			xc.Val = f->operator()(xc);
			PointVal<dim> xr{ xc * (1.0 + alpha) - xh * alpha };
			xr.Val = f->operator()(xr);
				if(xr.Val<xl.Val)
				{
					PointVal<dim> xe = xc * (1.0 - gamma) + xr * gamma;
					xe.Val = f->operator()(xe);
					if(xe.Val<xr.Val)
					{
						xh = xe;
						State.UpdateDomain(std::move(NewSimplex));
						return State.Guess();
					}
					else
					{
						xh = xr;
						State.UpdateDomain(std::move(NewSimplex));
						return State.Guess();
					}
				}
				else if(xr.Val<xg.Val)
				{
					xh = xr;
					State.UpdateDomain(std::move(NewSimplex));
					return State.Guess();
				}
				else if(xr.Val<xh.Val)
				{
					std::swap(xr, xh);
				//	std::swap(xr.Val, xh.Val);
				}
				PointVal<dim> xs = xh * betta + xc * (1 - betta);
				xs.Val = f->operator()(xs);
				if(xs.Val<xh.Val)
				{
					xh = xs;
					State.UpdateDomain(std::move(NewSimplex));
					return State.Guess();
				}
				else
				{
					SetOfPoints<dim+1, Point<dim>> NewSimplex1;
				//	NewSimplex1[0] = xl.P;
					for(int i = 0; i<dim+1;i++)
					{
						NewSimplex1[i] = Point<dim>{ std::move(xl.P + (State.GuessDomain().Points()[i].P - xl.P) / 2.0) };
					}
					State.SetDomain(std::move(NewSimplex1), this->f);
					return State.Guess();
				}

				return State.Guess();
			}
		};
	}//ConcreteOptimizer
}//OptLib