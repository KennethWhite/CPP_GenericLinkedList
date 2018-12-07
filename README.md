# CPP_GenericLinkedList
A C++ Linked List template class and corresponding unit tests
Kenneth White
CSCD 305 8:00 Spring 18
Assignment 100 - Putting it all together

### NOTE:
	As part of the unit tests I intentionally give methods invalid indices, which are caught and thrown from the method.
	These exceptions can register as memory leaks for the test cases in which they are used as VS maintains a pointer to the Exception. 
	I have these test cases disabled using a global	bool. To enable them change the bool g_test_assertions to true and rerun.

	All of the requirements listed on canvas are labelled in comments in unit tester source file
	Every test used both primitives and BigIntegers.

### Shortcomings :
	None that I know of, barring the memory issue with exception testing noted above.

### Compilation details :
	Compile using g++ *.cpp

	I used Microsoft Visual C++ compiler via Visual Studio 2017
	I also used g++ version 7.2.0 via MinGW

### Run details:
	run with 'cmd /k a.exe' to keep window open after tests complete.
	run additionally with -s or --success to display all passed assertions


### Results including memory checking:

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
