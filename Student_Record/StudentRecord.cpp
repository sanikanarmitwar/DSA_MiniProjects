#include <bits/stdc++.h>
 //#include<fstream>
using namespace std;


class StudentRecord{
private:
    string studentName;
    string rollNumber;

public:
    string get_studentName() {
        return studentName;
    }
    void set_studentName(string Name) {
        studentName = Name;
    }
    string get_rollNumber() {
        return rollNumber;
    }
    void set_rollNumber(string rollnum) {
        rollNumber = rollnum;
    }
};

 class Node{
 	private:
 		Node* next=NULL;
 		StudentRecord* element;
 	public:
 	    Node* get_next() {
 	        return next; 
 	    }
 	    StudentRecord* get_element() {
 	        return element; 
 	    }

 	    void set_next(Node* value){
 	    	next = value;
 	    }
 	    void set_element(StudentRecord* student){
 	    	element = student;
        }

 };

 class Entity {
 private:
     string name;
     Node* iterator=NULL;

 public:
     string get_name() {
         return name;
     }
     void set_name(string Name) {
         name = Name;
     }
     Node* get_iterator() {
         return iterator;
     }
     void set_iterator(Node* iter) {
         iterator = iter;
     }
 };
vector<StudentRecord> students;
//vector<LinkedList> EntityArray;


class LinkedList : public Entity {
   //Implement LinkedList members herecv
    public:
         void add(StudentRecord* student,LinkedList* lk){
                    Node* n = new Node;
                    (*n).set_element(student);
                    (*n).set_next(NULL);
                    if((*lk).get_iterator()==NULL)
                    {
                       (*lk).set_iterator(n);
                       return;
                    }
                    Node* p=(*lk).get_iterator();
                    while((*p).get_next()!=NULL)
                    {
                        p = (*p).get_next(); 
                    } 

                    (*p).set_next(n);
          

         }
         void add_student(StudentRecord student)
         {
               students.push_back(student);
               Node* g = new Node;
               (*g).set_element(&students[students.size()-1]);
               (*g).set_next(NULL);
               Node* y=this->get_iterator();
                    while((*y).get_next()!=NULL)
                    {
                        g = (*y).get_next(); 
                    } 

                    (*y).set_next(g);

         }

         void delete_student(string studentName){
            Node* de=this->get_iterator();
            while ((*(*(*de).get_next()).get_element()).get_studentName()!=studentName)
            {
                de = (*de).get_next();
            }
            (*de).set_next((*(*de).get_next()).get_next());
         }
 };
 vector<LinkedList> EntityArray;


void read_input_file(string file_path){
    fstream fl;
    fl.open(file_path,ios::in);

     if(!fl.is_open())
     {
         cout<<"ERROR"<<endl;
     }

    string sn;
    string rn,line,w;
    StudentRecord sr;
    while(getline(fl,line))
    {
        stringstream ss(line);
        getline(ss,sn,',');
        getline(ss,rn,',');
        sr.set_studentName(sn);
        sr.set_rollNumber(rn);
        students.push_back(sr);
        while(getline(ss,w,','))
        {
            if(w.at(0)=='[')
            {
                w.erase(w.begin()+0);

            }
            if(w.at(w.size()-1)==']')
            {
                w.erase(w.size()-1);
            }
            int c=0;
            for(int i=0;i<EntityArray.size();i++)
            {
                if(w==EntityArray[i].get_name())
                {
                    EntityArray[i].add(&students[students.size()-1],&EntityArray[i]);
                    c=1;
                    break;
                }
            }
            if(c==0)
            { 
                LinkedList ll;
                    ll.set_name(w);
                    ll.set_iterator(NULL);
                    EntityArray.push_back(ll);
                    ll.add(&students[students.size()-1],&EntityArray[EntityArray.size()-1]);
            }
        }
    }
}