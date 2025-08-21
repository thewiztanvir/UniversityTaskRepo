#include <stdio.h>
#include <string.h>

// ==========================
// Structure for Student Data
// ==========================
struct Student
{
    int id;              // Student ID
    char name[50];       // Student name
    char program[50];    // Program/department
    char blood_group[4]; // Blood group
    float cgpa;          // CGPA
};

// ==========================
// Global Variables
// ==========================
struct Student students[100]; // Array to store up to 100 students
int count = 0;                // Keeps track of current number of students

// ==========================
// Function Definitions
// ==========================

// Load data from binary file into memory
void loadFromFile()
{
    FILE *fptr = fopen("students_data.dat", "rb"); // Open file for reading (binary mode)
    if (fptr == NULL) // If file doesn't exist, just return
    {
        return;
    }
    // Read students into array and update count
    count = fread(students, sizeof(struct Student), 100, fptr);
    fclose(fptr);
};

// Save data from memory to binary file
void saveToFile()
{
    FILE *fptr = fopen("students_data.dat", "wb"); // Open file for writing (binary mode)
    if (fptr == NULL)
    {
        printf("Error saving file\n");
        return;
    }
    fwrite(students, sizeof(struct Student), count, fptr); // Write student records
    fclose(fptr);
};

// Check if a student ID already exists
int idExists(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            return 1; // Found
        }
    }
    return 0; // Not found
};

// Add a new student to the system
void addStudent()
{
    int id;
    printf("\nEnter ID Number: ");
    scanf("%d", &id);

    // Prevent duplicate IDs
    if (idExists(id))
    {
        printf("\nID number already exists!!!\n");
        return;
    }

    // Store student details
    students[count].id = id;
    printf("Enter Name: ");
    scanf(" %[^\n]", students[count].name); // Reads full line
    printf("Enter Program: ");
    scanf(" %[^\n]", students[count].program);
    printf("Enter Blood Group: ");
    scanf("%3s", students[count].blood_group);
    printf("Enter CGPA: ");
    scanf("%f", &students[count].cgpa);

    count++; // Increase total student count

    saveToFile(); // Save updated list
    printf("✅ Student Added Successfully\n");
};

// Display all students in a table format
void viewStudents()
{
    if (count == 0)
    {
        printf("No students to view\n");
        return;
    }

    printf("\n=== Student List ===\n");
    printf("---------------------------------------------------------------\n");
    printf("%-5s | %-20s | %-10s | %-10s | %-5s\n",
           "ID", "Name", "Program", "Blood", "CGPA");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-5d | %-20s | %-10s | %-10s | %-5.2f\n",
               students[i].id,
               students[i].name,
               students[i].program,
               students[i].blood_group,
               students[i].cgpa);
    }
    printf("---------------------------------------------------------------\n");
}

// Search and display a student by ID
void searchStudent()
{
    int id;
    printf("Enter Student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            // Print student details if found
            printf("\n=== Student Found ===\n");
            printf("---------------------------------------------------------------\n");
            printf("%-5s | %-20s | %-10s | %-10s | %-5s\n",
                   "ID", "Name", "Program", "Blood", "CGPA");
            printf("---------------------------------------------------------------\n");
            printf("%-5d | %-20s | %-10s | %-10s | %-5.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].program,
                   students[i].blood_group,
                   students[i].cgpa);
            printf("---------------------------------------------------------------\n");
            return;
        }
    }
    printf("❌ Student with ID %d not found.\n", id);
};

// Update student details by ID
void updateStudent()
{
    int id;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            // Show current record before updating
            printf("\nCurrent Record:\n");
            printf("---------------------------------------------------------------\n");
            printf("%-5s | %-20s | %-10s | %-10s | %-5s\n",
                   "ID", "Name", "Program", "Blood", "CGPA");
            printf("---------------------------------------------------------------\n");
            printf("%-5d | %-20s | %-10s | %-10s | %-5.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].program,
                   students[i].blood_group,
                   students[i].cgpa);
            printf("---------------------------------------------------------------\n");

            // Input new details
            printf("\nEnter new Name: ");
            scanf(" %[^\n]", students[i].name);
            printf("Enter new Program: ");
            scanf(" %[^\n]", students[i].program);
            printf("Enter new Blood Group: ");
            scanf("%3s", students[i].blood_group);
            printf("Enter new CGPA: ");
            scanf("%f", &students[i].cgpa);

            saveToFile(); // Save updated data
            printf("✅ Student updated successfully.\n");
            return;
        }
    }
    printf("❌ Student with ID %d not found.\n", id);
};

// Delete student by ID
void deleteStudent()
{
    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            // Show record before deleting
            printf("\nDeleting Record:\n");
            printf("---------------------------------------------------------------\n");
            printf("%-5s | %-20s | %-10s | %-10s | %-5s\n",
                   "ID", "Name", "Program", "Blood", "CGPA");
            printf("---------------------------------------------------------------\n");
            printf("%-5d | %-20s | %-10s | %-10s | %-5.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].program,
                   students[i].blood_group,
                   students[i].cgpa);
            printf("---------------------------------------------------------------\n");

            // Shift records to fill the deleted spot
            for (int j = i; j < count - 1; j++)
            {
                students[j] = students[j + 1];
            }
            count--; // Decrease total students
            saveToFile();
            printf("✅ Student deleted successfully.\n");
            return;
        }
    }
    printf("❌ Student with ID %d not found.\n", id);
};

// ==========================
// Main Function
// ==========================
int main()
{
    int choice;

    // Load saved data at program start
    loadFromFile();

    do
    {
        // Menu options
        printf("\n==== Student Record System ====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Handle user choice
        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            viewStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            updateStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            printf("Exiting... Data saved.\n");
            saveToFile();
            break;
        default:
            printf("❌ Invalid choice! Try again.\n");
        }
    } while (choice != 6); // Repeat until user exits

    return 0;
}
