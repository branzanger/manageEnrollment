//Brandon Zhang
//Manage course and activity registration
//
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <filesystem>


using namespace std;


class Course {
private:
	string name;
	int units;
public:
	Course() : name(""), units(0) {};
	Course(string iName, int iUnits) : name(iName), units(iUnits) {};
	int getUnits() {
		return units;
	}
	string getName() {
		return name;
	}
	virtual string toString() {
		stringstream output;
		output << "Course(" << name << ") UNITS(" << units << ")";
		return output.str();
	}
	virtual string printDetail() {
		stringstream output;
		output << right;
		output << "Class: " << name << setw(20) << "Units: " << units << endl;
		return output.str();
	}
};

class Activity : public Course {
private:
	string location;

public:
	Activity() : Course(), location("") {};
	Activity(string iName, int iUnits, string iLocation) : Course(iName, iUnits), location(iLocation) {};

	string getLocation() {
		return location;
	}
	string toString() {
		stringstream output;
		output << "Activity (" + Course::toString() + " Location (" << location << ")";
		return output.str();
	}
	string printDetail() {
		stringstream output;
		output << right;
		output << "Activity:" + Course::getName() << setw(20) << " Units: " << Course::getUnits() << " Location:" << location << endl;
		return output.str();
	}
};

void goMenu(vector<Course*>&);
void enrollCourses(vector<Course*>&);
void addActivity(vector<Course*>&);
void showDetail(vector<Course*>);
void searchCourses(vector<Course*>);
void showUnitsGT(vector<Course*>);
void showHelp();
const int MAX_NUM_OF_CLASSES = 100;
const double FEE_PER_UNITS = 31.0;


enum class MenuCode {
	eEnroll,
	eAddActivity,
	eDetail,
	eSearch,
	eUnits,
	eHelp,
	eExit,
	noCode
};
MenuCode getMenuCode(string menu) {
	MenuCode code = MenuCode :: noCode;
	if (menu == "enroll") {
		code = MenuCode::eEnroll;
	}
	if (menu == "addactivity") {
		code = MenuCode::eAddActivity;
	}
	else if (menu == "detail") {
		code = MenuCode::eDetail;
	}
	else if (menu == "search") {
		code = MenuCode::eSearch;
	}
	else if (menu == "units>=") {
		code = MenuCode::eUnits;
	}
	else if (menu == "help") {
		code = MenuCode::eHelp;
	}
	else if (menu == "exit") {
		code = MenuCode::eExit;
	}
	return code;
}
void goMenu(vector<Course*>& caList) {
	bool exit = false;
	while (!exit) {
		cout << "Please enter a command:   " << flush;
		string command;
		getline(cin, command);
		switch (getMenuCode(command)) {
		case MenuCode::eEnroll:
			enrollCourses(caList);
			break;
		case MenuCode::eAddActivity:
			addActivity(caList);
			break;
		case MenuCode::eDetail:
			showDetail(caList);
			break;
		case MenuCode::eSearch:
			searchCourses(caList);
			break;
		case MenuCode::eUnits:
			showUnitsGT(caList);
			break;
		case MenuCode::eHelp:
			showHelp();
			break;
		case MenuCode::eExit:
			exit = true;
			break;
		default:
			cout << "Invalid command. Please entre \"help\" for the list of valid commands" << endl;
		}
		if (caList.size() >= MAX_NUM_OF_CLASSES) {
			cout << "Number of courses exceeds maximal allowance. Exit" <<
				endl;
			exit = true;
		}
	}
	cout << "Thank You." << endl;
	return;
}

void enrollCourses(vector<Course*>& caList) {
	cout << "Please enter the class name : " << flush;
	string className;
	getline(cin, className);
	int units;
	cout << "Please enter the number of units for this class: " << flush;
	cin >> units;
	cin.ignore();
	Course *ptr = new Course(className, units);
	caList.push_back(ptr);
	cout << "You are enrolled." << endl;
	return;
}

void addActivity(vector<Course*>& caList) {
	cout << "Please enter the activity name : " << flush;
	string className;
	getline(cin, className);
	int units;
	cout << "Please enter the number of units for this class: " << flush;
	cin >> units;
	cin.ignore();
	cout << "Please enter the activity location : " << flush;
	string location;
	getline(cin, location);
	Activity *ptr = new Activity(className, units, location);
	caList.push_back(ptr);
	cout << "You are enrolled." << endl;
	return;
}

void showDetail(vector<Course*> caList) {
	int totalUnits = 0;
	cout << "======================================" << endl;
	for (int i = 0; i < caList.size(); i++) {
		cout << caList[i]->printDetail();
		totalUnits += caList[i]->getUnits();
	}
	cout << "Total Classes: " << caList.size() << endl;
	cout << "Total units:   " << totalUnits << endl;
	cout << fixed << setprecision(2) << "Total fee:    $" << totalUnits *
		FEE_PER_UNITS << endl;
	cout << "======================================" << endl;
	return;
}
void searchCourses(vector<Course*> caList) {
	cout << "Please enter search word: " << flush;
	string filter;
	getline(cin, filter);
	bool search = false;
	for (int i = 0; i < caList.size(); i++) {
		if (caList[i]->getName().find(filter) != std::string::npos) {
			if (search == false) {
				cout << "======================================" << endl;
			}
			cout << caList[i]->printDetail();
			search = true;
		}
	}
	if (!search) {
		cout << "Search did not match any class." << endl;
	}
	else {
		cout << "======================================" << endl;
	}
	return;
}
void showUnitsGT(vector<Course*> caList) {
	cout << "Please enter the search units: " << flush;
	int units;
	cin >> units;
	cin.ignore();
	bool search = false;
	for (int i = 0; i < caList.size(); i++) {
		if (caList[i]->getUnits() >= units) {
			if (search == false) {
				cout << "======================================" << endl;
			}
			search = true;
			cout << caList[i]->printDetail() << endl;
		}
	}
	if (!search) {
		cout << "Search did not match any class." << flush;
	}
	else {
		cout << "======================================" << endl;
	}
	return;
}
void showHelp() {
	cout << "List of available commands:" << endl;
	cout << "enroll  - to enroll in a class" << endl;
	cout << "addactivity  - to add an activity" << endl;
	cout << "detail  - to list the enrollment in details" << endl;
	cout << "search  - to search for a word in the class list" << endl;
	cout << "units>= - to search for classes with units greater and equal" <<
		endl;
	cout << "help    - to display list of valid commands" << endl;
	cout << "exit    - to exit the program" << endl;
	return;
}

int main(int argc, char* argv[]) {
	vector<Course*> courseAndActivityList;

	//cout << argv[0];
	//cin.get();
	//cout << "directory: " << cwd.string() << endl;
	if (argc > 1) {
		string fileName = argv[1];
		ifstream fin(fileName);
		if (fin.is_open() == false) {
			cout << "Invalid file name or directory." << endl;
		}
		else {
			cout << "Input courses and activities from " << fileName << endl;
			int units;
			string input, tmp;
			while (fin.eof() == false) {
				fin >> units;
				//cout << "units:" << units << endl;
				getline(fin, input);
				//cout << "input:" << input << endl;
				stringstream ss(input);

				vector<string> inputs;
				while (getline(ss, tmp, '|')) {
					inputs.push_back(tmp);
				}
				//cout << "inputs: " << inputs.size() << endl;
				if (inputs.size() == 1) {
					Course* ptr = new Course();
					*ptr = Course(inputs[0], units);
					courseAndActivityList.push_back(ptr);
					//cout << ptr->printDetail();

				}
				else if (inputs.size() == 2) {
					Activity* ptr = new Activity();
					*ptr = Activity(inputs[0], units, inputs[1]);
					courseAndActivityList.push_back(ptr);
					//cout << ptr->printDetail();
				}
			}

			//for (int i = 0; i < courseAndActivityList.size(); i++) {
			//	cout << courseAndActivityList[i]->printDetail();	
			//}
		}
	}
	goMenu(courseAndActivityList);
}