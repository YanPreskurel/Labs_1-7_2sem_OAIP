#include <iostream>
#include "stack.h"
#include <string>

bool Correct(std::string a) {
    stack<char> stack;
    int currentLine = 1;
    int pos = 0;
    for (char c : a) {
        pos++;
        switch (c) {

        case '(':
            stack.push(')');
            break;
        case '[':
            stack.push(']');
            break;
        case '{':
            stack.push('}');
            break;

        case ')':
        case ']':
        case '}':

            if (stack.get() != c) {
                return false;
            }

            stack.pop();

            break;

        case '\n':
            pos = 0;
            currentLine++;
            break;

        default:
            break;
        }
    }

    return true;
}

int main()
{
    std::string s = "(){}[]";
    std::cout << Correct(s);
}
