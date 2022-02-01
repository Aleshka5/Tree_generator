#include <iostream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <vector>
using namespace std;
template <typename T>
void print(T value) {
	cout << value << endl;
}
//Вывод массива в строку
void print(int* arr, int size) {
	if (arr != NULL) {
		for (int i = 0; i < size; i++)
		{
			cout << arr[i] << " ";
		}
		cout << "\n";
	}
	else {
		cout << "Невозможно вывести пустой массив" << endl;
	}
}
//Вывод поля
void print(int **field, int size_x, int size_y) {
	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			if (field[i][j] > -1) {
				cout << " " << field[i][j] << " ";
			}
			else {
				cout << field[i][j] << " ";
			}
		}
		cout << endl;

	}
	cout << endl;
}
//Вывод нескольких полей в сртоку
void print_v2(int ***arr_field, int count, int size) {
	for (int i = 0; i < size; i++) {
		for (int next = 0; next < count; next++) {
			for (int j = 0; j < size; j++) {
				if (arr_field[next][i][j] > -1) {
					cout << " " << arr_field[next][i][j] << " ";
				}
				else {
					cout << arr_field[next][i][j] << " ";
				}
			}
			cout << "  ";
		}
		cout << endl;

	}
	cout << endl;
}
//Удаление поля
void _delete_(int** field, int size_y) {
	if (field != NULL) {
		for (int j = 0; j < size_y; j++)
		{
			if (field[j] != NULL) {
				delete[] field[j];
			}
		}
		delete[] field;
	}
}
void _delete_(int*** field, int size_y, int size_z) {
	if (field != NULL) {
		for (int j = 0; j < size_z; j++)
		{
			for (int i = 0; i < size_y; i++) {
				delete[] field[j][i];
			}
			delete[] field[j];
		}
		delete[] field;
	}
}
//Удаление массива
template <typename T>
void _delete_(T* field) {
	if (field != NULL) {
		delete[] field;
	}
}


class Elem_Tree
{
private:
	//Размер передаваемого поля
	int const scale_x = 3;
	int const scale_y = 3;
	int const scale_z = 1;
	int count_links;
public:
	int** data_xy;
	int*** data_xyz;
	Elem_Tree* Next;
	int deep;
	//Конструктор с параметрами xy
	Elem_Tree(int** field, int x, int y, int deep_level) {
		this->data_xy = new int*[scale_y];
		for (int i = 0; i < this->scale_y; i++)
		{
			data_xy[i] = new int[scale_x];
		}

		for (int y = 0; y < this->scale_y; y++)
		{
			for (int x = 0; x < this->scale_x; x++)
			{
				this->data_xy[y][x] = field[x][y];
			}
		}
		delete[] this->data_xyz;
		this->deep = deep_level;
		this->count_links = 0;
	}
	//Конструктор с параметрами xyz
	Elem_Tree(int*** field, int x, int y, int z, int deep_level) {
		this->data_xyz = new int**[scale_z];
		for (int i = 0; i < this->scale_z; i++)
		{
			data_xyz[i] = new int*[scale_y];
			for (int j = 0; j < this->scale_z; j++)
			{
				data_xyz[i][j] = new int[scale_x];
			}
		}
		for (int z = 0; z < this->scale_z; z++)
		{
			for (int y = 0; y < this->scale_y; y++)
			{
				for (int x = 0; x < this->scale_x; x++)
				{
					this->data_xyz[z][y][x] = field[z][y][x];
				}
			}
		}
		delete[] this->data_xy;
		this->deep = deep_level;
		this->count_links = 0;
	}
	//Конструктор по умолчанию
	Elem_Tree() {
		if (this->scale_z == 1) {
			this->data_xy[scale_y][scale_x];
			//Заполнение нулями
			for (int y = 0; y < this->scale_y; y++)
			{
				for (int x = 0; x < this->scale_x; x++)
				{
					this->data_xy[y][x] = 0;
				}
			}
			delete[] data_xyz;
		}
		if (this->scale_z > 1) {
			this->data_xyz[scale_z][scale_y][scale_x];
			//Заполнение нулями
			for (int z = 0; z < this->scale_z; z++)
			{
				for (int y = 0; y < this->scale_y; y++)
				{
					for (int x = 0; x < this->scale_x; x++)
					{
						this->data_xyz[z][y][x] = 0;
					}
				}
			}
			delete[] data_xy;
		}
		this->deep = 0;
		this->count_links = 0;
		print("Вызвался консруктор");
	}
	void Insert_link(Elem_Tree* child_elem) {
		this->Next = child_elem;
	}
	void Delete_link() {

	}
	void Update_field(int** field, int x, int y) {

	}
	//Удаление поля
	void _delete_(int scale_y) {
		if (this->data_xy != NULL) {
			for (int j = 0; j < scale_y; j++)
			{
				if (this->data_xy[j] != NULL) {
					delete[] this->data_xy[j];
				}
			}
			delete[] this->data_xy;
		}
	}
	void _delete_(int scale_y, int scale_z) {
		if (this->data_xyz != NULL) {
			for (int j = 0; j < scale_z; j++)
			{
				for (int i = 0; i < scale_y; i++) {
					delete[] this->data_xyz[j][i];
				}
				delete[] this->data_xyz[j];
			}
			delete[] this->data_xyz;
		}
		print("Удалилось поле XY");
	}

	~Elem_Tree() {
		/*
		if (scale_z == 1) {
			this->_delete_(this->data_xy);
		}
		if (scale_z > 1) {
			this->_delete_(this->data_xyz);
		}
		delete[] Next;
		*/
		print("Вызвался деструктор");
	};
};

//Удаление элемента дерева
void _delete_(Elem_Tree field, int &count_dels) {

}
//Построение линейного дерева
void linear_tree(Elem_Tree* link_to_parent, int deep) {
	Elem_Tree t = Elem_Tree();
	(&t)->Insert_link(link_to_parent);
	if (deep != 0) {
		linear_tree(&t, deep - 1);
	}
	//t._delete_(3);	
}
void cleaner_linear_tree(Elem_Tree* link_to_parent, int& deep) {
	if (link_to_parent->Next != NULL) {
		deep--;
		print(deep);
		cleaner_linear_tree(link_to_parent->Next, deep);
	}
}

void rec(int d) {
	int arr[100];
	//print(d);
	if (d > 0) {
		rec(d - 1);
	}
}
void rec_din(int d) {
	int* arr = new int[100];
	//print(d);
	if (d > 0) {
		rec_din(d - 1);
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	//---- Постоянные константы:	----
	int numCPU = sysinfo.dwNumberOfProcessors; //Количество доступных потоков процессора
	//Размер передаваемого поля
	int const scale_x = 3;
	int const scale_y = 3;
	int const scale_z = 1;
	int x;
	print("До всех циклов");
	cin >> x;
	//rec(1600);		
	for (int i = 0; i < 2000; i++)
	{
		int arr[100];
	}
	print("После не динамического");
	cin >> x;
	//rec_din(4000);		
	for (int i = 0; i < 2000; i++)
	{
		int* arr = new int[100];
	}
	print("После динамического");
	cin >> x;
	int _if_;
	print("1 - Построение линейного дерева\n");
	cin >> _if_;
	switch (_if_)
	{
	case 1: {
		int deep = 1000;
		Elem_Tree* t = new Elem_Tree;
		linear_tree(t, 1000);
		//cleaner_linear_tree(t,deep);
		cin >> deep;
		break;
	}
	case 2: {
		break;
	}
	case 3: {
		break;
	}
	case 4: {
		break;
	}
	default:
		break;
	}
	return 0;
}
