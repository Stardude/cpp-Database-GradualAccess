#include "StudentDatabase.h"

void StudentDatabase::CreateDatabase()
{
	char p;
	system("cls");
	cout << "\n�� �������, �� ������ �������� ���� ���� �����? ����� ���� ����� ���� �������...";
	cout << "\n\n (1 - ���, 0 - Ͳ) -> "; cin >> p;
	if (p == '1')
	{
		database.open("database", ios_base::out);
		database.clear();
		database.close();
	}
}

void StudentDatabase::Insert()
{
	system("cls");
	cout << "���� �����, ������ ���������� ��� ������ ��������...";
	cout << "\nID -> "; cin >> student.id;
	if (Exist(student.id))
	{
		cout << "\n������� � ����� ID ��� ����...\n\n";
		system("pause");
		return;
	}
	cout << "\n������� -> "; cin >> student.surname;
	cout << "��\'� -> "; cin >> student.name;
	cout << "��-������� -> "; cin >> student.father;
	cout << "\n���� ���������� (��.��.����) -> "; cin >> student.birthday;
	getchar();
	cout << "������ -> "; gets_s(student.address);
	cout << "������� -> "; cin >> student.telephone;
	cout << "E-mail -> "; cin >> student.email;
	cout << "\n����� -> "; cin >> student.group;
	cout << "\n�� �� ��/���� ��������? (1 - ���, 0 - Ͳ) -> "; cin >> student.hasScolarship;
	student.operation = 1;

	char choice;
	cout << "\n������ ����� �������� �����:"
		<< "\n1.������ � ���� �����"
		<< "\n2.������ � ���� ������� �������"
		<< "\n\n -> ";
	cin >> choice;
	if (choice == '1')
		InsertToDatabase();
	else if (choice == '2')
		InsertToHandler();
}

void StudentDatabase::Edit()
{
	system("cls");
	cout << "������ ID ��������, ��� ��� ����� �� ������ ����������...";
	cout << "\n\nID -> "; cin >> student.id;
	if (!Exist(student.id))
	{
		cout << "\n�������� � ����� ID � ��� ����� �� ��������...\n\n";
		system("pause");
		return;
	}
	cout << "\n���� �����, ������ ���� ���������� ��� ��������...";
	cout << "\n\n������� -> "; cin >> student.surname;
	cout << "��\'� -> "; cin >> student.name;
	cout << "��-������� -> "; cin >> student.father;
	cout << "\n���� ���������� (��.��.����) -> "; cin >> student.birthday;
	getchar();
	cout << "������ -> "; gets_s(student.address);
	cout << "������� -> "; cin >> student.telephone;
	cout << "E-mail -> "; cin >> student.email;
	cout << "\n����� -> "; cin >> student.group;
	cout << "\n�� �� ��/���� ��������? (1 - ���, 0 - Ͳ) -> "; cin >> student.hasScolarship;
	student.operation = 2;

	char choice;
	cout << "\n������ ����� �������� ���:"
		<< "\n1.���������� � ��� �����"
		<< "\n2.������ � ���� ������� �������"
		<< "\n\n -> ";
	cin >> choice;
	if (choice == '1')
		EditInDatabase();
	else if (choice == '2')
		InsertToHandler();
}

void StudentDatabase::Delete()
{
	system("cls");
	cout << "������ ID ��������, ��� ��� ����� �� ������ ��������...";
	cout << "\n\nID -> "; cin >> student.id;
	if (!Exist(student.id))
	{
		cout << "\n�������� � ����� ID � ��� ����� �� ��������...\n\n";
		system("pause");
		return;
	}
	student.operation = 3;

	char choice;
	cout << "\n������ ����� ��������� �����:"
		<< "\n1.�������� � ���� �����"
		<< "\n2.������ � ���� ������� �������"
		<< "\n\n -> ";
	cin >> choice;
	if (choice == '1')
		DeleteFromDatabase();
	else if (choice == '2')
		InsertToHandler();
}

void StudentDatabase::InsertToHandler()
{
	database.open("handler", ios_base::in);
	if (!database)
	{
		database.open("handler", ios_base::out);
		database.write((char*)&student, sizeof(student));
		database.close();
		return;
	}
	tmp.open("tmp", ios_base::out);
	Student temp_stud;
	bool p = false;
	database.read((char*)&temp_stud, sizeof(temp_stud));
	while (!database.eof())
	{
		if (temp_stud.id <= student.id)
			tmp.write((char*)&temp_stud, sizeof(temp_stud));
		else
		{
			p = true;
			tmp.write((char*)&student, sizeof(student));
			tmp.write((char*)&temp_stud, sizeof(temp_stud));
			database.read((char*)&temp_stud, sizeof(temp_stud));
			while (!database.eof())
			{
				tmp.write((char*)&temp_stud, sizeof(temp_stud));
				database.read((char*)&temp_stud, sizeof(temp_stud));
			}
			break;
		}
		database.read((char*)&temp_stud, sizeof(temp_stud));
	}
	if (!p) tmp.write((char*)&student, sizeof(student));
	database.close();
	tmp.close();
	system("del handler");
	system("rename tmp handler");
}

void StudentDatabase::InsertToDatabase()
{
	database.open("database", ios_base::in);
	tmp.open("tmp", ios_base::out);
	Student temp_stud;
	bool p = false;
	database.read((char*)&temp_stud, sizeof(temp_stud));
	if (database.eof())
		tmp.write((char*)&student, sizeof(student));
	else
	{
		while (!database.eof())
		{
			if (temp_stud.id < student.id)
				tmp.write((char*)&temp_stud, sizeof(temp_stud));
			else
			{
				p = true;
				tmp.write((char*)&student, sizeof(student));
				tmp.write((char*)&temp_stud, sizeof(temp_stud));
				database.read((char*)&temp_stud, sizeof(temp_stud));
				while (!database.eof())
				{
					tmp.write((char*)&temp_stud, sizeof(temp_stud));
					database.read((char*)&temp_stud, sizeof(temp_stud));
				}
				break;
			}
			database.read((char*)&temp_stud, sizeof(temp_stud));
		}
		if (!p) tmp.write((char*)&student, sizeof(student));
	}
	database.close();
	tmp.close();
	system("del database");
	system("rename tmp database");
}

void StudentDatabase::EditInDatabase()
{
	Student temp_stud;
	database.open("database", ios_base::in);
	tmp.open("tmp", ios_base::out);
	database.read((char*)&temp_stud, sizeof(temp_stud));
	while (!database.eof())
	{
		if (temp_stud.id == student.id)
		{
			tmp.write((char*)&student, sizeof(student));
			database.read((char*)&student, sizeof(student));
			while (!database.eof())
			{
				tmp.write((char*)&student, sizeof(student));
				database.read((char*)&student, sizeof(student));
			}
			break;
		}
		tmp.write((char*)&temp_stud, sizeof(temp_stud));
		database.read((char*)&temp_stud, sizeof(temp_stud));
	}
	database.close();
	tmp.close();
	system("del database");
	system("rename tmp database");
}

void StudentDatabase::DeleteFromDatabase()
{
	Student temp_stud;
	database.open("database", ios_base::in);
	tmp.open("tmp", ios_base::out);
	database.read((char*)&temp_stud, sizeof(temp_stud));
	while (!database.eof())
	{
		if (temp_stud.id != student.id)
		{
			tmp.write((char*)&temp_stud, sizeof(temp_stud));
		}
		database.read((char*)&temp_stud, sizeof(temp_stud));
	}
	database.close();
	tmp.close();
	system("del database");
	system("rename tmp database");
}

void StudentDatabase::Search()
{
	system("cls");
	short choice;
	cout << "\n ������ ����, �� ����� �� ������ ���������� �����...\n";
	cout << "\n1.ID\t\t\t6.������"
		<< "\n2.�������\t\t7.�������"
		<< "\n3.��\'�\t\t\t8.E-mail"
		<< "\n4.��-�������\t\t9.�����"
		<< "\n5.���� ����������\t10.��������"
		<<"\n\n0.³����\n";
	cout << "\n -> "; cin >> choice;
	if (choice == 0) return;
	char tmp[40];
	cout << "\n\n������ ��������� ����� -> ";
	if(choice != 6) cin >> tmp;
	else gets_s(tmp);
	database.open("database", ios_base::in);
	database.read((char*)&student, sizeof(student));
	while (!database.eof())
	{
		switch (choice)
		{
		case 1:
			if (atoi(tmp) == student.id)
				PrintExact(student);
			break;
		case 2:
			if (strcmp(tmp, student.surname) == 0)
				PrintExact(student);
			break;
		case 3:
			if (strcmp(tmp, student.name) == 0)
				PrintExact(student);
			break;
		case 4:
			if (strcmp(tmp, student.father) == 0)
				PrintExact(student);
			break;
		case 5:
			if (strcmp(tmp, student.birthday) == 0)
				PrintExact(student);
			break;
		case 6:
			if (strcmp(tmp, student.address) == 0)
				PrintExact(student);
			break;
		case 7:
			if (strcmp(tmp, student.telephone) == 0)
				PrintExact(student);
			break;
		case 8:
			if (strcmp(tmp, student.email) == 0)
				PrintExact(student);
			break;
		case 9:
			if (strcmp(tmp, student.group) == 0)
				PrintExact(student);
			break;
		case 10:
			if (atoi(tmp) == student.hasScolarship)
				PrintExact(student);
			break;
		}
		database.read((char*)&student, sizeof(student));
	}
	database.close();
	cout << "\n\n";
	system("pause");
}

void StudentDatabase::ApplyHandler()
{
	system("cls");
	tmp.open("handler", ios_base::in);
	if (!tmp) {
		cout << "���� ������� ������� �������...\n\n";
		system("pause");
		return;
	}
	tmp.close();
	cout << "\n����� ������������...\n";
	RemoveColize();
	fstream result;
	Student temp_stud;
	database.open("database", ios_base::in);
	tmp.open("handler", ios_base::in);
	result.open("tmp", ios_base::out);
	database.read((char*)&student, sizeof(student));
	tmp.read((char*)&temp_stud, sizeof(temp_stud));
	while (!database.eof() || !tmp.eof())
	{
		while (temp_stud.operation == 1 && !tmp.eof())
		{
			if (database.eof())
			{
				result.write((char*)&temp_stud, sizeof(temp_stud));
				tmp.read((char*)&temp_stud, sizeof(temp_stud));
				break;
			}
			if (student.id < temp_stud.id)
			{
				result.write((char*)&student, sizeof(student));
				database.read((char*)&student, sizeof(student));
			}
			else
			{
				result.write((char*)&temp_stud, sizeof(temp_stud));
				tmp.read((char*)&temp_stud, sizeof(temp_stud));
			}
		}
		while (temp_stud.operation == 2 && !tmp.eof())
		{
			if (temp_stud.id == student.id)
			{
				result.write((char*)&temp_stud, sizeof(temp_stud));
				tmp.read((char*)&temp_stud, sizeof(temp_stud));
				database.read((char*)&student, sizeof(student));
			}
			else
			{
				result.write((char*)&student, sizeof(student));
				database.read((char*)&student, sizeof(student));
			}
		}
		while (temp_stud.operation == 3 && (!tmp.eof() || !database.eof()))
		{
			if (temp_stud.id != student.id)
			{
				result.write((char*)&student, sizeof(student));
				database.read((char*)&student, sizeof(student));
			}
			else
			{
				database.read((char*)&student, sizeof(student));
				tmp.read((char*)&temp_stud, sizeof(temp_stud));
			}
		}
		if (tmp.eof() && !database.eof())
		{
			result.write((char*)&student, sizeof(student));
			database.read((char*)&student, sizeof(student));

		}
	}
	database.close();
	tmp.close();
	result.close();
	system("del database");
	system("del handler");
	system("rename tmp database");
	cout << "\n������...";
	system("pause");
}

void StudentDatabase::RemoveColize()
{
	vector<Student> v;
	tmp.open("handler", ios_base::in);
	tmp.read((char*)&student, sizeof(student));
	while (!tmp.eof())
	{
		v.push_back(student);
		tmp.read((char*)&student, sizeof(student));
	}
	tmp.close();

	int j = 0, tmp_id;
	for (int i = v.size() - 1; i >= 0; i--)
	{
		tmp_id = v[i].id;
		if (i != 0) {
			j = i;
			while (v[j - 1].id == tmp_id)
			{
				v.erase(v.begin() + j - 1);
				j--;
				if (j == 0) break;
			}
			i = j;
		}
	}
	tmp.open("tmp", ios_base::out);
	for (int i = 0; i < v.size(); i++) {
		tmp.write((char*)&v[i], sizeof(v[i]));
	}
	tmp.close();
	system("del handler");
	system("rename tmp handler");
}

bool StudentDatabase::Exist(int id)
{
	bool p = false;
	database.open("database", ios_base::in);
	database.read((char*)&student, sizeof(student));
	while (!database.eof())
	{
		if (id == student.id)
		{
			database.close();
			p = true;
			break;
		}
		database.read((char*)&student, sizeof(student));
	}
	database.close();
	/*tmp.open("handler", ios_base::in);
	if (tmp)
	{
		tmp.read((char*)&student, sizeof(student));
		while (!tmp.eof())
		{
			if (id == student.id)
			{
				while (!tmp.eof() && id == student.id)
				{
					if (student.operation == 3)
						p = false;
					else if (student.operation == 1)
						p = true;
					tmp.read((char*)&student, sizeof(student));
				}
				tmp.close();
				return p;
			}
			tmp.read((char*)&student, sizeof(student));
		}
	}
	tmp.close();*/
	student.id = id;
	return p;
}

void StudentDatabase::Print()
{
	system("cls");
	database.open("database", ios_base::in);
	database.read((char*)&student, sizeof(student));
	if (database.eof()) cout << "���� ����� �������...";
	while (!database.eof())
	{
		PrintExact(student);
		database.read((char*)&student, sizeof(student));
	}
	database.close();
	cout << "\n\n";
	system("pause");
}

void StudentDatabase::PrintToFile()
{
	tmp.open("database.txt", ios_base::out);
	tmp.clear();
	tmp << left << setw(4) << "ID"
		<< left << setw(20) << "�������"
		<< left << setw(20) << "��\'�"
		<< left << setw(20) << "��-�������"
		<< left << setw(17) << "���� ����������"
		<< left << setw(40) << "������"
		<< left << setw(16) << "�������"
		<< left << setw(25) << "E-mail"
		<< left << setw(10) << "�����"
		<< left << setw(4) << "��������\n\n";
	database.open("database", ios_base::in);
	database.read((char*)&student, sizeof(student));
	while (!database.eof())
	{
		tmp << left << setw(4) << student.id
			<< left << setw(20) << student.surname
			<< left << setw(20) << student.name
			<< left << setw(20) << student.father
			<< left << setw(17) << student.birthday
			<< left << setw(40) << student.address
			<< left << setw(16) << student.telephone
			<< left << setw(25) << student.email
			<< left << setw(10) << student.group
			<< left << setw(4) << student.hasScolarship << "\n";
		database.read((char*)&student, sizeof(student));
	}
	tmp.close();
	database.close();
	system("explorer.exe database.txt");
}

void StudentDatabase::PrintExact(Student student)
{
	cout << "\nID:\t\t" << student.id
		<< "\n�������:\t" << student.surname
		<< "\n��\'�:\t\t" << student.name
		<< "\n��-�������:\t" << student.father
		<< "\n���� ����������:" << student.birthday
		<< "\n������:\t\t"; puts(student.address);
	cout << "�������:\t" << student.telephone
		<< "\nE-mail:\t\t" << student.email
		<< "\n�����:\t\t" << student.group
		<< "\n��������:\t" << student.hasScolarship
		<< "\n";
}

void StudentDatabase::PrintHandler()
{
	system("cls");
	tmp.open("handler", ios_base::in);
	if (!tmp) {
		cout << "���� ������� ������� �������...\n\n";
		tmp.close();
		system("pause");
		return;
	}
	tmp.read((char*)&student, sizeof(student));
	if (tmp.eof()) cout << "���� ������� ������� �������...";
	while (!tmp.eof())
	{
		PrintExact(student);
		cout << "��������:\t" << student.operation << "\n";
		tmp.read((char*)&student, sizeof(student));
	}
	tmp.close();
	cout << "\n\n";
	system("pause");
}

void StudentDatabase::DeleteHandler()
{
	system("cls");
	tmp.open("handler", ios_base::in);
	if (tmp) {
		cout << "\n���������...";
		tmp.close();
		system("del handler");
		cout << "\n\n������...";
	}
	else
	{	
		tmp.close();
		cout << "���� ������� ������� �������...\n\n";
	}
	system("pause");
}
