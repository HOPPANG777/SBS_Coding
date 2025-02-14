#include <stdio.h>

struct Parent
{
    virtual void Test(void)
    {
        printf( "부모 클래스 호출\n" );
    }
};

struct Child : public Parent
{
    void Test(void)
    {
        printf( "자식 클래스 호출\n" );
    }
};

void main(void)
{
    Parent parent;
    Child child;

    void (Parent::*ParentFunc)(void);
    void (Child::*ChildFunc)(void);

    printf( "[부모 클래스 함수 포인터 사용]\n" );
    ParentFunc = &Parent::Test;

    (parent.*ParentFunc)();
    (child.*ParentFunc)();

    printf( "\n[자식 클래스 함수 포인터 사용]\n" );
    ChildFunc = &Child::Test;

//  (parent.*ChildFunc)();
    (child.*ChildFunc)();

    printf( "\n[자식을 부모 클래스 포인터에 치환]\n" );
    ParentFunc = (void (Parent::*)(void)) ChildFunc;

    (parent.*ParentFunc)();
    (child.*ParentFunc)();
}

/*
[출력결과]
[부모 클래스 함수 포인터 사용]
부모 클래스 호출
자식 클래스 호출

[자식 클래스 함수 포인터 사용]
자식 클래스 호출

[자식을 부모 클래스 포인터에 치환]
부모 클래스 호출
자식 클래스 호출
*/
