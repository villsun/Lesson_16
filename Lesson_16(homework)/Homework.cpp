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

void Edit_Last_Name(Person* people, int index)
{
	cout << "Enter last name:\n";
	char str[200];
	cin >> str;
	strcpy(people[index].name, str);
}

void Edit_Age(Person* people, int index)
{
	cout << "Enter new age:\n";
	int new_age;
	cin >> new_age;
	people[index].age = new_age;
}

void Edit_Phone_Number(Person* people, int index)
{
	cout << "Enter phone number:\n";
	char str[200];
	cin >> str;
	strcpy(people[index].phone_number, str);
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

	cout << "What do you want edit:\n1 - Last name\n2 - Age\n3 - Phone number\n";
	cin >> user_input_edit;

	switch (user_input_edit)
	{
	case 1:
		cin.ignore();
		Edit_Last_Name(people, user_input - 1);
		break;
	case 2:
		/*cin.ignore();*/
		Edit_Age(people, user_input - 1);
		break;
	case 3:
		cin.ignore();
		Edit_Phone_Number(people, user_input - 1);
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

Person* Search_Person(Person* people, int size_1, int& size_2)
{
	char str_last_name[200];
	cout << "Enter Name:\n";
	cin >> str_last_name;

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

void Add_Person(Person*& people, int& size)
{
	size++;
	Person* new_person = new Person[size];

	for (int i = 0; i < size - 1; i++)
	{
		new_person[i] = people[i];
	}

	Edit_Last_Name(new_person, size - 1);
	Edit_Age(new_person, size - 1);
	Edit_Phone_Number(new_person, size - 1);

	delete[] people;

	people = new_person;
}

void Delete_Person(Person*& people, int& size)
{
	int user_input;
	do
	{
		cout << "Enter index from 1 to size:\n";
		cin >> user_input;
	} while (user_input<1 || user_input>size);

	Person* new_person = new Person[--size];
	user_input--;
	for (int i = 0; i < user_input; i++)
	{
		new_person[i] = people[i];
	}

	for (int i = user_input; i < size; i++)
	{
		new_person[i] = people[i + 1];
	}

	people = new_person;
}

Person* Search_by_Age(Person* people, int size_1, int& size_2)
{
	int age;
	cout << "Enter age:\n";
	cin >> age;

	int counter = 0;

	for (int i = 0; i < size_1; i++)
	{
		if (age == people[i].age)
		{
			counter++;
		}
	}

	Person* search_age = new Person[counter];
	int counter_index = 0;

	for (int i = 0; i < size_1; i++)
	{
		if (age == people[i].age)
		{
			search_age[counter_index++] = people[i];
		}
	}

	size_2 = counter;

	return search_age;
}

Person* Search_by_Letter_Name(Person* people, int size_1, int& size_2)
{
	char letter_name;
	cout << "Enter letter name:\n";
	cin >> letter_name;

	int counter = 0;

	for (int i = 0; i < size_1; i++)
	{
		if (letter_name == people[i].name[0])
		{
			counter++;
		}
	}

	Person* search_letter_name = new Person[counter];
	int counter_index = 0;

	for (int i = 0; i < size_1; i++)
	{
		if (letter_name == people[i].name[0])
		{
			search_letter_name[counter_index++] = people[i];
		}
	}

	size_2 = counter;

	return search_letter_name;
}

void Save_People(Person* people, int size)
{
	FILE* p_file = fopen(R"(F:\Temp_File\file_people_new.txt)", "w");

	for (int i = 0; i < size; i++)
	{
		fprintf(p_file, "%s %i %s\n", people[i].name, people[i].age, people[i].phone_number);
	}

}

int main()
{
	int size_1;
	Person* people = Reading_from_File(size_1);

	int user_input;
	Person* people_new;
	int size_2;
	do
	{
		do
		{
			cout << "Enter what do you waant:\n1 - Edit person\n2 - Search person\n3 - Add person\n4 - Delete person\n5 - Search by age\n6 - Search by letter name\n7 - Save people\n0 to stop\n";
			cin >> user_input;
		} while (user_input < 0 || user_input>7);

		if (user_input == 0)
		{
			Save_People(people, size_1);
			break;
		}

		switch (user_input)
		{
		case 1:
			Edit_Person(people, size_1);
			Show_People(people, size_1);
			break;
		case 2:
			people_new = Search_Person(people, size_1, size_2);
			Show_People(people_new, size_2);
			delete[] people_new;
			break;
		case 3:
			Add_Person(people, size_1);
			Show_People(people, size_1);
			break;
		case 4:
			Delete_Person(people, size_1);
			Show_People(people, size_1);
			break;
		case 5:
			people_new = Search_by_Age(people, size_1, size_2);
			Show_People(people_new, size_2);
			delete[] people_new;
			break;
		case 6:
			people_new = Search_by_Letter_Name(people, size_1, size_2);
			Show_People(people_new, size_2);
			delete[] people_new;
			break;
		case 7:
			Save_People(people, size_1);
			break;
		default:
			break;
		}
	} while (true);
	delete[] people;

	return 0;
}