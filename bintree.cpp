//using stack and queue
#include<iostream>
using namespace std;

struct btree
{
    int data;
    btree *left;
    btree *right;
};

class stack
{
    public:
        btree *st[20];
        int data,top;
    public:
        stack()
        {
            top = -1;
        }
        int isEmpty()
        {
            if(top==-1)
                return 1;
            else
                return 0;
        }
        void push(btree *nwnode)
        {
            top++;
            st[top] = nwnode;
        }
        btree *pop()
        {
            btree *nwnode;
            nwnode = st[top];
            top--;
            return(nwnode);
        }
};

class queue
{
    btree *que[20];
    int data,rear,front;
    public:
        queue()
        {
            rear = front = -1;
        }
        int isEmpty()
        {
            if(rear==front)
                return 1;
            else
                return 0;
        }
        int isFull()
        {
            if(rear==20)
                return 1;
            else
                return 0;
        }
        void add(btree *nwnode)
        {
            if(isFull())
                cout<<"\nQueue Overflow";
            else
            {
                rear++;
                que[rear] = nwnode;
            }
        }
        btree *del()
        {
            btree *nwnode;
            if(isEmpty())
            {
                cout<<"\nQueue is Empty";
            }
            else
            {
                front++;
                nwnode = que[front];
                return(nwnode);
            }
        }
};

class tree
{
    public:
        int z=1;
        btree *root = NULL;
        btree *clone = NULL;
        btree* create(btree *);
        void insert();
        void preorder(btree *);
        void inorder(btree *);
        void postorder(btree *);
        void bfs(btree *);
        void dfs(btree *);
        void display_traversals();
        btree* treecopy(btree *);
        void leaf_nodes(btree *);        
};

void tree::insert()
{
    int n;
    cout<<"\nEnter number of nodes : ";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        root = create(root);
    }
}

btree* tree::create(btree *root)
{
    int data;
    char ch;
    btree *temp = new btree;
    if(root==NULL)
    {
        root = new btree;
        cout<<"\nYou are at Level 0";
        cout<<"\nEnter the value of root : ";
        cin>>data;
        root->data=data;
        root->left = root->right = NULL;
    }
    else
    { 
        temp = root;
        cout<<"\nYou are at Level "<<z;
        cout<<"\nWhere do you want to insert (l/r) : ";
        cin>>ch;
        if(ch=='l')
        {
            if(temp->left!=NULL)
            {
                z++;
                create(temp->left);
                z--;
            }
            else
            {
                cout<<"\nEnter the value of node : ";
                cin>>data;
                temp->left = new btree;
                temp = temp->left;
                temp->data=data;
                temp->left=temp->right=NULL;
            }
        }
        else if(ch=='r')
        {
            if(temp->right!=NULL)
            {
                z++;
                create(temp->right);
                z--;
            }
            else
            {
                cout<<"\nEnter the value of node : ";
                cin>>data;
                temp->right = new btree;
                temp = temp->right;
                temp->data=data;
                temp->left=temp->right=NULL;   
            }
        }
        return root;
    }
}

void tree::preorder(btree *nwnode)
{
    if(nwnode!=NULL)
    {
        cout<<nwnode->data<<" ";
        preorder(nwnode->left);
        preorder(nwnode->right);
    }
}

void tree::inorder(btree *nwnode)
{
    if(nwnode!=NULL)
    {
        inorder(nwnode->left);
        cout<<nwnode->data<<" ";
        inorder(nwnode->right);
    }
}

void tree::postorder(btree *nwnode)
{
    if(nwnode!=NULL)
    {
        postorder(nwnode->left);
        postorder(nwnode->right);
        cout<<nwnode->data<<" ";
    }
}



void tree::display_traversals()
{
    cout<<"\n--------------------------------------------------------------------";
    cout<<"\nPreorder Traversal : ";
    preorder(root);
    cout<<"\n";
    cout<<"\nInorder Traversal : ";
    inorder(root);
    cout<<"\n";
    cout<<"\nPostorder Traversal : ";
    postorder(root);
    cout<<"\n";
}

btree* tree::treecopy(btree *nwnode)
{
    stack S,S1;
    btree *temp;
    btree *temp1;
    temp = root;
    clone = new btree;
    temp1  = clone;
    temp1->left = temp1->right = NULL;
    while(1)
    {
        temp1->data = temp->data;
        if(temp->right!=NULL)
        {
            S.push(temp->right);
            temp1->right = new btree;
            temp1->right->left = temp1->right->right = NULL;
            S1.push(temp1->right);
        }
        if(temp->left!=NULL)
        {
            S.push(temp->left);
            temp1->left = new btree;
            temp1->left->left = temp1->left->right = NULL;
            S1.push(temp1->left);
        }
        if(S.isEmpty())
            break;
        temp = S.pop();
        temp1 = S1.pop();
    }
    cout<<"\nCopied Successfully";
    return clone;
}

void tree::leaf_nodes(btree *nwnode)
{
    stack S;
    cout<<"\nLeaf nodes : ";
    while(1)
    {
        if(nwnode->left==NULL && nwnode->right==NULL)
            cout<<nwnode->data<<" ";
        if(nwnode->right!=NULL)
            S.push(nwnode->right);
        if(nwnode->left!=NULL)
            S.push(nwnode->left);
        if(S.isEmpty())
            break;
        nwnode = S.pop();
    }
}

int main()
{
    tree obj;
    btree *root1;
    int choice,ch;
    cout<<"\n1. Create a Binary Tree \n2. Exit"<<endl;
    cout<<"\nEnter your choice : ";
    cin>>choice;
    cout<<"\n--------------------------------------------------------------------";
    if(choice==1)
    {
        obj.insert();
        cout<<"\nTree Created Successfully"<<endl;
        while(1)
        {
            cout<<"\n--------------------------------------------------------------------";
            cout<<"\n1. Insert node \n2. Display Traversals \n3. Copy of a Tree \n4. Display Leaf nodes \n5. Exit";
            cout<<"\nEnter your choice : ";
            cin>>ch;
            cout<<"\n--------------------------------------------------------------------";
            if(ch==1)
            {
                obj.insert();
                cout<<"\nNode Inserted Successfully";
            }
            else if(ch==2)
                obj.display_traversals();
            else if(ch==3)
            {
                root1 = obj.treecopy(obj.root);
                cout<<"\nCopy of the tree is : ";
                obj.preorder(root1);
            }
            else if(ch==4)
                obj.leaf_nodes(obj.root);
            else
            {
                cout<<"\nProgram Exited";
                break;
            }
        }
    }
    else
    {
        cout<<"\nProgram exited";
    }
}