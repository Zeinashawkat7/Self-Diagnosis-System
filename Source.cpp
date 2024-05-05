#include<iostream>
#include <conio.h>
#include<string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
char* doctorORpatient;            //a pointer for log in stuff (a doctor or patient)
int* whichdoctorORpatient;          //a pointer for the index of the user (which account of this user)
const int size = 100;
int x = 0;
struct Account
{
	string username;
	string password;
};

struct Disease
{
	string Title;
	int ID;
	string general_info;
	string symptoms[100];
	int no_patients_diagnosed = 0;
}
Diseases[100]
{
	{"Diabetes",1,"Your body does not produce enough insulin, can lead to excess blood sugar levels.",
	{"feeling more thirsty","urinating often","having blurry vision","getting infections easily","fever"},0},
	{"Anemia",2,"Lacking enough healthy red blood cells to carry adequate oxygen to body's tissues.",
	{"Feeling weakness","Irregular heartbeats","dizziness","Pale or yellow skin","fever"},0},
	{"Kidney Stones", 3,"are hard deposits made of minerals and salts that form inside your kidneys",
	{"pain when urinating","red or brown urine", "nausea","vomiting","fever"}, 0},
	{"Common Cold",4,"infection of the nose and throat that is common in winter",
	{"Sneezing","sore throat","coughing","Mucus dripping from nose","stuffy nose"}, 0},
	{"Coronary Artery",5,"Clogging of the arteries, a struggle to send enough blood, oxygen and nutrients to the heart muscle",
	{"chest pain", "shortness of breath", "fatigue", "nausea","shoulder pain"}, 0}
};

struct Patient {
	string Full_name;
	Account acc_patient;
	int age;
	string gender;
	int disease_history[100] = { 0 };
};
vector<Patient> patients;

struct Doctor
{
	string fullname;
	Account account;
	vector<Disease> add_disease;
};
vector <Doctor> doctors;

void menudoctor()
{
	cout << "\n(1) Display diseases";
	cout << "\n(2) View patient with certain disease";
	cout << "\n(3) Edit info";
	cout << "\n(4) Add symptom";
	cout << "\n(5) Add disease";
	cout << "\n(6) Log out\n";
}

void displaydiseases() {
	cout << "The system's diseases are: \n";
	for (int i = 0; i < 100; i++) {
		if (Diseases[i].Title == "\0")
			break;
		cout << endl;
		cout << Diseases[i].Title << endl;
		cout << "ID: " << Diseases[i].ID << endl;
		cout << "Info: " << Diseases[i].general_info << endl;
		cout << "Symptoms: " << endl;
		for (int j = 0; j < 100; j++) {
			if (Diseases[i].symptoms[j] == "\0")
				break;
			cout << Diseases[i].symptoms[j] << endl;
		}
		cout << "No. of Patients diagnosed = " << Diseases[i].no_patients_diagnosed << endl;
	}
}

void display_all_diseases() {
	cout << "The system's diseases are: \n";
	for (int i = 0; i < 100; i++)
	{
		if (Diseases[i].Title == "\0")
			break;
		cout << Diseases[i].Title << endl;
	}
}

string chosen_disease() {
	display_all_diseases();
	cout << "\nPlease Choose a disease: " << endl;
	string disease;
	getline(cin >> ws, disease); // std::ws skips the whitespace, in particular the newline
	return disease;
}

Doctor Edit_Dr_Info() {
	//int* index = whichdoctorORpatient;
	string entered_pass;
	cout << "Enter your old password: ";
	getline(cin >> ws, entered_pass);
	if (entered_pass.compare(doctors[*whichdoctorORpatient].account.password) == 0)
	{
		cout << "Enter your new fullname: ";
		getline(cin >> ws, doctors[*whichdoctorORpatient].fullname);
		cout << "Enter your new username: ";
		getline(cin >> ws, doctors[*whichdoctorORpatient].account.username);
		cout << "Enter your new password: ";
		getline(cin >> ws, doctors[*whichdoctorORpatient].account.password);
		return doctors[*whichdoctorORpatient];
	}
	else
	{
		cout << "You Entered a Wrong Password! \n" << "Please press Y/y if you want to continue \n";
		char cont; cin >> cont;
		if (cont == 'Y' || cont == 'y')
			Edit_Dr_Info();
		return doctors[*whichdoctorORpatient];
	}
}

Disease Adding_Disease() {
	Disease new_disease;
	// Entering disease's data
	cout << "Enter Disease's name: ";
	string new_title;
	getline(cin >> ws, new_title);
	new_disease.Title = new_title;

	int new_ID;
	for (int i = 0; i < 100; i++) {
		if (Diseases[i].ID == 0) {
			new_ID = i + 1;
			break;
		}
	}
	new_disease.ID = new_ID;

	cout << "Enter Disease's info: ";
	string new_general_info;
	getline(cin >> ws, new_general_info);
	new_disease.general_info = new_general_info;

	cout << "Enter Disease's symptoms (please press 0 to end): \n";
	while (true) {
		string symptom;
		getline(cin >> ws, symptom);
		if (symptom == "0")
			break;
		else
		{
			for (int j = 0; j < 100; j++) {
				if (new_disease.symptoms[j] == "\0") {
					new_disease.symptoms[j] = symptom;
					break;
				}
			}
		}
	}

	for (int i = 0; i < 100; i++) {
		if (Diseases[i].Title == "\0")
		{
			Diseases[i] = new_disease;
			doctors[*whichdoctorORpatient].add_disease.push_back(Diseases[i]);
			// Printing Disease's data
			cout << "The new Disease's data are: \n";
			cout << "Name: " << Diseases[i].Title << endl;
			cout << "ID: " << Diseases[i].ID << endl;
			cout << "General info: " << Diseases[i].general_info << endl;
			cout << "Symptoms: " << endl;
			for (int j = 0; j < 100; j++) {
				if (Diseases[i].symptoms[j] == "\0")
					break;
				cout << Diseases[i].symptoms[j] << endl;
			}
			return Diseases[i];
		}
	}
}
bool checking_disease(string disease) {
	for (int i = 0; i < 100; i++) {
		if (Diseases[i].Title == "\0")
			break;
		if (disease == Diseases[i].Title)
			return true;
	}
	return false;
}
void add_symptom(string disease = chosen_disease()) {
	if (checking_disease(disease) == false) {
		cout << "Can't find this disease!\n";
		return;
	}
	bool allowed = false;
	for (int i = 0; i < doctors[*whichdoctorORpatient].add_disease.size(); i++) {
		if (doctors[*whichdoctorORpatient].add_disease[i].Title == disease) {
			allowed = true;
			break;
		}
	}
	if (allowed)
	{
		for (int i = 0; i < 100; i++)
		{
			if (Diseases[i].Title == "\0")
				break;
			if (disease == Diseases[i].Title)
			{
				cout << "Disease is: " << Diseases[i].Title << endl;
				cout << "Enter Disease's added symptom: ";
				string new_symptom;
				getline(cin >> ws, new_symptom);
				for (int j = 0; j < 100; j++) {
					if (Diseases[i].symptoms[j] == "\0")
					{
						Diseases[i].symptoms[j] = new_symptom;
						break;
					}
				}
				cout << "\nThe " << disease << "'s new symptoms are: \n";
				for (int j = 0; j < 100; j++) {
					if (Diseases[i].symptoms[j] == "\0")
						break;
					cout << Diseases[i].symptoms[j] << endl;
				}
				return;
			}
		}
	}
	else if (doctors[*whichdoctorORpatient].add_disease.size() == 0)
		cout << "You are not allowed to add a symptom to any disease!\n";

	else cout << "You are not allowed to add a symptom to this disease!\n";
}

void view_patient_with_certian_disease(string disease = chosen_disease())
{
	if (checking_disease(disease) == false) {
		cout << "Can't find this disease!\n";
		return;
	}

	bool check = false;
	for (int i = 0; i < 100; i++) {
		if (Diseases[i].Title == "\0")
			break;
		if (disease == Diseases[i].Title)
		{
			for (int j = 0; j < patients.size(); j++)
			{
				for (int k = 0; k < 100; k++)
				{
					if (patients[j].disease_history[k] == 0)
						break;
					if (patients[j].disease_history[k] == Diseases[i].ID) {
						if (check == false) {
							cout << "The patients who are diagnosed with " << Diseases[i].Title << " disease are: \n";
							cout << patients[j].Full_name << endl;
							check = true;
						}
						else cout << patients[j].Full_name << endl;
					}
				}
			}
		}
	}

	if (check == false)
		cout << "There are no patients diagnosed with " << disease << " disease!";
}

void menupatient() {
	cout << "\n(1) Find out your disease based on your symptoms ";
	cout << "\n(2) Display symptoms for a certain disease";
	cout << "\n(3) View diagnosis history";
	cout << "\n(4) Clear diagnosis history";
	cout << "\n(5) Log out\n";
}

float inputSymptoms_countsimilar(string inputsymptoms[], float countsimilar[])
{
	float countersymptoms = 0;
	int i = 0;
	cout << "Enter your symptoms (PLease press 0 to end): " << endl;
	for (i = 0; i < 20; i++)
	{
		getline(cin >> ws, inputsymptoms[i]);
		if (inputsymptoms[i] == "0")
			break;
		countersymptoms++;
	}
	for (int x = 0; x < 100; x++)
	{
		if (Diseases[x].Title == "\0")
			break;
		for (int j = 0; j < 100; j++)
		{
			if (Diseases[x].symptoms[j] == "\0")
				break;
			for (int y = 0; y < countersymptoms; y++)
			{
				if (inputsymptoms[y] == (Diseases[x].symptoms[j]))
					countsimilar[x]++;
			}
		}
	}
	return countersymptoms;
}

bool check_for_60(float countsimilar[], float countersymptoms)
{
	int i = 0, index;
	bool check_for_60_percent = false;
	float maximum = 0;
	for (i = 0; i < 100; i++)
	{
		if (Diseases[i].Title == "\0")
			break;
		if (maximum < float(countsimilar[i] / countersymptoms) && float(countsimilar[i] / countersymptoms) >= 0.6)
		{
			maximum = float(countsimilar[i] / countersymptoms);
			check_for_60_percent = true;
			index = i;
		}
	}
	if (check_for_60_percent == true) {
		cout << "You have been diagnosed with: " << Diseases[index].Title << endl;
		cout << Diseases[index].Title << "'s info is: " << Diseases[index].general_info << endl;
		Diseases[index].no_patients_diagnosed++;
		for (int n = 0; n < 100; n++)
		{
			if (patients[*whichdoctorORpatient].disease_history[n] == 0)
			{
				patients[*whichdoctorORpatient].disease_history[n] = Diseases[index].ID;
				break;
			}
		}
	}
	return check_for_60_percent;
}

void Display(float max, bool check_for_60_percent, int index)
{
	if (max != 0 && check_for_60_percent == false)
	{
		cout << "NO EXACT MATCH FOUND!" << endl;
		cout << "The closest disease that matches the symptoms is: " << endl;
		cout << Diseases[index].Title << endl;
		cout << Diseases[index].Title << "'s info is: " << Diseases[index].general_info << endl;
		cout << Diseases[index].Title << " match " << max << " % of your symptoms" << endl;
		cout << endl;
	}
	else if (max == 0 && check_for_60_percent == false)
		cout << "NO MATCH FOUND!" << endl;
}

void find_disease()
{
	int i = 0;
	string inputsymptoms[20];
	float countsimilar[100] = { 0 };
	float countersymptoms = inputSymptoms_countsimilar(inputsymptoms, countsimilar);
	int index = 0;
	bool check_for_60_percent = check_for_60(countsimilar, countersymptoms);
	float max = 0;
	for (i = 0; i < 100; i++)
	{
		if (Diseases[i].Title == "\0")
			break;
		if (max < float((countsimilar[i] / countersymptoms) * 100) && check_for_60_percent == false)
		{
			max = ((countsimilar[i] / countersymptoms) * 100);
			index = i;
		}
	}
	Display(max, check_for_60_percent, index);
}

void display_symptoms(string disease = chosen_disease())                        // el user bey5tar disease w e7na netala3 el symptoms beta3to
{
	if (checking_disease(disease) == false) {
		cout << "Can't find this disease!\n";
		return;
	}
	for (int j = 0; j < 100; j++) {
		if (Diseases[j].Title == "\0")
			break;
		if (disease == Diseases[j].Title)
		{
			cout << "Disease's symptoms are: \n";
			for (int i = 0; i < 100; i++) {
				if (Diseases[j].symptoms[i] == "\0")
					break;
				else cout << Diseases[j].symptoms[i] << endl;
			}
		}
	}
}

void view_diagnosis_history()
{
	bool checked = false;
	int i;
	for (i = 0; i < 100; i++)
	{
		if (patients[*whichdoctorORpatient].disease_history[i] != 0)
		{
			if (checked == false) {
				cout << "You are diagnosed with these diseases: \n";
				checked = true;
			}
			cout << "Name: " << Diseases[patients[*whichdoctorORpatient].disease_history[i] - 1].Title << "\t";
			cout << "ID: " << Diseases[patients[*whichdoctorORpatient].disease_history[i] - 1].ID << endl;
		}
	}
	if (checked == false) {
		cout << "There is no diagnosis history! \n";
	}
}

void clear_history()
{
	for (int i = 0; i < 100; i++)
		patients[*whichdoctorORpatient].disease_history[i] = 0;
	cout << "Your diagnosis history was deleted successfully\n";
}

void LOGIN()
{
	doctors.push_back({ "Menna Thabet", "mennathabet", "2022170844", {Diseases[0], Diseases[1]} });
	doctors.push_back({ "Zeina Shawkat", "zeinashawkat", "2022170818" });
	doctors.push_back({ "Shaden Khalifa","shadenkhalifa","2022170820" });
	patients.push_back({ "Clara Akmal","claraakmal", "2022170915",19,"female",Diseases[0].ID, Diseases[1].ID,Diseases[2].ID });
	patients.push_back({ "Amani Sattam","amanisattam", "2022170875",19,"female",Diseases[0].ID, Diseases[1].ID, Diseases[3].ID });
	patients.push_back({ "Raghad Rafat","raghadrafat", "2022170813",19,"female" });
	Diseases[0].no_patients_diagnosed = 2; Diseases[1].no_patients_diagnosed = 2; Diseases[2].no_patients_diagnosed = 1;  Diseases[3].no_patients_diagnosed = 1;
	bool LogInSuccesfully = false;
	string username;
	char type = '\0';
	int d, p;
	char c;
	cout << "\t\t\tLog In\n";
	do {
		cout << "Enter Username : ";
		getline(cin >> ws, username);

		for (d = 0, p = 0; d < doctors.size(), p < patients.size(); d++, p++)           //loop for comparing the username if it exists
		{
			if (username.compare(doctors[d].account.username) == 0)
			{
				type = 'd';
				whichdoctorORpatient = &d;           //the user index to modify his functions based on which account we are logging in with
				break;
			}
			else if (username.compare(patients[p].acc_patient.username) == 0)
			{
				type = 'p';
				whichdoctorORpatient = &p;
				break;
			}
		}
		if ((type == 'p') || (type == 'd'))
			break;
		else
			cout << "Invalid User(Not Found)\n";
	} while (true);

	if (type == 'd')
	{
		while (true)
		{
			std::cout << "Enter Password: ";
			c = '\0';
			string password;
			while ((c = _getch()) != '\r') {             //for hiding password
				if (c == '\b')
				{
					cout << '\b';
					password.pop_back();
					continue;
				}
				cout << '*';
				password += c;
			}
			cout << endl;
			if (password.compare(doctors[d].account.password) == 0)      //comparing the password with the user account password
			{
				LogInSuccesfully = true;
				doctorORpatient = &type;                      //the pointer to point to the type doctor or patient
				break;
			}
			else
				cout << "\nTry Again\n";
		}
	}
	else if (type == 'p')
	{
		while (true)
		{
			cout << "Enter Password: ";
			c = '\0';
			string password;
			while ((c = _getch()) != '\r') {
				if (c == '\b')
				{
					cout << '\b';
					password.pop_back();
					continue;
				}
				cout << '*';
				password += c;
			}
			cout << endl;
			if (password.compare(patients[p].acc_patient.password) == 0)
			{
				LogInSuccesfully = true;
				doctorORpatient = &type;
				break;
			}
			else
				cout << "\nTry Again\n";
		}
	}
}

void REGISTER()
{
	bool RegisteredSuccesfully = false;
	string username;
	string fullname;
	string password;
	int age;
	string gender;
	Doctor doctor;
	Patient patient;
	cout << "\t\t\tRegister\n";
	cout << "Enter Username : ";
	getline(cin >> ws, username);
	cout << "Enter fullname: ";
	getline(cin >> ws, fullname);
	cout << "Enter Password: ";
	char c, d;
	string ConfirmedPassword;

	while ((c = _getch()) != '\r') {
		if (c == '\b')
		{
			cout << '\b';
			password.pop_back();
			continue;
		}
		cout << c;
		password += c;
	}

	do {
		d = '\0';
		ConfirmedPassword = "\0";
		cout << "\nConfirm Password: ";    //password confirming

		while ((d = _getch()) != '\r')
		{
			if (d == '\b')
			{
				cout << '\b';
				ConfirmedPassword.pop_back();
				continue;
			}
			cout << d;
			ConfirmedPassword += d;
		}

		if (ConfirmedPassword.compare(password) == 0)            //comparing if it matches
		{
			RegisteredSuccesfully = true; break;
		}
		else
		{
			cout << "\nNO MATCH!";
		}
	} while (!RegisteredSuccesfully);        //it ends when the confirmed password matches the entered password

	char choice;
	do {
		cout << "\nDoctor (d) Or Patient (p): ";          //determining whether doctor or patient
		cin >> choice;
		switch (choice)
		{
		case 'd':
		case 'D':
		{
			doctorORpatient = &choice;      //(pointer) to record the choice and use it in main later
			doctor.fullname = fullname;
			doctor.account.username = username;
			doctor.account.password = password;
			doctors.push_back(doctor);
			break;
		}
		case 'p':
		case 'P':
		{
			cout << "Enter age: ";
			cin >> age;
			cout << "Enter gender: ";
			cin >> gender;
			doctorORpatient = &choice;
			patient.Full_name = fullname;
			patient.acc_patient.username = username;
			patient.acc_patient.password = password;
			patient.age = age;
			patient.gender = gender;
			patients.push_back(patient);
			break;
		}
		default:
		{
			cout << "Invalid!\n";
		}
		}

		if ((choice == 'd') || (choice == 'D') || (choice == 'p') || (choice == 'P'))
			break;
	} while (true);  //loop if the user entered another character
}

void system_entry()
{
	char choice;
	do {
		cout << "\tLog in(L) OR Register(R)\n";
		cin >> choice;
		switch (choice)
		{
		case 'L':
		case'l':
		{
			LOGIN();
			break;
		}
		case 'R':
		case 'r':
		{
			REGISTER();
			cout << "\nYou have registered successfully\n";
			cout << "PLease Log in to make actions\n";
			LOGIN();
			break;
		}
		default:
		{
			cout << "Enter a valid operation!\n";
		}
		}
		if ((choice == 'L') || (choice == 'l') || (choice == 'R') || (choice == 'r'))
			break;
	} while (true);
}

int main()
{
	do {
		system_entry();
		int answer;
		if ((*doctorORpatient == 'd') || (*doctorORpatient == 'D'))           //the doctor functions
		{
			do {
				menudoctor();
				cin >> answer;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "wrong input\n";
					cin >> answer;
					if (!cin.fail())
						break;
				}
				switch (answer)
				{
				case 1:displaydiseases(); break;
				case 2:view_patient_with_certian_disease(); break;
				case 3:Edit_Dr_Info(); break;
				case 4:add_symptom(); break;
				case 5:Adding_Disease(); break;
				case 6: break;
				default:cout << "Invalid\n";
				}
				if (answer == 6)
					break;
			} while (true);
		}
		else if ((*doctorORpatient == 'p') || (*doctorORpatient == 'P'))  //the patient functions
		{
			do {
				menupatient();
				cin >> answer;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "wrong input\n";
					cin >> answer;
					if (!cin.fail())
						break;
				}
				switch (answer)
				{
				case 1: find_disease(); break;
				case 2: display_symptoms(); break;
				case 3: view_diagnosis_history(); break;
				case 4: clear_history(); break;
				case 5: break;
				default:
					cout << "Invalid\n";
				}
				if (answer == 5)
					break;
			} while (true);

		}
	} while (true);


	return 0;
}