#pragma once
#include <bits/stdc++.h>
#include "Admin.h"
#include "TheTu.h"
#include "User.h"
#include "BanUser.h"
#include "History.h"
#include "demLogin.h"
using namespace std;
template <class DataType>
class Node {
public:
	DataType _data; //Giá trị của Node

	Node* _pNext; //Con trỏ trỏ đến Node kế tiếp

	/**************************************************************
    * @Description Khởi tạo một Node mới có giá trị là data
    **************************************************************/
	Node(DataType data) {
		_data = data;
		_pNext = NULL;
	}
	/**************************************************************
    * @Description Hiển thị giá trị Node
    **************************************************************/
	void display() {
		cout << _data<<endl;
	}
};
template <class DataType>
class LinkedList {
	Node<DataType>* _pHead;
	Node<DataType>* _pTail;
	int _iSize;
public:
	LinkedList() {
		_pHead = NULL;
		_pTail = NULL;
		_iSize = 0;
	};
	/**************************************************************
    * @Description Thêm một phần tử vào đầu LinkedList
    * @parameter Giá trị của phần tử cần thêm
    ***************************************************************/
	void addHead(DataType data) {
		Node<DataType>* pAdd = new Node<DataType>(data);
		if (_pHead == NULL) _pHead = _pTail = pAdd;
		else {
			pAdd->_pNext = _pHead;
			_pHead = pAdd;
		}
		_iSize++;
	}
	/**************************************************************
    * @Description Thêm một phần tử vào cuối LinkedList
    * @parameter Giá trị của phần tử cần thêm
    ***************************************************************/
	void addTail(DataType data) {
		Node<DataType>* pAdd = new Node<DataType>(data);
		if (_pHead == NULL) _pHead = _pTail = pAdd;
		else {
			_pTail->_pNext = pAdd;
			_pTail = pAdd;
		}
		_iSize++;
	}
	/*************************************************************
    * @Description Xuất toàn bộ dữ liệu của LinkedList
    *************************************************************/
	void display() {
		Node<DataType>* pWalker = _pHead;
		while (pWalker != NULL) {
			pWalker->display();
			pWalker = pWalker->_pNext;
		}
	}
	/*************************************************************
    * @Description Xuất toàn bộ dữ liệu về ID.txt
    *************************************************************/
	void displayID() {
		ofstream f("[ID].txt");
		Node<DataType>* pWalker = _pHead;
		while (pWalker != NULL) {
			if (pWalker == _pTail)
				f << pWalker->_data;
			else f << pWalker->_data << endl;
			pWalker = pWalker->_pNext;
		}
	}
	/*************************************************************
    * @Description Xuất toàn bộ dữ liệu về [LichSuID].txt
    *************************************************************/
	void displayHistory() {
		ofstream f("[LichSuID].txt");
		Node<DataType>* pWalker = _pHead;
		while (pWalker != NULL) {
			if (pWalker == _pTail)
				f << pWalker->_data;
			else f << pWalker->_data << endl;
			pWalker = pWalker->_pNext;
		}
	}
	/*************************************************************
    * @Description Xuất toàn bộ dữ liệu về TheTu.txt
    *************************************************************/
	void displayTheTu() {
		ofstream f("TheTu.txt");
		Node<DataType>* pWalker = _pHead;
		while (pWalker != NULL) {
			if (pWalker == _pTail)
				f << pWalker->_data;
			else f << pWalker->_data << endl;
			pWalker = pWalker->_pNext;
		}
	}
	/*************************************************************
    * @Description Xuất toàn bộ dữ liệu về ListBanUser.txt
    *************************************************************/
	void displayBanList() {
		ofstream f("ListBanUser.txt");
		Node<DataType>* pWalker = _pHead;
		while (pWalker != NULL) {
			if (pWalker == _pTail)
				f << pWalker->_data;
			else f << pWalker->_data << endl;
			pWalker = pWalker->_pNext;
		}
	}
	/*************************************************************
    * @Description Xuất toàn bộ dữ liệu về demLogin.txt
    *************************************************************/
	void displayLogin() {
		ofstream f("demLogin.txt");
		Node<DataType>* pWalker = _pHead;
		while (pWalker != NULL) {
			if (pWalker == _pTail)
				f << pWalker->_data;
			else f << pWalker->_data << endl;
			pWalker = pWalker->_pNext;
		}
	}
	/************************************************************
    * @Description Xóa phần tử có khóa là data trong LinkedList
    ************************************************************/
	void remove(DataType data){
		Node<DataType>* pWalker = _pHead, * pTemp = NULL;
		while ((pWalker != NULL) && (pWalker->_data != data)){
			pTemp = pWalker;	pWalker = pWalker->_pNext;
		}
		if (pWalker == NULL) return;
		if (pTemp != NULL){
			if (pWalker == _pTail)
			{
				_pTail = pTemp;
				_pTail->_pNext = NULL;
			}
			pTemp->_pNext = pWalker->_pNext;
			delete pWalker;
			_iSize--;
		}
	}
	/************************************************************
    * @Description Kiểm tra thông tin đăng nhập của Admin
    ************************************************************/
	bool checkAdmin(DataType data) {
		Node<DataType>* pWalker = _pHead;
		Node<DataType>* tmp = new Node<DataType>(data);
		while (pWalker != NULL) {
			if (pWalker->_data == tmp->_data) return true;
			pWalker = pWalker->_pNext;
		}
		return false;
	}
	/************************************************************
    * @Description Kiểm tra thông tin đăng nhập của User
    ************************************************************/
	bool checkUser(DataType data) {
		Node<DataType>* pWalker = _pHead;
		Node<DataType>* tmp = new Node<DataType>(data);
		while (pWalker != NULL) {
			if (pWalker->_data * tmp->_data) return true;
			pWalker = pWalker->_pNext;
		}
		return false;
	}
	/************************************************************
    * @Description Tìm một phần tử trong LinkedList khi biết khóa
    * @parameter Giá trị khóa của phần tử cần tìm
    * @return Trả về phần tử được tìm thấy, NULL nếu không tìm thấy
    *************************************************************/
	bool search(DataType data){
		Node<DataType>* pWalker = _pHead;
		while (pWalker != NULL) {
			if (pWalker->_data ==data) return true;
			pWalker = pWalker->_pNext;
		}
		return false;
	}

	// bool search *
	bool search1(DataType data) {
		Node<DataType>* pWalker = _pHead;
		while (pWalker != NULL) {
			if (pWalker->_data * data) return true;
			pWalker = pWalker->_pNext;
		}
		return false;
	}
	// bool search *
	bool search11(DataType data) {
		Node<DataType>* pWalker = _pHead;
		while (pWalker != NULL) {
			if (pWalker->_data == data) return true;
			pWalker = pWalker->_pNext;
		}
		return false;
	}
	// Data search *
	DataType search2(DataType data) {
		Node<DataType>* pWalker = _pHead;
		while (pWalker != NULL) {
			if (pWalker->_data * data) return pWalker->_data;
			pWalker = pWalker->_pNext;
		}
	}

	// void search 
	void search3(DataType data, LinkedList& l) {
		Node<DataType>* pWalker = _pHead;
		while (pWalker != NULL) {
			if (pWalker->_data != data) {
				l.addTail(pWalker->_data);
			}
			pWalker = pWalker->_pNext;
		}
	}

	// Data search ==
	DataType search4(DataType data) {
		Node<DataType>* pWalker = _pHead;
		while (pWalker != NULL) {
			if (pWalker->_data == data) return pWalker->_data;
			pWalker = pWalker->_pNext;
		}
	}

	// bool search ==
	bool search5(DataType data) {
		Node<DataType>* pWalker = _pHead;
		while (pWalker != NULL) {
			if (pWalker->_data == data) return true;
			pWalker = pWalker->_pNext;
		}
		return false;
	}
	
	// change tìm kiếm * gán *=
	void changeValue(DataType data) {
		for (Node<DataType>* pWalker = _pHead; pWalker; pWalker = pWalker->_pNext) {
			if (pWalker->_data * data) {
				pWalker->_data *= data;
				return;
			}
		}
	}
	// change tìm kiếm == gán *=
	void changeValue1(DataType data) {
		for (Node<DataType>* pWalker = _pHead; pWalker; pWalker = pWalker->_pNext) {
			if (pWalker->_data == data) {
				pWalker->_data *= data;
				return;
			}
		}
	}

	// find and up value
	DataType loginFailUp(DataType& data) {
		for (Node<DataType>* pWalker = _pHead; pWalker; pWalker = pWalker->_pNext) {
			if (pWalker->_data == data) {
				pWalker->_data++;
				return pWalker->_data;
			}
		}
	}

	//Hàm fake Mảng 
	DataType operator[](int i) {
		Node<DataType>* pWalker = _pHead;
		int ii = 0;
		for (Node<DataType>* pWalker = _pHead; pWalker; pWalker = pWalker->_pNext) {
			if (ii == i)
				return pWalker->_data;
			else ii++;
		}
	}
	/************************************************************
    * @Description Lấy số lượng phần tử có trong LinkedList
     @return Trả về số phần tử có trong LinkedList
    ***********************************************************/
	int getSize() {
		return _iSize;
	}
};

