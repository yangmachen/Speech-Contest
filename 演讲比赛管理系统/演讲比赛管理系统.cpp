#include <iostream>
#include "player.h"
#include "admin.h"

using namespace std;

int main(void)
{
    Admin ad;
    int select = 0;
    while (1)
    {
        ad.showMenu();
        cout << "请输入您的选择：" << endl;
        cin >> select;
        switch (select)
        {
        case 0:
            ad.exitSystem();
            break;
        case 1:
            ad.startSpeechContest();
            break;
        case 2:
            break;
        case 3:
            break;
        default:
        {
            cout << "您的输入有误！" << endl;
            system("read -s -n1 -p 'Press any key to continue...\n' key");
            system("clear");
            break;
        }

        }
    }
    

    return 0;
}