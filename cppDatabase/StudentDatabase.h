#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Student.h"
using namespace std;

static Student student;
static fstream database;
static fstream tmp;

class StudentDatabase
{
public:
	static void CreateDatabase();
	static void Insert();
	static void Edit();
	static void Delete();
	static void Search();
	static void Print();
	static void PrintToFile();
	static void ApplyHandler();
	static void PrintHandler();
	static void DeleteHandler();
private:
	static bool Exist(int);
	static void PrintExact(Student);
	static void InsertToHandler();
	static void InsertToDatabase();
	static void EditInDatabase();
	static void DeleteFromDatabase();
	static void RemoveColize();
};

