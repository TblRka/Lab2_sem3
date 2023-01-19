#include "pch.h"
#include "CppUnitTest.h"
#include "Histogram.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HistogramTest
{
	TEST_CLASS(HistogramTests)
	{
	public:

		TEST_METHOD(Filling)
		{
			srand(time(NULL));
			struct KeyGetter {
				char operator()(const std::string& str) {
					if (str.empty()) return ' ';
					return str[0];
				}
			};
			DynamicArray<Pair<char, char>> xseries({ Pair<char,char>{'a', 'f'},Pair<char,char>{'g', 'k'},Pair<char,char>{'l', 'p'},Pair<char,char>{'q', 'v'},Pair<char,char>{'w', 'z'} });
			DynamicArray<std::string> str_arr;s
			for (int i = 0; i < 10000; ++i) {
				str_arr.Append(generate<std::string>());
			}
			Histogram<std::string, char, KeyGetter> hist(xseries, str_arr);
			for (int i = 0; i < 1000; ++i) {
				hist.insert(generate<std::string>());
			}
			char c = 'c';
			char i = 'i';
			char o = 'o';
			char x = 'x';
			char r = 'r';
			hist.remove(c);
			hist.remove(i);
			hist.remove(o);
			hist.remove(x);
			hist.remove(r);
		}
		TEST_METHOD(Functions) {
			DynamicArray<Pair<int, int>> xseries({ Pair<int, int>{1, 20}, Pair<int, int>{21, 40},
												Pair<int, int>{41, 60},Pair<int, int>{61, 80},
												Pair<int, int>{81, 100} });
			DynamicArray<Student> objs({ Student("Yan", 19), Student("Alexey", 19),
			Student("Andrey", 20), Student("Artem", 40), Student("Nikita", 28),
			Student("Artem", 42), Student("Michail", 55), Student("Ivan", 63),
			Student("Jimmy", 69), Student("Maxim", 24), Student("Rob", 82),
			Student("John", 31), Student("LordByron", 49) });
			Histogram<Student, int, Age> hist(xseries, objs);
			double mean1 = 19 + 19 + 20;
			double mean2 = 40 + 28 + 24 + 31;
			double mean3 = 42 + 55 + 49;
			double mean4 = 69 + 63;
			double mean5 = 82;
			Assert::IsTrue(hist.mean(Pair<int, int>{1, 20}) == mean1 / 3, L"First column, mean");
			Assert::IsTrue(hist.mean(Pair<int, int>{21, 40}) == mean2 / 4, L"Second column, mean");
			Assert::IsTrue(hist.mean(Pair<int, int>{41, 60}) == mean3 / 3, L"Third column, mean");
			Assert::IsTrue(hist.mean(Pair<int, int>{61, 80}) == mean4 / 2, L"First column, mean");
			Assert::IsTrue(hist.mean(Pair<int, int>{81, 100}) == mean5, L"First column, mean");

			Assert::IsTrue(hist.max(Pair<int, int>{1, 20}) == 20, L"First column, max");
			Assert::IsTrue(hist.max(Pair<int, int>{21, 40}) == 40, L"Second column, max");
			Assert::IsTrue(hist.max(Pair<int, int>{41, 60}) == 55, L"Third column, max");
			Assert::IsTrue(hist.max(Pair<int, int>{61, 80}) == 69, L"First column, max");
			Assert::IsTrue(hist.max(Pair<int, int>{81, 100}) == 82, L"First column, max");

			Assert::IsTrue(hist.min(Pair<int, int>{1, 20}) == 19, L"First column, min");
			Assert::IsTrue(hist.min(Pair<int, int>{21, 40}) == 24, L"Second column, min");
			Assert::IsTrue(hist.min(Pair<int, int>{41, 60}) == 42, L"Third column, min");
			Assert::IsTrue(hist.min(Pair<int, int>{61, 80}) == 63, L"First column, min");
			Assert::IsTrue(hist.min(Pair<int, int>{81, 100}) == 82, L"First column, min");

			Assert::IsTrue(hist.get_columns_count() == 5, L"Get columns count method");
			Assert::IsTrue(hist.get_count() == 13, L"Get count method");
		}
	};
}
