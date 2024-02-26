#pragma once
#include <string>
#include <vector>

/*
Дата, фио, название дисциплины
1.3)дата, фио; двухпутевые вставки и пирамидальная
2.1)Дата, фио, название дисциплины; АБМХ, РХ;
*/
const int N = 8;

struct date
{
	int dd;
	int mm;
	int yy;
};
struct fio
{
	std::string name;
	std::string surname;
	std::string fathername;
};

struct key1
{
	date date_;
	fio fio_;
};

struct key2
{
	date date_;
	fio fio_;
	std::string discipline;
};

// [25, 57, 48, 37,12 92, 86, 33];
void twoWayInsertSort(int a[N])//добавить параметр, по которому сортировать(имя-фамилия-отч/во-дата)
{
	int temp[N] = { };
	int temp_el;

	int mid = (int)(N / 2);
	//temp_el = temp[mid];
	temp[mid] = a[0];


	for (int i = 1; i < N; ++i)
	
		if (a[i] >= temp[mid])
		{
			*(temp + i) = a[i];
		}
		else
		{
			int j = mid - 1;
			while (a[i] < temp[j])
				j -= 1;
			temp[j] = a[i];
		}
	}
	for (int i = 0; i < N; ++i)
	{
		a[i] = temp[i];
	}
}
void pyramidalSort(int a[N])
{

}

