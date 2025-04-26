#include <iostream>
#include <fstream>
using namespace std; 


void Writing_in_File() {
    ofstream file; // 1. Create an output file stream object.

    // 2. Open the file for writing (creates it if it doesn't exist).
    // If "sample.txt" already exists, it will be overwritten.
    file.open("sample.txt");

    if (!file.is_open()) { // 3. Good practice: check if file was opened.
        //cout << "Failed to open file for writing!" << endl;
        return;
    }

    char Line[] = "Hello World"; // 4. A C-style string (char array).
    string text = "Khaled's file"; // 5. A C++ string.

    file << Line << endl;   // 6. Write the char array to the file.
    file << "23" << endl;   // 7. Write a number (as a string) to the file.
    file << text << endl;   // 8. Write the C++ string to the file.

    file.close(); // 9. Always close the file when done.
}


void Reading_from_File() {
    ifstream file("sample.txt"); // 1. Open the file. (Missing file name!)

    if (!file.is_open()) { // 2. Always check if the file was opened successfully.
        //cout << "Failed to open file!" << endl;
        return;
    }

    file.seekg(0, ios::end); // 3. Use ios::end, not just "end".
    int size = file.tellg();  // 4. Get the file size in bytes.
    file.seekg(0, ios::beg);  // 5. Important! Reset position to the beginning.

    char* Line = new char[size + 1]; // 6. +1 to have space for '\0' (null terminator).

    // 7. Read the entire file into Line.
    file.getline(Line, size);
    Line[size] = '\0'; // 8. Null-terminate the character array manually.

    string text = "";
    text = Line; // 9. Now you can assign Line to text directly.
    cout << Line << endl;
    cout << text << endl;

    delete[] Line; // 10. Important! Free the allocated memory.
    file.close();  // 11. Close the file.
}



int main()
{
    Writing_in_File();
    Reading_from_File();
}


