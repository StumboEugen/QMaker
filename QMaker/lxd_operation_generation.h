// 
// �ļ�����lxd_operation_generation.h
// ˵  ����lxd_operation_generation.cpp ͷ�ļ���������ʽ��������������غ�����������
//
#ifndef LOG_H
#define LOG_H
//------------------------------------------
//		ͷ�ļ�����
//------------------------------------------
#include<vector>
#include<iostream>
#include"time.h"	
#include"stdlib.h"
#include"stdio.h"
#include <string>
#include<queue>
#include<sstream>
#include"shu.h"
using std::string;
using std::vector;
using std::queue;
using std::cout;
using std::endl;
//------------------------------------------
//		�ඨ��
//------------------------------------------
class Equation
{
public:
	string equation;
	SHU result;
};
// ����: TreeNode
// ˵�������������ݽṹ����ʽ��������
class TreeNode
{
public:
	int val;
	string type;
	string symbol;
	SHU number;
	int level;
	//������ز�����
	int osign;       //������Ӱ��λ
	int msign;	   //������Ӱ��λ
	TreeNode *left, *right;                //����������ָ��
	TreeNode(int);
	TreeNode();
	~TreeNode();
	string cal(int);					   //������ʽ
	SHU answer();						   //����
	void prePrint(TreeNode *);			   //ǰ�����
	void Link_num(TreeNode* root, string dir);//�����������Ӻ���----�ڲ����
	void Link_num(TreeNode* root, string dir, SHU numb);//�����������Ӻ���----�ⲿ����
	int generate_operation(); //�������ͬʱ��������----�ڲ����
	int generate_operation(vector <SHU>,vector <int>); //�������ͬʱ��������----�ⲿ����
//	Equation generate_equation(int);	   //���ýӿ�----�ڲ����
	Equation generate_equation(vector <SHU>, vector <int>);//���ýӿ�----�ⲿ����
	void see();              //��������������
	TreeNode* RandT(int n);
	string symbol_get(int);
};
int rand_area(int, int);                   //�����
string rand_symbol();					   //�������
//string num2str(int i);                     //c��������ת�ַ���
#endif