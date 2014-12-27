#include <iostream>
#include <string>
#include "conio.h"

#include "my2048.h"
#include "auto2048.h"

void test_destructor();
void test_manual_play();
void test_auto2048_with_show();
void evalate_auto2048();

int main()
{
    // test_destructor();
    test_manual_play();
    
    // test_auto2048_with_show();
    //evalate_auto2048();

	printf("Hello world.\n");
    system("pause");
    return 0;
}

void test_destructor()
{
    {
        my2048 a;
        a.init(10);
    }
    system("pause");
}

void test_manual_play()
{

    while(1)
    {
        std::string str;
        system("cls");
        std::cout << "Please input the size of the game(2~9) or p(quit): ";
        std::cin >> str;

        if(str == "p")
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
}

void test_auto2048_with_show()
{
    auto2048 ap(3);
    int max_val = ap.autoplay_random(true);
    std::cout << max_val << std::endl;
}

void evalate_auto2048()
{
    auto2048 ap(4);
    ap.evaluate_all_methods();
}