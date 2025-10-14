#include "compute_grades.hpp"

#include <algorithm>
#include <numeric>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <ranges>

void Student::validate() const {
    auto isOutOfRange = [](auto score){return score < 0 || score > 100;};

    auto invalidQuizIter = std::find_if(quiz.begin(), quiz.end(), isOutOfRange);
    auto invalidHwIter = std::find_if(hw.begin(), hw.end(), isOutOfRange);
    bool isFinalInvalid = isOutOfRange(final_score);

    if (invalidQuizIter != quiz.end()) {
        std::stringstream errorMsg;
        errorMsg << "Error: invalid percentage " << *invalidQuizIter;
        throw std::domain_error(errorMsg.str());
    }
    if (invalidHwIter != hw.end()) {
        std::stringstream errorMsg;
        errorMsg << "Error: invalid percentage " << *invalidHwIter;
        throw std::domain_error(errorMsg.str());
    }
    if (isFinalInvalid) {
        std::stringstream errorMsg;
        errorMsg << "Error: invalid percentage " << final_score;
        throw std::domain_error(errorMsg.str());
    }
}

void Student::compute_quiz_avg() {
    quiz_avg = quiz.empty() ? 0 : static_cast<double>(std::accumulate(quiz.begin(), quiz.end(), 0) - (quiz.size() > 1 ? *std::min_element(quiz.begin(), quiz.end()) : 0)) / std::max(1, static_cast<int>(quiz.size()) - 1);
}


void Student::compute_hw_avg() {
    hw_avg = hw.empty() ? 0 : static_cast<double>(std::accumulate(hw.begin(), hw.end(), 0)) / hw.size();
}

void Student::compute_course_score() {
    compute_quiz_avg();
    compute_hw_avg();
    double total = (0.4 * quiz_avg) + (0.3 * hw_avg) + (0.3 * final_score);
    course_score = std::round(total);
}

void Student::compute_grade() {
    compute_course_score();
    if (course_score >= 97) course_grade = "A+";
    else if (course_score >= 93) course_grade = "A";
    else if (course_score >= 90) course_grade = "A-";
    else if (course_score >= 87) course_grade = "B+";
    else if (course_score >= 83) course_grade = "B";
    else if (course_score >= 80) course_grade = "B-";
    else if (course_score >= 77) course_grade = "C+";
    else if (course_score >= 73) course_grade = "C";
    else if (course_score >= 70) course_grade = "C-";
    else if (course_score >= 67) course_grade = "D+";
    else if (course_score >= 63) course_grade = "D";
    else if (course_score >= 60) course_grade = "D-";
    else course_grade = "F";
}

std::strong_ordering Student::operator<=>(const Student& other) const {
    if (auto cmp = last_name <=> other.last_name; cmp != 0) return cmp;
    return first_name <=> other.first_name;
}

bool Student::operator==(const Student& other) const {
    return last_name == other.last_name && first_name == other.first_name;
}

std::istream& operator>>(std::istream& in, Student& s) {
    std::string line, label;
    s.first_name = "Missing";
    s.last_name = "Name";
    s.quiz.clear();
    s.hw.clear();

    while (std::getline(in, line) && !line.empty()) {
        std::istringstream ss(line);
        ss >> label;
        if (label == "Name") {
            ss >> s.first_name >> s.last_name;
        } else {
            std::vector<int>* target = nullptr;
            if (label == "Quiz") target = &s.quiz;
            else if (label == "HW") target = &s.hw;

            if (target) {
                int score;
                while (ss >> score) {
                    target->push_back(score);
                }
            } else if (label == "Final") {
                ss >> s.final_score;
            }
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << "Name:   " << std::left << std::setw(10) << s.first_name + " " + s.last_name << '\n'
        << "HW Ave: " << std::left << std::setw(8) << std::fixed << std::setprecision(2) << s.hw_avg << '\n'
        << "QZ Ave: " << std::left << std::setw(8) << s.quiz_avg << '\n'
        << "Final:  " << std::left << std::setw(8) << s.final_score << '\n'
        << "Total:  " << std::left << std::setw(8) << s.course_score << '\n'
        << "Grade:  " << std::left << s.course_grade << "\n\n";
    return out;
}

void Gradebook::compute_grades() {
    std::for_each(students.begin(), students.end(), [](Student& s) { s.compute_grade(); });
}

void Gradebook::sort() {
    std::ranges::sort(students);
}

void Gradebook::validate() const {
    std::for_each(students.begin(), students.end(), [](const Student& s) { s.validate(); });
}

std::istream& operator>>(std::istream& in, Gradebook& b) {
    Student s;
    while (in >> s) {
        b.students.push_back(s);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Gradebook& b) {
    std::for_each(b.students.begin(), b.students.end(), [&out](const Student& s) { out << s << "\n"; });
    return out;
}
