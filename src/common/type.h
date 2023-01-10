#pragma once

#include <cstdint>

// Vectors
template<typename T>
struct vector2
{
	T x, y; 
	vector2 operator* (float _fval)
	{
		return vector2
		{
			this->x *= _fval,
			this->y *= _fval
		};
	}
};

template<typename T>
struct vector3  
{ 
	T x, y, z; 
	vector3 operator* (float _fval)
	{
		return vector3
		{
			this->x *= _fval,
			this->y *= _fval,
			this->z *= _fval
		};
	}
};

template<typename T>
struct vector4
{ 
	T x, y, z, w; 
	vector4 operator* (float _fval)
	{
		return vector4
		{
			this->x *= _fval,
			this->y *= _fval,
			this->z *= _fval,
			this->w *= _fval
		};
	}
};

// Color vectors
struct rgb { uint8_t r, g, b; };
struct rgba { uint8_t r, g, b, a; };