#pragma once
#include "stdafx.h"

namespace OptLib
{
	template<int dim>
	using Point = std::array<double, dim>;

	template<int count, int dim>
	using Simplex = std::array<Point<dim>, count>;

	namespace AuxMethods
	{

		template<int dim = 1>
		std::ostream& operator<< (std::ostream& o, const Point<dim>& output)
		{
			o << "{ " << output[0];
			for (int i = 1; i < dim; i++)
				o << ", " << output[i];
			o << " }";

			return o;
		}

		template<int count = 2, int dim = 1>
		std::ostream& operator<< (std::ostream& o, const Simplex<count, dim>& output)
		{
			o << "{ " << output[0];
			for (int i = 1; i < count; i++)
				o << "; " << output[i];
			o << " }";

			return o;
		}

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
		/// returns mean value for a set of vectors
		/// </summary>
		/// <param name="simplex"></param>
		/// <returns></returns>
		template <int count, int dim>
		Point<dim> mean(const Simplex<count, dim>& simplex)
		{
			Point<dim> result{ simplex[0] };
			for (int i = 1; i < count; i++)
				result = result + simplex[i];
			result = result / (count + 0.0);
			return result;
		}

		/// <summary>
		/// returns mean and dispersion as std::pair
		/// </summary>
		/// <param name="simplex"></param>
		/// <returns></returns>
		template <int count, int dim>
		std::pair<Point<dim>, Point<dim>> dispersion(const Simplex<count, dim>& simplex)
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
		Point<dim> var_coef(const Simplex<count, dim>& simplex)
		{
			auto [avg, disp] = dispersion(simplex);
			return var_coef(avg, disp);
		}

		/// elementwise addition of vector + scalar
		template<int dim = 1>
		std::array<double, dim> operator+(Point<dim> arr, double step)
		{
			for (auto& elem : arr)
				elem += step;
			return arr;
		}

		/// elementwise subtraction of vector - vector
		template<int dim = 1>
		std::array<double, dim> operator-(const Point<dim>& arr1, const Point<dim>& arr2)
		{
			std::array<double, dim> result;
			std::transform(arr1.begin(), arr1.end(), arr2.begin(), result.begin(), std::minus<> {});
			return result;
		}

		/// elementwise addition of vector + vector
		template<int dim = 1>
		std::array<double, dim> operator+(const Point<dim>& arr1, const Point<dim>& arr2)
		{
			std::array<double, dim> result;
			std::transform(arr1.begin(), arr1.end(), arr2.begin(), result.begin(), std::plus<> {});
			return result;
		}

		/// elementwise division vectr / scalar
		template<int dim = 1>
		std::array<double, dim> operator/(Point<dim> arr, double val)
		{
			for (auto& elem : arr)
				elem /= val;
			return arr;
		}

		/// elementwise multiplication of vector * vector
		template<int dim = 1>
		std::array<double, dim> operator/(const Point<dim>& arr1, const Point<dim>& arr2)
		{
			Point<dim> result;
			std::transform(arr1.begin(), arr1.end(),
				arr2.begin(), result.begin(), [](double x, double y) {return x / y; });

			return result;
		}

		/// elementwise multiplication of vector * scalar
		template<int dim = 1>
		std::array<double, dim> operator*(Point<dim> arr, double val)
		{
			for (auto& elem : arr)
				elem *= val;
			return arr;
		}
	} // AuxMethods

} // OptLib