#include <iostream>
#include <stdio.h>
using namespace std;
struct CNode
{

	int curr;
	char** info;
	CNode* pnext;

};
struct CStack
{
	CNode* phead;
	CStack()
	{
		phead = NULL;
	}
	CNode* Pop()
	{
		if (phead == NULL)
		{
			return NULL;
		}
		CNode* ptrv = phead;
		phead = phead->pnext;
		ptrv->pnext = NULL;
		return ptrv;
	}
	void Push(CNode* pnn)
	{
		pnn->pnext = phead;
		phead = pnn;
	}
	~CStack()
	{
		CNode* Ptemp;
		CNode* Ptrav = phead;
		while (Ptrav != NULL)
		{
			Ptemp = Ptrav->pnext;
			delete Ptrav;
			Ptrav = Ptemp;
		}

	}
};
CNode* Create_In_state(int n)
{
	CNode* pnn;
	pnn = new CNode;
	pnn->pnext = NULL;
	pnn->curr = 0;
	pnn->info = new char* [n];
	for (int i = 0; i < n;i++)
	{
		pnn->info[i] = new char[n];
	}
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			pnn->info[r][c] = ' ';
		}
	}
	return pnn;
}
void expand_one_child( int n, int & Solutions_count, CNode* pcurr, CStack& PS)
{
	int i,j,row, column;
	int clm = 0;
	//number of children
	for (i = 0; i < n; i++)
	{
		//copying from father
		int flag = 0;
		CNode* pnn = new CNode;
		pnn->curr = pcurr->curr;
		pnn->info = new char* [n];
		for (j = 0; j < n;j++)
		{
			pnn->info[j] = new char[n];
		}
		for (row = 0; row < n; row++)
		{

			for (column = 0; column < n; column++)
			{
				pnn->info[row][column] = pcurr->info[row][column];
			}
		}
		//putting Q in child
		pnn->info[pcurr->curr][clm] = 'Q';
		// Diagonal up - left
		for (row= pcurr->curr - 1, column = clm - 1; row >= 0 && column >= 0; row--, column--)
		{
			if (pnn->info[row][column] == 'Q')
			{
				flag = 1;
			}
		}
		// straight up 
		for (int i = pcurr->curr - 1; i >= 0; i--)
		{
			if (pnn->info[i][clm] == 'Q')
			{
				flag = 1;
			}
		}
		// Diag Up - Right 
		for (row = pcurr->curr - 1, column = clm + 1; row >= 0 && column < n;column++, row--)
		{
			if (pnn->info[row][column] == 'Q')
			{
				flag = 1;
			}
		}
		//positive results
		if (flag == 0)
		{
			pnn->curr++;
			if (pnn->curr == n)
			{
				for (row = 0; row < n; row++)
				{
					for (column = 0; column < n; column++)
					{
						cout << "[";
						cout << pnn->info[row][column] << "]";
					}
					cout << endl;
				}
				cout << endl;
				Solutions_count++;
			}
			else
			{
				PS.Push(pnn);
			}
		}
		clm++;
	}
}
void Back_Track(int n)
{
	int Solutions_count = 0;
	CNode* pnn = Create_In_state(n);
	CStack S;
	S.Push(pnn);
	while (S.phead)
	{
		CNode* pfcurr = S.Pop();
		expand_one_child(n, Solutions_count, pfcurr, S);
	}
	cout << "Solution numbers: " << Solutions_count;
}
int main()
{
	int Nsize = 0;
	cout << "Enter Rows and Column Size: ";
	cin >> Nsize;
	cout << endl;
	Back_Track(Nsize);
    return 0;
}