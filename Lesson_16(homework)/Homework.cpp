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

void Edit_Person(Person* people, int size)
{
	int user_input;
	cout << "Enter the employee(1 - " << size << ")\n";

	do
	{
		cin >> user_input;
		if (user_input<1 || user_input>size)
		{
			cout << "ERROR!\n";
		}
	} while (user_input<1 || user_input>size);

	int user_input_edit;

	cout << "What do you want edit:\n1 - Lasr name\n2 - Age\n3 - Phone number\n";
	cin >> user_input;

	char str_user_input[200];
	int age;

	switch (user_input)
	{
	case 1:
		cin.ignore();
		cout << "Enter last name\n";
		cin.getline(str_user_input, 200);

		strcpy(people[user_input - 1].name, str_user_input);
		break;
	case 2:
		/*cin.ignore();*/
		cout << "Enter age\n";
		cin >> age;

		people[user_input - 1].age = age;
		break;
	case 3:
		cin.ignore();
		cout << "Enter phone number\n";
		cin.getline(str_user_input, 200);

		strcpy(people[user_input - 1].phone_number, str_user_input);
		break;
	default:
		break;
	}
}

int main()
{


	return 0;
}