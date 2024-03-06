#include <gtest/gtest.h>

#include <unordered_set>

#include "../s21_containersplus.h"

TEST(multiset, DefaultConstructor) {
  s21::multiset<int> s;
  std::multiset<int> s2;

  EXPECT_EQ(s.empty(), s2.empty());
}

TEST(multiset, InitializerListConstructor1) {
  s21::multiset<int> s1({1, 2, 3, 4, 5});
  EXPECT_EQ(s1.size(), 5);
  EXPECT_TRUE(s1.find(1) != s1.end());
  EXPECT_TRUE(s1.find(2) != s1.end());
  EXPECT_TRUE(s1.find(3) != s1.end());
  EXPECT_TRUE(s1.find(4) != s1.end());
  EXPECT_TRUE(s1.find(5) != s1.end());

  s21::multiset<std::string> s2({"hello", "world"});
  EXPECT_EQ(s2.size(), 2);
  EXPECT_TRUE(s2.find("hello") != s2.end());
  EXPECT_TRUE(s2.find("world") != s2.end());

  s21::multiset<int> s3({});
  EXPECT_EQ(s3.size(), 0);

  s21::multiset<std::string> s4({"foo", "bar", "baz", "qux"});
  EXPECT_EQ(s4.size(), 4);
  EXPECT_TRUE(s4.find("foo") != s4.end());
  EXPECT_TRUE(s4.find("bar") != s4.end());
  EXPECT_TRUE(s4.find("baz") != s4.end());
  EXPECT_TRUE(s4.find("qux") != s4.end());
}

TEST(multiset, CopyConstructor) {
  s21::multiset<int> s1{1, 2, 3};
  s21::multiset<int> s2(s1);
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(multiset, MoveConstructor) {
  s21::multiset<int> s1{1, 2, 3};
  s21::multiset<int> s2(std::move(s1));
  ASSERT_TRUE(s1.empty());
  ASSERT_EQ(s2.size(), 3);
  ASSERT_TRUE(s2.find(1) != s2.end());
  ASSERT_TRUE(s2.find(2) != s2.end());
  ASSERT_TRUE(s2.find(3) != s2.end());
}

TEST(multiset, Destructor) {
  s21::multiset<int>* s = new s21::multiset<int>{1, 2, 3};
  ASSERT_EQ(s->size(), 3);
  delete s;
}

TEST(multiset, MoveAssignment) {
  s21::multiset<int> s1;
  s1.insert(1);
  s1.insert(2);
  s1.insert(3);
  s21::multiset<int> s2;
  s2.insert(4);
  s2.insert(5);
  s2 = std::move(s1);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
  EXPECT_EQ(s1.size(), 0);
  EXPECT_FALSE(s1.contains(1));
  EXPECT_FALSE(s1.contains(2));
  EXPECT_FALSE(s1.contains(3));
}

TEST(multiset, EmptymultisetMoveAssignment) {
  s21::multiset<int> s1;
  s21::multiset<int> s2;
  s2.insert(1);
  s2 = std::move(s1);
  EXPECT_EQ(s2.size(), 0);
  EXPECT_FALSE(s2.contains(1));
  EXPECT_EQ(s1.size(), 0);
  EXPECT_FALSE(s1.contains(1));
}

TEST(multiset, SwapTest) {
  s21::multiset<int> mymultiset1 = {1, 2, 3};
  s21::multiset<int> mymultiset2 = {4, 5, 6, 7};
  mymultiset1.swap(mymultiset2);
  EXPECT_EQ(mymultiset1.contains(1), 0);
  EXPECT_EQ(mymultiset1.contains(2), 0);
  EXPECT_EQ(mymultiset1.contains(3), 0);
  EXPECT_EQ(mymultiset1.contains(4), 1);
  EXPECT_EQ(mymultiset1.contains(5), 1);
  EXPECT_EQ(mymultiset1.contains(6), 1);
  EXPECT_EQ(mymultiset1.size(), 4);

  EXPECT_EQ(mymultiset2.contains(1), 1);
  EXPECT_EQ(mymultiset2.contains(2), 1);
  EXPECT_EQ(mymultiset2.contains(3), 1);
  EXPECT_EQ(mymultiset2.contains(4), 0);
  EXPECT_EQ(mymultiset2.contains(5), 0);
  EXPECT_EQ(mymultiset2.contains(6), 0);
  EXPECT_EQ(mymultiset2.size(), 3);
}

TEST(multiset, Merge) {
  s21::multiset<int> s1 = {1, 3, 5};
  s21::multiset<int> s2 = {2, 4, 6};
  s1.merge(s2);
  EXPECT_TRUE(s2.empty());
  ASSERT_EQ(s1.size(), 6);
  auto it = s1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
}

TEST(multiset, MergeEmpty) {
  s21::multiset<int> s1 = {1, 3, 5};
  s21::multiset<int> s2;
  s1.merge(s2);
  EXPECT_TRUE(s2.empty());
  ASSERT_EQ(s1.size(), 3);
  auto it = s1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 5);
}

TEST(multiset, MergeAlreadyEmpty) {
  s21::multiset<int> s1 = {1, 3, 5};
  s21::multiset<int> s2;
  s2.merge(s1);
  EXPECT_TRUE(s1.empty());
  EXPECT_FALSE(s2.empty());
}

TEST(multiset, MergeSelf) {
  s21::multiset<int> s1 = {1, 3, 5};
  s1.merge(s1);
  ASSERT_EQ(s1.size(), 3);
  auto it = s1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 5);
}

TEST(multiset, FindEmpty) {
  s21::multiset<std::string> s;
  auto iter = s.find("one");
  EXPECT_EQ(iter, s.end());
}

TEST(multiset, BeginEmptymultiset) {
  s21::multiset<int> multiset;
  EXPECT_EQ(multiset.begin(), multiset.end());
}

TEST(multiset, BeginNonEmptymultiset) {
  s21::multiset<int> multiset = {3, 2, 1};
  EXPECT_EQ(*multiset.begin(), 1);
}

TEST(multiset, Find) {
  s21::multiset<int> s = {1, 2, 3};
  auto iter1 = s.find(1);
  EXPECT_NE(iter1, s.end());

  auto iter2 = s.find(4);
  EXPECT_EQ(iter2, s.end());
}

TEST(multiset, FindMultiple) {
  s21::multiset<int> s = {1, 2, 1};
  auto iter1 = s.find(1);
  EXPECT_NE(iter1, s.end());
  auto iter2 = s.find(2);
  EXPECT_NE(iter2, s.end());
  auto iter3 = s.find(3);
  EXPECT_EQ(iter3, s.end());
}

TEST(multiset, Size) {
  s21::multiset<int> multiset;
  multiset.insert(42);
  multiset.insert(24);
  multiset.insert(84);
  EXPECT_EQ(multiset.size(), 3);
}

TEST(multiset, SizeEmpty) {
  s21::multiset<int> multiset;
  EXPECT_EQ(multiset.size(), 0);
}

TEST(multiset, MaxSizeTest) {
  s21::multiset<int> mymultiset;
  size_t maxSize = mymultiset.max_size();
  EXPECT_GT(maxSize, 0);
  EXPECT_LE(maxSize, std::numeric_limits<size_t>::max());
}

TEST(multiset, Clear) {
  s21::multiset<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(3);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(2));
  EXPECT_FALSE(s.contains(3));
}

TEST(multiset, ClearEmptymultiset) {
  s21::multiset<int> s;
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(2));
  EXPECT_FALSE(s.contains(3));
}

TEST(multiset, Insert) {
  s21::multiset<int> multiset;
  multiset.insert(42);
  multiset.insert(24);
  multiset.insert(84);
  EXPECT_EQ(multiset.size(), 3);
  EXPECT_TRUE(multiset.contains(42));
  EXPECT_TRUE(multiset.contains(24));
  EXPECT_TRUE(multiset.contains(84));
  EXPECT_FALSE(multiset.insert(42).second);
}

TEST(multiset, InsertString) {
  s21::multiset<std::string> s;
  s.insert("foo");
  s.insert("bar");
  s.insert("baz");
  EXPECT_TRUE(s.contains("foo"));
  EXPECT_TRUE(s.contains("bar"));
  EXPECT_TRUE(s.contains("baz"));
  EXPECT_FALSE(s.contains("qux"));
  EXPECT_FALSE(s.contains("xyzzy"));
}

TEST(multiset, InsertEmpty) {
  s21::multiset<int> multiset;
  multiset.insert(42);
  EXPECT_EQ(multiset.size(), 1);
  EXPECT_TRUE(multiset.contains(42));
}

TEST(multiset, InsertDuplicate) {
  s21::multiset<int> multiset;
  multiset.insert(42);
  auto result = multiset.insert(42);
  EXPECT_FALSE(result.second);
}

TEST(multiset, EraseSingleElement) {
  s21::multiset<int> s{5, 4, 3, 2, 1};
  auto it = s.find(3);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(4u, s.size());
  ASSERT_EQ(s.end(), s.find(3));
}

TEST(multiset, EraseSingleElement1) {
  s21::multiset<int> s = {5, 6, 4, 7, 3, 8, 2, 9, 1};
  auto it = s.find(3);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(8u, s.size());
  ASSERT_EQ(s.end(), s.find(3));
}

TEST(multiset, EraseSingleElement2) {
  s21::multiset<int> s = {5, 6, 4, 7, 3, 8, 2, 9, 1};
  auto it = s.find(7);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(8u, s.size());
  ASSERT_EQ(s.end(), s.find(7));
}

TEST(multiset, EraseSingleElement3) {
  s21::multiset<int> s = {5, 8, 6, 7};
  auto it = s.find(8);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(3u, s.size());
  ASSERT_EQ(s.end(), s.find(8));
}

TEST(multiset, EraseFirstElement) {
  s21::multiset<int> s{3, 2, 1};
  auto it = s.begin();
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(2u, s.size());
  ASSERT_EQ(s.end(), s.find(1));
}

TEST(multiset, EraseLastElement) {
  s21::multiset<int> s{1, 2, 3};
  auto it = s.find(3);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(2u, s.size());
  ASSERT_EQ(s.end(), s.find(3));
}

TEST(multiset, constructor_default) {
  s21::multiset<std::string> mset;
  EXPECT_EQ(mset.size(), 0);
  EXPECT_TRUE(mset.empty());
  EXPECT_EQ(mset.begin(), --(mset.end()));
}

TEST(multiset, constructor_initializer_list) {
  s21::multiset<std::string> mset(
      {"a", "b", "c", "d", "e", "f", "a", "b", "c"});
  EXPECT_EQ(mset.size(), 9);
  auto it1 = mset.begin();
  EXPECT_EQ(*it1, "a");
  it1 = --mset.end();
  EXPECT_EQ(*it1, "f");
}

TEST(multiset, constructor_copy) {
  s21::multiset<double> mset({5.11, 5.11, 88.11, -14.01});
  EXPECT_EQ(mset.size(), 4);
  EXPECT_EQ(*mset.begin(), -14.01);
  EXPECT_EQ(*(--mset.end()), 88.11);
}

TEST(multiset, constructor_move) {
  s21::multiset<int> mset({18, 0, -812, 332, -11});
  s21::multiset<int> mset2(std::move(mset));
  s21::multiset<int> mset3({18, 0, -812, 332, -11});
  EXPECT_EQ(mset3.size(), mset2.size());
  EXPECT_TRUE(mset.empty());
  EXPECT_EQ(*mset3.begin(), *mset2.begin());
  EXPECT_EQ(*(--mset3.end()), *(--mset2.end()));
}

TEST(multiset, operator_equal) {
  s21::multiset<int> mset({18, 0, -812, 332, -11});
  s21::multiset<int> mset2;
  mset2 = std::move(mset);
  s21::multiset<int> mset3({18, 0, -812, 332, -11});
  EXPECT_EQ(mset3.size(), mset2.size());
  EXPECT_TRUE(mset.empty());
  EXPECT_EQ(*mset3.begin(), *mset2.begin());
  EXPECT_EQ(*(--mset3.end()), *(--mset2.end()));
}

TEST(multiset, clear) {
  s21::multiset<std::string> mset({"t", "v", "p", "s"});
  mset.clear();
  EXPECT_EQ(mset.size(), 0);
}

TEST(multiset, clear_empty) {
  s21::multiset<std::string> mset;
  mset.clear();
  EXPECT_EQ(mset.size(), 0);
  EXPECT_TRUE(mset.empty());
}

TEST(multiset, erase_no_children_01) {
  s21::multiset<float> mset({5.11, -0.67, 88.11, -14.01});
  auto t = mset.begin();
  ++t;
  mset.erase(mset.begin());
  EXPECT_EQ(*mset.begin(), *t);
}

TEST(multiset, erase_no_children_02) {
  s21::multiset<float> mset({5.11, 5, 11, -0.67, 88.11, -14.01});
  auto t = mset.begin();
  ++t;
  mset.erase(mset.begin());
  EXPECT_EQ(*mset.begin(), *t);
}

TEST(multiset, erase_one_child) {
  s21::multiset<std::string> mset({"h", "t"});
  mset.erase(mset.begin());
  EXPECT_EQ(mset.size(), 1);
  EXPECT_EQ(*mset.begin(), "t");
}

TEST(multiset, erase_two_children) {
  s21::multiset<int> mset({2, 1, 1, 3});
  auto i = ++mset.begin();
  mset.erase(i);
  EXPECT_EQ(mset.size(), 3);
}

TEST(multiset, erase_two_children_02) {
  s21::multiset<int> mset({2, 1, 3});
  auto i = ++mset.begin();
  mset.erase(i);
  EXPECT_EQ(mset.size(), 2);
}

TEST(multiset, erase_end) {
  s21::multiset<int> mset({1, 2, 3});
  auto i = --mset.end();
  mset.erase(i);
  EXPECT_EQ(mset.size(), 2);
}

TEST(multiset, erase_01) {
  s21::multiset<int> mset({2, 1, 3, 3, 4, 4});
  auto i = --mset.end();
  --i;
  mset.erase(i);
  EXPECT_EQ(mset.size(), 5);
}

TEST(multiset, erase_02) {
  s21::multiset<int> mset({2, 1, 3, 4, -2, -4, -4, 0, -1});
  auto i = ++mset.begin();
  mset.erase(i);
  EXPECT_EQ(mset.size(), 8);
}

TEST(multiset, erase_03) {
  s21::multiset<int> mset({2, 1, 3, 4, -2, -4, 0, -1});
  auto i = ++mset.begin();
  mset.erase(i);
  EXPECT_EQ(mset.size(), 7);
}

TEST(multiset, insert_to_empty) {
  s21::multiset<std::string> mset;
  mset.insert("a");
  mset.insert("a");
  mset.insert("a");
  EXPECT_EQ(mset.size(), 3);
  EXPECT_EQ(*mset.begin(), "a");
}

TEST(multiset, insert_01) {
  s21::multiset<double> mset({5.11, -0.67, 5.11, 88.11, -14.01});
  EXPECT_EQ(mset.size(), 5);
}

TEST(multiset, insert_many) {
  s21::multiset<std::string> mset({"hello"});
  mset.insert_many("bye", "bye");
  EXPECT_EQ(mset.size(), 3);
  EXPECT_EQ(*mset.begin(), "bye");
  EXPECT_EQ(*(--mset.end()), "hello");
}

TEST(multiset, begin_post_increment) {
  s21::multiset<std::string> mset({"t", "v", "p", "s"});
  std::multiset<std::string> mset2({"t", "v", "p", "s"});
  auto it = mset.begin();
  auto it2 = mset2.begin();
  it++;
  it2++;
  EXPECT_EQ(*it, *it2);
}

TEST(multiset, begin_pre_increment) {
  s21::multiset<std::string> mset({"t", "v", "p", "s"});
  std::multiset<std::string> mset2({"t", "v", "p", "s"});
  auto it = mset.begin();
  auto it2 = mset2.begin();
  it++;
  it2++;
  it--;
  it2--;
  EXPECT_EQ(*it, *it2);
}

TEST(multiset, increment_01) {
  s21::multiset<int> mset({0,   50,  -50, 25,  75,  -25, -75, 10,  40, 60, 90,
                           -10, -40, -60, -90, 5,   15,  35,  45,  55, 65, 85,
                           95,  -5,  -15, -35, -45, -55, -65, -85, -95});
  for (auto i = mset.begin(); i != mset.end();) {
    ++i;
  }
}

TEST(multiset, decrement) {
  s21::multiset<int> mset({0,   50,  -50, 25,  75,  -25, -75, 10,  40, 60, 90,
                           -10, -40, -60, -90, 5,   15,  35,  45,  55, 65, 85,
                           95,  -5,  -15, -35, -45, -55, -65, -85, -95});
  auto i = mset.end();
  for (int t = 0; t < 31; ++t) {
    --i;
  }
}

TEST(multiset, end) {
  s21::multiset<std::string> mset({"t", "v", "p", "s", "s", "s", "s"});
  std::multiset<std::string> mset2({"t", "v", "p", "s", "s", "s", "s"});
  EXPECT_EQ(*(--mset.end()), *(--mset2.end()));
}

TEST(multiset, end_increment) {
  s21::multiset<std::string> mset({"t", "v", "p", "s", "s"});
  std::multiset<std::string> mset2({"t", "v", "p", "s", "s"});
  auto it = --mset.end();
  auto it2 = --mset2.end();
  it++;
  it2++;
  EXPECT_EQ(*(--mset.end()), *(--mset2.end()));
}

TEST(multiset, size) {
  s21::multiset<int> mset({6, 18, -22, 0, 77, 812, -888, 153, 933, -704});
  std::multiset<int> mset2({6, 18, -22, 0, 77, 812, -888, 153, 933, -704});
  EXPECT_EQ(mset.size(), mset2.size());
}

TEST(multiset, size_empty) {
  s21::multiset<int> mset;
  std::multiset<int> mset2;
  EXPECT_EQ(mset.size(), mset2.size());
  EXPECT_TRUE(mset.empty());
}

TEST(multiset, swap) {
  s21::multiset<std::string> mset({"t", "v", "p", "s"});
  s21::multiset<std::string> mset2({"g"});
  s21::multiset<std::string> mset3({"t", "v", "p", "s"});
  mset.swap(mset2);
  EXPECT_EQ(mset.size(), 1);
  EXPECT_EQ(mset2.size(), mset3.size());
  EXPECT_EQ(*mset2.begin(), *mset3.begin());
  EXPECT_EQ(*(--mset2.end()), *(--mset3.end()));
}

TEST(multiset, merge_01) {
  s21::multiset<std::string> mset({"t", "v", "p", "s"});
  s21::multiset<std::string> mset2({"g"});
  mset.merge(mset2);
  EXPECT_EQ(mset.size(), 5);
  EXPECT_EQ(mset2.size(), 0);
}

TEST(multiset, merge_02) {
  s21::multiset<std::string> mset({"t", "v", "p", "s"});
  s21::multiset<std::string> mset2;
  mset.merge(mset2);
  EXPECT_EQ(mset.size(), 4);
  EXPECT_EQ(mset2.size(), 0);
}

TEST(multiset, merge_03) {
  s21::multiset<std::string> mset;
  s21::multiset<std::string> mset2({"t", "v", "p", "s"});
  mset.merge(mset2);
  EXPECT_EQ(mset.size(), 4);
  EXPECT_EQ(mset2.size(), 0);
}

TEST(multiset, merge_04) {
  s21::multiset<std::string> mset;
  s21::multiset<std::string> mset2;
  mset.merge(mset2);
  EXPECT_EQ(mset.size(), 0);
  EXPECT_EQ(mset2.size(), 0);
}

TEST(multiset, count_01) {
  s21::multiset<std::string> mset({"t", "v", "p", "s"});
  EXPECT_EQ(mset.count("v"), 1);
}

TEST(multiset, count_02) {
  s21::multiset<std::string> mset({"t", "v", "p", "s", "a", "a", "a"});
  EXPECT_EQ(mset.count("a"), 3);
}

TEST(multiset, find_01) {
  s21::multiset<std::string> mset({"t", "v", "p", "w"});
  auto i = mset.begin();
  EXPECT_EQ(i, mset.find("p"));
}

TEST(multiset, find_03) {
  s21::multiset<std::string> mset({"a", "a", "b", "b", "t", "v", "p", "w"});
  auto i = ++mset.begin();
  EXPECT_EQ(i, mset.find("a"));
}

TEST(multiset, contains_true) {
  s21::multiset<std::string> mset({"c", "c", "d", "d", "e"});
  EXPECT_TRUE(mset.contains("c"));
}

TEST(multiset, contains_false) {
  s21::multiset<std::string> mset({"c", "c", "d", "d", "e"});
  EXPECT_FALSE(mset.contains("n"));
}

TEST(multiset, lower_bound) {
  s21::multiset<int> mset({-1, -19, 1, 1, 3, 5, 5, 8, 55, 100});
  std::multiset<int> mset2({-1, -19, 1, 1, 3, 5, 5, 8, 55, 100});
  EXPECT_EQ(*mset.lower_bound(100), *mset2.lower_bound(100));
}

TEST(multiset, lower_bound_02) {
  s21::multiset<int> mset({-1, -19, 1, 1, 3, 5, 5, 8, 55, 102});
  std::multiset<int> mset2({-1, -19, 1, 1, 3, 5, 5, 8, 55, 102});
  EXPECT_EQ(*mset.lower_bound(100), *mset2.lower_bound(100));
}

TEST(multiset, upper_bound) {
  s21::multiset<int> mset({-1, -19, 1, 1, 3, 5, 5, 8, 55, 55, 100});
  std::multiset<int> mset2({-1, -19, 1, 1, 3, 5, 5, 8, 55, 55, 100});
  EXPECT_EQ(*mset.upper_bound(55), *mset2.upper_bound(55));
}

TEST(multiset, range) {
  s21::multiset<std::string> mset(
      {"a", "a", "a", "t", "c", "a", "d", "e", "a", "f"});
  std::multiset<std::string> mset2(
      {"a", "a", "a", "t", "c", "a", "d", "e", "a", "f"});
  EXPECT_EQ(*mset.equal_range("a").first, *mset2.equal_range("a").first);
  EXPECT_EQ(*mset2.equal_range("a").second, *mset.equal_range("a").second);
}
