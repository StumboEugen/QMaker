// 
// �ļ�����shu.cpp
// ˵  ������SHU��ĳ�Ա��������ʵ��
//

//------------------------------------------
//		ͷ�ļ�����
//------------------------------------------
#include <cmath>
#include "shu.h"

//------------------------------------------
//		��������
//------------------------------------------

/// <summary>
/// ���ڳ�ʼ��һ������
/// </summary>
/// <param name="num">����</param>
/// <returns></returns>
SHU::SHU(int num)
{
	this->Num = num;
	this->Den = 1;
}

/// <summary>
/// ���ڳ�ʼ��һ����������������
/// </summary>
/// <param name="num">�������ķ���</param>
/// <param name="den">�������ķ�ĸ������Ϊ��</param>
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
/// Ĭ�ϵĹ��캯��
/// </summary>
/// <returns></returns>
SHU::SHU()
{
	this->Num = 0;
	this->Den = 1;
}

/// <summary>
/// ��������
/// </summary>
/// <returns></returns>
SHU::~SHU()
{
}

/// <summary>
/// ��ȡʵ����ֵ
/// </summary>
/// <returns>ʵ����ֵ</returns>
double SHU::getValue() const
{
	return 1.0 * this->Num / this->Den;
}

/// <summary>
/// ��ȡʵ���ַ���ֵ
/// </summary>
/// <returns>ʵ���ַ���ֵ</returns>
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
/// ����� + ������
/// </summary>
/// <param name="addend">����</param>
/// <returns>������ʵ��</returns>
SHU SHU::operator+(const SHU & addend) const
{
	SHU result = SHU();
	result.Den = (this->Den) * addend.Den;
	result.Num = (this->Num) * addend.Den + (this->Den) * addend.Num;
	result.reduct();
	return result;
}

/// <summary>
/// ����� - ������
/// </summary>
/// <param name="addend">����</param>
/// <returns>������ʵ��</returns>
SHU SHU::operator-(const SHU & subtrahend) const
{
	SHU result = SHU();
	result.Den = (this->Den) * subtrahend.Den;
	result.Num = (this->Num) * subtrahend.Den - (this->Den) * subtrahend.Num;
	result.reduct();
	return result;
}

/// <summary>
/// ����� * ������
/// </summary>
/// <param name="addend">����</param>
/// <returns>������ʵ��</returns>
SHU SHU::operator*(const SHU & multiplier) const
{
	SHU result = SHU();
	result.Num = (this->Num) * multiplier.Num;
	result.Den = (this->Den) * multiplier.Den;
	result.reduct();
	return result;
}

/// <summary>
/// ����� / ������
/// </summary>
/// <param name="addend">����</param>
/// <returns>������ʵ��</returns>
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
/// ��ȡʵ���ַ���ֵ
/// </summary>
/// <returns>ʵ���ַ���ֵ</returns>
void SHU::reduct()
{
	int gcd = this->getGCD(abs(this->Num), this->Den);
	this->Num /= gcd;
	this->Den /= gcd;
}

/// <summary>
/// �������������Լ�����ݹ鷨��
/// ���� X > Y
/// </summary>
/// <param name="x">��1</param>
/// <param name="y">��2</param>
/// <returns>ʵ���ַ���ֵ</returns>
int SHU::getGCD(int x, int y)
{
	if (x % y == 0)
		return y;
	else
		return this->getGCD(y, x % y);
}

/// <summary>
/// ��Ԫ����� + ������
/// </summary>
/// <returns>������ʵ��</returns>
SHU operator+(int a, const SHU & b)
{
	SHU result = SHU(a);
	result = result + b;
	return result;
}

/// <summary>
/// ��Ԫ����� - ������
/// </summary>
/// <returns>������ʵ��</returns>
SHU operator-(int a, const SHU & b)
{
	SHU result = SHU(a);
	result = result - b;
	return result;
}

/// <summary>
/// ��Ԫ����� * ������
/// </summary>
/// <returns>������ʵ��</returns>
SHU operator*(int a, const SHU & b)
{
	SHU result = SHU(a);
	result = result * b;
	return result;
}

/// <summary>
/// ��Ԫ����� / ������
/// </summary>
/// <returns>������ʵ��</returns>
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