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
    if (quiz.empty()) {
        quiz_avg = 0.0;
        return;
    }
    if (quiz.size() > 1) {
        auto min_it = std::min_element(quiz.begin(), quiz.end());
        double sum = std::accumulate(quiz.begin(), quiz.end(), 0.0) - *min_it;
        quiz_avg = sum / (quiz.size() - 1); 
    } else {
        quiz_avg = std::accumulate(quiz.begin(), quiz.end(), 0.0) / quiz.size();
    }
}


void Student::compute_hw_avg() {
    if (hw.empty()) {
        hw_avg = 0.0;
        return;
    }
    hw_avg = std::accumulate(hw.begin(), hw.end(), 0.0) / hw.size();
}

void Student::compute_course_score() {
    compute_quiz_avg();
    compute_hw_avg();
    double total = (0.4 * quiz_avg) + (0.3 * hw_avg) + (0.3 * final_score);
    course_score = static_cast<int>(std::round(total));
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
    return std::tie(last_name, first_name) <=> std::tie(other.last_name, other.first_name);
}

bool Student::operator==(const Student& other) const {
    return last_name == other.last_name && first_name == other.first_name;
}

std::istream& operator>>(std::istream& in, Student& s) {
    std::string line;
    while (std::getline(in, line) && !line.empty()) {
        std::istringstream iss(line);
        std::string key;
        iss >> key;

        if (key == "Name" || key == "Name:") {  
            std::vector<std::string> name_parts;
            std::string name_part;
            while (iss >> name_part) { 
                name_parts.push_back(name_part);
            }

            if (!name_parts.empty()) {
                s.first_name = name_parts.front(); 
                if (name_parts.size() > 1) {
                    s.last_name = name_parts[1]; 
                    for (size_t i = 2; i < name_parts.size(); ++i) {
                        s.last_name += " " + name_parts[i]; 
                    }
                }
            } else {
                s.first_name = "Missing";
                s.last_name = "Name";
            }
        } 
        else if (key == "Quiz:") {
            int score;
            while (iss >> score) {
                s.quiz.push_back(score);
            }
        } 
        else if (key == "HW:") {
            int score;
            while (iss >> score) {
                s.hw.push_back(score);
            }
        } 
        else if (key == "Final:") {
            iss >> s.final_score;
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << std::left << std::setw(8) << "Name:"  << s.first_name << " " << s.last_name << "\n"
        << std::setw(8) << "HW Ave:" << std::round(s.hw_avg) << "\n"
        << std::setw(8) << "QZ Ave:" << std::round(s.quiz_avg) << "\n"
        << std::setw(8) << "Final:"  << s.final_score << "\n"
        << std::setw(8) << "Total:"  << s.course_score << "\n"
        << std::setw(8) << "Grade:"  << s.course_grade << "\n";
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
