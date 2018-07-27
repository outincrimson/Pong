#pragma once
#include <array>
#include <math.h>

template<typename T, size_t N, size_t M = N>
struct Matrix
{
	using dot_type = typename std::conditional<!(N == M && N == 1), Matrix<T, 1, M>, T>::type;
	friend std::ostream& operator << ( std::ostream& os, const Matrix& rhs )
	{
		for(auto& row : rhs)
		{
			for(auto& col : row)
			{
				os << col << " ";
			}
			os << "\n";
		}
		return os;
	}
public:
	template<typename U>
	explicit constexpr operator Matrix<U, N, M>() const
	{
		Matrix<U, N, M> result;
		for(size_t i = 0; i < N; i++)
		{
			for(size_t j = 0; j < M; j++)
			{
				result[i][j] = (U) elements[i][j];
			}
		}
		return result;
	}
	explicit constexpr operator T() const noexcept
	{
		static_assert(std::is_arithmetic<dot_type>::value);
		return elements[0][0];
	}

	constexpr Matrix operator+( const Matrix& rhs ) const
	{
		Matrix result = *this;
		for(size_t i = 0; i < N; i++)
		{
			for(size_t j = 0; j < M; j++)
			{
				result.elements[i][j] += rhs.elements[i][j];
			}
		}
		return result;
	}
	constexpr Matrix& operator+=( const Matrix& rhs )
	{
		return *this = *this + rhs;
	}

	template<size_t N1, size_t M1 = N1>
	constexpr Matrix<T, N, M1> operator*( const Matrix<T, N1, M1>& rhs ) const
	{
		static_assert(M == N1);
		Matrix<T, N, M1> result;
		for(size_t i = 0; i < N; i++)
		{
			for(size_t m = 0; m < M1; m++)
			{
				auto sum = T { 0 };
				for(size_t n = 0; n < M; n++)
				{
					sum += elements[i][n] * rhs.elements[n][m];
				}
				result.elements[i][m] = sum;
			}
		}
		return result;
	}

	constexpr Matrix& operator*=( const Matrix& rhs )
	{
		return *this = *this * rhs;
	}

	constexpr Matrix operator*( T k ) const
	{
		Matrix result = *this;
		for(auto& row : result)
		{
			for(auto& col : row)
			{
				col *= k;
			}
		}
		return result;
	}
	constexpr Matrix& operator*=( T k )
	{
		return *this = *this * k;
	}
	constexpr Matrix operator/( T k ) const
	{
		Matrix result = *this;
		for(auto& row : result)
		{
			for(auto& col : row)
			{
				col /= k;
			}
		}
		return result;
	}
	constexpr Matrix& operator/=( T k )
	{
		return *this = *this / k;
	}

	constexpr dot_type dot( const Matrix& rhs ) const
	{
		Matrix<T, 1, M> result;
		for(size_t j = 0; j < M; j++)
		{
			auto val = T { 0 };
			for(size_t i = 0; i < N; i++)
			{
				val += elements[i][j] * rhs.elements[i][j];
			}
			result.elements[0][j] = val;
		}
		return (dot_type) result;
	}

	constexpr auto& operator[]( size_t p )
	{
		return elements[p];
	}
	constexpr const auto& operator[]( size_t p ) const
	{
		return elements[p];
	}

	constexpr auto begin()
	{
		return elements.begin();
	}
	constexpr auto end()
	{
		return elements.end();
	}
	constexpr auto begin() const
	{
		return elements.begin();
	}
	constexpr auto end() const
	{
		return elements.end();
	}
	constexpr auto cbegin() const
	{
		return elements.cbegin();
	}
	constexpr auto cend() const
	{
		return elements.cend();
	}

	static constexpr Matrix identity()
	{
		static_assert(N == M);
		Matrix id_mat { };
		for(int i = 0; i < N; i++)
		{
			id_mat[i][i] = T { 1 };
		}
		return id_mat;
	}
	static constexpr Matrix scaling( T k )
	{
		return identity() * k;
	}

	static constexpr Matrix rotate_x( T theta )
	{
		static_assert(N == M && N == 3);
		const T sin_theta = sin( theta );
		const T cos_theta = cos( theta );
		return
		{
			(T) 1,  (T) 0,     (T) 0,
			(T) 0,  cos_theta, sin_theta,
			(T) 0, -sin_theta, cos_theta,
		};
	}
	static constexpr Matrix rotate_y( T theta )
	{
		static_assert(N == M && N == 3);
		const T sin_theta = std::sin( theta );
		const T cos_theta = std::cos( theta );
		return
		{
			cos_theta, (T) 0, -sin_theta,
			(T) 0,     (T) 1, (T) 0,
			sin_theta, (T) 0, cos_theta
		};
	}
	static constexpr Matrix rotate_z( T theta )
	{
		static_assert(N == M && N == 3);
		const T sin_theta = sin( theta );
		const T cos_theta = cos( theta );
		return
		{
			cos_theta,  sin_theta, (T) 0,
			-sin_theta, cos_theta, (T) 0,
			(T) 0,      (T) 0,     (T) 1
		};
	}

	static constexpr Matrix rotate( T theta )
	{
		static_assert(N == M && N == 2);
		const T cos_theta = cos( theta );
		const T sin_theta = sin( theta );
		return
		{
			cos_theta,	sin_theta,
			-sin_theta,	cos_theta
		};
	}

public:
	std::array<std::array<T, M>, N> elements;

};


using Mat3d = Matrix<double, 3>;
using Mat3f = Matrix<float, 3>;
using Mat3i = Matrix<int, 3>;
using Mat3u = Matrix<unsigned int, 3>;

using Mat2d = Matrix<double, 2>;
using Mat2f = Matrix<float, 2>;
using Mat2i = Matrix<int, 2>;
using Mat2u = Matrix<unsigned int, 2>;