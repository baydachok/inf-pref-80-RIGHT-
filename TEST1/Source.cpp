#include <iostream>

using namespace std;

struct Operators
{
	Operators* next;
	char symbol;
};
struct Itog
{
	Itog* next;
	string num;
};

char popOp(Operators*& top);
string popNum(Itog*& top);
void pushOp(Operators*& top, Itog*& nums, char d, string& newstr);
void pushNum(Itog*& nums, string d);
void pushNum(Itog*& nums, char d);
void result(string s, Itog*& s1, Operators*& w);




char popOp(Operators*& top) {
	char temp = top->symbol;
	Operators* pv = top;
	top = top->next;
	delete pv;
	return temp;

}
string popNum(Itog*& top) {
	string temp = top->num;
	Itog* pv = top;
	top = top->next;
	delete pv;
	return temp;

}

void pushOp(Operators*& top, Itog*& nums, char d, string& newstr) {
	if (top == nullptr) {
		Operators* p = new Operators;
		p->next = nullptr; p->symbol = d;
		top = p;
	}
	else {
		if (d == ')') {
			while (top->symbol != '(') {
				char tempop = popOp(top);
				string n1 = popNum(nums);
				string n2 = popNum(nums);
				string ssnew = tempop + n2 + n1;
				pushNum(nums, ssnew);
			}
			char tempop = popOp(top);
		}
		else if (d == '*' || d == '/') {
			if (top->symbol != '/' && top->symbol != '*') {
				Operators* pv = new Operators;
				pv->symbol = d;
				pv->next = top;
				top = pv;
			}
			else {
				char tempop = top->symbol;
				top->symbol = d;
				string n1 = popNum(nums);
				string n2 = popNum(nums);
				string s = tempop + n2 + n1;
				pushNum(nums, s);
			}
		}
		else {
			if (top->symbol != '+' && top->symbol != '-') {
				char tempop = top->symbol;
				top->symbol = d;
				string n1 = popNum(nums);
				string n2 = popNum(nums);
				string s = tempop + n2 + n1;
				pushNum(nums, s);
				
			}
			
			while((top->symbol == '+' || top->symbol == '-') && (top->next->symbol == '+' || top->next->symbol == '-')) {
				Operators* temp = top;
				char ch = top->symbol;
				top = top->next;
				delete temp;
				temp = nullptr;
				string n1 = popNum(nums);
				string n2 = popNum(nums);
				string s = ch + n2 + n1;
				pushNum(nums, s);
				if (top->next == nullptr) break;
			}
		}

	}
}
void pushNum(Itog*& nums, string d) {
	if (nums == nullptr) {
		Itog* p = new Itog;
		p->next = nullptr; p->num = d;
		nums = p;
	}
	else {
		Itog* pv = new Itog;
		pv->num = d;
		pv->next = nums;
		nums = pv;
	}
}
void pushNum(Itog*& nums, char d) {
	if (nums == nullptr) {
		Itog* p = new Itog;
		p->next = nullptr; p->num = d;
		nums = p;
	}
	else {
		Itog* pv = new Itog;
		pv->num = d;
		pv->next = nums;
		nums = pv;
	}
}
void result(string s, Itog*& s1, Operators*& w) {
	string* newstr = new string;
	for (char i : s) {
		if (i != '(' && i != ')' && i != '-' && i != '+' && i != '/' && i != '*') {
			pushNum(s1, i);
		}
		else
		{
			pushOp(w, s1, i, *newstr);
		}
	}
	while (w) {

		char tempop = popOp(w);
		string n1 = popNum(s1);
		string n2 = popNum(s1);
		string ssnew = tempop + n2 + n1;
		pushNum(s1, ssnew);


	}
	cout << s1->num;
}



int main() {
	string s = "a+b*d+c";
	Itog* s1 = nullptr;
	Operators* w = nullptr;
	result(s, s1, w);

}