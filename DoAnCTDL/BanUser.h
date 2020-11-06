#pragma once
#include <bits/stdc++.h>
using namespace std;
class BanUser {
	string _strID;
	string _strStatus;
public:
	BanUser(string _ID="", string _Status="") {
		_strID = _ID;
		_strStatus = _Status;
	};
	friend ostream& operator<<(ostream& os, BanUser a) {
		os << a._strID << endl << a._strStatus;
		return os;
	}
	string getID() {
		return _strID;
	}
	string getStatus() {
		return _strStatus;
	}
	friend bool operator==(BanUser a, BanUser b) {
		return (a.getID() == b.getID());
	}
	friend bool operator!=(BanUser a, BanUser b) {
		return (a.getID() != b.getID());
	}
	void operator*=(BanUser a) {
		_strStatus = a.getStatus();
	}
};

