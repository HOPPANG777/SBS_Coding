//====================================================================
#pragma once
//====================================================================
template <typename T>
class CStack
{
	int _topIdx;
	T* _pStack;

public:
	CStack(int size = 10);
	~CStack();
	void Push(const T value);
	T Pop();
	int GetCount() { return _topIdx + 1; }
};
//====================================================================
template <typename T>
CStack<T>::CStack(int size)
{
	_topIdx = -1;
	_pStack = new T[size];
}
//--------------------------------------------------------------------
template <typename T>
CStack<T>::~CStack()
{
	if (_pStack != NULL)
	{
		delete[] _pStack;
		_pStack = NULL;
	}	
}
//--------------------------------------------------------------------
template <typename T>
void CStack<T>::Push(const T value) { _pStack[++_topIdx] = value; }
//--------------------------------------------------------------------
template <typename T>
T CStack<T>::Pop() { return _pStack[_topIdx--]; }
//====================================================================