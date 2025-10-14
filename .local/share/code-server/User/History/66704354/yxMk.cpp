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

TEST(StudentValidationTest, InvalidScores) {
    std::stringstream str1{"Name John Doe\nQuiz 105 85 95\nHW 80 100\nFinal 92"};
    Student s1;
    str1 >> s1;
    std::cout << "Checking s1: Quiz values -> " << s1.quiz[0] << std::endl;
    EXPECT_THROW(s1.validate(), std::domain_error);

    std::stringstream str2{"Name Jane Doe\nQuiz 90 85 95\nHW 80 101\nFinal 92"};
    Student s2;
    str2 >> s2;
    std::cout << "Checking s2: HW values -> " << s2.hw[1] << std::endl;
    EXPECT_THROW(s2.validate(), std::domain_error);

    std::stringstream str3{"Name Jake Doe\nQuiz 90 85 95\nHW 80 100\nFinal 102"};
    Student s3;
    str3 >> s3;
    std::cout << "Checking s3: Final value -> " << s3.final_score << std::endl;
    EXPECT_THROW(s3.validate(), std::domain_error);
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
    student.compute_grade();
    
    std::stringstream output;
    output << student;
    
    std::string expectedOutput =
        "Name:   Jane Doe\n"
        "HW Ave: 85\n"
        "QZ Ave: 95\n"  
        "Final:  85\n"
        "Total:  89\n"
        "Grade:  B+\n";
    
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(StudentComputeTest, ComputeHWAverage) {
    std::stringstream str{"Name Jane Doe\nQuiz 90 85 95\nHW 90 80 85\nFinal 85"};
    Student student;
    str >> student;
    
    student.compute_grade();  

    std::stringstream output;
    output << student;

    std::string expectedOutput =
        "Name:   Jane Doe\n"
        "HW Ave: 85\n"  
        "QZ Ave: 90\n"
        "Final:  85\n"
        "Total:  88\n"
        "Grade:  B+\n";

    EXPECT_EQ(output.str(), expectedOutput);
}


TEST(GradebookTest, SortStudents) {
    Gradebook g;
    std::stringstream str{
        "Name Lisa Simpson\nQuiz 100 100 100\nHW 100 100\nFinal 100\n\n"
        "Name Bart Simpson\nQuiz 90 80 70\nHW 80 90\nFinal 85\n\n"
    };
    str >> g;  
    g.sort(); 

    std::stringstream output;
    output << g;  

    std::string expectedOutput =
        "Name:   Bart Simpson\n";

    EXPECT_NE(output.str().find(expectedOutput), std::string::npos);
}
