#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Stack.h"
#include "Tree.h"
using namespace std;
int prec(char c);
bool isOperator(char c);
string infixToPostfix(string s);

int main()
{
	ifstream rff("A.txt");
    SetConsoleOutputCP(CP_UTF8);
    Tree* Tr = new Tree;
    string infix;
    rff >> infix;
	//cin >> infix;
	string postfix = infixToPostfix(infix);
	//cout << postfix << '\n';
    Tr->parseToTree(postfix);
	cout << infix << endl;
	Tr->print();
    Tr->treeTransform();
	Tr->print();
    delete Tr;
}
bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int prec(char c) {
    if (c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else 
        return -1;
}
string infixToPostfix(string infix) {
    Stack *s = new Stack;
    string postfix;
	for (unsigned int i = 0; i < infix.length();i++)
	{
		if ((infix[i] >= 'a' && infix[i] <= 'z')
			|| (infix[i] >= 'A' && infix[i] <= 'Z') || (infix[i]>='0' && infix[i]<='9'))
		{
			postfix += infix[i];
		}
		else if (infix[i] == '(')
		{
			s->push(infix[i]);
		}
		else if (infix[i] == ')')
		{
			while ((s->getTop()->data != '(') && (!s->isEmpty()))
			{
				postfix += s->pop();
			}
			if (s->getTop()->data == '(')
			{
				s->pop();
			}
		}
		else if (isOperator(infix[i]))
		{
			if (s->isEmpty())
			{
				s->push(infix[i]);
			}
			else
			{
				if (prec(infix[i]) > prec(s->getTop()->data))
				{
					s->push(infix[i]);
				}
				else
				{
					while ((!s->isEmpty()) && (prec(infix[i]) <= prec(s->getTop()->data)))
					{
						postfix += s->pop();
					}
					s->push(infix[i]);
				}
			}
		}
	}
	while (!s->isEmpty())
	{
		postfix += s->pop();
	}
	delete s;
    return postfix;
}
