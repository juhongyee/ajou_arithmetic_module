#include "fixed.h"

#if FX_SYSTEM == FX_U_14_18

fixed fromFloat(float f)
{
	int ret;
	ret = (fixed) (f * (1<< FX_Q_NUM));
	return ret;
}

float toFloat(fixed x)
{
	return (float) x / 256.0f;
}

#endif

