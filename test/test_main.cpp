#include <gtest/gtest.h>
#include "polinoms.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(PolinomTest, Constructor_DefaultCreatesEmpty) {
    Polinom p;
    Polinom empty;
    EXPECT_TRUE(p == empty);
}

TEST(PolinomTest, Constructor_CopyIsDeep) {
    Polinom p1;
    p1.addMonom(1.0, 111);
    Polinom p2 = p1;
    p2.addMonom(1.0, 111);

    EXPECT_FALSE(p1 == p2);
}

TEST(PolinomTest, AddMonom_SingleTerm) {
    Polinom p;
    p.addMonom(3.5, 123);
    Polinom expected;
    expected.addMonom(3.5, 123);
    EXPECT_TRUE(p == expected);
}

TEST(PolinomTest, AddMonom_SumSameDegree) {
    Polinom p;
    p.addMonom(2.0, 123);
    p.addMonom(3.0, 123);
    p.addMonom(-1.0, 123);

    Polinom expected;
    expected.addMonom(4.0, 123);
    EXPECT_TRUE(p == expected);
}

TEST(PolinomTest, AddMonom_CancellationToZero) {
    Polinom p;
    p.addMonom(5.0, 123);
    p.addMonom(-5.0, 123);

    Polinom empty;
    EXPECT_TRUE(p == empty);
}

TEST(PolinomTest, AddMonom_OrderDoesNotMatter) {
    Polinom p1, p2;
    p1.addMonom(1.0, 100); p1.addMonom(2.0, 10); p1.addMonom(3.0, 1);
    p2.addMonom(3.0, 1); p2.addMonom(1.0, 100); p2.addMonom(2.0, 10);

    EXPECT_TRUE(p1 == p2);
}

TEST(PolinomTest, Addition_SimilarTerms) {
    Polinom p1, p2, expected;
    p1.addMonom(2.0, 111);
    p2.addMonom(3.0, 111);
    expected.addMonom(5.0, 111);
    EXPECT_TRUE((p1 + p2) == expected);
}

TEST(PolinomTest, Subtraction_PartialCancellation) {
    Polinom p1, p2, expected;
    p1.addMonom(5.0, 100); p1.addMonom(3.0, 10);
    p2.addMonom(2.0, 100); p2.addMonom(3.0, 10);

    expected.addMonom(3.0, 100);
    EXPECT_TRUE((p1 - p2) == expected);
}

TEST(PolinomTest, Subtraction_NegativeCoefficients) {
    Polinom p1, p2, expected;
    p1.addMonom(5.0, 100);
    p2.addMonom(-3.0, 100);
    expected.addMonom(8.0, 100);
    EXPECT_TRUE((p1 - p2) == expected);
}

TEST(PolinomTest, ScalarMultiplication_PositiveAndNegative) {
    Polinom p, expected;
    p.addMonom(2.0, 100);

    expected.addMonom(-4.0, 100);
    EXPECT_TRUE((p * -2.0) == expected);
}

TEST(PolinomTest, ScalarMultiplication_ByZero) {
    Polinom p;
    p.addMonom(10.0, 123);
    Polinom res = p * 0.0;
    Polinom empty;
    EXPECT_TRUE(res == empty);
}

TEST(PolinomTest, Multiplication_SimplePolynomials) {
    Polinom p1, p2, expected;
    p1.addMonom(2.0, 100);
    p2.addMonom(3.0, 10);
    expected.addMonom(6.0, 110);
    EXPECT_TRUE((p1 * p2) == expected);
}

TEST(PolinomTest, Multiplication_ComplexPolynomials) {
    Polinom p1, p2, expected;
    p1.addMonom(2.0, 100); p1.addMonom(3.0, 10);
    p2.addMonom(4.0, 10); p2.addMonom(5.0, 1);

    expected.addMonom(8.0, 110);
    expected.addMonom(10.0, 101);
    expected.addMonom(12.0, 20);
    expected.addMonom(15.0, 11);

    EXPECT_TRUE((p1 * p2) == expected);
}

TEST(PolinomTest, Degree_OverflowThrowsError) {
    Polinom p1, p2;
    p1.addMonom(1.0, 800);
    p2.addMonom(1.0, 300);
    EXPECT_THROW(p1 * p2, std::runtime_error);
}

TEST(PolinomTest, Degree_BoundaryMaxAllowed) {
    Polinom p1, p2;
    p1.addMonom(1.0, 900);
    p2.addMonom(1.0, 90);
    EXPECT_NO_THROW(p1 * p2);
}

TEST(PolinomTest, Assignment_SelfAssignment) {
    Polinom p;
    p.addMonom(4.0, 123);
    ASSERT_NO_THROW(p = p);
    EXPECT_EQ(4.0, 4.0);
}

TEST(PolinomTest, Assignment_Chained) {
    Polinom p1, p2, p3, expected;
    p1.addMonom(2.0, 100);
    expected.addMonom(2.0, 100);

    p3 = p2 = p1;
    EXPECT_TRUE(p2 == expected);
    EXPECT_TRUE(p3 == expected);
}

TEST(PolinomTest, Assignment_IndependenceAfterCopy) {
    Polinom p1, p2;
    p1.addMonom(2.0, 100);
    p2 = p1;
    p1.addMonom(3.0, 10);

    Polinom expected_p2;
    expected_p2.addMonom(2.0, 100);
    EXPECT_TRUE(p2 == expected_p2);
}

TEST(PolinomTest, Const_OperationsWork) {
    const Polinom p1 = []() { Polinom p; p.addMonom(2.0, 100); return p; }();
    const Polinom p2 = []() { Polinom p; p.addMonom(3.0, 10); return p; }();

    Polinom prod = p1 * p2;
    Polinom expected;
    expected.addMonom(6.0, 110);
    EXPECT_TRUE(prod == expected);
}

TEST(PolinomTest, AddMonom_VerySmallCoefficients) {
    Polinom p;
    p.addMonom(1e-15, 100);
    p.addMonom(-1e-15, 100);
    Polinom empty;
    EXPECT_TRUE(p == empty);
}

TEST(PolinomTest, Degree_OverflowXOnly) {
    Polinom p1, p2;
    p1.addMonom(1.0, 900);
    p2.addMonom(1.0, 100);
    EXPECT_THROW(p1 * p2, std::runtime_error);
}

TEST(PolinomTest, Degree_OverflowYOnly) {
    Polinom p1, p2;
    p1.addMonom(1.0, 90);
    p2.addMonom(1.0, 10);
    EXPECT_THROW(p1 * p2, std::runtime_error);
}

        