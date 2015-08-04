/*
 *
 * Max Adelman
 * Winter 2014
 * Lab 7
 *
 * This program is edited from lab5
 * speech.txt file
 * creates a frequency tree based on occurances of characters
 */

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdbool.h>
#include <fstream>
#include <iomanip>
#include <list>
#include <stack>

using namespace std;


struct Value
{
    char data;
    int numbers;
    Value()
    {
        data = '\0';
        numbers = 0;
    }
    Value(char d) 
    { 
        numbers = 1;
        data = d; 
    }

    bool operator < (const Value&A)
    {
        if(A.numbers < numbers)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    bool operator >= (const Value&A)
    {
        if(A.numbers >= numbers)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    operator char() { return data; }
};

struct Node
{
    Value data;
    Node* left;
    Node* right;

    Node()
    {
        left = NULL;
        right = NULL;
        Value nothing;
        data = nothing;

    }
    Node(Value data2)
    {
        data = data2;
    }
    Node(Node &n)
    {
        data = n.data;
        left = n.left;
        right = n.right;
    }
};


int height(Node*);

int height(Node *n)
{
    int H = 0;
    if(n != NULL)
    {
        int L = height(n->left);
        int R = height(n->right);
        int M;
        if(L >= R)
        {
            M = L;
        }
        else
        {
            M = R;
        }

        H = M++;

    }
    return H;
}

int difference(Node *n)
{
    
    int L = height(n->left);
    
    int R = height(n->right);

    int B = L - R;
    return B;
}

Node* rrRotation(Node *n)
{   
    Node *T = n->right;
    n->right = T->left;
    T->left = n;
    return T;
}

Node* llRotation(Node *n)
{
    Node *T = n->left;
    n->left = T->right;
    T->right = n;
    return T;
}

Node* lrRotation(Node *n)
{
    Node *T = n->left;
    n->left = rrRotation(T);
    return llRotation(n);
}

Node* rlRotation(Node *n)
{
    Node *T = n->right;
    n->right = llRotation(T);
    return rrRotation(n);
}

Node* balance(Node *n)
{
    int F = difference(n);
    if(F > 1)
    {
        if(difference(n->right) > 0)
        {
            n = llRotation(n);
        }
        else
        {
            n = lrRotation(n);
        }
    }
    else if(F < -1)
    {
        if(difference(n->right) > 0)
        {
            n = rlRotation(n);
        }
        else
        {
            n = rrRotation(n);
        }
    }
    return n;
}

Node* insert(Node *n,Value v)
{
    
    if(n == NULL)
    {
        n = new Node(v);
        n->left = NULL;
        n->right = NULL;
        return n;
    }

    else if(v.numbers < n->data.numbers)
    {
        n->left = insert(n->left, v);
        n = balance(n);
    }
    else if(v.numbers >= n->data.numbers)
    {
        n->right = insert(n->right,v);
        n = balance(n);
    }
    return n;
}





// *****************************************************

class holder
{
public:
	char head;
	int num;

	void plus()
	{
		num++;
	}
	friend bool operator<(const holder&, const holder&);
};

bool operator<(const holder &a, const holder &b)
{
	if(a.num >= b.num)// && (a.carNumber == b.carNumber))
	{	
		return true;
	}
	else
	{
		return false;
	}

}

template <typename E, typename C>
class ListPriorityQueue 
{ 
public:
	int size() const;				// number of elements
    bool empty() const;				// is the queue empty?
    void insert(const E& e);			// insert element
    const E& min() const;			// minimum element
    void removeMin();				// remove minimum
private:
    std::list<E> L;				// priority queue contents
    C isLess;					// less-than comparator
};

template <typename E, typename C>			// insert element
void ListPriorityQueue<E,C>::insert(const E& e) 
{
	typename std::list<E>::iterator p;
	p = L.begin();
    while (p != L.end() && !isLess(e, *p)) ++p;		// find larger element
    L.insert(p, e);					// insert e before p
}


template <typename E, typename C>			// minimum element
const E& ListPriorityQueue<E,C>::min() const
{ 
	return L.front(); 
}				// minimum is at the front

template <typename E, typename C>			// remove minimum
void ListPriorityQueue<E,C>::removeMin()	
{ 
	L.pop_front(); 
}

template <typename E, typename C>		// number of elements
int ListPriorityQueue<E,C>::size() const
{ 
	return L.size(); 
}

template <typename E, typename C>		// is the queue empty?
bool ListPriorityQueue<E,C>::empty() const
{ 
	return L.empty(); 
}




int main()
{
	

	ListPriorityQueue<holder, less<holder> > pqueue;
	ListPriorityQueue<char,less<char> > pqueue2;
	ifstream inputFile;

    inputFile.open("Speech.txt");
    
    
    if(inputFile.fail())
    {
    	fprintf(stderr, "Error in reading file\n");
    	exit(1);
    }

    //this loop will continue until the end of the file is reached
    while(inputFile.peek() != EOF)
    {
            string s;
            getline(inputFile, s);
            int tempSize = s.size();
            
            for(int i = 0; i <= tempSize; i++)
            {
            	char temp = s[i];
            	pqueue2.insert(temp);
            }        
    } 

    inputFile.close();

    holder force;
    force.num = 0;

    while(pqueue2.empty() != true)
    {
    	char zaku;
    	zaku = pqueue2.min();
    	pqueue2.removeMin();

    	if(force.head == zaku)
    	{
    		force.plus();
    	}
    	else
    	{
    		pqueue.insert(force);
    		
    		force.head = zaku;
    		force.num = 1;
    	}

    }
    pqueue.insert(force);
	int i = 0;

    Node *tree;

    while(pqueue.empty()!=true)
    {

        cout << pqueue.min().head << " (" << pqueue.min().num << ")" <<  endl;
        
        Value putter;
        putter.data = pqueue.min().head;
        putter.numbers = pqueue.min().num;
        tree = insert(tree,putter);
        pqueue.removeMin();
       	i++;
    }

	return 0;
}
