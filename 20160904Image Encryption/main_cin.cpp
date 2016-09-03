#include "newHead.h"

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

		mat imgA(size);
		mat imgB(size);

		for (int m = 0; m < size; m++)
		{
			for (int n = 0; n < size; n++)
			{
				int p;
				cin >> p;
				imgA.Set(m, n, p);
			}
		}
		for (int m = 0; m < size; m++)
		{
			for (int n = 0; n < size; n++)
			{
				int p;
				cin >> p;
				imgB.Set(m, n, p);
			}
		}
		if (checkMat(&imgA, &imgB, udlr(0, size, 0, size), udlr(0, size, 0, size)))
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No" << endl;
		}

	}

	return 0;
}