#include <iostream>
#include <fstream>
using namespace std; 

#pragma region Lab 3
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

#pragma endregion

#pragma region Fixed Length
struct student {
    int Id;
    char Name[20];
    float Price;
    int Qun;
};

void AddStudent(fstream& file) {
    student s;
    cout << "Enter student data:\n";
    cout << "ID: ";
    cin >> s.Id;
    cin.ignore();
    cout << "Name: ";
    cin.getline(s.Name, 20);
    cout << "Price: ";
    cin >> s.Price;
    cout << "Quantity: ";
    cin >> s.Qun;

    // Move to end of file (append)
    file.seekp(0, ios::end);
    file.write((char*)&s, sizeof(s));
}

// Function to update by **record index** (0-based)
void UpdateByIndex(fstream& file, int index) {
    student s;

    // Go to correct position
    file.seekg(index * sizeof(s), ios::beg);
    file.read((char*)&s, sizeof(s));

    // Check if record is valid
    if (s.Id == -1) {
        cout << "Record not found or deleted.\n";
        return;
    }

    cout << "Current data:\n";
    cout << "ID: " << s.Id << "\nName: " << s.Name << "\nPrice: " << s.Price << "\nQuantity: " << s.Qun << endl;

    // Update record
    cout << "Enter new data:\n";
    cin.ignore();
    cout << "Name: ";
    cin.getline(s.Name, 20);
    cout << "Price: ";
    cin >> s.Price;
    cout << "Quantity: ";
    cin >> s.Qun;

    // Move back to correct write position
    file.seekp(index * sizeof(s), ios::beg);
    file.write((char*)&s, sizeof(s));

    cout << "Record updated successfully.\n";
}

// Function to delete by **record index** (logical delete)
void DeleteByIndex(fstream& file, int index) {
    student s;

    // Go to correct position
    file.seekg(index * sizeof(s), ios::beg);
    file.read((char*)&s, sizeof(s));

    // Check if record is valid
    if (s.Id == -1) {
        cout << "Record not found or already deleted.\n";
        return;
    }

    cout << "Current data:\n";
    cout << "ID: " << s.Id << "\nName: " << s.Name << "\nPrice: " << s.Price << "\nQuantity: " << s.Qun << endl;

    // Logical delete by setting Id to -1
    s.Id = -1;

    file.seekp(index * sizeof(s), ios::beg);
    file.write((char*)&s, sizeof(s));

    cout << "Record deleted successfully.\n";
}



#pragma endregion



int main()
{
    Writing_in_File();
    Reading_from_File();
}


