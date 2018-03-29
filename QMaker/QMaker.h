#ifndef QMAKER_H
#define QMAKER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <time.h>
#include "shu.h"
#include "lxd_operation_generation.h"

using namespace std;

class QMaker {
public:
	QMaker(size_t level = 1, size_t q_num = 10) :
		level(level), q_num(q_num) {
		srand((unsigned)time(NULL));
		buildByLevel(level);
	};
	size_t getQ_num() { return q_num; }
	size_t getMaxLength() { return maxLength; }
	size_t getMinLength() { return minLength; }
	size_t getMaxNum() { return maxNum; }
	bool gethaveMultip() { return haveMultip; }
	bool getAllowNegetaive() { return allowNegative; }
	
	///<summary>
	///设置习题集中的习题数量
	///</summary>
	size_t setQ_num(size_t num) {
		if (q_num)
			q_num = num;
		return q_num;
	}

	///<summary>
	///设置算式的最大长度(多少个数字)
	///</summary>
	size_t setMaxLength(size_t len) {
		if (len >= minLength) {
			maxLength = len;
		}
		return maxLength;
	}

	///<summary>
	///设置算式的最小长度(多少个数字)
	///</summary>
	size_t setMinLength(size_t len) {
		if (len <= maxLength) {
			minLength = len;
		}
		return minLength;
	}

	///<summary>
	///是否有乘除号?
	///</summary>
	void setHaveMultip(bool Multip) {
		haveMultip = Multip;
	}
	
	///<summary>
	///设置算式中数字的最大值
	///</summary>
	void setMaxNum(size_t num) {
		maxNum = num;
	}

	///<summary>
	///设置是否允许结果为负号
	///</summary>
	void setAllowNegative(bool b) {
		allowNegative = b;
	};

	///<summary>
	///按照设置,制作习题集
	///</summary>
	map<string, SHU> makeQs();

	///<summary>
	///得到上次制作的习题集
	///</summary>
	map<string, SHU> getQs() { return Qlist; }

private:
	///<summary>
	///按照预先设置的级别,调整难度
	///</summary>
	void buildByLevel(size_t level); 

	///<summary>
	///获取随机数,比如:输入8得到0-7随机数
	///</summary>
	unsigned int getRand(unsigned int max) {
		if (max == 0) {
			return 0;
		}
		return rand() % max;
	}

	static const size_t level_num = 4;
	const bool difc_Mult[level_num] = { false, false, true, true };
	const bool difc_allowNegative[level_num] = { false, true, true, true };
	const size_t difc_maxLen[level_num] = { 2, 4, 2, 5 };
	const size_t difc_minLen[level_num] = { 2, 2, 2, 3 };
	const size_t difc_maxNum[level_num] = { 10, 70, 10, 20 };

	size_t level;
	size_t q_num;
	bool haveMultip;
	bool allowNegative;
	size_t maxLength;
	size_t minLength;
	size_t maxNum;
	map<string, SHU> Qlist;
	vector<SHU> nums;
	vector<int> operators;
}

#endif