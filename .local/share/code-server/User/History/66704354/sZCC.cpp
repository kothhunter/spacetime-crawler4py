#include "compute_grades.hpp"
#include <gtest/gtest.h>
#include <sstream>

// class TestStudent : public Student {
// public:
//     using Student::compute_grade;
//     using Student::validate;
//     void setScores(const std::vector<int>& quiz_scores, const std::vector<int>& hw_scores, double final) {
//         quiz = quiz_scores;
//         hw = hw_scores;
//         final_score = final;
//     }
// };

TEST(StudentTest, Validation) {
    Student s1;
    s1.setScores({90, 85, 100}, {80, 70, 60}, 95);
    EXPECT_NO_THROW(s1.validate());

    Student s2;
    s2.setScores({110}, {80, 70, 60}, 95);
    EXPECT_THROW(s2.validate(), std::domain_error);

    Student s3;
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
