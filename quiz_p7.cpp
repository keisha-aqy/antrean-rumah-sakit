#include <iostream>
#include <queue>
#include <vector>
#include <list>
using namespace std;

namespace control{
    
    struct patient{
        string name;
        int age;
        string disease;
        int day;
    };

    struct doctor {
        string name;
        string specialist;
    };
}

namespace ctrl = control;

namespace Menu{
    int Menu_Utama(){
        int Menu;
        do{
            cout << "\n======== HOSPITAL PROGRAM ========\n";
            cout << "1) Administrator\n";
            cout << "2) Doctor\n";
            cout << "3) Registretion\n";
            cout << "4) Close the program\n";
            cout << "===================================\n";
            cout << "Choose Menu (1/2/3/4) : ";
            cin >> Menu;

            if(Menu < 1 || Menu > 4){
                cout << "Invalid input. Please enter a valid option\n";
            }
        } while(Menu < 1 || Menu > 4);

        return Menu;
    }

    int Menu_admin(){
        int menuadmin;
        do{
            cout << "\n======== ADMINISTRATOR MENU ========\n";
            cout << "1) View Patient List\n";
            cout << "2) View Doctor List\n";
            cout << "3) Close the Program\n";
            cout << "====================================\n";
            cout << "Choose Menu (1/2/3) : ";
            cin >> menuadmin;

            if(menuadmin < 1 || menuadmin > 3){
                cout << "Invalid input. Please enter a valid option\n";
            }
        } while(menuadmin < 1 || menuadmin > 3);\

        return menuadmin;
    }

    int Menu_doctor(){
        int menudoc;
        do{
            cout << "\n======== DOCTOR MENU ========\n";
            cout << "1) Search Patient\n";
            cout << "2) Add doctor data\n";
            cout << "3) Close the program\n";
            cout << "=============================\n";
            cout << "Choose Menu (1/2/3) : ";
            cin >> menudoc;

            if(menudoc < 1 || menudoc > 3){
                cout << "Invalid input. Please enter a valid option\n";
            }
        } while(menudoc < 1 || menudoc > 3);

        return menudoc;
    }

    void Registration(queue<ctrl::patient>& q){
        ctrl::patient p;

        cout << "\nNote: The patient will be charged Rp 350000 per day of stay.";
        cout << "\n      A discount Rp 100000 stay is more than 5 days.\n";

        cout << "Name : ";
        cin.ignore();
        getline(cin, p.name);

        cout << "Age : ";
        cin >> p.age;

        cout << "Disease : ";
        cin.ignore();
        getline(cin, p.disease);

        cout << "Long stay (days): ";
        cin >> p.day;

        q.push(p);
        cout << "Succesfully registered!\n";
    }

    void Add_doctor(vector<ctrl::doctor>& list){
        ctrl::doctor d;
        cin.ignore();
        cout << "Name : ";;
        getline(cin, d.name);

        cout << "Specialist : ";
        getline(cin, d.specialist);
        list.push_back(d);
        cout << "Successfully registered!\n";
    }

    template<typename T>
    T calculate_Cost(T day, T rate){
        return day * rate;
    }

    template<typename T>
    T calculate_Cost(T day, T rate, T discount){
        T total = day * rate;
        return total - discount;
    }


    void showPatient(queue<ctrl::patient> q){
        cout << "\n======== Patient List ========\n";
        const int cost_day = 350000;
        while(!q.empty()){
            ctrl::patient p = q.front();
            cout << "---------------------------\n";
            cout << "Name : " << p.name << endl;
            cout << "Age : " << p.age << endl;
            cout << "Disease : " << p.disease << endl;
            cout << "Long stay (days) : " << p.day << endl;
            if(p.day > 5){
                cout << "Total Cost (with discount) : Rp " << calculate_Cost(p.day, cost_day, 100000) << endl;
            } else {
                cout << "Total Cost : Rp " << calculate_Cost(p.day, cost_day) << endl;
            }
            q.pop();
        }
    }

    void showDoctor(const vector<ctrl::doctor>& list){
        cout << "======== DOCTOR LIST ========\n";
        for(const auto& d : list){
            cout << "---------------------------\n";
            cout << "Name : " << d.name << endl;
            cout << "Specialist : " << d.specialist << endl;
        } 
    }

    void search_patient(queue<ctrl::patient> q){
        string search;
        cout << "Name patient: ";
        cin.ignore();
        getline(cin, search);

        bool found = false;
        while(!q.empty()){
            if(q.front().name == search){
                cout <<"\n---------------------------\n";
                cout << "Patient was found!\n";
                cout << "Name : " << q.front().name << endl;
                cout << "Disease : " << q.front().disease << endl;
                found = true;
            }
            q.pop();
        }

        if(!found){
            cout << "Patient not found!\n";
        }
    }
}

namespace Login{

    const string adminPass = "admin123";
    const string docPass = "doctor456";
  
    bool adminLogin() {
        string input;
        cout << "Enter the password : ";
        cin.ignore(); 
        getline(cin, input);
        return input == adminPass;
    }

    bool doctorLogin() {
        string input;
        cout << "Enter the password : ";
        cin.ignore(); 
        getline(cin, input);
        return input == docPass;
    }
}


namespace greetings{
    inline void greet(){
        cout << "\n========== FLOWER HOSPITAL ==========\n";
        cout << "Welcome to flower hospital!\n";
        cout << "Please choose menu below.\n";
        cout << endl;
    }

    inline void thanks(){
        cout << "\n----Thank you for using our program!----\n";
        cout << "-------Stay Healthy and take care!-------\n";
    }
}

namespace log = Login;
namespace grt = greetings;

int main(){
    int choice;
    
    queue<ctrl::patient> patientQueue;
    vector<ctrl::doctor> doctorList;
    do{
        grt::greet();
        choice = Menu::Menu_Utama();

        switch(choice){
            case 1 :
                if(log::adminLogin()){
                    int adm;
                    do{
                        adm = Menu::Menu_admin();
                        switch(adm){
                            case 1 :
                                Menu::showPatient(patientQueue);
                                break;
                            case 2 :
                                Menu::showDoctor(doctorList);
                                break;
                        }
                    } while(adm != 3);
                } else{
                    cout << "Invalid Password!\n";
                }
            break;

            case 2 :
                if(log::doctorLogin()){
                    int doc;
                    do{
                        doc = Menu::Menu_doctor();
                        switch(doc){
                            case 1 :
                                Menu::search_patient(patientQueue);
                                break;
                            case 2 :
                                Menu::Add_doctor(doctorList);
                                break;
                        }
                    }while(doc!= 3);
                } else{
                    cout << "Invalid Password!\n";
                }
            break;

            case 3 :
                Menu::Registration(patientQueue);
            break;

            case 4 :
                grt::thanks();
        }
    } while(choice != 4);

    return 0;
}
