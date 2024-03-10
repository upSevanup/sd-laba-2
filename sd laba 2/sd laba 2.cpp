#include <iostream>
#include <clocale>
#include <fstream>

//Лабораторная работа 2. Поливцев Михаил, ИВТ-31. Индивидуальный вариант 16.

using namespace std;

struct Pair {
	int Num1, Num2;
	Pair* Next;
};

Pair add_pair(Pair* Head, int num1, int num2);
bool check_pair(Pair* Head, int num1, int num2);
void print_list(Pair* Head);

int main() {
	setlocale(LC_ALL, "ru");

	ofstream inputfile("input.dat");
	ofstream outputfile("output.dat");

	Pair* Head = new Pair;		

	int p;
	cout << "Введите количество пар >> ";
	cin >> p;
	inputfile << "Количество пар: " << p << endl;

	int a, b, s = 0;
	cout << "Введите " << p << " пар чисел через пробел" << endl;

	// первый ввод
	cout << ">> "; cin >> a >> b;
	inputfile << a << "-" << b << endl;
	Head->Next = NULL;
	Head->Num1 = a;
	Head->Num2 = b;
	
	while (s != p-1) {
		cout << ">> "; cin >> a >> b;
		inputfile << a << "-" << b << endl;
		if (a != b && check_pair(Head, a, b)) {
			add_pair(Head, a, b);
		}
		s += 1;
	}

	// вывод в консоль
	print_list(Head);
	// запись в файл
	Pair* Current = Head;
	while (Current != NULL) {
		outputfile << Current->Num1 << "-" << Current->Num2 << "\t";
		Current = Current->Next;
	}

	inputfile.close();
	outputfile.close();
}

Pair add_pair(Pair* Head, int num1, int num2) {
	Pair *NewItem = new Pair;
	NewItem->Num1 = num1;
	NewItem->Num2 = num2;
	NewItem->Next = NULL;
	if (Head == NULL) {
		Head = NewItem;
	}
	else
	{
		Pair* Current = Head;
		while (Current->Next != NULL) {
			Current = Current->Next;
		}
		Current->Next = NewItem;
	}
	return *Head;
}

bool check_pair(Pair* Head, int num1, int num2) {
	// проверка есть лиэлементы в списке
	bool flag1 = true;
	bool flag2 = true;
	Pair *Current = Head;
	while (Current->Next != NULL) {
		if (Current->Num1 == num1 or Current->Num2 == num1) {
			flag1 = false;
		}
		if (Current->Num1 == num2 or Current->Num2 == num2) {
			flag2 = false;
		}
		Current = Current->Next;
	}
	if (flag1 or flag2) {
		return true;
	}
	// если элементы уже в списке то проверка на связь
	int c_num = num1, counter = -1, old_num = c_num;
	while (c_num != num2) {
		Current = Head;
		int s = 0;
		while (Current->Next != NULL) {
			if (Current->Num1 == c_num && counter != s) {
				c_num = Current->Num2;
				counter = s;
				break;
			}
			if (Current->Num2 == c_num && counter != s) {
				c_num = Current->Num1;
				counter = s;
				break;
			}
			s += 1;
			Current = Current->Next;
		}
		if (c_num == old_num) {
			return true;
		}
		old_num = c_num;

	}
	return false; 
}

void print_list(Pair* Head) {
	if (Head != NULL) {
		cout << Head->Num1 << "-" << Head->Num2 << "\t";
		print_list(Head->Next);
	}
	else {
		cout << "\n";
	}
}