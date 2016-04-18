#include "StudentDatabase.h"

void StudentDatabase::CreateDatabase()
{
	char p;
	system("cls");
	cout << "\nВи впевнені, що хочете створити нову базу даних? Стара база даних буде знищена...";
	cout << "\n\n (1 - ТАК, 0 - НІ) -> "; cin >> p;
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
	cout << "Будь ласка, введіть інформацію про нового студента...";
	cout << "\nID -> "; cin >> student.id;
	if (Exist(student.id))
	{
		cout << "\nСтудент з таким ID вже існує...\n\n";
		system("pause");
		return;
	}
	cout << "\nПрізвище -> "; cin >> student.surname;
	cout << "Ім\'я -> "; cin >> student.name;
	cout << "По-батькові -> "; cin >> student.father;
	cout << "\nДень народження (ДД.ММ.РРРР) -> "; cin >> student.birthday;
	getchar();
	cout << "Адреса -> "; gets_s(student.address);
	cout << "Телефон -> "; cin >> student.telephone;
	cout << "E-mail -> "; cin >> student.email;
	cout << "\nГрупа -> "; cin >> student.group;
	cout << "\nЧи має він/вона стипендію? (1 - ТАК, 0 - НІ) -> "; cin >> student.hasScolarship;
	student.operation = 1;

	char choice;
	cout << "\nОберіть спосіб внесення даних:"
		<< "\n1.Внести в базу даних"
		<< "\n2.Внести в файл групової обробки"
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
	cout << "Введіть ID студента, дані про якого ви хочете редагувати...";
	cout << "\n\nID -> "; cin >> student.id;
	if (!Exist(student.id))
	{
		cout << "\nСтудента з таким ID в базі даних не виявлено...\n\n";
		system("pause");
		return;
	}
	cout << "\nБудь ласка, введіть нову інформацію про студента...";
	cout << "\n\nПрізвище -> "; cin >> student.surname;
	cout << "Ім\'я -> "; cin >> student.name;
	cout << "По-батькові -> "; cin >> student.father;
	cout << "\nДень народження (ДД.ММ.РРРР) -> "; cin >> student.birthday;
	getchar();
	cout << "Адреса -> "; gets_s(student.address);
	cout << "Телефон -> "; cin >> student.telephone;
	cout << "E-mail -> "; cin >> student.email;
	cout << "\nГрупа -> "; cin >> student.group;
	cout << "\nЧи має він/вона стипендію? (1 - ТАК, 0 - НІ) -> "; cin >> student.hasScolarship;
	student.operation = 2;

	char choice;
	cout << "\nОберіть спосіб внесення змін:"
		<< "\n1.Редагувати в базі даних"
		<< "\n2.Внести в файл групової обробки"
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
	cout << "Введіть ID студента, дані про якого ви хочете видалити...";
	cout << "\n\nID -> "; cin >> student.id;
	if (!Exist(student.id))
	{
		cout << "\nСтудента з таким ID в базі даних не виявлено...\n\n";
		system("pause");
		return;
	}
	student.operation = 3;

	char choice;
	cout << "\nОберіть спосіб видалення даних:"
		<< "\n1.Видалити з бази даних"
		<< "\n2.Внести в файл групової обробки"
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
	cout << "\n Оберіть поле, по якому ви хочете здійснювати пошук...\n";
	cout << "\n1.ID\t\t\t6.Адреса"
		<< "\n2.Прізвище\t\t7.Телефон"
		<< "\n3.Ім\'я\t\t\t8.E-mail"
		<< "\n4.По-батькові\t\t9.Група"
		<< "\n5.День народження\t10.Стипендія"
		<<"\n\n0.Відміна\n";
	cout << "\n -> "; cin >> choice;
	if (choice == 0) return;
	char tmp[40];
	cout << "\n\nВведіть пошуковий запит -> ";
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
		cout << "Файл групової обробки відсутній...\n\n";
		system("pause");
		return;
	}
	tmp.close();
	cout << "\nТриває застосування...\n";
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
	cout << "\nГотово...";
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
	if (database.eof()) cout << "База даних порожня...";
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
		<< left << setw(20) << "Прізвище"
		<< left << setw(20) << "Ім\'я"
		<< left << setw(20) << "По-батькові"
		<< left << setw(17) << "День народження"
		<< left << setw(40) << "Адреса"
		<< left << setw(16) << "Телефон"
		<< left << setw(25) << "E-mail"
		<< left << setw(10) << "Група"
		<< left << setw(4) << "Стипендія\n\n";
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
		<< "\nПрізвище:\t" << student.surname
		<< "\nІм\'я:\t\t" << student.name
		<< "\nПо-батькові:\t" << student.father
		<< "\nДень народження:" << student.birthday
		<< "\nАдреса:\t\t"; puts(student.address);
	cout << "Телефон:\t" << student.telephone
		<< "\nE-mail:\t\t" << student.email
		<< "\nГрупа:\t\t" << student.group
		<< "\nСтипендія:\t" << student.hasScolarship
		<< "\n";
}

void StudentDatabase::PrintHandler()
{
	system("cls");
	tmp.open("handler", ios_base::in);
	if (!tmp) {
		cout << "Файл групової обробки відсутній...\n\n";
		tmp.close();
		system("pause");
		return;
	}
	tmp.read((char*)&student, sizeof(student));
	if (tmp.eof()) cout << "Файл групової обробки порожній...";
	while (!tmp.eof())
	{
		PrintExact(student);
		cout << "Операція:\t" << student.operation << "\n";
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
		cout << "\nВидалення...";
		tmp.close();
		system("del handler");
		cout << "\n\nГотово...";
	}
	else
	{	
		tmp.close();
		cout << "Файл групової обробки відсутній...\n\n";
	}
	system("pause");
}
