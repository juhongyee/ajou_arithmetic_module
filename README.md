# 실전코딩 기말 프로젝트
## 이주홍
### 202021223

* 내가 만들어야할 프로젝트 : unsigned, Floating 18bit, Integer 14

## 1. Fixed point
fixed point는 고정소수점이라는 의미로, 컴퓨터에서 실수를 표현할 때 Integer bit와 Floating bit를 고정하여 정하여 실수를 표현하는 방식이다.

이번 project에서는 Integer bit를 14bit, Floating bit를 18bit로 할당한 unsigned 32bit 수를 표현하고자 하였다.

$[00000000000000].[000000000000000000]$

**상위 14bit는 Integer bit**, **하위 18bit는 Floating bit**

위와 같은 형식을 따를 때 표현가능한 최댓값과 최솟값을 유추할 수 있다.

최댓값 : $[11111111111111].[111111111111111111]$ : 32767.6185

최솟값 : $[00000000000000].[000000000000000001]$ : 0.3815

**이번 project에서는 unsigned 연산이므로 fixed point를 계산하기 위해 unsigned int형을 fixed형으로 정의하여 사용한다.**

## 2. Calculation Algorithm
## 0) toFloat,fromFloat

### 1. **fromFloat**

함수 정의 : float형을 fixed 형으로 변환하는 함수

함수 설명 : float형에의 변수에는 직접적으로 bit shift를 할 수 없다. 그러므로 1을 18만큼 left bitshift를 하여 곱함으로 bit shift를 한 것과 같은 결과를 유도한다.

이 과정을 통해 32bit computer에서 원래 float형의 하위 integer 14bit와 상위 float 18bit로 구성된 새로운 fixed형 변수를 얻을 수 있다.

함수 코드

    fixed fromFloat(float f)
    {
        fixed ret;

        ret = (fixed) (f*(1<<FX_Q_NUM));
        return ret;
    }


### 2. **toFloat**

함수 정의 : fixed형을 float 형으로 변환하는 함수

함수 설명 : fixed x를 $2^18.0f$로 나눔으로써 강제로 float형으로 변환시키는 함수

함수코드

    float toFloat(fixed x)
    { 
        return (x/FX_Q_FVAL);
    }


## 1) ADD, SUBTRACT
fixed point의 add와 subtract는 매우 간단하다. 특별한 자릿수의 변환없이 덧셈과 뺄셈을 해주면 된다.

이러한 간단한 연산 속에서 본 프로젝트는 **scanf,printf에서 영감을 받아 임의의 개수의 수들를 입력받아 더하거나 빼는 ADD와 SUBTRACT를 구현**하였다.

### 1. **add**
함수 정의 : num_args 만큼의 변수를 parameter로 받아 그 합을 구하는 함수

-----
함수 설명 :
![image.png](./image.png)
출처 : Secure Coding in C and C++(2013)

1. **va_list** ap 작동(va_list는 macro)
이 때 va_list는 pointer가 되어 parameter의 변수들이 모인 맨 처음 주소를 가리킨다.

2. num_args는 입력된 변수가 아닌 변수의 개수만을 가리키므로 num_args의 크기만큼 pointer 이동(va_start macro의 역할)

3. 현재 ap가 가리키는 주소의 값을 sum에 더하고 fixed의 크기만큼 그 주소를 이동시킴.(va_arg macro의 역할)

4. va_end(ap)로 ap가 NULL을 가리키게 함. (종료의미)
-----
함수 코드 : 

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

### 2. **subtract**

Without Lose Of Generality

add의 +를 -로 대체

## 2) multiplication


