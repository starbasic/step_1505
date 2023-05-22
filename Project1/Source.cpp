#include <iostream>
using namespace std;
int main()
{
	const char* path = "D:\\examples\\b_data.dat";
	const int n = 10;
	int arr[n], a;
	FILE* f;
	if (fopen_s(&f, path, "w") != NULL)
		cout << "The file cannot be opened";
	else
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] = i + 1;
		}
		fwrite(&arr, sizeof(arr), 1, f);
		fclose(f);
	}
	if (fopen_s(&f, path, "r") != NULL)
		cout << "The file cannot be opened";
	else
	{
		for (int i = 0; i < n; i++)
		{
			fread(&a, sizeof(int), 1, f);
			cout << a << "\n";
		}
		

			fclose(f);
	}
	if (fopen_s(&f, path, "r") != NULL)
		cout << "The file cannot be opened";
	else
	{
		fread(&a, sizeof(int), 1, f);
		cout << a;
		fclose(f);
	}
	return 0;
}