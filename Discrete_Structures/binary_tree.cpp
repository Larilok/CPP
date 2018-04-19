#include <iostream>
#include <string>

using namespace std;
struct Node
{
    int value;
    Node *l,*r;
};

void print(Node *&Tree){
    if(Tree != NULL){
        print(Tree->l);
        cout<< Tree->value << endl;
        print(Tree->r);
    }
}

void FreeTree(Node *Branch)
{
	if (!Branch) return;
	FreeTree(Branch->l);
	FreeTree(Branch->r);
	delete Branch;
}

void addNode(int v,Node *&Tree){
    if(!Tree){
        
        Tree = new Node;
        Tree->value = v;
        Tree->l=Tree->r=NULL;
        return;
    }
    if(v < Tree->value){
        addNode(v,Tree->l);
    }
    else{
        addNode(v,Tree->r);
    }
    
}

void addNodeFT(Node *AnTree,Node *&Tree){
    if(!Tree){
        
        Tree = new Node;
        Tree->value = AnTree->value;
        Tree->l=Tree->r=NULL;
        return;
    }
    else if(AnTree->r != NULL )
    addNodeFT(AnTree->r,Tree->r);
    
}

void fillTree(Node *&Tree){
    for(int i = 0;i < 15;i++)
	{
		addNode(rand()%(200)-100,Tree);
	}
}

Node * find(Node *&Tree, int d)
{
if (Tree==NULL)
    {
    return NULL;  
    }

if (d<Tree->value)
    {
    // left
    if (Tree->l!=NULL && Tree->l->value > d)
        return find(Tree->l,d); // рекурсивный поиск влево
    else return Tree; // нашли 
    }
    else 
    {
    //right
    if(d>Tree->value){  // рекурсивный поиск вправо
        if (Tree->r!=NULL && Tree->r->value < d)
        return find(Tree->r,d);  
    else return Tree->r;    
    }
    }
}

int main(){
    Node *Tree = NULL;
    char v;int k;
    bool valid;
    cout << "Do u wanna fill array with random values? [y/n] "<<endl ;
    while( cin >> v){
        if (v=='y') {fillTree(Tree);break;}
        else if (v == 'n') {
            for(int i = 0; i < 15;i++){
                cout << "Value " <<i+1 <<" : ";
                cin >> k;
                addNode(k, Tree);
            }
            break;
        }
        else cout<<"Enter [t/f] ";
    }
    int comp;
    cout << "Enter comparer : ";
    cin >> comp;
    
    Node *Beg = find(Tree,comp);
    Node *BegTree = NULL;
    addNodeFT(Beg,BegTree);
    print(BegTree);
    FreeTree(Tree);
}