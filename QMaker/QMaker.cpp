// QMaker.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "QMaker.h"

;
map<string, SHU> QMaker::makeQs() {
	Qlist.clear();
	//cout << "jxlsb" << endl;
	for (size_t i = 0; i < q_num; i++) {
		bool made = false;
		do {
			nums.clear();
			operators.clear();
			size_t num_counts = getRand(maxLength - minLength) + minLength;
			for (size_t j = 0; j < num_counts; j++) {
				int a = getRand(maxNum) + 1;
				nums.push_back(SHU(a));
			}
			for (size_t j = 0; j < num_counts - 1; j++) {
				if (haveMultip) {
					int a = getRand(4) + 1;
					operators.push_back(a);
				} else {
					int a = getRand(2) + 1;
					operators.push_back(a);
				}
			}

			try {
				
				TreeNode suanshi;
				auto eq = suanshi.generate_equation(nums, operators);
				SHU answer = eq.result;
				string str_suanshi = eq.equation;

				if (answer.getValue() != answer.getValue()) {
					continue;
				}

				if (!allowNegative && answer.getValue() < 0) {
					continue;
				}

				made = Qlist.insert({ str_suanshi, answer }).second;
			}
			catch (const std::exception& ex) {
				cout << "exception!" << endl;
			}
			
		} while (!made);
	}
	return Qlist;
}

void QMaker::buildByLevel(size_t level) {
	if (level == 0)
		level++;
	else if (level > level_num)
		level = level_num;
	level--;
	maxLength = difc_maxLen[level];
	minLength = difc_minLen[level];
	haveMultip = difc_Mult[level];
	maxNum = difc_maxNum[level];
	allowNegative = difc_allowNegative[level];
}

int main() {
	QMaker q(2, 5);
	auto themap = q.makeQs();
	for (auto &xt: themap) {
		cout << xt.first << "=\t" << xt.second.getString() << endl;
	}
	q.setHaveMultip(true);
	q.setMaxLength(6);
	q.setMinLength(5);
	q.setQ_num(3);
	q.setAllowNegative(false);
	themap = q.makeQs();
	for (auto &xt : themap) {
		cout << xt.first << "=\t" << xt.second.getString() << endl;
	}
	system("pause");
	return 0;
}