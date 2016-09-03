#include <iostream>
#include <cstring>

#define CACHE_SIZE 1024

using namespace std;

void index2rc(int index, int size, int &row, int& col)
{
	row = index / size;
	col = index % size;
}

int rc2index(int row, int col, int size)
{
	return row*size + col;
}

void writeMat(int size, int * mat, int row, char* p)
{
	int index = -1, last = 0;
	for (int t = 0; t < size; t++)
	{
		last = index + 1;
		index = last;
		while (index < CACHE_SIZE)
		{
			if (*(p + index) == ' ' || *(p + index) == 0)
			{
				break;
			}
			index++;
		}
		char* tmp = new char[index - last];
		memcpy(tmp, p + last, index - last);
		int data = atoi(tmp);
		*(mat + rc2index(row, t, size)) = data;
		delete[]tmp;
	}
}

void printMat(int* mat, int size)
{
	for (int m = 0; m < size; m++)
	{
		for (int n = 0; n < size; n++)
		{
			cout << *(mat + rc2index(m, n, size));
		}
		cout << endl;
	}
}

//Rotate the selected matrix
void rotMat(int *src, int size, int left, int right, int up, int down)
{
	int lrm = (right + left) / 2;
	int udm = (up + down) / 2;
	int half = (right - left) / 2;
	for (int m = up; m < udm; m++)
	{
		for (int n = left; n < lrm; n++)
		{
			int tmp = *(src + rc2index(m, n,size));
			*(src + rc2index(m, n, size)) = *(src + rc2index(m + half, n, size));
			*(src + rc2index(m + half, n, size)) = *(src + rc2index(m + half, n + half, size));
			*(src + rc2index(m + half, n + half, size)) = *(src + rc2index(m, n+half, size));
			*(src + rc2index(m, n + half, size)) = tmp;
		}
	}
}

int checkMat(int* matA, int *matB, int size, int left, int right, int up, int down)
{
	unsigned int p = 0x0F;

	if ((right - left) % 2 || (right - left) < 4)
	{

		//check every value
		for (int m = up; m < down; m++)
		{
			for (int n = left; n < right; n++)
			{

				if (p == 0)
				{
					return 0;
				}
				int data = *(matA + rc2index(m, n, size));
				cout << "row:" << m << " col:" << n << " data:" << data << ":";
				if (p % 2)
				{
					if (data != *(matB + rc2index(m, n, size)))
					{
						p = p & 0x0E;
					}
				}
				cout << p << "-";
				if ((p >> 1) % 2)
				{
					if (data != *(matB + rc2index(n - left + up, down - m - 1 + left, size)))
					{
						p = p & 0x0D;
					}
				}
				cout << p << "-";
				if ((p >> 2) % 2)
				{
					if (data != *(matB + rc2index(down - m - 1 + up, right - n - 1 + left, size)))
					{
						p = p & 0x0B;
					}
				}
				cout << p << "-";
				if ((p >> 3) % 2)
				{
					if (data != *(matB + rc2index(right - n - 1 + up, m - up + left, size)))
					{
						p = p & 0x07;
					}
				}
				cout<< p << endl;
			}
		}
	}
	else
	{
		int lrm = (left + right) / 2;
		int udm = (up + down) / 2;
		int cc = 0;
		for (int r = 0; r < 4; r++)
		{
			cc = 0;
			cout << "Rot:"<<r << endl;
			cout << "PrintA:" << endl;
			printMat(matA, size);
			if (r != 0){ rotMat(matA, size, left, right, up, down); }

			cout << "PrintARot:" << endl;
			printMat(matA, size);
			if (checkMat(matA, matB, size, left, lrm, up, udm) > 0)
			{
				cc++;
			}
			//cout << endl;
			if (checkMat(matA, matB, size, lrm, right, up, udm) > 0)
			{
				cc++;
			}
			//cout << endl;
			if (checkMat(matA, matB, size, lrm, right, udm, down) > 0)
			{
				cc++;
			}
			//cout << endl;
			if (checkMat(matA, matB, size, left, lrm, udm, down) > 0)
			{
				cc++;
			}
			//cout << endl;
			if (cc == 4)
			{
				p = 0x01 << r;
				break;
			}
			else
			{
				p = 0;
			}
		}

	}

	return p;
}