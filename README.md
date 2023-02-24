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

함수 설명 : fixed x를 $2^{18}.0f$로 나눔으로써 강제로 float형으로 변환시키는 함수

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

### fx_mul_o
**Precision과 Speed를 동시에 만족하는 함수**

함수 정의 : Integer와 Floating point를 나누어 계산하는 multiplication 함수

함수 설명 : 곱하기연산이 underflow와 overflow에 취약한 점을 개선하고자 고안된 multiplication 함수이며 bitshift와 곱하기 연산만을 사용하므로 충분한 속도를 보장받는다.

### 1. Integer와 Floating 분리
a와 b를 입력받았을 때

a>>18 연산을 할 경우 a의 Integer part만 남음.
b>>18 연산도 마찬가지

(a<<14)>>14 연산을 할 경우 a의 Floating part만 남음.
(b<<14)>>14 연산도 마찬가지

### 2. Integer와 Floating의 연산

간단한 인수분해 공식을 떠올려보자.
현재 a라는 수를 a_I와 a_F라는 정수와 소수로 나눈 상태이다.

즉, a = a_I+a_F.

b도 마찬가지로

b = b_I+b_F라고 할 수 있다.

이 때 **ab = (a_I + a_F)(b_I + b_F) = a_I$\times$b_I + a_F$\times$b_I + a_I$\times$b_F + a_F$\times$b_F** 로 쓸 수 있다.

1. a_I$\times$b_I : 두 Integer를 곱하는 연산을 그냥 해주게 되면 현재 우측으로 18bit 이동한 상태이기 때문에 다시 좌측으로 18bit 이동해주어야 한다. 
즉 (a_I$\times$b_I)<<18로 구현 된다.

**위와 같이 Integer part를 우측 끝까지 bit shift를 해줌으로 overflow를 최대한 방지한채로 연산이 가능하다.**

2. a_F$\times$b_I + a_I$\times$b_F : Integer들은 우측 끝까지 bit shift 되어 있으나 a_F와 b_F는 $2^{18}$이 곱해진 것과 같으므로 그냥 그대로 a_F$\times$b_I + a_I$\times$b_F 와 같이 구현하면 된다.

3. **a_F$\times$b_F**
가장 문제가 되는 부분이다. 그냥 연산을 하게 되면 연산의 정확도가 매우 떨어지게 된다. 

왜냐하면 a_F와 b_F는 각각 18개의 bit로 표현되어 있기 때문이다. a_F와 b_F를 fixed의 float부분이 아닌 그냥 unsigned integer로 간주한다면 a_F,b_F<=$2^{18}-1$이다. 이 때 두 수를 곱하면 a_F$\times$b_F <= 2^{36}-1 부등식이 성립함을 알 수 있고 즉 35bit가 필요하다는 결론을 얻는다.(overflow)



