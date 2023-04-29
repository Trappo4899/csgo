#pragma once

/* https://www.unknowncheats.me/forum/c-and-c-/157292-variadic-vector-class.html */

template< typename T, size_t _size >
class Vector
{
private:

	std::array<T, _size> m_arr;

public:

	Vector()
	{
		m_arr = { };
	}

	Vector(std::array<T, _size> arr )
	{
		m_arr = arr;
	}

	template < typename... Args >
	Vector(Args... args) : m_arr{ static_cast<T>(std::forward< Args >(args))... } { }

public:

	std::array<T, _size> get()
	{
		return m_arr;
	}

	T& at(int idx)
	{
		if (idx >= 0 && idx <= m_arr.size())
		{
			return m_arr.at(idx);
		}
	}

	float dot(std::array<T, _size> vec)
	{
		float ret = { };

		for (int i = 0; i < _size; i++)
		{
			ret += (m_arr[i] * vec[i]);
		}

		return ret;
	}

	float distance(std::array<T, _size> vec)
	{
		float ret = { };

		for (int i = 0; i < _size; i++)
		{
			ret += powf(m_arr[i] - vec[i], 2);
		}

		return sqrtf(ret);
	}

	float size()
	{
		float ret = { };

		for (int i = 0; i < _size; i++)
		{
			ret += powf(m_arr[i], 2);
		}

		return sqrtf(ret);
	}

public:

	T& operator[](int idx)
	{
		return this->at(idx);
	}

	std::array<T, _size> operator+(std::array<T, _size> vec)
	{
		std::array<T, _size> ret = { };

		for (int i = 0; i < _size; i++)
		{
			ret.at(i) = (m_arr.at(i) + vec.at(i));
		}

		return ret;
	}

	std::array<T, _size> operator-(std::array<T, _size> vec)
	{
		std::array<T, _size> ret = { };

		for (int i = 0; i < _size; i++)
		{
			ret.at(i) = (m_arr.at(i) - vec.at(i));
		}

		return ret;
	}

	void operator+=(std::array<T, _size> vec)
	{
		for (int i = 0; i < _size; i++)
		{
			m_arr.at(i) += vec.at(i);
		}
	}

	void operator-=(std::array<T, _size> vec)
	{
		for (int i = 0; i < _size; i++)
		{
			m_arr.at(i) -= vec.at(i);
		}
	}
};

using   Vector2     = Vector <  float, 2  >;
using   Vector3     = Vector <  float, 3  >;
using   Vector4     = Vector <  float, 4  >;
using   Box         = Vector <  float, 4  >;