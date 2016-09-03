#include "head.h"

int main()
{
	//input testcase num.
	int imgCount = 0, size = 0;
	cin >> imgCount;
	//Get the number of testcase
	for (int i = 0; i < imgCount; i++)
	{
		//Get img size:
		cin >> size;
		//cout << size << endl;
		cin.sync();
		int* imgA = new int[size * size];
		int* imgB = new int[size * size];

		for (int m = 0; m < size ; m++)
		{ 
			for (int n = 0; n < size; n++)
			{
				cin>>*(imgA + rc2index(m, n, size));
			}
		}
		for (int m = 0; m < size; m++)
		{
			for (int n = 0; n < size; n++)
			{
				cin >> *(imgB + rc2index(m, n, size));
			}
		}
		if (checkMat(imgA, imgB, size, 0, size, 0, size))
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No" << endl;
		}

		delete[] imgA;
		delete[] imgB;
	}


	return 0;
}