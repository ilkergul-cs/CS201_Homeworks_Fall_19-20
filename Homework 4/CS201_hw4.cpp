#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

// I added sstream and fstream libraries to use ifstream and istringstream

using namespace std;

// This function helps to check whether route file is opened or not

bool routes_file_checker(ifstream & input1, string  filename1)
{
	input1.open(filename1);
	while (input1.fail())
	{
		cout << "cannot open routes database file" << endl;
		cout << "Please enter a filename for route database: ";
		cin >> filename1;
		input1.clear();
		input1.open(filename1.c_str());
	}
	return true;
}

// This function helps to check whether time file is opened or not

bool times_file_checker(ifstream & input2, string filename2)
{
	input2.open(filename2);
	while (input2.fail())
	{
		cout << "cannot open times database file" << endl;
		cout << "Please enter a filename for time database: ";
		cin >> filename2;
		input2.clear();
		input2.open(filename2.c_str());
	}
	return true;
}

//This function helps to check whether character are in the expected range in ascii table or not

bool char_checker(char analog)
{
	if ( analog <= '9' && analog >= '0')
		return true;
	else
		return false;

}

// To check the length of the time input to determine validation of the given input to use in our code

bool length_checker(string analog)
{
	if(analog.length() == 5 && char_checker(analog[0]) && char_checker(analog[1]) && analog[2] == ':' && char_checker(analog[3]) && char_checker(analog[4]))
	{
		if ( analog.substr(0,2) > "23" || analog.substr(3,2) > "59")
		{
			return false;
		}
		return true;
	}
	return false;
}

// This one is the most important function in the code
// it helps user to read the the txt file and use parse method to find the wanted information

void printing_operation(ifstream & route, ifstream & time, string departure, string ticket_time)
{
	string saat, yer, code1, code2, start, end, bus_time;
	while (getline(route, yer))
	{
		istringstream solver(yer);
		solver >> code1;
		solver >> start;
		solver >> end;

		if( start == departure)
		{
			while(getline(time, saat))
			{
				istringstream finder(saat);
				finder >> code2;
				finder >> bus_time;
				if(code1 == code2)
				{
					if(ticket_time <= bus_time)
					{
						
						cout << departure <<" "<< end <<" "<< bus_time << endl;
					}
				}
			}
			time.clear();
			time.seekg(0);
		}
		
	}
	route.clear();
	route.seekg(0);

}

// This is the main function in which defined functions are called
int main()
{
	string file_name_for_route, file_name_for_time, departure_location, start_time;

	ifstream routes_of_the_bus;
	ifstream times_of_the_bus;

	cout << "Please enter a filename for route database: ";
	cin >> file_name_for_route;
	if (routes_file_checker(routes_of_the_bus, file_name_for_route))
	{
		cout << "Please enter a filename for time database: ";
		cin >> file_name_for_time;
		if(times_file_checker(times_of_the_bus, file_name_for_time))
		{
			cout<<"Please enter departure location: ";
			cin>> departure_location;
			while (departure_location != "EXIT")
			{
				cout<<"Please enter start time of travel: ";
				cin>> start_time;
				while(length_checker(start_time) == false)
				{
					cout<<"Time is not in correct format"<<endl <<"Please enter start time of travel: ";
					cin>> start_time;
				}
				cout << "The search results are: \n";
				printing_operation(routes_of_the_bus ,times_of_the_bus, departure_location, start_time);
				
				cout<<"Please enter departure location: ";
				cin>> departure_location;

			}
		}
	}

	return 0;
}

// End of homework 4
// Yours sincerely
// ilker
