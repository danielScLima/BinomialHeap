#include "binomialheap.h"

BinomialHeap::BinomialHeap()
{

}

BinomialHeap::~BinomialHeap()
{
    dealockList(start, start);
}

BinomialHeapNode *BinomialHeap::getStartNode()
{
    return this->start;
}

BinomialHeapNode *BinomialHeap::getMinNode()
{
    return this->nodeWithMinimumValue;
}

void BinomialHeap::dealockList(BinomialHeapNode* initial, BinomialHeapNode* currentNode)
{
    if (currentNode == nullptr)
        return;

    BinomialHeapNode* children = currentNode->children;
    if (children != nullptr)
    {
        dealockList(children, children);
    }

    BinomialHeapNode* next = currentNode->next;
    delete currentNode;
    if (next != initial)
    {
        dealockList(initial, next);
    }
}

void BinomialHeap::insertBeforeStart(struct BinomialHeapNode* tmp)
{
    if (this->nodeWithMinimumValue == nullptr)
        this->nodeWithMinimumValue = tmp;
    else if (this->nodeWithMinimumValue->data > tmp->data) //update min node
    {
        this->nodeWithMinimumValue = tmp;
    }

    if (start == nullptr)
    {
        start = tmp;
        start->next = start;
        start->previous = start;
    }
    else
    {
        BinomialHeapNode* previousStart = start->previous;
        tmp->next = start;
        tmp->previous = previousStart;

        start->previous = tmp;
        previousStart->next = tmp;
    }

    countOfRoots++;
}


bool BinomialHeap::decrementKey(int dataKey, int decrement)
{
    BinomialHeapNode *node = search(dataKey);
    if (node == nullptr)
        return false; //Este nó não existe

    node->data = node->data - decrement;

    if (node->father == nullptr) //Verificar se deve atualizar o min
    {
        if (nodeWithMinimumValue->data > node->data)
            nodeWithMinimumValue = node;
    }
    else
    {
        if (node->father->data > node->data)
        {
            changeNodePosition(node);
        }
    }

    return true;
}

void BinomialHeap::changeNodePosition(BinomialHeapNode* node)
{
    BinomialHeapNode* backupFather = node->father;
    if (node->next == node) //não tem irmãos
    {
        //Ele é apontado pelo pai
        if (node->father != nullptr)
        {
            node->father->children = nullptr;
            node->father->grau = node->father->grau-1;
        }

        node->father = nullptr;
        insertBeforeStart(node); //insere na lista principal
    }
    else //tem irmãos
    {
        BinomialHeapNode* previous = node->previous;
        BinomialHeapNode* next = node->next;
        previous->next = next;
        next->previous = previous;

        //checar se o pai aponta pra ele
        //se sim, alterar
        if (node->father != nullptr)
        {
            if (node->father->children == node)
                node->father->children = next;

            node->father->grau = node->father->grau-1;
        }

        node->previous = nullptr;
        node->next = nullptr;
        node->father = nullptr;

        insertBeforeStart(node); //insere na lista principal
    }

    node->marked = Marked::NO;

    if (backupFather != nullptr)
        increaseMarkAndCheckCondition(backupFather);
}

void BinomialHeap::increaseMarkAndCheckCondition(BinomialHeapNode* node)
{
    if (node->marked == Marked::NO)
        node->marked = Marked::YES;
    else //node->marked == Marked::YES
    {
        changeNodePosition(node);
    }
}

BinomialHeapNode *BinomialHeap::search(int data)
{
    if (start == nullptr)
        return nullptr;

    return BinomialHeap::searchStartingOfNode(data, start);
}

BinomialHeapNode *BinomialHeap::searchStartingOfNode
(
    int data,
    BinomialHeapNode *initial
)
{
    BinomialHeapNode *tmp = initial;
    if (tmp == nullptr)
        return nullptr;

    do
    {
        if (tmp->data == data)
            return tmp;

        //busca nos filhos de tmp
        if (tmp->children != nullptr && data > tmp->data)
        {
            auto ret = searchStartingOfNode
            (
                data,
                tmp->children
            );
            if (ret != nullptr)
                return ret;
        }

        tmp = tmp->next;

    } while(tmp != initial);

    return nullptr;
}

void BinomialHeap::insertBeforeStart(int data)
{
    struct BinomialHeapNode* tmp = new BinomialHeapNode(data);
    insertBeforeStart(tmp);
    this->countOfNodes++;

    //you must call the consolidate function
    consolidateFunction();
}

BinomialHeapNode *BinomialHeap::deleteMinInterface()
{
    BinomialHeapNode* min = deleteMin();
    if (min != nullptr)
        countOfNodes--;
    return min;
}

BinomialHeapNode *BinomialHeap::removeBeforeStart()
{
    if (start == nullptr)
        return nullptr;
    else
    {
        if (start->next == start)
        {
            BinomialHeapNode *tmp = start;

            tmp->next = tmp->previous = tmp;

            countOfRoots = 0;
            start = nullptr;
            return tmp;
        }
        else
        {
            BinomialHeapNode *tmp = start->previous;
            BinomialHeapNode *beforeTmp = tmp->previous;

            beforeTmp->next = start;
            start->previous = beforeTmp;

            countOfRoots--;

            tmp->next = tmp->previous = tmp;

            return tmp;
        }
    }
}

std::vector<std::string> BinomialHeap::getElementsAsVector()
{
    std::vector<std::string> vec;

    if (start != nullptr)
    {
        vec.push_back(std::to_string(start->data));

        if (start->next != nullptr)
        {
            BinomialHeapNode* tmp = start->next;
            while (tmp != start)
            {
                vec.push_back(std::to_string(tmp->data));
                tmp = tmp->next;
            }
        }
    }

    return vec;
}

void BinomialHeap::getCodeOfNode(BinomialHeapNode* node, std::string& nodeDeclaration)
{
    //nodeDeclaration += std::to_string(node->data)+";";

    nodeDeclaration += std::to_string(node->data)+"[label=<";
    nodeDeclaration += "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">";
    nodeDeclaration += "  <TR>";
    nodeDeclaration += "    <TD ROWSPAN=\"5\" PORT=\"left\">Left</TD>";
    nodeDeclaration += "    <TD COLSPAN=\"3\" PORT=\"parent\">Parent</TD>";
    nodeDeclaration += "    <TD ROWSPAN=\"5\" PORT=\"right\">Right</TD>";
    nodeDeclaration += "  </TR>";
    nodeDeclaration += "  <TR>";
    nodeDeclaration += "    <TD COLSPAN=\"3\">Key: "+std::to_string(node->data)+"</TD>";
    nodeDeclaration += "  </TR>";
    nodeDeclaration += "  <TR>";
    nodeDeclaration += "    <TD COLSPAN=\"3\">Grau: "+std::to_string(node->grau)+"</TD>";
    nodeDeclaration += "  </TR>";
    nodeDeclaration += "  <TR>";

    std::string msg = node->marked == YES? "true":"false";

    nodeDeclaration += "    <TD COLSPAN=\"3\">Marked: "+msg+"</TD>";
    nodeDeclaration += "  </TR>";
    nodeDeclaration += "  <TR>";
    nodeDeclaration += "    <TD COLSPAN=\"3\" PORT=\"child\">Child</TD>";
    nodeDeclaration += "  </TR>";
    nodeDeclaration += "</TABLE>";
    nodeDeclaration += ">];";
}

void BinomialHeap::getDrawStartingOfNodeByModeTwo
(
    BinomialHeapNode* initial,
    std::string& nodeDeclaration,
    std::string& linksDeclaration
)
{
    getCodeOfNode(initial, nodeDeclaration);

    if (initial->children != nullptr)
    {
        //O próprio pai já faz o link bidirecional
        linksDeclaration += std::to_string(initial->data) +":child ->" +
                std::to_string(initial->children->data)+":parent [dir=both color=red];";

        getDrawStartingOfNodeByModeTwo
        (
            initial->children,
            nodeDeclaration,
            linksDeclaration
        );
    }

    if (initial->father != nullptr && initial != initial->father->children)
    {
        //Deve fazer um link para o pai
        linksDeclaration += std::to_string(initial->data) +":parent ->" +
                std::to_string(initial->father->data)+" [color=red];";
    }

    if (initial->father != nullptr && initial == initial->father->children)
    {
        //Obter nomes de todos os nós até a direita
        nodeDeclaration += "{rank=same;";
        nodeDeclaration += " "+std::to_string(initial->data);
        BinomialHeapNode* tmp = initial->next;
        while (tmp != tmp->father->children)
        {
            nodeDeclaration += " "+std::to_string(tmp->data);
            tmp = tmp->next;
        }
        nodeDeclaration += "};";
    }

    if (initial->father == nullptr && initial == start)
    {
        //Obter nomes de todos os nós até a direita
        nodeDeclaration += "{rank=same;";
        nodeDeclaration += " "+std::to_string(initial->data);
        BinomialHeapNode* tmp = initial->next;
        while (tmp != start)
        {
            nodeDeclaration += " "+std::to_string(tmp->data);
            tmp = tmp->next;
        }
        nodeDeclaration += "};";
    }

    if (initial != initial->next)
    {
        linksDeclaration += std::to_string(initial->data) +":right:s -> " +
                std::to_string(initial->next->data)+":left:s [color=blue];";
    }
    else
    {
        linksDeclaration += std::to_string(initial->data) +":right -> " +
                std::to_string(initial->next->data)+":parent [color=blue];";
    }
    if (initial != initial->previous)
    {
        linksDeclaration += std::to_string(initial->data) +":left:n -> " +
                std::to_string(initial->previous->data)+":right:n [color=green];";
    }
    else
    {
        linksDeclaration += std::to_string(initial->data) +":left -> " +
                std::to_string(initial->previous->data)+":parent [color=green];";
    }

    if (initial->father == nullptr)
    {
        if (initial->next != start)
        {
            //Continua com o próximo
            getDrawStartingOfNodeByModeTwo
            (
                initial->next,
                nodeDeclaration,
                linksDeclaration
            );
        }
    }
    else //tem pai
    {
        if (initial->next != initial->father->children)
        {
            //Continua com o próximo
            getDrawStartingOfNodeByModeTwo
            (
                initial->next,
                nodeDeclaration,
                linksDeclaration
            );
        }
    }
}

void BinomialHeap::getDrawStartingOfNodeByModeOne
(
    BinomialHeapNode* initial,
    std::string& textToFile
)
{
    BinomialHeapNode* tmp = initial;
    std::string values;
    if (tmp != nullptr)
    {
        if (tmp->marked == YES)
        {
            textToFile += std::to_string(tmp->data)+
                    " [fillcolor=red style=filled fontcolor=white];";
        }

        textToFile += std::to_string(tmp->data) +"->"+
                std::to_string(tmp->next->data)+"[dir=both color=green minlen=2];";

        values = "{ rank=same;";
        values += " "+std::to_string(tmp->data)+";";

        //se tem pai, desenha link para pai
        if (tmp->father != nullptr)
        {
            textToFile += std::to_string(tmp->data) +"->"+
                    std::to_string(tmp->father->data)+"[color=red minlen=2];";
        }

        //Se tem filho, desenha link para filho e desenha tudo de filho
        if (tmp->children != nullptr)
        {
            if (tmp->children->marked == YES)
            {
                textToFile += std::to_string(tmp->children->data)+
                        " [fillcolor=red style=filled fontcolor=white];";
            }

            textToFile += std::to_string(tmp->data) +"->"+
                    std::to_string(tmp->children->data)+"[color=red minlen=2];";

            //desenhar tudo de filho
            getDrawStartingOfNodeByModeOne(tmp->children, textToFile);
        }

        tmp = tmp->next;
        while(tmp != initial)
        {
            if (tmp->marked == YES)
            {
                textToFile += std::to_string(tmp->data)+
                        " [fillcolor=red style=filled fontcolor=white];";
            }

            textToFile += std::to_string(tmp->data) +"->"+
                    std::to_string(tmp->next->data)+"[dir=both color=green minlen=2];";
            values += " "+std::to_string(tmp->data)+";";

            //se tem pai, desenha link para pai
            if (tmp->father != nullptr)
            {
                textToFile += std::to_string(tmp->data) +"->"+
                        std::to_string(tmp->father->data)+"[color=red minlen=2];";
            }

            //Se tem filho, desenha link para filho e desenha tudo de filho
            if (tmp->children != nullptr)
            {
                textToFile += std::to_string(tmp->data) +"->"+
                        std::to_string(tmp->children->data)+"[color=red minlen=2];";

                //desenhar tudo de filho
                getDrawStartingOfNodeByModeOne(tmp->children, textToFile);
            }

            tmp = tmp->next;
        }
        values += "};";

        textToFile += values;
    }
}

const std::string BinomialHeap::getDrawModeOne()
{
    std::string textToFile = "digraph g{";
    textToFile += "rankdir = TB;";

    if (start == nullptr || nodeWithMinimumValue == nullptr)
    {
        textToFile += "NULL [ fontcolor=red ];start -> NULL;minimum -> NULL;";
    }
    else
    {
        textToFile += "start -> "+std::to_string(start->data)+";";
        textToFile += "minimum -> "+std::to_string(nodeWithMinimumValue->data)+";";
    }
    textToFile += "{ rank=min; start;minimum;};";

    getDrawStartingOfNodeByModeOne(start, textToFile);
    textToFile += "}";

    return textToFile;
}

const std::string BinomialHeap::getDrawModeTwo()
{
    std::string textToFile = "digraph g{";
    textToFile += "node [shape=plaintext ];";

    std::string linkDeclaration;
    if (start != nullptr)
        getDrawStartingOfNodeByModeTwo(start, textToFile, linkDeclaration);

    linkDeclaration +="start [shape=box];";
    linkDeclaration +="minimum [shape=box];";


    if (start == nullptr || nodeWithMinimumValue == nullptr)
    {
        textToFile += "NULL [ fontcolor=red ];start -> NULL;minimum -> NULL;";
    }
    else
    {
        textToFile += "start -> "+std::to_string(start->data)+";";
        textToFile += "minimum -> "+std::to_string(nodeWithMinimumValue->data)+";";
    }
    textToFile += "{ rank=min; start; minimum;};";


    textToFile += linkDeclaration;
    textToFile += "}";

    return textToFile;
}

BinomialHeapNode* BinomialHeap::mergeSubTrees
(
      BinomialHeapNode* rootOne,
      BinomialHeapNode* rootTwo
)
{
    if (rootOne->data <= rootTwo->data)
    {
        //Inserir rootTwo como um filho de rootOne

        if (rootOne->children == nullptr)
        {
            rootOne->children = rootTwo;
            rootTwo->father = rootOne;
        }
        else
        {
            BinomialHeapNode* previousChildrenOfRootOne = rootOne->children->previous;
            previousChildrenOfRootOne->next = rootTwo;
            rootTwo->next = rootOne->children;
            rootOne->children->previous = rootTwo;
            rootTwo->previous = previousChildrenOfRootOne;
            rootTwo->father = rootOne;
        }

        rootOne->grau = rootOne->grau+1;

        return rootOne;
    }
    else //Inserir rootOne como um filho de rootTwo
    {
        if (rootTwo->children == nullptr)
        {
            rootTwo->children = rootOne;
            rootOne->father = rootTwo;
        }
        else
        {
            BinomialHeapNode* previousChildrenOfRootTwo = rootTwo->children->previous;
            previousChildrenOfRootTwo->next = rootOne;
            rootOne->next = rootTwo->children;
            rootTwo->children->previous = rootOne;
            rootOne->previous = previousChildrenOfRootTwo;
            rootOne->father = rootTwo;
        }

        rootTwo->grau = rootTwo->grau+1;

        return rootTwo;
    }
}

BinomialHeapNode* BinomialHeap::deleteMin()
{
    //Take the pointer to the minimum element in the tree
    //Remove this root and promote the childrens to root
    if (nodeWithMinimumValue == nullptr)
        return nullptr;
    else
    {
        //remove da lista que começa com start
        if (nodeWithMinimumValue->next == nodeWithMinimumValue) //é único
        {
            if (nodeWithMinimumValue->children != nullptr)
            {
                this->start = nodeWithMinimumValue->children;
                this->countOfRoots = 1;

                BinomialHeapNode* current = start;
                this->start->father = nullptr;
                while (current->next != start)
                {
                    current = current->next;
                    current->father = nullptr;
                    this->countOfRoots++;
                }

                this->start->marked = NO;
            }
            else
            {
                this->start = nullptr;
                this->countOfRoots = 0;
            }
        }
        else
        {
            BinomialHeapNode* previousMin = nodeWithMinimumValue->previous;
            BinomialHeapNode* nextMin = nodeWithMinimumValue->next;

            previousMin->next = nextMin;
            nextMin->previous = previousMin;

            if (start->data == nodeWithMinimumValue->data)
                start = nextMin;

            this->countOfRoots--;

            BinomialHeapNode* initialChild = nodeWithMinimumValue->children;
            BinomialHeapNode* child = initialChild;
            while (child != nullptr) //Quando acabar os elementos, ocorrerá um break
            {
                child->father = nullptr;
                child->marked = NO; //Por definição

                //deve remover do link dos seus irmãos
                if (child->next == child)
                {
                    child->next = child->previous = child;

                    //Deve inserir na lista principal
                    insertBeforeStart(child);

                    break; //filho unico
                }
                else
                {
                    BinomialHeapNode* previousChild = child->previous;
                    BinomialHeapNode* nextChild = child->next;

                    previousChild->next = nextChild;
                    nextChild->previous = previousChild;

                    //Deve inserir na lista principal
                    insertBeforeStart(child);

                    child = nextChild;
                }
            }
        }
    }

    BinomialHeapNode *nodeWithMinimumValueBackup = nodeWithMinimumValue;

    //call the consolidate structure function with merge functions
    consolidateFunction();

    //The Update the minimum node was already made by insertBeforeStart,
    //That was called since the heap had zero values, after the remove,
    //Inside of consolidateFunction() call

    return nodeWithMinimumValueBackup;
}

void BinomialHeap::consolidateFunction()
{
    //Se a quantidade de elementos for menor que 0, 1 ou mais
    nodeWithMinimumValue = start; //mesmo que não seja
    if (countOfNodes > 1)
    {
        std::vector<BinomialHeapNode*> vec;
        vec.reserve(countOfNodes); //Coloca nullptr em todo o vetor
        vec.resize(countOfNodes);

        while (start != nullptr)
        {
            BinomialHeapNode* removedNodeOfList = removeBeforeStart();
            int grau = removedNodeOfList->grau;
            if (vec.at(grau) == nullptr)
            {
                //Insere nessa posição
                vec[grau] = removedNodeOfList;
            }
            else
            {
                //Tira a tree do vetor
                BinomialHeapNode* removedNodeOfVector = vec[grau];
                vec[grau] = nullptr;

                //Faz o merge com o removido
                BinomialHeapNode* newTree = BinomialHeap::mergeSubTrees
                (
                      removedNodeOfList,
                      removedNodeOfVector
                );

                //Insere em heap novamente
                insertBeforeStart(newTree);
            }
        }

        for (int index = 0; index < vec.size(); ++index)
        {
            auto node = vec.at(index);
            if (node != nullptr)
            {
                //Insere em heap novamente
                insertBeforeStart(node);
            }
        }
    }
}
