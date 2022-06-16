#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;


void stringToLower(string& s)
{
    for (char& i : s)
    {
        i = tolower(i);
    }
}

void insertionSort(vector<string>& vec1, vector<int>& vec2);

void binarySearch(vector<string>& vec1, vector<int>& vec2, string name);


// takes a text file as an input with string and int value pairs / line
// example of 1 line in the text file: john 40
// string values will go into a string vector and int values will go into an int vector during the input file stream

int main(int argc, char* argv[])
{
    ifstream inputStream;
    string name;
    int age;
    string query;
    vector<string> nameVect;    // takes the string values
    vector<int> ageVect;        // takes the int values

    if (argc != 2)
    {
        cout << "Usage: ./program_name <filename>" << endl;
        exit(-1);
    }

    inputStream.open(argv[1]);
    while (inputStream >> name)
    {
        stringToLower(name);
        nameVect.push_back(name);
        inputStream >> age;
        ageVect.push_back(age);
    }
    inputStream.close();

    insertionSort(nameVect, ageVect);

    do
    {
        cout << "Enter a name to be searched in the database (or type 'quit'): ";
        cin >> query;
        stringToLower(query);
        if (query == "quit")
        {
            break;
        }
        binarySearch(nameVect, ageVect, query);
    } while (query != "quit");

    return 0;

}


void insertionSort(vector<string>& vec1, vector<int>& vec2)
{
    string temp_name;
    int temp_age;
    string insertion_item;
    int sorted_position;

    //insertion sort
    for (int i = 0; i < vec1.size(); i++)
    {
        //set the item position to be inserted into sorted area 
        insertion_item = vec1[i];

        //set the rightmost position of sorted area
        sorted_position = i - 1;

        //swapping loop 
        while (sorted_position >= 0 && vec1[sorted_position] > insertion_item)
        {
            //Swap name vector
            temp_name = vec1[sorted_position];
            vec1[sorted_position] = vec1[sorted_position + 1];
            vec1[sorted_position + 1] = temp_name;

            //Swap age vector to match the name vector
            temp_age = vec2[sorted_position];
            vec2[sorted_position] = vec2[sorted_position + 1];
            vec2[sorted_position + 1] = temp_age;

            //Move our position one to the left inside the sorted area 
            sorted_position--;
        }
    }
}

void binarySearch(vector<string>& vec1, vector<int>& vec2, string name)
{
    int low = 0;
    int high = vec1.size() - 1;
    int middle;
    while (low <= high)
    {
        middle = (low + high) / 2;
        if (name > vec1[middle])
        {
            low = middle + 1;
        }
        else if (name < vec1[middle])
        {
            high = middle - 1;
        }
        else
        {
            cout << "The age for " << name << " is " << vec2[middle] << endl;
            return;
        }
    }
    cout << "The name " << name << " does not exist in the database" << endl;
}
