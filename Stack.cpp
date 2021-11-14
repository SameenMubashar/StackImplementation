#include<iostream>
#include<cmath>
#include<string>
#define SIZE 100
using namespace std;
string infixtopostfix(string exp);
int prec(char op);
bool parenthesesCheck(string exp);
int postfixEvaluation(string exp);
template<class X>
class Stack
{
public:
	X arr[SIZE];
	int top = -1;
	int length = 0;
	bool isEmpty()
	{
		if (top < 0)
		{
			return true;
		}
		else
			return false;
	}
	bool isFull()
	{
		if (top == SIZE - 1)
		{
			return true;
		}
		else
			return false;
	}
	void Push(X element)
	{
		if (!isFull())
		{
			arr[++top] = element;
			length++;
		}
		else
			cout << "Array is Full" << endl;
	}
	X Pop()
	{
		X data;
		if (!isEmpty())
		{
			data = arr[top--];
			length--;
			return data;
		}
		else
		{
			cout << "Array is Empty " << endl;
		}
	}
	X peek()
	{
		if (!isEmpty())
		{
			return arr[top];
		}
		else
		{
			cout << "Array is Empty " << endl;
		}
	}
	void clear()
	{
		while (!isEmpty())
		{
			Pop();
		}
	}
};


int main()
{
	string exp,answer;
	cout << "\t***Infix to Postfix expression convertor and evaluator***" << endl;
	cout << "Enter the expression " << endl;
	getline(cin, exp);
	answer = infixtopostfix(exp);
	cout << "The expression in postfix is:" << answer << endl;
	cout << endl << "The answer of expression is:\t" << postfixEvaluation(answer);
	cin.ignore();
	cin.ignore();
	return 0;
}

Stack<char> st;
string infixtopostfix(string exp)
{
	string postfixExp = "";
	if (parenthesesCheck(exp))
	{
		for (int i = 0; i < exp.length(); i++)
		{
			// checking if the character is a number
			if (isdigit(exp[i]))
			{
				postfixExp += exp[i];
			}
			else
			{
				postfixExp += ' ';  // to add a space after every number

				if (exp[i] == ' ')
				{
					continue;
				}
				// if an opening bracket is encountered 
				else if (exp[i] == '('|| exp[i] == '['|| exp[i] == '{')
				{
					st.Push(exp[i]);
				}
				// if a closing bracket is encountered
				else if (exp[i] == ')')
				{
					// poping the operators
					while (!st.isEmpty() && st.peek() != '(')
					{
						postfixExp += st.Pop();
					}
					if (!st.isEmpty())
						st.Pop();
				}
				else if (exp[i] == ']')
				{
					// poping the operators
					while (!st.isEmpty() && st.peek() != '[')
					{
						postfixExp += st.Pop();
					}
					if (!st.isEmpty())
						st.Pop();
				}
				else if (exp[i] == '}')
				{
					// poping the operators
					while (!st.isEmpty() && st.peek() != '{')
					{
						postfixExp += st.Pop();
					}
					if (!st.isEmpty())
						st.Pop();
				}
				else
				{
					// Poping the operators with respect to their precedence
					while (!st.isEmpty() && prec(st.peek()) >= prec(exp[i]))
					{
						postfixExp += st.peek();
						st.Pop();
					}

					st.Push(exp[i]);
				}
			}
		}
		while (!st.isEmpty())
		{
			postfixExp += st.peek();
			st.Pop();
		}

	}
	else
	{
		postfixExp = "not valid";
	}
	return postfixExp;

}

// Function to check precedence check
// higher the return value, higher the precedence
int prec(char op)
{
	if (op == '^')
		return 3;
	else if (op == '*' || op == '/')
		return 2;
	else if (op == '+' || op == '-')
		return 1;
	else
		return 0;
}
bool parenthesesCheck(string exp)
{
	Stack<char> penC;
	Stack<int> pos;

	int i;
	for (i = 0; i < exp.length(); i++)
	{
		// checking for opening brackets in the current place 
		if (exp[i] == '[' || exp[i] == '{' || exp[i] == '(')
		{
			penC.Push(exp[i]);
			pos.Push(i + 1);
		}

		/* checking for closing brackets and confirming
		*  if its corresponding opening bracket exist  */
		else if (exp[i] == ')')
		{
			if (penC.peek() == '(')
			{
				penC.Pop();
				pos.Pop();
			}
			else
				break;
		}
		else if (exp[i] == '}')
		{
			if (penC.peek() == '{')
			{
				penC.Pop();
				pos.Pop();
			}
			else
				break;
		}
		else if (exp[i] == ']')
		{
			if (penC.peek() == '[')
			{
				penC.Pop();
				pos.Pop();
			}
			else
				break;
		}
	}

	if (penC.isEmpty())
	{
		return true;
	}
	else
		return false;
}
int postfixEvaluation(string exp)
{
	Stack<string> EV;
	string num;
	for (int i = 0; i < exp.length(); i++)
	{
		// checking if the character is a number
		while (isdigit(exp[i]))
		{
			num.append(to_string(exp[i] - 48));
			i++;
		}

		if (num != "")
		{
			EV.Push(num);
			num = "";
		}

		// equation solving process starts here
		if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '^')
		{
			int op1 = stoi(EV.Pop());
			int op2 = stoi(EV.Pop());
			int res = 0;
			switch (exp[i])
			{
			case '+':
				res = op2 + op1;
				break;
			case '-':
				res = op2 - op1;
				break;
			case '*':
				res = op2 * op1;
				break;
			case '/':
				res = op2 / op1;
				break;
			case '^':
				res = pow(op2, op1);
				break;
			default:
				break;
			}

			EV.Push(to_string(res));
		}
	}
	return stoi(EV.Pop());
}
