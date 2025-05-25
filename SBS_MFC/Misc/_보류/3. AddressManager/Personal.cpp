
#include "Personal.h"

Personal::Personal()
:_name(""), _address(""), _telephoneNumber(""), _emailAddress("")
//	초기화 리스트..
//	-	생성자에서 필드를 간단하게 초기화하는 방법
//	-	초기화 리스트를 반드시 사용해야하는 경우..
//		-	필드에 선언과 동시에 초기화가 이루어져야 하는 경우
//			-	필드에 const로 선언된 변수(상수)를 초기화하는 경우..
//			-	필드에 선언된 레퍼런스 변수를 초기화하는 경우..
// 
//	참고 : https://velog.io/@sjongyuuu/C-%EC%83%9D%EC%84%B1%EC%9E%90-%EC%B4%88%EA%B8%B0%ED%99%94%EB%A6%AC%EC%8A%A4%ED%8A%B8
{
}

Personal::Personal(string _name, string address, string _telephoneNumber, string _emailAddress)
:_name(_name), _address(address), _telephoneNumber(_telephoneNumber), _emailAddress(_emailAddress) { //데이터 멤버(매개변수) 순서
}

Personal::Personal(const Personal& source)
:_name(source._name), _address(source._address), _telephoneNumber(source._telephoneNumber), _emailAddress(source._emailAddress) {
}
//	연산자 오버로딩..
Personal& Personal::operator =(const Personal& source) {

	this->_name = source._name;
	this->_address = source._address;
	this->_telephoneNumber = source._telephoneNumber;
	this->_emailAddress = source._emailAddress;

	return *this;
}

Personal::~Personal() {
}

bool Personal::IsEqual(const Personal& other) {

	bool ret = false;
	
	if(	_name.compare(other._name) == 0 &&
		_address.compare(other._address) == 0 &&
		_telephoneNumber.compare(other._address) == 0 &&
		_emailAddress.compare(other._emailAddress) == 0 )
		ret = true;

	return ret;
}

bool Personal::IsNotEqual(const Personal& other) {

	bool ret = false;	
	if(	_name.compare(other._name) != 0 ||
		_address.compare(other._address) != 0 ||
		_telephoneNumber.compare(other._address) != 0 ||
		_emailAddress.compare(other._emailAddress) != 0 )
		ret = true;

	return ret;
}

bool Personal::operator ==(const Personal& source) {

	bool ret = false;
	if( IsEqual( source ) ) ret = true;

	return ret;
}


bool Personal::operator !=(const Personal& source) {

	bool ret = false;
	if (IsEqual(source)) ret = true;

	return ret;
}
//Personal.cpp