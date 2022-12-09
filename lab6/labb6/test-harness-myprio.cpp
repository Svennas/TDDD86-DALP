/*************************************************
 * File: test-harness-myprio.cpp 
 *
 * File containing several test cases that can be
 * used to verify the correctness of the MyPriorityQueue
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
#include "MyPriorityQueue.h"
using namespace std;

/* These flags control which tests will be run.  Initially, only the
 * basic test will be executed.  As you complete more and more parts
 * of the implementation, you will want to turn more and more of these
 * flags on.
 */
#define BasicMyPriorityQueueTestEnabled          1 
#define ModerateMyPriorityQueueTestEnabled       1

#define BasicCopyTestEnabled            1
#define ModerateCopyTestEnabled         1


/* Utility function that pauses until the user hits ENTER. */
void pressEnterToContinue() {
  /* Use getline to stall until receiving input. */
  string line;
  getline(cin, line);
}

/* This function is what the test suite uses to ensure that the MyPriorityQueue works
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

struct comp{
  bool operator()(int l, int r) const{
    return l > r;
  }
};

/* Basic test: Can we build an empty priority queue? */
void basicMyPriorityQueueTest() try {
#if BasicMyPriorityQueueTestEnabled
  printBanner("Basic MyPriorityQueue Test");

  /* Construct the MyPriorityQueue. */
  MyPriorityQueue<int,comp> prio;
  checkCondition(true, "MyPriorityQueue construction completed.");

  /* Check basic properties of the MyPriorityQueue. */
  checkCondition(prio.size() == 0,      "New prio queue has no elements.");
  checkCondition(prio.empty(),          "prio queue is empty.");

  endTest();
#else
  testDisabled("BasicMyPriorityQueueTest");
#endif
} catch (const exception& e) {
  failTest(e);
}

/* A trickier test that involves a data set .
 */
void moderateMyPriorityQueueTest() try {
#if ModerateMyPriorityQueueTestEnabled
  printBanner("Moderate MyPriorityQueue Test");

  MyPriorityQueue<int,comp> prio;
  for (size_t i = 0; i < 8; ++i)
    prio.push(i);
  for (size_t i = 0; i < 8; ++i)
    prio.push(7-i);

  /* Check that basic properties hold. */
  checkCondition(prio.size() == 16, "New prio has the right number of elements.");
  checkCondition(!prio.empty(),     "prio queue is nonempty.");

  /* Make sure that the values of these points are correct. */
  for (size_t i = 0; i < 16; ++i){
    checkCondition(prio.size() == 16-i, "prio has the right number of elements.");
    int current = prio.top();
    checkCondition(current == i/2,      "top prio element is correct.");
    prio.pop();
  }

  checkCondition(prio.empty(),     "prio is empty.");
  
  
  endTest();
#else
  testDisabled("moderateMyPriorityQueueTest");
#endif
} catch (const exception& e) {
  failTest(e);
}



/* Tests basic behavior of the copy constructor and assignment operator. */
void basicCopyTest() try {
#if BasicCopyTestEnabled
  printBanner("Basic Copy Test");

  /* For simplicity, we'll use one-dimensional MyPriorityQueues in this step. */
  MyPriorityQueue<int, comp> one;
  for (size_t i = 0; i < 10; ++i)
    one.push(i); 
  for (size_t i = 0; i < 10; ++i)
    one.push(9 - i); 

  
  {
    /* Create a clone of one and confirm that everything copied correctly. 
     * This uses the copy constructor.
     */
    MyPriorityQueue<int,comp> clone = one;

    /* Basic checks. */
    checkCondition(one.size() == clone.size(),   "clone has the same number of elements as original one.");
    checkCondition(one.empty() == clone.empty(), "clone and one agree on emptiness.");

    /* Check that everything in one is there. */
    for (size_t i = 0; i < 20; ++i){
      checkCondition(clone.size() == 20-i, "clone has the right number of elements.");
      int current = clone.top();
      checkCondition(current == i/2,      "top clone element is correct.");
      clone.pop();
    }

    checkCondition(clone.empty(),     "clone is empty.");  

  }
  {
    /* Create a clone of one and confirm that everything copied correctly. 
     * This uses the assignment operator.
     */
    MyPriorityQueue<int,comp> clone;
    clone = one;    

    /* Check that everything in one is there. */
    for (size_t i = 0; i < 20; ++i){
      checkCondition(clone.size() == 20-i, "clone  has the right number of elements.");
      int current = clone.top();
      checkCondition(current == i/2,      "top clone element is correct.");
      clone.pop();
    }

    checkCondition(clone.empty(),     "clone is empty.");  

    
  }

  /* Check that everything in one is there. */
  for (size_t i = 0; i < 20; ++i){
    checkCondition(one.size() == 20-i, "After clone destructor, one has the right number of elements.");
    int current = one.top();
    checkCondition(current == i/2,     "After clone destructor, top one element is correct.");
    one.pop();
  }

  checkCondition(one.empty(),     "one is empty.");  

  
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

  MyPriorityQueue<int,comp> one;
  for (size_t i = 0; i < 10; ++i)
    one.push(i); 
  for (size_t i = 0; i < 10; ++i)
    one.push(9 - i);
  
  {
    /* Create a clone of one and confirm that everything copied correctly. 
     * This uses the copy constructor.
     */
    MyPriorityQueue<int,comp> clone = one;

    for (size_t i = 0; i < 10; ++i)
      clone.push(2*(10+i));

    /* Confirm that they didn't appear in one. */
    checkCondition(one.size() == 20, "Adding to clone does not change original one size.");
  }

  /* Check the integrity of the original out here as well to see that the destructor didn't hose things. */
  checkCondition(one.size() == 20, "After destructor, one has original size.");


  
   {
     /*Create a clone of one and confirm that everything copied correctly.
      * This uses the assignment operator.*/
     MyPriorityQueue<int,comp> clone;
     clone = one;

     /* Do awful, awful things to the copy.*/
     clone = clone = (clone = clone);
     (clone = one) = clone;
     clone = clone = clone = clone = clone;

     /*  Check that everything in one is there.*/
     for (size_t i = 0; i < 20; ++i){
       checkCondition(clone.size() == 20-i, "clone has the right number of elements.");
       int current = clone.top();
       checkCondition(current == i/2,      "top clone element is correct.");
       clone.pop();
     }

     checkCondition(clone.empty(),     "clone is empty.");

   }

/*   Check that everything in one is there.*/
   for (size_t i = 0; i < 20; ++i){
     checkCondition(one.size() == 20-i, "one has the right number of elements.");
     int current = one.top();
     checkCondition(current == i/2,     "top one element is correct.");
     one.pop();
   }

   checkCondition(one.empty(),     "one is empty.");


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
  basicMyPriorityQueueTest();
  moderateMyPriorityQueueTest();
  basicCopyTest();
  moderateCopyTest();

#if (BasicMyPriorityQueueTestEnabled && \
      ModerateMyPriorityQueueTestEnabled && \
      BasicCopyTestEnabled &&		   \
      ModerateCopyTestEnabled)
  cout << "All tests completed!  If they passed, you should be good to go!" << endl << endl;
#else
  cout << "Not all tests were run.  Enable the rest of the tests, then run again." << endl << endl;
#endif
  
  pressEnterToContinue();
}
