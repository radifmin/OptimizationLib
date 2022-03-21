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
	/// elementwise sqrt
	template<int dim>
	Point<dim> sqrt(Point<dim> arr, double val)
	{
		for (auto& elem : arr)
			elem = std::sqrt(val);
		return arr;
	}
	/// elementwise abs
	template<int dim>
	Point<dim> abs(Point<dim> arr, double val)
	{
		for (auto& elem : arr)
			elem = std::abs(val);
		return arr;
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
		double& operator[](int i) { return P[i]; }
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
		PointVal(const Point<dim>& _P, double _Val) : RawPoint{ (_P) }, Val{ _Val }{}
		PointVal(const RawPoint<dim>& _P, double _Val) : PointVal((_P.P), _Val) {}
		bool operator<(const PointVal& rhs)
		{
			return this->Val < rhs.Val;
		}

		operator Point<dim>() { return P; }
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
		return PointVal{ std::move(arr.P / val), arr.Val / val };
	}
	/// elementwise multiplication of vector * vector
	template<int dim>
	PointVal<dim> operator*(const PointVal<dim>& arr1, const PointVal<dim>& arr2)
	{
		return PointVal<dim>{std::move(arr1.P* arr2.P), arr1.Val* arr2.Val};
	}
	///  elementwise sqrt
	template<int dim>
	PointVal<dim> sqrt(const PointVal<dim>& p)
	{
		return PointVal{ std::move(sqrt(p.P)), std::sqrt(p.Val) };
	}
	///  elementwise abs
	template<int dim>
	PointVal<dim> abs(const PointVal<dim>& p)
	{
		return PointVal{ std::move(abs(p.P)), std::abs(p.Val) };
	}
	template<int dim>
	std::ostream& operator<<(std::ostream& o, const PointVal<dim>& r)
	{
		o << r.P << ", val is " << r.Val; return o;
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
	/// returns mean value for a set of vectors
	/// </summary>
	/// <param name="simplex"></param>
	/// <returns></returns>
	template <int count, typename point>
	point mean(const SetOfPoints<count, point>& simplex)
	{
		point result{ simplex[0] };
		for (int i = 1; i < count; i++)
			result = result + simplex[i];
		result = result / (count + 0.0);
		return result;
	}

	/// <summary>
	/// A set of points of type point with +-*/ operators overloaded for calculation of Mean, Disp, and VarCoef
	/// </summary>
	/// <typeparam name="point"></typeparam>
	template<int count, typename point>
	class SimplexSimple
	{
	protected:
		SetOfPoints<count, point> ItsSimplex;

	public:
		SimplexSimple() = default;
		SimplexSimple( SetOfPoints<count, point>&& _s) : ItsSimplex{ std::move(_s) } { }
		const point& operator[](int i) const { return Simplex()[i]; }

		const SetOfPoints<count, point>& Simplex() const { return ItsSimplex; }

		point SimplexCenter() const
		{ // requires vector+vector and vector/double
			point result{ Simplex()[0] };
			for (int i = 1; i < count; i++)
				result = result + Simplex()[i];
			result = result / (count + 0.0);
			return result;
		}

		std::pair<point, point> DispersionSimplex() const
		{// requires vector+-*vector, vector/double
			point avg{ SimplexCenter() };
			point result = (Simplex()[0] - avg) * (Simplex()[0] - avg);

			for (int i = 1; i < count; i++)
				result = result + (Simplex()[i] - avg) * (Simplex()[i] - avg);

			return { avg, result / (count + 0.0) };
		}

		point VarCoefSimplex(const point& avg, const point& disp) const
		{// requires sqrt(vector), abs(vector), vector/vector
			return abs(avg) / sqrt(disp);
		}
	};
	template<int count, typename point>
	std::ostream& operator<< (std::ostream& o, const SimplexSimple<count, point>& output)
	{
		o << "{ " << output[0];
		for (int i = 1; i < count; i++)
			o << "; " << output[i];
		o << " }";
		return o;
	}

	using Segment = SimplexSimple<2, Point<1>>;

	/// <summary>
	/// A set of points of a concrete type PointVal<dim>
	/// </summary>
	template<int count, int dim> 
	class SimplexValNoSort : public SimplexSimple<count, PointVal<dim>>
	{
	protected:
		static std::array<PointVal<dim>, count> make_field(std::array<Point<dim>, count>&& _s, std::array<double, count>&& FuncVals)
		{
			std::array<PointVal<dim>, count> P;
			for (int i = 0; i < count; i++)
				P[i] = PointVal<dim>{ (_s[i]), FuncVals[i] };
			return P;
		}

	public:
		SimplexValNoSort() = default;
		SimplexValNoSort(SetOfPoints<count, Point<dim>>&& _s, std::array<double, count>&& FuncVals) :
			SimplexSimple<count, PointVal<dim>>{ make_field(std::move(_s), std::move(FuncVals)) }
		{
		}
		SimplexValNoSort(SetOfPoints<count, PointVal<dim>>&& _s) :
			SimplexSimple<count, PointVal<dim>>{ std::move(_s) }
		{
		}

		double MeanVal() const
		{
			double result{ ItsSimplex[0].Val };
			for (int i = 1; i < count; i++)
				result = result + ItsSimplex[i].Val;
			return result / (count + 0.0);
		}

		std::pair<double, double> DispersionVal() const
		{
			double avg{ MeanVal() };

			double result{ 0.0 };
			for (int i = 0; i < count; i++)
				result += (ItsSimplex[i].Val - avg) * (ItsSimplex[i].Val - avg);
			return { avg, result / (count + 0.0) };
		}

		PointVal<dim> OverallCenter() const
		{
			return PointVal<dim>{std::move(this->SimplexCenter().P), MeanVal()};
		}

		std::pair< PointVal<dim>, PointVal<dim>> OverallRadius() const
		{
			auto [avgVal, dispVal] = DispersionVal();
			auto [avgSimplex, dispSimplex] = DispersionSimplex();

			return { PointVal<dim>{std::move(avgSimplex.P), avgVal} , PointVal<dim>{std::move(dispSimplex.P), dispVal} };
		}
	};
	template<int dim>
	PointVal<dim> OverallVariation(const PointVal<dim>& avg, const PointVal<dim>& disp)
	{
		double val = std::abs(avg.Val / std::sqrt(disp.Val));
		Point<dim> p;
		for (int i = 0; i < dim; i++)
		{
			p[i] = std::abs(avg[i] / std::sqrt(disp[i]));
		}
		return PointVal<dim>{ std::move(p), val };
	}


	template<int count, int dim>
	class SimplexValSort : public SimplexValNoSort<count, dim>
	{
	private:
		void Sort() { std::sort(ItsSimplex.begin(), ItsSimplex.end()); }

	public:
		SimplexValSort() = default;
		SimplexValSort(std::array<Point<dim>, count>&& _s, std::array<double, count>&& FuncVals) :
			SimplexValNoSort<count, dim>{ std::move(_s), std::move(FuncVals)}
		{
			this->Sort();
		}
	};

	namespace AuxMethods
	{
		/// <summary>
		/// Euclidian norm
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		template<int dim>
		double norm(const Point<dim>& x, const Point<dim>& y)
		{
			double s = 0;
			for (int i = 0; i < dim; i++)
				s += (x[i] - y[i]) * (x[i] - y[i]);
			return std::sqrt(s);
		}

		/// <summary>
		/// scalar product of two vectors
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		template <int dim>
		double scalar_product(const Point<dim>& x, const Point<dim>& y)
		{
			double s = 0;
			for (int i = 0; i < dim; i++)
				s += x[i] * y[i];
			return s;
		}


		/// <summary>
		/// returns mean and dispersion as std::pair
		/// </summary>
		/// <param name="simplex"></param>
		/// <returns></returns>
		template <int count, int dim>
		std::pair<Point<dim>, Point<dim>> dispersion(const SetOfPoints<count, Point<dim>>& simplex)
		{
			Point<dim> avg{ mean(simplex) };
			Point<dim> result;

			for (int j = 0; j < dim; j++)
			{
				result[j] = 0.0;
				for (int i = 0; i < count; i++)
				{
					result[j] += std::pow((simplex[i][j] - avg[j]), 2.0);
				}
			}
			result = result / (count + 0.0);
			return { avg, result };
		}

		/// <summary>
		/// variation coefficient for a set of vectors
		/// </summary>
		/// <param name="simplex"></param>
		/// <returns></returns>
		template <int dim>
		Point<dim> var_coef( Point<dim> avg,  Point<dim> disp)
		{
			for (auto& r : disp)
				r = sqrt(r);
			for (auto& r : avg)
				r = abs(r);

			return avg / disp;
		}
		template <int count, int dim>
		Point<dim> var_coef(const SetOfPoints<count, Point<dim>>& simplex)
		{
			auto [avg, disp] = dispersion(simplex);
			return var_coef(avg, disp);
		}

		/// elementwise addition of vector + scalar
		template<int dim>
		Point<dim> operator+(RawPoint<dim> arr, double step)
		{
			for (auto& elem : arr.P)
				elem += step;
			return arr;
		}

	} // AuxMethods
} // OptLib