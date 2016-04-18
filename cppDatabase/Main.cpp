#include<iostream>
#include<Windows.h>
#include"StudentDatabase.h"
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	short choice, M;
	while (1)
	{
		/*Головне Меню*/
		system("cls");
		cout << "\n\t1.Створити базу даних"
			<< "\n\n\t2.Додати дані про нового студента"
			<< "\n\t3.Редагувати дані про студента"
			<< "\n\t4.Видалити дані про студента"
			<< "\n\n\t5.Пошук"
			<< "\n\t6.Вивести на екран"
			<< "\n\t7.Друкувати у файл"
			<< "\n\n\t8.Застосувати зміни"
			<< "\n\n\t9.Вивести файл групової обробки"
			<< "\n\t10.Видалити файл групової обробки"
			<< "\n\n\t0.Вихід";
		cout << "\n\n\tОберіть операцію:\n";
		M:	cout << "\t -> "; cin >> choice;
		switch (choice)
		{
		case 1: StudentDatabase::CreateDatabase(); break;
		case 2:	StudentDatabase::Insert(); break;
		case 3:	StudentDatabase::Edit(); break;
		case 4:	StudentDatabase::Delete(); break;
		case 5:	StudentDatabase::Search(); break;
		case 6:	StudentDatabase::Print(); break;
		case 7:	StudentDatabase::PrintToFile(); break;
		case 8:	StudentDatabase::ApplyHandler(); break;
		case 9:	StudentDatabase::PrintHandler(); break;
		case 10: StudentDatabase::DeleteHandler(); break;
		case 0:	exit(1); break;
		default: cout << "\nБудь ласка, повторіть спробу...\n"; goto M; break;
		}
	}
	cout << "\n\n";
	return 1;
}