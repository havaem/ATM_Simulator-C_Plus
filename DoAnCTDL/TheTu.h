#pragma once
#include <bits/stdc++.h>
using namespace std;
class TheTu {
	string _strID;
	string _strPIN;
public:
	TheTu(string _ID = "", string _PIN = "123456") {
		_strID = _ID;
		_strPIN = _PIN;
	};
	string getID() {
		return _strID;
	}
	string getPIN() {
		return _strPIN;
	}
	void Change_PIN(string s) {
		_strPIN = s;
	}
	friend bool operator*(TheTu a, TheTu b) {
		return (a.getID() == b.getID() && a.getPIN() == b.getPIN());
	}
	/***********************************************************
	 * Kiểm tra xem giá trị của hai toán hạng có bằng nhau hay không 
	 * Nếu có thì điều kiện trở thành true.
	*************************************************************/
	friend bool operator==(TheTu a, TheTu b) {
		return (a.getID() == b.getID());
	}
	/************************************************************
	 *Kiểm tra xem giá trị của hai TheTu có bằng nhau hay không 
	 *Nếu các giá trị không bằng nhau thì điều kiện trở thành true.
	 ************************************************************/
	friend bool operator!=(TheTu a, TheTu b) {
		return (a.getID() != b.getID());
	}
	void operator*=(TheTu a) {
		_strPIN = a.getPIN();
	}
	/***************************************************************
	* Xuất TheTu
	****************************************************************/
	friend ostream& operator<<(ostream& os, TheTu a) {
		os <<a._strID <<" "<< a._strPIN;
		return os;
	}
};
