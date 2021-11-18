#include <iostream>
#include <fstream>
#include <Windows.h>
//#include <string>
//#include <algorithm>
#include "Stack.h"
//#include "Queue.h"
#include "Tree.h"
using namespace std;
int prec(char c);
bool isOperator(char c);
string infixToPostfix(string s);
//string openBrackets(string infix);

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
/*string openBrackets(string infix) {
	bool brackets = true;
	while (brackets) {
		brackets = false;
		int leftBracketCount = -1;
		int rightBracketCount = -1;
		int startIndex = 0;
		int endIndex = 0;
		int bracketStart = 0;
		bool swapSign = false;
		for (unsigned int i = 0; i < infix.length(); i++) {
			if (infix[i] == '(')
				leftBracketCount++;
			else if (infix[i] == ')')
				rightBracketCount++;
		}
		for (unsigned int i = 0; i < infix.length(); i++) {
			if (infix[i] == '(') {
				leftBracketCount--;
				startIndex = i + 1;
				bracketStart = i + 1;
			}
			else if (infix[i] == ')')
				rightBracketCount--;
			if (infix[i] == '*' && infix[i + 1] == '(') {
				brackets = true;
				string copyString = "";
				string stringToQueue = "";
				StringQueue strQueue;
				if (startIndex && infix[startIndex - 1] == '-')
					swapSign = true;
				copyString = infix.substr(startIndex, i - startIndex);
				endIndex = i + 3;
				for (int j = i + 2; infix[j] != ')' && j<infix.length(); j++) {

					if (infix[j] == '+' || infix[j] == '-') {
						strQueue.enqueue(stringToQueue + infix[j]);
						stringToQueue = "";
					}
					else {
						stringToQueue += infix[j];
					}
					++endIndex;
				}
				strQueue.enqueue(stringToQueue);
				string tmpString = "";
				while (!strQueue.isEmpty()) {
					tmpString += copyString + '*' + strQueue.dequeue();
				}
				if (swapSign) {
					replace(tmpString.begin(), tmpString.end(), '+', '$');
					replace(tmpString.begin(), tmpString.end(), '-', '+');
					replace(tmpString.begin(), tmpString.end(), '$', '-');
					swapSign = false;
				}
				infix = infix.substr(0, startIndex) +  tmpString + infix.substr(endIndex, infix.length() - endIndex + 1);
				break;
			}
			else if (infix[i] == '(') {
				bracketStart = i + 1;
			}
			else if (infix[i] == ')' && infix[i + 1] == '*') {
				string stringToQueue = "";
				StringQueue strQueue;
				brackets = true;
				if (bracketStart>=2 && infix[bracketStart - 2] == '-')
					swapSign = true;
				int bracketEnd = bracketStart + 1;
				for (int j = bracketStart; infix[j] != ')' ; j++) {
					if (infix[j] == '+' || infix[j] == '-') {
						strQueue.enqueue(stringToQueue + infix[j]);
						stringToQueue = "";
					}
					else {
						stringToQueue += infix[j];
					}
					++bracketEnd;
				}
				strQueue.enqueue(stringToQueue);
				string copyString="";
				endIndex = bracketEnd + 1;
				while (infix[endIndex] == ')' || infix[endIndex] == '*')
					++endIndex;
				if (infix[endIndex]=='(') {
					for (unsigned int j = endIndex; infix[j] != ')' && j < infix.length(); j++) {
						copyString += infix[j];
							++endIndex;
					}
					if (i<infix.length()-2 && infix[i + 2] == '(')
						copyString += ')';
				}
				else {
					for (unsigned int j = endIndex; infix[j] != '+' && infix[j] != '-' && infix[j] != ')' && j < infix.length(); j++) {
						copyString += infix[j];
							++endIndex;
					}
				}
				string tmpString;
				if(infix[i+2]=='(')
					tmpString = "(";
				while (!strQueue.isEmpty()) {
					tmpString += copyString + '*' + strQueue.dequeue();
				}
				if (infix[i + 2] == '(')
					tmpString += ')';
				if (swapSign) {
					replace(tmpString.begin(), tmpString.end(), '+', '$');
					replace(tmpString.begin(), tmpString.end(), '-', '+');
					replace(tmpString.begin(), tmpString.end(), '$', '-');
					swapSign = false;
				}
				infix = infix.substr(0, bracketStart-1) + tmpString + infix.substr(endIndex, infix.length() - endIndex);
				break;
			}
			else if (infix[i] == '+' || infix[i] == '-') {
				startIndex = i + 1;
			}
		}
	}
	infix.erase(remove(infix.begin(), infix.end(), '('), infix.end());
	infix.erase(remove(infix.begin(), infix.end(), ')'), infix.end());
	return infix;
}*/