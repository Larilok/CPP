#include <iostream>
#include <string>
#include <vector>

#define WORK

using namespace std;
struct Node
{
    int value;
    Node *l,*r;
};


int GetHeight (Node *Tree){
    int Lheight = 0, Rheight = 0;
    if(Tree != 0){
        if (Tree->l != 0) Lheight = GetHeight(Tree->l) + 1;
        if (Tree->r != 0) Rheight = GetHeight(Tree->r) + 1;
    }
    if (Lheight > Rheight) return Lheight;
    else return Rheight;
}

void printL(Node *&Tree, int level){
    if (Tree == NULL)  {
        cout << "__," ;  return;
    }

        if (level == 0 && Tree != NULL){
            cout << Tree->value << " ";
        }
        else {
             printL(Tree->l, level-1);
             printL (Tree->r, level-1);
        }
    }


void print(Node *&Tree, int level){
    if (Tree == NULL) return;

    int height = GetHeight(Tree);
    while (height >= level) {

        printL(Tree, level);
        level++;
        cout << endl;
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
    else if(v < Tree->value){
        addNode(v,Tree->l);
    }
    else if(v > Tree->value){
        addNode(v,Tree->r);
    }
    
}



void fillTree(Node *&Tree){
    for(int i = 0;i < 10;i++)
	{
	//	addNode(rand()%(200)-100,Tree);
		addNode(rand()%100,Tree);
	}
}

Node * MinValue(Node *&Leave){
	if (Leave->l == NULL){
		return Leave;
	}
	MinValue(Leave->l);
}

void deleteNode(Node *&	Tree){
	if (Tree == NULL){
		return;
	}
	else if (Tree->l == NULL && Tree->r == NULL) {
		delete Tree;
		Tree = nullptr;
	}
	else if (Tree->l == NULL){
		Node * temp = Tree;
		Tree = Tree->r;
		delete temp;
	}
	else if (Tree->r == NULL){
		Node * temp = Tree;
		Tree = Tree->l;
		delete temp;
	}
	else {
		Node * temp = MinValue(Tree->r);
		Tree->value = temp->value;
		deleteNode(temp);
		
		
	}
}

void remove(Node *&Tree, int d) {
    if (Tree == NULL) {
        return;
    }
    else{
        if(Tree->l != NULL)  remove(Tree->l, d);
        if(Tree->r != NULL)  remove(Tree->r, d);
        if (Tree->value > d) deleteNode(Tree);
    }

}void remove2(Node *&Tree, int c) {
    if (Tree == NULL) {
        return;
    }
    else{
        if(Tree->l != NULL)  remove2(Tree->l,c);
        if(Tree->r != NULL)  remove2(Tree->r,c);
        int temp = Tree->value;
        int v = temp%10 + (temp-temp%10)/10;
        if (v > c ) deleteNode(Tree);
    }

}


int get_Node(Node *Tree,int row,int col,int nil)
{
    Node *p=Tree;
    int i,c;
    c=1;
    // начальная колонка правой части
    for (i=row;--i>0;c<<=1);
    while (row && c)
    {
        if (col<c) {
            // левая
            p=p->l;
        }
        else {
            // правая
            col=col-c;
            p=p->r;
        }
        if (p==NULL) return nil;
        c>>=1; --row;
    }
    return p->value;
}
// выводит дерево, но нужно конкретно затачивать под данные
// сейчас - вывод 0-9 и символов
void show_Tree(Node *Tree)
{
    int lvl= GetHeight(Tree);
    int z,zz;
    zz=-1; // ключ несуществующего узла
    int c=1;
    int s=1; // сколько пробелов надо вывести перед данными
    for (z=lvl;--z>=0;s<<=1);
    printf("\n");
    for (int i=0;i<=lvl;++i) {
        for (int j=0;j<c;++j) {
            int s0 = j == 0 ? s / 2 : s; // первая колонка укороченная
            for (int k=0;++k<s0;) printf(" ");
            z=get_Node(Tree,i,j,zz);
            if (z==zz) printf(" ");
                else printf("%d",z);
        }
        printf("\n");
        s>>=1;
        c<<=1;
    }
}
int main(){
    Node *Tree = NULL;
    char v;
    int k;
    fillTree(Tree);
#ifdef WORK
//   cout << "Do u wanna fill array with random values(r) or manually? [r/m] "<<endl ;
//    while( cin >> v){
//        if (v=='r') {fillTree(Tree);break;}
//        else if (v == 'm') {
//            cout << "How many elements you wanna add ?"<< endl;
//            int am = 0;
//            cin >> am;
//            for(int i = 0; i < am;i++){
//                cout << "Value " <<i+1 <<" : ";
//                cin >> k;
//                addNode(k, Tree);
//            }
//            break;
//        }
//        else cout<<"Enter [r/m] ";
//    }
//    int comp;
//    cout << "Enter first comparer : ";
//    cin >> comp;
//    Node *Tree2 = NULL;
//
//    fillTree(Tree2);
//    cout << "------------THE FIRST TASK-------------" << endl;
//    show_Tree(Tree);
//   remove(Tree, comp);
//
//    cout << "------------AFTER REMOVING-------------" << endl;
//    show_Tree(Tree);

    int c;
    cout << endl << "------------THE SECOND TASK-------------" << endl << endl;
    cout << "Enter second comparer [0..18] : ";
//    while(cin >> c){
//        if (c > 19) cout << "The sum cannot be greater than 18" << endl;
//        else break;
//    }
    c=7;

    Node *Tree2 = NULL;
//
    fillTree(Tree2);
    show_Tree(Tree2);
    remove2(Tree2,c);

    cout << "------------AFTER REMOVING-------------" << endl;
    show_Tree(Tree2);

   cout << "The end" << endl;
   FreeTree(Tree);
#endif
 return 0;
}
