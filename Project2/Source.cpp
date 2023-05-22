#include <iostream>
using namespace std;
int main()
{
	const char* path = "D:\\examples\\b_data.txt";
	
	FILE* f;
	if (fopen_s(&f, path, "wb") != NULL)
		cout << "The file cannot be opened";
	else
	{
		fputs("String 1\n", f);
		fputs("String 2\n", f);
		fputs("String 3\n", f);
	}
	

	fclose(f);

	char buff[255];

	if (fopen_s(&f, path, "r") != NULL)
		cout << "The file cannot be opened";
	else
	{
		while (true)
		{
			fgets(buff, 255, f);
			if (feof(f)) break;
			cout << buff <<endl;
		}
		
	}
	fclose(f);

}