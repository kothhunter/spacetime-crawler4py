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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
