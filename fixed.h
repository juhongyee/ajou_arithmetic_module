#define FX_SYSTEM   FX_U_14_18
#define __COMPILE_OPTION_M32	1		//0 M64 1 M32

#define PI 3.141593f
#define PI_reciprocal 0.318310f
#define NATURAL_e 2.718282f
#define log10 2.302585f
#define log2 0.693147f
#define sqrt_2 1.414214f
#define sqrt_3 1.732051f

#if FX_SYSTEM == FX_U_14_18

typedef unsigned int fixed;

extern fixed fromFloat(float f);
extern float toFloat(fixed x);
extern fixed add(fixed args,...);
extern fixed minus(fixed args,...);
extern fixed fx_mul_f(fixed a,fixed b);
extern fixed fx_mul_o(fixed a,fixed b);
extern fixed fx_mul_64(fixed a, fixed b);
extern fixed fx_mul_with_integer(fixed a, fixed b);
extern fixed fx_div_f(fixed a,fixed b);
extern fixed fx_div(fixed a,fixed b);
extern fixed fx_div_64(fixed a, fixed b);
extern fixed fx_div_reciprocal(fixed a,fixed b);

#endif
