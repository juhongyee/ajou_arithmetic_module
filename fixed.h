#define FX_SYSTEM   FX_U_14_18
#define __COMPILE_OPTION_M64	1		//0 M64 1 M32

#if FX_SYSTEM == FX_U_24_08
#define FX_Q_NUM    18		// bits number below point

typedef unsigned int fixed;

extern fixed fromFloat(float f);
extern float toFloat(fixed x);

#endif
