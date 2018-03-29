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
		return "��";
	}
	else
	{
		return "��";
	}
}

TreeNode::TreeNode(){
}

TreeNode::~TreeNode(){
}

string TreeNode::cal(int sign)//�޷��ڷ���ֵΪ��������ʹ��string�� ԭ���� ��ʱ�����������
{
	if (this->type == "num")
	{
		return (this->number).getString();
	}
	else if (this->type == "sym")
	{
		if ((sign == 1 && (this->symbol != "��") && this->symbol != "��")||sign ==2) //���ü����� �Լ����ǳ˳�ʱ �� ����ǳ������Լ����Ҳ�ʱ ��
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
		if (this->symbol == "��")
		{
			return this->left->answer() * this->right->answer() *1.0;
		}
		if (this->symbol == "��")
		{
			return this->left->answer() / this->right->answer() *1.0;
		}
	}
}

TreeNode::TreeNode(int val) {
	this->val = val;
	this->left = this->right = NULL;
}

TreeNode* TreeNode::RandT(int n) {            //�������������
	if(n<1)
	{
		return NULL;//Ҫ������0���ڵ�Ŀ�Ҷ������Ϊ����ĸ���ʱ ���ؿ�ָ��
	}
	else if (n == 1)
	{
		TreeNode *T = new TreeNode(n);  	//����һ���ڵ��Ҷ�ڵ�
		T->left = NULL;
		T->right = NULL;
		return T;
	}
	else
	{										//�����²��������ڵ�ĸ��ڵ�ʱ
		int left_num = rand_area(1,n-1);    //���������ڵ� �������Ϊ��������
		int right_num = n-1-left_num;     	//�ظ�����
		TreeNode *T = new TreeNode(n);
		T->left = this -> RandT(left_num);
		T->right = this->RandT(right_num);
		return T;
	}
}

void TreeNode::see() {                       //������� �۲�����̬
	if (this == NULL)
	{
		cout<<"����"<<endl;
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
		if (currentCount == 0) {             //�����
			currentCount = nextCount;
			nextCount = 0;
			lev = lev + 1;
			cout << endl;
		}
	}
	return;
}

void TreeNode::prePrint(TreeNode* root){    //ǰ�����
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
		p->type = "sym";            //���ڵ� ����λ
		p->symbol = rand_symbol();  //������ɷ���
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
		else if(p->symbol == "��")
		{
			p->osign = 1;
			p->msign = 2;
		}
		else
		{
			p->osign = 1;
			p->msign = 1;
		}
		p->level = lev;             //��¼����
		currentCount--;
		if (p->left) {              //������� 
			que.push(p->left);
			nextCount++;
		}
		else                        //��������� ����Ҷ����
		{
			Link_num(p, "left");
		}
		if (p->right) {				//�Ҹ�����
			que.push(p->right);
			nextCount++;
		}
		else                        //�Ҹ������� ����Ҷ����
		{
			Link_num(p, "right");
		}
		if (currentCount == 0) {             //һ�����
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
		p->type = "sym";            //���ڵ� ����λ
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
		else if (p->symbol == "��")
		{
			p->osign = 1;
			p->msign = 2;
		}
		else
		{
			p->osign = 1;
			p->msign = 1;
		}
		p->level = lev;             //��¼����
		currentCount--;
		if (p->left) {              //������� 
			que.push(p->left);
			nextCount++;
		}
		else                        //��������� ����Ҷ����
		{
			Link_num(p, "left",shuzi[shuzi_count]);
			shuzi_count++;
		}
		if (p->right) {				//�Ҹ�����
			que.push(p->right);
			nextCount++;
		}
		else                        //�Ҹ������� ����Ҷ����
		{
			Link_num(p, "right", shuzi[shuzi_count]);
			shuzi_count++;
		}
		if (currentCount == 0) {             //һ�����
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
		return "��";
	}
	else
	{
		return "��";
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
//	srand(time(NULL));  //ʱ������ ��ǿ�����  �ڲ����ʱӰ����ʽ���� ���� ����ṹ˳�� �ⲿ���ʱ��Ӱ����ʽ�ṹ˳��
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
//		eq = fuck_tree->generate_equation(shuzi, fuhao);  //������ⲿ���뺯�� ���Կ���
//		cout << eq.equation << endl;                      //��Ҫ��������vector�ͷ���vector ����Ҫ��1��
//		cout << eq.result.getString() << endl;			  //��Ҫ������һ��Equation �� �� TreeNode ��
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