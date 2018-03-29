// 
// 文件名：shu.h
// 说  明：shu.cpp 头文件，定义了XITI类和SHU类
//

#ifndef SHU_H
#define SHU_H
//------------------------------------------
//		头文件包含
//------------------------------------------
#include <string>

//------------------------------------------
//		类定义
//------------------------------------------

// 类名:	SHU
// 说明：该类将分数进行封装，并重载了运算符方便运算
class SHU
{
	
public:
	//
	// 公有成员
	//

	//
	// 公有函数
	//
	SHU(int);		// 整数 构造函数
	SHU(int, int);	// 有理数 构造函数
	SHU();			// 默认 构造函数
	~SHU();			// 析构函数

	double getValue() const;		// 获取实例的值
	std::string getString() const;	// 获取实例字符串值

	// 运算符的重载
	SHU operator+(const SHU &) const;
	SHU operator-(const SHU &) const;
	SHU operator*(const SHU &) const;
	SHU operator/(const SHU &) const;
	friend SHU operator+(int, const SHU&);
	friend SHU operator-(int, const SHU&);
	friend SHU operator*(int, const SHU&);
	friend SHU operator/(int, const SHU&);

private:
	//
	// 私有成员
	//
	int Num;		// 分子
	int Den;		// 分母

	//
	// 私有函数
	//
	void reduct();			// 约分
	int getGCD(int, int);	// 求最大公约数（递归法）

};

// 类名:	XITI
// 说明：该类将一道题目进行封装
class XITI
{
public:
	XITI(std::string, SHU);
	XITI();
	~XITI();

private:
	std::string timu;
	SHU answer;
};

#endif