#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 

using namespace std;


struct Course {
    string name;
    string grade;
    double creditHours;
    double gradePoint;
};


double convertGradeToPoint(string grade) {
    for (auto &c : grade) c = toupper(c); 
    if (grade == "A") return 4.0;
    if (grade == "A-") return 3.7;
    if (grade == "B+") return 3.3;
    if (grade == "B") return 3.0;
    if (grade == "B-") return 2.7;
    if (grade == "C+") return 2.3;
    if (grade == "C") return 2.0;
    if (grade == "C-") return 1.7;
    if (grade == "D+") return 1.3;
    if (grade == "D") return 1.0;
    return 0.0; 
}

int main() {
    int numCourses;
    double totalCredits = 0.0;
    double totalGradePoints = 0.0;
    vector<Course> courses;

    cout << "--- C++ CGPA Calculator ---" << endl;
    cout << "Enter the number of courses: ";
    cin >> numCourses;

    for (int i = 0; i < numCourses; ++i) {
        Course c;
        cout<<"\nCourse " << i + 1 << " details:"<< endl;
        
        cout<<"  Enter Grade (e.g., A, B+, C): ";
        cin>>c.grade;
        
        cout<<"  Enter Credit Hours: ";
        cin>>c.creditHours;

        c.gradePoint = convertGradeToPoint(c.grade);
        
      
        totalCredits += c.creditHours;
        totalGradePoints += (c.gradePoint * c.creditHours);
        
        courses.push_back(c);
    }


    double cgpa = (totalCredits > 0) ? (totalGradePoints / totalCredits) : 0.0;

   
    cout<<"\n" << string(35, '=')<< endl;
    cout<<left << setw(10)<< "Course"<< " | " << setw(8) << "Grade" << " | " << "Credits" << endl;
    cout<<string(35, '-')<< endl;

    for (int i = 0; i < courses.size(); ++i) {
        cout << left << setw(10) << (i + 1) 
             << " | " << setw(8) << courses[i].grade 
             << " | " << courses[i].creditHours << endl;
    }

    cout<<string(35, '=') << endl;
    cout<<fixed << setprecision(2); 
    cout<<"Total Credits: " << totalCredits << endl;
    cout<<"Final CGPA:    " << cgpa << endl;
    cout<<string(35, '=') << endl;

    return 0;
}