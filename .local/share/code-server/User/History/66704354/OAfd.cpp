#include "compute_grades.hpp"
#include <gtest/gtest.h>
#include <sstream>

class TestStudent : public Student {
public:
    using Student::compute_grade;
    using Student::validate;
    void setScores(const std::vector<int>& quiz_scores, const std::vector<int>& hw_scores, double final) {
        quiz = quiz_scores;
        hw = hw_scores;
        final_score = final;
    }
};

TEST(StudentTest, Validation) {
    TestStudent s1;
    s1.setScores({90, 85, 100}, {80, 70, 60}, 95);
    EXPECT_NO_THROW(s1.validate());

    TestStudent s2;
    s2.setScores({110}, {80, 70, 60}, 95);
    EXPECT_THROW(s2.validate(), std::domain_error);

    TestStudent s3;
    s3.setScores({90, 85, 100}, {80, 70, 60}, -5);
    EXPECT_THROW(s3.validate(), std::domain_error);
}

TEST(StudentTest, ComputeCourseScoreAndGrade) {
    TestStudent s;
    s.setScores({100, 100, 100}, {100, 100, 100}, 100);
    s.compute_grade();
    EXPECT_EQ(s.course_score, 100);
    EXPECT_EQ(s.course_grade, "A+");
    
    s.setScores({70, 75, 80}, {80, 85, 90}, 85);
    s.compute_grade();
    EXPECT_EQ(s.course_score, 81);
    EXPECT_EQ(s.course_grade, "B-");
}

TEST(GradebookTest, SortStudents) {
    Gradebook gb;
    Student s1, s2;
    s1.first_name = "John";
    s1.last_name = "Doe";
    s2.first_name = "Alice";
    s2.last_name = "Smith";
    gb.students = {s1, s2};
    gb.sort();
    EXPECT_EQ(gb.students.front().last_name, "Doe");
    EXPECT_EQ(gb.students.back().last_name, "Smith");
}

TEST(GradebookTest, SampleGradebook) {
    Gradebook gb;

    Student s1, s2, s3, s4;
    s1.first_name = "A";
    s1.last_name = "Bar";
    s1.hw = {}; 
    s1.quiz = {80}; 
    s1.final_score = 50;

    s2.first_name = "Foo";
    s2.last_name = "Bar";
    s2.hw = {90}; 
    s2.quiz = {70}; 
    s2.final_score = 50;

    s3.first_name = "Testing";
    s3.last_name = "Test";
    s3.hw = {50}; 
    s3.quiz = {20}; 
    s3.final_score = 50;

    s4.first_name = "Hello";
    s4.last_name = "World";
    s4.hw = {}; 
    s4.quiz = {70}; 
    s4.final_score = 10;

    gb.students = {s1, s2, s3, s4};

    gb.compute_grades(); // Ensure grades are computed before checking output

    std::ostringstream out;
    out << gb; // This should now contain computed grades

    std::string expected =
        "Name:   A Bar\nHW Ave: 0\nQZ Ave: 80\nFinal:  50\nTotal:  47\nGrade:  F\n\n"
        "Name:   Foo Bar\nHW Ave: 90\nQZ Ave: 70\nFinal:  50\nTotal:  70\nGrade:  C-\n\n"
        "Name:   Testing Test\nHW Ave: 50\nQZ Ave: 20\nFinal:  50\nTotal:  38\nGrade:  F\n\n"
        "Name:   Hello World\nHW Ave: 0\nQZ Ave: 70\nFinal:  10\nTotal:  31\nGrade:  F\n\n";

    EXPECT_EQ(out.str(), expected);
}


TEST(IOTest, ReadStudent) {
    std::istringstream input("Name: John Doe\nQuiz: 90 80 70\nHW: 100 95 90\nFinal: 85\n\n");
    Student s;
    input >> s;
    EXPECT_EQ(s.first_name, "John");
    EXPECT_EQ(s.last_name, "Doe");
}

TEST(IOTest, WriteStudent) {
    Student s;
    s.first_name = "Jane";
    s.last_name = "Doe";
    std::ostringstream output;
    output << s;
    std::string expected = "Name:   Jane Doe\nHW Ave: 0\nQZ Ave: 0\nFinal:  0\nTotal:  0\nGrade:  \n\n";
    EXPECT_EQ(output.str(), expected);
}
