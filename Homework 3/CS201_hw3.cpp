#include <iostream>
#include <string>

using namespace std;

// I am creating a void function to detect whether there is a match index between source and search

void substring_finder_in_source_string(string source, string search)
{
	int i = 0;
	int j = 0;
	int found_index = 0;
	int no_match = 0;
	string found_string = "";
	int search_length = search.length();
	
	cout << "For the source word \""<< source << "\" and search word \""<< search << "\"," ;
	
	// with this for loop I will detect the matches if there is any

	for (i=0; i < source.length() - search_length + 1 ; i++)
	{
		string submatch = source.substr(i, search_length);
		bool is_match_with_string = true;

		for (j=0; j < submatch.length(); j++)
		{
			if (search[j] == submatch[j] || search[j] == '?' )
			{
				if (j == 0)
				{
					found_index = i;
				}
				found_string += submatch[j];
				continue;
			}
			else
			{
				is_match_with_string = false;
				found_string = "";
				break;
			}
		}
		if (is_match_with_string)
		{
			cout << endl << "\"" << found_string << "\" has been found at index " << found_index;
			found_index = 0;
			found_string = "";
			
			no_match +=1;
		}
	}
	// I count matches with no match if it is zero then I should display something different

	if (no_match == 0)
	{
		cout << " no match has been found.";
	}
	cout << endl << endl;
}

// This bool func will help me to check pre-conditions of being a valid search string with question marks

bool question_mark_checker_for_search(string search_source)
{
	int i;
	int question_mark_count = 0;
	
	// checking question count to decide the search string is valid or not is compulsory

	bool is_all_question_marks = false;
	for (i=0; i < search_source.length(); i++)
	{
		if ( search_source[i] == 63)
		{
			question_mark_count += 1;
		}
	}
	if ( question_mark_count == search_source.length())
	{
		is_all_question_marks = true;
	}
	return is_all_question_marks;
}

// This bool func will help me to check pre-conditions of being a valid source string

bool input_format_checker_for_source(string chosen)
{
	int i;
	bool is_valid_source_format = true;
	int source_length = chosen.length(); 
	if (source_length == 0)
	{
		is_valid_source_format = false;
	}
	else
	{
		for ( i= 0; i < source_length; i++)
		{
			if (char(chosen[i]) < 97 || char(chosen[i]) > 122 )
			{
				is_valid_source_format = false;
				break;
			}
		}	
	}
	
	return is_valid_source_format;
}

// This bool func will help me to check pre-conditions of being a valid search string

bool input_format_checker_for_search(string chosen, int source_length)
{
	int i;
	bool is_valid_search_format = true;
	int search_length = chosen.length(); 
	if (search_length == 0 || search_length > source_length || question_mark_checker_for_search(chosen))
	{
		is_valid_search_format = false;
	}
	else
	{
		for ( i= 0; i < search_length; i++)
		{
			if ((char(chosen[i]) < 97 || char(chosen[i]) > 122 )&& char(chosen[i]) != 63)
			{
				is_valid_search_format = false;
				break;
			}
		}	
	}
	
	return is_valid_search_format;
}

// This one will be my main void function to use in main function

void main_checker_func()
{
	string chosen_option_by_user, source_word, search_word;

	cout << "Enter your choice and string: ";
	cin >> chosen_option_by_user ;

	// This while loop will help me to run the code by checking preference option

	while (chosen_option_by_user != "3")
	{
		if ( chosen_option_by_user == "1" || chosen_option_by_user == "2" ) 
		{
			if (chosen_option_by_user == "1")
			{
				cin >> source_word;
				if (input_format_checker_for_source(source_word) == false)
				{
					cout << "Wrong input format! Try again.\n\n" ;
					
				}
				else 
				{
					cout << "Source word has been changed to \"" << source_word << "\"\n\n" ;
				}
			}
			else if (chosen_option_by_user == "2")
			{
				cin >> search_word;
				if (input_format_checker_for_search(search_word, source_word.length()) == false)
				{
					cout << "Wrong input format! Try again.\n\n" ;
					
				}
				else 
				{
					substring_finder_in_source_string(source_word, search_word);
				}

			}
			cout << "Enter your choice and string: ";
			cin >> chosen_option_by_user ;
		}					
		else
		{
			cout << "Choice can be 1, 2 or 3! Try again.\n\n" ; 
			cout << "Enter your choice and string: ";
			cin >> chosen_option_by_user ;
		}
	}
	cout << "See you!" << endl;
}

int main)
{
	cout << "This program searches a search string in a source string with the option of wildcards.\n\n" ;
	cout << "Example inputs with their meaning in parantheses:" << endl;
	cout << "1 thislectureisawesome (to enter a new source string)" << endl
		<< "2 lecture (to enter a new source string)" << endl
		<< "2 t?r? (to enter a source string with wildcards)  " << endl
		<< "3 (to exit the program)\n\n" ;

	main_checker_func();
	
	return 0;
}

void main18()
{
	int X_coordinate, Y_coordinate;
	cout << "Please enter starting coordinates, first row X then column Y: " ;
	cin >> X_coordinate >> Y_coordinate;
	while (X_coordinate >= 0 && X_coordinate < Matrix.size() && Y_coordinate >= 0 && Y_coordinate < Matrix[0].size()) 
	{
		cout << "Invalid Coordinates" << endl << endl << "Please enter starting coordinates, first row X then column Y: " ;
		cin >> X_coordinate >> Y_coordinate;
	}

	
}

// end of homework 3
// yours sincerely,
// ilker
