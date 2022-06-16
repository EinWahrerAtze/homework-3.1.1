#include <iostream>
#include <fstream>

void show_array(const int *array, const int size)
{
	std::cout << size << std::endl;

	for (int i = 0; i < size; ++i)
	{
		std::cout << array[i] << (i == size - 1 ? "\n" : " ");
	}
}

int main()
{
	char in_filename[] = "in.txt";
	std::ifstream fin(in_filename);

	if (!fin.is_open())
	{
		std::cout << "Could not open file \"" << in_filename << "\".\n";
		exit(EXIT_FAILURE);
	}

	int count = 0;
	int first_size = 0;
	fin >> first_size;
	++count;

	int *first_array = new int[first_size]();

	for (int i = 0; i < first_size; ++i)
	{
		i == 0 ? fin >> first_array[first_size - 1] : fin >> first_array[i - 1];
		++count;
	}

	int second_size = 0;
	fin >> second_size;
	++count;

	int *second_array = new int[second_size]();

	for (int i = 0; i < second_size; ++i)
	{
		i == second_size - 1 ? fin >> second_array[0] : fin >> second_array[i + 1];
		++count;
	}

	if (fin.eof())
	{
		std::cout << "End of file reached.\n";
	}
	else if (fin.fail())
	{
		std::cout << "Input terminated by data mismatch.\n";
	}
	else
	{
		std::cout << "Input terminated for unknown reason.\n";
	}

	if (first_size + second_size == 0)
	{
		std::cout << "File \"" << in_filename << "\" is empty.\n";
	}
	else
	{
		std::cout << "Items read: " << count << ".\n\n";
	}

	fin.close();

	show_array(first_array, first_size);
	show_array(second_array, second_size);

	char out_filename[] = "out.txt";
	std::ofstream fout(out_filename);

	if (!fout.is_open())
	{
		std::cout << "Could not open file \"" << out_filename << "\" for output.\n";
	}

	fout << second_size << "\n";

	for (int i = 0; i < second_size; ++i)
	{
		fout << second_array[i] << (i == second_size - 1 ? "\n" : " ");
	}

	fout << first_size << "\n";

	for (int i = 0; i < first_size; ++i)
	{
		fout << first_array[i] << (i == first_size - 1 ? "\n" : " ");
	}

	std::cout << "\nData successfully written in \"" << out_filename << "\" file.\n";

	fout.close();

	delete[] first_array;
	delete[] second_array;
	return 0;
}