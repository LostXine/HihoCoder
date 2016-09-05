#include <iostream>
#include <vector>

using namespace std;

#define CHAR_SIZE 12

class Node
{
public:
	char val;
	int sum;
	vector<Node*> child;

	Node(char x)
	{
		val = x;
		sum = 0;
	}

	~Node()
	{
		for (int i = 0; i<child.size(); i++)
		{
			delete child[i];
		}
	}

	int findChild(char x)
	{
		int pos = -1;
		for (int i = 0; i<child.size(); i++)
		{
			if (child[i]->val == x)
			{
				pos = i;
				break;
			}
		}
		return pos;
	}

	Node* addChild(char x)
	{
		sum++;
		if (x != 0)
		{
			int loc = findChild(x);
			if (loc<0)
			{
				Node * p = new Node(x);
				child.push_back(p);
				return p;
			}
			else
			{
				return child[loc];
			}
		}

	}

};

int main()
{
	Node head(0);

	int dicNum;
	cin >> dicNum;

	char cache[CHAR_SIZE] = { 0 };
	//establish tree
	for (int i = 0; i<dicNum; i++)
	{
		cin >> cache;
		int p = 0;
		Node * now = &head;

		while (p<CHAR_SIZE)
		{
			now = now->addChild(cache[p]);
			if (cache[p] == 0)
			{
				break;
			}
			p++;
		}

		for (auto &t : cache)
		{
			t = 0;
		}
	}

	int findNum;
	cin >> findNum;
	for (int m = 0; m<findNum; m++)
	{
		cin >> cache;
		int p = 0;
		Node * now = &head;
		int count = 0;
		while (p<CHAR_SIZE)
		{
			if (cache[p] == 0)
			{
				break;
			}
			int pos = now->findChild(cache[p]);
			if (pos < 0)
			{
				count = 0; 
				break;
			}
			now = now->child[pos];
			count = now->sum;
			p++;
		}

		cout << count << endl;
		for (auto &t : cache)
		{
			t = 0;
		}
	}

	return 0;
}