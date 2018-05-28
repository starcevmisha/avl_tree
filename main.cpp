#include <iostream>

class node
{
  public:
    int key;
    unsigned char height;
    node *left;
    node *right;

    node(int key)
    {
        this->key = key;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

unsigned char height(node *p)
{
    if (p != nullptr)
    {
        return p->height;
    }
    return 0;
}

int bfactor(node *p)
{
    return height(p->right) - height(p->left);
}

void recount_height(node *p)
{
    auto height_l = height(p->left);
    auto height_r = height(p->right);
    p->height = (height_l > height_r ? height_l : height_r) + 1;
}

node *small_right_rotate(node *p)
{
    node *q = p->left;
    p->left = q->right;
    q->right = p;
    recount_height(p);
    recount_height(q);
    return q;
}

node *small_left_rotate(node *q)
{

    node *p = q->right;
    q->right = p->left;
    p->left = q;
    recount_height(p);
    recount_height(q);
    return p;
}

node *balance(node *p)
{
    recount_height(p);
    auto b = bfactor(p);
    if (bfactor(p) == 2) //big left rotate
    {
        if (bfactor(p->right) > 0)
        {
            p->right = small_right_rotate(p->right);
        }
        return small_left_rotate(p);
    }

    if (bfactor(p) == -2) // big right rotate
    {
        if (bfactor(p->left) > 0)
        {
            p->left = small_left_rotate(p->left);
        }
        return small_right_rotate(p);
    }
    return p;
}

node* findmin(node *p)//minimal key in subtree
{
    return p->left ? findmin(p->left) : p;
}

node * removemin(node* p){
    if (p->left==nullptr){
        return p->right;
    }
    p->left = removemin(p->left);
    balance(p);
}

node *insert(node *p, int key)
{
    if (p == nullptr)
    {
        return new node(key);
    }
    if (key >= p->key)
    {
        p->right = insert(p->right, key);
    }
    else
    {
        p->left = insert(p->left, key);
    }
    return balance(p);
}

node *remove(node *p, int key)
{
    if(p == nullptr){
        return nullptr;
    }
    if (key < p->key)
    {
        p->left = remove(p->left, key);
    }
    else if (p->key < key)
    {
        p->right = remove(p->right, key);
    }
    else
    {
        node * left = p->left;
        node* right = p->right;
        delete p;

        node* min_in_right = findmin(right);
        min_in_right->right = removemin(right);
        min_in_right->left = left;
        return balance(min_in_right);
    }
}



int main(int argc, char *argv[])
{
    node *tree = new node(25);
    std::cerr << "1\n";
    tree = insert(tree, 14);
    std::cerr << "2\n";
    tree = insert(tree, 10);
    tree = insert(tree,11);
    std::cerr << "3\n";
    tree = remove(tree, 12);
    auto a = 67;
}