#include <iostream>
#include <string>
#include <stack>

using namespace std;

class ZeroDivisionException{};
int operation(int a, int b, char op);
int main()
{
    
    string expression;
    stack<int> operands;
    int number = 0;
    bool flag = true; //флаг для считывания многозначных чисел

    cout << "enter expression: ";
    getline(cin, expression);

    for (char symbol : expression)
    {
        if (isdigit(symbol))
        {
            number *= 10;
            number += (symbol - '0');
            flag = true;
        }
        else
        {
            if (symbol != ' ' && symbol!='~')
            {
                int num2 = operands.top();
                operands.pop();
                int num1 = operands.top();
                operands.pop();
                try 
                {
                    operands.push(operation(num1, num2, symbol));
                }
                catch (ZeroDivisionException)
                {
                    cout << "There is division by zero in your expression!";
                    return 0;
                }
                flag = false; //если пробел идет после оператора, ветвь ниже не выполняется
            }
            else if (symbol == '~')
            {
                int num = operands.top();
                operands.pop();
                operands.push(-num);
                flag = false;
            }
            else if (symbol == ' ' && flag)//если пробел идет после числа, оно заносится в стек
            {
                operands.push(number);
                number = 0;
            }

            
        }
    }

    cout << operands.top();

    return 0;
}

int operation(int a, int b, char op)
{
    switch (op) 
    {
        case '+':return a + b;
        case '-':return a - b;
        case '*':return a * b;
        case '/':
            if (b == 0)throw ZeroDivisionException();
            else return a / b;
    }
}