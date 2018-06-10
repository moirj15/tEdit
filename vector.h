#ifndef VECTOR_H
#define VECTOR_H

#include "utils.h"

namespace Math {

/**
 * 4D vector 
 */
struct Vec4f {
	float x;
	float y;
	float z;
	float w;

	/**
	 * Constructors.
	 */
	Vec4f(void);
	Vec4f(float _x, float _y, float _z, float _w);
	
	/**
	 * Destructor.
	 */
	~Vec4f(void);

	Vec4f operator -(const Vec4f &b);
	Vec4f operator +(const Vec4f &b);
	Vec4f operator *(const float a);

	void normalize(void);
};

/**
 * 3D vector 
 */
struct Vec3f {
	float x;
	float y;
	float z;

	/**
	 * Constructors.
	 */
	Vec3f(void);
	Vec3f(float _x, float _y, float _z);
	
	/**
	 * Destructor.
	 */
	~Vec3f(void);
	
	/**
	 * Overloaded operators.
	 */
	Vec3f operator- (const Vec3f &b);
	Vec3f operator+ (const Vec3f &b);
	Vec3f operator* (const Vec3f &b);
	Vec3f operator/ (const Vec3f &b);
	
	/**
	 * Scalar multiplication and division.
	 */
	Vec3f operator* (const float a);
	Vec3f operator/ (const float a);
	
	/**
	 * Normalizes the vector.
	 */
	void normalize(void);
	
	/**
	 * Prints the contents of the vector.
	 */
	void printVec(void);
};

/**
 * 2D vector 
 */
struct Vec2f {
	float x;
	float y;

	/**
	 * Constructors.
	 */
	Vec2f(void);
	Vec2f(float _x, float _y);
	
	/**
	 * Destructor.
	 */
	~Vec2f(void);

	/**
	 * Overloaded operators.
	 */
	Vec2f operator- (const Vec2f &b);
	Vec2f operator+ (const Vec2f &b);
	Vec2f operator* (const Vec2f &b);
	Vec2f operator/ (const Vec2f &b);
	
	/**
	 * Scalar multiplication and division.
	 */
	Vec2f operator* (const float a);
	Vec2f operator/ (const float a);
	
	/**
	 * Normalizes the vector.
	 */
	void normalize(void);
	
	/**
	 * Prints the contents of the vector.
	 */
	void printVec(void);
};

/**
 * Takes the given vector and returns a normalized version.
 *
 * @param a: The vector that will be used to construct the normalized vector.
 * @return: The normalized vector.
 */
Vec4f normalize(const Vec4f &a);
Vec3f normalize(const Vec3f &a);
Vec2f normalize(const Vec2f &a);

/**
 * Computes the dot product between the two given vectors.
 *
 * @param a: The first vector.
 * @param b: The second vector.
 * @return: The result of the dot product.
 */
float dot(const Vec4f &a, const Vec4f &b);
float dot(const Vec3f &a, const Vec3f &b);
float dot(const Vec2f &a, const Vec2f &b);


/**
 * Computes the cross product between the two given vectors.
 *
 * @param a: The first vector.
 * @param b: The second vector.
 * @return: The result of the cross product.
 */
Vec3f cross(const Vec3f &a, const Vec3f &b);

}; // end namespace

#endif
