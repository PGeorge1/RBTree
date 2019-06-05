/* red-black tree */

#include <iostream>
#include <fstream>
#include <set>

template<typename T, typename compLT = std::less<T>>
class RBTree
{
public:
    /* Red-Black tree */
    typedef enum { BLACK, RED } nodeColor;

    class Node
    {
    public:
        Node ()
        {
        }

        Node (Node *left, Node *right, Node *parent, nodeColor color, T data) :
            left (left), right (right), parent (parent), color (color), data (data)
        {
        }

        Node *left = nullptr;         /* left child */
        Node *right = nullptr;        /* right child */
        Node *parent = nullptr;       /* parent */
        nodeColor color = BLACK;      /* node color (BLACK, RED) */
        T data;                       /* data stored in node */
    };

    RBTree ()
    {
      NIL = new Node ();
      NIL->color = BLACK;
      root = NIL;
    }

    void rotateLeft(Node *x)
    {

       /**************************
        *  rotate node x to left *
        **************************/
    }

    void rotateRight(Node *x)
    {
       /****************************
        *  rotate node x to right  *
        ****************************/
    }

    void insertFixup(Node *x) 
    {

       /*************************************
        *  maintain Red-Black tree balance  *
        *  after inserting node x           *
        *************************************/

    }

    Node *insertNode(T data)
    {
        Node *current, *parent, *x;

       /***********************************************
        *  allocate node for data and insert in tree  *
        ***********************************************/

        /* find where node belongs */
        current = root;
        parent = 0;
        while (current != NIL)
        {
            if (data == current->data)
                return (current);

            parent = current;
            current = comp(data, current->data) ? current->left : current->right;
        }

        /* setup new node */
        x = new Node (NIL, NIL, parent, RED, data);

        /* insert node in tree */
        if(parent)
        {
            if(comp(data, parent->data))
                parent->left = x;
            else
                parent->right = x;
        }
        else
        {
            root = x;
        }

        insertFixup(x);
        return x;
    }

    Node *findNode(T data)
    {
       /*******************************
        *  find node containing data  *
        *******************************/

        Node *current = root;
        while(current != NIL)
            if(data == current->data)
                return current;
            else
                current = comp (data, current->data) ?
                    current->left : current->right;
        return nullptr;
    }

    void free(Node *node)
    {
        if (node == NIL)
            return;
        free (node->left);
        free (node->right);
        delete node;
    }

    ~RBTree ()
    {
        free (root);
        delete NIL;
    }


    void save_tree_in_graphviz_format (std::string filename)
    {
      std::ofstream os (filename);
      os << "digraph {";
      std::string vertices;
      std::string edges;
      save_tree_in_graphviz_format_call (root, vertices, edges);
      os << vertices << edges << "}";
    }

private:

    void save_tree_in_graphviz_format_call (Node *node, std::string &vertices, std::string &edges)
    {
        if (node == NIL)
            return;

        if (node->color == RED)
        {
            vertices += " " + std::to_string( node->data) + "[color=red];";
        }

        if (node->parent)
            edges += std::to_string( node->parent->data) + "->" + std::to_string( node->data) + ";";


        save_tree_in_graphviz_format_call (node->left, vertices, edges);
        save_tree_in_graphviz_format_call (node->right, vertices, edges);

    }

    Node *NIL;                /* NIL element of the tree */
    Node *root;               /* root of Red-Black tree */
    compLT comp;
};

