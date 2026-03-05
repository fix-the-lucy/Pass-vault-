#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int main() {
    string username[10];
    string password[10];
    int choice;
    int i = 0;
    string login, pass;

    while(true) {
        cout << "\n1. New user\n2. Old user\n3. Exit\nEnter choice: ";
        cin >> choice;

        if(choice == 1) {
            if(i < 10) {
                cout << "Enter your username: ";
                cin >> username[i];
                cout << "Enter the password: ";
                cin >> password[i];

                ofstream file;
                file.open("users.txt", ios::app);
                if(file.is_open()) {
                    file << username[i] << " " << password[i] << endl;
                    file.close();
                }

                i++;
                cout << "Registered successfully and saved to file!" << endl;
            } else {
                cout << "Memory Full!" << endl;
            }
        }
        else if (choice == 2) {
            bool found = false;
            cout << "Enter your username: ";
            cin >> login;
            cout << "Enter the password: ";
            cin >> pass;

            for(int j = 0; j < i; j++) {
                if(username[j] == login && password[j] == pass) {
                    cout << "Welcome " << username[j] << "!" << endl;
                    found = true;

                    int subChoice;
                    bool loggedIn = true;
                    while(loggedIn) {
                        cout << "\n--- DASHBOARD ---\n1. View Profile\n2. Change Password\n3. Logout\nEnter: ";
                        cin >> subChoice;

                        if(subChoice == 1) {
                            cout << "Username: " << username[j] << endl;
                        }
                        else if(subChoice == 2) {
                            cout << "Enter new password: ";
                            cin >> password[j];
                            cout << "Password updated in RAM!" << endl;
                        }
                        else if(subChoice == 3) {
                            loggedIn = false;
                        }
                    }
                    break;
                }
            }

            if(!found) {
                cout << "Invalid Username/Password or Not Registered!" << endl;
            }
        }
        else if(choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
