#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stack>
#include <queue>
#include <cstring>

using namespace std;
string INFIX_TO_POSTFIX(stack <char> operators, queue <char> numbers, char value, string expression);
int EVALUATE_POSTFIX(string p_express);
bool Is_It_An_Operator(char value);
bool Is_It_An_Operand(char value);
int Operator_Weight(char value);
bool Higher_Precedence(char value, stack <char> &operators);
bool IS_IT_A_PARENTHESIS(char value);

int main()
{
    string p_express ="";
    stack <char> operators;
    queue <char> numbers;
    char value;
    string expression;
    ifstream input;
    input.open("a2.txt");
    while (!input.eof())
    {
       getline(input, expression);
       cout << "Here is the infix expression: " << expression << endl;
       p_express = INFIX_TO_POSTFIX(operators, numbers, value, expression);
       cout << "Here is the postfix expression: " << p_express << endl;
       EVALUATE_POSTFIX(p_express);
    }

    input.close();
    return 0;
}

string INFIX_TO_POSTFIX(stack <char> operators, queue <char> numbers, char value, string expression)
{
    char temp;
    string postfix = "";
    int length = expression.length();
    for (int i=0; i<length; i++)
    {
        if (Is_It_An_Operator(expression[i]))
        {
            while (!operators.empty() && operators.top() != '(' && Higher_Precedence(expression[i], operators))
                {
                        temp = operators.top();
                        operators.pop();
                        numbers.push(temp);
                }
                    operators.push(expression[i]);
        }


        if (Is_It_An_Operand(expression[i]))
        {
            numbers.push(expression[i]);
        }
        if (IS_IT_A_PARENTHESIS(expression[i]))
        {
            if (expression[i] == '(')
            {
                operators.push(expression[i]);
            }
            if (expression[i] == ')')
            {

               do
               {
                   temp = operators.top();
                   operators.pop();
                   numbers.push(temp);
                   if (operators.top() == '(')
                   {
                       operators.pop();
                       break;
                   }
               }
               while (expression[i] != '(' && !operators.empty());
            }
        }

    }

        while(!numbers.empty())
        {
            postfix += numbers.front();
            numbers.pop();
        }

         while (!operators.empty())
            {
                postfix += operators.top();
                operators.pop();
            }
        return postfix;
}

int EVALUATE_POSTFIX(string p_express)
{
    stack <double> express;
    char value;
    double temp1;
    double temp2;
    double answer;
    int length = p_express.length();
    for (int i=0; i<length; i++)
    {
        value = p_express[i];
        if (Is_It_An_Operand(value))
        {
            express.push(value - '0');

        }
        if (Is_It_An_Operator(value))
        {
        temp2 = express.top();
        express.pop();
        temp1 = express.top();
        express.pop();
            if(value == '+')
            {
                answer = temp1 + temp2;
            }
            if(value == '-')
            {
                answer = temp1 - temp2;
            }
            if (value == '*')
            {
                answer = temp1 * temp2;
            }
            if (value == '/')
            {
                answer = temp1 / temp2;
            }
            express.push(answer);
        }
    }
    cout << "Here is the postfix evaluation: " << answer << endl << endl;
    return answer;
}

bool Is_It_An_Operator(char value)
{
    if (value == '+' || value == '-' || value == '*' || value == '/')
        return true;
    else
        return false;
}

bool Is_It_An_Operand(char value)
{
    if (value >= '0' && value <= '100')
        return true;
    else
        return false;
}

int Operator_Weight(char value)
{
    int weight;
    if (value == '^')
    {
        weight = 3;
    }
    else if (value == '*' || value == '/')
    {
        weight = 2;
    }
    else if (value == '+' || value == '-')
    {
        weight = 1;
    }
    return weight;
}

bool IS_IT_A_PARENTHESIS(char value)
{
    if (value == '(')
    {
    return true;
    }
    if (value == ')'){
    return true;
    }
}

bool Higher_Precedence(char value, stack <char> &operators)
{
    if (!operators.empty()){
    if (Operator_Weight(operators.top()) > Operator_Weight(value))
    {
        return true;
    }
    if (Operator_Weight(operators.top()) == Operator_Weight(value))
    {
        return true;
    }
    else
    {
        return false;
    }
        return false;
    }

}


