// 
// �ļ�����shu.h
// ˵  ����shu.cpp ͷ�ļ���������XITI���SHU��
//

#ifndef SHU_H
#define SHU_H
//------------------------------------------
//		ͷ�ļ�����
//------------------------------------------
#include <string>

//------------------------------------------
//		�ඨ��
//------------------------------------------

// ����:	SHU
// ˵�������ཫ�������з�װ�����������������������
class SHU
{
	
public:
	//
	// ���г�Ա
	//

	//
	// ���к���
	//
	SHU(int);		// ���� ���캯��
	SHU(int, int);	// ������ ���캯��
	SHU();			// Ĭ�� ���캯��
	~SHU();			// ��������

	double getValue() const;		// ��ȡʵ����ֵ
	std::string getString() const;	// ��ȡʵ���ַ���ֵ

	// �����������
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
	// ˽�г�Ա
	//
	int Num;		// ����
	int Den;		// ��ĸ

	//
	// ˽�к���
	//
	void reduct();			// Լ��
	int getGCD(int, int);	// �����Լ�����ݹ鷨��

};

// ����:	XITI
// ˵�������ཫһ����Ŀ���з�װ
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