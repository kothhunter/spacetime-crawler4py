#include "compute_grades.hpp"

#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>

TEST(StudentInputTest, ReadFromStringStream) {
    std::stringstream str{"Name John Doe\nQuiz 90 85 95\nHW 80 100\nFinal 92"};
    Student student;
    str >> student;

    EXPECT_NO_THROW(student.validate());
}

TEST(StudentComputeTest, ComputeCourseScore) {
    std::stringstream str{"Name John Doe\nQuiz 100 90 80\nHW 100 80 90\nFinal 90"};
    Student student;
    str >> student; 
    student.compute_grade();

    std::stringstream output;
    output << student;

    std::string expectedOutput =
        "Name:   John Doe\n"
        "HW Ave: 90\n"
        "QZ Ave: 95\n"
        "Final:  90\n"
        "Total:  91\n"
        "Grade:  A-\n";

    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(StudentValidationTest, InvalidQuizScore) {
    std::stringstream str{"Name Jane Doe\nQuiz 105 85 95\nHW 80 100\nFinal 92"};
    Student student;
    str >> student;
    EXPECT_THROW(student.validate(), std::domain_error);
}

TEST(StudentValidationTest, InvalidHWScore) {
    std::stringstream str{"Name Jane Doe\nQuiz 90 85 95\nHW 80 101\nFinal 92"};
    Student student;
    str >> student;
    EXPECT_THROW(student.validate(), std::domain_error);
}

TEST(StudentValidationTest, InvalidFinalScore) {
    std::stringstream str{"Name Jane Doe\nQuiz 90 85 95\nHW 80 100\nFinal 102"};
    Student student;
    str >> student;
    EXPECT_THROW(student.validate(), std::domain_error);
}

TEST(StudentComputeTest, ComputeQuizAverage) {
    std::stringstream str{"Name Jane Doe\nQuiz 100 90 80\nHW 90 80\nFinal 85"};
    Student student;
    str >> student;
    student.compute_quiz_avg();
    EXPECT_EQ(student.quiz_avg, 95.0); 
}

TEST(StudentComputeTest, ComputeHWAverage) {
    std::stringstream str{"Name Jane Doe\nQuiz 90 85 95\nHW 90 80 85\nFinal 85"};
    Student student;
    str >> student;
    student.compute_hw_avg();
    EXPECT_EQ(student.hw_avg, 85.0); // Averages (90, 80, 85)
}

TEST(GradebookTest, SortStudents) {
    Gradebook g;
    std::stringstream str1{"Name Lisa Simpson\nQuiz 100 100 100\nHW 100 100\nFinal 100"};
    std::stringstream str2{"Name Bart Simpson\nQuiz 90 80 70\nHW 80 90\nFinal 85"};
    Student s1, s2;
    str1 >> s1;
    str2 >> s2;
    g.students.push_back(s1);
    g.students.push_back(s2);
    g.sort();
    EXPECT_EQ(g.students.front().first_name, "Bart");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
