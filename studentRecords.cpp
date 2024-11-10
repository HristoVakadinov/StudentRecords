#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

class Date {
private:
    int day, month, year;

public:
    Date() : day(1), month(1), year(2000) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    void setDate(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
    }

    int calculateAge() const {
        time_t t = time(0);
        tm *now = localtime(&t);
        int age = (now->tm_year + 1900) - year;
        if (month > (now->tm_mon + 1) || (month == (now->tm_mon + 1) && day > now->tm_mday))
            age--;
        return age;
    }
};

class Student {
private:
    string name;
    int facultyNumber;
    Date birthDate;
    double averageGrade;

public:
    Student() : name(""), facultyNumber(0), birthDate(), averageGrade(0.0) {}
    Student(const string &n, int fn, Date bd, double avg)
        : name(n), facultyNumber(fn), birthDate(bd), averageGrade(avg) {}

    string getName() const { return name; }
    int getFacultyNumber() const { return facultyNumber; }
    double getAverageGrade() const { return averageGrade; }
    int getAge() const { return birthDate.calculateAge(); }

    friend ostream &operator<<(ostream &out, const Student &s) {
        out << "Име: " << s.name << ", Факултетен номер: " << s.facultyNumber
            << ", Възраст: " << s.getAge() << ", Среден успех: " << s.averageGrade;
        return out;
    }
};

Student findTopStudent(const vector<Student> &students) {
    Student topStudent = students[0];
    for (const Student &s : students) {
        if (s.getAverageGrade() > topStudent.getAverageGrade()) {
            topStudent = s;
        }
    }
    return topStudent;
}

void writeToFile(const vector<Student> &students, const string &filename, const Student &topStudent) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "Студенти между 18 и 26 години:\n";
        for (const Student &s : students) {
            file << s << endl;
        }
        file << endl; 
        file << "Студент с най-висок успех:\n" << topStudent << endl; 
        file.close();
    } else {
        cerr << "Не може да се отвори файлът за запис.\n";
    }
}

int main() {
    vector<Student> students = {
        Student("Иван Иванов", 12345, Date(15, 5, 2000), 5.50),
        Student("Мария Петрова", 12346, Date(12, 11, 1998), 5.80),
        Student("Георги Георгиев", 12347, Date(7, 8, 2003), 4.90),
        Student("Петя Димитрова", 12348, Date(25, 3, 1993), 5.20),
        Student("Стефан Стефанов", 12349, Date(30, 9, 2001), 5.00),
        Student("Марин Стефанов", 12350, Date(10, 2, 1997), 5.60),
        Student("Десислава Веселинова", 12351, Date(20, 6, 2002), 4.70),
        Student("Ивелин Михайлов", 12352, Date(5, 12, 1999), 5.40),
        Student("Силвия Караиванова", 12353, Date(18, 4, 1995), 5.10),
        Student("Кирил Кирилов", 12354, Date(22, 10, 2000), 5.70)
    };

    cout << "Студенти между 18 и 26 години:\n";
    for (const Student &s : students) {
        if (s.getAge() >= 18 && s.getAge() <= 26) {
            cout << s << endl;
        }
    }

    Student topStudent = findTopStudent(students);
    cout << "\nСтудент с най-висок успех:\n" << topStudent << endl;

    writeToFile(students, "students.txt", topStudent);

    return 0;
}