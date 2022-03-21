#pragma once

#include <sstream>
#include <set>
#include "Tuple.h"


using namespace std;

class Relation {

private:
string name;
Scheme scheme; 
set<Tuple> tuple_set;


public:
    void addTuple(Tuple t) {
        tuple_set.insert(t);
    };
    
    string getName() {
        return name;
    };

    Scheme getScheme() {
        return scheme;
    };

    set<Tuple> getSet() {
        return tuple_set;
    };

    Relation() {};
    
    Relation(string n, Scheme s) {
        name = n;
        scheme = s;
    };
    
    Relation(string n, set<Tuple> s) {
        name = n;
        tuple_set = s;
    };
    
    Relation(string n) {
        name = n;
    };
    
    string toString() {
        stringstream ss;
        if(tuple_set.empty()) {
            ss << "No";
        }
        else {
            ss << "Yes(" << tuple_set.size() << ")";
            for(auto& t : tuple_set) {
                if(t.empty()) {
                    
                }
                else {
                    ss << endl << "  ";
                    for(int i = 0; i < (int)t.size(); ++i) {
                        ss << scheme.at(i) << "=" << t.at(i);
                        if(i == (int)t.size()-1) {
                            
                        }
                        else {
                            ss << ", ";
                        }
                    }
                }
                
            }
        }
        return ss.str();
    };

    Relation select(string constant, int index, Relation relation) {
        Relation newRelation(relation.getName(), relation.getScheme());
        for(auto& t : relation.getSet()) {
            if(t.at(index) == constant) {
                newRelation.addTuple(t);
            }
        }
        return newRelation;
    };
    Relation select(int index1, int index2, Relation relation) {
        Relation newRelation(relation.getName(), relation.getScheme());
        for(auto& t : relation.getSet()) {
            if(t.at(index1) == t.at(index2)) {
                newRelation.addTuple(t);
            }
        }
        return newRelation;
    };


    Relation project(vector<int> positions, Relation relation) {
        Relation newRelation(relation.getName());
        for(auto& t : relation.getSet()) {
            Tuple temp;
            for(int j = 0; j < (int)positions.size(); j++){
                temp.push_back(t.at(positions.at(j)));
                scheme.push_back(relation.scheme.at(j));
            }
            newRelation.addTuple(temp);
        }
        return newRelation;
    };



    Relation rename(vector<string> variables, Relation relation) {
        Relation newRelation(relation.getName(), relation.getSet());
        for(int i = 0; i < (int)variables.size(); i++) {
            newRelation.scheme.push_back(variables.at(i));
        }
        return newRelation;
    };

    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme,
	    	const Tuple& leftTuple, const Tuple& rightTuple) {
        bool flag = true;

        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
            const string& leftName = leftScheme.at(leftIndex);
            const string& leftValue = leftTuple.at(leftIndex);
            cout << "left name: " << leftName << " value: " << leftValue << endl;
            for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
                const string& rightName = rightScheme.at(rightIndex);
                const string& rightValue = rightTuple.at(rightIndex);
                cout << "right name: " << rightName << " value: " << rightValue << endl;
                if(leftIndex != leftScheme.size()-1) {
                    for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
                        const string& rightName = rightScheme.at(rightIndex);
                        const string& rightValue = rightTuple.at(rightIndex);
                        if(leftScheme.at(leftIndex+1) == rightName && leftTuple.at(leftIndex+1) != rightValue) {
                            flag = false;
                        }
                    }
                }
                
            }
        }

        return flag;
    }

    Relation join(const Relation& r) {

        const Scheme& leftScheme = scheme;
        const Scheme& rightScheme = r.scheme;

        for (const Tuple& leftTuple : tuple_set) {
            cout << "left tuple: " << leftTuple.toString(leftScheme) << endl;

            for (const Tuple& rightTuple : r.tuple_set) {
                cout << "right tuple: " << rightTuple.toString(rightScheme) << endl;
            }
        }

        
        

        return Relation();
    }

};

