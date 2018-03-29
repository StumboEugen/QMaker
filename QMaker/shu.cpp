// 
// 文件名：shu.cpp
// 说  明：对SHU类的成员函数进行实现
//

//------------------------------------------
//		头文件包含
//------------------------------------------
#include <cmath>
#include "shu.h"

//------------------------------------------
//		函数定义
//------------------------------------------

/// <summary>
/// 用于初始化一个整数
/// </summary>
/// <param name="num">整数</param>
/// <returns></returns>
SHU::SHU(int num)
{
	this->Num = num;
	this->Den = 1;
}

/// <summary>
/// 用于初始化一个分数（有理数）
/// </summary>
/// <param name="num">有理数的分子</param>
/// <param name="den">有理数的分母，不能为零</param>
/// <returns></returns>
SHU::SHU(int num, int den)
{
	if (den != 0)
	{
		this->Num = num * (den < 0 ? -1 : 1);
		this->Den = abs(den);
	}
	else
		throw(std::exception("Warning: SHU.Den can't be zero!"));
}

/// <summary>
/// 默认的构造函数
/// </summary>
/// <returns></returns>
SHU::SHU()
{
	this->Num = 0;
	this->Den = 1;
}

/// <summary>
/// 析构函数
/// </summary>
/// <returns></returns>
SHU::~SHU()
{
}

/// <summary>
/// 获取实例的值
/// </summary>
/// <returns>实例的值</returns>
double SHU::getValue() const
{
	return 1.0 * this->Num / this->Den;
}

/// <summary>
/// 获取实例字符串值
/// </summary>
/// <returns>实例字符串值</returns>
std::string SHU::getString() const
{
	std::string s = "";
	char temp_s[30] = "";
	if (this->Den == 1)
	{
		sprintf_s(temp_s, "%d", this->Num);
	}
	else
	{
		sprintf_s(temp_s, "%d/%d", this->Num, this->Den);
	}
	s = temp_s;

	return s;
}

/// <summary>
/// 运算符 + 的重载
/// </summary>
/// <param name="addend">加数</param>
/// <returns>计算结果实例</returns>
SHU SHU::operator+(const SHU & addend) const
{
	SHU result = SHU();
	result.Den = (this->Den) * addend.Den;
	result.Num = (this->Num) * addend.Den + (this->Den) * addend.Num;
	result.reduct();
	return result;
}

/// <summary>
/// 运算符 - 的重载
/// </summary>
/// <param name="addend">减数</param>
/// <returns>计算结果实例</returns>
SHU SHU::operator-(const SHU & subtrahend) const
{
	SHU result = SHU();
	result.Den = (this->Den) * subtrahend.Den;
	result.Num = (this->Num) * subtrahend.Den - (this->Den) * subtrahend.Num;
	result.reduct();
	return result;
}

/// <summary>
/// 运算符 * 的重载
/// </summary>
/// <param name="addend">乘数</param>
/// <returns>计算结果实例</returns>
SHU SHU::operator*(const SHU & multiplier) const
{
	SHU result = SHU();
	result.Num = (this->Num) * multiplier.Num;
	result.Den = (this->Den) * multiplier.Den;
	result.reduct();
	return result;
}

/// <summary>
/// 运算符 / 的重载
/// </summary>
/// <param name="addend">除数</param>
/// <returns>计算结果实例</returns>
SHU SHU::operator/(const SHU & divisor) const
{
	SHU result = SHU();
	if (divisor.getValue() == 0)
		throw(std::exception("Error:divisor can't be Zero!"));
	result.Num = (this->Num) * divisor.Den;
	result.Den = (this->Den) * divisor.Num;
	result.reduct();
	return result;
}

/// <summary>
/// 获取实例字符串值
/// </summary>
/// <returns>实例字符串值</returns>
void SHU::reduct()
{
	int gcd = this->getGCD(abs(this->Num), this->Den);
	this->Num /= gcd;
	this->Den /= gcd;
}

/// <summary>
/// 求两个数的最大公约数（递归法）
/// 假设 X > Y
/// </summary>
/// <param name="x">数1</param>
/// <param name="y">数2</param>
/// <returns>实例字符串值</returns>
int SHU::getGCD(int x, int y)
{
	if (x % y == 0)
		return y;
	else
		return this->getGCD(y, x % y);
}

/// <summary>
/// 友元运算符 + 的重载
/// </summary>
/// <returns>计算结果实例</returns>
SHU operator+(int a, const SHU & b)
{
	SHU result = SHU(a);
	result = result + b;
	return result;
}

/// <summary>
/// 友元运算符 - 的重载
/// </summary>
/// <returns>计算结果实例</returns>
SHU operator-(int a, const SHU & b)
{
	SHU result = SHU(a);
	result = result - b;
	return result;
}

/// <summary>
/// 友元运算符 * 的重载
/// </summary>
/// <returns>计算结果实例</returns>
SHU operator*(int a, const SHU & b)
{
	SHU result = SHU(a);
	result = result * b;
	return result;
}

/// <summary>
/// 友元运算符 / 的重载
/// </summary>
/// <returns>计算结果实例</returns>
SHU operator/(int a, const SHU & b)
{
	SHU result = SHU(a);
	result = result / b;
	return result;
}

inline XITI::XITI(std::string t, SHU a)
{
	this->timu = t; this->answer = a;
}

XITI::XITI()
{
	this->timu = "";
	answer = SHU(0);
}

XITI::~XITI()
{
}