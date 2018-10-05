void QuatSlerp(QUAT * from, QUAT * to, float t, QUAT * res)
{
	float to1[4];
	double omega, cosom, sinom, scale0, scale1;

	// calc cosine 
	cosom = from->x * to->x + from->y * to->y + from->z * to->z + from->w * to->w;

	// adjust signs 
	(if necessary)
		if (cosom <0.0)
		{
			cosom = -cosom;
			to1[0] = -to->x;
			to1[1] = -to->y;
			to1[2] = -to->z;
			to1[3] = -to->w;
		}
		else
		{
			to1[0] = to->x;
			to1[1] = to->y;
			to1[2] = to->z;
			to1[3] = to->w;
		}

	// calculate coefficients
	if ((1.0 - cosom) > DELTA)
	{
		// standard case
		(slerp)omega = acos(cosom);
		sinom = sin(omega);
		scale0 = sin((1.0 - t) * omega) / sinom;
		scale1 = sin(t * omega) / sinom;
	}
	else
	{
		// "from" and "to" quaternions are very close
		// ... so we can do a linear interpolation 
		scale0 = 1.0 - t;
		scale1 = t;
	}

	// calculate final values 
	res->x = scale0 * from->x + scale1 * to1[0];
	res->y = scale0 * from->y + scale1 * to1[1];
	res->z = scale0 * from->z + scale1 * to1[2];
	res->w = scale0 * from->w + scale1 * to1[3];
}