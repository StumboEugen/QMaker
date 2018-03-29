// 
// 文件名：lxd_operation_generation.h
// 说  明：lxd_operation_generation.cpp 头文件，对于算式生成与结果计算相关函数进行声明
//
#ifndef LOG_H
#define LOG_H
//------------------------------------------
//		头文件包含
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
//		类定义
//------------------------------------------
class Equation
{
public:
	string equation;
	SHU result;
};
// 类名: TreeNode
// 说明：二叉树数据结构，算式与结果生成
class TreeNode
{
public:
	int val;
	string type;
	string symbol;
	SHU number;
	int level;
	//括号相关布尔量
	int osign;       //左括号影响位
	int msign;	   //右括号影响位
	TreeNode *left, *right;                //二叉树左右指针
	TreeNode(int);
	TreeNode();
	~TreeNode();
	string cal(int);					   //生成算式
	SHU answer();						   //求结果
	void prePrint(TreeNode *);			   //前序遍历
	void Link_num(TreeNode* root, string dir);//补充数字链接函数----内部随机
	void Link_num(TreeNode* root, string dir, SHU numb);//补充数字链接函数----外部输入
	int generate_operation(); //层序遍历同时补充数字----内部随机
	int generate_operation(vector <SHU>,vector <int>); //层序遍历同时补充数字----外部输入
//	Equation generate_equation(int);	   //调用接口----内部随机
	Equation generate_equation(vector <SHU>, vector <int>);//调用接口----外部输入
	void see();              //层序遍历检测树型
	TreeNode* RandT(int n);
	string symbol_get(int);
};
int rand_area(int, int);                   //随机数
string rand_symbol();					   //随机符号
//string num2str(int i);                     //c语言数字转字符串
#endif