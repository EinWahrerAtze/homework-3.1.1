#include <iostream>
#include <fstream>
#include <vector>

void read_file(std::vector<int>* const arr, const char filename[])
{
	std::ifstream fin(filename);

	if (fin.is_open())
	{
		int n = 0;
		bool odd = false;

		while (fin.good() && fin >> n)
		{
			if (!odd)
			{
				arr->insert(arr->begin(), n);

				for (int i = 0; i < arr->front(); ++i)
				{
					fin >> n;
					i == 0 ? arr->insert(arr->begin() + 1, n) : arr->insert(arr->begin() + i, n);
				}

				odd = true;
			}
			else
			{
				arr->insert(arr->begin(), n);

				for (int i = 0; i < arr->front(); ++i)
				{
					fin >> n;
					i == arr->front() - 1 ? arr->insert(arr->begin() + 1, n) : arr->insert(arr->begin() + 1 + i, n);
				}

				odd = false;
			}
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

		if (arr->begin() == arr->end())
		{
			std::cout << "No data to processed. File is empty.\n";
		}
		else
		{
			std::cout << "Characters read: " << arr->size() << ".\n";
		}

		fin.close();
	}
	else
	{
		std::cout << "Could not open file \"" << filename << "\".\n";
		std::cout << "Program terminating.\n";
		exit(EXIT_FAILURE);
	}
}

void write_file(const std::vector<int>* const arr, const char filename[])
{
	std::ofstream fout(filename);

	if (fout.is_open())
	{

		int mark = 0;

		for (int i = 0; i < arr->size(); ++i)
		{
			if (i == mark)
			{
				fout << arr->at(i) << "\n";
				mark += arr->at(i) + 1;
			}
			else
			{
				fout << arr->at(i) << (i == mark - 1 ? "\n" : " ");
			}
		}

		std::cout << "Output data successfully written in \"" << filename << "\" file.\n";
		fout.close();
	}
	else
	{
		std::cout << "Could not open file \"" << filename << "\" for output.\n";
		std::cout << "Program terminating.\n";
		exit(EXIT_FAILURE);
	}
}

int main()
{
	char in_filename[] = "in.txt";
	char out_filename[] = "out.txt";
	std::vector<int> arr;

	read_file(&arr, in_filename);

	int mark = 0;

	for (int i = 0; i < arr.size(); ++i)
	{
		if (i == mark)
		{
			std::cout << "[" << arr.at(i) << "]" << "\t";
			mark += arr.at(i) + 1;
		}
		else
		{
			std::cout << arr.at(i) << (i == mark - 1? "\n" : " ");
		}
	}

	write_file(&arr, out_filename);
	return 0;
}
