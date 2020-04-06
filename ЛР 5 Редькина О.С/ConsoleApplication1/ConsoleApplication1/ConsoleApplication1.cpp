#include <iostream>;
#include <stdio.h>;
#include <cstdlib>;

using namespace std;

int Check_Element();
void Quick_Sort(int* array, int left, int right);

int main()
{
	system("color F0");
	int number = 0;
	int i = 0;
	int element = 0;

	cout << "This programm sorts the array by alghorithm called Quick Sort" << endl;
	cout << "Please enter the number of components of your array: ";
	number = Check_Element();                                //ввод количества элементов в массиве
	cout << endl;
	int* array = new int[number];
	cout << "Enter the components of array:" << endl;
	for (i = 0; i < number; i++)                              //заполнение массива
	{
		element = Check_Element();
		array[i] = element;
	};
	cout << "Your array:" << endl;
	for (i = 0; i < number; i++)                               //вывод введенного массива
	{
		cout << array[i] << " ";
	};
	cout << endl;
	Quick_Sort(array, 0, number - 1);                          //вызов функции быстрой сортировки
	cout << "Sorted array:" << endl;
	for (i = 0; i < number; i++)                               //вывод полученного массива
	{
		cout << array[i] << " ";
	};
	cout << endl;
	return 0;
};

//проверяет введенную компоненту
//происходит ввод данных в самой функции, возвращает введенную компоненту 
int Check_Element()
{
	int x = 0, y = 0;
	char buf[64];                                              // значение, которое ввел пользователь
	while (1)
	{
		x = scanf("%d", &y);                                    // если успешно, то цикл завершается
		if (x) break;
		scanf("%s", &buf);                                      // если неуспешно, то считываем значение как массив char
		printf("Uncorrect value. Please try again.\n");
		system("pause");
		cout << endl;
		main();
	};
	return y;
};

//сортирует массив
//перестановка элементов местами
void Quick_Sort(int* array, int left, int right)
{
	int point = array[left];
	int left_element = left, right_element = right;
	int gap = 0;
	int i = 0;

	while (left < right)                                          //пока границы не сомкнулись
	{
		while ((array[right] >= point) && (left < right))
			right--;                                              // сдвигаем правую границу пока элемент [right] больше [pivot]
		if (left != right)                                        // если границы не сомкнулись
		{
			array[left] = array[right];                           // перемещаем элемент [right] на место разрешающего
			left++;                                               // сдвигаем левую границу вправо
		}
		while ((array[left] <= point) && (left < right))
			left++;                                               // сдвигаем левую границу пока элемент [left] меньше [pivot]
		if (left != right)                                        // если границы не сомкнулись
		{
			array[right] = array[left];                           // перемещаем элемент [left] на место [right]
			right--;                                              // сдвигаем правую границу вправо
		}
	};
	array[left] = point;                                          // ставим разрешающий элемент на место
	point = left;
	left = left_element;
	right = right_element;
	if (left < point)                                             // рекурсивно вызываем сортировку для левой и правой части массива
		Quick_Sort(array, left, point - 1);
	if (right > point)
		Quick_Sort(array, point + 1, right);
};
