//Personal.h

#ifndef _PERSONAL_H
#define _PERSONAL_H
#include <string>

using namespace std;

class Personal {
public :
	Personal();
	Personal(string name, string address, string telephoneNumber, string emailAddress);
	Personal(const Personal& source);

	~Personal();

	bool IsEqual(const Personal& other);
	bool IsNotEqual(const Personal& other);

	Personal& operator =(const Personal& source);
	bool operator ==(const Personal& source);
	bool operator !=(const Personal& source);

	string GetName() const;
	string GetAddress() const;
	string GetTelephoneNumber() const;
	string GetEmailAddress() const;

private :
	string _name;
	string _address;
	string _telephoneNumber;
	string _emailAddress;
};

inline string Personal::GetName() const{
	return _name;
}

inline string Personal::GetAddress() const {
	return _address;
}

inline string Personal::GetTelephoneNumber() const {
	return _telephoneNumber;
}

inline string Personal::GetEmailAddress() const {
	return _emailAddress;
}
#endif //_PERSONAL_H