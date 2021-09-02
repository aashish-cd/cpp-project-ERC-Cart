#include<iostream>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<conio.h>
#include<fstream>
#include<iomanip>

using namespace std;

// menus
class Menus {
    public:
        static void loginMenu() {
            system("cls");
            cout << "                           Select Your Choice:       " << endl << endl;
            cout << "                             1)User Login            " << endl << endl;
            cout << "                             2)Sign Up               " << endl << endl;
            cout << "                             3)Exit                  " << endl;
        }

    static void mainMenu() {
        system("cls");

        cout << "                         Select Your Choice:             " << endl << endl;
        cout << "                             1)Add Items to sell    " << endl << endl;
        cout << "                             2)View Items to buy             " << endl << endl;
        cout << "                             3)Cart                      " << endl << endl;
        cout << "                             4)Log Out                   " << endl << endl;
        cout << "                             5)Exit                      " << endl << endl;
    }
    static void category() {
        system("cls");

        cout << "                         Select Your Choice:         " << endl << endl;
        cout << "                             1)Furniture        " << endl << endl;
        cout << "                             2)Kitchen Ware             " << endl << endl;
        cout << "                             3)Electronics           " << endl << endl;
        cout << "                             4)Back               " << endl << endl;
    }
};

class Login {
    protected:
    string username;
    string password;
    public:
        void getUserPass() {
            cout << "Enter Username: ";
            cin >> username;
            cout << "\nEnter Password: ";
            char ch;
            int i = 0;
            while (1) {
                ch = getch();

                if (ch == 13) {
                    break;
                } else if (ch == '\b') {
                    password.pop_back();
                    ch = '\b';
                } else {
                    password.push_back(ch);
                    ch = '*';
                }
                cout << ch;
            }
        }
    bool authenticate() {
        bool user, pass, both;
        string ouser, opass;
        ifstream file;
        file.open("Users/users.txt");
        if(!file) {cout<<"No Data File";}
        else{
            while (file.eof() != true) {
            getline(file, ouser, ':');
            getline(file, opass, '\n');

            if (username == ouser) {
                user = true;
                if (password == opass) {
                    cout << "\n\tLogin Successfull" << endl;
                    break;
                } else {
                    pass = false;
                    cout << "\n\n\tIncorrect Password!!" << endl;
                    break;
                }
            } else {
                user = false;
            }
        }
        user == false ? cout << "\n\n\tCan't Find You In My Database!" << endl : cout << endl;
        file.close();
        _sleep(400);
        return (user && pass);
        }
    }
};

class Register {
    protected:
        string username;
    string password;
    public:
        string s;
    void setusername() {
        cout << "Enter Username: ";
        cin >> username;
    }
    void setpassword() {
        cout << "Enter Password: ";
        char ch;
        int i = 0;
        while (1) {
            ch = getch();
            //Checking for enter
            if (ch == 13) {
                break;
            } else if (ch == '\b') { //checking for backspace
                password.pop_back();
                ch = '\b';
            } else {
                password.push_back(ch);
                ch = '*';
            }
            cout << ch;
        }
    }
    void saveData() {
        ofstream file;
        file.open("Users/users.txt", ios_base::app);
        if(!file) {
            mkdir("Users");
            this->saveData();
        } else {
        file << username << ":" << password << endl;
        cout << "Register Successfully! Enter any key" << endl;
        getch();
        file.close();
        }
    }
};

// add items (write to file)
class ManageItems {
    protected:
        string itemD[4];
    ofstream fileWrite;
    ifstream fileRead;
    int itemToBuy;
    public:
        void addItem(string filename) {
            system("cls");
            cout << "Items Details:" << endl;
            fileWrite.open("Items/" + filename + ".txt", ios_base::app | ios_base::ate);
            if(!fileWrite) {
            mkdir("Items");
            this->addItem(filename);
            } else {
            cout << "Enter Item's Name,Price and Location" << endl;
            cin >> itemD[0] >> itemD[1] >> itemD[2];
            fileWrite << itemD[0] << " " << itemD[1] << " " << itemD[2] << endl;
            fileWrite.close();
            cout << "\n\n\tItem List Updated! Press Any Key To Go Back" << endl;
            getch();
            }
        }

    void viewItems(string catName, int i = 0) {
        fileRead.open("Items/" + catName + ".txt");
        if(!fileRead) {
            mkdir("Items");
            this->viewItems(catName);
        } else {
        system("cls");
        cout << "               Name      |       Price           |         Location        |" << endl << endl;
        while (fileRead >> itemD[0] >> itemD[1] >> itemD[2]) { //read text gap by space
            cout << setw(20) << itemD[0] << setw(20) << itemD[1] << setw(20) << itemD[2] << endl << endl;
        }
        fileRead.close();
        if (i == 0) {
            cout << "Enter the item's line number which you want to buy or [0] to go back:" << endl;
            cin >> itemToBuy;
            if (itemToBuy == 0) {} else {
                int checkLine = 1;
                fileRead.open("Items/" + catName + ".txt");
                while (fileRead >> itemD[0] >> itemD[1] >> itemD[2]) { //read text gap by space
                    cout << setw(20) << itemD[0] << setw(20) << itemD[1] << setw(20) << itemD[2] << endl << endl;
                    if (checkLine == itemToBuy) {
                        break;
                    } else {
                        checkLine++;
                    }
                }
                this -> postToCart();
            }
        }
    }
    }
    void postToCart() {
        fileWrite.open("Items/cart.txt", ios_base::app | ios_base::ate);
        fileWrite << itemD[0] << " " << itemD[1] << " " << itemD[2] << endl;
        fileWrite.close();
        cout << "\n\n\tItem Added To Cart Successfully" << endl;
        getch();
    }
};

class Cart: public ManageItems {
    private: char choice;
    ofstream fileWrite;
    public: void displayCartItems() {
        ManageItems::viewItems("cart", 1);
        cout << "\n\t\t\t\t[y] to buy      [b] to go back" << endl;
        cin >> choice;
        if (choice == 'y') {
            fileWrite.open("Items/cart.txt");
            fileWrite.close();
        } else if (choice == 'b') {}
    }
};

int main() {
    bool viewMenuCheck = false, addItems = false, mainmenu = false;
    int choice;
    while (1) {
        Menus::loginMenu();
        cin >> choice;
        switch (choice) {
        case 1: {
            Login l;
            l.getUserPass();
            mainmenu = l.authenticate();
        }
        break;
        case 2: {
            Register l, m;
            l.setusername();
            l.setpassword();
            l.saveData();
        }
        break;
        case 3:
            return 1;
            break;
        default:
            break;
        }
        if (mainmenu == true) break;
    }

    if (mainmenu == true) {
        while (1) {
            Menus::mainMenu();
            cin >> choice;
            switch (choice) {
            case 1: {
                addItems = true;
            }
            break;
            case 2: {
                viewMenuCheck = true;
            }
            break;
            case 3: {
                Cart c;
                c.displayCartItems();
                break;
            }
            break;
            case 4: {
                main();
            }
            break;
            case 5: {
                return 1;
            }
            break;
            default:
                break;
            }

            if (addItems == true) {
                ManageItems m;
                while (1) {
                    Menus::category();
                    cin >> choice;
                    switch (choice) {
                    case 1: {
                        m.addItem("furniture");
                        break;
                    }
                    case 2: {
                        m.addItem("kitchenware");
                        break;
                    }
                    case 3: {
                        m.addItem("electronics");
                        break;
                    }
                    break;
                    case 4: {
                        addItems = false;
                        break;
                    }
                    break;
                    default:
                        break;
                    }
                    if (addItems == false) {
                        break;
                    }
                }

            } else if (viewMenuCheck == true) {
                while (1) {
                    ManageItems m;
                    Menus::category();
                    cin >> choice;
                    switch (choice) {
                    case 1: {
                        m.viewItems("furniture");
                        break;
                    }
                    case 2: {
                        m.viewItems("kitchenware");
                        break;
                    }
                    break;
                    case 3: {
                        m.viewItems("electronics");
                        break;
                    }
                    break;
                    case 4: {
                        viewMenuCheck = false;
                        break;
                    }
                    break;
                    default:
                        break;
                    }
                    if (viewMenuCheck == false) {
                        break;
                    }
                }
            }
        }
    }
}
