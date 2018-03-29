#include<vector>
#include<iostream>
#include"time.h"	
#include"stdlib.h"
#include"stdio.h"
#include<string>
#include<queue>
#include<sstream>
#include"shu.h"
#include"lxd_operation_generation.h"
using std::string;
using std::vector;
using std::queue;
using std::cout;
using std::endl;

int rand_area(int min, int max){
	return rand() % (max - min + 1) + min;
}

string rand_symbol(){
	int sym = rand_area(1, 4);
	if (sym == 1)
	{
		return "+";
	}
	if (sym == 2)
	{
		return "-";
	}
	if (sym == 3)
	{
		return "×";
	}
	else
	{
		return "÷";
	}
}

TreeNode::TreeNode(){
}

TreeNode::~TreeNode(){
}

string TreeNode::cal(int sign)//无法在返回值为类的情况下使用string库 原因不明 暂时拆成两个函数
{
	if (this->type == "num")
	{
		return (this->number).getString();
	}
	else if (this->type == "sym")
	{
		if ((sign == 1 && (this->symbol != "×") && this->symbol != "÷")||sign ==2) //爹让加括号 自己不是乘除时 加 或爹是除法且自己在右侧时 加
		{
			string s = "(" + this->left->cal(this->osign) + this->symbol + this->right->cal(this->msign) + ")";
			return s;
		}
		else
		{
			string s = this->left->cal(this->osign) + this->symbol + this->right->cal(this->msign);
			return s;
		}
	}
}

SHU TreeNode::answer()
{
	if (this->type == "num") return this->number;
	else if (this->type == "sym")
	{
		if (this->symbol == "+")
		{
			return (this->left->answer() + this->right->answer());
		}
		if (this->symbol == "-")
		{
			return (this->left->answer() - this->right->answer());
		}
		if (this->symbol == "×")
		{
			return this->left->answer() * this->right->answer() *1.0;
		}
		if (this->symbol == "÷")
		{
			return this->left->answer() / this->right->answer() *1.0;
		}
	}
}

TreeNode::TreeNode(int val) {
	this->val = val;
	this->left = this->right = NULL;
}

TreeNode* TreeNode::RandT(int n) {            //生成随机二叉树
	if(n<1)
	{
		return NULL;//要求生成0个节点的空叶或输入为错误的负数时 返回空指针
	}
	else if (n == 1)
	{
		TreeNode *T = new TreeNode(n);  	//生成一个节点的叶节点
		T->left = NULL;
		T->right = NULL;
		return T;
	}
	else
	{										//生成下层包含多个节点的根节点时
		int left_num = rand_area(1,n-1);    //不包含本节点 随机分配为两个子树
		int right_num = n-1-left_num;     	//重复迭代
		TreeNode *T = new TreeNode(n);
		T->left = this -> RandT(left_num);
		T->right = this->RandT(right_num);
		return T;
	}
}

void TreeNode::see() {                       //层序遍历 观察树形态
	if (this == NULL)
	{
		cout<<"空树"<<endl;
		return;
	}
	queue<TreeNode*> que;
	int currentCount = 1;
	int nextCount = 0;
	int lev = 1;
	que.push(this);
	while (!que.empty()) {
		TreeNode* r = que.front();
		que.pop();
		if (r->type == "sym")
		{
			cout << r->symbol << " ";
		}
		else if (r->type == "num")
		{
			cout << (r->number).getString() << " ";
		}
		else
		{
			cout << r->val<<" ";
		}
		currentCount--;
		if (r->left) {
			que.push(r->left);
			nextCount++;
		}
		if (r->right) {
			que.push(r->right);
			nextCount++;
		}
		if (currentCount == 0) {             //层结束
			currentCount = nextCount;
			nextCount = 0;
			lev = lev + 1;
			cout << endl;
		}
	}
	return;
}

void TreeNode::prePrint(TreeNode* root){    //前序遍历
	if (root == NULL)
	{
		return;
	}
	cout << root->val << ",";
	if (root->left)
	{
		prePrint(root->left);
	}
	if (root->right)
	{
		prePrint(root->right);
	}
}  

int TreeNode::generate_operation() {
	if (this == NULL)
		return 0;
	queue<TreeNode*> que;
	int currentCount = 1;
	int nextCount = 0;
	int lev = 1;
	que.push(this);
	while (!que.empty()) {
		TreeNode* p = que.front();
		que.pop();
		p->type = "sym";            //根节点 符号位
		p->symbol = rand_symbol();  //随机生成符号
		if (p->symbol == "+")
		{
			p->osign = 0;
			p->msign = 0;
		}
		else if (p->symbol == "-")
		{
			p->osign = 0;
			p->msign = 1;
		}
		else if(p->symbol == "÷")
		{
			p->osign = 1;
			p->msign = 2;
		}
		else
		{
			p->osign = 1;
			p->msign = 1;
		}
		p->level = lev;             //记录层数
		currentCount--;
		if (p->left) {              //左根存在 
			que.push(p->left);
			nextCount++;
		}
		else                        //左根不存在 补齐叶数字
		{
			Link_num(p, "left");
		}
		if (p->right) {				//右根存在
			que.push(p->right);
			nextCount++;
		}
		else                        //右根不存在 补齐叶数字
		{
			Link_num(p, "right");
		}
		if (currentCount == 0) {             //一层结束
			currentCount = nextCount;
			nextCount = 0;
			lev = lev + 1;
		}
	}
	return lev;
}

int TreeNode::generate_operation(vector<SHU> shuzi,vector <int> fuhao) {
	if (this == NULL)
		return 0;
	queue<TreeNode*> que;
	int currentCount = 1;
	int nextCount = 0;
	int lev = 1;
	int shuzi_count = 0;
	int fuhao_count = 0;
	que.push(this);
	while (!que.empty()) {
		TreeNode* p = que.front();
		que.pop();
		p->type = "sym";            //根节点 符号位
		p->symbol = symbol_get(fuhao[fuhao_count]);
		fuhao_count++;
		if (p->symbol == "+")
		{
			p->osign = 0;
			p->msign = 0;
		}
		else if (p->symbol == "-")
		{
			p->osign = 0;
			p->msign = 1;
		}
		else if (p->symbol == "÷")
		{
			p->osign = 1;
			p->msign = 2;
		}
		else
		{
			p->osign = 1;
			p->msign = 1;
		}
		p->level = lev;             //记录层数
		currentCount--;
		if (p->left) {              //左根存在 
			que.push(p->left);
			nextCount++;
		}
		else                        //左根不存在 补齐叶数字
		{
			Link_num(p, "left",shuzi[shuzi_count]);
			shuzi_count++;
		}
		if (p->right) {				//右根存在
			que.push(p->right);
			nextCount++;
		}
		else                        //右根不存在 补齐叶数字
		{
			Link_num(p, "right", shuzi[shuzi_count]);
			shuzi_count++;
		}
		if (currentCount == 0) {             //一层结束
			currentCount = nextCount;
			nextCount = 0;
			lev = lev + 1;
		}
	}
	return lev;
}

void TreeNode::Link_num(TreeNode* root, string dir){
	TreeNode* L;
	L = new TreeNode(0);
	L->type = "num";
	L->number = rand_area(1, 10);
	L->left = NULL;
	L->right = NULL;
	if (dir == "left")
	{
		root->left = L;
	}
	else if (dir == "right")
	{
		root->right = L;
	}
}

void TreeNode::Link_num(TreeNode* root, string dir,SHU numb) {
	TreeNode* L;
	L = new TreeNode(0);
	L->type = "num";
	L->number = numb;
	L->left = NULL;
	L->right = NULL;
	if (dir == "left")
	{
		root->left = L;
	}
	else if (dir == "right")
	{
		root->right = L;
	}
}

string TreeNode::symbol_get(int n)
{
	if (n==1)
	{
		return "+";
	}
	else if (n == 2)
	{
		return "-";
	}
	else if (n == 3)
	{
		return "×";
	}
	else
	{
		return "÷";
	}
}

Equation TreeNode::generate_equation(vector<SHU> shuzi, vector <int> fuhao)
{
	Equation eq;
	eq.equation = "NuLL";
	eq.result = SHU(0);
	if ((shuzi.size() - fuhao.size()) != 1)
	{
		//cout << "error";
		throw(std::exception("shuzi.size() - fuhao.size()) != 1"));
		return eq;
	}
	else
	{
		TreeNode* new_tree = new TreeNode();
		new_tree = new_tree->RandT(fuhao.size());
		new_tree->generate_operation(shuzi, fuhao);
		eq.equation = new_tree->cal(0);
		eq.result = new_tree->answer();
		delete new_tree;
		return eq;
	}
}

//int main()
//{
//	srand(time(NULL));  //时间种子 增强随机性  内部随机时影响算式数字 符号 运算结构顺序 外部随机时仅影响算式结构顺序
//	TreeNode* fuck_tree = new TreeNode();
//	Equation eq;
//	vector <SHU> shuzi;
//	vector <int> fuhao;
//	shuzi.push_back(SHU(2, 5));
//	shuzi.push_back(SHU(3, 7));
//	shuzi.push_back(SHU(1, 5));
//	shuzi.push_back(SHU(2, 9));
//	fuhao.push_back(1);
//	fuhao.push_back(4);
//	fuhao.push_back(3);
//	for (int i = 0;i<100;i++)
//	{
//		eq = fuck_tree->generate_equation(shuzi, fuhao);  //这个是外部输入函数 测试可用
//		cout << eq.equation << endl;                      //需要输入数字vector和符号vector 数字要多1个
//		cout << eq.result.getString() << endl;			  //需要先声明一个Equation 类 和 TreeNode 类
//	}
//	/*if ((shuzi.size() - fuhao.size()) != 1)
//	{
//		cout << "error";
//	}
//	else
//	{
//		fuck_tree = fuck_tree->RandT(fuhao.size());
//	}
//	fuck_tree->generate_operation(shuzi, fuhao);
//	fuck_tree->see();
//	cout << fuck_tree->cal(0) << endl;
//	cout << fuck_tree->answer().getString() << endl;*/
//
//	/*for(int i =0 ;i<10;i++)
//	{
//		fuck_tree = fuck_tree->RandT(5);
//		//fuck_tree->see();
//		fuck_tree->generate_operation();
//		//fuck_tree->see();
//		cout << fuck_tree->cal(0) << endl;
//		cout << fuck_tree->answer().getString() << endl;
//	}*/
//		
//	system("pause");
//	return 0;
//}