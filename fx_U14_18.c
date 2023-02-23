#include "fixed.h"

#if FX_SYSTEM == FX_U_14_18

#include <stdarg.h>
#include <stdio.h>
#define FX_I_NUM	14
#define FX_Q_NUM    18		// bits number below point
#define FX_Q_FVAL 262144.0f

fixed fx_mul_o(fixed a, fixed b)
{
	fixed I_a = a>>FX_Q_NUM;
	fixed I_b = b>>FX_Q_NUM;
	fixed p_a = (a<<FX_I_NUM)>>FX_I_NUM;
	fixed p_b = (b<<FX_I_NUM)>>FX_I_NUM;

	return (((I_a*I_b)<<FX_Q_NUM)+I_a*p_b+I_b*p_a+(((p_a>>2)*(p_b>>2))>>FX_I_NUM));
}

fixed fx_mul_64(fixed a, fixed b)
{
	return ((long long) a * (long long) b) >> FX_Q_NUM;
}

fixed fx_mul_with_integer(fixed a, fixed b)
{
	//b가 integer일 때 제일 높은 정확도 및 속도
	return a * (b >> FX_Q_NUM);
}

fixed fx_mul_f(fixed a, fixed b)
{
	return (fixed)((float) a * b /FX_Q_FVAL);
}

fixed fromFloat(float f)
{
	fixed ret;

	ret = (fixed) (f*(1<<FX_Q_NUM));
	return ret;
}

float toFloat(fixed x)
{ 
	return (float) (x/FX_Q_FVAL);
}

fixed add(fixed num_args, ...)
{
	va_list ap;
	va_start(ap,num_args);
	fixed sum = 0;

	for(int i = 0;i<num_args;i++)
	{
		sum += va_arg(ap,fixed);
	}
	va_end(ap);

	return sum;
}

fixed minus(fixed num_args, ...)
{
	//subtract all args except first one from first one
        va_list ap;
        va_start(ap,num_args);
        fixed sum = va_arg(ap,fixed);

        for(int i = 0;i<num_args-1;i++)
        {
                sum -= va_arg(ap,fixed);
        }
        va_end(ap);

        return sum;
}

fixed fx_div_f(fixed a,fixed b)
{
	return (fixed) (FX_Q_FVAL * (float)a / (float) b);
}

fixed fx_div_64(fixed a, fixed b)
{
	return (fixed)(((long long)a<<FX_Q_NUM)/b);
}

fixed fx_div(fixed a,fixed b)
{
	return a/b;
}

fixed fx_div_reciprocal_1(fixed a, fixed b)
{
	fixed reciprocal = ((fixed) ((2147483647)/b)<<5); //역수를 구할 떄  1/b가 아닌 미리 2^18을 곱해줌.

	return fx_mul_o(a,reciprocal); 
}

fixed fx_div_reciprocal_2(fixed a, fixed b)
{
	fixed reciprocal = ((2147483647/b)<<5); //오버플로우 방지를 위해 2147493648 이 아닌 2147493647로
	
	return (a*reciprocal)>>FX_Q_NUM;
}

#endif

