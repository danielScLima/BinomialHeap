// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "binomialheap.h"

TEST_CASE( "Testing the insert calls in the heap", "[single-file]" )
{
    SECTION( "Inserting" )
	{
		BinomialHeapDS f;
		f.insertBeforeStart(50);
		
		BinomialHeapNode *startNode = f.getStartNode();
		BinomialHeapNode *minNode = f.getMinNode();
		REQUIRE (startNode->data == 50);
		REQUIRE (minNode->data == 50);
		REQUIRE (startNode->next->data == 50);
		
		f.insertBeforeStart(100);
		
		startNode = f.getStartNode();
		minNode = f.getMinNode();
		REQUIRE (minNode->data == 50);
		
		REQUIRE (startNode->data == 50);
		REQUIRE (startNode->next->data == 50);
		REQUIRE (startNode->children->data == 100);
		REQUIRE (startNode->children->next->data == 100);
		
		f.insertBeforeStart(75);
		
		startNode = f.getStartNode();
		minNode = f.getMinNode();
		REQUIRE (minNode->data == 50);
		
		REQUIRE (startNode->data == 75);
		REQUIRE (startNode->next->data == 50);
		REQUIRE (startNode->next->next->data == 75);
		REQUIRE (startNode->next->children->data == 100);
		REQUIRE (startNode->next->children->next->data == 100);
		
		f.insertBeforeStart(200);
		
		startNode = f.getStartNode();
		minNode = f.getMinNode();
		REQUIRE (startNode->data == 50);
		REQUIRE (minNode->data == 50);
		
		REQUIRE (startNode->data == 50);
		REQUIRE (startNode->next->data == 50);
		REQUIRE (startNode->children->data == 100);
		REQUIRE (startNode->children->next->data == 75);
		REQUIRE (startNode->children->next->next->data == 100);
		REQUIRE (startNode->children->next->children->data == 200);
		REQUIRE (startNode->children->next->children->next->data == 200);
    }
	
}

TEST_CASE( "Testing the remove calls in the heap", "[single-file]" )
{	
	SECTION( "Removing the min" )
	{
		BinomialHeapDS f;
		f.insertBeforeStart(50);	
		f.insertBeforeStart(100);
		f.insertBeforeStart(75);
		f.insertBeforeStart(200);
		
		BinomialHeapNode *startNode = nullptr;
		BinomialHeapNode *minNode = nullptr;
		
		startNode = f.getStartNode();
		minNode = f.getMinNode();
		REQUIRE (startNode->data == 50);
		REQUIRE (minNode->data == 50);
		
		REQUIRE (startNode->data == 50);
		REQUIRE (startNode->next->data == 50);
		REQUIRE (startNode->children->data == 100);
		REQUIRE (startNode->children->next->data == 75);
		REQUIRE (startNode->children->next->next->data == 100);
		REQUIRE (startNode->children->next->children->data == 200);
		REQUIRE (startNode->children->next->children->next->data == 200);
		
		BinomialHeapNode * min = f.deleteMinInterface(); //50
		REQUIRE (min->data == 50);
		delete min;
		
		startNode = f.getStartNode();
		minNode = f.getMinNode();
		REQUIRE (startNode->data == 100);
		REQUIRE (minNode->data == 75);
		
		REQUIRE (startNode->data == 100);
		REQUIRE (startNode->next->data == 75);
		REQUIRE (startNode->next->next->data == 100);
		REQUIRE (startNode->next->children->data == 200);
		REQUIRE (startNode->next->children->next->data == 200);
		
		min = f.deleteMinInterface(); //75
		REQUIRE (min->data == 75);
		delete min;
		
		startNode = f.getStartNode();
		minNode = f.getMinNode();
		REQUIRE (startNode->data == 100);
		REQUIRE (minNode->data == 100);
		
		REQUIRE (startNode->data == 100);
		REQUIRE (startNode->next->data == 100);
		REQUIRE (startNode->children->data == 200);
		REQUIRE (startNode->children->next->data == 200);
		
		min = f.deleteMinInterface(); //100
		REQUIRE (min->data == 100);
		delete min;
		
		startNode = f.getStartNode();
		minNode = f.getMinNode();
		REQUIRE (startNode->data == 200);
		REQUIRE (minNode->data == 200);
		
		REQUIRE (startNode->data == 200);
		REQUIRE (startNode->next->data == 200);
		REQUIRE (startNode->children == nullptr);
		
		min = f.deleteMinInterface(); //200
		REQUIRE (min->data == 200);
		delete min;
		
		startNode = f.getStartNode();
		minNode = f.getMinNode();
		REQUIRE (startNode == nullptr);
		REQUIRE (minNode == nullptr);
    }
}

TEST_CASE( "Testing the decrease calls in the heap", "[single-file]" )
{	
	SECTION( "Testing the decrease, case one" )
	{	
		BinomialHeapDS f;
		f.insertBeforeStart(50);	
		f.insertBeforeStart(100);
		f.insertBeforeStart(75);
		f.insertBeforeStart(200);
		
		BinomialHeapNode *startNode = nullptr;
		BinomialHeapNode *minNode = nullptr;
		
		startNode = f.getStartNode();
		minNode = f.getMinNode();
		REQUIRE (startNode->data == 50);
		REQUIRE (minNode->data == 50);
		
		REQUIRE (startNode->data == 50);
		REQUIRE (startNode->next->data == 50);
		REQUIRE (startNode->children->data == 100);
		REQUIRE (startNode->children->next->data == 75);
		REQUIRE (startNode->children->next->next->data == 100);
		REQUIRE (startNode->children->next->children->data == 200);
		REQUIRE (startNode->children->next->children->next->data == 200);
		
		bool ret = f.decrementKey(200, 2);
		REQUIRE (ret);
		
		startNode = f.getStartNode();
		minNode = f.getMinNode();
		REQUIRE (startNode->data == 50);
		REQUIRE (minNode->data == 50);
		
		REQUIRE (startNode->data == 50);
		REQUIRE (startNode->next->data == 50);
		REQUIRE (startNode->children->data == 100);
		REQUIRE (startNode->children->next->data == 75);
		REQUIRE (startNode->children->next->next->data == 100);
		REQUIRE (startNode->children->next->children->data == 198);
		REQUIRE (startNode->children->next->children->next->data == 198);
	}
	
	SECTION( "Testing the decrease, case two" )
	{
		BinomialHeapDS f;
		f.insertBeforeStart(50);	
		f.insertBeforeStart(100);
		f.insertBeforeStart(75);
		f.insertBeforeStart(200);
		
		BinomialHeapNode *startNode = nullptr;
		BinomialHeapNode *minNode = nullptr;
		
		startNode = f.getStartNode();
		minNode = f.getMinNode();
		REQUIRE (startNode->data == 50);
		REQUIRE (minNode->data == 50);
		
		REQUIRE (startNode->data == 50);
		REQUIRE (startNode->next->data == 50);
		REQUIRE (startNode->children->data == 100);
		REQUIRE (startNode->children->next->data == 75);
		REQUIRE (startNode->children->next->next->data == 100);
		REQUIRE (startNode->children->next->children->data == 200);
		REQUIRE (startNode->children->next->children->next->data == 200);
		
		bool ret = f.decrementKey(200, 2);
		REQUIRE (ret);
		
		startNode = f.getStartNode();
		minNode = f.getMinNode();
		REQUIRE (startNode->data == 50);
		REQUIRE (minNode->data == 50);
		
		REQUIRE (startNode->data == 50);
		REQUIRE (startNode->next->data == 50);
		REQUIRE (startNode->children->data == 100);
		REQUIRE (startNode->children->next->data == 75);
		REQUIRE (startNode->children->next->next->data == 100);
		REQUIRE (startNode->children->next->children->data == 198);
		REQUIRE (startNode->children->next->children->next->data == 198);
		
		ret = f.decrementKey(198, 197);
		REQUIRE (ret);
		
		startNode = f.getStartNode();
		minNode = f.getMinNode();
		REQUIRE (startNode->data == 50);
		REQUIRE (minNode->data == 1);
		
		REQUIRE (startNode->data == 50);
		REQUIRE (startNode->next->data == 1);
		REQUIRE (startNode->next->next->data == 50);
		REQUIRE (startNode->children->data == 100);
		REQUIRE (startNode->children->next->data == 75);
		REQUIRE (startNode->children->next->next->data == 100);
		REQUIRE (startNode->children->next->children == nullptr);
	}
	
}

TEST_CASE( "Testing the search calls in the heap", "[single-file]" )
{	
	SECTION( "search calls" )
	{	
		BinomialHeapDS f;
		f.insertBeforeStart(50);	
		f.insertBeforeStart(100);
		f.insertBeforeStart(75);
		f.insertBeforeStart(200);
		
		REQUIRE (f.search(50) != nullptr);
		REQUIRE (f.search(100) != nullptr);
		REQUIRE (f.search(75) != nullptr);
		REQUIRE (f.search(200) != nullptr);
		
		REQUIRE (f.search(10) == nullptr);
	}
}



