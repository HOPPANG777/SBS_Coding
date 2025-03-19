#include<iostream>
#include"CAnimal.h"

int main()
{
	CCat cat("Nero");
	CDog dog("Baduk");
	CRooster rooster("Kokodak");

	CAnimal* pAnimal[3] = { &cat, &dog, &rooster };

	for (int i = 0; i < 3; i++)
	{
		cout << "이름 : " << pAnimal[i]->GetName() << endl;
		cout << "소리 : ";
		pAnimal[i]->MakeVoice();
		cout << endl;
	}

	return 0;
}