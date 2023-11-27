#include <iostream>
using namespace std;
#include <string>
#include <cctype>
#include "BST.h"

void easyop();
void easyloop();

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
         << "  (S)earch for a Specific Entry" << endl
         << "  (P)rint the Current BST" << endl
         << "  (?) Bring up this menu again" << endl
         << "  (X) Exit the Program" << endl;
}

void easyloop()
{
    BST a;
    easyop();
    char op;
    int i = 0;
    int split = 'a' - 'A';

    while(true)
    {
        cout << "What would you like to do?" << endl;
        cin >> op;
        if (op != 'M' && op >= 'A' && op <= 'Z')
            op = op + split;            

        switch(op)
        {
            case 'x': //Exit
            {
                cout << "Are you sure? Any unsaved progress will be lost. (Y/N)" << endl;
                cin >> op;
                if (op >= 'A' && op <= 'Z')
                    op = op + split;

                if (op == 'x' || op == 'y')
                    return;
                else
                    break;
            }
            case '?': //easyop
            {
                easyop();
                break;
            }
            case 'r': //Read from File
            {
                string flnm;
                cout << "Please enter the name of the file you wish to read:" << endl;
                cin >> flnm;
                a.read(flnm);
                cout << "Done." << endl;
                break;
            }
            case 'w': //Write to File
            {
                string flnm;
                cout << "Please enter the name of the while you wish to write to:" << endl;
                cin >> flnm;
                a.write(flnm);
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
                a.add(newkey, newdata);

                cout << "Done." << endl;
                break;
            }
            case 'd': //Delete an existing entry
            {
                string choppingblock;
                cout << "Please enter the item you wish to delete (String):" << endl;
                cin >> choppingblock;
                a.remove(choppingblock);
                cout << endl << "Done." << endl;
                break;
            }
            case 's': //Search
            {
                string findme;
                cout << "Please enter the item you wish to find (String):" << endl;
                cin >> findme;
                a.siprint(a.find(NULL, findme));
                cout << endl << "Done." << endl;
                break;
            }
            case 'p': //Print
            {
                a.printinitializer();
                break;
            }
            case 'm': //Min Function
            {
                a.siprint(a.min(NULL));
                break;
            }
            case 'M': //Max Function
            {
                a.siprint(a.max(NULL));
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