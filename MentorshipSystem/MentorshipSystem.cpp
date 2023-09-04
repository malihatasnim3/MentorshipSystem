#include <iostream>
#include <string>
using namespace std;

class Student
{
protected:
    string name;

public:
    Student(string n = "");
    string getName() const;
    void setName(string n);
};


class Mentor : public Student
{
protected:
    double cpa;

public:
    Mentor(string n, double c) : Student(n), cpa(c) {}
    virtual void edit() = 0;
    virtual void print() const = 0;
};

class Coach : public Mentor
{
protected:
    string expertise;
public:
    Coach(string name, double cpa, string expertise);
    string getExpertise()const;
    void setExpertise(string expertise);
    void edit();
    void print() const;

};


class Support : public Mentor
{
protected:
    string phone;
public:
    Support(string name, double cpa, string phone);
    string getPhone() const;
    void setPhone(string p);
    void edit();
    void print() const;
};


class Mentee :public Student
{
protected:
    int level;
    Mentor* mentor;
public:
    Mentee(string name, int level);
    void assignMentor(Mentor* m);
    void displayInfo() const;
};


Student::Student(string n) : name(n) {}
string Student::getName() const { return name; }
void Student::setName(string n) { name = n; }


Coach::Coach(string name, double cpa, string expertise) : Mentor(name, cpa), expertise(expertise) {}

string Coach::getExpertise() const { return expertise; }
void Coach::setExpertise(string expertise) { this->expertise = expertise; }

void Coach::edit()
{
    cout << "Mentor's Information : " << endl;
    print();
    cout << endl;
    cout << "You can only edit the mentor's expertise" << endl << endl;
    cout << "Enter new expertise => ";
    cin.ignore();
    string expertise;
    getline(cin, expertise);

    this->expertise = expertise;

}

void Coach::print() const
{
    cout << "Mentoring type : Coach-based " << endl;
    cout << "Mentor's Name : " << name << endl;
    cout << "Mentor's CPA : " << cpa << endl;
    cout << "Mentor's Expertise : " << expertise << endl;
}

Support::Support(string name, double cpa, string phone) :Mentor(name, cpa), phone(phone) {}

string Support::getPhone() const { return phone; }
void Support::setPhone(string p) { phone = p; }

void Support::edit()
{
    cout << "Mentor's Information: " << endl;
    print();
    cout << endl;
    cout << "You can only edit the mentor's phone number" << endl << endl;
    cout << "Enter new phone number =>";
    cin >> phone;
}
void Support::print() const
{
    cout << "Mentoring type : Support-based" << endl;
    cout << "Mentor's Name : " << name << endl;
    cout << "Mentor's CPA : " << cpa << endl;
    cout << "Mentor's Phone : " << phone << endl;
}

Mentee::Mentee(string name, int level) : Student(name), level(level), mentor(NULL) {}

void Mentee::assignMentor(Mentor* m)
{
    mentor = m;
}

void Mentee::displayInfo() const
{
    cout << "Mentee's Name : " << name << endl;
    cout << "Mentee's Level : " << level << endl;

    if (mentor)
    {
        mentor->print();
    }
    else
    {
        cout << "No mentor yet" << endl;
    }

    cout << endl;
}

int menu()
{
    cout << endl;
    cout << "========== Menu ==========" << endl;
    cout << "1. Select first mentor" << endl;
    cout << "2. Select second mentor" << endl;
    cout << "3. Display selected mentor" << endl;
    cout << "4. Edit selected mentor" << endl;
    cout << "5. Assign selected mentor to mentee" << endl;
    cout << "6. Unassign mentor from mentee" << endl;
    cout << "7. Display all mentees" << endl;
    cout << "9. Exit" << endl;
    cout << endl;

    int choice;
    cout << "Choose an operation [1-7, or 9] => ";
    cin >> choice;

    cin.ignore();
    cout << endl;

    return choice;
}


int main()
{

    Mentee mentees[3] = { Mentee("Abdul Samad", 2),
                         Mentee("Nurdiana", 1),
                         Mentee("Nurazlan", 2) };
    int index;

    Coach mentor1("Ahmad Kamal", 3.87, "Programming");
    Support mentor2("Siti Aminah", 3.98, "0123456789");

    Mentor* nowMentor = &mentor1;

    int operation;

    operation = menu();

    while (operation != 9)
    {
        switch (operation)
        {
        case 1:
            nowMentor = &mentor1;
            cout << "First mentor is selected" << endl;
            break;

        case 2:
            nowMentor = &mentor2;
            cout << "Second mentor is selected" << endl;
            break;

        case 3:
            cout << "Current selected mentor: " << nowMentor->getName() << endl;
            break;

        case 4:
            nowMentor->edit();
            break;

        case 5:
            cout << "Enter the index of mentee to assign with the current mentor => ";
            cin >> index;
            mentees[index].assignMentor(nowMentor);
            break;

        case 6:
            cout << "Enter the index of mentee to remove its mentor => ";
            cin >> index;
            mentees[index].assignMentor(NULL);
            break;

        case 7:
            cout << "List of mentees:" << endl;
            for (int i = 0; i < 3; i++)
            {
                cout << "#" << i + 1 << endl;
                mentees[i].displayInfo();
            }
            break;

        }

        operation = menu();

    }

    system("pause");
    return 0;
}
