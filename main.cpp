#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct student{
    string name;
    int grade[4];
};

double grade_Average(int grade[4]);
int findBestStudent(student s[],int n); //finds the index

int main()
{
    ifstream input;
    ofstream output;
    input.open("C:\\dev\\cpp_Projects\\Student_Grade_Analyzer\\duomenys.txt");
    output.open("Output_data.txt");

    student s[100];
    int n = 0;

    if(input.fail())
    {
        output << "Input file not found." << endl;
        return 0;
    }
    else
    {
        while(n < 100 && input >> s[n].name)
        {
            for(int i = 0; i < 4; i++)
            {
                if(!(input >> s[n].grade[i]))
                {
                    output << "The input file is not correct. Ensure that only 4 grades are entered per student. Missing or Invalid grade for student: " << s[n].name << endl;
                    return 0;
                }
            }
            n++;
        }
        if( n == 0)
        {
            output << "No student data found." << endl;
            return 0;
        }
            output << fixed << setprecision(2);
            for(int i = 0; i < n; i++)
            {
                output << s[i].name << " ";

                for(int j = 0; j < 4; j++)
                {
                    output << s[i].grade[j] << " ";
                }
                output << "| Avg: " << grade_Average(s[i].grade) << endl;
            }

        int bestStudent = findBestStudent(s,n);
        double maxAverage = grade_Average(s[bestStudent].grade);

        output << "\nBest student is " << s[bestStudent].name << ". Grade average: " << maxAverage << endl;
    }

    input.close();
    output.close();
    return 0;
}

double grade_Average(int grade[4])
{
    double sum = 0;
    for (int i = 0;i < 4; i++)
    {
        sum += grade[i];
    }
    return sum / 4;
}
int findBestStudent(student s[],int n)
{
    double maxAverage = grade_Average(s[0].grade);
    int bestIndex = 0;
    for(int i = 1; i < n; i++)
    {
        double currentAverage = grade_Average(s[i].grade);
        if(currentAverage > maxAverage)
        {
            maxAverage = currentAverage;
            bestIndex = i;
        }
    }
    return bestIndex;
}
