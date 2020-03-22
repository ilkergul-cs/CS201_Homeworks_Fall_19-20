#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct student_evaluation     // This is important when we need to store diffrent data in a vector
{
	string student_name;
	double total_grade;
	string student_id;
	int student_rank;
	
	student_evaluation()
	{
		total_grade = 0;
		student_rank = 0;			// this one is for assigning initial values to integer variables
	}
};

// The most key function in the program it reads the files and uses istream and growing the vectors when needed

int rank_order_function(vector<student_evaluation> & info_vector, ifstream & grade, ifstream & student_info)
{
	string name, parselling, grade_checker;
	string id1, id2; 
	double respected_constant, student_grade;
	int rank_limit;

	while(getline(student_info, parselling))
	{
		string full_name = "";
		student_evaluation elements;
		istringstream line_detector(parselling);
		if (!(parselling == ""))
		{
			line_detector >> id1;
			elements.student_id = id1;
			while ( line_detector >> name)
			{
				full_name += " " + name  ;
			}
			elements.student_name = full_name;

			while(getline(grade,grade_checker))
			{
				if(grade_checker == "***FINAL***") // constants is important
				{
					respected_constant = 0.3;
				}
				else if(grade_checker == "***MIDTERM***") // constants is important since different
				{
					respected_constant = 0.2;
				}
				else if(grade_checker == "***HOMEWORK***") // again the same importance
				{
					respected_constant = 0.1;
				}
				else
				{
					if(!(grade_checker == ""))
					{
						istringstream finder(grade_checker);
						finder >> id2;
						finder >> student_grade;
						if (id1 == id2)
						{
							elements.total_grade += student_grade * respected_constant;
						}
					}
				}
			}
			if(elements.total_grade > 0)
			{	
				info_vector.push_back(elements);
			}
			grade.clear();
			grade.seekg(0);
		}
	}
	rank_limit = info_vector.size();
	return rank_limit;
}

int compare_lastnames_function(const string & a, const string & b) // if the lastnames are important this function will help
{
	int lastindex1 = a.length()-1, lastindex2 = b.length() -1;
	int indexa, indexb;
	string lastname_a, lastname_b;
	for(int k= lastindex1; k >= 0; k--)
	{
		if(a[k] == ' ')
		{
			indexa = k+1;
			break;
		}
	}
	lastname_a = a.substr(indexa, lastindex1);
	for(int c= lastindex2; c >= 0; c--)
	{
		if(b[c] == ' ')
		{
			indexb = c+1;
			break;
		}
	}
	lastname_b = b.substr(indexb, lastindex2);
	if(lastname_a.compare(lastname_b) == 0)
	{
		return 1;
	}
	else if( lastname_a.compare(lastname_b) < 0)
	{
		return 5;
	}
	else 
	{
		return 10;
	}
}


void last_name_evaluation_function(vector<student_evaluation> & student_vector) // this function checks the order and make the evaluations if needed
{
	for(int i= 1; i < student_vector.size() ; i++)
	{
		student_evaluation temp;

		if(student_vector[i-1].total_grade == student_vector[i].total_grade)
		{
			if(compare_lastnames_function(student_vector[i-1].student_name, student_vector[i].student_name) == 10)
			{
				temp = student_vector[i-1];
				student_vector[i-1] = student_vector[i];
				student_vector[i] = temp;
			}
		}
	}
}

void insertion_and_ranking_sort(vector<student_evaluation> & hallettik)
{
	int k, j, location, number_of_elements = hallettik.size();
	for ( k= 1; k < number_of_elements ; k++)
	{
		student_evaluation total = hallettik[k];
		location = k;
		while ( 0 < location && total.total_grade > hallettik[location-1].total_grade)
		{
			hallettik[location] = hallettik[location - 1];
			location --;
		}
		hallettik[location] = total;
	}
	last_name_evaluation_function(hallettik);

	for(j = 0; j < number_of_elements; j++)
	{
		hallettik[j].student_rank = j + 1;
	}
}


void printing_struct_vector_components( const vector<student_evaluation> & sorted_vector, int wanted_rank)
{
	int k, index_number;
	int elements = sorted_vector.size();
	for(k = 0; k < elements ; k++)
	{
		if(sorted_vector[k].student_rank == wanted_rank)
		{
			index_number = k;
		}
	}
	cout << sorted_vector[index_number].student_rank << ", " << sorted_vector[index_number].student_id <<
		"," << sorted_vector[index_number].student_name << ", " << sorted_vector[index_number].total_grade << endl;
}

int main() // main function the other functions will be called
{
	vector <student_evaluation> info_holder;
	string grade_results, student_name;
	ifstream grade_text, student_info;
	int rank, rank_limit;

	cout << "Please enter a filename for Students Grades Results: ";
	cin >> grade_results;
	grade_text.open(grade_results);
	if(grade_text.fail())
	{
		cout << "Can not find the requested file. Terminating application ..." << endl;
	}
	else
	{
		cout << "Please enter a filename for Students Names : ";
		cin >> student_name;
		student_info.open(student_name);
		if (student_info.fail())
		{
			cout << "Can not find the requested file. Terminating application ..." << endl;
		}
		else
		{
			rank_limit = rank_order_function(info_holder, grade_text, student_info); // important for storing data
			insertion_and_ranking_sort(info_holder);								// important for ranking data

			cout << "Enter the rank you want to query (enter 0 to exit): ";
			cin >> rank ;
			while (rank != 0)
			{
				if (rank < 0 || rank > rank_limit)
				{
					cout << "Rank needs to be greater than 0 and smaller than " << rank_limit +1 << "!" << endl;
				}
				else
				{
												
					printing_struct_vector_components(info_holder, rank); 

				}
				cout << "Enter the rank you want to query (enter 0 to exit): ";
				cin >> rank ;
			}
			cout << "Exiting..." << endl;
		}
	}	
		
	return 0;
}
