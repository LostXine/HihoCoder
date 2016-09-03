#include <iostream>
#include <cstring>

#define CACHE_SIZE 1024

using namespace std;

//Rect structure.
struct udlr
{
	int up, down, left, right;
	int udm, lrm;
	udlr(int _u, int _d, int  _l, int _r) :up(_u), down(_d), left(_l), right(_r)
	{
		udm = (up + down) / 2;
		lrm = (left + right) / 2;
	};
};

class mat
{
private:
	int *data;
	int **slide;
	int size;
public:
	mat(int _s)
	{
		size = _s;
		data = new int[size*size];
		slide = new int*[size];

		for (int i = 0; i < size; i++)
		{
			slide[i] = data + size*i;
		}
	}

	~mat()
	{
		delete[]slide;
		delete[]data;
	}

	int Get(int row, int col)
	{
		return *(slide[row]  + col);
	}
	void Set(int row, int col, int val)
	{
		*(slide[row] + col) = val;
	}

	void print()
	{
		for (int m = 0; m < size; m++)
		{
			for (int n = 0; n < size; n++)
			{
				cout << this->Get(m, n) << " ";
			}
			cout << endl;
		}
	}
};

void writeMat(int size, mat* mat, int row, char* p)
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
		mat->Set(row, t, data);
		delete[]tmp;
	}
}

int checkMat(mat* matA, mat* matB, udlr bA, udlr bB)
{
	unsigned int p = 0x0F;

	if ((bA.right - bA.left) % 2 || (bA.right - bA.left) < 4)
	{

		//check every value
		for (int m = bA.up; m < bA.down; m++)
		{
			for (int n = bA.left; n < bA.right; n++)
			{

				if (p == 0)
				{
					return 0;
				}
				int data = matA->Get(m, n);
				cout << "row:" << m << " col:" << n << " data:" << data << ":";
				if (p % 2)
				{
					if (data != matB->Get(m - bA.up + bB.up, n - bA.left + bB.left))
					{
						p = p & 0x0E;
					}
				}
				cout << p << "-";
				if ((p >> 1) % 2)
				{
					if (data != matB->Get(n - bA.left + bB.up, bA.down - m - 1 + bB.left))
					{
						p = p & 0x0D;
					}
				}
				cout << p << "-";
				if ((p >> 2) % 2)
				{
					if (data != matB->Get(bA.down - m - 1 + +bB.up, bA.right - n - 1 + bB.left))
					{
						p = p & 0x0B;
					}
				}
				cout << p << "-";
				if ((p >> 3) % 2)
				{
					if (data != matB->Get(bA.right - n - 1 + +bB.up, m - bA.up + bB.left))
					{
						p = p & 0x07;
					}
				}
				cout << p << endl;
			}
		}
	}
	else
	{
		udlr pa[4] =
		{
			udlr(bA.up, bA.udm, bA.left, bA.lrm),
			udlr(bA.up, bA.udm, bA.lrm, bA.right),
			udlr(bA.udm, bA.down, bA.lrm, bA.right),
			udlr(bA.udm, bA.down, bA.left, bA.lrm)
		};
		udlr pb[4] =
		{
			udlr(bB.up, bB.udm, bB.left, bB.lrm),
			udlr(bB.up, bB.udm, bB.lrm, bB.right),
			udlr(bB.udm, bB.down, bB.lrm, bB.right),
			udlr(bB.udm, bB.down, bB.left, bB.lrm)
		};

		int cc = 0;
		for (int r = 0; r < 4; r++)
		{
			cc = 0;

			if (checkMat(matA, matB, pa[0], pb[r % 4]) > 0)
			{
				cc++;
			}
			//cout << endl;
			if (checkMat(matA, matB, pa[1], pb[(r + 1) % 4]) > 0)
			{
				cc++;
			}
			//cout << endl;
			if (checkMat(matA, matB, pa[2], pb[(r + 2) % 4]) > 0)
			{
				cc++;
			}
			//cout << endl;
			if (checkMat(matA, matB, pa[3], pb[(r + 3) % 4]) > 0)
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