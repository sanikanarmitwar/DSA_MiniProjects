// #include <iostream>
// #include <vector>
// #include <map>
#include <bits/stdc++.h>
using namespace std;

class Vehicle;

class Trip {
public:
    Trip(Vehicle* vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle* getVehicle() const {
        return vehicle;
    }

    std::string getPickUpLocation() const {
        return pick_up_location;
    }

    std::string getDropLocation() const {
        return drop_location;
    }

    int getDepartureTime() const {
        return departure_time;
    }

    int getBookedSeats() const {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle* v) {
        vehicle = v;
    }

    void setPickUpLocation(std::string location) {
        pick_up_location = location;
    }

    void setDropLocation(std::string location) {
        drop_location = location;
    }

    void setDepartureTime(int time) {
        departure_time = time;
    }

    void setBookedSeats(int seats) {
        booked_seats = seats;
    }

private:
    Vehicle* vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};


class BinaryTreeNode {
public:
    BinaryTreeNode(int departuretime = 0, Trip* tripenodeptr = nullptr, BinaryTreeNode* parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode* getLeftPtr() const {
        return leftptr;
    }

    BinaryTreeNode* getRightPtr() const {
        return rightptr;
    }

    BinaryTreeNode* getParentPtr() const {
        return parentptr;
    }

    int getDepartureTime() const {
        return departuretime;
    }

    Trip* getTripNodePtr() const {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode* left) {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode* right) {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode* parent) {
        parentptr = parent;
    }

    void setDepartureTime(int time) {
        departuretime = time;
    }

    void setTripNodePtr(Trip* trip) {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode* leftptr;
    BinaryTreeNode* rightptr;
    BinaryTreeNode* parentptr;
    int departuretime;
    Trip* tripnodeptr;
};

class TransportService {
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    BinaryTreeNode* getBSTHead() const {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name) {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode* node) {
        BSThead = node;
    }

    void addTrip(int key, Trip* trip)
    {
        BinaryTreeNode* nn= new BinaryTreeNode(key,trip);
        if(this->getBSTHead()==nullptr)
        {
            setBSTHead(nn);
            return;
        }
        else
        {
            BinaryTreeNode* pv=NULL;
            BinaryTreeNode* nd=this->getBSTHead();
            while (nd!=nullptr)
            {
                if((nd->getTripNodePtr())->getDepartureTime()>key)
                {
                   pv=nd;
                   nd=nd->getLeftPtr();
                }
                else if((nd->getTripNodePtr())->getDepartureTime()<key)
                {
                   pv=nd;
                   nd=nd->getRightPtr();
                }
                else
                return;
            }
            if(pv->getDepartureTime()>key)
            {
               pv->setLeftPtr(nn);
            }
            else if(pv->getDepartureTime()<key)
            {
               pv->setRightPtr(nn);
            }
            nn->setParentPtr(pv);
            return;
        }
    }

private:
    std::string name;
    BinaryTreeNode* BSThead;
};
class Vehicle {
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const {
        return vehicle_number;
    }

    int getSeatingCapacity() const {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number) {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity) {
        seating_capacity = capacity;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

    vector<Trip*> getTrips(){
        return trips;
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip*> trips;
};

class Location {
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    TransportService* getServicePtr(std::string droplocation) const {
        for(int i=0;i<serviceptrs.size();i++)
        {
            if(serviceptrs[i]->getName()==droplocation)
            {
                return serviceptrs[i];
            }
        }
        return nullptr;
    }

    // Setter functions
    void setName(std::string location_name) {
        name = location_name;
    }

    vector<TransportService*> getvector()
    {
        return serviceptrs; 
    }

    TransportService* setServicePtr(std::string droplocation) {
        TransportService* ts=new TransportService(droplocation);
        int c=0;
        for(int i=0;i<serviceptrs.size();i++)
        {
            if(droplocation==serviceptrs[i]->getName())
            {
                c=1;
                return nullptr;
            }
        }
        if(c==0)
        {
          serviceptrs.push_back(ts);
        }
        return nullptr;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

private:
    std::string name;
    std::vector<TransportService* >serviceptrs;
    std::vector<Trip*> trips;
};

class BinaryTree {
protected:
    BinaryTreeNode* root;

public:
    BinaryTree() : root(nullptr) {}

    int getHeight() const {
    int depth = 0;
    queue<BinaryTreeNode*> q;
    q.push(root);
    q.push(NULL);
    while (!q.empty()) {
        BinaryTreeNode* temp = q.front();
        q.pop();
 
        // When NULL encountered, increment the value
        if (temp == nullptr) {
            depth++;
        }
 
        // If NULL not encountered, keep moving
        if (temp != nullptr) {
            if (temp->getLeftPtr()!=nullptr) {
                q.push(temp->getLeftPtr());
            }
            if (temp->getRightPtr()!=nullptr) {
                q.push(temp->getRightPtr());
            }
        }
 
        // If queue still have elements left,
        // push NULL again to the queue.
        else if (!q.empty()) {
            q.push(NULL);
        }
    }
    return depth;
    }

    int getNumberOfNodes() const {
    if (root==nullptr) 
        return 0; 
    queue<BinaryTreeNode *> q; 
    BinaryTreeNode* temp;
      
    // Do level order traversal starting from root 
    int count = 0; // Initialize count of full nodes 
    q.push(root); 
    while (!q.empty()) 
    { 
        temp = q.front(); 
        q.pop(); 
        if(temp!= nullptr)
        {
            count++;
        }
        if (temp->getLeftPtr() != nullptr) 
            q.push(temp->getLeftPtr()); 
        if (temp->getRightPtr() != nullptr) 
            q.push(temp->getRightPtr()); 
    } 
    return count; 
    }
};

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree() {}

    BinaryTreeNode* getElementWithMinimumKey() const {
        BinaryTreeNode* mk = root;
        while(mk->getLeftPtr()!= nullptr)
        {
            mk=mk->getLeftPtr();
        }
        // Implement this function to return the element with the minimum key
        return mk; // Placeholder
    }

    BinaryTreeNode* getElementWithMaximumKey() const {
        BinaryTreeNode* mk = root;
        while(mk->getRightPtr()!= nullptr)
        {
            mk=mk->getRightPtr();
        }
        return mk;
    }

    BinaryTreeNode* searchNodeWithKey(int key) const {
        BinaryTreeNode *ns = root;
        while(ns!=nullptr)
        {
            if(ns->getDepartureTime()==key)
            return ns;
            else if(ns->getDepartureTime()>key)
            ns=ns->getLeftPtr();
            else
            ns=ns->getRightPtr();
        }
        // Implement this function to search for a node with the given key or the next larger key
        return nullptr; // Placeholder
    }

    BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node) const {
        BinaryTreeNode* itt = root;
        BinaryTreeNode* sc;
        if(root==nullptr)
        {
            return nullptr;
        }
        while(itt!=nullptr)
        {
            if(itt->getDepartureTime()==node->getDepartureTime())
            {
                if(itt->getRightPtr()!=nullptr)
                {
                    sc=itt->getRightPtr();
                    while(sc->getLeftPtr()!=nullptr)
                    {
                        sc=sc->getLeftPtr();
                    }
                    return sc;
                }
                else
                return sc;
            }
            else if(itt->getDepartureTime()<node->getDepartureTime())
            {
                itt=itt->getRightPtr();
            }
            else
            {
                sc=itt;
                itt=itt->getLeftPtr();
            }
        }
        return sc;
    }

    BinaryTreeNode* getSuccessorNodeByKey(int key) const {
        BinaryTreeNode* itt = root;
        BinaryTreeNode* sc;
        if(root==nullptr)
        {
            return nullptr;
        }
        while(itt!=nullptr)
        {
            if(itt->getDepartureTime()==key)
            {
                if(itt->getRightPtr()!=nullptr)
                {
                    sc=itt->getRightPtr();
                    while(sc->getLeftPtr()!=nullptr)
                    {
                        sc=sc->getLeftPtr();
                    }
                    return sc;
                }
                else 
                return sc;
            }
            else if(itt->getDepartureTime()<key)
            {
                itt=itt->getRightPtr();
            }
            else
            {
                sc=itt;
                itt=itt->getLeftPtr();
            }
        }
        return sc;
    }

    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const {
         BinaryTreeNode* itt = root;
        BinaryTreeNode* pv;
        if(root==nullptr)
        {
            return nullptr;
        }
        while(itt!=nullptr)
        {
            if(itt->getDepartureTime()==node->getDepartureTime())
            {
                if(itt->getLeftPtr()!=nullptr)
                {
                    pv=itt->getLeftPtr();
                    while(pv->getRightPtr()!=nullptr)
                    {
                        pv=pv->getRightPtr();
                    }
                    return pv;
                }
                else
                return pv;
            }
            else if(itt->getDepartureTime()<node->getDepartureTime())
            {
                pv=itt;
                itt=itt->getRightPtr();
            }
            else
            {
                itt=itt->getLeftPtr();
            }
        }
        return pv;
    }

    BinaryTreeNode* getPredecessorNodeByKey(int key) const {
         BinaryTreeNode* itt = root;
        BinaryTreeNode* pv;
        if(root==nullptr)
        {
            return nullptr;
        }
        while(itt!=nullptr)
        {
            if(itt->getDepartureTime()==key)
            {
                if(itt->getLeftPtr()!=nullptr)
                {
                    pv=itt->getLeftPtr();
                    while(pv->getRightPtr()!=nullptr)
                    {
                        pv=pv->getRightPtr();
                    }
                    return pv;
                }
                else
                return pv;
            }
            else if(itt->getDepartureTime()<key)
            {
                pv=itt;
                itt=itt->getRightPtr();
            }
            else
            {
                itt=itt->getLeftPtr();
            }
        }
        return pv;
    }
};

class TravelDesk {
public:
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time) {
        int k=0;
        Vehicle* vh;
        for(int i=0;i<vehicles.size();i++)
        {
            if(vehicle_number==vehicles[i]->getVehicleNumber())
            {
               vh=vehicles[i];
               k=1;
            }
        }
        if(k==0)
        {
            Vehicle* vehicle = new Vehicle(vehicle_number,seating_capacity);
            vehicles.push_back(vehicle);
            vh=vehicle;
        }
        Trip* tp = new Trip(vh,pick_up_location,drop_location,departure_time);
        vh->addTrip(tp);
         int v=0;
                for(int i=0;i<locations.size();i++)
                 {
                     if(pick_up_location==locations[i]->getName())
                    {
                        locations[i]->setServicePtr(drop_location);
                        locations[i]->addTrip(tp);
                        TransportService* ttp=locations[i]->getServicePtr(drop_location);
                        ttp->addTrip(departure_time,tp);
                        v=1;
                    }
                }
                if(v==0)
                {
                   Location* lo=new Location(pick_up_location);
                   lo->addTrip(tp);
                   locations.push_back(lo);
                   lo->setServicePtr(drop_location);
                   TransportService* tsp = lo->getServicePtr(drop_location);
                   tsp->addTrip(departure_time,tp);

                }
    }

    std::vector<Trip*> showTrips(std::string pick_up_location, int after_time, int before_time) {
        vector<Trip*> ti;
        stack<BinaryTreeNode*> st;
        vector<TransportService*> tss;
        Location* ll;
        for(int i=0;i<locations.size();i++)
        {
            if(pick_up_location==locations[i]->getName())
            {
               ll=locations[i];
            }
        }
                tss=ll->getvector();
                for(int j=0;j<tss.size();j++)
                {
                TransportService* stp=ll->getServicePtr(tss[j]->getName());
                BinaryTreeNode* bn=stp->getBSTHead();
                while (bn != NULL || st.empty() == false) 
                {
                   while (bn != NULL) 
                   {
                       st.push(bn);
                       bn = bn->getLeftPtr();
                   }
                   bn = st.top();
                   if(bn->getDepartureTime()>after_time && bn->getDepartureTime()<before_time)
                   {
                   ti.push_back(bn->getTripNodePtr());
                   }
                   st.pop();
                   bn = bn->getRightPtr();
                }
                }
        // Implement this function to retrieve trips within a specified time range
        return ti; // Placeholder
    }
    std::vector<Trip*> showTripsbydestination(std::string pick_up_location, std::string destination,int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
         stack<BinaryTreeNode*> st;
        vector<Trip*> ti;
        for(int i=0;i<locations.size();i++)
        {
            if(locations[i]->getName()==pick_up_location)
            {
                TransportService* stp=locations[i]->getServicePtr(destination);
                BinaryTreeNode* bn=stp->getBSTHead();
                while (bn != NULL || st.empty() == false) 
                {
                   while (bn != NULL) 
                   {
                       st.push(bn);
                       bn = bn->getLeftPtr();
                   }
                   bn = st.top();
                   if(bn->getDepartureTime()>after_time && bn->getDepartureTime()<before_time)
                   {
                   ti.push_back(bn->getTripNodePtr());
                   }
                   st.pop();
                   bn = bn->getRightPtr();
                }
            } 
        }
        return ti;
    }

    Trip* bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time) {
        for(int i=0;i<locations.size();i++)
        {
            if(locations[i]->getName()== pick_up_location)
            {
                TransportService* stp=locations[i]->getServicePtr(drop_location);
                if(stp==nullptr)
                {
                    return nullptr;
                }
                BinaryTreeNode* bn=stp->getBSTHead();
                while(bn!=nullptr)
                {
                    if(bn->getDepartureTime()==departure_time)
                    {
                        if(bn->getTripNodePtr()->getBookedSeats()==bn->getTripNodePtr()->getVehicle()->getSeatingCapacity())
                        {
                            return nullptr;
                        }
                        else
                        {
                            bn->getTripNodePtr()->setBookedSeats(bn->getTripNodePtr()->getBookedSeats()+1);
                            return bn->getTripNodePtr();
                        }
                    }
                    else if(bn->getDepartureTime()>departure_time)
                    {
                        bn=bn->getLeftPtr();
                    }
                    else if(bn->getDepartureTime()<departure_time)
                    {
                        bn=bn->getRightPtr();
                    }
                }

            }
        }
        // Implement this function to book a trip
        return nullptr; // Placeholder
    }

    Location* getLocation(std::string location){
        for(int i=0;i<locations.size();i++)
        {
            if(locations[i]->getName()==location)
            {
                return locations[i];
            }
        }
        return nullptr;
    }
    void readfile(string file)
    {
        fstream fl;
       fl.open(file,ios::in);
       if(!fl.is_open())
     {
         cout<<"ERROR"<<endl;
     }
     string line,wo,vn,pn,op,cc,pl,dl,tt;
     int sc;
       while(getline(fl,line))
    {
        stringstream sm(line);
        getline(sm,op,' ');
        if(op=="ADDTRIP")
        {
        getline(sm,vn,' ');
        getline(sm,cc,' ');
        sc=stoi(cc);
        getline(sm,pl,' ');
        getline(sm,dl,' ');
        getline(sm,tt,' ');
        for(int i=0;i<tt.size();i++)
        {
            if(tt.at(i)==':')
            {
                for(int j=i;j<tt.size();j++)
                {
                    tt[j]=tt[j+1];
                }
            }
        }
            this->addTrip(vn,sc,pl,dl,stoi(tt));
        }

    }
    }

private:
    std::vector<Vehicle*> vehicles;
    std::vector<Location*> locations;
};