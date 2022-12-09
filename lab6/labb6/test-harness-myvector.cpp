/*************************************************
 * File: test-harness-myvector.cpp 
 *
 * File containing several test cases that can be
 * used to verify the correctness of the MyVector
 * implementation.  You should make sure to do your
 * own testing in addition to ensuring that the test
 * cases here pass.
 */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstdarg>
#include <set>
#include "MyVector.h"
using namespace std;

/* These flags control which tests will be run.  Initially, only the
 * basic test will be executed.  As you complete more and more parts
 * of the implementation, you will want to turn more and more of these
 * flags on.
 */
#define BasicMyVectorTestEnabled          1 
#define ModerateMyVectorTestEnabled       1
#define HarderMyVectorTestEnabled         1
#define MutatingMyVectorTestEnabled       1

#define ConstMyVectorTestEnabled          1
#define BasicCopyTestEnabled              1
#define ModerateCopyTestEnabled           1


/* Utility function that pauses until the user hits ENTER. */
void pressEnterToContinue() {
  /* Use getline to stall until receiving input. */
  string line;
  getline(cin, line);
}

/* This function is what the test suite uses to ensure that the MyVector works
 * correctly.  It takes as parameters an expression and description, along
 * with a file and line number, then checks whether the condition is true.
 * If so, it prints that the test passed.  Otherwise, it reports that the
 * test fails and points the caller to the proper file and line.
 */
void doCheckCondition(bool expr, const string& rationale, const string& file, int line) {
  /* It worked!  Congrats. */
  if (expr) {
    cout << "PASS: " << rationale << endl;
    return;
  }

  /* Uh oh!  The test failed! */
  cout << "FAIL: " << rationale << endl;
  cout << "  Error at " << file << ", line " << line << endl;
  cout << "  (ENTER to continue)" << endl;

  /* Pause so that the test fail stands out. */
  pressEnterToContinue();
}

/* Reports that an unexpected error occurred that caused a test to fail. */
void failTest(const exception& e) {
  cerr << "TEST FAILED: Unexpected exception: " << e.what() << endl;
  pressEnterToContinue();
}

/* This macro takes in an expression and a string, then invokes
 * doCheckCondition passing in the arguments along with the file
 * and line number on which the macro was called.  This makes it
 * easier to track down the source of bugs if a test case should
 * fail.
 */
#define checkCondition(expr, rationale) doCheckCondition(expr, rationale, __FILE__, __LINE__)

/* Utility function to delimit the start and end of test cases. */
void printBanner(const string& header) {
  cout << "\nBeginning test: " << header << endl;
  cout << setw(40) << setfill('-') << "" << setfill(' ') << endl;
}

/* Utility function to signal that a test isn't begin run. */
void testDisabled(const string& header) {
  cout << "== Test " << header << " NOT RUN: press ENTER to continue ==" << endl;

  /* Pause for the user to hit enter. */
  pressEnterToContinue();
}

/* Utility function to signal the end of a test. */
void endTest() {
  cout << "== end of test: press ENTER to continue ==" << endl;
  pressEnterToContinue();
}

/* Basic test: Can we build an empty vector and clear it? */
void basicMyVectorTest() try {
#if BasicMyVectorTestEnabled
  printBanner("Basic MyVector Test");

  /* Construct the MyVector. */
  MyVector<int> vect;
  checkCondition(true, "New MyVector construction completed.");

  /* Check basic properties of the MyVector. */
  checkCondition(vect.size() == 0,      "vector has no elements.");
  checkCondition(vect.empty(),          "vector is empty.");

  /* Clear the MyVctor and check basic properties again. */
  vect.clear();
  checkCondition(vect.size() == 0,      "vector has no elements.");
  checkCondition(vect.empty(),          "vector is empty.");

  endTest();
#else
  testDisabled("BasicMyVectorTest");
#endif
} catch (const exception& e) {
  failTest(e);
}

/* A trickier test that involves a data set and iterating through the vector with pointers.
 */
void moderateMyVectorTest() try {
#if ModerateMyVectorTestEnabled
  printBanner("Moderate MyVector Test");

  /* Build a palindrome. */
  MyVector<int> vect;
  for (size_t i = 0; i < 8; ++i)
    vect.push_back(i);
  for (size_t i = 0; i < 8; ++i)
    vect.push_back(7-i);

  /* Check that basic properties hold. */
  checkCondition(vect.size() == 16, "New vector has the right number of elements.");
  checkCondition(!vect.empty(),     "vector is nonempty.");

  /* Make sure that the values of these points are correct. */
  int* fwd = vect.begin();
  int* bwd = vect.end(); 
  while(fwd != bwd){
    --bwd;
    checkCondition(*fwd == *bwd, "vector has correct values.");
    ++fwd;
  }

  for (size_t i = 0; i < 8; ++i)
    vect.pop_back();

  /* Check basic properties again. */
  checkCondition(vect.size() == 8,      "vector has 8 elements.");
  checkCondition(!vect.empty(),         "vector is nonempty.");


  for (size_t i = 0; i < 8; ++i)
    vect.pop_back();

  /* Check basic properties again. */
  checkCondition(vect.size() == 0,      "vector has no elements.");
  checkCondition(vect.empty(),          "vector is empty.");
  
  endTest();
#else
  testDisabled("moderateMyVectorTest");
#endif
} catch (const exception& e) {
  failTest(e);
}

/* This test still uses just the basic functionality, but uses larger 
 * data set and index based access
 */
void harderMyVectorTest() try {
#if HarderMyVectorTestEnabled
  printBanner("Harder MyVector Test");

  MyVector<int> vect;
  for (size_t i = 0; i < 4096; ++i)
    vect.push_back(i);

  /* Check that basic properties hold. */
  checkCondition(vect.size() == 4096, "New vector has 4096 elements.");
  checkCondition(!vect.empty(),       "vector is nonempty.");

  for (size_t i = 0; i < 2048; ++i)
    vect.pop_back();

  /* Check basic properties again. */
  checkCondition(vect.size() == 2048, "vector has now 2048 elements.");
  checkCondition(!vect.empty(),       "vector is nonempty.");


  for (size_t i = 0; i < 2048; ++i)
    vect.push_back(-i);
  
  /* Check that basic properties hold. */
  checkCondition(vect.size() == 4096, "vector has now 4096 elements.");
  checkCondition(!vect.empty(),       "vector is nonempty.");

  /* Clear the MyVctor and check basic properties again. */
  vect.clear();
  checkCondition(vect.size() == 0,    "vector has no elements.");
  checkCondition(vect.empty(),        "vector is empty.");

  for (size_t i = 0; i < 4096; ++i)
    vect.push_back(i);

  /* Check that basic properties hold. */
  checkCondition(vect.size() == 4096, "vector has again 4096 elements.");
  checkCondition(!vect.empty(),       "vector is nonempty.");

  
  endTest();
#else
  testDisabled("HarderMyVectorTest");
#endif
} catch (const exception& e) {
  failTest(e);
}


/* This test actively mutates the elements of the MyVector using
 * operator[].  If you are failing this test, check to make sure
 * that your implementation of operator[] correctly allows for
 * mutation.
 */
void mutatingMyVectorTest() try {
#if MutatingMyVectorTestEnabled
  printBanner("Mutating MyVector Test");

  MyVector<int> vect;
  for (size_t i = 0; i < 16; ++i)
    vect.push_back(i);

  /* Check that basic properties hold. */
  checkCondition(vect.size() == 16, "New vector has 16 elements.");
  checkCondition(!vect.empty(),     "vector is nonempty.");

  for (size_t i = 0; i < 16; ++i)
    vect[i] = vect[i] + 1; 

  for (size_t i = 0; i < 16; ++i)
    checkCondition(vect[i] == i + 1, "updated vector has correct values.");

  endTest();
#else
  testDisabled("mutatingMyVectorTest");
#endif
} catch (const exception& e) {
  failTest(e);
}


/* A basic test that creates a const MyVector and a non-const MyVector to ensure
 * the class still compiles properly. It also tests the const version of
 * [] is working correctly on the basic MyVector tests.
 */
void constMyVectorTest() try {
#if ConstMyVectorTestEnabled
  printBanner("Const MyVector Test");

  MyVector<int> vect;
  for (size_t i = 0; i < 4; ++i)
    vect.push_back(i); 
  
  /* Check that the code compiles for the non-const version. */
  vect.size();
  vect.empty();
  vect[3]=10; 

  const MyVector<int>& const_vect = vect;
  
  /* Check that the code compiles for the const version. */
  const_vect.size();
  const_vect.empty();
  const_vect[3]; 
  
  checkCondition(true, "Const code compiles.");
  
  /* Run the basic vect tests using a const vect. */
  checkCondition(const_vect[0]==0, "const_vect has element zero.");
  checkCondition(const_vect[1]==1, "const_vect has element one.");
  checkCondition(const_vect[2]==2, "const_vect has element two.");
  checkCondition(const_vect[3]==10, "const_vect has element ten.");

  endTest();
#else
  testDisabled("ConstMyVectorTest");
#endif
} catch (const exception& e) {
  cout << "Note: vect lookup failed, but const code compiles." << endl;
  failTest(e);
}


/* Tests basic behavior of the copy constructor and assignment operator. */
void basicCopyTest() try {
#if BasicCopyTestEnabled
  printBanner("Basic Copy Test");

  MyVector<int> one;
  for (size_t i = 0; i < 10; ++i)
    one.push_back(2*i); 

  {
    /* Create a clone of one and confirm that everything copied correctly. 
     * This uses the copy constructor.
     */
    MyVector<int> clone = one;

    /* Basic checks. */
    checkCondition(one.size() == clone.size(),   "clone has the same number of elements as one.");
    checkCondition(one.empty() == clone.empty(), "clone and one agree on emptiness.");

    /* Check that everything in one is there. */
    for (size_t i = 0; i < 10; ++i)
      checkCondition(clone[i]==2*i, "Element from one present in clone.");

  }
  {
    /* Create a clone of one and confirm that everything copied correctly. 
     * This uses the assignment operator.
     */
    MyVector<int> clone;
    clone = one;    

    /* Basic checks. */
    checkCondition(one.size() == clone.size(),           "clone has the same number of elements as the one.");
    checkCondition(one.empty() == clone.empty(),         "clone and one agree on emptiness.");

    /* Check that everything in one is there. */
    for (size_t i = 0; i < 10; ++i)
      checkCondition(clone[i]==2*i, "Element from one present in clone.");
  }

  endTest();
#else
  testDisabled("BasicCopyTest");
#endif
} catch (const exception& e) {
  failTest(e);
}

/* A more merciless test of copy behavior.. */
void moderateCopyTest() try {
#if BasicCopyTestEnabled
  printBanner("Moderate Copy Test");

  MyVector<int> one;
  for (size_t i = 0; i < 10; ++i)
    one.push_back(2*i); 

  {
    /* Create a clone of one and confirm that everything copied correctly. 
     * This uses the copy constructor.
     */
    MyVector<int> clone = one;

    /* Add odd numbers to the clone. */
    for (size_t i = 0; i < 10; ++i)
      clone.push_back(2*(10+i));

    checkCondition(one.size() == 10, "Adding to clone did not change one size.");
  }

  /* Check the integrity of the original out here as well to see that the destructor didn't hose things. */
  checkCondition(one.size() == 10, "After clone destructor, one has original size.");
  for (size_t i = 0; i < 10; ++i) {
    checkCondition(one[i]==2*i, "After clone destructor, one contains same as original.");
  }

  {
    /* Create a clone of one and confirm that everything copied correctly. 
     * This uses the assignment operator.
     */
    MyVector<int> clone;
    clone = one;

    /* Do awful, awful things to the copy. */
    clone = clone = (clone = clone);
    (clone = one) = clone;
    clone = clone = clone = clone = clone;
  }

  endTest();
#else
  testDisabled("ModerateCopyTest");
#endif
} catch (const exception& e) {
  failTest(e);
}

/* Main entry point simply runs all the tests.  Note that these functions might be no-ops
 * if they are disabled by the configuration settings at the top of the program.
 */
int main() {
  basicMyVectorTest();
  moderateMyVectorTest();
  harderMyVectorTest();
  mutatingMyVectorTest();
  constMyVectorTest();
  
  basicCopyTest();
  moderateCopyTest();

#if (BasicMyVectorTestEnabled && \
     ModerateMyVectorTestEnabled && \
     HarderMyVectorTestEnabled &&   \
     MutatingMyVectorTestEnabled && \
     ConstMyVectorTestEnabled && \
     BasicCopyTestEnabled && \
     ModerateCopyTestEnabled)
  cout << "All tests completed!  If they passed, you should be good to go!" << endl << endl;
#else
  cout << "Not all tests were run.  Enable the rest of the tests, then run again." << endl << endl;
#endif
  
  pressEnterToContinue();
}
