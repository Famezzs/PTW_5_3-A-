// 5_3(A)
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

enum class Speciality { COMPUTERSCIENCE, INFORMATICS, ECONOMICS, PHYSICS, CRAFT };
string SpecialityStr[] = { "Computer Science", "Informatics", "Mathematics and Economics", "Physics and Mathematics", "Craft" };

struct Student
{
	char surname[81];
	unsigned course;
	Speciality speciality;
	unsigned gradePhysics;
	unsigned gradeMathematics;
	unsigned gradeInformatics;
};

void Create(const string filename);
void Edit(const string filename);
void Display(const string filename, size_t size = 0, size_t k = 0);
void IndexDisplay(const string filename, size_t size = 0, size_t k = 0);
bool Sort(const string filename);
void IndexSort(const string filename);
int BinSearch(const string filename, const string surname, const Speciality speciality, const unsigned grade);
int IndexBinSearch(const string filename, const string surname, const Speciality speciality, const unsigned grade);
void Find(const string filename);
void IndexFind(const string filename);
Student fRead(fstream& f, const size_t i);
void fWrite(fstream& f, const size_t i, const Student x);
int fReadi(fstream& f, const size_t i);
void fWritei(fstream& f, const size_t i, const int x);
size_t Size(const string filename);

int main()
{
	string filename;
	char choice;
	do
	{
		cout << "What do you wish to do?\n[1] - Create a file\n[2] - Print a file\n[3] - Print an index sorted file\n[4] - Edit a file\n[5] - Sort\n[6] - Index sort\n[7] - Find\n[8] - Find in an index sorted file\n\n[0] - Exit the program\n";
		cin >> choice;

		switch (choice)
		{
		case '1':
			cout << "File's name : "; cin >> filename;
			Create(filename);
			break;
		case '2':
			cout << "File's name : "; cin >> filename;
			Display(filename);
			break;
		case '3':
			cout << "File's name : "; cin >> filename;
			IndexDisplay(filename);
			break;
		case '4':
			cout << "File's name : "; cin >> filename;
			Edit(filename);
			break;
		case '5':
			cout << "File's name : "; cin >> filename;
			Sort(filename);
			break;
		case '6':
			cout << "File's name : "; cin >> filename;
			IndexSort(filename);
			break;
		case '7':
			cout << "File's name : "; cin >> filename;
			Find(filename);
			break;
		case '8':
			cout << "File's name : "; cin >> filename;
			IndexFind(filename);
			break;
		case '0':
			break;
		default:
			cout << "\nWrong option chosen.\n\n";
			break;
		}

	} while (choice != '0');

	return 0;
}

void Create(const string filename)
{
	ofstream file(filename, ios::binary);
	if (!file)
	{
		cerr << "Could not create \"" << filename << "\".\n\n";
		return;
	}

	cout << "Successfully created \"" << filename << "\".\n\n";
}

void Edit(const string filename)
{
	ofstream file(filename, ios::binary | ios::ate | ios::_Nocreate);
	if (!file)
	{
		cerr << "Could not create \"" << filename << "\".\n\n";
		return;
	}

	int speciality;
	int i = 0;
	Student list;
	char choice;
	do
	{
		cout << "Student No. " << i + 1 << " :\n";
		cin.get();
		cin.sync();
		cout << "	Surname: "; cin.getline(list.surname, 80);
		cout << "	Course: "; cin >> list.course;
		cout << "	Speciality (0 - Computer Science, 1 - Informatics, 2 - Mathematics and Economics, 3 - Physics and Mathematics, 4 - Craft): "; cin >> speciality;
		list.speciality = (Speciality)speciality;
		cout << "	Grade for Physics: "; cin >> list.gradePhysics;
		cout << "	Grade for Mathematics: "; cin >> list.gradeMathematics;
		cout << "	Grade for Informatics: "; cin >> list.gradeInformatics;
		cout << endl;
		i++;

		file.write((char*)&list, sizeof(list));

		cin.get();
		cin.sync();
		cout << "Continue? (Y/N)\n";
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
}

void Display(const string filename, size_t size, size_t k)
{
	cout << "================================================================================================\n";
	cout << "| No |      Surname      | Course |         Speciality         | Physics | Maths | Informatics |\n";
	cout << "================================================================================================\n";

	fstream file(filename, ios::binary | ios::in);
	if (!file)
	{
		cerr << "Could not read \"" << filename << "\".\n\n";
		return;
	}

	if (size == 0)
		size = Size(filename);

	if (size != 0)
		for (size_t i = k; i < size; i++)
		{
			cout << "|" << setw(4) << right << i + 1 << "|" << setw(19) << left << fRead(file, i).surname << "|"
				<< setw(8) << right << fRead(file, i).course;
			switch (fRead(file, i).speciality)
			{
			case Speciality::COMPUTERSCIENCE:
				cout << "|" << setw(28) << left << "Computer Science" << "|"
					<< setw(9) << right << fRead(file, i).gradePhysics << "|"
					<< setw(7) << right << fRead(file, i).gradeMathematics << "|"
					<< setw(13) << right << fRead(file, i).gradeInformatics << "|\n";
				break;
			case Speciality::INFORMATICS:
				cout << "|" << setw(28) << left << "Informatics" << "|"
					<< setw(9) << right << fRead(file, i).gradePhysics << "|"
					<< setw(7) << right << fRead(file, i).gradeMathematics << "|"
					<< setw(13) << right << fRead(file, i).gradeInformatics << "|\n";
				break;
			case Speciality::ECONOMICS:
				cout << "|" << setw(28) << left << "Mathematics and Economics" << "|"
					<< setw(9) << right << fRead(file, i).gradePhysics << "|"
					<< setw(7) << right << fRead(file, i).gradeMathematics << "|"
					<< setw(13) << right << fRead(file, i).gradeInformatics << "|\n";
				break;
			case Speciality::PHYSICS:
				cout << "|" << setw(28) << left << "Physics and Mathematics" << "|"
					<< setw(9) << right << fRead(file, i).gradePhysics << "|"
					<< setw(7) << right << fRead(file, i).gradeMathematics << "|"
					<< setw(13) << right << fRead(file, i).gradeInformatics << "|\n";
				break;
			case Speciality::CRAFT:
				cout << "|" << setw(28) << left << "Craft" << "|"
					<< setw(9) << right << fRead(file, i).gradePhysics << "|" << setw(7)
					<< right << fRead(file, i).gradeMathematics << "|"
					<< setw(13) << right << fRead(file, i).gradeInformatics << "|\n";
				break;
			}
		}
	cout << "================================================================================================\n\n\n";
}

void IndexDisplay(const string filename, size_t size, size_t k)
{
	fstream file(filename, ios::binary | ios::in);
	if (!file)
	{
		cerr << "Could not open \"" << filename << "\".\n\n";
		return;
	}

	fstream index(filename + "index", ios::binary | ios::in);
	if (!index)
	{
		cerr << "Could not open \"" << filename + "index" << "\".\n\n";
		return;
	}

	cout << "================================================================================================\n";
	cout << "| No |      Surname      | Course |         Speciality         | Physics | Maths | Informatics |\n";
	cout << "================================================================================================\n";

	if (size == 0)
		size = Size(filename);

	if (size != 0)
		for (size_t i = k; i < size; i++)
		{
			cout << "|" << setw(4) << right << i + 1 << "|" << setw(19) << left << fRead(file, fReadi(index, i)).surname
				<< "|" << setw(8) << right << fRead(file, fReadi(index, i)).course;
			switch (fRead(file, fReadi(index, i)).speciality)
			{
			case Speciality::COMPUTERSCIENCE:
				cout << "|" << setw(28) << left << "Computer Science" << "|"
					<< setw(9) << right << fRead(file, fReadi(index, i)).gradePhysics << "|" << setw(7)
					<< right << fRead(file, fReadi(index, i)).gradeMathematics << "|"
					<< setw(13) << right << fRead(file, fReadi(index, i)).gradeInformatics << "|\n";
				break;
			case Speciality::INFORMATICS:
				cout << "|" << setw(28) << left << "Informatics" << "|"
					<< setw(9) << right << fRead(file, fReadi(index, i)).gradePhysics << "|" << setw(7)
					<< right << fRead(file, fReadi(index, i)).gradeMathematics << "|"
					<<  setw(13) << right << fRead(file, fReadi(index, i)).gradeInformatics << "|\n";
				break;
			case Speciality::ECONOMICS:
				cout << "|" << setw(28) << left << "Mathematics and Economics" << "|"
					<< setw(9) << right << fRead(file, fReadi(index, i)).gradePhysics << "|" << setw(7) << right
					<< fRead(file, fReadi(index, i)).gradeMathematics << "|"
					<<  setw(13) << right << fRead(file, fReadi(index, i)).gradeInformatics << "|\n";
				break;
			case Speciality::PHYSICS:
				cout << "|" << setw(28) << left << "Physics and Mathematics" << "|"
					<< setw(9) << right << fRead(file, fReadi(index, i)).gradePhysics << "|" << setw(7)
					<< right << fRead(file, fReadi(index, i)).gradeMathematics << "|"
					<<  setw(13) << right << fRead(file, fReadi(index, i)).gradeInformatics << "|\n";
				break;
			case Speciality::CRAFT:
				cout << "|" << setw(28) << left << "Craft" << "|"
					<< setw(9) << right << fRead(file, fReadi(index, i)).gradePhysics << "|" << setw(7)
					<< right << fRead(file, fReadi(index, i)).gradeMathematics << "|"
					<<  setw(13) << right << fRead(file, fReadi(index, i)).gradeInformatics << "|\n";
				break;
			}
		}
	cout << "================================================================================================\n\n\n";
}

size_t Size(const string filename)
{
	size_t count = 0;
	ifstream file(filename, ios::binary | ios::in);
	if (!file)
		return 0;

	Student list;
	while (file.read(reinterpret_cast<char*>(&list), sizeof(list)))
		count++;

	return count;
}

Student fRead(fstream& f, const size_t i)
{
	Student x;
	f.seekg(i * (long)sizeof(Student)); 
	f.read((char*)&x, sizeof(Student)); 
	return x;
}

int fReadi(fstream& f, const size_t i)
{
	int x;
	f.seekg(i * (long)sizeof(int)); 
	f.read((char*)&x, sizeof(int)); 
	return x;
}

void fWritei(fstream& f, const size_t i, const int x)
{
	f.seekp(i * (long)sizeof(int)); 
	f.write((char*)&x, sizeof(int)); 
}

void fWrite(fstream& f, const size_t i, const Student x)
{
	f.seekp(i * (long)sizeof(Student));
	f.write((char*)&x, sizeof(Student));
}

bool Sort(const string filename)
{
	Student tmp;
	size_t size = Size(filename);

	fstream file(filename, ios::binary | ios::_Nocreate | ios::out | ios::in);
	if (!file)
	{
		cerr << "Could not open \"" << filename << "\".\n\n";
		return false;
	}

	for (int i0 = 0; i0 < size - 1; i0++)
	{
		for (int i1 = 0; i1 < size - i0 - 1; i1++)
		{
			if ((fRead(file, i1).speciality > fRead(file, i1 + 1).speciality) ||
				(fRead(file, i1).speciality == fRead(file, i1 + 1).speciality &&
					fRead(file, i1).gradeInformatics < fRead(file, i1 + 1).gradeInformatics) ||
				(fRead(file, i1).speciality == fRead(file, i1 + 1).speciality &&
					fRead(file, i1).gradeInformatics == fRead(file, i1 + 1).gradeInformatics &&
					string(fRead(file, i1).surname) > string(fRead(file, i1 + 1).surname)))
			{
				tmp = fRead(file, i1);
				fWrite(file, i1, fRead(file, i1 + 1));
				fWrite(file, i1 + 1, tmp);
			}
		}
	}
	return true;
}


void IndexSort(const string filename)
{
	size_t size = Size(filename);

	fstream srce(filename, ios::binary | ios::_Nocreate | ios::in);
	if (!srce)
	{
		cerr << "Could not open \"" << filename << "\".\n\n";
		return;
	}

	fstream dest(filename + "index", ios::binary | ios::in | ios::out | ios::trunc);
	if (!dest)
	{
		cerr << "Could not open \"" << filename + "index" << "\".\n\n";
		return;
	}

	for (int i = 0; i < size; i++)
		fWritei(dest, i, i);
	int i, j, value;
	for (i = 1; i < size; i++)
	{
		value = fReadi(dest, i);
		for (j = i - 1;
			j >= 0 && ((fRead(srce, fReadi(dest, j)).speciality > fRead(srce, value).speciality) ||
				(fRead(srce, fReadi(dest, j)).speciality == fRead(srce, value).speciality &&
					fRead(srce, fReadi(dest, j)).gradeInformatics < fRead(srce, value).gradeInformatics) ||
				(fRead(srce, fReadi(dest, j)).speciality == fRead(srce, value).speciality &&
					fRead(srce, fReadi(dest, j)).gradeInformatics == fRead(srce, value).gradeInformatics &&
					string(fRead(srce, fReadi(dest, j)).surname) > string(fRead(srce, value).surname)));
			j--)
		{
			fWritei(dest, j + 1, fReadi(dest, j));
		}
		fWritei(dest, j + 1, value);
	}

	srce.close();
	dest.close();
}

int BinSearch(const string filename, const string surname, const Speciality speciality, const unsigned grade)
{
	fstream file(filename, ios::binary | ios::in);
	if (!file)
	{
		cerr << "Could not open \"" << filename << "\".\n\n";
		return -1;
	}

	size_t size = Size(filename);
	int L = 0, R = size - 1, m;
	do {
		m = (L + R) / 2;
		if (string(fRead(file, m).surname) == surname && fRead(file, m).speciality == speciality &&
			fRead(file, m).gradeInformatics == grade)
			return m;
		if ((fRead(file, m).speciality < speciality)
			||
			(fRead(file, m).speciality == speciality &&
				fRead(file, m).gradeInformatics > grade) || (fRead(file, m).speciality == speciality &&
					fRead(file, m).gradeInformatics == grade && string(fRead(file, m).surname) < surname))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}

int IndexBinSearch(const string filename, const string surname, const Speciality speciality, const unsigned grade)
{
	fstream file(filename, ios::binary | ios::in);
	if (!file)
	{
		cerr << "Could not open \"" << filename << "\".\n\n";
		return -1;
	}

	fstream index(filename + "index", ios::binary | ios::in);
	if (!index)
	{
		cerr << "Could not open \"" << filename + "index" << "\".\n\n";
		return -1;
	}

	size_t size = Size(filename);
	int L = 0, R = size - 1, m;
	do {
		m = (L + R) / 2;
		if (string(fRead(file, fReadi(index, m)).surname) == surname &&
			fRead(file, fReadi(index, m)).speciality == speciality &&
			fRead(file, fReadi(index, m)).gradeInformatics == grade)
			return m;
		if ((fRead(file, fReadi(index, m)).speciality < speciality)
			||
			(fRead(file, fReadi(index, m)).speciality == speciality &&
				fRead(file, fReadi(index, m)).gradeInformatics > grade) ||
			(fRead(file, fReadi(index, m)).speciality == speciality &&
				fRead(file, fReadi(index, m)).gradeInformatics == grade &&
				string(fRead(file, fReadi(index, m)).surname) < surname))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}

void Find(const string filename)
{
	string surname;
	int _speciality;
	unsigned grade;
	Speciality speciality;
	bool isnotadequate = false;

	do
	{
		cin.get();
		cin.sync();

		cout << "	Surname: ";
		getline(cin, surname);
		cout << "	Speciality (0 - Computer Science, 1 - Informatics, 2 - Mathematics and Economics, 3 - Physics and Mathematics, 4 - Craft): "; cin >> _speciality;
		speciality = (Speciality)_speciality;
		
		cout << "	Grade for Informatics: ";
		cin >> grade;
		cout << endl;

		isnotadequate = _speciality < 0 || _speciality > 4 || grade == 0 || grade > 5;
		if (isnotadequate)
			cout << "Values provided are inadequate.\n\n";
	} while (isnotadequate);

	int foundat = BinSearch(filename, surname, speciality, grade);
	if (foundat != -1)
		Display(filename, foundat + 1, foundat);
	else
		cout << "No such student exists.\n\n";
		
}

void IndexFind(const string filename)
{
	string surname;
	int _speciality;
	unsigned grade;
	Speciality speciality;
	bool isnotadequate = false;

	do
	{
		cin.get();
		cin.sync();

		cout << "	Surname: ";
		getline(cin, surname);
		cout << "	Speciality (0 - Computer Science, 1 - Informatics, 2 - Mathematics and Economics, 3 - Physics and Mathematics, 4 - Craft): "; cin >> _speciality;
		speciality = (Speciality)_speciality;
		cout << "	Grade for Informatics: ";
		cin >> grade;
		cout << endl;

		isnotadequate = _speciality < 0 || _speciality > 4 || grade == 0 || grade > 5;
		if (isnotadequate)
			cout << "Values provided are inadequate.\n\n";
	} while (isnotadequate);

	int foundat = IndexBinSearch(filename, surname, speciality, grade);
	if (foundat != -1)
		IndexDisplay(filename, foundat + 1, foundat);
	else
		cout << "No such student exists.\n\n";
}