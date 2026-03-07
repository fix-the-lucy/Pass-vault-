#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int main() {
    string username[10], password[10];
    string storedFile[10][10], storedPass[10][10];
    int fileCount[10] = {0};
    int choice, i = 0;
    string login, pass;

    ifstream reader("users.txt");
    if(reader.is_open()) {
        while(i < 10 && reader >> username[i] >> password[i]) {
            reader >> fileCount[i];
            for(int j = 0; j < fileCount[i]; j++) {
                reader >> storedFile[i][j] >> storedPass[i][j];
            }
            i++;
        }
        reader.close();
    }

    while(true) {
        cout << "\n1. New user\n2. Old user\n3. Exit\nSelection: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        cin.ignore();

        if(choice == 1) {
            if(i < 10) {
                cout << "Enter username: "; getline(cin, username[i]);
                cout << "Enter password: "; getline(cin, password[i]);
                fileCount[i] = 0;

                ofstream file("users.txt", ios::app);
                file << username[i] << " " << password[i] << " " << fileCount[i] << endl;
                file.close();

                i++;
                cout << "Registered!" << endl;
            } else { cout << "Limit reached!" << endl; }
        }
        else if (choice == 2) {
            bool found = false;
            cout << "Username: "; getline(cin, login);
            cout << "Password: "; getline(cin, pass);

            for(int j = 0; j < i; j++) {
                if(username[j] == login && password[j] == pass) {
                    found = true;
                    cout << "\nWelcome " << username[j] << "!" << endl;
                    int subChoice;
                    bool loggedIn = true;
                    while(loggedIn) {
                        cout << "\n1. Add New File\n2. View My Vault\n3. Logout\nEnter: ";
                        cin >> subChoice; cin.ignore();
                        
                        if(subChoice == 1) {
                            if(fileCount[j] < 10) {
                                cout << "File Name: "; getline(cin, storedFile[j][fileCount[j]]);
                                cout << "File Pass: "; getline(cin, storedPass[j][fileCount[j]]);
                                fileCount[j]++;

                                ofstream updateFile("users.txt");
                                for(int k=0; k<i; k++) {
                                    updateFile << username[k] << " " << password[k] << " " << fileCount[k] << " ";
                                    for(int f=0; f<fileCount[k]; f++) {
                                        updateFile << storedFile[k][f] << " " << storedPass[k][f] << " ";
                                    }
                                    updateFile << endl;
                                }
                                updateFile.close();
                                cout << "File Added!" << endl;
                            } else { cout << "Vault Full (Max 10)!" << endl; }
                        }    
                        else if(subChoice == 2) {
                            cout << "\n--- " << username[j] << "'s VAULT ---" << endl;
                            if(fileCount[j] == 0) cout << "No files stored." << endl;
                            for(int f=0; f<fileCount[j]; f++) {
                                cout << f+1 << ". File: " << storedFile[j][f] << " | Pass: " << storedPass[j][f] << endl;
                            }
                        }
                        else if(subChoice == 3) { loggedIn = false; }
                    }
                    break;
                }
            }
            if(!found) cout << "Login Failed!" << endl;
        }
        else if(choice == 3) break;
    }
    return 0;
}
