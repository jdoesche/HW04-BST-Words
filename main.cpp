#include <iostream>
using namespace std;
#include "BST.h"

int main()
{
    cout << "HELLO WORLD!" << endl;
    cout << "Welcome to the BST Program" << endl;
    easyloop();
    return 0;
}

void easyop()
{
    cout << "You can:" << endl
         << "  (R)ead from File" << endl
         << "  (W)rite to File" << endl
         << "  (A)dd a New Entry to the BST" << endl
         << "  (D)elete an Existing Entry to the BST" << endl
         << "  (m)in Function" << endl
         << "  (M)ax Function" << endl
         << "  (P)rint the Current BST" << endl
         << "  (?) Bring up this menu again" << endl
         << "  (X) Exit the Program" << endl;
}

void easyloop()
{
    easyop();
    char op;
    int i = 0;

    while(true)
    {
        cout << "What would you like to do?" << endl;
        cin >> op;
        if (op != 'M')
            tolower(op);

        switch(op)
        {
            case 'x': //Exit
            {
                cout << "Are you sure? Any unsaved progress will be lost. (Y/N)" << endl;
                cin >> easyop;
                tolower (easyop);

                if (easyop == x || easyop == y)
                    return;
                else
                    break;
            }
            case '?': //easyop
            {
                easyop;
                break;
            }
            case 'r': //Read from File
            {
                string flnm;
                cout << "Please enter the name of the file you wish to read:" << endl;
                cin >> flnm;
                read(flnm);
                cout << "Done." << endl;
                break;
            }
            case 'w': //Write to File
            {
                string flnm;
                cout << "Please enter the name of the while you wish to write to:" << endl;
                cin >> flnm;
                write(flnm);
                cout << "Done." << endl;
                break;
            }
            case 'a': //Add a new entry
            {
                string newkey;
                int newdata;
                cout << "Please enter:" << endl;
                cout << " The item you wish to store (String):" << endl;
                cin >> newkey;
                cout << endl << "The number that represents it (Int):" << endl;
                cin >> newdata;
                cout << endl;
                add(newkey, newdata);

                cout << "Done." << endl;
            }
            case 'd': //Delete an existing entry
            {
                string choppingblock;
                cout << "Please enter the item you wish to delete (String):" << endl;
                cin >> choppingblock;
                remove(choppingblock);
                cout << endl << "Done." << endl;
                break;
            }
            case 'p': //Print
            {
                printinitializer();
                break;
            }
            case 'm': //Min Function
            {
                siprint(min(minmax()));
                break;
            }
            case 'M': //Max Function
            {
                siprint(max(minmax()));
                break;
            }
            default: //Wat?
            {
                cout << "Input not recognized. Try again." << endl;
                break;
            }
        }

        cout << "------------------------------[ " << i << " ]" << endl;
        i++;
    }
}