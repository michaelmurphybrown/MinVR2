#include "config/VRDataIndex.h"
#include "config/VRDataQueue.h"

int TestQueueArray();
int TestQueueUnpack();

int queuetest(int argc, char* argv[]) {
  
  int defaultchoice = 1;
  
  int choice = defaultchoice;

  if (argc > 1) {
    if(sscanf(argv[1], "%d", &choice) != 1) {
      printf("Couldn't parse that input as a number\n");
      return -1;
    }
  }

  int output;
  
  switch(choice) {
  case 1:
    output = TestQueueArray();
    break;
    
  case 2:
    output = TestQueueUnpack();
    break;

    // Add case statements to handle other values.
  default:
    std::cout << "Test #" << choice << " does not exist!\n";
    output = -1;
  }
  
  return output;
}

// This is pretty much the same function as setupIndex() in
// indextest.cpp, but has its name changed to avoid link conflicts in
// the construction of test_runner.
VRDataIndex* setupQIndex() {

  VRDataIndex *n = new VRDataIndex;
  
  VRInt a = 4;
  VRDouble b = 3.1415926;
  
  n->addData("/george/a0", a);
  n->addData("/george/a1", a + 1);
  n->addData("/george/a2", a + 2);
  n->addData("/george/a3", a + 3);
  n->addData("/george/a4", a + 4);
  n->addData("/george/a5", a + 5);
  n->addData("/george/a6", a + 6);
  n->addData("/george/a7", a + 7);
  n->addData("/george/a8", a + 8);
  n->addData("/george/a9", a + 9);

  n->addData("/martha/b0", b);
  n->addData("/martha/b1", b * 1);
  n->addData("/martha/b2", b * 2);
  n->addData("/martha/b3", b * 3);
  n->addData("/martha/b4", b * 4);
  n->addData("/martha/b5", b * 5);
  n->addData("/martha/b6", b * 6);
  n->addData("/martha/b7", b * 7);
  n->addData("/martha/b8", b * 8);
  n->addData("/martha/b9", b * 9);

  VRString c = "abigail";
  n->addData("/john/c0", c + "0");
  n->addData("/john/c1", c + "1");
  n->addData("/john/c2", c + "2");
  n->addData("/john/c3", c + "3");
  n->addData("/john/c4", c + "4");
  n->addData("/john/c5", c + "5");
  n->addData("/john/c6", c + "6");
  n->addData("/john/c7", c + "7");
  n->addData("/john/c8", c + "8");
  n->addData("/john/c9", c + "9");

  std::vector<double>d;
  d.push_back(1.2);
  d.push_back(2.3);
  d.push_back(3.4);
  d.push_back(4.5);
  d.push_back(5.6);

  n->addData("/donna/d0", d);
  
  // This file is specified using the WORKING_DIRECTORY option in the
  // ctest framework.  See the CMakeLists.txt file in this directory,
  // and look for the add_test command.
  n->processXMLFile("test.xml", "/");
  
  return n;
}

// Removes the timestamps from a queue string so they can be compared
// with each other.
std::string removeTimeStamps(const std::string inString) {

  std::string outString = inString;
  
  size_t start = 0, timeStampPos, endQuotePos;

  // Find the 'timeStamp' string.
  while ((timeStampPos = outString.find("timeStamp", start)) != std::string::npos) {

    // Find the closing quote of its value.
    if ((endQuotePos = outString.find("\"", timeStampPos + 12))
        != std::string::npos) {

      // Delete the timeStamp value between the quotes.
      outString.replace(timeStampPos + 11, endQuotePos - timeStampPos - 11, "");

      start = endQuotePos;

    } else break;
  }

  return outString;
}
    
  

int TestQueueArray() {

  std::string testString = "<VRDataQueue num=\"2\"><VRDataQueueItem timeStamp=\"1454671331220377\"><atestarray type=\"intarray\">0@1@2@3@4@5@6@7@8@9@10@11@12@13@14@15@16@17@18@19@20@21@22@23@24@25@26@27@28@29@30@31@32@33@34@35@36@37@38@39@40@41@42@43@44@45@46@47@48@49@50@51@52@53@54@55@56@57@58@59@60@61@62@63@64@65@66@67@68@69@70@71@72@73@74@75@76@77@78@79@80@81@82@83@84@85@86@87@88@89@90@91@92@93@94@95@96@97@98@99</atestarray></VRDataQueueItem><VRDataQueueItem timeStamp=\"1454671331220395\"><d0 type=\"doublearray\">1.200000@2.300000@3.400000@4.500000@5.600000</d0></VRDataQueueItem></VRDataQueue>";

  testString = removeTimeStamps(testString);
  
  VRDataIndex *n = setupQIndex();
  VRDataQueue *q = new VRDataQueue;
  
  std::vector<int>e;

  for (int i = 0; i < 100; i++) {
    e.push_back(i);
  }

  n->addData("/george/atestarray", e);

  q->push(n->serialize("atestarray", "/george/"));
  q->push(n->serialize("/donna/d0"));
  
  std::string output = removeTimeStamps(q->serialize());
  
  //std::cout << "test:" << testString << std::endl;
  //std::cout << "outp:" << output << std::endl;
  
  // Test that the new queue is the same as the test string.
  int out = output.compare(testString);
  delete n;
  delete q;
  
  return out;
}
  
int TestQueueUnpack() {

  std::string testString;

  // Create an index and a queue.
  VRDataIndex *n = setupQIndex();
  VRDataQueue *q = new VRDataQueue;
  
  std::vector<int>e;

  for (int i = 0; i < 100; i++) {
    e.push_back(i);
  }

  // Add an array to the index.
  n->addData("/george/atestarray", e);

  // Get the serialized version of an index object.
  testString = n->serialize("/george");

  // Put that object into the queue.
  q->push(n->serialize("/george"));
  
  VRDataIndex* index = new VRDataIndex;

  // Unpack the serialized object.
  index->addSerializedValue( q->getSerializedObject(), "/" );

  // Unpack it into a different index.
  std::string output = index->serialize("/george");

  // Does it match?
  int out = testString.compare(output);

  delete n;
  delete q;
  delete index;

  return out;
}

