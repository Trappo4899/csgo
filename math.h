#pragma once

namespace math
{
	Vector3 model_to_world(Vector3 model, matrix3x4_t rotation);

	Color colour_interpolation(Color from, Color to, float min, float max, float val);
}