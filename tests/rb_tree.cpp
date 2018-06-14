#include <cassert>
#include <catch.hpp>
#include <sstream>

#include "RBtree.hpp"

TEST_CASE("experiment_1")
{
    tree_t<short> tree;
	
    tree.insert(5);
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.insert(7);
    tree.insert(6);
    tree.insert(8);
	
    REQUIRE(tree.find(5) == true);
    REQUIRE(tree.find(8) == true);
    REQUIRE(tree.find(0) == false);
}

TEST_CASE("action_1")
{
    tree_t<int> tree;
	
	action(tree, "+ 3");
	
	action(tree, "+ 4");
	
	action(tree, "+ 2");
	
	std::ostringstream stream_o;
	action(tree, "? 2", stream_o);
	
	REQUIRE(stream_o.str() == "true");
}

TEST_CASE("action_2")
{
    tree_t<int> tree;
	
	action(tree, "+ 3");
	
	action(tree, "+ 4");
	
	action(tree, "+ 2");
	
	std::ostringstream stream_o;
	action(tree, "? 5", stream_o);
		
	REQUIRE(stream_o.str() == "false");
}

TEST_CASE("balance_1")
{
    tree_t<int> tree;
	
	action(tree, "+ 3");
	
	action(tree, "+ 2");
	
	action(tree, "+ 1");
	
	std::string out {
		
		"--------3\n"
		"----2\n"
		"--------1\n"
	};

	std::ostringstream stream_o;
	action(tree, "=", stream_o);
	
	REQUIRE(stream_o.str() == out);
}

TEST_CASE("balance_2")
{
    tree_t<int> tree;
	
	action(tree, "+ 5");
	
	action(tree, "+ 3");
	
	action(tree, "+ 6");
	
	action(tree, "+ 8");
	
	action(tree, "+ 9");
	
	action(tree, "+ 10");
	
	action(tree, "+ 12");
	
	action(tree, "+ 13");
	
	std::string out {
		
		"----------------13\n"
		"------------12\n"
		"--------10\n"
		"------------9\n"
		"----8\n"
		"------------6\n"
		"--------5\n"
		"------------3\n"
	};

	std::ostringstream stream_o;
	action(tree, "=", stream_o);
	
	REQUIRE(stream_o.str() == out);
}

TEST_CASE("balance_3")
{
    tree_t<int> tree;
	
	action(tree, "+ 1");
	
	action(tree, "+ 2");
	
	action(tree, "+ 3");
	
	action(tree, "+ 4");
	
	action(tree, "+ 5");
	
	std::string out {
		
		"------------5\n"
		"--------4\n"
		"------------3\n"
		"----2\n"
		"--------1\n"
	};

	std::ostringstream stream_o;
	action(tree, "=", stream_o);
	
	REQUIRE(stream_o.str() == out);
}

TEST_CASE("balance_4")
{
    tree_t<int> tree;
	
	action(tree, "+ 10");
	
	action(tree, "+ 85");
	
	action(tree, "+ 15");
	
	action(tree, "+ 70");
	
	action(tree, "+ 20");
	
	action(tree, "+ 60");
	
	action(tree, "+ 30");
	
	action(tree, "+ 50");
	
	action(tree, "+ 65");
	
	action(tree, "+ 80");
	
	action(tree, "+ 90");
	
	action(tree, "+ 40");
	
	action(tree, "+ 5");
	
	action(tree, "+ 55");
	
	std::string out {
		
		"----------------90\n"
		"------------85\n"
		"----------------80\n"
		"--------70\n"
		"----------------65\n"
		"------------60\n"
		"--------------------55\n"
		"----------------50\n"
		"--------------------40\n"
		"----30\n"
		"------------20\n"
		"--------15\n"
		"------------10\n"
		"----------------5\n"
	};

	std::ostringstream stream_o;
	action(tree, "=", stream_o);
	
	REQUIRE(stream_o.str() == out);
}

TEST_CASE("delition_1")
{
    tree_t<int> tree;
	
	action(tree, "+ 1");
	
	action(tree, "+ 2");
	
	action(tree, "+ 3");
	
	action(tree, "+ 4");
	
	action(tree, "+ 5");
	
	action(tree, "- 4");
	
	std::string out {
		
		"--------5\n"
		"------------3\n"
		"----2\n"
		"--------1\n"
	};

	std::ostringstream stream_o;
	action(tree, "=", stream_o);
	
	REQUIRE(stream_o.str() == out);
}

TEST_CASE("delition_2")
{
    tree_t<int> tree;
	
	action(tree, "+ 7");
	
	action(tree, "+ 3");
	
	action(tree, "+ 8");
	
	action(tree, "+ 9");
	
	action(tree, "+ 1");
	
	action(tree, "+ 0");
	
	action(tree, "- 1");
	
	std::string out {
		
		"------------9\n"
		"--------8\n"
		"----7\n"
		"--------3\n"
		"------------0\n"
	};

	std::ostringstream stream_o;
	action(tree, "=", stream_o);
	
	REQUIRE(stream_o.str() == out);
}

TEST_CASE("delition_when_brother_is_black_and_his_right_son_is_red")
{
    tree_t<int> tree;
	
	action(tree, "+ 1");
	
	action(tree, "+ 2");
	
	action(tree, "+ 3");
	
	action(tree, "+ 4");
	
	action(tree, "+ 5");
	
	action(tree, "+ 6");
	
	action(tree, "+ 7");
	
	action(tree, "+ 8");
	
	action(tree, "+ 9");
	
	action(tree, "+ 10");
	
	action(tree, "+ 11");
	
	action(tree, "+ 0");
	
	action(tree, "- 3");
	
	action(tree, "- 2");
	
	std::string out {
		
		"----------------11\n"
		"------------10\n"
		"----------------9\n"
		"--------8\n"
		"------------7\n"
		"----6\n"
		"------------5\n"
		"--------4\n"
		"------------1\n"
		"----------------0\n"
	};

	std::ostringstream stream_o;
	action(tree, "=", stream_o);
	
	REQUIRE(stream_o.str() == out);
}

TEST_CASE("delition_when_brother_is_black_and_his_sons")
{
    tree_t<int> tree;
	
	action(tree, "+ 5");
	
	action(tree, "+ 3");
	
	action(tree, "+ 7");
	
	action(tree, "+ 8");
	
	action(tree, "- 8");
	
	action(tree, "- 3");
	
	std::string out {
		"--------7\n"
		"----5\n"
	};

	std::ostringstream stream_o;
	action(tree, "=", stream_o);
	
	REQUIRE(stream_o.str() == out);
}

TEST_CASE("delition_when_brother_is_red")
{
    tree_t<int> tree;
	
	action(tree, "+ 5");
	
	action(tree, "+ 3");
	
	action(tree, "+ 7");
	
	action(tree, "+ 8");
	
	action(tree, "+ 6");
	
	action(tree, "+ 2");
	
	action(tree, "+ 1");
	
	action(tree, "+ 9");
	
	action(tree, "- 2");
	
	std::string out {
		
		"----------------9\n"
		"------------8\n"
		"--------7\n"
		"------------6\n"
		"----5\n"
		"--------3\n"
		"------------1\n"
	};

	std::ostringstream stream_o;
	action(tree, "=", stream_o);
	
	REQUIRE(stream_o.str() == out);
}

TEST_CASE("exception")
{
    tree_t<int> tree;
	
    REQUIRE_THROWS_AS(action(tree, "& 2"), std::invalid_argument);
}
