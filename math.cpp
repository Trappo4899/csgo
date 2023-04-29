#include "includes.h"

Vector3 math::model_to_world(Vector3 model, matrix3x4_t rotation)
{
	Vector3 out = { };

	auto rot1 = rotation[0];
	auto rot2 = rotation[1];
	auto rot3 = rotation[2];

	out[0] = model.dot({ rot1[0], rot1[1], rot1[2] }) + rotation[0][3];
	out[1] = model.dot({ rot2[0], rot2[1], rot2[2] }) + rotation[1][3];
	out[2] = model.dot({ rot3[0], rot3[1], rot3[2] }) + rotation[2][3];

	return out;
}

Color math::colour_interpolation(Color from, Color to, float min, float max, float val)
{
	float t = (val - min) / (max - min);

	const auto fr = from.r();
	const auto fg = from.g();
	const auto fb = from.b();
	const auto fa = from.a();

	const auto tr = to.r();
	const auto tg = to.g();
	const auto tb = to.b();
	const auto ta = to.a();

	return {
		int((float)fr + ((float)tr - (float)fr) * t),
		int((float)fg + ((float)tg - (float)fg) * t),
		int((float)fb + ((float)tb - (float)fb) * t),
		int((float)fa + ((float)ta - (float)fa) * t)
	};
}