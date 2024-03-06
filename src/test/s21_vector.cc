#include <gtest/gtest.h>

#include <vector>

#include "../s21_containers.h"

TEST(vector, constructor_test_01) {
  s21::vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
}

TEST(vector, constructor_test_02) {
  std::vector<int> v(20);
  s21::vector<int> o{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  EXPECT_EQ(v.size(), 20);
  EXPECT_EQ(v.capacity(), 20);
  for (size_t i = 0; i < v.size(); ++i) EXPECT_EQ(v[i], o[i]);
}

TEST(vector, constructor_test_03) {
  s21::vector<double> v1{1.01, 2.02, 3.03};
  s21::vector<double> v2(v1);
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.at(1), v2.at(1));
}

TEST(vector, constructor_test_04) {
  s21::vector<double> v1{1.01, 2.02, 3.03};
  s21::vector<double> v2(std::move(v1));
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v2.size(), 3);
}

TEST(vector, data_test_01) {
  s21::vector<double> v{1.01, 2.02, 3.03};
  EXPECT_EQ(v.data(), v.begin());
}

TEST(vector, data_test_02) {
  s21::vector<double> v{1.01, 2.02, 3.03};
  v.reserve(10);
  EXPECT_EQ(v.begin() + v.size(), v.end());
  EXPECT_EQ(v.capacity(), 10);
}

TEST(vector, reserve_test_01) {
  s21::vector<double> v{1.01, 2.02, 3.03};
  v.reserve(2);
  EXPECT_EQ(v.capacity(), 3);
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 3);
}

TEST(vector, eq_oper__test_01) {
  s21::vector<double> v1{1.01, 2.02, 3.03};
  s21::vector<double> v2;

  v2 = std::move(v1);
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v2.size(), 3);
}

TEST(vector, front_back_oper_test_01) {
  s21::vector<double> v{1.01, 2.02, 3.03};
  EXPECT_EQ(v.front(), 1.01);
  EXPECT_EQ(v.back(), 3.03);
}

TEST(vector, bool_empty_case_test_01) {
  s21::vector<int> v;
  EXPECT_TRUE(v.empty());
}

TEST(vector, bool_empty_case_test_02) {
  s21::vector<int> v(20);
  v.clear();
  EXPECT_TRUE(v.empty());
}

TEST(vector, max_size_test_01) {
  s21::vector<int> v;
  std::vector<int> v1;
  EXPECT_EQ(v.max_size(), v1.max_size());
}

TEST(vector, push_back_test_01) {
  s21::vector<double> v;
  v.push_back(7.31);
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.capacity(), 1);
  v.push_back(7.32);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.capacity(), 2);
  v.push_back(7.33);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 4);
}

TEST(vector, pop_back_test_01) {
  s21::vector<double> v;
  v.push_back(7.31);
  v.push_back(7.32);
  v.push_back(7.33);
  v.pop_back();
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.capacity(), 4);
  v.pop_back();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.capacity(), 4);
  v.pop_back();
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 4);
}

TEST(vector, insert_test_01) {
  s21::vector<double> v;
  v.insert(v.begin(), 7.31);
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.capacity(), 1);
  v.insert(v.begin(), 7.32);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.capacity(), 2);
  double* ptr = v.insert(v.begin() + 1, 7.33);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 4);
  EXPECT_EQ(v.at(1), 7.33);
  EXPECT_EQ(ptr, v.begin() + 1);
}

TEST(vector, insert_test_02) {
  s21::vector<double> s21_vec{1.01, 1.02, 0};
  std::vector<double> std_vec{1.01, 1.02, 0};
  s21_vec.insert(s21_vec.begin() + 1, 2.04);
  std_vec.insert(std_vec.begin() + 1, 2.04);
  std_vec.insert(std_vec.begin() + 4, 77);
  s21_vec.insert(s21_vec.begin() + 4, 77);
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  EXPECT_EQ(s21_vec.at(1), std_vec.at(1));
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(s21_vec.at(i), std_vec.at(i));
  }
}

TEST(vector, erase_test_01) {
  s21::vector<double> v{1.01, 1.02, 1.03};
  v.erase(v.begin() + 1);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.capacity(), 3);
  EXPECT_EQ(v.at(1), 1.03);
}

TEST(vector, swap_test_01) {
  s21::vector<double> v1{1.01, 1.02, 1.03};
  s21::vector<double> v2{1.04, 1.05, 1.06, 1.07};
  v1.swap(v2);
  EXPECT_EQ(v1.size(), 4);
  EXPECT_EQ(v1.capacity(), 4);
  EXPECT_EQ(v1[1], 1.05);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2.capacity(), 3);
  EXPECT_EQ(v2.at(1), 1.02);
}

TEST(vector, at_test_01) {
  s21::vector<double> v{1.01, 1.02, 1.03};
  EXPECT_EQ(v.at(1), 1.02);
}

TEST(vector, shrink_to_fit_test_01) {
  s21::vector<double> v{1.01, 1.02, 1.03};
  v.pop_back();
  v.shrink_to_fit();
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.capacity(), 2);
}

TEST(vector, constructors_1) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(vector, constructors_initializer_vector_1) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(vector, constructors_2) {
  s21::vector<double> s21_vector(5);
  std::vector<double> std_vector(5);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}
TEST(vector, constructors_copy_1) {
  s21::vector<char> s21_vector_1 = {'a', 'b', 'c', 'd'};
  std::vector<char> std_vector_1 = {'a', 'b', 'c', 'd'};
  s21::vector<char> s21_vector_2 = s21_vector_1;
  std::vector<char> std_vector_2 = std_vector_1;

  EXPECT_EQ(s21_vector_1.size(), s21_vector_2.size());
  EXPECT_EQ(std_vector_1.size(), std_vector_2.size());
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();
  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}
TEST(vector, constructors_move_1) {
  s21::vector<char> s21_vector_1 = {'a', 'b', 'c', 'd'};
  std::vector<char> std_vector_1 = {'a', 'b', 'c', 'd'};
  s21::vector<char> s21_vector_2 = std::move(s21_vector_1);
  std::vector<char> std_vector_2 = std::move(std_vector_1);

  EXPECT_EQ(s21_vector_2.size(), std_vector_2.size());
  EXPECT_EQ(s21_vector_1.size(), std_vector_1.size());
  EXPECT_EQ(s21_vector_1.empty(), std_vector_1.empty());
  auto it1 = s21_vector_2.begin();
  auto it2 = std_vector_2.begin();
  while (it1 != s21_vector_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(vector, modifiers_insert_1) {
  s21::vector<int> s21_vector_1 = {'a', 'c', 'd'};
  s21::vector<int> s21_vector_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_vector_1.begin();
  ++it;
  s21_vector_1.insert(it, 'b');
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();
  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_vector_1.size(), s21_vector_2.size());
  s21_vector_1.insert(s21_vector_1.end(), '5');
  EXPECT_EQ(s21_vector_1.back(), '5');
}

TEST(vector, modifiers_erase_1) {
  s21::vector<int> s21_vector_1 = {'a', 'c', 'd'};
  s21::vector<int> s21_vector_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_vector_2.begin();
  ++it;
  s21_vector_2.erase(it);
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();
  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_vector_1.size(), s21_vector_2.size());
}

TEST(vector, modifiers_push_1) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  s21_vector.push_back(5);
  std_vector.push_back(5);
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  auto it1 = s21_vector.begin();
  auto it2 = std_vector.begin();
  while (it1 != s21_vector.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(vector, modifiers_pop_1) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  s21_vector.pop_back();
  std_vector.pop_back();
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  auto it1 = s21_vector.begin();
  auto it2 = std_vector.begin();
  while (it1 != s21_vector.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(vector, modifiers_swap_1) {
  s21::vector<char> s21_vector_1 = {'a', 'b', 'o', 'b', 'a'};
  s21::vector<char> s21_vector_2 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21::vector<char> s21_vector_3 = {'a', 'b', 'o', 'b', 'a'};
  s21::vector<char> s21_vector_4 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21_vector_1.swap(s21_vector_2);
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();
  auto it3 = s21_vector_3.begin();
  auto it4 = s21_vector_4.begin();
  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_vector_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_vector_1.size(), s21_vector_4.size());
  EXPECT_EQ(s21_vector_2.size(), s21_vector_3.size());
}

TEST(vector, constructors_3) {
  s21::vector<int> v;
  ASSERT_EQ(v.size(), 0);
  ASSERT_EQ(v.capacity(), 0);
}

TEST(vector, constructors_4) {
  s21::vector<char> v;
  ASSERT_EQ(v.size(), 0);
  ASSERT_EQ(v.capacity(), 0);
}

TEST(vector, constructors_5) {
  s21::vector<int> v(5);
  ASSERT_EQ(v.size(), 5);
  ASSERT_EQ(v.capacity(), 5);
}

TEST(vector, constructors_6) {
  s21::vector<char> v(5);
  ASSERT_EQ(v.size(), 5);
  ASSERT_EQ(v.capacity(), 5);
}

TEST(vector, constructors_7) {
  s21::vector<int> v = {};
  EXPECT_EQ(v.size(), 0);
}

TEST(vector, constructors_iterator_vector_2) {
  s21::vector<double> v = {3.14};
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v[0], 3.14);
}

TEST(vector, constructors_iterator_vector_3) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(vector, constructors_iterator_vector_4) {
  s21::vector<std::string> v = {"hello", "world"};
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], "hello");
  EXPECT_EQ(v[1], "world");
}

TEST(vector, constructors_iterator_vector_5) {
  struct Person {
    std::string name;
    int age;
  };
  s21::vector<Person> v = {{"Alice", 25}, {"Bob", 30}};
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0].name, "Alice");
  EXPECT_EQ(v[0].age, 25);
  EXPECT_EQ(v[1].name, "Bob");
  EXPECT_EQ(v[1].age, 30);
}

TEST(vector, modifiers_size_1) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2;
  v2.size();
}

TEST(vector, constructors_copy_2) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(v1);
  EXPECT_EQ(v2.size(), v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
  v2[0] = 10;
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v2[0], 10);
  s21::vector<int> v3;
  EXPECT_NO_THROW(s21::vector<int> v4(v3));
}

TEST(vector, constructors_move_2) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(std::move(v1));
  EXPECT_TRUE(v1.empty());
  ASSERT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
  EXPECT_EQ(v2[2], 3);
}

TEST(vector, modifiers_push_back_1) {
  s21::vector<int> v;
  v.push_back(1);
  ASSERT_EQ(v.size(), 1);
  ASSERT_EQ(v.capacity(), 1);
  ASSERT_EQ(v[0], 1);
}

TEST(vector, modifiers_push_back_2) {
  s21::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), 2);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
}

TEST(vector, modifiers_push_back_3) {
  s21::vector<int> v;
  for (int i = 0; i < 10; i++) {
    v.push_back(i);
  }
  EXPECT_EQ(10, v.size());
  EXPECT_EQ(16, v.capacity());
}

TEST(vector, modifiers_push_back_4) {
  s21::vector<std::string> v;
  v.push_back("Hello");
  v.push_back("World");
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), 2);
  ASSERT_EQ(v[0], "Hello");
  ASSERT_EQ(v[1], "World");
}

TEST(vector, modifiers_push_back_5) {
  s21::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.pop_back();
  EXPECT_EQ(2, v.size());
  EXPECT_EQ(4, v.capacity());
  EXPECT_EQ(2, v.back());
}

TEST(vector, modifiers_pop_back_1) {
  s21::vector<char> v;
  v.push_back(4);
  v.push_back(5);
  v.pop_back();
  v.pop_back();
  EXPECT_EQ(0, v.size());
  EXPECT_EQ(2, v.capacity());
}

TEST(vector, modifiers_pop_back_2) {
  s21::vector<double> v;
  for (int i = 0; i < 10; i++) {
    v.push_back(i);
  }
  for (int i = 0; i < 5; i++) {
    v.pop_back();
  }
  EXPECT_EQ(5, v.size());
  EXPECT_EQ(16, v.capacity());
}

TEST(vector, iterators_1) {
  s21::vector<int> v = {1, 2, 3};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, v.end());
}

TEST(vector, iterators_begin_1) {
  s21::vector<std::string> v = {"Hello", "Done", "Report"};
  auto it = v.begin();
  EXPECT_EQ(*it, "Hello");
  ++it;
  EXPECT_EQ(*it, "Done");
  ++it;
  EXPECT_EQ(*it, "Report");
  ++it;
  EXPECT_EQ(it, v.end());
}

TEST(vector, iterators_begin_2) {
  s21::vector<int> v;
  auto it = v.begin();
  EXPECT_EQ(it, v.end());
}

TEST(vector, iterators_begin_3) {
  s21::vector<int> v = {1};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(it, v.end());
}

TEST(vector, iterators_begin_4) {
  s21::vector<int> v = {1, 2, 3};
  auto it1 = v.begin();
  auto it2 = v.begin();
  EXPECT_EQ(it1, it2);
  ++it1;
  EXPECT_NE(it1, it2);
}

TEST(vector, iterators_begin_5) {
  s21::vector<int> v = {1, 2, 3};
  auto it = v.begin();
  *it = 4;
  EXPECT_EQ(*it, 4);
}

TEST(vector, iterators_begin_6) {
  s21::vector<std::string> v = {"Hello", "Done", "Report"};
  auto it = v.begin();
  *it = "Bye";
  EXPECT_EQ(*it, "Bye");
}

TEST(vector, iterators_begin_7) {
  s21::vector<int> v = {1, 2, 3};
  auto it = v.begin();
  int val = *(it++);
  EXPECT_EQ(val, 1);
  EXPECT_EQ(*it, 2);
}

TEST(vector, iterators_begin_8) {
  s21::vector<std::string> v = {"Hello", "Done", "Report"};
  auto it = v.begin();
  std::string val = *(it++);
  EXPECT_EQ(val, "Hello");
  EXPECT_EQ(*it, "Done");
}

TEST(vector, iterators_begin_9) {
  s21::vector<int> v = {1, 2, 3};
  auto it = v.begin();
  ++it;
  int val = *it;
  EXPECT_EQ(val, 2);
  EXPECT_EQ(*it, 2);
}

TEST(vector, iterators_end_1) {
  s21::vector<int> v1 = {1, 2, 3};
  EXPECT_EQ(*(v1.end() - 1), 3);
}

TEST(vector, iterators_end_2) {
  s21::vector<std::string> v1 = {"Hello", "world", "!"};
  EXPECT_EQ(*(v1.end() - 1), "!");
}

TEST(vector, iterators_end_3) {
  s21::vector<int> v1;
  EXPECT_EQ(v1.end(), v1.begin());
}

TEST(vector, modifiers_swap_2) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6};
  s21::vector<int> v1_copy = v1;
  s21::vector<int> v2_copy = v2;

  v1.swap(v2);

  EXPECT_EQ(v1[0], v2_copy[0]);
  EXPECT_EQ(v1[1], v2_copy[1]);
  EXPECT_EQ(v1[2], v2_copy[2]);
  EXPECT_EQ(v2[0], v1_copy[0]);
  EXPECT_EQ(v2[1], v1_copy[1]);
  EXPECT_EQ(v2[2], v1_copy[2]);
}

TEST(vector, modifiers_empty_1) {
  s21::vector<int> v1;
  EXPECT_TRUE(v1.empty());
  v1.push_back(42);
  EXPECT_FALSE(v1.empty());
}

TEST(vector, modifiers_at_1) {
  s21::vector<int> v1 = {1, 2, 3};

  EXPECT_EQ(v1.at(0), 1);
  EXPECT_EQ(v1.at(1), 2);
  EXPECT_EQ(v1.at(2), 3);
  EXPECT_THROW(v1.at(3), std::out_of_range);
}

TEST(vector, modifiers_at_2) {
  s21::vector<std::string> v1 = {"Hello", "world"};

  EXPECT_EQ(v1.at(0), "Hello");
  EXPECT_EQ(v1.at(1), "world");
  EXPECT_THROW(v1.at(2), std::out_of_range);
}

TEST(vector, modifiers_equals_1) {
  s21::vector<int> v1 = {1, 2, 3};
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(v1[2], 3);
  v1[1] = 42;
  EXPECT_EQ(v1[1], 42);
}

TEST(vector, modifiers_equals_2) {
  s21::vector<std::string> v1 = {"Hello", "world"};
  EXPECT_EQ(v1[0], "Hello");
  EXPECT_EQ(v1[1], "world");
  v1[1] = "everyone";
  EXPECT_EQ(v1[1], "everyone");
}

TEST(vector, modifiers_move_1) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6};
  v1 = std::move(v2);
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[1], 5);
  EXPECT_EQ(v1[2], 6);
  EXPECT_EQ(v2.size(), 0);
  EXPECT_TRUE(v2.empty());
}

TEST(vector, modifiers_move_2) {
  s21::vector<std::string> v1 = {"Hello", "world", "!"};
  s21::vector<std::string> v2 = {"Goodbye", "cruel", "world"};
  v1 = std::move(v2);
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1[0], "Goodbye");
  EXPECT_EQ(v1[1], "cruel");
  EXPECT_EQ(v1[2], "world");
  EXPECT_EQ(v2.size(), 0);
  EXPECT_TRUE(v2.empty());
}

TEST(vector, modifiers_move_3) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {1, 2, 3};
  v1 = std::move(v2);
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(v1[2], 3);
  EXPECT_EQ(v2.size(), 0);
  EXPECT_TRUE(v2.empty());
}

TEST(vector, modifiers_front_1) {
  s21::vector<int> v1 = {1, 2, 3};

  EXPECT_EQ(v1.front(), 1);
}

TEST(vector, modifiers_front_2) {
  s21::vector<std::string> v1 = {"Hello", "world"};
  EXPECT_EQ(v1.front(), "Hello");
}

TEST(vector, modifiers_front_3) {
  s21::vector<int> v1;
  EXPECT_THROW(v1.front(), std::logic_error);
}

TEST(vector, modifiers_back_1) {
  s21::vector<int> v1 = {1, 2, 3};
  EXPECT_EQ(v1.back(), 3);
}

TEST(vector, modifiers_back_2) {
  s21::vector<std::string> v1 = {"Hello", "world", "!"};
  EXPECT_EQ(v1.back(), "!");
}

TEST(vector, modifiers_back_3) {
  s21::vector<int> v1;
  EXPECT_THROW(v1.back(), std::logic_error);
}

TEST(vector, modifiers_data_1) {
  s21::vector<int> v1 = {1, 2, 3};
  int* data_ptr = v1.data();
  EXPECT_NE(data_ptr, nullptr);
  EXPECT_EQ(*data_ptr, 1);
  *data_ptr = 42;
  EXPECT_EQ(v1[0], 42);
}

TEST(vector, modifiers_data_2) {
  s21::vector<std::string> v1 = {"Hello", "world", "!"};
  std::string* data_ptr = v1.data();
  EXPECT_NE(data_ptr, nullptr);
  EXPECT_EQ(*data_ptr, "Hello");
  *data_ptr = "Hi";
  EXPECT_EQ(v1[0], "Hi");
}

TEST(vector, modifiers_data_3) {
  s21::vector<int> v1;
  int* data_ptr = v1.data();
  EXPECT_EQ(data_ptr, nullptr);
}

TEST(vector, modifiers_size_2) {
  s21::vector<int> v1 = {1, 2, 3};
  EXPECT_EQ(v1.size(), 3);
  v1.push_back(4);
  EXPECT_EQ(v1.size(), 4);
}

TEST(vector, modifiers_size_3) {
  s21::vector<std::string> v1 = {"Hello", "world", "!"};
  EXPECT_EQ(v1.size(), 3);
  v1.push_back("Howdy");
  EXPECT_EQ(v1.size(), 4);
}

TEST(vector, modifiers_size_4) {
  s21::vector<int> v1;
  EXPECT_EQ(v1.size(), 0);
}

TEST(vector, modifiers_max_size_1) {
  s21::vector<int> v;
  EXPECT_GE(v.max_size(), v.size());
}

TEST(vector, modifiers_max_size_2) {
  s21::vector<int> v;
  EXPECT_GT(v.max_size(), 0);
}

TEST(vector, modifiers_max_size_3) {
  s21::vector<int> v(100);
  EXPECT_GE(v.max_size(), v.size());
}

TEST(vector, modifiers_reverse_1) {
  s21::vector<int> v1 = {1, 2, 3};
  v1.reserve(10);
  EXPECT_GE(v1.capacity(), 10);
  v1.push_back(4);
  EXPECT_EQ(v1.size(), 4);
  EXPECT_EQ(v1.capacity(), 10);
}

TEST(vector, modifiers_reverse_2) {
  s21::vector<std::string> v1;
  v1.reserve(100);
  EXPECT_GE(v1.capacity(), 100);
  v1.push_back("Hello");
  EXPECT_EQ(v1.size(), 1);
  EXPECT_EQ(v1.capacity(), 100);
}

TEST(vector, modifiers_reverse_3) {
  s21::vector<int> v1 = {1, 2, 3};
  v1.reserve(1);
  EXPECT_EQ(v1.capacity(), 3);
}

TEST(vector, modifiers_reverse_4) {
  s21::vector<std::string> v1;
  v1.reserve(1);
  EXPECT_GE(v1.capacity(), 1);
  v1.push_back("Hello");
  EXPECT_EQ(v1.size(), 1);
  EXPECT_EQ(v1.capacity(), 1);
  v1.push_back("my");
  v1.push_back("World");
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1.capacity(), 4);
}

TEST(vector, modifiers_shrink_to_fit_1) {
  s21::vector<int> v = {1, 2, 3};
  v.push_back(4);
  v.push_back(5);
  v.reserve(10);
  v.shrink_to_fit();
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);
}

TEST(vector, modifiers_shrink_to_fit_2) {
  s21::vector<int> v;
  v.reserve(10);
  v.shrink_to_fit();
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
}

TEST(vector, modifiers_shrink_to_fit_3) {
  s21::vector<int> v = {1, 2, 3};
  v.reserve(3);
  v.shrink_to_fit();
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 3);
}

TEST(vector, modifiers_capacity_1) {
  s21::vector<int> v1 = {1, 2, 3};
  EXPECT_GE(v1.capacity(), 3);
  v1.reserve(10);
  EXPECT_GE(v1.capacity(), 10);
}

TEST(vector, modifiers_capacity_2) {
  s21::vector<std::string> v1 = {"Hello", "world", "!"};
  EXPECT_GE(v1.capacity(), 3);
  v1.reserve(100);
  EXPECT_GE(v1.capacity(), 100);
}

TEST(vector, modifiers_capacity_3) {
  s21::vector<int> v1;
  EXPECT_GE(v1.capacity(), 0);
}

TEST(vector, modifiers_clear_1) {
  s21::vector<int> v1 = {1, 2, 3};
  v1.clear();
  EXPECT_TRUE(v1.empty());
}

TEST(vector, modifiers_clear_2) {
  s21::vector<std::string> v1 = {"Hello", "world", "!"};
  v1.clear();
  EXPECT_TRUE(v1.empty());
}

TEST(vector, modifiers_clear_3) {
  s21::vector<int> v1;
  v1.clear();
  EXPECT_TRUE(v1.empty());
}

TEST(vector, modifiers_erase_2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin() + 2;
  v.erase(it);
  ASSERT_EQ(v.size(), 4);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
  ASSERT_EQ(v[2], 4);
  ASSERT_EQ(v[3], 5);
}

TEST(vector, modifiers_erase_3) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin();
  v.erase(it);
  it = v.begin();
  v.erase(it);
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v[0], 3);
  ASSERT_EQ(v[1], 4);
  ASSERT_EQ(v[2], 5);
}

TEST(vector, modifiers_insert_2) {
  s21::vector<int> v = {1, 2, 3};
  auto it = v.insert(v.begin(), 4);
  ASSERT_EQ(*it, 4);
  ASSERT_EQ(v.size(), 4);
  ASSERT_EQ(v[0], 4);
  ASSERT_EQ(v[1], 1);
  ASSERT_EQ(v[2], 2);
  ASSERT_EQ(v[3], 3);
}

TEST(vector, modifiers_insert_3) {
  s21::vector<std::string> v = {"my", "world"};
  auto it = v.insert(v.begin(), "Hello");
  ASSERT_EQ(*it, "Hello");
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v[0], "Hello");
  ASSERT_EQ(v[1], "my");
  ASSERT_EQ(v[2], "world");
}

TEST(vector, modifiers_insert_4) {
  s21::vector<std::string> v = {"Hello", "world"};
  auto it = v.insert(v.begin() + 1, "my");
  ASSERT_EQ(*it, "my");
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v[0], "Hello");
  ASSERT_EQ(v[1], "my");
  ASSERT_EQ(v[2], "world");
}

TEST(vector, modifiers_insert_5) {
  s21::vector<int> v{1, 2, 3, 4};
  auto it = v.insert(v.begin(), 0);
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(*it, 0);
  EXPECT_EQ(v[0], 0);
  EXPECT_EQ(v[1], 1);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 3);
  EXPECT_EQ(v[4], 4);

  it = v.insert(v.begin() + 2, 5);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(*it, 5);
  EXPECT_EQ(v[0], 0);
  EXPECT_EQ(v[1], 1);
  EXPECT_EQ(v[2], 5);
  EXPECT_EQ(v[3], 2);
  EXPECT_EQ(v[4], 3);
  EXPECT_EQ(v[5], 4);

  it = v.insert(v.end(), 6);
  EXPECT_EQ(v.size(), 7);
  EXPECT_EQ(*it, 6);
  EXPECT_EQ(v[0], 0);
  EXPECT_EQ(v[1], 1);
  EXPECT_EQ(v[2], 5);
  EXPECT_EQ(v[3], 2);
  EXPECT_EQ(v[4], 3);
  EXPECT_EQ(v[5], 4);
  EXPECT_EQ(v[6], 6);
}

TEST(vector, modifiers_insert_6) {
  s21::vector<int> v;
  v.insert(v.begin(), 0);
  EXPECT_EQ(v[0], 0);
}

TEST(vector, modifiers_insert_many_back_1) {
  s21::vector<int> vec = {1, 2, 3};
  vec.insert_many_back(4, 5, 6);
  s21::vector<int> vec_1 = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(vec.size(), 6);
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], vec_1[i]);
  }
}

TEST(vector, modifiers_insert_many_back_2) {
  s21::vector<std::string> vec = {"Hello", "my"};
  s21::vector<std::string> vec_1 = {"Hello", "my", "World", "!",
                                    "Hello", "my", "friend"};
  vec.insert_many_back("World", "!", "Hello", "my", "friend");
  EXPECT_EQ(vec.size(), 7);
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], vec_1[i]);
  }
}

//--------------------------------------------------------------------
// insert_many()
//--------------------------------------------------------------------
TEST(vector, modifiers_insert_many_1) {
  s21::vector<int> v{1, 2, 3, 4, 5};
  auto it = v.insert_many(v.begin() + 2, 6);
  EXPECT_EQ(*it, 6);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[2], 6);
  EXPECT_EQ(v[3], 3);
}
TEST(vector, modifiers_insert_many_2) {
  s21::vector<int> v{1, 2, 3, 4, 5};
  auto it = v.insert_many(v.begin() + 5, 6);
  EXPECT_EQ(*it, 6);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[5], 6);
}

TEST(vector, modifiers_insert_many_3) {
  s21::vector<int> v{1, 2, 3, 4, 5};
  auto it = v.insert_many(v.begin(), 0);
  EXPECT_EQ(*it, 0);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[0], 0);
}

TEST(vector, modifiers_insert_many_4) {
  s21::vector<std::string> v{"hello", "world"};
  auto it = v.insert_many(v.begin() + 1, "there");
  EXPECT_EQ(*it, "there");
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[1], "there");
}

TEST(vector, modifiers_insert_many_5) {
  s21::vector<int> v{1, 2, 3, 4, 5};
  auto it = v.insert_many(v.begin() + 2, -10);
  EXPECT_EQ(*it, -10);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[2], -10);
}

TEST(vector, modifiers_insert_many_6) {
  s21::vector<std::string> v{"hello", "world"};

  auto it = v.insert_many(
      v.begin() + 1,
      "this is a very long string that we want to insert into the vector");

  EXPECT_EQ(
      *it, "this is a very long string that we want to insert into the vector");
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], "hello");
  EXPECT_EQ(
      v[1],
      "this is a very long string that we want to insert into the vector");
  EXPECT_EQ(v[2], "world");
}

TEST(vector, modifiers_insert_many_7) {
  s21::vector<std::string> v{"hello", "world"};
  auto it =
      v.insert_many(v.begin() + 1, "this", "is", "a", "list", "of", "words");

  EXPECT_EQ(v.size(), 8);
  EXPECT_EQ(*it, "words");
  EXPECT_EQ(v[0], "hello");
  EXPECT_EQ(v[1], "this");
  EXPECT_EQ(v[2], "is");
  EXPECT_EQ(v[3], "a");
  EXPECT_EQ(v[4], "list");
  EXPECT_EQ(v[5], "of");
  EXPECT_EQ(v[6], "words");
  EXPECT_EQ(v[7], "world");
}
