#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>

using namespace std;

struct Person
{
	char name[200];
	int age;
	char phone_number[200];
};

Person* Reading_from_File(int& size)
{
	FILE* p_file;
	char str_file_name[200];
	cout << "Enter file\n";
	cin.getline(str_file_name, 200);

	p_file = fopen(str_file_name, "r");

	if (p_file == nullptr)
	{
		cout << "Error!\n";
		return nullptr;
	}

	char str_temp[200];
	int counter = 0;

	while (fgets(str_temp, 200, p_file) != nullptr)
	{
		counter++;
	}

	fseek(p_file, 0, SEEK_SET);
	Person* people = new Person[counter];

	for (int i = 0; i < counter; i++)
	{
		fscanf(p_file, "%s %i %s", people[i].name, &people[i].age, people[i].phone_number);
	}

	size = counter;

	return people;
}

int main()
{


	return 0;
}