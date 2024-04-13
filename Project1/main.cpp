#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <random>

std::string const inputFile = "input.txt";
std::string const outputf = "output.txt";
class QuadEquation {
    double a;
    double b;
    double c;
    std::vector<double> roots;
public:
    QuadEquation(double const A, double const B, double const C) {
        a = A;
        b = B;
        c = C;
    }
    std::vector<double> solve() {
        if (a == 0.0) {
            if (b != 0.0) {
                roots.push_back(-c / b);
            }
        }
        else {
            double D;
            D = b * b - 4.0 * a * c;
            if (D > 0.0) {
                roots.push_back((-b - sqrt(D)) / (2.0 * a));
                roots.push_back((-b + sqrt(D)) / (2.0 * a));
            }
            else if (D == 0.0) {
                roots.push_back(-b / (2.0 * a));
            }
        }
        return roots;
    }
    std::vector<double> getRoots() {
        return roots;
    }
    double getA() { return a; };
    double getB() { return b; };
    double getC() { return c; };
};

class Student {
protected:
    std::string surname;
    std::vector<QuadEquation> read(const std::string& inputFile) {
        std::vector<QuadEquation> equations;
        std::ifstream file(inputFile);

        double a, b, c;
        while (file >> a >> b >> c) {
            QuadEquation equation(a, b, c);
            equations.push_back(equation);
        }
        file.close();
        return equations;
    }
    void writeout(std::vector<std::vector<double>>& eqsRoots, std::vector<QuadEquation>& equations) {
        std::ofstream outputFile(outputf, std::ofstream::app);

        if (!outputFile.is_open()) {
            return;
        }

        for (int i = 0; i < eqsRoots.size(); i++) {
            outputFile << equations[i].getA() << " " << equations[i].getB() << " " << equations[i].getC() << std::endl;
            outputFile << surname << std::endl;
            if ((eqsRoots[i].size()) == 0) {
                outputFile << "N";
            }
            if ((eqsRoots[i].size()) == 1) {
                outputFile << eqsRoots[i][0];
            }
            if ((eqsRoots[i].size()) == 2) {
                outputFile << eqsRoots[i][0] << " " << eqsRoots[i][1];
            }
            outputFile << std::endl;
        }
        outputFile.close();
    }
public:
    Student(std::string sur) {
        this->surname = sur;
    }
    std::string getSurname() {
        return surname;
    }
    virtual void SolveEquations() = 0;
};

class Good : public Student {
public:
    void SolveEquations() {
        std::vector<QuadEquation> equations;
        std::vector<std::vector<double>> eqsRoots;
        equations = read(inputFile);
        for (int i = 0; i < equations.size(); i++) {
            eqsRoots.push_back(equations[i].solve());
        }
        writeout(eqsRoots, equations);
    }
    Good(std::string sur) : Student(sur) {
        this->surname = sur;
    }
};

class Medium : public Student {
public:
    void SolveEquations() {
        std::vector<QuadEquation> equations;
        std::vector<std::vector<double>> eqsRoots;
        equations = read(inputFile);
        for (int i = 0; i < equations.size(); i++) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<double> a(0.0, 1.0);
            if (a(gen) >= 0.55) {
                eqsRoots.push_back(equations[i].solve());
            }
            else eqsRoots.push_back({ 0 });
        }
        writeout(eqsRoots, equations);
    }
    Medium(std::string sur) : Student(sur) {
        this->surname = sur;
    }
};

class Bad : public Student {
public:
    void SolveEquations() {
        std::vector<QuadEquation> equations;
        std::vector<std::vector<double>> eqsRoots;
        equations = read(inputFile);
        for (int i = 0; i < equations.size(); i++) {
            eqsRoots.push_back({ 0 });
        }
        writeout(eqsRoots, equations);
    }
    Bad(std::string sur) : Student(sur) {
        this->surname = sur;
    }
};
int main(void) {
    std::string sur1 = "Ivanov";
    Good stud1(sur1);
    stud1.SolveEquations();
    std::string sur2 = "Murygin";
    Medium stud2(sur2);
    stud2.SolveEquations();
    std::string sur3 = "Teslenko";
    Bad stud3(sur3);
    stud3.SolveEquations();
    return 0;
}