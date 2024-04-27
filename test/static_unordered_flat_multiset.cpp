//
// g++ -std=c++11 -g -O0 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include static_unordered_flat_multiset.cpp
// valgrind --leak-check=full ./a.out
//

#undef NDEBUG // This is very important. Must be in the first line.

#define SFL_TEST_STATIC_UNORDERED_FLAT_MULTISET
#include "sfl/static_unordered_flat_multiset.hpp"

#include "check.hpp"
#include "print.hpp"

#include "xint.hpp"
#include "xint_xint.hpp"
#include "xobj.hpp"

#include <vector>

void test_static_unordered_flat_multiset()
{
    using sfl::test::xint;
    using sfl::test::xint_xint;
    using sfl::test::xobj;

    PRINT("Test PRIVATE member function emplace_back(Args&&...)");
    {
        sfl::static_unordered_flat_multiset<xint_xint, 5, std::equal_to<xint_xint>> set;

        {
            CHECK(set.empty() == true);
            CHECK(set.full() == false);
            CHECK(set.size() == 0);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 5);
        }

        {
            PRINT(">");
            const auto res = set.emplace_back(10, 1);
            PRINT("<");

            CHECK(res == set.nth(0));
            CHECK(set.empty() == false);
            CHECK(set.full() == false);
            CHECK(set.size() == 1);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 4);
            CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
        }

        {
            PRINT(">");
            const auto res = set.emplace_back(20, 1);
            PRINT("<");

            CHECK(res == set.nth(1));
            CHECK(set.empty() == false);
            CHECK(set.full() == false);
            CHECK(set.size() == 2);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 3);
            CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
            CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
        }

        {
            PRINT(">");
            const auto res = set.emplace_back(30, 1);
            PRINT("<");

            CHECK(res == set.nth(2));
            CHECK(set.empty() == false);
            CHECK(set.full() == false);
            CHECK(set.size() == 3);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 2);
            CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
            CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
            CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);
        }

        {
            PRINT(">");
            const auto res = set.emplace_back(40, 1);
            PRINT("<");

            CHECK(res == set.nth(3));
            CHECK(set.empty() == false);
            CHECK(set.full() == false);
            CHECK(set.size() == 4);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 1);
            CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
            CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
            CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);
            CHECK(set.nth(3)->first == 40); CHECK(set.nth(3)->second == 1);
        }

        {
            PRINT(">");
            const auto res = set.emplace_back(50, 1);
            PRINT("<");

            CHECK(res == set.nth(4));
            CHECK(set.empty() == false);
            CHECK(set.full() == true);
            CHECK(set.size() == 5);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 0);
            CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
            CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
            CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);
            CHECK(set.nth(3)->first == 40); CHECK(set.nth(3)->second == 1);
            CHECK(set.nth(4)->first == 50); CHECK(set.nth(4)->second == 1);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test begin, end, cbegin, cend, nth, index_of");
    {
        sfl::static_unordered_flat_multiset<xint_xint, 100, std::equal_to<xint_xint>> set;

        set.emplace_back(20, 1);
        set.emplace_back(40, 1);
        set.emplace_back(60, 1);

        CHECK(set.size() == 3);
        CHECK(set.nth(0)->first == 20); CHECK(set.nth(0)->second == 1);
        CHECK(set.nth(1)->first == 40); CHECK(set.nth(1)->second == 1);
        CHECK(set.nth(2)->first == 60); CHECK(set.nth(2)->second == 1);

        ///////////////////////////////////////////////////////////////////////

        auto it = set.begin();
        CHECK(it->first == 20); CHECK(it->second == 1); ++it;
        CHECK(it->first == 40); CHECK(it->second == 1); ++it;
        CHECK(it->first == 60); CHECK(it->second == 1); ++it;
        CHECK(it == set.end());

        ///////////////////////////////////////////////////////////////////////

        auto cit = set.cbegin();
        CHECK(cit->first == 20); CHECK(cit->second == 1); ++cit;
        CHECK(cit->first == 40); CHECK(cit->second == 1); ++cit;
        CHECK(cit->first == 60); CHECK(cit->second == 1); ++cit;
        CHECK(cit == set.cend());

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.nth(0)->first == 20); CHECK(set.nth(0)->second == 1);
        CHECK(set.nth(1)->first == 40); CHECK(set.nth(1)->second == 1);
        CHECK(set.nth(2)->first == 60); CHECK(set.nth(2)->second == 1);
        CHECK(set.nth(3) == set.end());

        ///////////////////////////////////////////////////////////////////////

        CHECK(std::next(set.begin(), 0) == set.nth(0));
        CHECK(std::next(set.begin(), 1) == set.nth(1));
        CHECK(std::next(set.begin(), 2) == set.nth(2));
        CHECK(std::next(set.begin(), 3) == set.nth(3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(std::next(set.cbegin(), 0) == set.nth(0));
        CHECK(std::next(set.cbegin(), 1) == set.nth(1));
        CHECK(std::next(set.cbegin(), 2) == set.nth(2));
        CHECK(std::next(set.cbegin(), 3) == set.nth(3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.nth(0) < set.nth(1));
        CHECK(set.nth(0) < set.nth(2));
        CHECK(set.nth(0) < set.nth(3));

        CHECK(set.nth(1) < set.nth(2));
        CHECK(set.nth(1) < set.nth(3));

        CHECK(set.nth(2) < set.nth(3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.index_of(set.nth(0)) == 0);
        CHECK(set.index_of(set.nth(1)) == 1);
        CHECK(set.index_of(set.nth(2)) == 2);
        CHECK(set.index_of(set.nth(3)) == 3);
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test key_eq()");
    {
        {
            sfl::static_unordered_flat_multiset<xint, 100, std::equal_to<xint>> set;

            auto key_eq = set.key_eq();

            CHECK(key_eq(10, 10) == true);
            CHECK(key_eq(10, 20) == false);
            CHECK(key_eq(20, 10) == false);
            CHECK(key_eq(20, 20) == true);
        }

        {
            sfl::static_unordered_flat_multiset<xobj, 100, xobj::equal> set;

            auto key_eq = set.key_eq();

            CHECK(key_eq(xobj(10), 10) == true);
            CHECK(key_eq(xobj(10), 20) == false);
            CHECK(key_eq(xobj(20), 10) == false);
            CHECK(key_eq(xobj(20), 20) == true);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test find, count, contains");
    {
        // xint
        {
            sfl::static_unordered_flat_multiset<xint, 100, std::equal_to<xint>> set;

            set.emplace_back(20);
            set.emplace_back(40);
            set.emplace_back(60);

            CHECK(set.size() == 3);
            CHECK(*set.nth(0) == 20);
            CHECK(*set.nth(1) == 40);
            CHECK(*set.nth(2) == 60);

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.find(10) == set.end());
            CHECK(set.find(20) == set.nth(0));
            CHECK(set.find(30) == set.end());
            CHECK(set.find(40) == set.nth(1));
            CHECK(set.find(50) == set.end());
            CHECK(set.find(60) == set.nth(2));
            CHECK(set.find(70) == set.end());

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.count(10) == 0);
            CHECK(set.count(20) == 1);
            CHECK(set.count(30) == 0);
            CHECK(set.count(40) == 1);
            CHECK(set.count(50) == 0);
            CHECK(set.count(60) == 1);
            CHECK(set.count(70) == 0);

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.contains(10) == false);
            CHECK(set.contains(20) == true);
            CHECK(set.contains(30) == false);
            CHECK(set.contains(40) == true);
            CHECK(set.contains(50) == false);
            CHECK(set.contains(60) == true);
            CHECK(set.contains(70) == false);
        }

        // xobj
        {
            sfl::static_unordered_flat_multiset<xobj, 100, xobj::equal> set;

            set.emplace_back(20);
            set.emplace_back(40);
            set.emplace_back(60);

            CHECK(set.size() == 3);
            CHECK(set.nth(0)->value() == 20);
            CHECK(set.nth(1)->value() == 40);
            CHECK(set.nth(2)->value() == 60);

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.find(10) == set.end());
            CHECK(set.find(20) == set.nth(0));
            CHECK(set.find(30) == set.end());
            CHECK(set.find(40) == set.nth(1));
            CHECK(set.find(50) == set.end());
            CHECK(set.find(60) == set.nth(2));
            CHECK(set.find(70) == set.end());

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.count(10) == 0);
            CHECK(set.count(20) == 1);
            CHECK(set.count(30) == 0);
            CHECK(set.count(40) == 1);
            CHECK(set.count(50) == 0);
            CHECK(set.count(60) == 1);
            CHECK(set.count(70) == 0);

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.contains(10) == false);
            CHECK(set.contains(20) == true);
            CHECK(set.contains(30) == false);
            CHECK(set.contains(40) == true);
            CHECK(set.contains(50) == false);
            CHECK(set.contains(60) == true);
            CHECK(set.contains(70) == false);
        }
    }
}

int main()
{
    test_static_unordered_flat_multiset();
}
