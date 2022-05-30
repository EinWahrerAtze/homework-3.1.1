#include <iostream>
#include <fstream>
#include <string>

struct Arrays
{
	int size = 0;
	int* array = new int[size];
};

int check_data(std::string value)
{
	try 
	{
		return stoi(value);
	}
	catch (std::invalid_argument& value)
	{
		std::cout << value.what() << std::endl;
		std::cout << "Check the initial .txt file!\n";
	}
	catch (std::out_of_range& value)
	{
		std::cout << value.what() << std::endl;
		std::cout << "Check the initial .txt file!\n";
	}
}

int file_size(std::string filename)
{
	std::ifstream fin(filename);

	if (fin.is_open())
	{
		int count = 0;
		std::string temp;

		while (getline(fin, temp))
		{
			++count;
		}
		if (count == 0)
		{
			std::cout << "No data processed. File \"" << filename << "\" is empty.\n";
			exit(EXIT_FAILURE);
		}
		if (fin.eof())
		{
			std::cout << "End of file reached;\n";
			std::cout << "Lines read: " << count << ";" << std::endl;
		} 
		else
		{
			std::cout << "Input terminated for unknown reason.\n";
			exit(EXIT_FAILURE);
		}

		fin.close();
		return count;
	}
	else
	{
		std::cout << "Could not open \"" << filename << "\";" << std::endl;
		std::cout << "Program terminating.\n";
		exit(EXIT_FAILURE);
	}
}

void read_file(std::string filename, Arrays* arr)
{
	std::ifstream fin(filename);

	if (fin.is_open())
	{
		static int fptr = 0;
		fin.seekg(fptr);
		std::string temp;

		fin >> temp;
		arr->size = check_data(temp);

		if (arr->size < 0) arr->size = -arr->size;

		arr->array = new int[arr->size]();

		static int count = 0;

		if ((count & 1) == 0) // even
		{
			for (int i = 0; i < arr->size; ++i)
			{
				fin >> temp;
				i == 0 ? *(arr->array + arr->size - 1) = check_data(temp) : *(arr->array + i - 1) = check_data(temp);
			}
		}
		else // odd
		{
			for (int i = 0; i < arr->size; ++i)
			{
				fin >> temp;
				i == arr->size - 1? *(arr->array + 0) = check_data(temp) : *(arr->array + i + 1) = check_data(temp);
			}
		}

		++count;
		fptr = static_cast<int>(fin.tellg());
		fin.close();
	}
	else
	{
		std::cout << "Could not open \"" << filename << "\";" << std::endl;
		std::cout << "Program terminating.\n";
		exit(EXIT_FAILURE);
	}
}

void write_file(std::string filename, const Arrays* const arr)
{
	std::ofstream fout(filename, std::ios_base::out | std::ios_base::app);

	if (fout.is_open())
	{
		fout << arr->size << std::endl;

		for (int i = 0; i < arr->size; ++i)
		{
			fout << arr->array[i] << (i == arr->size - 1 ? "\n" : " ");
		}

		fout.close();
	}
	else
	{
		std::cout << "Could not open \"" << filename << "\" file for output.\n";
		exit(EXIT_FAILURE);
	}
}

int main()
{
	std::string in_fname = "in.txt";
	std::string out_fname = "out.txt";

	int fsize = file_size(in_fname);
	Arrays* collection = new Arrays[fsize / 2];

	std::cout << "Arrays created: " << fsize / 2 << ";" << std::endl;

	for (int i = 0; i < fsize / 2; ++i)
	{
		read_file(in_fname, &collection[i]);
	}

	for (int i = 0; i < fsize / 2; ++i)
	{
		std::cout << "[" << (collection + i)->size << "] \t";
				
		for (int j = 0; j < (collection + i)->size; ++j)
		{
			std::cout << (collection + i)->array[j] << (j == (collection + i)->size - 1 ? "\n" : " ");
		}
	}

	for (int i = fsize / 2 - 1; i >= 0; --i)
	{
		write_file(out_fname, &collection[i]);
	}

	std::cout << "Output data written in \"" << out_fname << "\" file in the project folder.\n";

	delete[] collection;
	return 0;
}
