#pragma once
#include <bits/stdc++.h>
using namespace std;
class Admin {
	string _strUsername;
	string _strPassword;
public:
	Admin() {};
	Admin(string a, string b) {
		_strUsername = a;
		_strPassword = b;
	}
	friend istream& operator>>(istream& is, Admin& a) {
		is >> a._strUsername >> a._strPassword;
		return is;
	}
	friend ostream& operator<<(ostream& os, Admin a) {
		os << a._strUsername << " " << a._strPassword;
		return os;
	}
	friend bool operator!=(Admin a, Admin b) {
		return (a._strUsername != b._strUsername && a._strPassword !=b._strPassword);
	}
	friend bool operator==(Admin a, Admin b) {
		return (a._strUsername == b._strUsername && a._strPassword == b._strPassword);
	}
};

