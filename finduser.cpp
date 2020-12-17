// findUser2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
struct Person {
    string name;
    string sex;
    vector<string> favor;
};

void constructorPerson(Person& person, string name, string sex, vector<string> favor);
void readFile(vector<string> &data, string file);
Person getPerson(string str);
void printPerson(Person person);
vector<string> sameFavor(Person p1, Person p2);
vector<string> splitStr(string str);
void printListPerson(vector<Person> people);
void inputPerson(Person& p);
void findPerson(vector<Person> people, Person p);
void menu(int& key);
string getString(Person p);
void writeFile(string data, string file);
void findName(vector<Person> p);
int main()
{
	string file = "input.txt"; //tên file
	vector<string> data; //lưu dữ liệu từ file
	vector<Person> people; // lưu danh sách person
	
	//lưu thông tin người dùng
	Person p;
	readFile(data, file); // lấy file ra data
				//chuyển data thành danh sách Person
	for (int i = 0; i < data.size(); i++) {
		if (data[i] == "")
			break;
		people.push_back(getPerson(data[i]));
	}
	int option;
	while (true) {
		menu(option);
		if (option == 0)
			break;
		switch (option) {
			case 1:
				data.clear();
				people.clear();
				readFile(data, file); // lấy file ra data
				//chuyển data thành danh sách Person
				for (int i = 0; i < data.size(); i++) {
					if (data[i] == "")
						break;
					people.push_back(getPerson(data[i]));
				}
				printListPerson(people);
				break;
			case 2:
				inputPerson(p);
				break;
			case 3:
				findPerson(people, p);
				break;
			case 4:
				writeFile(getString(p), file);
				break;
			case 5:
				findName(people);
				break;
			default:
				cout << "Nhap khong dung lua chon, moi nhap lai!";
					break;

		}
	}

}
//menu
void menu(int& key) {
		cout << "CHUONG TRINH LAM MAI MOI C/C++\n";
		cout << "*************************MENU********************************\n";
		cout << "**  1.  Hien thi danh sach nguoi ghep doi.                 **\n";
		cout << "**  2.  Nhap thong tin nguoi ghep doi.                     **\n";
		cout << "**  3.  Tim nguoi co chung so thich (2 so thich tro len).  **\n";
		cout << "**  4.  Ghi danh sach nguoi ghep doi vao file.             **\n";
		cout << "**  5.  Tim kiem ten nguoi trong danh sach.                **\n";
		cout << "**  0. Thoat                                               **\n";
		cout << "*************************************************************\n";
		cout << "Nhap tuy chon: ";
		cin >> key;
}

//input person
void inputPerson(Person& p) {
	cout << "nhap vao thong tin: \n";
	
	cout << "ho ten: "; 
	cin.ignore();
	getline(cin, p.name);
	cout << "gioi tinh: "; 
	getline(cin,p.sex);
	cout << "so thich: (nhap so luong): ";
	int k; cin >> k;
	cin.ignore();
	for (int i = 0; i < k; i++) {
		string st;
		cout << "so thich " << i + 1 << ": ";
		
		getline(cin, st); 
		p.favor.push_back(st);		
	}
}
//đọc file
void readFile(vector<string>& data, string file) {
	fstream f;
	f.open(file, ios::in);
	string line;
	while (!f.eof())          
	{
		getline(f, line); 
		data.push_back(line);
	}
	f.close();
}
//lấy thông tin từ dữ liệu lấy được trong file
Person getPerson(string str) {
	Person result;
	vector<string> split = splitStr(str);
	string name = split.at(0);
	string sex = split.at(1);
	vector<string> favor;
	int j = 0;
	for (int i = 2; i < split.size(); i++)
	{
		favor.push_back(split.at(i));
	}
	constructorPerson(result,name, sex, favor);
	return result;
}
//tách các thông tin
vector<string> splitStr(string str)
{
	vector<string> result;
	string temp = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != ',' && i!= str.length()-1)
		{
			 temp+= str[i];
		}
		else
			if (i == str.length() - 1)
			{
				temp += str[i];
				result.push_back(temp);
				break;
			}
			else
		{
			i += 1;
			result.push_back(temp);
			temp = "";
		}
	}
	return result;
}
//khởi tạo 1 cấu trúc person
void constructorPerson(Person& person, string name, string sex, vector<string> favor) {
	person.name = name;
	person.sex = sex;
	person.favor = favor;
}
//xuất ra 1 cấu trúc Person
void printPerson(Person person) {
	cout << "Ho ten: " << person.name << endl
		<< "Gioi tinh: " << person.sex << endl
		<< "So thich: ";
	for (int i = 0; i < person.favor.size(); i++) {
		cout << person.favor.at(i) << ", ";
	}
	cout << endl;
}
//xuất ra list trong file
void printListPerson(vector<Person> people) {
	cout << "DANH SACH GHEP DOI \n";
		cout << setw(5) << "STT|"     <<setw(4)<< "Ho ten"          <<setw(20) << "|"<<"Gioi tinh"     << setw(1) << "|"<<setw(5)<<"So thich\n";
		cout << "--------------------------------------------------------------\n";
	for (int i = 0; i < people.size(); i++) {
		cout << setw(4) << i + 1<<"|" <<setw(4)<< people.at(i).name <<setw(26- people.at(i).name.length()) << "|"<<people.at(i).sex <<setw(10 - people.at(i).sex.length())  << "|"<<setw(5);
		for (int j = 0; j < people.at(i).favor.size(); j++) {
			cout << people.at(i).favor.at(j);
			if (j != people.at(i).favor.size() - 1)
				cout << ", ";
			else
				cout << ".";
		}
		cout << endl;
	}
}
//lấy ra list sở thích chung của p1 so với p2
vector<string> sameFavor(Person p1, Person p2) {
	vector<string> result;
	for (int i = 0; i < p1.favor.size(); i++)
	{
		for (int j = 0; j < p2.favor.size(); j++) {
			if (p1.favor.at(i) == p2.favor.at(j) && p1.sex != p2.sex) {
				result.push_back(p1.favor.at(i));
			}
		}
	}
	return result;
}
void findPerson(vector<Person> people, Person p) {
	int max = 0;
	int index = -1;
	
	for (int i = 0; i < people.size(); i++) {
		int size = sameFavor(people.at(i), p).size();
		if (max < size) {
			max = size;
			index = i;
		}
	}
	if (max >= 2)
	{
		cout << "Nguoi phu hop voi ban: \n";
		printPerson(people[index]);
		cout << endl;
	}
	else
	{
		cout << "Rat tiec! Khong co nguoi phu hop! \n";
	}
		
}
//chuyen thong tin person sang chuoi
string getString(Person p) {
	string result = "\n";
	result += p.name;
	result += ", ";
	result += p.sex;
	result += ", ";
	for (int i = 0; i < p.favor.size(); i++) {
		result += p.favor.at(i);
		if (i != p.favor.size() - 1)
			result += ", ";
	}
	return result;
}
//ghi thong tin vao file
void writeFile(string data, string file) {
	ofstream f;
	f.open(file, ios::out | ios::app);
	f << data;
	f.close();
}
void findName(vector<Person> p) {
	bool isFind = false;
	string name;
	cout << "Nhap ten nguoi can tim: ";
	cin.ignore();
	getline(cin,name);
	for (int i = 0; i < p.size(); i++)
	{
		if (p[i].name == name)
		{
			cout << "Thong tin tim duoc: \n";
			printPerson(p[i]);
			isFind = true;
			break;
		}
	}
	if (!isFind) {
		cout << "Khong ton tai nguoi can tim trong danh sach! \n";
	}
}

