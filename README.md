BinomialHeap
====================

This repository has a project with the implementation of a BinomialHeap.

It is written in C++.

The code of the BinomialHeap is independent of platform.

Is has two possible main files:

* [Codes](#markdown-header)
	* [A main that triggers unit test;](#markdown-header-emphasis)

	* [A Qt project to manage the stack (With Gui).](#markdown-header-strikethrough)
	
The library used to make the Unit Test is the Catch v2.12.3. The code is already in this repository.

The Qt project generates images of the BinomialHeap, using the lib Graphviz.
Install this lib in your computer for you to be able to create such images.

The code was written containing the Doxygen documentation.

- - -

You have several options to build the project: 
====================

* [Build tools](#markdown-header)
	* [Makefile (using the file named MakefileGeneral);](#markdown-header-emphasis)
	* [CMake.](#markdown-header-emphasis)
	* [Qt Project (With QMake).](#markdown-header-emphasis)

The project has no leaks (Fully tested with Valgrind).

All the unit tests are ok.

- - -

The functionalities available are: 
====================

* [Functionalities](#markdown-header)
	* [Insert;](#markdown-header-emphasis)
	* [Search;](#markdown-header-emphasis)	
	* [Remove the minimum number;](#markdown-header-emphasis)
	* [Decrease a number with some decrement value;](#markdown-header-emphasis)
	
	
- - -	
Heap sample 1: 
====================
A sample of the heap is shown below (type of view 1):

![Alt text](images/sample0.png)	


- - -	
Heap sample 2: 
====================
A sample of the heap is shown below (type of view 2):

![Alt text](images/sample1.png)	
	
- - -

Insertion demo steps (simple view): 
====================

## Initial

![Alt text](images/inserting/0a.png)

## Inserting 50

![Alt text](images/inserting/1a.png)

## Inserting 100

![Alt text](images/inserting/2a.png)

## Inserting 75

![Alt text](images/inserting/3a.png)

## Inserting 200

![Alt text](images/inserting/4a.png)


- - -

Insertion demo steps (improved view): 
====================

## Initial

![Alt text](images/inserting/0b.png)

## Inserting 50

![Alt text](images/inserting/1b.png)

## Inserting 100

![Alt text](images/inserting/2b.png)

## Inserting 75

![Alt text](images/inserting/3b.png)

## Inserting 200

![Alt text](images/inserting/4b.png)


- - -

Remove min steps (simple view): 
====================

## Initial 

![Alt text](images/removing/0a.png)

## Removing

![Alt text](images/removing/1a.png)

## Removing

![Alt text](images/removing/2a.png)

## Removing

![Alt text](images/removing/3a.png)

## Removing

![Alt text](images/removing/4a.png)


- - -

Remove min steps (improved view): 
====================

## Initial 

![Alt text](images/removing/0b.png)

## Removing

![Alt text](images/removing/1b.png)

## Removing

![Alt text](images/removing/2b.png)

## Removing

![Alt text](images/removing/3b.png)

## Removing

![Alt text](images/removing/4b.png)

- - -

Decrement steps (case 1): 
====================

## Initial 

![Alt text](images/decrementing/0a.png)

## Decrementing the entry 200 by 2

![Alt text](images/decrementing/0b.png)

- - -

Decrement steps (case 2): 
====================

## Initial 

![Alt text](images/decrementing/0b.png)

## Decrementing the entry 198 by 197

![Alt text](images/decrementing/0c.png)


Qt gui project: 
====================
The qt gui application gui is shown below:

![Alt text](images/guisample.png)