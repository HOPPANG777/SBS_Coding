//===========================================================
#pragma once
//-------------------------------
const int NAMELEN = 20;	//	이름 길이..
typedef struct SAccount
{
	int _id;				//	계좌번호..
	int _balance;			//	잔액..
	char _szName[NAMELEN];	//	이름..

}SAccount;
//-------------------------------
//	extern 
//	-	이미 선언 또는 초기화 되어 있는
//		전역변수를 사용할때 선언..
extern SAccount g_AccountArray[100];	//	계좌정보 배열...
extern int g_index;						//	계설된 계좌수...
//-------------------------------
void ShowMenu();
void MakeAccount();
void Deposit();
void Withdraw();
void Inquire();
void InquireAll();
//-------------------------------
enum
{
	MAKEACCOUNT = 1,
	DEPOSIT,
	WITHDRAW,
	INQUIRE,
	INQUIREALL,
	EXIT,
};
//-------------------------------

//===========================================================//