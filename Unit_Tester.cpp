/*
Kenneth White
CSCD 305 8:00 Spring 18
Assignment 100 - Putting it all together

NOTE TO GRADER:
	As part of the unit tests I intentionally give methods invalid indices, which are caught and thrown from the method.
	These exceptions can register as memory leaks for the test cases in which they are used as VS maintains a pointer to the Exception. 
	I have these test cases disabled using a global	bool. To enable them change the bool g_test_assertions to true and rerun.

	All of the requirements listed on canvas are labeled in comments below

Shortcomings :
	None that I know of, barring the memory issue with exception testing noted above.

Compilation details :
	Compile using g++ *.cpp

	I used Microsoft Visual C++ compiler via Visual Studio 2017
	I also used g++ version 7.2.0 via MinGW6100


Memory Checking
	Visual Leak Detector Version 2.5.1 installed.

	'Unit_Tester.exe' (Win32): Loaded
	The thread 0xb70cc has exited with code 0 (0x0).
	The thread 0x9c7100 has exited with code 0 (0x0).
	The thread 0x100316c has exited with code 0 (0x0).
	No memory leaks detected.
	Visual Leak Detector is now exiting.

Results:

	Visual Leak Detector read settings from: C:\Program Files (x86)\Visual Leak Detector\vld.ini
	Visual Leak Detector Version 2.5.1 installed.
	[Index 0, Index 1]
	Foreach on empty list

	===============================================================================
	All tests passed (172 assertions in 18 test cases)

	'Unit_Tester.exe' (Win32): Loaded
	The thread 0xb70cc has exited with code 0 (0x0).
	The thread 0x9c7100 has exited with code 0 (0x0).
	The thread 0x100316c has exited with code 0 (0x0).
	No memory leaks detected.
	Visual Leak Detector is now exiting.

*/

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#include "LinkedList.h"
#include "BigInteger.h"

using namespace std;
#include "BigInteger.h"

bool g_test_assertions = false;

TEST_CASE("Test Constructor", "[constructor]") {
	SECTION("Construct Type char") {
		LinkedList<char> test;
	}

	SECTION("Construct Type BigInteger") {
		LinkedList<BigInteger> test = LinkedList<BigInteger>();
	}
}

// 2 - Copy Constructor
TEST_CASE("Assignment CTOR", "[assignment CTOR]") {
	SECTION("EmptyList copied to EmptyList") {
		LinkedList<int> list;

		LinkedList<int> result(list);

		REQUIRE(list.getSize() == 0);

		REQUIRE(result.getSize() == 0);
	}

	SECTION("LL copied into Empty LL") {
		LinkedList<int> list;
		list.add(5555);
		list.add(100);

		LinkedList<int> result(list);

		REQUIRE(list[0] == 5555);
		REQUIRE(list[1] == 100);

		REQUIRE(result[0] == 5555);
		REQUIRE(result[1] == 100);
	}
	SECTION("Big Integer Copy") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111")); 
		list.add(BigInteger("222222"));

		LinkedList<BigInteger> result(list);

		REQUIRE(list[0] == BigInteger("111111"));
		REQUIRE(list[1] == BigInteger("222222"));

		REQUIRE(result[0] == BigInteger("111111"));
		REQUIRE(result[1] == BigInteger("222222"));
	}
}

// 3 - Move Constructor
TEST_CASE("Move Constructor, [Move CTOR]") {
	SECTION("Move Empty List") {
		LinkedList<int> list;

		LinkedList<int> result = std::move(list);

		REQUIRE(result.getSize() == 0);

		REQUIRE(list.getSize() == 0);
	}

	SECTION("Move List size 1") {
		LinkedList<int> list;
		list.add(1);

		LinkedList<int> result = std::move(list);

		REQUIRE(result.getSize() == 1);
		REQUIRE(result[0] == 1);

		REQUIRE(list.getSize() == 0);
	}

	SECTION("Move List size: 3") {
		LinkedList<int> list;
		list.add(1);
		list.add(3);
		list.add(2);

		LinkedList<int> result = std::move(list);

		REQUIRE(result.getSize() == 3);
		REQUIRE(result[0] == 1);
		REQUIRE(result[1] == 3);
		REQUIRE(result[2] == 2);

		REQUIRE(list.getSize() == 0);
	}
	SECTION("Big Integer Move") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));

		LinkedList<BigInteger> result= std::move(list);

		REQUIRE(list.getSize() == 0);
		

		REQUIRE(result[0] == BigInteger("111111"));
		REQUIRE(result[1] == BigInteger("222222"));
		REQUIRE(result.getSize() == 2);
	}
}

// 4 - Destructor
TEST_CASE("Destructor", "[destructor]") {
	SECTION("Destruct empty list") {
		LinkedList<int> list;
		list.~LinkedList();
		REQUIRE(list.getSize() == 0);
	}

	SECTION("Destruct LL size 2") {
		LinkedList<int> list;
		list.add(5555);
		list.add(100);

		list.~LinkedList();
		REQUIRE(list.getSize() == 0);
	}

	SECTION("Destruct LL size 1") {
		LinkedList<int> list;
		list.add(5555);

		list.~LinkedList();
		REQUIRE(list.getSize() == 0);
	}
	SECTION("Big Integer Destruct") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));
		list.~LinkedList();
		REQUIRE(list.getSize() == 0);		
	}
}

// 5 - Assignment Operator
TEST_CASE("Assignment Operator", "[assignment operator]") {
	SECTION("Assign Empty List to Empty List") {
		LinkedList<int> list;
		LinkedList<int> result;

		list.operator=(result);

		REQUIRE(list.getSize() == 0);

		REQUIRE(result.getSize() == 0);
	}

	SECTION("Assign size 2 to Empty") {
		LinkedList<int> list;
		LinkedList<int> result;
		list.add(55);
		list.add(6);

		result.operator=(list);

		REQUIRE(list[0] == 55);
		REQUIRE(list[1] == 6);

		REQUIRE(result[0] == 55);
		REQUIRE(result[1] == 6);
	}

	SECTION("Assign size 2 into size 2") {
		LinkedList<int> list;
		LinkedList<int> result;
		list.add(55);
		list.add(100);

		result.add(1);
		result.add(2);

		result.operator=(list);

		REQUIRE(list[0] == 55);
		REQUIRE(list[1] == 100);

		REQUIRE(result[0] == 55);
		REQUIRE(result[1] == 100);
	}

	SECTION("Big Integer Assign") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));

		LinkedList<BigInteger> result = list;

		REQUIRE(list[0] == BigInteger("111111"));
		REQUIRE(list[1] == BigInteger("222222"));

		REQUIRE(result[0] == BigInteger("111111"));
		REQUIRE(result[1] == BigInteger("222222"));
	}
}

// 6 - move = operator overload (&&)
TEST_CASE("Move assignment operator overload (&&)", "[move][assignment]") {
	SECTION("Empty to Empty") {
		LinkedList<char> list;

		LinkedList<char> result;
		result.operator=(std::move(list));

		REQUIRE(result.getSize() == 0);

		//ensure old list is empty
		REQUIRE(list.getSize() == 0);
	}

	SECTION("Move size 2 to Empty") {
		LinkedList<string> list;
		list.add("55");
		list.add("100");

		LinkedList<string> result;
		result.operator=(std::move(list));

		REQUIRE(result.getSize() == 2);
		REQUIRE(result[0] == "55");
		REQUIRE(result[1] == "100");

		//ensure old list is empty
		REQUIRE(list.getSize() == 0);
	}

	SECTION("Move size 2 to size 2") {
		LinkedList<string> list;
		list.add("55");
		list.add("100");

		LinkedList<string> result;
		result.add("100");
		result.add("3");

		result.operator=(std::move(list));

		REQUIRE(result.getSize() == 2);
		REQUIRE(result[0] == "55");
		REQUIRE(result[1] == "100");

		//insure old list is empty
		REQUIRE(list.getSize() == 0);
	}

	SECTION("Big Integer Copy") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));

		LinkedList<BigInteger> result(list);

		REQUIRE(list[0] == BigInteger("111111"));
		REQUIRE(list[1] == BigInteger("222222"));

		REQUIRE(result[0] == BigInteger("111111"));
		REQUIRE(result[1] == BigInteger("222222"));
	}
}

// 7 - Equals Operator
TEST_CASE("Test Equals", "[equals]") {
	SECTION("Size 2 == size 2") {
		int toAdd = 55;
		int toAdd2 = 55;

		LinkedList<int> list;

		list.add(toAdd);
		list.add(toAdd);

		LinkedList<int> temp2;

		temp2.add(toAdd2);
		temp2.add(toAdd2);

		REQUIRE((list == temp2));
	}

	SECTION("Empty == Empty") {
		LinkedList<int> list;

		LinkedList<int> temp2;

		REQUIRE((list == temp2));
	}

	SECTION("Size 1 == Empty") {
		string toAdd = "123";

		LinkedList<string> list;
		list.add(toAdd);

		LinkedList<string> temp2;

		REQUIRE(!(list == temp2));
	}

	SECTION("Same 2 items, different order") {
		string str1 = "55";
		string str2 = "100";

		LinkedList<std::string> list;
		list.add(str1);
		list.add(str2);

		LinkedList<std::string> temp2;
		temp2.add(str2);
		temp2.add(str1);

		REQUIRE(!(list == temp2));
	}
	SECTION("Big Integer ==, equal list") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));

		LinkedList<BigInteger> result;
		result.add(BigInteger("111111"));
		result.add(BigInteger("222222"));

		REQUIRE((list == result));
	}
	SECTION("Big Integer ==, not equal list") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));

		LinkedList<BigInteger> result;
		result.add(BigInteger("222222"));
		result.add(BigInteger("111111"));
		

		REQUIRE(!(list == result));
	}
}

// 8 - [] Operator
TEST_CASE("Test [] operator", "[operator][get]") {
	SECTION("Retrieve using []") {
		LinkedList<std::string> test;

		string testStr = "test";
		test.add(testStr);

		string res = test[0];

		REQUIRE(res == testStr);
	}

	SECTION("Retriece [0] from list size 2") {
		LinkedList<std::string> test;

		string testStr = "test";
		test.add(testStr);

		string testStr2 = "test2";
		test.add(testStr2);

		string res = test[0];

		REQUIRE(res == testStr);
	}

	SECTION("Retrieving [1] from list size 2") {
		LinkedList<std::string> test;

		string testStr = "test";
		test.add(testStr);

		string testStr2 = "test2";
		test.add(testStr2);

		string res = test[1];

		REQUIRE(res == testStr2);
	}
	SECTION("Big Integer Assign[0]") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));

		BigInteger res = list[0];

		REQUIRE(list[0] == res);
	}
}

// 8 - [] Operator
TEST_CASE("Test Subscript Set", "[operator][set]") {
	SECTION("Assign [0]") {
		string testStr = "test";
		string toReplace = "test2";

		LinkedList<std::string> test;
		test.add(testStr);

		test[0] = toReplace;

		REQUIRE(test[0] == toReplace);
	}

	SECTION("Assign [0] over old data") {
		string testStr = "test";
		string toReplace = "test2";

		LinkedList<std::string> test;
		test.add(testStr);
		test.add(toReplace);

		test[0] = toReplace;

		REQUIRE(test[0] == toReplace);
	}

	SECTION("Assign [1] in size 2") {
		string testStr = "test";
		string toReplace = "test2";

		LinkedList<std::string> test;
		test.add(testStr);
		test.add(toReplace);

		test[1] = testStr;

		REQUIRE(test[1] == testStr);
	}

	SECTION("Assign [1] in size 2") {
		string testStr = "test";
		string toReplace = "test2";

		LinkedList<std::string> test;
		test.add(toReplace);
		test.add(testStr);

		test[1] = toReplace;

		REQUIRE(test[1] == toReplace);
	}

	SECTION("Big Integer Assign[0]") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));

		list[0] = BigInteger("333333");

		REQUIRE(list[0] == BigInteger("333333"));
		REQUIRE(list[1] == BigInteger("222222"));
	}
}

// 9 + Operator
TEST_CASE("Addition", "[addition][operator]") {
	SECTION("Empty List + Empty List") {
		LinkedList<std::string> list;

		LinkedList<std::string> temp2;

		LinkedList<std::string> result = (list + temp2);

		LinkedList<std::string> testList;

		REQUIRE((result == testList));
		REQUIRE(result.getSize() == 0);
	}

	SECTION("Size 1 + size 0") {
		LinkedList<std::string> list;
		string str1 = "55";
		list.add(str1);

		LinkedList<std::string> temp2;

		LinkedList<std::string> result = (list + temp2);

		LinkedList<std::string> testList;
		testList.add(str1);

		REQUIRE((result == testList));
		REQUIRE(result.getSize() == 1);
	}

	SECTION("Size 0 + size 1") {
		LinkedList<std::string> list;

		LinkedList<std::string> temp2;
		string str1 = "55";
		temp2.add(str1);

		LinkedList<std::string> result = (list + temp2);

		LinkedList<std::string> testList;
		testList.add(str1);

		REQUIRE((result == testList));
		REQUIRE(result.getSize() == 1);
	}

	SECTION("Size 2 + size 1") {
		string str1 = "1";
		string str2 = "2";
		string str3 = "3";

		LinkedList<std::string> list;
		list.add(str1);
		list.add(str2);

		LinkedList<std::string> temp2;
		temp2.add(str3);

		LinkedList<std::string> result = (list + temp2);

		LinkedList<std::string> testList;
		testList.add(str1);
		testList.add(str2);
		testList.add(str3);

		REQUIRE((result == testList));
		REQUIRE(result.getSize() == 3);
	}
	SECTION("Big Integer + Big Integer") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));

		LinkedList<BigInteger> result;
		result.add(BigInteger("333333"));
		result.add(BigInteger("444444"));

		LinkedList<BigInteger> ll = list + result;

		REQUIRE(ll[0] == BigInteger("111111"));
		REQUIRE(ll[1] == BigInteger("222222"));
		REQUIRE(ll[2] == BigInteger("333333"));
		REQUIRE(ll[3] == BigInteger("444444"));
	}
}

// 10 - Output Operator
//Utilize a toString Method to allow easier unit testing of <<
TEST_CASE("Output Operator", "[output][operator]") {
	SECTION("Size 0") {
		LinkedList<std::string> list;
		string result = list.toString();

		REQUIRE("[Empty List]" == result);
	}

	SECTION("Size 1") {
		int toAdd = 55;
		LinkedList<int> list;
		list.add(toAdd);

		string result = list.toString();

		REQUIRE("[55]" == result);
	}

	SECTION("Print to Screen") {
		LinkedList<string> list;
		list.add("Index 0");
		list.add("Index 1");

		cout << list << std::endl;
	}
	SECTION("Big Integer List <<") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));

		string result = list.toString();

		REQUIRE(result == "[111111, 222222]");
	}
}

// 11 - add(data) method
TEST_CASE("Test Add(data)", "[add]") {
	SECTION("Add 'waffle' to empty list") {
		string toAdd = "waffle";

		LinkedList<string> temp;
		temp.add(toAdd);

		REQUIRE(temp[0] == toAdd);
		REQUIRE(temp.getSize() == 1);
	}

	SECTION("Add 99 to list size 1") {
		int toAdd = 55;
		int toAdd2 = 99;

		LinkedList<int> temp;
		temp.add(toAdd);
		temp.add(toAdd2);

		REQUIRE(temp[1] == toAdd2);
		REQUIRE(temp.getSize() == 2);
	}

	SECTION("Big Integer Add ") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));

		REQUIRE(list[0] == BigInteger("111111"));
		REQUIRE(list[1] == BigInteger("222222"));
	}

}

// 12 - add(data, index)
TEST_CASE("Test Add add(data,index)", "[add][add(data,index)]") {

	if (g_test_assertions) {
		SECTION("Add to invalid index") {
			int toAdd = 55;

			LinkedList<int> temp;
			CHECK_THROWS(temp.add(33, toAdd));
		}
	}


	SECTION("Add <int>55 to empty list") {
		int toAdd = 55;

		LinkedList<int> temp;
		temp.add(0, toAdd);

		REQUIRE(temp[0] == toAdd);
		REQUIRE(temp.getSize() == 1);
	}

	SECTION("Add <int>6 to end of list with size:1") {
		int toAdd = 55;
		int toAdd6 = 6;

		LinkedList<int> temp;
		temp.add(0, toAdd);
		temp.add(1, toAdd6);

		REQUIRE(temp[1] == toAdd6);
		REQUIRE(temp.getSize() == 2);
	}

	SECTION("Add <int>100 to middle of list with size:2") {
		int toAdd = 55;
		int toAdd100 = 100;
		int toAdd6 = 6;

		LinkedList<int> temp;
		temp.add(0, toAdd);
		temp.add(1, toAdd6);
		temp.add(1, toAdd100);

		REQUIRE(temp[1] == toAdd100);
		REQUIRE(temp.getSize() == 3);
	}

	SECTION("Add <int>100 to front of list with size:1") {
		int toAdd = 55;
		int toAdd100 = 100;

		LinkedList<int> temp;
		temp.add(0, toAdd);
		temp.add(0, toAdd100);

		REQUIRE(temp[0] == toAdd100);
		REQUIRE(temp.getSize() == 2);
	}

	SECTION("Big Integer Add ") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111"));
		BigInteger b = BigInteger("222222");
		list.add(1, b);
		b = BigInteger("333333");
		list.add(0, b);

		REQUIRE(list[0] == BigInteger("333333"));
		REQUIRE(list[2] == BigInteger("222222"));
	}

}


// 13 - remove(data) return bool
TEST_CASE("Remove data", "[remove][remove(data)]") {
	SECTION("Remove from Empty List") {
		LinkedList<string> list;

		string toRemove = "55";

		bool result = list.remove(toRemove);

		REQUIRE(result == false);
	}

	SECTION("Remove from size 1, data not in list") {
		LinkedList<string> list;
		list.add("waffles");

		string toRemove = "FNF";

		bool result = list.remove(toRemove);

		REQUIRE(result == false);
	}

	SECTION("Remove from size 1, data in list") {
		LinkedList<string> list;
		list.add("wow");

		string toRemove = "wow";

		bool result = list.remove(toRemove);

		REQUIRE(result);
		REQUIRE(list.getSize() == 0);
	}

	SECTION("Remove from size 3, data in list") {
		LinkedList<string> list;
		list.add("incredible");
		list.add("wow");
		list.add("cscd");

		string toRemove = "wow";

		bool result = list.remove(toRemove);

		REQUIRE(result);
		REQUIRE(list.getSize() == 2);

		REQUIRE(list[0] == "incredible");
		REQUIRE(list[1] == "cscd");
	}

	SECTION("Remove from end of list size 3") {
		LinkedList<string> list;
		list.add("wow");
		list.add("two");
		list.add("three");

		string toRemove = "three";

		bool result = list.remove(toRemove);

		REQUIRE(result);
		REQUIRE(list.getSize() == 2);

		REQUIRE(list[0] == "wow");
		REQUIRE(list[1] == "two");
	}
}

// 14 - remove(index) return removed data
TEST_CASE("Remove by index, return data", "[remove][remove(index)]") {
	
	if (g_test_assertions) {//This test can be percieved as a leak in some memory checkers
		SECTION("Remove from empty list") {
			LinkedList<char> list;
			CHECK_THROWS(list.removeIndex(0));
		}
	}

	SECTION("Remove from size 1") {
		LinkedList<string> list;
		list.add("55");

		string data = list.removeIndex(0);

		REQUIRE(list.getSize() == 0);
		REQUIRE(data == "55");
	}

	SECTION("Remove from end of list size 3") {
		LinkedList<string> list;
		list.add("100");
		list.add("77");
		list.add("55");

		string data = list.removeIndex(1);

		REQUIRE(list.getSize() == 2);
		REQUIRE(data == "77");
		REQUIRE(list[0] == "100");
		REQUIRE(list[1] == "55");
	}

	SECTION("Remove from middle of size 3") {
		LinkedList<string> list;
		list.add("100");
		list.add("55");
		list.add("100");

		string data = list.removeIndex(1);

		REQUIRE(list.getSize() == 2);
		REQUIRE(data == "55");
		REQUIRE(list[0] == "100");
		REQUIRE(list[1] == "100");
	}

	SECTION("Remove from beginning of size 3") {
		LinkedList<string> list;
		list.add("100");
		list.add("55");
		list.add("100");

		string data = list.removeIndex(0);

		REQUIRE(list.getSize() == 2);
		REQUIRE(data == "100");
		REQUIRE(list[0] == "55");
		REQUIRE(list[1] == "100");
	}

	SECTION("Remove BigInteger") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("123123"));
		list.add(BigInteger("456456"));

		BigInteger data = list.removeIndex(0);

		REQUIRE(list.getSize() == 1);
		REQUIRE(data == BigInteger("123123"));
		REQUIRE(list[0] == BigInteger("456456"));
	}
}

// 15 - removeAll(data) return bool
TEST_CASE("Test removeAll(data)", "[remove][removeAll][removeAll(data]") {
	SECTION("Test remove from list size:0") {
		LinkedList<int> list;

		bool result = list.removeAll(100);

		REQUIRE(result == false);
	}

	SECTION("Remove all members of list") {
		LinkedList<string> list;
		list.add("100");
		list.add("100");
		list.add("100");
		list.add("100");
		list.add("100");
		list.add("100");

		bool result = list.removeAll("100");

		REQUIRE(result);
		REQUIRE(list.getSize() == 0);
	}

	SECTION("Remove everything from size 1") {
		LinkedList<string> list;
		list.add("100");

		bool result = list.removeAll("100");

		REQUIRE(result);
		REQUIRE(list.getSize() == 0);
	}

	SECTION("Remove from beginning of list") {
		LinkedList<string> list;
		list.add("100");
		list.add("55");

		bool result = list.removeAll("100");

		REQUIRE(result);
		REQUIRE(list.getSize() == 1);
		REQUIRE(list[0] == "55");
	}

	SECTION("Remove from end of list") {
		LinkedList<string> list;
		list.add("55");
		list.add("100");

		bool result = list.removeAll("100");

		REQUIRE(result);
		REQUIRE(list.getSize() == 1);
		REQUIRE(list[0] == "55");
	}

	SECTION("Remove multiple occurenced from middle of list") {
		LinkedList<string> list;
		list.add("55");
		list.add("100");
		list.add("100");
		list.add("55");

		bool result = list.removeAll("100");

		REQUIRE(result);
		REQUIRE(list.getSize() == 2);
		REQUIRE(list[0] == "55");
		REQUIRE(list[1] == "55");
	}

	SECTION("BigInteger remove multiple occurences") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));
		list.add(BigInteger("111111"));

		bool result = list.removeAll(BigInteger("111111"));

		REQUIRE(result);
		REQUIRE(list.getSize() == 3);
		REQUIRE(list[0] == BigInteger("222222"));
		REQUIRE(list[1] == BigInteger("222222"));
		REQUIRE(list[2] == BigInteger("222222"));
	}


}

// 16 - sort
TEST_CASE("Sorting", "[sort]") {
	SECTION("Empty List") {
		LinkedList<int> list;

		list.sort();

		REQUIRE(list.getSize() == 0);
	}

	SECTION("Sort") {
		LinkedList<string> list;
		list.add("zebra");
		list.add("colonial");
		list.add("aardvark");
		list.add("apple");

		list.sort();

		REQUIRE(list.getSize() == 4);

		REQUIRE(list[0] == "aardvark");
		REQUIRE(list[1] == "apple");
		REQUIRE(list[2] == "colonial");
		REQUIRE(list[3] == "zebra");
	}

	SECTION("Sort size 1") {
		LinkedList<int> list;
		list.add(55);

		list.sort();

		REQUIRE(list.getSize() == 1);

		REQUIRE(list[0] == 55);
	}

	SECTION("Sort BigInteger") {
		LinkedList<BigInteger> list;
		list.add(BigInteger("111111"));
		list.add(BigInteger("222222"));
		list.add(BigInteger("333333"));
		list.add(BigInteger("555555"));
		list.add(BigInteger("11"));
		list.add(BigInteger("222"));
		list.add(BigInteger("3333"));

		list.sort();

		REQUIRE(list.getSize() == 7);
		REQUIRE(list[0] == BigInteger("11"));
		REQUIRE(list[1] == BigInteger("222"));
		REQUIRE(list[2] == BigInteger("3333"));
		REQUIRE(list[3] == BigInteger("111111"));
		REQUIRE(list[4] == BigInteger("222222"));
		REQUIRE(list[5] == BigInteger("333333"));
		REQUIRE(list[6] == BigInteger("555555"));
	}
}

	// 17 - Iterator
	TEST_CASE("Iterator", "[iterator]") {
		SECTION("Empty List") {
			LinkedList<int> list;
			cout << "Foreach on empty list" << endl;
			for(int var : list)
			{
				cout << var << endl;
			}
			cout << endl;
		}

		SECTION("Size 3") {
			LinkedList<int> list;
			list.add(5);
			list.add(10);
			list.add(15);
			int sum = 0;
			for (int var : list)
			{
				sum = sum + var;
			}

			REQUIRE(sum == 30);
			REQUIRE(list.getSize() == 3);
		}

		SECTION("BigInteger iterator test") {
			LinkedList<BigInteger> list;
			list.add(BigInteger("111111"));
			list.add(BigInteger("222222"));
			list.add(BigInteger("333333"));
			BigInteger sum = BigInteger("0");
			for (BigInteger var : list)
			{
				sum = sum + var;
			}

			REQUIRE(sum == BigInteger("666666"));
			REQUIRE(list.getSize() == 3);
		}

}