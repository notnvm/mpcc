#include <gtest/gtest.h>
// #include <gmock/gmock.h>
#include "lib.h"

TEST(generator, generate_random_seq) {
    std::vector<int> t = generator::create_seq(10, 1, 50, 0);
    auto it = std::max_element(std::begin(t), std::end(t));


    EXPECT_EQ(10, t.size());
    EXPECT_TRUE(*it <= 50);
}

TEST(generator, is_convex) {
    std::vector<int> t{ 1,2,3 };

    EXPECT_TRUE(generator::is_convex(t));
}

TEST(generator, is_convex2) {
    std::vector<int> t{ 1, 2, 4, 7, 11, 16 };

    EXPECT_TRUE(generator::is_convex(t));
}

TEST(generator, is_convex3) {
    std::vector<int> t{ 1, 2, 4, 7, 7, 16 };

    EXPECT_FALSE(generator::is_convex(t));
}

TEST(generator, generate_convex_seq) {
    std::vector<int> t = generator::create_seq(10, 1, 4, 1);

    EXPECT_EQ(10, t.size());
    EXPECT_TRUE(generator::is_convex(t));
}

TEST(generator, generate_zero_seq) {
    std::vector<int> t = generator::create_seq(5, 0, 0, 0);

    std::vector<int> expected{ 0,0,0,0,0 };

    EXPECT_EQ(expected, t);

}

TEST(generator, generate_zero_size_seq) {
    std::vector<int> t = generator::create_seq(0, 0, 0, 0);
    std::vector<int> t2 = generator::create_seq(0, 0, 0, 1);
    std::vector<int> expected{};

    EXPECT_EQ(expected, t);
    EXPECT_EQ(expected, t2);
}

TEST(mpcc, mpcc_test_size) {
    std::vector<int> a{ generator::create_seq(5, 1, 10, 0) };
    std::vector<int> b{ generator::create_seq(5, 1, 10, 1) };
    size_t expected = a.size() + b.size() - 1;

    std::vector<int> c = smawk::mpcc(a, b);

    EXPECT_EQ(expected, c.size());
}

TEST(mpcc, mpcc_a_or_b_zerosize) {
    std::vector<int> a{};
    std::vector<int> a2{ generator::create_seq(5, 1, 10, 0) };
    std::vector<int> b{ generator::create_seq(5, 1, 10, 1) };
    std::vector<int> b2{};
    size_t expected = 0;

    std::vector<int> c = smawk::mpcc(a, b);
    std::vector<int> c2 = smawk::mpcc(a2, b2);

    EXPECT_EQ(expected, c.size());
    EXPECT_EQ(expected, c2.size());
}

TEST(mpcc, mpcc_n_less_m) {
    std::vector<int> a{ generator::create_seq(5, 1, 10, 0) };
    std::vector<int> b{ generator::create_seq(10, 1, 10, 1) };

    ASSERT_ANY_THROW(smawk::mpcc(a, b));
}

TEST(mpcc, mpcc_a_convex_b_random) {
    std::vector<int> a{ generator::create_seq(5, 1, 10, 1) };
    std::vector<int> b{ generator::create_seq(5, 1, 10, 0) };

    EXPECT_NO_THROW(smawk::mpcc(a, b));
}

TEST(mpcc, mpcc_a_and_b_not_convex) {
    std::vector<int> a{ generator::create_seq(5, 1, 10, 0) };
    std::vector<int> b{ generator::create_seq(5, 1, 10, 0) };

    EXPECT_ANY_THROW(smawk::mpcc(a, b));
}

TEST(mpcc, mpcc_bigsize_nothrow) {
    std::vector<int> a{ generator::create_seq(10'000, 1, 10, 0) };
    std::vector<int> b{ generator::create_seq(10'000, 1, 10, 1) };

    EXPECT_NO_THROW(smawk::mpcc(a, b));
}

TEST(mpcc, mpcc_allzero) {
    std::vector<int> a{ generator::create_seq(10'000, 0, 0, 0) };
    std::vector<int> b{ generator::create_seq(10'000, 0, 0, 0) };
    size_t expected = a.size() + b.size() - 1;
    std::vector<int> expected_vec(expected, 0);

    std::vector<int> c = smawk::mpcc(a, b);

    EXPECT_EQ(expected, c.size());
    EXPECT_TRUE(expected_vec == c);
}

TEST(mpcc, mpcc_result_1) {
    std::vector<int> a{ 1,1,1,1 };
    std::vector<int> b{ 1,1,1,1 };

    std::vector<int> expected(a.size() + b.size() - 1, 2);
    std::vector<int> c = smawk::mpcc(a, b);

    EXPECT_TRUE(generator::is_convex(b));
    EXPECT_NO_THROW(smawk::mpcc(a, b));
    // ASSERT_THAT(c, ElementsAre(2, 2, 2, 2, 2, 2, 2));
    for (size_t i{}; i < c.size(); ++i)
        EXPECT_EQ(expected[i], c[i]);
}

TEST(mpcc, mpcc_result_2) {
    std::vector<int> a{ 3,2,5,2 };
    std::vector<int> b{ 1,2,4,7 };

    std::vector<int> expected{ 4, 3, 4, 3, 4, 6, 9 };
    std::vector<int> c = smawk::mpcc(a, b);

    EXPECT_TRUE(generator::is_convex(b));
    EXPECT_NO_THROW(smawk::mpcc(a, b));
    for (size_t i{}; i < c.size(); ++i)
        EXPECT_EQ(expected[i], c[i]);
}

TEST(mpcc, mpcc_result_3) {
    std::vector<int> a{ -1, 8, 6, 2 };
    std::vector<int> b{ 8, 9, 11 };

    std::vector<int> expected{ 7, 8, 10, 10, 11, 13 };
    std::vector<int> c = smawk::mpcc(a, b);

    EXPECT_TRUE(generator::is_convex(b));
    EXPECT_NO_THROW(smawk::mpcc(a, b));
    for (size_t i{}; i < c.size(); ++i)
        EXPECT_EQ(expected[i], c[i]);
}

TEST(mpcc, mpcc_result_4) {
    std::vector<int> a{ -1, -10};
    std::vector<int> b{ 1, 2 };

    std::vector<int> expected{ 0, -9, -8 };
    std::vector<int> c = smawk::mpcc(a, b);

    EXPECT_TRUE(generator::is_convex(b));
    EXPECT_NO_THROW(smawk::mpcc(a, b));
    for (size_t i{}; i < c.size(); ++i)
        EXPECT_EQ(expected[i], c[i]);
}

TEST(mpcc, mpcc_result_5) {
    std::vector<int> a{ -2, 0, 3, 7, 12 };
    std::vector<int> b{ -1, -10, 14, 13, 22 };
    EXPECT_FALSE(generator::is_convex(b));

    std::vector<int> expected{ -3, -12, -10, -7, -3, 2, 20, 25, 34 };
    std::vector<int> c = smawk::mpcc(a, b);
    EXPECT_TRUE(generator::is_convex(b)); // check for swap if b is not convex
    
    EXPECT_NO_THROW(smawk::mpcc(a, b));
    for (size_t i{}; i < c.size(); ++i)
        EXPECT_EQ(expected[i], c[i]);
}
