// GROUP 7
// UTM HOTEL MANAGEMENT SYSTEM
// MAYSARA MOHAMED SHOKRY A21EC4002
//
//
//
#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <cmath>
#include <cstdlib>
#include <cctype>

using namespace std;

class BillNode
{
public:
    int roomNum, days;
    float price;
    string MatricNum, name, DateIn, DateOut, Emial;
    double total;
    BillNode *next;
};
class BillQueue
{
    BillNode *frontPtr, *BackPtr;

public:
    BillQueue();
    ~BillQueue();
    bool IsEmpty();

    // the implementation of queue
    void Enqueue(int, float, string, string, string, string, string, int);

    void ConfirmPage(BillNode *);

    // implementation of queue
    string Dequeue();

    BillNode *GetRoomNum()
    {
        BillNode *tmp = new BillNode;
        if (frontPtr != NULL)
        {
            tmp = frontPtr;
        }
        return tmp;
    }
};
BillQueue::BillQueue()
{
    BackPtr = NULL;
    frontPtr = NULL;
}
BillQueue::~BillQueue()
{
    BillNode *tmp = frontPtr;
    while (tmp)
    {
        frontPtr = tmp->next;
        delete tmp;
        tmp = frontPtr;
    }
}
bool BillQueue::IsEmpty()
{
    return (BackPtr == NULL && frontPtr == NULL);
}
void BillQueue::Enqueue(int _RoomNum, float _Price, string _MatricNum, string _Name, string _DateIn, string _DateOut, string _Email, int _days)
{
    BillNode *tmp = new BillNode;
    if (BackPtr == NULL)
    {
        tmp->next = NULL;
        tmp->roomNum = _RoomNum;
        tmp->price = _Price;
        tmp->MatricNum = _MatricNum;
        tmp->name = _Name;
        tmp->DateIn = _DateIn;
        tmp->DateOut = _DateOut;
        tmp->days = _days;
        tmp->Emial = _Email;
        frontPtr = BackPtr = tmp;
    }
    else
    {
        BackPtr->next = tmp;
        tmp->roomNum = _RoomNum;
        tmp->price = _Price;
        tmp->MatricNum = _MatricNum;
        tmp->name = _Name;
        tmp->DateIn = _DateIn;
        tmp->DateOut = _DateOut;
        tmp->days = _days;
        tmp->Emial = _Email;
        tmp->next = NULL;
        BackPtr = tmp;
    }
}
void BillQueue::ConfirmPage(BillNode *tmp)
{
    if (tmp->days <= 1)
    {
        tmp->days == 1;
    }
    tmp->total = tmp->price * 1.06 * (tmp->days * 1.0);
    cout << "\n\n======	BOOKING NEED TO CONFIRM		======";
    cout << "\nCUSTOMER NAME\t: " << tmp->name << endl;
    cout << "\nCUSTOMER EMAIL\t: " << tmp->Emial << endl;
    cout << "CUSTOMER IC\t: " << tmp->MatricNum << endl;
    cout << "BOOKING ROOM NO\t: " << tmp->roomNum << endl;
    cout << "DATE CHECK IN\t: " << tmp->DateIn << endl;
    cout << "DATE CHECK OUT\t: " << tmp->DateOut << endl;
    cout << "NUMBER OF DAYS\t: " << tmp->days << endl;
    cout << "PRICE PER NIGHT\t: RM" << tmp->price << endl;
    cout << "TOTAL(AFTER SST): RM" << tmp->total << endl;
}
string BillQueue::Dequeue()
{
    BillNode *tmp = new BillNode;
    tmp = frontPtr;
    if (frontPtr == NULL)
    {
        cout << "NO PENDING BOOKING NEED TO BE CONFIRMED" << endl;
        return "NULL";
    }
    else if (tmp->next != NULL)
    {
        int choice;
        ConfirmPage(tmp);
        do
        {
            cout << "DO YOU WANT TO CONFIRM THIS BOOKING? (0-PENDING, 1-CONFIRMED, 2-CANCELLED) : ";
            cin >> choice;
            if (choice == 1)
            {
                tmp = tmp->next;
                frontPtr = tmp;
                return "BOOKED-CONFIRMED";
            }
            else if (choice == 0)
            {
                tmp = tmp->next;
                frontPtr = tmp;
                return "BOOKED-PENDING";
            }
            else if (choice == 2)
            {
                tmp = tmp->next;
                frontPtr = tmp;
                return "CANCELLED";
            }
        } while (choice < 0 && choice > 2);
    }
    else
    {
        int choice;
        ConfirmPage(tmp);
        do
        {
            cout << "\n\nDO YOU WANT TO CONFIRM THIS BOOKING? (0-PENDING, 1-CONFIRMED, 2-CANCELLED) : ";
            cin >> choice;
            if (choice == 1)
            {
                tmp = tmp->next;
                frontPtr = tmp;
                return "BOOKED-CONFIRMED";
            }
            else if (choice == 0)
            {
                return "BOOKED-PENDING";
            }
            else if (choice == 2)
            {
                return "CANCELLED";
            }
        } while (choice < 0 && choice > 2);
    }
}

class StudentNode
{
public:
    string StudentName, StudentPhone, MatricNum, DateIn, DateOut, Email;
    int RoomNum;
    StudentNode *next;
};
class Student
{
    StudentNode *head;

public:
    Student();
    void StudentData(string, string, string, string, string, string, int);
    void deleteStudent(string, int);
    bool FindStudent(string);
    void DisplayRoom();
};
Student::Student()
{
    head = NULL;
}
void Student::StudentData(string _Name, string _Phone, string _MatricNum, string _Email, string _DateIn, string _DateOut, int _RoomNum)
{
    int currIndex = 0;
    StudentNode *currNode = head;
    StudentNode *prevNode = NULL;
    while (currNode && _Name > currNode->StudentName)
    {
        prevNode = currNode;
        currNode = currNode->next;
        currIndex++;
    }
    StudentNode *newNode = new StudentNode;
    newNode->StudentName = _Name;
    newNode->StudentPhone = _Phone;
    newNode->MatricNum = _MatricNum;
    newNode->Email = _Email;
    newNode->DateIn = _DateIn;
    newNode->DateOut = _DateOut;
    newNode->RoomNum = _RoomNum;
    if (currIndex == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }
}
void Student::deleteStudent(string _MatricNum, int _RoomNum)
{
    StudentNode *prevNode = NULL;
    StudentNode *CurrNode = head;
    int currIndex = 1;

    string matric = CurrNode->MatricNum.substr(0, 8);
    int y = atoi(matric.c_str());
    int x = atoi(_MatricNum.c_str());

    while ((CurrNode && x != y) || (CurrNode && CurrNode->RoomNum != _RoomNum))
    {
        prevNode = CurrNode;
        CurrNode = CurrNode->next;
        currIndex++;
    }
    if (x == y)
    {
        if (CurrNode)
        {
            if (prevNode)
            {
                prevNode->next = CurrNode->next;
                delete CurrNode;
            }
            else
            {
                head = CurrNode->next;
                delete CurrNode;
            }
        }
        cout << "ROOM BOOKED(" << _RoomNum << ") UNDER STUDENT WITH MATRIC NUMBER : " << _MatricNum << " HAS BEEN DELETED " << endl;
    }
    else
    {
        cout << "BOOKING RECORD OF ROOM NUMBER" << _RoomNum << " UNDER STUDENT WITH MATRIC NUMBER " << _MatricNum << " ICANNOT BE FOUND" << endl;
    }
}
bool Student::FindStudent(string _MatricNum)
{
    StudentNode *currNode = head;
    int currIndex = 1;
    string Matric = currNode->MatricNum.substr(0, 8);
    int y = atoi(Matric.c_str());
    int x = atoi(_MatricNum.c_str());

    if (x == y)
        return true;
    else
        return false;
}
void Student::DisplayRoom()
{
    int num = 0;
    StudentNode *currNode = head;
    cout << "\n\n======================================    WELCOME TO UTM HOTEL    ======================================" << endl;
    cout << "\n\n======================================    BOOKING IN UTM HOTEL    ======================================" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(40) << "NAME" << setw(50) << "EMAIL" << setw(11) << "ROOM NO." << setw(15) << "PHONE" << setw(20) << "MATRIC" << setw(12) << "DATE IN" << setw(12) << "DATE OUT" << endl;

    while (currNode != NULL)
    {
        cout << left << setw(40) << currNode->StudentName
             << setw(50) << left << currNode->Email
             << setw(11) << left << currNode->RoomNum
             << setw(15) << left << currNode->StudentPhone
             << setw(20) << left << currNode->MatricNum
             << setw(12) << left << currNode->DateIn
             << setw(12) << left << currNode->DateOut
             << endl;
        currNode = currNode->next;
        num++;
    }
    cout << "\nNUMBER OF ROOM IN THE HOTEL: " << num << endl
         << endl
         << endl;
}

class RoomNode
{
public:
    int floorNum, roomNum, roomType, status;
    float price;
    RoomNode *next, *prev;
};

string roomType(int roomT)
{
    if (roomT == 1)
    {
        return "SINGLE";
    }
    else if (roomT == 2)
    {
        return "DOUBLE";
    }
    else if (roomT == 3)
    {
        return "TRIPLE";
    }
    else if (roomT == 4)
    {
        return "PREMIUM";
    }
    else
    {
        return "DEFAULT";
    }
}

string status(int status)
{
    if (status == 1)
    {
        return "BOOKED-PENDING";
    }
    else if (status == 2)
    {
        return "BOOKED-CONFIRMED";
    }
    else if (status == 0)
    {
        return "AVAILABLE";
    }
    else
    {
        return "DEFAULT";
    }
}

class room
{
private:
    RoomNode *head;

public:
    room();
    void insertRoom(int);
    void deleteRoom(int);
    bool booking(int);
    bool cancel(int);
    bool findBookedRoom(int);
    RoomNode *findRoom(int);
    void printRoom();
    float setprice(RoomNode *);
};

room::room()
{
    head = NULL;
}

void room::insertRoom(int RoomNum)
{
    int currIndex = 0;
    RoomNode *currNode = head;
    RoomNode *prevNode = NULL;

    while (currNode && RoomNum > currNode->roomNum)
    {
        prevNode = currNode;
        currNode = currNode->next;
        currIndex++;
    }
    RoomNode *newNode = new RoomNode;
    newNode->roomNum = RoomNum;
    newNode->floorNum = RoomNum / 1000;
    newNode->roomType = (RoomNum - (RoomNum / 1000 * 1000)) / 100;
    newNode->price = setprice(newNode);
    newNode->status = 0;
    if (currIndex == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }
}

float room::setprice(RoomNode *n)
{
    float price = 0;
    RoomNode *newNode = new RoomNode;
    newNode = n;

    if (newNode->roomType == 1)
    {
        price += 600.00;
    }
    if (newNode->roomType == 2)
    {
        price += 400.00;
    }
    if (newNode->roomType == 3)
    {
        price += 300.00;
    }
    if (newNode->roomType == 4)
    {
        price += 900.00;
    }
    else
    {
        price = 0.00;
    }
    price += (newNode->floorNum * 10.00);
    return price;
}

void room::deleteRoom(int RoomNum)
{
    RoomNode *prevNode = NULL;
    RoomNode *currNode = head;

    int currIndex = 1;
    while (currNode && currNode->roomNum != RoomNum)
    {
        prevNode = currNode;
        currNode = currNode->next;
        currIndex++;
    }
    if (currNode)
    {
        if (prevNode)
        {
            prevNode->next = currNode->next;
            delete currNode;
        }
        else
        {
            head = currNode->next;
            delete currNode;
        }
        cout << "YOU SUCCESSFULLY ROOM NUMBER :" << RoomNum << endl;
    }
    else
    {
        cout << "ROOM NUMBER (" << RoomNum << ") DOES NOT EXIST." << endl;
    }
}

bool room::booking(int RoomNum)
{
    RoomNode *newNode = new RoomNode;
    newNode = findRoom(RoomNum);
    if (!newNode)
    {
        cout << "ROOM NUMBER " << RoomNum << " CANNOT BE FOUND\n"
             << endl;
        return false;
    }
    else
    {
        if (newNode->status == 0)
        {
            newNode->status = 1;
            cout << "ROOM NUMBER " << RoomNum << " IS SUCCESSFULLY BOOKED\n\n"
                 << endl;
            return true;
        }
        else
        {
            cout << "ROOM NUMBER " << RoomNum << " IS NOT AVAILABLE\n\n " << endl;
            return false;
        }
    }
}
bool room::cancel(int RoomNum)
{
    RoomNode *newNode = new RoomNode;
    newNode = findRoom(RoomNum);
    if (!newNode)
    {
        cout << "ROOM NUMBER " << RoomNum << " NOT FOUND\n"
             << endl;
        return false;
    }
    else
    {
        if (newNode->status == 1)
        {
            newNode->status = 0;
            cout << "BOOKING ROOM NUMBER" << RoomNum << " IS SUCCESSFULLY CANCELLED" << endl;
            return true;
        }
        else
        {
            cout << "BOOKING ROOM NUMBER (" << RoomNum << ") NOT FOUND" << endl;
            cout << "SOORY , UNABLE TO MAKE CANCELLATION , TRY AGAIN" << endl;
            return false;
        }
    }
}
bool room::findBookedRoom(int RoomNum)
{
    RoomNode *newNode = new RoomNode;
    newNode = findRoom(RoomNum);
    if (!newNode)
    {
        return false;
    }
    else if (newNode->status == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
RoomNode *room::findRoom(int RoomNum)
{
    RoomNode *currNode = head;
    int currIndex = 1;
    while (currNode && currNode->roomNum != RoomNum)
    {
        currNode = currNode->next;
        currIndex++;
    }
    if (currNode)
        return currNode;
    else
        return 0;
}
void room::printRoom()
{
    int num = 0;
    RoomNode *currNode = head;
    cout << "====================    UTM HOTEL ROOMS DETAILS    ====================" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "FLOOR\tROOM NO.\tROOM TYPE\tPRICE\tSTATUS" << endl;
    while (currNode != NULL)
    {
        cout << currNode->floorNum << "\t"
             << currNode->roomNum << "\t\t"
             << roomType(currNode->roomType) << "\t\t"
             << currNode->price << "\t"
             << status(currNode->status) << "\t"
             << endl;

        currNode = currNode->next;
        num++;
    }
    cout << "\nNUMBER OF ROOM IN UTM HOTEL: " << num << endl
         << endl
         << endl;
}

int Days(string date)
{
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(4, 2).c_str());
    int day = atoi(date.substr(6, 2).c_str());
    int choice = 0;
    for (int i = 1900; i < year; ++i)
    {
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        {
            choice += 366;
        }
        else
        {
            choice += 365;
        }
    }
    for (int i = 1; i < month; ++i)
    {
        switch (i)
        {
        case 1:
            choice += 31;
            break;
        case 2:
            choice += (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) ? 29 : 28;
            break;
        case 3:
            choice += 31;
            break;
        case 4:
            choice += 30;
            break;
        case 5:
            choice += 31;
            break;
        case 6:
            choice += 30;
            break;
        case 7:
            choice += 31;
            break;
        case 8:
            choice += 31;
            break;
        case 9:
            choice += 30;
            break;
        case 10:
            choice += 31;
            break;
        case 11:
            choice += 30;
            break;
        case 12:
            choice += 31;
            break;
        }
    }
    return choice += day - 1;
}

int date(string date1, string date2)
{
    return (Days(date1) - Days(date2));
}

int main()
{

    // room object
    room r;
    Student s;
    BillQueue b;
    int choice;

    // rooms
    int rooms[] = {1101, 1202, 1303, 1401, 1501, 1102, 1103, 1104, 1105, 2201, 2202, 2203, 2204, 2205, 3301, 3302, 3303, 3304, 3305, 4401, 4402, 4403, 4404, 4405};

    for (int i = 0; i < 24; i++)
    {
        r.insertRoom(rooms[i]);
    }

    do
    {
        system("CLS");
        cout << "=============		WELCOME TO UTM HOTEL MANAGEMENT SYSTEM		=============" << endl;
        cout << "\t\t\tLOGIN AS" << endl;
        cout << "\t\t\t1. ADMIN\n\t\t\t2. STUDENT \n\t\t\t3. EXIT\n"
             << endl;
        cout << "CHOICE : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int choice1;
            int roomNum;
            int count1;
            do
            {
                system("CLS");
                cout << "=============	ADMIN MENU	=============" << endl;
                cout << "\t1. ADD ROOM\n\t2. DELETE ROOM\n\t3. DISPLAY ROOM\n\t4. CHANGE PRICE\n\t5. CHECK CUSTOMER BOOKING LIST\n\t6. REVIEW AND CONFIRM PENDING BOOKING\n\t7. BACK TO MAIN MENU\n"
                     << endl;
                cout << "CHOICE : ";
                cin >> choice1;
                switch (choice1)
                {
                case 1:
                    count1 = 1;
                    do
                    {
                        cout << "\nENTER THE ROOM NUMBER YOU WANT TO ADD : ";
                        cin >> roomNum;
                        if (!r.findRoom(roomNum))
                        {
                            r.insertRoom(roomNum);
                            cout << "YOU SUCCESSFULLY ADD ROOM NUMBER (" << roomNum << ") INTO THE LIST" << endl;
                        }
                        else
                        {
                            cout << "ROOM NUMBER " << roomNum << " IS OUT OF THE LIST.  ENTER ANOTHER ROOM NUMBER." << endl;
                        }
                        cout << "DO YOU WANT TO CONTINUE TO ADD MORE ROOM ( 1-YES, 0-NO ) :";
                        cin >> count1;
                    } while (count1 != 0);
                    break;
                case 2:
                    count1 = 1;
                    do
                    {
                        cout << "\nENTER THE ROOM NUMBER YOU WANT TO DELETE : ";
                        cin >> roomNum;
                        if (r.findRoom(roomNum))
                        {
                            r.deleteRoom(roomNum);
                        }
                        else
                        {
                            cout << "ROOM IS NOT FOUND! ENTER ANOTHER ROOM NUMBER." << endl;
                        }
                        cout << "DO YOU WANT TO DELETE OTHER ROOMS ?( 1-YES, 0-NO ) : ";
                        cin >> count1;
                    } while (count1 != 0);
                    break;

                case 3:
                    r.printRoom();
                    break;
                case 4:
                    count1 = 1;
                    do
                    {
                        cout << "\nENTER THE ROOM NUMBER TO CHANGE PRICE: " << endl;
                        cout << "ROOM NUMBER        : ";
                        cin >> roomNum;
                        if (r.findRoom(roomNum))
                        {
                            float newPrice;
                            cout << "CHANGE PRICE RM : ";
                            cin >> newPrice;
                            RoomNode *newNode = r.findRoom(roomNum);
                            newNode->price = newPrice;
                            cout << "YOU SUCCESSFULLY CHANGE THE PRICE OF ROOM NUMBER " << roomNum << " TO PRICE RM " << newPrice << endl
                                 << endl;
                        }
                        else
                        {
                            cout << "ROOM NUMBER (" << roomNum << ") IS NOT FOUND. ENTER ANOTHER ROOM NUMBER." << endl
                                 << endl;
                        }
                        cout << "DO YOU WANT TO CHANGE PRICES OF OTHER ROOMS? ( 1-YES, 0-NO ) :";
                        cin >> count1;
                    } while (count1 != 0);
                    break;

                case 5:
                    s.DisplayRoom();
                    break;
                case 6:
                    count1 = 1;

                    cout << "\n\n======      REVIEWING BOOKING INFORMATION     ======\n";
                    do
                    {
                        BillNode *rev = new BillNode;
                        rev = b.GetRoomNum();
                        string x = b.Dequeue();
                        RoomNode *tmp = new RoomNode;
                        tmp = r.findRoom(rev->roomNum);

                        if (x == "BOOKED & CONFIRMED")
                        {
                            tmp->status = 2;
                            break;
                        }
                        else if (x == "CANCELLED")
                        {
                            tmp->status = 0;
                            break;
                        }
                        else if (x == "BOOKED & PENDING")
                        {
                            tmp->status = 1;
                            b.Enqueue(rev->roomNum, rev->price, rev->MatricNum, rev->name, rev->Emial, rev->DateIn, rev->DateOut, rev->days);
                            break;
                        }
                        else
                        {
                        }
                        cout << "DO YOU WANT TO CONTINUE REVIEWING BOOKING INFORMATION  ( 1-YES, 0-NO ) :";
                        cin >> count1;
                    } while (count1 != 0);
                    break;

                case 7:
                    break;
                default:
                    cout << "ERROR , INVALID CHOICE." << endl;
                    break;
                }
                system("pause");
                getch();
            } while (choice1 != 7);
            break;
        }
        break;
        case 2:
        {
            int choice2;
            int roomNum1, roomNum2;
            int count2;
            do
            {
                system("CLS");
                cout << "=============	STUDENT MENU	=============" << endl;
                cout << "\t1. DISPLAY ROOM\n\t2. BOOK A ROOM\n\t3. CANCEL ROOM\n\t4. BACK TO MAIN MENU" << endl;
                cout << "CHOICE : ";
                cin >> choice2;

                switch (choice2)
                {
                case 1:
                    r.printRoom();
                    break;
                case 2:
                    count2 = 1;
                    do
                    {
                        cout << "\nENTER THE ROOM NUMBER YOU WANT TO BOOK : ";
                        cin >> roomNum1;

                        bool booking = r.booking(roomNum1);

                        if (booking)
                        {
                            string name, phone, matric, email, in, out;
                            int dayIn, MounthIn, YearIn, dayOut, MounthOut, YearOut;
                            char S;
                            cout << "========  STUDENT INFO ========" << endl;
                            cout << "ENTER YOUR NAME      : ";
                            cin.ignore();
                            getline(cin, name);
                            cout << "ENTER YOUR PHONE NO  : ";
                            getline(cin, phone);
                            cout << "ENTER YOUR IC (xxxxxx-xx-xxxx): ";
                            getline(cin, matric);
                            cout << "ENTER YOUR EMAIL (xxxxxx-@-xxxx.COM): ";
                            getline(cin, email);
                            cout << "DATE IN (YYYYMMDD)   : ";
                            getline(cin, in);
                            cout << "DATE OUT (YYYYMMDD)  : ";
                            getline(cin, out);

                            int days = date(in, out);
                            s.StudentData(name, phone, matric, email, in, out, roomNum1);
                            cout << "\n----------------------------------\n";
                            cout << "\nPLEASE PROCEEED TO BILL AT MANAGEMENT OFFICE\n";
                            cout << "\n----------------------------------\n";

                            RoomNode *tmp = new RoomNode;
                            tmp = r.findRoom(roomNum1);
                            b.Enqueue(roomNum1, tmp->price, matric, name, in, out, email, days);
                        }
                        cout << "DO YOU WANT TO BOOK ANOTHER ROOM( 1-YES, 0-NO ) :";
                        cin >> count2;
                    } while (count2 != 0);
                    break;

                case 3:
                    count2 = 1;

                    do
                    {
                        string matric2;
                        int room_number2 = 0;

                        cout << "\nENTER THE ROOM NUMBER YOU WANT TO CANCEL : ";
                        cin >> room_number2;
                        cout << "ENTER YOUR MATRIC NUMBER TO MAKE CANCELLATION (xxxxxx-xx-xxxx): ";
                        cin.ignore();
                        getline(cin, matric2);

                        bool target = r.findBookedRoom(room_number2);
                        if (target)
                        {
                            bool targetS = s.FindStudent(matric2);
                            if (targetS)
                            {
                                r.cancel(room_number2);
                                s.deleteStudent(matric2, room_number2);
                            }
                            else
                            {
                                cout << "\nRECORD CANNOT BE FOUND\nUNABLE TO MAKE CANCELLATION" << endl;
                            }
                        }
                        else
                        {
                            cout << "RECORD CANNOT BE FOUND\nUNABLE TO MAKE CANCELLATION" << endl;
                        }
                        cout << "DO YOU WANT TO CANCEL OTHER ROOMS( 1-YES, 0-NO ) : ";
                        cin >> count2;
                    } while (count2 != 0);
                    break;

                case 4:
                    break;
                default:
                    cout << "ERROR INVALID CHOICE." << endl;
                    break;
                }
                system("pause");
                getch();
            } while (choice2 != 4);
            break;
        }
        case 3:
            cout << "THANK YOU FOR VISITING UTM HOTEL! SEE U." << endl;
            exit(0);
        default:
            cout << "ERROR INVALID CHOICE." << endl;
            break;
        }
        getch();
    } while (choice != 3);

    return 0;
}