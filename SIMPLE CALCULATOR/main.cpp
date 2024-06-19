#include <iostream>
#include <limits>

using namespace std;


int main()
{
    float num1, num2;
    char op, in;

    cout << "***SIMPLE CALCULATOR***" << endl;

    while(true)
    {
        cout << "Enter first number: ";
        cin >> num1;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, enter first number: ";
            cin >> num1;
        }

        cout << "Enter second number: ";
        cin >> num2;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, enter second number: ";
            cin >> num2;
        }

        cout << "chose the operation from the list: " << endl;
        cout << "1) +" << endl << "2) -" << endl << "3) *" << endl << "4) /" << endl;
        cout << "Enter your choice: ";
        cin >> op;
        while(cin.fail() || (op != '1' && op != '2' && op != '3' && op != '4' && op != '+' && op != '-' && op != '*' && op != '/'))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, enter your choice: ";
            cin >> op;
        }

        switch(op)
        {
        case '1':
        case '+':
            cout << num1 << " + " << num2 << " = " << num1 + num2 << endl;
            break;
        case '2':
        case '-':
            cout << num1 << " - " << num2 << " = " << num1 - num2 << endl;
            break;
        case '3':
        case '*':
            cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;
            break;
        case '4':
        case '/':
            cout << num1 << " / " << num2 << " = " << num1 / num2 << endl;
            break;
        }
        cout << "Want another operation? enter y for yes and n for no: ";
        cin >> in;
        while(cin.fail() || (in != 'y' && in != 'n' && in != 'Y' && in != 'N'))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, enter y for yes and n for no: ";
            cin >> in;
        }

        cout << endl;
        if(in == 'n')
            break;
    }

    cout << "See you soon!";
    return 0;
}
