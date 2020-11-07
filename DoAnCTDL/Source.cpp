#include "LinkedList.h"
#include "Graphic.h"
#include<string.h>
#include<iostream>

#pragma warning(disable:4996)
#define YELLOW textcolor(14);
#define BLUE textcolor(9);
#define GREEN textcolor(10);
#define MAUXANH textcolor(2);
#define WHITE textcolor(15);
#define RED textcolor(4);
#define LISTADMIN LinkedList<Admin> listAdmin, LinkedList<User> listUser, LinkedList<TheTu> listTheTu,LinkedList<History> listLog,LinkedList<BanUser> listBanUser,LinkedList<demLogin> listLogin
#define CALLLIST listAdmin,listUser,listTheTu,listLog,listBanUser,listLogin
#define ClearSceen system("cls");
using namespace std;

/*********************************************************
* Hàm dùng để load database từ file txt đẩy vào LinkedList
***********************************************************/
void loadAdmin(LinkedList<Admin>& lListAdmin);
void loadID(LinkedList<User>& listUser);
void loadTheTu(LinkedList<TheTu>& listTheTu);
void loadLog(LinkedList<History>& listLog);
void loadBanList(LinkedList<BanUser>& listBanUser);
void loadlistLogin(LinkedList<demLogin>& listLogin);

/*******************************************************
* Hàm giao diện
********************************************************/
void showMain(LISTADMIN);
void showAccessAdmin(LISTADMIN);
void showAccessUser(LISTADMIN,string sUserNow);
void showLoginUser(LISTADMIN);
void showLoginAdmin(LISTADMIN);

/******************************************************
* Chức năng của admin 
********************************************************/
void adminAddUser(LISTADMIN);
void adminDeleteUser(LISTADMIN);
void adminUnlockUser(LISTADMIN);
void adminShowUser(LISTADMIN);

/******************************************************
* Chức năng của user 
*******************************************************/
void userXemSoDu(LISTADMIN,string sUserNow);
void userRutTien(LISTADMIN, string sUserNow);
void userChuyenTien(LISTADMIN, string sUserNow);
void userNoiDungGD(LISTADMIN, string sUserNow);
void userDoiMaPin(LISTADMIN, string sUserNow);

/*****************************************************
* Hàm cập nhật lại database trong file txt
*******************************************************/
void updateHistory(LISTADMIN);
void updateID(LISTADMIN);
void updateTheTu(LISTADMIN);
void updateListBan(LISTADMIN);
void updateListLogin(LISTADMIN);

/******************************************************
* Hàm khởi tạo khung
*******************************************************/
void setKhung(LISTADMIN);
/******************************************************
* Hàm lấy thời gian 
*******************************************************/
const string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), " %X ngày %d tháng %m năm %Y", &tstruct);
	return buf;
}
/******************************************************
* Những hàm xử lý các công việc riêng 
*******************************************************/
void inputPassword(string& pw);
bool checkLoginAdmin(string _strUser, string _strPassword, LinkedList<Admin> listAdmin);
bool checkLoginUser(string _strUser, string _strPassword, LISTADMIN);
void checkRutTien(LISTADMIN, long long _llWallet, User tmp);

/*****************************************************
* Hàm Hiển thị tiếng Việt và các ký tự đặc biệt
******************************************************/
BOOL WINAPI SetConsoleOutputCP(_In_ UINT wCodePageID);

int main() {
	SetConsoleOutputCP(65001);
	resizeConsole(800, 600); // Tạo độ dài và rộng cho console
	LinkedList<Admin> listAdmin;LinkedList<User> listUser;LinkedList<TheTu> listTheTu;LinkedList<History> listLog;LinkedList<BanUser> listBanUser;LinkedList<demLogin> listLogin;
	loadAdmin(listAdmin);loadTheTu(listTheTu);loadLog(listLog);loadID(listUser);loadBanList(listBanUser);loadlistLogin(listLogin);
	showMain(CALLLIST);
	system("pause >nul");
}

/******************************************************
* Hàm hỗ trợ đọc và viết file txt 
*******************************************************/
void loadlistLogin(LinkedList<demLogin>& listLogin) {
	ifstream f;
	f.open("demLogin.txt");
	string _strAccountNumber;
	while (!f.eof()) { 
		f >> _strAccountNumber;
		demLogin tmp(_strAccountNumber, 0);
		listLogin.addTail(tmp);
	}
	f.close();
}
void loadAdmin(LinkedList<Admin>& lListAdmin) {
	ifstream f; 
	f.open("Admin.txt");
	while (!f.eof()) {
		bool _bA = false;
		string sU, sP, stmp;
		getline(f, stmp);
		for (int i = 0; i < stmp.size(); i++) {
			if (stmp[i] == ' ') _bA = true;
			else if (_bA == false) sU.push_back(stmp[i]);
			else sP.push_back(stmp[i]);
		}
		Admin ttmp(sU, sP);
		lListAdmin.addTail(ttmp);
	}
	f.close();
}
void loadID(LinkedList<User>& listUser) {
	ifstream f; 
	f.open("[ID].txt");
	string sNumber, sName, sType;
	long lWallet;
	while (!f.eof()) {
		sNumber = "";
		sName = "";
		lWallet = 0;
		sType = "";
		f >> sNumber;
		f.ignore();
		getline(f, sName);
		f >> lWallet;
		f >> sType;
		User ttmp(sNumber, sName, lWallet, sType);
		listUser.addTail(ttmp);
		f.ignore();
	}
	f.close();
}
void loadTheTu(LinkedList<TheTu>& listTheTu) {
	ifstream f;
	f.open("TheTu.txt");
	string sU, sP, sTmp;
	while (!f.eof()) { 
		sU = "";
		sP = "";
		bool a = false;
		getline(f, sTmp);
		for (int i = 0; i < sTmp.size(); i++) {
			if (sTmp[i] == ' ') a = true;
			else if (a == false) sU.push_back(sTmp[i]);
			else sP.push_back(sTmp[i]);
		}
		TheTu ttmp(sU, sP);
		listTheTu.addTail(ttmp);
	}
	f.close();
}
void loadLog(LinkedList<History>& listLog) {
	ifstream f;
	f.open("[LichSuID].txt");
	string sTmp;
	string sNoti, sSend, sReceive;
	while (!f.eof()) {
		sSend = "";
		sReceive = "";
		sNoti = "";
		getline(f, sNoti);
		f >> sSend;
		f >> sReceive;
		f.ignore();
		History h(sNoti,sSend,sReceive);
		listLog.addTail(h);
	}
	f.close();
}
void loadBanList(LinkedList<BanUser>& listBanUser) {
	ifstream f;
	f.open("ListBanUser.txt");
	string _sID;
	string _sStatus;
	while (!f.eof()) {
		f >> _sID;
		f >> _sStatus;
		BanUser user(_sID,_sStatus);
		listBanUser.addTail(user);
	}
	f.close();
}
void updateHistory(LISTADMIN) {
	listLog.displayHistory();
}
void updateID(LISTADMIN) {
	listUser.displayID();
}
void updateTheTu(LISTADMIN) {
	listTheTu.displayTheTu();
}
void updateListBan(LISTADMIN) {
	listBanUser.displayBanList();
}
void updateListLogin(LISTADMIN) {
	listLogin.displayLogin();
}

/****************************************************
* Hàm dành cho admin 
*****************************************************/
void showLoginAdmin(LISTADMIN) {
	setKhung(CALLLIST);
	bool _bA = false;
	while (!_bA) {
		YELLOW
			gotoxy(42, 15); cout << "* ** ** ** ** ** ** *";
		gotoxy(42, 16); cout << "** "; GREEN cout << "ĐĂNG NHẬP ADMIN"; YELLOW cout << " **" << endl;
		gotoxy(42, 17);  cout << "* ** ** ** ** ** ** *";
		gotoxy(42, 18); BLUE cout << "User     :";
		gotoxy(42, 19); BLUE cout << "Password :";
		gotoxy(53, 18); WHITE string user = ""; cin >> user;
		gotoxy(53, 19); WHITE string password; inputPassword(password);
		gotoxy(41, 20);
		if (checkLoginAdmin(user, password, listAdmin)) {
			MAUXANH cout << "Bạn đã login thành công"; _bA = true;
			Sleep(200);
			ClearSceen
				setKhung(CALLLIST);
			showAccessAdmin(CALLLIST);
		}
		else {
			RED
				cout << "==>Vui lòng thử lại<==";
			Sleep(200);
			ClearSceen //hàm xóa màn hình sau khi nhập sai 
				setKhung(CALLLIST);
		}
	}
}
void showAccessAdmin(LISTADMIN) {
	setKhung(CALLLIST);
	ToMau(32, 13, "* * * * * * * * * *MENU* * * * * * * * * *", 14);
	ToMau(40, 14, "1. Xem danh sách tài khoản", 202);
	ToMau(40, 15, "2. Thêm tài khoản", 14);
	ToMau(40, 16, "3. Xóa tài khoản", 14);
	ToMau(40, 17, "4. Mở khóa tài khoản", 14);
	ToMau(40, 18, "5. Thoát", 14);
	ToMau(30, 19, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	int _iChoose = 0;
	int _iToaDo = 14;
	do {
		char _cA = _getch();
		if (_cA == 80) _iChoose = 1; //bắt sự kiện nút lên 
		else if (_cA == 72) _iChoose = 2;//bắt sự kiện nút enter  
		else if (_cA == 13) _iChoose = 3; // //bắt sự kiện nút xuống
		else _iChoose = 0;
		if (_iChoose == 1 && _iToaDo < 19) _iToaDo++;
		else if (_iChoose == 2 && _iToaDo > 13) _iToaDo--;
		if (_iToaDo == 14) {
			ToMau(40, 14, "1. Xem danh sách tài khoản", 202);
			ToMau(40, 15, "2. Thêm tài khoản", 14);
			ToMau(40, 16, "3. Xóa tài khoản", 14);
			ToMau(40, 17, "4. Mở khóa tài khoản", 14);
			ToMau(40, 18, "5. Thoát", 14);
		}
		if (_iToaDo == 15) {
			ToMau(40, 14, "1. Xem danh sách tài khoản", 14);
			ToMau(40, 15, "2. Thêm tài khoản", 202);
			ToMau(40, 16, "3. Xóa tài khoản", 14);
			ToMau(40, 17, "4. Mở khóa tài khoản", 14);
			ToMau(40, 18, "5. Thoát", 14);
		}
		if (_iToaDo == 16) {
			ToMau(40, 14, "1. Xem danh sách tài khoản", 14);
			ToMau(40, 15, "2. Thêm tài khoản", 14);
			ToMau(40, 16, "3. Xóa tài khoản", 202);
			ToMau(40, 17, "4. Mở khóa tài khoản", 14);
			ToMau(40, 18, "5. Thoát", 14);
		}
		if (_iToaDo == 17) {
			ToMau(40, 14, "1. Xem danh sách tài khoản", 14);
			ToMau(40, 15, "2. Thêm tài khoản", 14);
			ToMau(40, 16, "3. Xóa tài khoản", 14);
			ToMau(40, 17, "4. Mở khóa tài khoản", 202);
			ToMau(40, 18, "5. Thoát", 14);
		}
		if (_iToaDo == 18) {
			ToMau(40, 14, "1. Xem danh sách tài khoản", 14);
			ToMau(40, 15, "2. Thêm tài khoản", 14);
			ToMau(40, 16, "3. Xóa tài khoản", 14);
			ToMau(40, 17, "4. Mở khóa tài khoản", 14);
			ToMau(40, 18, "5. Thoát", 202);
		}
	} while (_iChoose != 3);
	ClearSceen
		if (_iToaDo == 14) {
			ClearSceen
				adminShowUser(CALLLIST);
			char a = _getch();
			if (a != '+') { ClearSceen showAccessAdmin(CALLLIST); }
		}
		else if (_iToaDo == 15) {
			ClearSceen
				adminAddUser(CALLLIST);
		}
		else if (_iToaDo == 16) { ClearSceen adminDeleteUser(CALLLIST); }
		else if (_iToaDo == 17) { ClearSceen adminUnlockUser(CALLLIST); }
		else if (_iToaDo == 18) { showLoginAdmin(CALLLIST); }
}
void adminAddUser(LISTADMIN) {
	setKhung(CALLLIST);
	string sName;
	string sNumberAccount;
	string sType;
	cin.ignore();
	long long llWallet = 0;
	string sWallet = "";
	ToMau(31, 13, "* ** ** ** ** ** **THÊM TÀI KHOẢN* ** ** ** ** ** **", 4);
	ToMau(36, 14, "Họ và tên    : ", 10);
	ToMau(36, 15, "Số tài khoản : ", 10);
	ToMau(36, 16, "Số dư        : ", 10);
	ToMau(36, 17, "Loại tiền    : ", 10);
	ToMau(31, 19, "* ** ** ** ** ** **THÊM TÀI KHOẢN* ** ** ** ** ** **", 4);
	gotoxy(55, 14); getline(cin, sName);
	gotoxy(55, 15); cin >> sNumberAccount;
	gotoxy(55, 16);	cin >> sWallet;
	for (int i = 0; i < sWallet.size(); i++) {
		if (sWallet[i] < 48 || sWallet[i]>57) {
			llWallet = 50000;
		}
		else {
			llWallet = stol(sWallet);
		}
	}
	gotoxy(55, 17); cout<<"VND";
	cin.ignore();
	if (sName.length() == 0) sName = "TESTER";
	if (llWallet < 50000) llWallet = 50000;
	TheTu tmp(sNumberAccount,"123456");
	if (listTheTu.search11(tmp.getID())) {
		gotoxy(40, 20); cout << "Trùng với ID đã tồn tại!!!";
		Sleep(1000);
		ClearSceen
			showAccessAdmin(CALLLIST);
	}
	else if (sNumberAccount.length()!=14) {
		gotoxy(40, 20); cout << "STK bạn nhập chưa đủ 14 số!!";
		Sleep(1000);
		ClearSceen
			showAccessAdmin(CALLLIST);
	}
	else {
		BanUser tmp11(sNumberAccount, "Active");
		listBanUser.addTail(tmp11);
		updateListBan(CALLLIST);
		User tmp1(sNumberAccount, sName, llWallet, sType);
		listUser.addTail(tmp1);
		listTheTu.addTail(tmp);
		string noti = "[" + sNumberAccount + "]-[" + sName + "]" + "-[" + to_string(llWallet) + sType + "] được tạo bởi ADMIN vào lúc" + currentDateTime();
		History notii(noti,"Admin","NewUser");
		listLog.addTail(notii);
		demLogin z(sNumberAccount, 0);
		listLogin.addTail(z);
		updateHistory(CALLLIST);
		updateID(CALLLIST);
		updateTheTu(CALLLIST);
		updateListLogin(CALLLIST);
		ToMau(40, 20, "Bạn đã tạo thành công!!!!", 10);
		Sleep(2000);
		ClearSceen;
		showAccessAdmin(CALLLIST);
		cin.ignore();
	}

}
void adminDeleteUser(LISTADMIN) {
	ToMau(31, 13, "* ** ** ** ** ** **XÓA TÀI KHOẢN* ** ** ** ** ** **", 14);
	ToMau(36, 14, "STK cần xóa  : ", 10);
	ToMau(36, 15, "Lí do xóa    : ", 10);
	ToMau(31, 19, "* ** ** ** ** ** **XÓA TÀI KHOẢN* ** ** ** ** ** **", 14);
	string _sAccountNumber;
	gotoxy(51, 14); cin >> _sAccountNumber;
	User tmp1(_sAccountNumber,"",0,"");
	TheTu tmp2(_sAccountNumber, "");
	BanUser tmp3(_sAccountNumber, "");
	if (listTheTu.search5(tmp2)) {
		listUser.remove(tmp1);
		listTheTu.remove(tmp2);
		listBanUser.remove(tmp3);
		updateTheTu(CALLLIST);
		updateID(CALLLIST);
		updateListBan(CALLLIST);
		string _sReason, _sNoti;
		gotoxy(51, 15); cin.ignore(); getline(cin, _sReason);
		_sNoti = "Admin vừa xóa tài khoản " + _sAccountNumber + " với lí do: " + _sReason + " vào lúc" + currentDateTime();
		History noti1(_sNoti, "Admin", _sAccountNumber);
		listLog.addTail(noti1);
		updateHistory(CALLLIST);
		Sleep(2000);
		ToMau(32, 16, "Bạn đã xóa "+ _sAccountNumber +" thành công!!!", 10);
		Sleep(1000);
		ClearSceen
			showAccessAdmin(CALLLIST);
	}
	else {
		ToMau(32, 16, "Số tài khoản này không tồn tại trong database!!!", 4);
		Sleep(1000);
		ClearSceen
			showAccessAdmin(CALLLIST);
	}
	cin.ignore();
}
void adminUnlockUser(LISTADMIN){
	cin.ignore();
	ToMau(31, 13, "* ** ** ** ** ** **MỞ TÀI KHOẢN* ** ** ** ** ** **", 14);
	ToMau(36, 14, "STK cần mở  : ", 9);
	ToMau(36, 15, "Trạng thái  : ", 9);
	ToMau(31, 16, "* ** ** ** ** ** **MỞ TÀI KHOẢN* ** ** ** ** ** **", 14);
	string _sAccountNumber;
	gotoxy(51, 14); cin >> _sAccountNumber;
	BanUser ttmp(_sAccountNumber, "");
	if (listBanUser.search(ttmp)) {
		BanUser tmp = listBanUser.search4(ttmp);
		if (tmp.getStatus() == "Active") {
			ToMau(51, 15, "Active", 10);
			Sleep(1000);
			ClearSceen
				showAccessAdmin(CALLLIST);
		}
		else {
			ToMau(51, 15, "Ban", 4);
			Sleep(1000);
			ToMau(36, 15, "Mở khóa thành công!!", 2);
			BanUser tmp1(_sAccountNumber, "Active");
			listBanUser.changeValue1(tmp1);
			updateListBan(CALLLIST);
			Sleep(2000);
			ClearSceen
				showAccessAdmin(CALLLIST);
		}
	}
	else {
		ToMau(36, 15, "Số tài khoản bạn nhập không tồn tại!!!", 15);
		Sleep(2000);
		ClearSceen
			showAccessAdmin(CALLLIST);
	}
}
void adminShowUser(LISTADMIN) {
	ClearSceen
		//cout << "║╔ ═ ╗╝╚ ╦ ╠ ╩ ╣ ╬";
	int iNumberLines = 4; 
	int iColorTitle = 11;
	int iQuantity = listUser.getSize();
	int sColorInformations = 15;
	ToMau(1, 1, "╔══════════════════════════╦══════════════════════════╦══════════════════════════╦═══════════════════════╗", 9);
	ToMau(1, 2, "║                          ║                          ║                          ║                       ║",9);
	ToMau(9, 2, "SỐ TÀI KHOẢN", iColorTitle);
	ToMau(38, 2, "HỌ VÀ TÊN", iColorTitle);
	ToMau(66, 2, "SỐ DƯ", iColorTitle);
	ToMau(92, 2, "MÃ PIN", iColorTitle);
	ToMau(1, 3, "╠══════════════════════════╬══════════════════════════╬══════════════════════════╬═══════════════════════╣", 9);
	for (int i = 0; i < iQuantity; i++) {
		User tmp;
		tmp = listUser[i];
		TheTu tmp1 = listTheTu[i];
		ToMau(8, iNumberLines,tmp.getID(), sColorInformations);
		ToMau(33, iNumberLines,tmp.getName(), sColorInformations);
		ToMau(62, iNumberLines,to_string(tmp.getWallet())+ " "+tmp.getType(), sColorInformations);
		ToMau(92, iNumberLines,tmp1.getPIN(), sColorInformations);
		ToMau(1, iNumberLines, "║", 9);
		ToMau(28, iNumberLines, "║", 9);
		ToMau(55, iNumberLines, "║", 9);
		ToMau(82, iNumberLines, "║", 9);
		ToMau(106, iNumberLines, "║", 9);
		if(i<iQuantity-1) ToMau(1, iNumberLines +=1, "╠══════════════════════════╬══════════════════════════╬══════════════════════════╬═══════════════════════╣", 9);
		iNumberLines++;
	}
	ToMau(1, iNumberLines, "╚══════════════════════════╩══════════════════════════╩══════════════════════════╩═══════════════════════╝", 9);
	char _cA = _getch();
	if (_cA != '+') { ClearSceen showAccessAdmin(CALLLIST); }
}

/**************************************************
*  Hàm dành cho user
***************************************************/
void showLoginUser(LISTADMIN) {
	setKhung(CALLLIST);
	bool _bA = false;
	while (!_bA) {
		string sUser = "";
		string sPassword = "";
		YELLOW
			gotoxy(42, 15); cout << "* ** ** ** ** ** ** *";
		gotoxy(42, 16); cout << "** "; BLUE cout << "ĐĂNG NHẬP USER "; YELLOW cout << " **" << endl;
		gotoxy(42, 17);  cout << "* ** ** ** ** ** ** *";
		gotoxy(42, 18); GREEN cout << "ID    :";
		gotoxy(42, 19); GREEN cout << "PIN   :";
		gotoxy(52, 18); WHITE cin >> sUser;
		gotoxy(52, 19); WHITE inputPassword(sPassword);
		gotoxy(41, 20);
		if (checkLoginUser(sUser, sPassword, CALLLIST)) {
			MAUXANH cout << "Bạn đã login thành công"; _bA = true;
			Sleep(200);
			ClearSceen
			setKhung(CALLLIST);
			string sUserNow = sUser;
			showAccessUser(CALLLIST, sUserNow);
		}
		else {
			BanUser z(sUser, "");
			if (listBanUser.search5(z)) {
				BanUser zz = listBanUser.search4(z);
				if (zz.getStatus() == "Ban") {
					RED
						cout << "Tài khoản này đã bị Ban";
					Sleep(1500);
					ClearSceen
						setKhung(CALLLIST);
				}
				else {
					demLogin t(sUser, 0);
					demLogin tmp = listLogin.search4(t);
					tmp = listLogin.loginFailUp(tmp);
					if (tmp.getD() == 3) {
						BanUser tmp1(sUser, "Ban");
						listBanUser.changeValue1(tmp1);
						updateListBan(CALLLIST);
					}
					RED
						cout << "==>Vui lòng thử lại<==";
					Sleep(1500);
					ClearSceen
						setKhung(CALLLIST);
				}
			}
			else {
				RED
					cout << "==>Vui lòng thử lại<==";
				Sleep(1000);
				ClearSceen
					setKhung(CALLLIST);
			}
		}
	}
}
void showAccessUser(LISTADMIN,string sUserNow) {
	setKhung(CALLLIST);
	ToMau(32, 13, "* * * * * * * * * *MENU* * * * * * * * * *", 14);
	ToMau(40, 14, "1. Xem thông tin tài khoản", 202);
	ToMau(40, 15, "2. Rút tiền", 14);
	ToMau(40, 16, "3. Chuyển tiền", 14);
	ToMau(40, 17, "4. Xem nội dung giao dịch", 14);
	ToMau(40, 18, "5. Đổi mã pin", 14);
	ToMau(40, 19, "6. Thoát", 14);
	ToMau(30, 20, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	int iChoose = 0;
	int iToaDo = 14;
	do {
		char a = _getch();
		if (a == 80) iChoose = 1; //bắt sự kiện nút lên 
		else if (a == 72) iChoose = 2;//bắt sự kiện nút enter  
		else if (a == 13) iChoose = 3; // //bắt sự kiện nút xuống
		else iChoose = 0;
		if (iChoose == 1 && iToaDo < 20) iToaDo++;
		else if (iChoose == 2 && iToaDo > 13) iToaDo--;
		if (iToaDo == 14){
			ToMau(40, 14, "1. Xem thông tin tài khoản", 202);
			ToMau(40, 15, "2. Rút tiền", 14);
			ToMau(40, 16, "3. Chuyển tiền", 14);
			ToMau(40, 17, "4. Xem nội dung giao dịch", 14);
			ToMau(40, 18, "5. Đổi mã pin", 14);
			ToMau(40, 19, "6. Thoát", 14);
		}
		if (iToaDo == 15){
			ToMau(40, 14, "1. Xem thông tin tài khoản", 14);
			ToMau(40, 15, "2. Rút tiền", 202);
			ToMau(40, 16, "3. Chuyển tiền", 14);
			ToMau(40, 17, "4. Xem nội dung giao dịch", 14);
			ToMau(40, 18, "5. Đổi mã pin", 14);
			ToMau(40, 19, "6. Thoát", 14);
		}
		if (iToaDo == 16){
			ToMau(40, 14, "1. Xem thông tin tài khoản", 14);
			ToMau(40, 15, "2. Rút tiền", 14);
			ToMau(40, 16, "3. Chuyển tiền", 202);
			ToMau(40, 17, "4. Xem nội dung giao dịch", 14);
			ToMau(40, 18, "5. Đổi mã pin", 14);
			ToMau(40, 19, "6. Thoát", 14);
		}
		if (iToaDo == 17){
			ToMau(40, 14, "1. Xem thông tin tài khoản", 14);
			ToMau(40, 15, "2. Rút tiền", 14);
			ToMau(40, 16, "3. Chuyển tiền", 14);
			ToMau(40, 17, "4. Xem nội dung giao dịch", 202);
			ToMau(40, 18, "5. Đổi mã pin", 14);
			ToMau(40, 19, "6. Thoát", 14);
		}
		if (iToaDo == 18){
			ToMau(40, 14, "1. Xem thông tin tài khoản", 14);
			ToMau(40, 15, "2. Rút tiền", 14);
			ToMau(40, 16, "3. Chuyển tiền", 14);
			ToMau(40, 17, "4. Xem nội dung giao dịch", 14);
			ToMau(40, 18, "5. Đổi mã pin", 202);
			ToMau(40, 19, "6. Thoát", 14);
		}
		if (iToaDo == 19){
			ToMau(40, 14, "1. Xem thông tin tài khoản", 14);
			ToMau(40, 15, "2. Rút tiền", 14);
			ToMau(40, 16, "3. Chuyển tiền", 14);
			ToMau(40, 17, "4. Xem nội dung giao dịch", 14);
			ToMau(40, 18, "5. Đổi mã pin", 14);
			ToMau(40, 19, "6. Thoát", 202);
		}
	} while (iChoose != 3);
	ClearSceen
		if (iToaDo == 14) userXemSoDu(CALLLIST, sUserNow);
		else if (iToaDo == 15) userRutTien(CALLLIST, sUserNow);
		else if (iToaDo == 16) userChuyenTien(CALLLIST, sUserNow);
		else if (iToaDo == 17) userNoiDungGD(CALLLIST, sUserNow);
		else if (iToaDo == 18) userDoiMaPin(CALLLIST, sUserNow);
	else if (iToaDo == 19) showLoginUser(CALLLIST);
}
void userXemSoDu(LISTADMIN,string sUserNow) {
	setKhung(CALLLIST);
	string sAccountNumber, sName, sWallet, sType;
	User ttmp(sUserNow,"",0,"");
	User tmp = listUser.search2(ttmp);
	ToMau(32, 13, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	ToMau(38, 14, "1.Số tài khoản: ", 14);
	ToMau(38, 15, "2.Họ và tên   : ", 14);
	ToMau(38, 16, "3.Số dư       : ", 14);
	ToMau(38, 17, "4.Đơn vị tiền : ", 14);
	ToMau(38, 18, "5.Trạng thái  : ", 14);
	ToMau(30, 19, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	Sleep(200); gotoxy(54, 14); BLUE cout << tmp.getID();
	Sleep(200); gotoxy(54, 15); WHITE cout<< tmp.getName();
	Sleep(200); gotoxy(54, 16); WHITE cout<< tmp.getWallet();
	Sleep(200); gotoxy(54, 17); RED cout<<tmp.getType();
	Sleep(200); gotoxy(54, 18); GREEN cout << "Online";
	char _cA = _getch();
	if (_cA != '+') {
		ClearSceen
			setKhung(CALLLIST);
		showAccessUser(CALLLIST, sUserNow);
	}
}
void userRutTien(LISTADMIN, string sUserNow) {
	setKhung(CALLLIST);
	string sAccountNumber, sName, sWallet, sType;
	User ttmp(sUserNow, "", 0, "");
	User tmp = listUser.search2(ttmp);
	ToMau(32, 13, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	ToMau(34, 14, "[50000] ", 32);
	ToMau(34, 16, "[100000]", 91);
	ToMau(34, 18, "[200000]", 91);
	ToMau(65, 14, "[400000]", 91);
	ToMau(65, 16, "[500000]", 91);
	ToMau(64, 18, " SỐ KHÁC ", 91);
	ToMau(50, 16, "THOÁT", 91);
	ToMau(30, 19, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	int iChoose = 0;
	int iToaDo = 14;
	do {
		char _cA = _getch();
		if (_cA == 80) iChoose = 1; //bắt sự kiện nút lên 
		else if (_cA == 72) iChoose = 2;//bắt sự kiện nút enter  
		else if (_cA == 13) iChoose = 3; // //bắt sự kiện nút xuống
		else iChoose = 0;
		if (iChoose == 1 && iToaDo < 21) iToaDo++;
		else if (iChoose == 2 && iToaDo > 13) iToaDo--;
		if (iToaDo == 14) {
			ToMau(34, 14, "[50000] ", 32);
			ToMau(34, 16, "[100000]", 91);
			ToMau(34, 18, "[200000]", 91);
			ToMau(65, 14, "[400000]", 91);
			ToMau(65, 16, "[500000]", 91);
			ToMau(64, 18, " SỐ KHÁC ", 91);
			ToMau(50, 16, "THOÁT", 91);
		}
		if (iToaDo == 15) {
			ToMau(34, 14, "[50000] ", 91);
			ToMau(34, 16, "[100000]", 32);
			ToMau(34, 18, "[200000]", 91);
			ToMau(65, 14, "[400000]", 91);
			ToMau(65, 16, "[500000]", 91);
			ToMau(64, 18, " SỐ KHÁC ", 91);
			ToMau(50, 16, "THOÁT", 91);
		}
		if (iToaDo == 16) {
			ToMau(34, 14, "[50000] ", 91);
			ToMau(34, 16, "[100000]", 91);
			ToMau(34, 18, "[200000]", 32);
			ToMau(65, 14, "[400000]", 91);
			ToMau(65, 16, "[500000]", 91);
			ToMau(64, 18, " SỐ KHÁC ", 91);
			ToMau(50, 16, "THOÁT", 91);
		}
		if (iToaDo == 17) {
			ToMau(34, 14, "[50000] ", 91);
			ToMau(34, 16, "[100000]", 91);
			ToMau(34, 18, "[200000]", 91);
			ToMau(65, 14, "[400000]", 32);
			ToMau(65, 16, "[500000]", 91);
			ToMau(64, 18, " SỐ KHÁC ", 91);
			ToMau(50, 16, "THOÁT", 91);
		}
		if (iToaDo == 18) {
			ToMau(34, 14, "[50000] ", 91);
			ToMau(34, 16, "[100000]", 91);
			ToMau(34, 18, "[200000]", 91);
			ToMau(65, 14, "[400000]", 91);
			ToMau(65, 16, "[500000]", 32);
			ToMau(64, 18, " SỐ KHÁC ", 91);
			ToMau(50, 16, "THOÁT", 91);
		}
		if (iToaDo == 19) {
			ToMau(34, 14, "[50000] ", 91);
			ToMau(34, 16, "[100000]", 91);
			ToMau(34, 18, "[200000]", 91);
			ToMau(65, 14, "[400000]", 91);
			ToMau(65, 16, "[500000]", 91);
			ToMau(64, 18, " SỐ KHÁC ", 32);
			ToMau(50, 16, "THOÁT", 91);
		}
		if (iToaDo == 20) {
			ToMau(34, 14, "[50000] ", 91);
			ToMau(34, 16, "[100000]", 91);
			ToMau(34, 18, "[200000]", 91);
			ToMau(65, 14, "[400000]", 91);
			ToMau(65, 16, "[500000]", 91);
			ToMau(64, 18, " SỐ KHÁC ", 91);
			ToMau(50, 16, "THOÁT", 32);
		}
	} while (iChoose != 3);
	//XOAMANHINH setKhung(CALLLIST);
	if (iToaDo == 14)checkRutTien(CALLLIST, 50000, tmp);
	else if (iToaDo == 15)  checkRutTien(CALLLIST, 100000, tmp);
	else if (iToaDo == 16) checkRutTien(CALLLIST, 200000, tmp);
	else if (iToaDo == 17) checkRutTien(CALLLIST, 400000, tmp);
	else if (iToaDo == 18) checkRutTien(CALLLIST, 500000, tmp);
	else if (iToaDo == 20) { ClearSceen showAccessUser(CALLLIST, sUserNow); }
	else if (iToaDo == 19) {
		gotoxy(73, 18); int iwall=0; cin >> iwall;
		checkRutTien(CALLLIST, iwall, tmp);
	}
}
void userChuyenTien(LISTADMIN, string sUserNow) {
	User tmp1(sUserNow, "", 0, "");
	User tmp11 = listUser.search2(tmp1);
	string sUserReceive = "";
	long long llNumberMoneyTranferred;
	setKhung(CALLLIST);
	ToMau(32, 13, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	ToMau(34, 14, "STK người nhận:", 3);
	ToMau(34, 15, "Số dư hiện tại:", 5);
	gotoxy(50, 15);  cout << tmp11.getWallet() <<" "<< tmp11.getType();
	ToMau(34, 16, "Người nhận:", 6);
	ToMau(34, 17, "Số tiền:", 2);
	ToMau(30, 19, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	gotoxy(50, 14); cin >> sUserReceive;
	User tmp2(sUserReceive, "", 0, "");
	if (listUser.search1(tmp2) && sUserNow!=sUserReceive) {
		User tmp22 = listUser.search2(tmp2);
		gotoxy(50, 16); cout << tmp22.getName();
		gotoxy(50, 17); cin >> llNumberMoneyTranferred;
		if (llNumberMoneyTranferred >= 50000 && llNumberMoneyTranferred <= tmp11.getWallet() - 50000 && llNumberMoneyTranferred % 50000 == 0) {
			string sNoti = tmp11.getName() + " vừa chuyển " + to_string(llNumberMoneyTranferred) + " đến "+ tmp22.getName() + " vào lúc" + currentDateTime();
			History noti1(sNoti, tmp11.getID(), tmp22.getID());
			listLog.addTail(noti1);
			tmp11.Except_Money(llNumberMoneyTranferred);
			tmp22.Plus_Money(llNumberMoneyTranferred);
			updateHistory(CALLLIST);
			listUser.changeValue(tmp11);
			listUser.changeValue(tmp22);
			updateID(CALLLIST);
			Sleep(1000);
			ToMau(34, 18, "Bạn đã chuyển thành công!!", 4);
			Sleep(2000);
			ClearSceen
				setKhung(CALLLIST);
			showAccessUser(CALLLIST, tmp11.getID());
		}
		else {
			ToMau(34, 18, "Vui lòng nhập lại! Tiền bạn chưa đủ hoặc không phải bội 50000", 4);
			Sleep(2000);
			ClearSceen
				showAccessUser(CALLLIST, sUserNow);
		}
	}
	else {
		ToMau(34, 18, "Sai định dạng hoặc sai số tài khoản!!!!", 4);
		Sleep(2000);
		ClearSceen
			showAccessUser(CALLLIST, sUserNow);

	}
}
void userNoiDungGD(LISTADMIN, string sUserNow) {
	resizeConsole(1027, 600);
	History noti1("", sUserNow, sUserNow);
	LinkedList<History> tmp;
	listLog.search3(noti1, tmp);
	int iNumberLines = 4;
	int iColorTitle = 11;
	int iQuantity = tmp.getSize();
	int iColorInformations = 15;
	ToMau(1, 1, "╔════════════════╦════════════════╦══════════════════════════════════════════════════════════════════════════════════════════════════════╗", 9);
	ToMau(1, 2, "║                ║                ║                                                                                                      ║", 9);
	ToMau(8, 2, "FROM", iColorTitle);
	ToMau(26, 2, "TO", iColorTitle);
	ToMau(85, 2, "NỘI DUNG", iColorTitle);
	ToMau(1, 3, "╠════════════════╬════════════════╬══════════════════════════════════════════════════════════════════════════════════════════════════════╣", 9);
	for (int i = 0; i < iQuantity; i++) {
		
		ToMau(3, iNumberLines, tmp[i].getSend(), iColorInformations);
		if (tmp[i].getReceive() == "0") {
			ToMau(20, iNumberLines, tmp[i].getSend(), iColorInformations);
		}
		else ToMau(20, iNumberLines, tmp[i].getReceive(), iColorInformations);
		ToMau(37, iNumberLines, tmp[i].getNoti(), iColorInformations);
		ToMau(1, iNumberLines, "║", 9);
		ToMau(18, iNumberLines, "║", 9);
		ToMau(35, iNumberLines, "║", 9);
		ToMau(138, iNumberLines, "║", 9);
		if (i < iQuantity - 1) ToMau(1, iNumberLines += 1, "╠════════════════╬════════════════╬══════════════════════════════════════════════════════════════════════════════════════════════════════╣", 9);
		iNumberLines++;
	}
	ToMau(1, iNumberLines, "╚════════════════╩════════════════╩══════════════════════════════════════════════════════════════════════════════════════════════════════╝", 9);
	char _cA = _getch();
	if (_cA != '+') {
		resizeConsole(800, 600);
		ClearSceen
			setKhung(CALLLIST);
		showAccessUser(CALLLIST, sUserNow);
	}
}
void userDoiMaPin(LISTADMIN, string sUserNow) {
	TheTu a(sUserNow, "");
	a=listTheTu.search4(a);
	setKhung(CALLLIST);
	string sPinNow = a.getPIN();
	TheTu ttmp(sUserNow, a.getPIN());
	TheTu tmp = listTheTu.search2(ttmp);
	string sPinInput;
	string sNewPin, sNewPin1;
	ToMau(32, 13, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	ToMau(34, 14, "Mã pin hiên tại    :", 3);
	ToMau(30, 19, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	gotoxy(55, 14);  cin >> sPinInput;
	if (sPinInput == sPinNow) {
		ToMau(34, 15, "Mã pin mới:", 5);
		gotoxy(55, 15); cin >> sNewPin;
		if (sNewPin.size() != 6) {
			ToMau(40, 20, "Mã pin mới có 6 ký tự!!", 4);
			Sleep(1000);
			ClearSceen
				showAccessUser(CALLLIST, sUserNow);
		}
		ToMau(34, 16, "Nhập lại mã pin mới:", 6);
		gotoxy(55, 16); cin >> sNewPin1;
		if (sNewPin != sNewPin1) {
			ToMau(40, 20, "2 mã pin bạn nhập vào khác nhau!!", 4);
			Sleep(1000);
			ClearSceen
			showAccessUser(CALLLIST, sUserNow);
		}
		else {
			ToMau(40, 20, "Bạn đã đổi mã pin thành công!!", 4);
			tmp.Change_PIN(sNewPin);
			listTheTu.changeValue1(tmp);
			updateTheTu(CALLLIST);
			Sleep(2000);
			ClearSceen
			showAccessUser(CALLLIST, sUserNow);
		}
	}
	else {
		ToMau(40, 20, "Mã pin hiện tại bạn nhập sai!!!", 4);
		Sleep(1000);
		ClearSceen
		showAccessUser(CALLLIST, sUserNow);
	}
}

// 1 số hàm check và tạo khung 
void setKhung(LISTADMIN) {
	//35 dòng và 106 cột
	int iSampleFrame = 14;
	ToMau(1, 1, "╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗", iSampleFrame);
	int _iX = 2;
	for (int i = 0; i < 34; i++) {
		ToMau(1, _iX, "║", iSampleFrame);
		ToMau(106, _iX, "║", iSampleFrame);
		_iX++;
	}
	ToMau(1, 35, "╚════════════════════════════════════════════════════════════════════════════════════════════════════════╝", iSampleFrame);
	gotoxy(1, 1);
}
bool checkLoginAdmin(string user, string password, LinkedList<Admin> listAdmin) {
	Admin z(user, password);
	return (listAdmin.checkAdmin(z));
}
bool checkLoginUser(string user, string password, LISTADMIN) {
	TheTu z(user, password);
	return (listTheTu.checkUser(z));
}
void checkRutTien(LISTADMIN,long long wallet, User tmp) {
	long long soDu = tmp.getWallet();
	if (wallet >= 50 && wallet <= soDu - 50000 && wallet % 50000 == 0) {
		gotoxy(40, 20); cout << "Vui lòng đợi một tí...";
		tmp.Except_Money(wallet);
		string sNoti = tmp.getName() + " vừa rút "+ to_string(wallet)+" vào lúc" + currentDateTime();
		History noti1(sNoti,tmp.getID(), "0");
		listLog.addTail(noti1);
		updateHistory(CALLLIST);
		listUser.changeValue(tmp);
		updateID(CALLLIST);
		Sleep(1000);
		ToMau(38, 21, "BẠN ĐÃ RÚT THÀNH CÔNG " + to_string(wallet), 4);
		Sleep(2000);
		ClearSceen
			setKhung(CALLLIST);
		showAccessUser(CALLLIST, tmp.getID());
	}
	else {
		gotoxy(20, 20); cout << "Vui lòng nhập lại! Tiền bạn chưa đủ hoặc không phải bội 50000";
		Sleep(3000);
		ClearSceen
			setKhung(CALLLIST);
		showAccessUser(CALLLIST, tmp.getID());
	}
}
void inputPassword(string& pw) {
	char cPass[32];
	int i = 0;
	char _cA;
	for (i = 0;;) {
		_cA = _getch();
		if ((_cA >= 'a' && _cA <= 'z') || (_cA >= 'A' && _cA <= 'Z') || (_cA >= '0' && _cA <= '9')) {
			cPass[i] = _cA;
			++i;
			cout << "*";
		}
		if (_cA == '\b' && i >= 1) {
			cout << "\b \b";
			--i;
		}
		if (_cA == '\r') {
			cPass[i] = '\0';
			break;
		}
	}
	for (int z = 0; z < i; z++) {
		pw.push_back(cPass[z]);
	}
}

void showMain(LISTADMIN) {
	setKhung(CALLLIST);
	int iLeft = 38;
	ToMau(iLeft - 17, 15, " ██╗       ██╗███████╗██╗      █████╗  █████╗ ███╗   ███╗███████╗", 15);
	ToMau(iLeft - 17, 16, " ██║  ██╗  ██║██╔════╝██║     ██╔══██╗██╔══██╗████╗ ████║██╔════╝", 15);
	ToMau(iLeft - 17, 17, " ╚██╗████╗██╔╝█████╗  ██║     ██║  ╚═╝██║  ██║██╔████╔██║█████╗  ", 15);
	ToMau(iLeft - 17, 18, "  ████╔═████║ ██╔══╝  ██║     ██║  ██╗██║  ██║██║╚██╔╝██║██╔══╝  ", 15);
	ToMau(iLeft - 17, 19, "  ╚██╔╝ ╚██╔╝ ███████╗███████╗╚█████╔╝╚█████╔╝██║ ╚═╝ ██║███████╗", 15);
	ToMau(iLeft - 17, 20, "   ╚═╝   ╚═╝  ╚══════╝╚══════╝ ╚════╝  ╚════╝ ╚═╝     ╚═╝╚══════╝", 15);
	Sleep(600);
	ToMau(iLeft - 17, 15, "                                                                 ", 0);
	ToMau(iLeft - 17, 16, "                                                                 ", 0);
	ToMau(iLeft - 17, 17, "                                                                 ", 0);
	ToMau(iLeft - 17, 18, "                                                                 ", 0);
	ToMau(iLeft - 17, 19, "                                                                 ", 0);
	ToMau(iLeft - 17, 20, "                                                                 ", 0);
	ToMau(iLeft + 8, 15, "████████╗ █████╗ ", 12);
	ToMau(iLeft + 8, 16, "╚══██╔══╝██╔══██╗", 12);
	ToMau(iLeft + 8, 17, "   ██║   ██║  ██║", 12);
	ToMau(iLeft + 8, 18, "   ██║   ██║  ██║", 12);
	ToMau(iLeft + 8, 19, "   ██║   ╚█████╔╝", 12);
	ToMau(iLeft + 8, 20, "   ╚═╝    ╚════╝ ", 12);
	Sleep(600);
	ToMau(iLeft - 17, 15, "                                                                 ", 0);
	ToMau(iLeft - 17, 16, "                                                                 ", 0);
	ToMau(iLeft - 17, 17, "                                                                 ", 0);
	ToMau(iLeft - 17, 18, "                                                                 ", 0);
	ToMau(iLeft - 17, 19, "                                                                 ", 0);
	ToMau(iLeft - 17, 20, "                                                                 ", 0);
	ToMau(iLeft, 13, "█░█ █▄░█", 15);
	ToMau(iLeft, 14, "▀▄▀ █░▀█", 15);
	ToMau(iLeft, 15, "██████╗  █████╗ ███╗  ██╗██╗  ██╗", 11);
	ToMau(iLeft, 16, "██╔══██╗██╔══██╗████╗ ██║██║ ██╔╝", 11);
	ToMau(iLeft, 17, "██████╦╝███████║██╔██╗██║█████═╝ ", 11);
	ToMau(iLeft, 18, "██╔══██╗██╔══██║██║╚████║██╔═██╗ ", 11);
	ToMau(iLeft, 19, "██████╦╝██║  ██║██║ ╚███║██║ ╚██╗", 11);
	ToMau(iLeft, 20, "╚═════╝ ╚═╝  ╚═╝╚═╝  ╚══╝╚═╝  ╚═╝", 9);
	Sleep(200);
	ToMau(65, 33, "Press z to open the Administrator login", 15);
	ToMau(65, 34, "      x to open the User login", 15);
	char _cA = _getch();
	if (_cA == 'z') { ClearSceen showLoginAdmin(CALLLIST);}
	if (_cA == 'x') { ClearSceen showLoginUser(CALLLIST);}
}