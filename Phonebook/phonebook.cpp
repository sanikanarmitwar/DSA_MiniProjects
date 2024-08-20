// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm>
// #include <set>
// #include <fstream>
// #include <sstream>
// #include <map>
#include <bits/stdc++.h>

using namespace std;

class PhoneRecord {
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string& n, const string& org, const vector<string>& numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getter methods
    string getName() const {
        return name;
    }

    string getOrganisation() const {
        return organisation;
    }

    vector<string> getPhoneNumbers() const {
        return phoneNumbers;
    }
};

class HashTableRecord {
private:
    int key;
    PhoneRecord* element; // Pointer to PhoneRecord
    HashTableRecord* next;

public:
    // Constructor
    HashTableRecord(int k, PhoneRecord* rec)
        : key(k), element(rec), next(NULL) {}

    // Getter methods
    int getKey() const {
        return key;
    }

    PhoneRecord* getRecord() const {
        return element;
    }

    HashTableRecord* getNext() const {
        return next;
    }

    void setNext(HashTableRecord* nxt) {
        next = nxt;
    }
};

class PhoneBook {
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord* hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = NULL;
        }
    }

    // Add your own implementation for hashing
    long long computeHash(const string& str)
     {
        // Implement a hash function for strings
        long long s=0;
        for(int i=0;i<str.size();i++)
        {
            // long long p = 1000000007;
            long long r = pow(263,i);
            s=s+(long long)(((long long int)(int(str.at(i))*r))%1000000007);
        }
        long long ky=(long long int)s%263;
        return ky;
    }

    // Add your own implementation for adding a contact
    void addContact(const PhoneRecord* record)
    { 
        PhoneRecord* pc = (PhoneRecord*)(record);
        string nm=(pc)->getName();
        istringstream sm(nm);
        string wo;
        while (sm >> wo)
        {
            int k = this->computeHash(wo);
            HashTableRecord* ht = new HashTableRecord(k,pc);
            if(hashTable[k]!=NULL)
            {
               HashTableRecord* hr = hashTable[(ht)->getKey()];
               while((hr)->getNext()!=NULL)
               { 
                if(hr->getRecord()->getName()==record->getName())
                {
                    return;
                }
                hr=(hr)->getNext();
               }
               (hr)->setNext(ht);
            }
            else if(hashTable[k]==NULL)
            {
                hashTable[(ht)->getKey()]=ht;
            }
        }
    }

    // Add your own implementation for deleting a contact
    bool deleteContact(const string* searchName)
    {
        istringstream sm((*searchName));
        string wo;
        while(sm>>wo)
        {
            int k = this->computeHash(wo);
            HashTableRecord* pp=hashTable[k];
            HashTableRecord* pre = nullptr;
            if(hashTable[k]==nullptr)
            {
                return 0;
            }
            if((((hashTable[k])->getRecord())->getName()).find(*searchName) != string::npos)
            {
                hashTable[k]=(hashTable[k])->getNext();
                continue;
            }
            while(((pp)->getRecord())->getName().find(*searchName) == string::npos)
            {
               if(((pp)->getNext())==NULL)
               {
                return 0;
               }
               else
               pre=pp;
               pp=(pp)->getNext();
            }
            (pre)->setNext(((pre)->getNext())->getNext());
        }
        return 1;
    }

    // Add your own implementation for fetching contacts
    vector<PhoneRecord*> fetchContacts(const string* query)
    {
        istringstream sm((*query));
        string wo;
        vector<PhoneRecord*> fc;

        while(sm>>wo)
        {
            int k=this->computeHash(wo);
            HashTableRecord* hs= hashTable[k];
            if(hashTable[k]==nullptr)
            {
                continue;
            }
            while(hs!=NULL)
            {
            if(hs->getRecord()->getName().find(wo)!= string::npos)
            {
            fc.push_back((hs)->getRecord());
            }
            hs=hs->getNext();
            }
        }
        sort(fc.begin(),fc.end());
        return fc;

    }

    // Add your own implementation for counting records pointing to a contact
    int countRecordsPointingTo(const PhoneRecord* record) const
    {
        PhoneRecord* pc = (PhoneRecord*)(record);
        string nm=(*record).getName();
        istringstream sm(nm);
        string wo;
        int c=0;
        while (sm >> wo)
        {
           int k = ((PhoneBook*)(this))->computeHash(wo);
            HashTableRecord* pp=hashTable[k];
            if((*hashTable[k]).getRecord()==record)
            {
                c++;
                continue;
            }
            while((*(*pp).getNext()).getRecord()!=record)
            {
               if((*(*pp).getNext()).getNext()==NULL)
               {
                continue;
               }
               else
               pp=(*pp).getNext();
            }
            c++;
            
        }
        return c;
    }

    // Add your own implementation for reading records from a file
    void readRecordsFromFile(const string& filename)
    {
    fstream fl;
    fl.open(filename,ios::in);

     if(!fl.is_open())
     {
         cout<<"ERROR"<<endl;
     }
    string na,org,line,w;
    // vector<string> ph;
    while(getline(fl,line))
    {
        vector<string> ph;
        stringstream ss(line);
        getline(ss,na,',');
        while (getline(ss,w,','))
        {
            if(int(w.at(0))>=48 && int(w.at(0))<=57)
            {
                ph.push_back(w);
            }
            else{
                org=w;
            }
        }
        PhoneRecord* pr = new PhoneRecord(na,org,ph);
        istringstream sm((*pr).getName());
        string wo;
        while (sm >> wo)
        {
            int k = this->computeHash(wo);
            HashTableRecord* ht = new HashTableRecord(k,pr);
            if(hashTable[(*ht).getKey()]!=NULL)
            {
               HashTableRecord* hr = hashTable[(*ht).getKey()];
               while((*hr).getNext()!=NULL)
               {
                     hr=(*hr).getNext();
               }
               (*hr).setNext(ht);
            }
            else if(hashTable[(*ht).getKey()]==NULL)
            {
                hashTable[(*ht).getKey()]=ht;
            }
        }
    }
    

    
}

    // Destructor
    // ~PhoneBook();
};

