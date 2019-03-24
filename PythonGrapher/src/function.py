import matplotlib.pyplot as plt
import sympy as sp
import math


# 상수
pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
e = 2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274

# 디그리 to 라디안
def radian(x):
	return x * pi / 180

# 라디안 to 디그리
def degree(x):
	return x * 180 / pi

# 제곱
def power(x, y):
	return x ** y

# 제곱근
def root(x):
    i = 1
    n = 1 - ((1 - x) / 2.0)
    while i < 10:
    	n = n - ((n ** 2 - x) / (2 * n))
    	i += 1
    return n

# 팩토리얼
def fac(x):
	i = 1
	n = 1
	while i <= x:
		n = n * i
		i += 1
	return n

# 사인 함수
def sin(x):
    x = radian(x)
    result = 0.0
    for n in range(50):
    	result = result + ((-1) ** n) * (x ** (2 * n + 1)) / fac(2 * n + 1)
    return result
# 코사인 함수
def cos(x):
    x = radian(x)
    result = 0.0
    for n in range(50):
    	result = result + ((-1) ** n) / fac(2 * n) * (x ** (2 * n))
    return result

# 탄젠트 함수
def tan(x):
	return sin(2 * pi * x) / cos(2 * pi * x)

# 아크사인 함수
def asin(x):
	result = 0.0
	if abs(x) > 1.05:
		return sp.nan
	for n in range(60):
		result = result + (fac(2 * n) * (x ** (2 * n + 1))) / ((2 ** (2 * n)) * (fac(n) ** 2) * (2 * n + 1))
	return result

# 아크코사인 함수
def acos(x):
	if (abs(x) > 1).all():
		return sp.nan
	return pi / 2 - asin(x)

# 아크탄젠트 함수
def atan(x):
	a = (1 + (x ** 2)) ** (-0.5)
	b = 1
	for n in range(1000):
		a = 0.5 * (a + b)
		b = root(a * b)
		
	return x / (root(1 + (x ** 2)) * a)

# 자연로그 함수
def ln(x):
    return sp.Piecewise(
    	(-e, x < 0),
    	(log_f(x), True))
    

# 상용로그 함수
def log(x):
	return ln(x) / ln(10)

# 지수 함수
def exp(x):
	return e ** x

def log_f(x):
	result = 0.0
	for n in range(200):
		result = result + (2 / (2 * n + 1)) * (((x - 1) / (x + 1)) ** (2 * n + 1))
	return result