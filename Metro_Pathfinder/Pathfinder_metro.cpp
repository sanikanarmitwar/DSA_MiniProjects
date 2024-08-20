#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;



// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop {
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(std::string name, MetroLine* metroLine, int fare) {
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const {
    return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

// MetroLine class
class MetroLine {
private:
    std::string lineName;
    MetroStop* node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name) {
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this->node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const {
    int c=0;
    MetroStop* nnn = this->getNode();
    while(nnn!=nullptr)
    {
        c++;
        nnn=nnn->getNextStop();
    }
    return c;
}

void MetroLine::populateLine(std::string filename) {
    fstream fl;
    fl.open(filename,ios::in);
    if(!fl.is_open())
    {
        cout<<"ERROR"<<endl;
    }
    string line;
    while(getline(fl,line))
    {
        string sp,ff;
        int i=line.length();
        while(line[i-1]!=' ')
        {
            i--;
        }
        for(int j=0;j<i-1;j++)
        {
            sp.push_back(line[j]);
        }
        int c=0;
        for(int k=i;k<line.length();k++)
        {
            ff[c]=line[k];
            c++;
        }
        int ss=stoi(ff);
        MetroStop* ms = new MetroStop(sp,this,ss);
        if(this->getNode()==nullptr)
        {
            setNode(ms);
        }
        else
        {
            MetroStop* itt=getNode();
            while(itt->getNextStop()!=nullptr)
            {
                itt=itt->getNextStop();
            }
            itt->setNextStop(ms);
            ms->setPrevStop(itt);
        }

    }
    // Read the file and populate the line
}

// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop*>& getStops() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
};

AVLNode::AVLNode(std::string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

std::string AVLNode::getStopName() const {
    return stopName;
}

const std::vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree {
    // Define your AVLTree implementation here.
private:
    AVLNode* root;

public:
    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    void rotateLeft(AVLNode* node);
    void rotateRight(AVLNode* node);
    void balance(AVLNode* node);
    int stringCompare(string s1, string s2);
    void insert(AVLNode* node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
};

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node) {
    if (node == NULL)
        return 0;
    else {
        int lh = height(node->getLeft());
        int rh = height(node->getRight());
        if (lh > rh)
            return (lh + 1);
        else
            return (rh + 1);
    }
}

int AVLTree::stringCompare(string s1, string s2) {
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode* node) {
    int bf = height(node->getLeft()) - height(node->getRight());
    return bf;
}

void AVLTree::rotateLeft(AVLNode* node) {
    AVLNode *y = node->getRight();
    AVLNode *T2 = node->getRight()->getLeft();
    if(node==this->getRoot())
    {
        this->setRoot(y);
    }
    y->setParent(node->getParent());
    if(y!=this->getRoot()){
    if(y->getParent()->getLeft()==node)
    {
        y->getParent()->setLeft(y);
    }
    else
    {
        y->getParent()->setRight(y);
    }
    }
    node->setParent(y);
    if(T2!=nullptr)
    {
    T2->setParent(node);
    }
    node->setRight(T2);
    y->setLeft(node);
}

void AVLTree::rotateRight(AVLNode* node) {
    AVLNode *x = node->getLeft();
    AVLNode *T2 = node->getLeft()->getRight();
    if(this->getRoot()==node)
    {
        this->setRoot(x);
    }
    x->setParent(node->getParent());
    if(x!=this->getRoot()){
    if(x->getParent()->getLeft()==node)
    {
        x->getParent()->setLeft(x);
    }
    else
    {
        x->getParent()->setRight(x);
    }
    }
    node->setParent(x);
    if(T2!=nullptr)
    {
    T2->setParent(node);
    }
    node->setLeft(T2);
    x->setRight(node);
}
void AVLTree::balance(AVLNode* node) {
    // if (balanceFactor(node)> 1 && stringCompare(node->getStopName(),node->getLeft()->getStopName())<0)
    //     rotateRight(node);
    // else if (balanceFactor(node) < -1 && stringCompare(node->getStopName(),node->getRight()->getStopName())>0)
    //      rotateLeft(node);
    // else if (balanceFactor(node) > 1 && stringCompare(node->getStopName(),node->getLeft()->getStopName())>0)
    // {
    //     rotateLeft(node->getLeft());
    //     rotateRight(node);
    // }
    // else if (balanceFactor(node) < -1 && stringCompare(node->getStopName(),node->getRight()->getStopName())<0)
    // {
    //     rotateRight(node->getRight());
    //     rotateLeft(node);
    // }
}

void AVLTree::insert(AVLNode* node, MetroStop* metroStop) {
    if(stringCompare(node->getStopName(),metroStop->getStopName())>0)
    { 
        if(node->getLeft()==nullptr)
        {
            AVLNode* nn= new AVLNode(metroStop->getStopName());
            node->setLeft(nn);
            nn->setParent(node);
            nn->addMetroStop(metroStop);
            // balance(nn);
        }
        else
        insert(node->getLeft(),metroStop);
    }
    else if(stringCompare(node->getStopName(),metroStop->getStopName())<0)
    {
        if(node->getRight()==nullptr)
        {
            AVLNode* nn= new AVLNode(metroStop->getStopName());
            node->setRight(nn);
            nn->setParent(node);
            nn->addMetroStop(metroStop);
            // balance(nn);
        }
        else
        insert(node->getRight(),metroStop);
    }
    else
    {
        node->addMetroStop(metroStop);
    }
    // balance(node);
    if (balanceFactor(node)> 1 && stringCompare(metroStop->getStopName(),node->getLeft()->getStopName())<0)
        rotateRight(node);
    else if (balanceFactor(node) < -1 && stringCompare(metroStop->getStopName(),node->getRight()->getStopName())>0)
         rotateLeft(node);
    else if (balanceFactor(node) > 1 && stringCompare(metroStop->getStopName(),node->getLeft()->getStopName())>0)
    {
        rotateLeft(node->getLeft());
        rotateRight(node);
    }
    else if (balanceFactor(node) < -1 && stringCompare(metroStop->getStopName(),node->getRight()->getStopName())<0)
    {
        rotateRight(node->getRight());
        rotateLeft(node);
    }
}

void AVLTree::populateTree(MetroLine* metroLine) {
    MetroStop* mst= metroLine->getNode();
    while(mst!=nullptr)
    { 
        if(this->getRoot()==nullptr)
        {
            setRoot(new AVLNode(mst->getStopName()));
        }
        else if(mst->getStopName()=="Dwarka Sec-21")
        {
            mst=mst->getNextStop();
        }
        else{
            this->insert(this->getRoot(),mst);
            mst=mst->getNextStop();
        }
    }
}

void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode* AVLTree::searchStop(string stopName) {
    AVLNode* at=this->getRoot();
    while(at->getStopName()!=stopName)
    {
        if(stringCompare(at->getStopName(),stopName)>0)
        {
            at=at->getLeft();
        }
        else
        {
            at=at->getRight();
        }
    }
    return at;
}

// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip);

    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip) {
    node = metroStop;
    prev = previousTrip;
}

MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

std::queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}

class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

std::vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    for (auto stop : stops) {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;

public:
    PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines);
    void createAVLTree();
    Path* findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree* getTree() const;
    const std::vector<MetroLine*>& getLines() const;
};

PathFinder::PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines) {
    tree = avlTree;
    lines = metroLines;
}

AVLTree* PathFinder::getTree() const {
    return tree;
}

const std::vector<MetroLine*>& PathFinder::getLines() const {
    return lines;
}

void PathFinder::createAVLTree() {
    for(int i=0;i<lines.size();i++)
    {
        tree->populateTree(lines[i]);
    }
}

Path* PathFinder::findPath(std::string origin, std::string destination) {
    AVLNode* ptr = tree->searchStop(origin);
    for(int i=0;i<ptr->getStops().size();i++)
    {
       Trip* tf= new Trip(ptr->getStops()[i],nullptr);
       Exploration* ep=new Exploration();
       ep->enqueue(tf);
       while(1)
       {
        if(ep->getTrips().back()->getNode()->getStopName()==destination)
        {
            Path* pt = new Path();
            vector<MetroStop*> vm;
            while(!ep->isEmpty())
            {
                vm.push_back(ep->dequeue()->getNode());
            }
            for(int j=vm.size()-1;j>=0;j--)
            {
                pt->addStop(vm.at(j));
            }
            pt->setTotalFare((pt->getStops().at(0)->getFare())-(pt->getStops().at(pt->getStops().size()-1)->getFare()));
            return pt;
        }
        else
        {
            if(ep->getTrips().back()->getNode()->getNextStop()==nullptr)
            {
                break;
            }
            else
            {
            Trip* nw = new Trip(ep->getTrips().back()->getNode()->getNextStop(),ep->getTrips().back());
            ep->enqueue(nw);
            }
        }
       }

    }




}