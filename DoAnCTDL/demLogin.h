#pragma once
#include <bits/stdc++.h>
using namespace std;
class demLogin {
	string _strAccount_Number;
	int _d;
public:
	demLogin(string stk = "",int d = 0) {
		_strAccount_Number = stk;
		_d = d;
	}
	void operator=(const demLogin& a) {
		_strAccount_Number = a._strAccount_Number;
		_d = a._d;
	}
	void loginFail() {
		_d++;
	}
	int getD() {
		return _d;
	}
	string getID() {
		return _strAccount_Number;
	}
	friend bool operator==(demLogin a, demLogin b) {
		return (a.getID() == b.getID());
	}
	void operator*=(demLogin a) {
		_d = a.getD();
	}
	int operator++(int z) {
		loginFail();
		return 0;
	}
	friend ostream& operator<<(ostream& os, demLogin a) {
		os << a._strAccount_Number;
		return os;
	}
};