#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

struct student{
    string name;
    vector<int> grade;
};

double grade_Average(const vector<int>& grade);
int findBestStudent(const vector<student>& s); //finds the index

int main()
{
    ifstream input;
    ofstream output;
    input.open("C:\\dev\\cpp_Projects\\Student_Grade_Analyzer\\duomenys.txt");
    output.open("Output_data.txt");

    vector<student> s;
    int gradeCount; // first number after the name indicates the grade count (inside the input file)
    student temp;

    if(input.fail())
    {
        output << "Input file not found." << endl;
        return 0;
    }
    else
    {
        while(input >> temp.name >> gradeCount)
        {
            temp.grade.clear();
            for(int i = 0; i < gradeCount; i++)
            {
                int g;
                input >> g;
                temp.grade.push_back(g);
            }
            s.push_back(temp);
        }
            output << fixed << setprecision(2);

            for(int i = 0; i < s.size(); i++)
            {
                output << s[i].name << " ";

                for(int j = 0; j < s[i].grade.size(); j++)
                {
                    output << s[i].grade[j] << " ";
                }
                double avg = grade_Average(s[i].grade);
                if(avg == -1)
                {
                    output << "The student has no grades. Please review the input file." << endl;
                }
                else
                {
                    output << "| Avg: " << avg << endl;
                }
            }

        int bestStudent = findBestStudent(s);
        if (bestStudent == -2)
        {
            output << "There are no student data." << endl;
        }
        else
        {
            double maxAverage = grade_Average(s[bestStudent].grade);

            output << "\nBest student is " << s[bestStudent].name << ". Grade average: " << maxAverage << endl;
        }
    }

    input.close();
    output.close();
    return 0;
}

double grade_Average(const vector<int>& grade)
{
    if(grade.empty())
    {
        return -1;
    }
    double sum = 0;
    for (int i = 0;i < grade.size(); i++)
    {
        sum += grade[i];
    }
    return sum / grade.size();
}
int findBestStudent(const vector<student>& s)
{
    if(s.empty())
    {
        return -2;
    }
    double maxAverage = grade_Average(s[0].grade);
    int bestIndex = 0;
    for(int i = 1; i < s.size(); i++)
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
