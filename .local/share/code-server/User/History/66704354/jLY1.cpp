#include "compute_grades.hpp"
#include <gtest/gtest.h>
#include <sstream>

class StudentTest : public ::testing::Test {
protected:
    StudentTest student;
};

TEST_F(StudentTest, ValidateScores) {
    student.quiz = {90, 85, 95};
    student.hw = {80, 75, 85};
    student.final_score = 88;

    EXPECT_NO_THROW(student.validate());

    student.quiz = {110}; 
    EXPECT_THROW(student.validate(), std::domain_error);

    student.hw = {-5}; 
    EXPECT_THROW(student.validate(), std::domain_error);

    student.final_score = 102; 
    EXPECT_THROW(student.validate(), std::domain_error);
}

TEST_F(StudentTest, ComputeQuizAverage) {
    student.quiz = {80, 90, 70, 85};
    student.compute_quiz_avg();
    EXPECT_DOUBLE_EQ(student.quiz_avg, (80 + 90 + 85) / 3.0);
}

TEST_F(StudentTest, ComputeHwAverage) {
    student.hw = {70, 80, 90};
    student.compute_hw_avg();
    EXPECT_DOUBLE_EQ(student.hw_avg, (70 + 80 + 90) / 3.0);
}

TEST_F(StudentTest, ComputeCourseScore) {
    student.quiz = {80, 90, 70, 85};
    student.hw = {75, 85, 95};
    student.final_score = 88;
    
    student.compute_course_score();
    
    double expected_score = std::round((0.4 * (80 + 90 + 85) / 3.0) + (0.3 * 85.0) + (0.3 * 88.0));
    EXPECT_EQ(student.course_score, static_cast<int>(expected_score));
}

TEST_F(StudentTest, ComputeGrade) {
    student.course_score = 95;
    student.compute_grade();
    EXPECT_EQ(student.course_grade, "A");

    student.course_score = 89;
    student.compute_grade();
    EXPECT_EQ(student.course_grade, "B+");

    student.course_score = 60;
    student.compute_grade();
    EXPECT_EQ(student.course_grade, "D-");

    student.course_score = 59;
    student.compute_grade();
    EXPECT_EQ(student.course_grade, "F");
}

TEST_F(StudentTest, ComparisonOperators) {
    Student s1, s2;
    s1.first_name = "Alice";
    s1.last_name = "Smith";
    s2.first_name = "Bob";
    s2.last_name = "Jones";

    EXPECT_TRUE(s1 > s2);
    EXPECT_FALSE(s1 == s2);
}

TEST_F(StudentTest, StudentInputParsing) {
    std::istringstream input("Name: John Doe\nQuiz: 80 90 85\nHW: 75 85 90\nFinal: 88\n");
    Student s;
    input >> s;

    EXPECT_EQ(s.first_name, "John");
    EXPECT_EQ(s.last_name, "Doe");
    EXPECT_EQ(s.quiz, std::vector<int>({80, 90, 85}));
    EXPECT_EQ(s.hw, std::vector<int>({75, 85, 90}));
    EXPECT_EQ(s.final_score, 88);
}

TEST_F(StudentTest, StudentOutputFormatting) {
    student.first_name = "Jane";
    student.last_name = "Doe";
    student.hw_avg = 85.0;
    student.quiz_avg = 88.0;
    student.final_score = 90;
    student.course_score = 87;
    student.course_grade = "B+";

    std::ostringstream output;
    output << student;
    
    std::string expected_output = 
        "Name:   Jane Doe\n"
        "HW Ave: 85\n"
        "QZ Ave: 88\n"
        "Final:  90\n"
        "Total:  87\n"
        "Grade:  B+\n";

    EXPECT_EQ(output.str(), expected_output);
}

class GradebookTest : public ::testing::Test {
protected:
    Gradebook gradebook;
};

TEST_F(GradebookTest, ComputeGrades) {
    Student s1, s2;
    s1.quiz = {80, 90};
    s1.hw = {85, 90};
    s1.final_score = 88;
    
    s2.quiz = {70, 75};
    s2.hw = {60, 65};
    s2.final_score = 72;

    gradebook.students.push_back(s1);
    gradebook.students.push_back(s2);

    gradebook.compute_grades();

    EXPECT_FALSE(gradebook.students[0].course_grade.empty());
    EXPECT_FALSE(gradebook.students[1].course_grade.empty());
}

TEST_F(GradebookTest, SortStudents) {
    Student s1, s2;
    s1.first_name = "Alice";
    s1.last_name = "Smith";
    s2.first_name = "Bob";
    s2.last_name = "Jones";

    gradebook.students.push_back(s1);
    gradebook.students.push_back(s2);

    gradebook.sort();

    EXPECT_EQ(gradebook.students[0].first_name, "Bob");
    EXPECT_EQ(gradebook.students[1].first_name, "Alice");
}

TEST_F(GradebookTest, GradebookInputParsing) {
    std::istringstream input(
        "Name: John Doe\nQuiz: 80 90 85\nHW: 75 85 90\nFinal: 88\n\n"
        "Name: Alice Smith\nQuiz: 90 95 92\nHW: 88 92 90\nFinal: 91\n"
    );
    
    Gradebook g;
    input >> g;

    EXPECT_EQ(g.students.size(), 2);
    EXPECT_EQ(g.students[0].first_name, "John");
    EXPECT_EQ(g.students[1].first_name, "Alice");
}

TEST_F(GradebookTest, GradebookOutputFormatting) {
    Student s1, s2;
    s1.first_name = "John";
    s1.last_name = "Doe";
    s1.hw_avg = 85;
    s1.quiz_avg = 88;
    s1.final_score = 90;
    s1.course_score = 87;
    s1.course_grade = "B+";

    s2.first_name = "Alice";
    s2.last_name = "Smith";
    s2.hw_avg = 92;
    s2.quiz_avg = 95;
    s2.final_score = 97;
    s2.course_score = 94;
    s2.course_grade = "A";

    gradebook.students.push_back(s1);
    gradebook.students.push_back(s2);

    std::ostringstream output;
    output << gradebook;

    EXPECT_NE(output.str().find("Name:   John Doe"), std::string::npos);
    EXPECT_NE(output.str().find("Grade:  B+"), std::string::npos);
    EXPECT_NE(output.str().find("Name:   Alice Smith"), std::string::npos);
    EXPECT_NE(output.str().find("Grade:  A"), std::string::npos);
}

// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
