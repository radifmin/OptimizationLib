#pragma once
#include "stdafx.h"

namespace OptLib
{
	/// <summary>
	/// An alias for std::array. It is required for the ease of RawPoint construction.
	/// </summary>
	template<int dim>
	using Point = std::array<double, dim>;
	/// elementwise addition of vector + vector
	template<int dim>
	Point<dim> operator+(const Point<dim>& arr1, const Point<dim>& arr2)
	{
		std::array<double, dim> result;
		std::transform(arr1.begin(), arr1.end(), arr2.begin(), result.begin(), std::plus<> {});
		return result;
	}
	/// elementwise subtraction of vector - vector
	template<int dim>
	Point<dim> operator-(const Point<dim>& arr1, const Point<dim>& arr2)
	{
		std::array<double, dim> result;
		std::transform(arr1.begin(), arr1.end(), arr2.begin(), result.begin(), std::minus<> {});
		return result;
	}
	/// elementwise division vector / scalar
	template<int dim>
	Point<dim> operator/(Point<dim> arr, double val)
	{
		for (auto& elem : arr)
			elem /= val;
		return arr;
	}
	/// elementwise division of vector / vector
	template<int dim>
	Point<dim> operator/(const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result;
		std::transform(arr1.begin(), arr1.end(),
			arr2.begin(), result.begin(), [](double x, double y) {return x / y; });
		return result;
	}
	/// elementwise multiplication of vector * vector
	template<int dim>
	Point<dim> operator*(const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result;
		std::transform(arr1.begin(), arr1.end(),
			arr2.begin(), result.begin(), [](double x, double y) {return x * y; });

		return result;
	}
	/// elementwise multiplication of vector * scalar
	template<int dim>
	Point<dim> operator*(Point<dim> arr, double val)
	{
		for (auto& elem : arr)
			elem *= val;
		return arr;
	}
	/// elementwise sqrt bbb
	template<int dim>
	Point<dim> sqrt(Point<dim> arr)
	{
		for (auto& elem : arr)
			elem = std::sqrt(elem);
		return arr;
	}
	/// elementwise abs
	template<int dim>
	Point<dim> abs(Point<dim> arr)
	{
		for (auto& elem : arr)
			elem = std::abs(elem);
		return arr;
	}
	/// scalar product of two vectors
	template <int dim>
	double scalar_product(const Point<dim>& x, const Point<dim>& y)
	{
		double s = 0;
		for (int i = 0; i < dim; i++)
			s += x[i] * y[i];
		return s;
	}
	template<int dim>
	std::ostream& operator<< (std::ostream& o, const Point<dim>& output)
	{
		o << "{ " << output[0];
		if constexpr (dim > 1)
		{
			for (int i = 1; i < dim; i++) {


				o << ", " << output[i];
			}
		}
		o << " }";

		return o;
	}


	/// <summary>
	/// Envelope for the Point<dim>
	/// </summary>
	template<int dim>
	struct RawPoint
	{
		RawPoint() = default;

		Point<dim> P;
		RawPoint(Point<dim>&& _P) :P{ std::move(_P)} {};
		RawPoint(const Point<dim>& _P) :P{ _P } {};
		double operator[](int i) const { return P[i]; }

		operator Point<dim>() { return P; }
	};
	///// elementwise addition of vector + vector
	//template<int dim>
	//RawPoint<dim> operator+(const RawPoint<dim>& arr1, const RawPoint<dim>& arr2)
	//{
	//	return RawPoint<dim>{std::move(arr1.P+arr2.P)};
	//}
	///// elementwise subtraction of vector - vector
	//template<int dim>
	//RawPoint<dim> operator-(const RawPoint<dim>& arr1, const RawPoint<dim>& arr2)
	//{
	//	return RawPoint<dim>{std::move(arr1.P-arr2.P)};
	//}
	///// elementwise division vector / scalar
	//template<int dim>
	//RawPoint<dim> operator/(RawPoint<dim> arr, double val)
	//{
	//	return RawPoint{ stq::move(arr.P / val) };
	//}
	///// elementwise division of vector / vector
	//template<int dim>
	//RawPoint<dim> operator/(const RawPoint<dim>& arr1, const RawPoint<dim>& arr2)
	//{
	//	return RawPoint<dim>{std::move(arr1.P / arr2.P)};
	//}
	///// elementwise multiplication of vector * vector
	//template<int dim>
	//RawPoint<dim> operator*(const RawPoint<dim>& arr1, const RawPoint<dim>& arr2)
	//{
	//	return RawPoint<dim>{std::move(arr1.P* arr2.P)};
	//}
	///// elementwise multiplication of vector * scalar
	//template<int dim>
	//RawPoint<dim> operator*(RawPoint<dim> arr, double val)
	//{
	//	return RawPoint<dim>{arr.P* val};
	//}
	template<int dim>
	std::ostream& operator<<(std::ostream& o, const RawPoint<dim>& r)
	{
		o << r.P; return o;
	}


	/// <summary>
	/// Point with associated Value. Essentially a {Point, Val}-pair with a comparator to sort Points
	/// </summary>
	template<int dim>
	struct PointVal : public RawPoint<dim>
	{
		double Val;
		PointVal() = default;
		PointVal(Point<dim>&& _P, double _Val) : RawPoint{ std::move(_P) }, Val{ _Val }{}
		PointVal(const Point<dim>& _P, double _Val) : RawPoint{ _P }, Val{ _Val }{}
		bool operator<(const PointVal& rhs)
		{
			return this->Val < rhs.Val;
		}
	};
	/// elementwise addition of vector + vector
	template<int dim>
	PointVal<dim> operator+(const PointVal<dim>& arr1, const PointVal<dim>& arr2)
	{
		return PointVal<dim>{std::move(arr1.P + arr2.P), arr1.Val + arr2.Val};
	}
	/// elementwise subtraction of vector - vector
	template<int dim>
	PointVal<dim> operator-(const PointVal<dim>& arr1, const PointVal<dim>& arr2)
	{
		return PointVal<dim>{std::move(arr1.P - arr2.P), arr1.Val - arr2.Val};
	}
	/// elementwise division vector / scalar
	template<int dim>
	PointVal<dim> operator/(PointVal<dim> arr, double val)
	{
		return PointVal<dim>{ std::move(arr.P / val), arr.Val / val };
	}
	/// elementwise multiplication of vector * vector
	template<int dim>
	PointVal<dim> operator*(const PointVal<dim>& arr1, const PointVal<dim>& arr2)
	{
		return PointVal<dim>{std::move(arr1.P* arr2.P), arr1.Val* arr2.Val};
	}
	/// elementwise division of vector * vector
	template<int dim>
	PointVal<dim> operator/(const PointVal<dim>& arr1, const PointVal<dim>& arr2)
	{
		return PointVal<dim>{std::move(arr1.P/ arr2.P), arr1.Val/ arr2.Val};
	}
	///  elementwise sqrt nnn
	template<int dim>
	PointVal<dim> sqrt(const PointVal<dim>& p)
	{
		return PointVal<dim>{ sqrt<dim>(p.P), std::sqrt(p.Val) };
	}
	///  elementwise abs
	template<int dim>
	PointVal<dim> abs(const PointVal<dim>& p)
	{
		return PointVal<dim>{ abs<dim>(p.P), std::abs(p.Val) };
	}
	template<int dim>
	std::ostream& operator<<(std::ostream& o, const PointVal<dim>& r)
	{
		o << "{ " << r.P << ' ' << r.Val << " }"; return o;
	}

	/// <summary>
	/// coefficient of variation, mean/variance
	/// </summary>
	/// <typeparam name="point"></typeparam>
	/// <param name="avg"></param>
	/// <param name="disp"></param>
	/// <returns></returns>
	template<typename point>
	point VarCoef(const point& avg, const point& disp)
	{// requires sqrt(vector), abs(vector), vector/vector
		return abs(avg) / sqrt(disp);
	}

	template<int count, typename point>
	using SetOfPoints = std::array<point, count>;
	template<int count, typename point>
	std::ostream& operator<< (std::ostream& o, const SetOfPoints<count, point>& output)
	{
		o << "{ " << output[0];
		if constexpr (count > 1)
		{
			for (int i = 1; i < count; i++)
				o << "; " << output[i];
		}
		o << " }";

		return o;
	}

	/// <summary>
	/// A set of points of type point with +-*/ operators overloaded for calculation of Mean, Disp, and VarCoef
	/// </summary>
	/// <typeparam name="point"></typeparam>
	template<int count, typename point>
	class RawSetOfPoints
	{
	protected:
		SetOfPoints<count, point> ItsSetOfPoints;
	public:
		RawSetOfPoints() = default;
		RawSetOfPoints(SetOfPoints<count, point> && _s) : ItsSetOfPoints{ std::move(_s) } { }
		RawSetOfPoints(const SetOfPoints<count, point>& _s) : ItsSetOfPoints{ _s } { }
		const point& operator[](int i) const { return Points()[i]; }

		const SetOfPoints<count, point>& Points() const { return ItsSetOfPoints; }
		point Mean() const
		{ // requires vector+vector and vector/double
			point result{ Points()[0] };
			for (int i = 1; i < count; i++)
				result = result + Points()[i];
			result = result / (count + 0.0);
			return result;
		}
		std::pair<point, point> Dispersion() const
		{// requires vector+-*vector, vector/double
			point avg{ Mean() };
			point result = (Points()[0] - avg) * (Points()[0] - avg);

			for (int i = 1; i < count; i++)
				result = result + (Points()[i] - avg) * (Points()[i] - avg);

			return { avg, result / (count + 0.0) };
		}

		operator SetOfPoints<count, point>() { return Points(); }
	};
	template<int count, typename point>
	std::ostream& operator<< (std::ostream& o, const RawSetOfPoints<count, point>& output)
	{
		o << "{ " << output[0];
		for (int i = 1; i < count; i++)
			o << "; " << output[i];
		o << " }";
		return o;
	}


	/// <summary>
	/// A set of points of type {point with Val} with +-*/ operators overloaded for calculation of Mean, Disp, and VarCoef
	/// </summary>
	/// <typeparam name="point"></typeparam>
	template<int count, typename point, typename pointval>
	class SetOfPointValsSort : public RawSetOfPoints<count, pointval>
	{
	private:
		void Sort() { std::sort(ItsSetOfPoints.begin(), ItsSetOfPoints.end()); }
		static SetOfPoints<count, pointval> make_field(SetOfPoints<count, point>&& _s, std::array<double, count>&& FuncVals)
		{
			SetOfPoints<count, pointval> P;
			for (int i = 0; i < count; i++)
				P[i] = pointval{ std::move(_s[i]), FuncVals[i] };
			return P;
		}
	public:
		SetOfPointValsSort() = default;
			SetOfPointValsSort(SetOfPoints<count, pointval>&& _s) :
			RawSetOfPoints<count, pointval>{ std::move(_s) } { this->Sort(); }
		SetOfPointValsSort(SetOfPoints<count, point>&& _s, std::array<double, count>&& funcVals) : // transforms points to points with vals
			SetOfPointValsSort<count, point, pointval>{ std::move(make_field(std::move(_s), std::move(funcVals))) } {}
		//SetOfPointValsSort(const SetOfPoints<count, point>& _s, const std::array<double, count>& funcVals) : // transforms points to points with vals
		//	SetOfPointValsSort<count, point, pointval>{ make_field(_s, funcVals) } {}
	};

	using Segment = RawSetOfPoints<2, PointVal<1>>;

	template<int dim>
	using SimplexValNoSort = RawSetOfPoints<dim + 1, PointVal<dim>>;

	template<int dim>
	using SimplexValSort = SetOfPointValsSort<dim + 1, Point<dim>, PointVal<dim>>;
} // OptLib