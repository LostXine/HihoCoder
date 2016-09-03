#include "head.h"
#include <fstream>

int main()
{
	//open testcase file.
	fstream fs;
	fs.open("testcase.txt", ios::in);
	if (!fs.is_open())
	{
		return 1;
	}
	//input testcase num.
	int imgCount = 0, size = 0;
	char cache[CACHE_SIZE];
	fs.getline(cache, CACHE_SIZE);
	imgCount = atoi(cache);
	//Get the number of testcase
	for (int i = 0; i < imgCount; i++)
	{
		for (auto &p : cache)
		{
			p = 0;
		}
		//Get img size.
		fs.getline(cache, CACHE_SIZE);
		size = atoi(cache);
		//cout << size << endl;

		int* imgA = new int[size * size];
		int* imgB = new int[size * size];

		//Get img input
		for (int m = 0; m < size << 1; m++)
		{
			fs.getline(cache, CACHE_SIZE);
			if (m < size)
			{
				writeMat(size, imgA, m, cache);
			}
			else
			{
				writeMat(size, imgB, m - size, cache);
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