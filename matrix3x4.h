#pragma once

inline unsigned long& FloatBits(float& f)
{
	return *reinterpret_cast<unsigned long*>(&f);
}

inline unsigned long const& FloatBits(float const& f)
{
	return *reinterpret_cast<unsigned long const*>(&f);
}

inline float BitsToFloat(unsigned long i)
{
	return *reinterpret_cast<float*>(&i);
}

inline bool IsFinite(const float& f)
{
	return ((FloatBits(f) & 0x7F800000) != 0x7F800000);
}


struct matrix3x4_t
{
	matrix3x4_t() {}
	//matrix3x4_t(
	//	float m00, float m01, float m02, float m03,
	//	float m10, float m11, float m12, float m13,
	//	float m20, float m21, float m22, float m23)
	//{
	//	m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
	//	m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
	//	m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	//}

	///// Creates a matrix where the X axis = forward the Y axis = left, and the Z axis = up
	//void InitXYZ(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis, const Vector3& vecOrigin)
	//{
	//	m_flMatVal[0][0] = xAxis[0]; m_flMatVal[0][1] = yAxis[0]; m_flMatVal[0][2] = zAxis[0]; m_flMatVal[0][3] = vecOrigin[0];
	//	m_flMatVal[1][0] = xAxis[1]; m_flMatVal[1][1] = yAxis[1]; m_flMatVal[1][2] = zAxis[1]; m_flMatVal[1][3] = vecOrigin[1];
	//	m_flMatVal[2][0] = xAxis[1]; m_flMatVal[2][1] = yAxis[2]; m_flMatVal[2][2] = zAxis[2]; m_flMatVal[2][3] = vecOrigin[2];
	//}

	////-----------------------------------------------------------------------------
	//// Creates a matrix where the X axis = forward
	//// the Y axis = left, and the Z axis = up
	////-----------------------------------------------------------------------------
	//void Init(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis, const Vector3& vecOrigin)
	//{
	//	m_flMatVal[0][0] = xAxis[0]; m_flMatVal[0][1] = yAxis[0]; m_flMatVal[0][2] = zAxis[0]; m_flMatVal[0][3] = vecOrigin[0];
	//	m_flMatVal[1][0] = xAxis[1]; m_flMatVal[1][1] = yAxis[1]; m_flMatVal[1][2] = zAxis[1]; m_flMatVal[1][3] = vecOrigin[1];
	//	m_flMatVal[2][0] = xAxis[2]; m_flMatVal[2][1] = yAxis[2]; m_flMatVal[2][2] = zAxis[2]; m_flMatVal[2][3] = vecOrigin[2];
	//}

	////-----------------------------------------------------------------------------
	//// Creates a matrix where the X axis = forward
	//// the Y axis = left, and the Z axis = up
	////-----------------------------------------------------------------------------
	//matrix3x4_t(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis, const Vector3& vecOrigin)
	//{
	//	Init(xAxis, yAxis, zAxis, vecOrigin);
	//}

	///// modify the origin
	//inline void SetOrigin(Vector3 const& p)
	//{
	//	m_flMatVal[0][3] = p[0];
	//	m_flMatVal[1][3] = p[1];
	//	m_flMatVal[2][3] = p[2];
	//}

	/// return the origin
	inline Vector3 GetOrigin(void) const
	{
		Vector3 vecRet(m_flMatVal[0][3], m_flMatVal[1][3], m_flMatVal[2][3]);
		return vecRet;
	}

	inline void Invalidate(void)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_flMatVal[i][j] = 0.f;
			}
		}
	}

	/// check all components for invalid floating point values
	inline bool IsValid(void) const
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (!IsFinite(m_flMatVal[i][j]))
					return false;
			}
		}
		return true;
	}

	bool operator==(const matrix3x4_t& other) const
	{
		return memcmp(this, &other, sizeof(matrix3x4_t)) == 0;
	}

	bool operator!=(const matrix3x4_t& other) const
	{
		return memcmp(this, &other, sizeof(matrix3x4_t)) != 0;
	}

	float* operator[](int i) { assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
	const float* operator[](int i) const { assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
	float* Base() { return &m_flMatVal[0][0]; }
	const float* Base() const { return &m_flMatVal[0][0]; }

	float m_flMatVal[3][4];
};
