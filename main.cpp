#include <iostream>
#include <string>
#include "conio.h"

#include "my2048.h"

int main()
{
    while(1)
    {
        std::string str;
        system("cls");
        std::cout << "Please input the size of the game(2~9) or q(uit): ";
        std::cin >> str;

        if(str == "q")
        {
            break;
        }

        if(str.size() != 1 || str[0] < '2' || str[0] > '9')
        {
            std::cout << str << " is invalid size." << std::endl;
            system("pause");
            continue;
        }
        int size = (int)(str[0] - '0');
        my2048 pl(size);
        pl.play();
    }
    return 0;
}