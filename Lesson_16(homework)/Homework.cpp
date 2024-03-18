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
	char str_file_name[200] = R"(F:\Temp_File\file_people.txt)";
	/*cout << "Enter file\n";
	cin.getline(str_file_name, 200);*/

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

void Show_People(Person* people, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "Last name: " << people[i].name << endl;
		cout << "Age: " << people[i].age << endl;
		cout << "Phone number: " << people[i].phone_number << endl;
	}

}

Person* Search_Person(Person* people, char* str_last_name, int size_1, int& size_2)
{
	int counter_1 = 0;
	for (int i = 0; i < size_1; i++)
	{
		if (strcmp(people[i].name, str_last_name) == 0)
		{
			counter_1++;
		}
	}

	size_2 = counter_1;

	Person* surnames_found = new Person[counter_1];

	for (int i = 0, j = 0; i < size_1; i++)
	{
		if (strcmp(people[i].name, str_last_name) == 0)
		{
			surnames_found[j] = people[i];
			j++;
		}
	}

	return surnames_found;
}

int main()
{
	int size_1;
	Person* people = Reading_from_File(size_1);

	/*Edit_Person(people, size);*/

	Show_People(people, size_1);

	int size_2;
	char str[] = "Noina";
	Person* surnames_found = Search_Person(people, str, size_1, size_2);
	Show_People(surnames_found, size_2);

	delete[] people;
	delete[] surnames_found;

	return 0;
}