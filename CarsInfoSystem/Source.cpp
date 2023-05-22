#include <iostream>
#include <cstring>
using namespace std;
struct car
{
	char brand[30];
	char model[50];
	int year;
	int mileage;
	double price;
};

void add_car(const char* f_name);
void show_all(const char* f_name);
void find_by_brand(const char* f_name);
void find_by_year(const char* f_name);
void find_by_mileage(const char* f_name);
void find_by_price(const char* f_name);
void update_by_position(const char* f_name);
void delete_by_position(const char* f_name);
void empty_fun(const char* f_name) {}


int main()
{
	const char* path = "D:\\examples\\car_store.dat";
	void (* menu[])(const char* f_name) = { empty_fun, add_car, show_all, find_by_brand,
						find_by_year, find_by_mileage, find_by_price, update_by_position
					, delete_by_position };
	
	int selected_id{ 0 };
	for(;;)
	{
		system("cls");
		cout << "Select menu option:\n";
		cout << "Add new car - \t\t1\n";
		cout << "Print all cars - \t\t2\n";
		cout << "Find cars by brand - 3\n";
		cout << "Find cars by year - 4\n";
		cout << "Find cars by mileage - 5\n";
		cout << "Find cars by price - 6\n";
		cout << "Update car - 7\n";
		cout << "Delete car - 8\n";
		cout << "Quit - 9\n";
		cin >> selected_id;
		cin.get();
		if (selected_id == 9) break;
		menu[selected_id](path);
	}
}

car input_car(const char* prompt)
{
	car car;
	cout << prompt<<":\n";
	cout << "brand: ";
	cin.getline(car.brand, 30);
	cout << "model: ";
	cin.getline(car.model, 50);
	cout << "year: ";
	cin >> car.year;
	cout << "mileage: ";
	cin >> car.mileage;
	cout << "price: ";
	cin >> car.price;
	return car;
}

void add_car(const char* f_name)
{
	FILE* f;
	car car = input_car("Enter data for new car");
	fopen_s(&f, f_name, "a+b");
	fwrite(&car, sizeof(car), 1, f);
	fflush(f);
	fclose(f);
}

void print_car(car c)
{
	cout << c.brand << " " << c.model << endl;
	cout << "manufactured: " << c.year << endl;
	cout << c.mileage << " miles\n";
	printf("price $%.2f\n", c.price);
	cout << endl;
}

void show_all(const char* f_name)
{
	FILE* f;
	fopen_s(&f, f_name, "rb");
	car car;
	cout << endl;
	for (;;)
	{
		fread(&car, sizeof(car), 1, f);
		if (feof(f)) break;
		print_car(car);
	}
	fclose(f);
	system("pause");
}

void find_by_brand(const char* f_name)
{
	FILE* f;
	fopen_s(&f, f_name, "rb");
	car car;
	char brand[30];
	cout << "car brand >>";
	cin.getline(brand, 30);
	cout << endl;
	for (;;)
	{
		fread(&car, sizeof(car), 1, f);
		if (feof(f)) break;
		if(strcmp(car.brand, brand)==0)
		{
			print_car(car);
		}
	}
	fclose(f);
	system("pause");
}

void find_by_year(const char* f_name)
{
	FILE* f;
	fopen_s(&f, f_name, "rb");
	car car;
	int min_year, max_year;
	cout << "years diapason >>";
	cin >> min_year;
	cin >> max_year;
	cout << endl;
	for (;;)
	{
		fread(&car, sizeof(car), 1, f);
		if (feof(f)) break;
		if (car.year >= min_year && car.year <= max_year)
		{
			print_car(car);
		}
	}
	fclose(f);
	system("pause");
}

void find_by_mileage(const char* f_name)
{
}

void find_by_price(const char* f_name)
{
}

void update_by_position(const char* f_name)
{
	FILE* f;
	fopen_s(&f, f_name, "rb");
	car car;
	int id {};
	cout << endl;
	for (;;)
	{
		fread(&car, sizeof(car), 1, f);
		if (feof(f)) break;
		cout << (++id) << "\t";
		print_car(car);
	}
	fclose(f);

	int id_to_update;
	cout << "select car id to change : ";
	cin >> id_to_update;
	cin.get();
	car = input_car("Enter new data for car");
	
	fopen_s(&f, f_name, "r+b");
	fseek(f, (id_to_update - 1) * sizeof(car), SEEK_SET);
	fwrite(&car, sizeof(car),1, f);
	fclose(f);
}

void delete_by_position(const char* f_name)
{
	FILE* f;
	fopen_s(&f, f_name, "rb");
	car car;
	int id{};
	cout << endl;
	for (;;)
	{
		fread(&car, sizeof(car), 1, f);
		if (feof(f)) break;
		cout << (++id) << "\t";
		print_car(car);
	}
	fclose(f);

	int id_to_del;
	cout << "select car id to delete : ";
	cin >> id_to_del;
	
	FILE* f_tmp;
	fopen_s(&f_tmp, "tmp_file", "wb");
	fopen_s(&f, f_name, "rb");
	for (size_t i = 1; i < id_to_del; i++)
	{
		fread(&car, sizeof(car), 1, f);
		fwrite(&car, sizeof(car), 1, f_tmp);
	}
	fseek(f, sizeof(car), SEEK_CUR);
	for (;;)
	{
		fread(&car, sizeof(car), 1, f);
		if (feof(f))break;
		fwrite(&car, sizeof(car), 1, f_tmp);
	}
	fclose(f_tmp);
	fclose(f);

	fopen_s(&f_tmp, "tmp_file", "rb");
	fopen_s(&f, f_name, "wb");
	for (;;)
	{
		fread(&car, sizeof(car), 1, f_tmp);
		if (feof(f_tmp))break;
		fwrite(&car, sizeof(car), 1, f);
	}
	fclose(f_tmp);
	fclose(f);
}
