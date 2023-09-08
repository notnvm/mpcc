#include <gtest/gtest.h>
#include "lib.h"

TEST(generator, generate_random_seq) {
    std::vector<int> t = generator::create_random_seq(10, 1, 50);
    auto it = std::max_element(std::begin(t), std::end(t));


    EXPECT_EQ(10, t.size());
    EXPECT_TRUE(*it <= 50);
}

TEST(generator, is_convex) {
    std::vector<int> t{ 1,2,3 };

    EXPECT_TRUE(generator::is_convex(t));
}

TEST(generator, generate_convex_seq) {
    std::vector<int> t = generator::create_convex_seq(10, 1, 4);

    EXPECT_EQ(10, t.size());
    EXPECT_TRUE(generator::is_convex(t));
}

TEST(generator, generate_zero_seq){
    std::vector<int> t = generator::create_random_seq(5, 0, 0);

    std::vector<int> expected{ 0,0,0,0,0 };

    EXPECT_EQ(expected, t);

}

TEST(generator, generate_zero_size_seq){
    std::vector<int> t = generator::create_random_seq(0, 0, 0);
    std::vector<int> t2 = generator::create_convex_seq(0, 0, 0);
    std::vector<int> expected{};

    EXPECT_EQ(expected, t);
    EXPECT_EQ(expected, t2);
}

TEST(mpcc, mpcc_test_size) {
    std::vector<int> a{ generator::create_random_seq(5,1,10) };
    std::vector<int> b{ generator::create_convex_seq(5,1,10) };
    size_t expected = a.size() + b.size() - 1;

    std::vector<int> c = smawk::mpcc(a, b);

    EXPECT_EQ(expected, c.size());
}

TEST(mpcc, mpcc_a_or_b_zerosize) {
    std::vector<int> a{};
    std::vector<int> a2{ generator::create_random_seq(5,1,10) };
    std::vector<int> b{ generator::create_convex_seq(5,1,10) };
    std::vector<int> b2{};
    size_t expected = 0;

    std::vector<int> c = smawk::mpcc(a, b);
    std::vector<int> c2 = smawk::mpcc(a2, b2);
    
    EXPECT_EQ(expected, c.size());
    EXPECT_EQ(expected, c2.size());
}

TEST(mpcc, mpcc_n_less_m) {
    std::vector<int> a{ generator::create_random_seq(5,1,10) };
    std::vector<int> b{ generator::create_convex_seq(10,1,10) };

    ASSERT_ANY_THROW(smawk::mpcc(a, b));
}

TEST(mpcc, mpcc_a_convex_b_random) {
    std::vector<int> a{ generator::create_convex_seq(5,1,10) };
    std::vector<int> b{ generator::create_random_seq(5,1,10) };

    EXPECT_NO_THROW(smawk::mpcc(a, b));
}

TEST(mpcc, mpcc_a_and_b_not_convex){
    std::vector<int> a{ generator::create_random_seq(5,1,10) };
    std::vector<int> b{ generator::create_random_seq(5,1,10) };

    EXPECT_ANY_THROW(smawk::mpcc(a, b));
}

TEST(mpcc, mpcc_bigsize_nothrow) {
    std::vector<int> a{ generator::create_convex_seq(10'000,1,10) };
    std::vector<int> b{ generator::create_random_seq(10'000,1,10) };

    EXPECT_NO_THROW(smawk::mpcc(a, b));
}

TEST(mpcc, mpcc_allzero) {
    std::vector<int> a{ generator::create_random_seq(10'000,0,0) };
    std::vector<int> b{ generator::create_random_seq(10'000,0,0) };
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

    EXPECT_EQ(expected, c);
}

TEST(mpcc, mpcc_result_2) {
    std::vector<int> a{ 3,2,5,2 };
    std::vector<int> b{ 1,2,4,7 };

    std::vector<int> expected{ 4, 3, 4, 3, 4, 6, 9 };
    std::vector<int> c = smawk::mpcc(a, b);

    EXPECT_EQ(expected, c);
}