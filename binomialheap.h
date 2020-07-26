#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#include <iostream>
#include <vector>

//Indicando que já teve um filho removido
enum Marked
{
    YES, NO
};

/*!
 * \brief The BinomialHeapNode struct
 */
struct BinomialHeapNode
{
    /*!
     * \brief BinomialHeapNode
     * \param data
     */
    BinomialHeapNode(int data)
    {
        this->data = data;
        next = nullptr;
        previous = nullptr;
    }

    int data = 0;
    int grau = 0; //quantidade de filhos
    Marked marked = NO;
    struct BinomialHeapNode* next = nullptr;
    struct BinomialHeapNode* previous = nullptr;

    struct BinomialHeapNode* father = nullptr;
    struct BinomialHeapNode* children = nullptr; //aponta para apenas um filho
};

/*!
 * \brief The BinomialHeap class
 */
class BinomialHeap
{
public:
    /*!
     * \brief BinomialHeap
     */
    BinomialHeap();
    /*!
     * \brief insertBeforeStart
     * \param data
     */
    void insertBeforeStart(int data);

    /*!
     * \brief deleteMinInterface
     * \return
     */
    BinomialHeapNode *deleteMinInterface();

    /*!
     * \brief getElementsAsVector
     * \return
     */
    std::vector<std::string> getElementsAsVector();

    /*!
     * \brief getDrawModeOne
     * \return
     */
    const std::string getDrawModeOne();
    /*!
     * \brief getDrawModeTwo
     * \return
     */
    const std::string getDrawModeTwo();

    /*!
     * \brief insertBeforeStart
     * \param tmp
     */
    void insertBeforeStart(BinomialHeapNode *tmp);

    /*!
     * \brief search
     * \param data
     * \return
     */
    BinomialHeapNode* search(int data);
    /*!
     * \brief searchStartingOfNode
     * \param data
     * \param initial
     * \return
     */
    BinomialHeapNode *searchStartingOfNode(int data, BinomialHeapNode *initial);
    /*!
     * \brief decrementKey
     * \param dataKey
     * \param decrement
     * \return
     */
    bool decrementKey(int dataKey, int decrement);

    /*!
     * \brief getDrawStartingOfNodeByModeTwo
     * \param initial
     * \param NodeDeclaration
     * \param linksDeclaration
     */
    void getDrawStartingOfNodeByModeTwo
    (
        BinomialHeapNode *initial,
        std::string &NodeDeclaration,
        std::string &linksDeclaration
    );
    /*!
     * \brief getCodeOfNode
     * \param node
     * \param NodeDeclaration
     */
    void getCodeOfNode(BinomialHeapNode *node, std::string& NodeDeclaration);

    ~BinomialHeap();

    /*!
     * \brief dealockList
     * \param initial
     * \param currentNode
     */
    void dealockList(BinomialHeapNode *initial, BinomialHeapNode *currentNode);

    /*!
     * \brief getStartNode
     * \return
     */
    BinomialHeapNode *getStartNode();

    /*!
     * \brief getMinNode
     * \return
     */
    BinomialHeapNode *getMinNode();
private:
    int countOfRoots = 0;
    int countOfNodes = 0;
    struct BinomialHeapNode* start = nullptr;
    BinomialHeapNode *nodeWithMinimumValue = nullptr;

    /*!
     * \brief getDrawStartingOfNodeByModeOne
     * \param node
     * \param textToFile
     */
    void getDrawStartingOfNodeByModeOne
    (
        BinomialHeapNode *node,
        std::string& textToFile
    );

    /*!
     * \brief mergeSubTrees
     * \param rootOne
     * \param rootTwo
     * \return
     */
    BinomialHeapNode *mergeSubTrees
    (
        BinomialHeapNode *rootOne,
        BinomialHeapNode *rootTwo
    );

    /*!
     * \brief removeBeforeStart
     * \return
     */
    BinomialHeapNode *removeBeforeStart();
    /*!
     * \brief consolidateFunction
     */
    void consolidateFunction();
    /*!
     * \brief increaseMarkAndCheckCondition
     * \param node
     */
    void increaseMarkAndCheckCondition(BinomialHeapNode *node);
    /*!
     * \brief changeNodePosition
     * \param node
     */
    void changeNodePosition(BinomialHeapNode *node);
    /*!
     * \brief deleteMin
     * \return
     */
    BinomialHeapNode *deleteMin();
};

#endif // BINOMIAL_HEAP_H
