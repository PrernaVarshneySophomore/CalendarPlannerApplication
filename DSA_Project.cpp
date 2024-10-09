#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Function to determine if a year is a leap year
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to get the day of the week for a given date (Zeller's Congruence)
int dayOfWeek(int year, int month, int day) {
    if (month < 3) {
        month += 12;
		year --;
	}
    int k = year % 100;   // Year
    int j = year / 100;   // Century
	return (day + (13 * (month - 2) - 1) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
}

// Function to display a calendar for a specific month and year
void displayCalendar(int year, int month) {
    const char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    const int daysInMonth[] = {31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    int firstDay = dayOfWeek(year, month, 1);
    cout << months[month - 1] << " " << year << "\n";
    cout << "Sun Mon Tue Wed Thu Fri Sat\n";
	
	if(firstDay < 0){
		for (int i = 0; i < 7+firstDay; i++) {
        	cout << "    ";
    	}
	} else {
		for (int i = 0; i < firstDay; i++) {
			cout << "    ";
		}
	}

    for (int day = 1; day <= daysInMonth[month - 1]; day++) {
        cout << setw(3) << day << " ";
        if ((firstDay + day) % 7 == 0) {
            cout << "\n";
        }
    }

    cout << "\n";
}

struct Event {
    string date;
    string title;
    string description;
    Event* next;

    Event(const string& d, const string& t, const string& desc)
        : date(d), title(t), description(desc), next(nullptr) {}
};

class Calendar {
public:
    Calendar() : head(nullptr) {}

    void addEvent(const string& date, const string& title, const string& description) {
        //Adding event at the end of the linked list...
		Event* newEvent = new Event(date, title, description);
        if (!head) {
            head = newEvent;
        } else {
            Event* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newEvent;
        }
    }

    void viewMonthlyEvents(int year, int month) {
	    int daysInMonth[] = {31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		for (int i = 1; i <= daysInMonth[month - 1]; i++){
			string date = to_string(i) + "-" + to_string(month) + "-" + to_string(year);
            Event* current = head;
        	while (current) {
            	if (current->date == date) {
                	cout << current->date << ":  " << current->title << endl;
            	}
            	current = current->next;
        	}
		}
		cout << "-----------------------" << endl;
    }

	void viewEvents(const string& date) {
        Event* current = head;
        bool found = false;

        while (current) {
            if (current->date == date) {
                found = true;
                cout << "Date: " << current->date << endl;
                cout << "Title: " << current->title << endl;
                cout << "Description: " << current->description << endl;
                cout << "-----------------------" << endl;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No events found for " << date << endl;
			cout << "-----------------------" << endl;
        }
    }

    ~Calendar() {
        while (head) {
            Event* temp = head;
            head = head->next;
            delete temp;
        }
    }

private:
    Event* head;
};

struct Task{
	string task;
	struct Task* next;

	Task(const string& t) : task(t), next(nullptr) {}
};

class Date{
public:
	string date;
	Date(string date) : rear(nullptr), front(nullptr) {
		this->date = date;
	}
	
	void enQueue(const string& task) {
		Task* newTask = new Task(task);
		if ((!front) && (!rear)) {
			front = newTask;
			rear = newTask;
		} else {
			Task* current = rear;
			current->next = newTask;
			rear = newTask;
		}
	}
	
	void deQueue() {
		if(!front) {
			cout << "Congratulation!! You have no pending work..." << endl;
		} else {
			Task* temp = front;
			front = front->next;
			cout << "Congratulations on completion of " << temp->task <<endl;
			delete temp;
		}
	}

	void displayTask() {
		Task* current = front;
		int i=1;
		cout << "Date: " <<  date << endl;
		if (!current) {
			cout << "Task not added yet." << endl;
		} else {
			while (current){
				cout << i << ". " << current->task <<endl;
				current = current->next;
				i++;
			}
		}
	}

	~Date() {
		while (front) {
			Task* temp = front;
			front = front->next;
			delete temp;
		}
	}
private:
	Task* front;
	Task* rear;
};

int main() {
    Calendar calendar;

    while (true) {
        cout << "Calendar/Planner Application" << endl;
        cout << "1. View Monthly Calender" << endl;
		cout << "2. Add Event" << endl;
        cout << "3. View Events" << endl;
        cout << "4. View Monthly Events" << endl;
		cout << "5. Create a To-Do List" << endl;
		cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
           case 1:
				{
					int year, month;
					cout << "Enter year (e.g., 2023): ";
					cin >> year;
					cout << "Enter month (1-12): ";
					cin >> month;

					displayCalendar(year, month);
					cout << "-----------------------" << endl;
				}
				break;

			case 2:
                {
                    string date, title, description;
                    cout << "Enter date (DD-MM-YYYY): ";
                    cin >> date;
                    cout << "Enter event title: ";
                    cin.ignore();
                    getline(cin, title);
                    cout << "Enter event description: ";
                    getline(cin, description);

                    calendar.addEvent(date, title, description);
                    cout << "Event added successfully!" << endl;
					cout << "-----------------------" << endl;
                }
                break;

            case 3:
                {
                    string date;
                    cout << "Enter date (DD-MM-YYYY) to view events: ";
                    cin >> date;

                    calendar.viewEvents(date);
                }
                break;
			
			case 4:
				{
					int year, month;
					cout << "Enter year: ";
					cin >> year;
					cout << "Enter month: ";
					cin >> month;

					displayCalendar(year, month);
					cout << "-----------------------" << endl;
					
					calendar.viewMonthlyEvents(year, month);					
				}
				break;
			
			case 5:
			    {
					string date;
					cout << "Enter date (DD-MM-YYYY): ";
					cin >> date;
					Date d1 = Date(date);
					int stay = 1;
					cout << "-----------------------" << endl;
					while (stay) {
				        cout << "       To-Do List" << endl;
        				cout << "       1. Entering Task" << endl;
						cout << "       2. View To-Do List" << endl;
       				    cout << "       3. Updating list" << endl;
       					cout << "       4. Exit" << endl;
						cout << "Enter your choice: ";

						int job;
						cin >> job;

						switch (job) {
							case 1:
								{
					            	string task;
					            	cout << "Enter task: ";
                    				cin.ignore();
                    				getline(cin, task);
									d1.enQueue(task);
									cout << "Task added successfully." << endl;
									cout << "-----------------------" << endl;
								}
								break;
						
							case 2:
								{								
									d1.displayTask();
									cout << "-----------------------" << endl;
								}
								break;

							case 3:
								{
									d1.deQueue();
									cout << "-----------------------" << endl;
								}
								break;

							case 4:
								{
									cout << "Hope so you have completed your tasks." << endl;
									cout << "-----------------------" << endl;
									stay = 0;
								}

							default:
									cout << "Invalid choice. please try again." << endl;
						}
					}
				}
				break; 

            case 6:
				{
				cout << "Thanks For working with:" << endl << "    1.PALAK JAIN" <<endl << "    2.PRERNA VARSHNEY" << endl << "    3.PRIYA KUMARI" << endl; 
                cout << "Exiting the application. Goodbye!" << endl;
				cout << "-----------------------" << endl;
                return 0;
				}
				
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
