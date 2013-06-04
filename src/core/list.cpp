#include "include/core/list.h"
#include "include/core/types.h"

/*
    list types:
    false - Braun Tree
    true - 2/3 Finger Tree
*/




namespace panopticon
{

//======================================
// General / Language Callbacks
//======================================

int test_num = 0;
void complexity_test()
{
    out() << "Num steps: " << test_num << std::endl;
}

bool convert_array_to_list(object& result, object& array)
{
    result = mem_alloc(LIST);
    for(Array::reverse_iterator it = array.data.array->rbegin();it!=array.data.array->rend();++it)
    {
#ifdef TWO_THREE_TREE
        result.data.list =  two_three_list_cons(result.data.list,*it);
#elif BRAUN_TREE
        result.data.list =  braun_cons(*it,result.data.list);
#endif
    }
    //    test_num = 0;
}

bool print_list(const object &A, int arrayNum)
{
    if(arrayNum!=0)
    {
        out() << " ";
    }
    out() << "L[";
    //    test_num = 0;
#ifdef TWO_THREE_TREE
    two_three_print(A.data.list);
#else
    print_braun_tree(A.data.list);
#endif
    out() << " ]";
    if(arrayNum==0)
    {
        out() << std::endl;
    }
    test_num = 0;
}

bool prepend(object& result_A, const object& B, const object& container_C)
{
    if(container_C.type != LIST)
    {
#ifdef TWO_THREE_TREE
        result_A = mem_alloc(LIST);
        List* list = two_three_list_cons(result_A.data.list,container_C);
        list = two_three_list_cons(list,B);
        result_A.data.list = list;
#else
        result_A = mem_alloc(LIST);
        List* list = braun_cons(container_C,result_A.data.list);
        list = braun_cons(B,list);
        result_A.data.list = list;
#endif
        return true;
    }
#ifdef TWO_THREE_TREE
    result_A = mem_alloc(LIST);
    List* list = two_three_list_cons(container_C.data.list,B);
    result_A.data.list = list;
#else
    test_num = 0;
    result_A = mem_alloc(LIST);
    List* list = braun_cons(B,container_C.data.list);
    result_A.data.list = list;
    complexity_test();
#endif
    return true;
}

bool append(object& result_A, const object& container_B, const object& object_C)
{
    if(container_B.type != LIST)
    {
#ifdef TWO_THREE_TREE
        result_A = mem_alloc(LIST);
        List* list = two_three_list_cons(result_A.data.list,object_C);
        list = two_three_list_cons(list,container_B);
        result_A.data.list = list;
#else
        result_A = mem_alloc(LIST);
        List* list = braun_cons(container_B,result_A.data.list);
        list = braun_cons(object_C,list);
        result_A.data.list = list;
#endif
        return true;
    }
#ifdef TWO_THREE_TREE
    result_A = mem_alloc(LIST);
    List* list = two_three_list_append(container_B.data.list,object_C);
    result_A.data.list = list;
#else
    test_num = 0;
    result_A = mem_alloc(LIST);
    List* list = braun_update(container_B.data.list,braun_length(container_B.data.list),object_C);
    result_A.data.list = list;
    complexity_test();
#endif
    return true;
}

bool concat(object& A, const object& B, const object& C)
{
#ifdef TWO_THREE_TREE
    std::stringstream ss;
    switch(B.type)
    {
    case BOOL:
        switch(C.type)
        {
        case BOOL:
        case NUMBER:
            return prepend(A,B,C);
        case STRING:
            A = mem_alloc(STRING);

            if(B.data.boolean)
            {
                A.data.string->append("true");
            }

            else
            {
                A.data.string->append("false");
            }

            A.data.string->append(*C.data.string);
            break;
        case LIST:
            A = mem_alloc(LIST);
            A.data.list = two_three_list_cons(C.data.list,B);
            break;
        }
        break;
    case NUMBER:
        switch(C.type)
        {
        case BOOL:
        case NUMBER:
            return prepend(A,B,C);
        case STRING:
            ss << B.data.number;
            A.data.string->append(ss.str());
            A.data.string->append(*C.data.string);
            break;
        case LIST:
            A = mem_alloc(LIST);
            A.data.list = two_three_list_cons(C.data.list,B);
            break;
        }
        break;
    case STRING:
        switch(C.type)
        {
        case BOOL:
            if(B.data.boolean)
            {
                A.data.string->append("true");
            }
            else
            {
                A.data.string->append("false");
            }
            break;
        case NUMBER:
            ss << C.data.number;
            A.data.string->append(ss.str());
            break;
        case STRING:
            A.data.string->append(*C.data.string);
            break;
        case LIST:
            A = mem_alloc(LIST);
            A.data.list = two_three_list_cons(C.data.list,B);
            break;
        }
        break;
    case LIST:
        switch(C.type)
        {
        case NUMBER:
        case STRING:
        case BOOL:
            A = mem_alloc(LIST);
            A.data.list = two_three_list_append(B.data.list,C);
            break;
        case LIST:
            A = mem_alloc(LIST);
            test_num = 0;
            A.data.list = two_three_list_concatenation(B.data.list,C.data.list);
            complexity_test();
            break;
        }
        break;
    }
#else
    std::stringstream ss;
    switch(B.type)
    {
    case BOOL:
        switch(C.type)
        {
        case BOOL:
        case NUMBER:
            return prepend(A,B,C);
        case STRING:
            A = mem_alloc(STRING);

            if(B.data.boolean)
            {
                A.data.string->append("true");
            }

            else
            {
                A.data.string->append("false");
            }

            A.data.string->append(*C.data.string);
            break;
        case LIST:
            A = mem_alloc(LIST);
            List* list = braun_cons(B,C.data.list);
            A.data.list = list;
            break;
        }
        break;
    case NUMBER:
        switch(C.type)
        {
        case BOOL:
        case NUMBER:
            return prepend(A,B,C);
        case STRING:
            ss << B.data.number;
            A.data.string->append(ss.str());
            A.data.string->append(*C.data.string);
            break;
        case LIST:
            A = mem_alloc(LIST);
            List* list = braun_cons(B,C.data.list);
            A.data.list = list;
            break;
        }
        break;
    case STRING:
        switch(C.type)
        {
        case BOOL:
            if(B.data.boolean)
            {
                A.data.string->append("true");
            }
            else
            {
                A.data.string->append("false");
            }
            break;
        case NUMBER:
            ss << C.data.number;
            A.data.string->append(ss.str());
            break;
        case STRING:
            A.data.string->append(*C.data.string);
            break;
        case LIST:
            A = mem_alloc(LIST);
            List* list = braun_cons(B,C.data.list);
            A.data.list = list;
            break;
        }
        break;
    case LIST:
        List* list;
        switch(C.type)
        {
        case NUMBER:
            A = mem_alloc(LIST);
            list = braun_update(B.data.list,braun_length(B.data.list),C);
            A.data.list = list;
            break;
        case STRING:
            A = mem_alloc(LIST);
            list = braun_update(B.data.list,braun_length(B.data.list),C);
            A.data.list = list;
            break;
        case BOOL:
            A = mem_alloc(LIST);
            list = braun_update(B.data.list,braun_length(B.data.list),C);
            A.data.list = list;
            break;
        case LIST:
            A = mem_alloc(LIST);

            A.data.list = list;
            break;
        }
        break;
    }
#endif
}

//======================================
//Braun_Tree Implementation
//======================================
#ifdef BRAUN_TREE
//Braun-tree implentation of List

inline List* create_braun_node(List* l,const object& x, List* r)
{
    test_num++;
    List* node = new List();
    node->data = x;
    node->left = l;
    node->right = r;
    return node;
}

//traverse tree
int braun_rows(List* list, int row=0)
{
    if(list == 0)
    {
        return row;
    }
    return braun_rows(list->left,row+1);
}

inline bool braun_null(List* list)
{
    if(list==0)
    {
        return true;
    }
    return false;
}

List* braun_cons(const object &x, List* list)
{
    //    test_num++;
    if(braun_null(list))
    {
        return create_braun_node(0, x, 0);
    }
    return create_braun_node(braun_cons(list->data,list->right),x,list->left);
}

inline List* braun_join(List* list1,List* list2)
{
    //    test_num++;
    if(list1==0)
    {
        return 0;
    }
    return create_braun_node(list2,list1->data,braun_join(list1->left,list1->right));
}

List* braun_tail(List* list)
{
    //    test_num++;
    return braun_join(list->left,list->right);
}

//O(log(n))
List* braun_update(List* list, int index,const object& y)
{
    //    test_num++;
    if(index==0)
    {
        if(list==0)
        {
            return create_braun_node(0,y,0);
        }
        return create_braun_node(list->left,y,list->right);
    }
    if(index%2==0)
    {
        return create_braun_node(list->left,list->data,braun_update(list->right,((index)/2)-1,y));
    }
    return create_braun_node(braun_update(list->left,(index-1)/2,y),list->data,list->right);
}

inline object braun_head(List* list)
{
    //    test_num++;
    return list->data;
}

/*
lookup (Node l x r) 0 = x
lookup (Node l x r) n
    | n `mod` 2 == 0 = lookup r ((n `div` 2)-1)
    | otherwise
    = lookup l ((n-1) `div` 2)
*/

inline object braun_lookup(List* list, int index)
{
    //    test_num++;
    if(index==0)
    {
        return list->data;
    }
    if(index%2==0)
    {
        return braun_lookup(list->right,((index)/2)-1);
    }
    return braun_lookup(list->left,(index-1)/2);
}

inline int braun_diff(List* list, int n)
{
    //    test_num++;
    if(list==0&&n==0)
    {
        return 0;
    }
    if(n==0)
    {
        return 1;
    }
    if(n%2 == 1)
    {
        //if odd
        return braun_diff(list->left, (((float)(n - 1)) / 2.0));
    }
    else
    {
        //if even
        return braun_diff( list->right, (((float)(n - 2)) / 2.0));
    }
}

int braun_length(List* list)
{
    //    test_num++;
    if(list==0)
    {
        return 0;
    }
    int right_size = braun_length(list->right);
    return 1 + 2 * right_size + braun_diff(list->left,right_size);
}

bool print_braun_tree(List* list)
{
    if(braun_null(list))
    {
        return true;
    }
    print_object_in_array(braun_head(list),1);
    return print_braun_tree(braun_tail(list));
}
#endif

//======================================
//2-3 Finger Tree Implementation
//======================================

#ifdef TWO_THREE_TREE

inline int two_three_node_shallow_element_count(TwoThreeFingerTree* a)
{
    if(a->type == FT_ELEMENT)
    {
        return 1;
    }
    if(a->type == FT_NODE2)
    {
        return a->node.node2->element_count;
    }
    if(a->type == FT_NODE3)
    {
        return a->node.node3->element_count;
    }
}

inline int two_three_node_deep_element_count(TwoThreeFingerTree* a)
{
    int count = 0;
    if(a->type == FT_ELEMENT)
    {
        count =  1;
    }
    else if(a->type == FT_SINGLE)
    {
        count += a->node.single->element_count;
    }
    else if(a->type == FT_NODE2)
    {
        count += two_three_node_shallow_element_count(a->node.node2->a);
        count += two_three_node_shallow_element_count(a->node.node2->b);
        a->node.node2->element_count = count;
    }
    else if(a->type == FT_NODE3)
    {
        count += two_three_node_shallow_element_count(a->node.node3->a);
        count += two_three_node_shallow_element_count(a->node.node3->b);
        count += two_three_node_shallow_element_count(a->node.node3->c);
        a->node.node3->element_count = count;
    }

    return count;
}

inline int two_three_digit_element_count(Digit* a)
{
    int count = 0;
    switch(a->size)
    {
    case 1:
        count = two_three_node_shallow_element_count(a->one);
        break;
    case 2:
        count = two_three_node_shallow_element_count(a->one) + two_three_node_shallow_element_count(a->two);
        break;
    case 3:
        count = two_three_node_shallow_element_count(a->one) + two_three_node_shallow_element_count(a->two) + two_three_node_shallow_element_count(a->three);
        break;
    case 4:
        count = two_three_node_shallow_element_count(a->one) + two_three_node_shallow_element_count(a->two) + two_three_node_shallow_element_count(a->three) + two_three_node_shallow_element_count(a->four);
        break;
    }
    a->element_count = count;
    return count;
}

int two_three_length(TwoThreeFingerTree* a)
{
    if(a->type == FT_ELEMENT)
    {
        return 1;
    }
    else if(a->type == FT_SINGLE)
    {
        return a->node.single->element_count;
    }
    else if(a->type == FT_DEEP)
    {
        return a->node.deep->element_count;
    }
}

int two_three_element_count(TwoThreeFingerTree* a)
{
    int count = 0;

    if(a->type == FT_ELEMENT)
    {
        count = 1;
    }
    else if(a->type == FT_SINGLE)
    {
        count = two_three_node_shallow_element_count(a->node.single->a);
        a->node.single->element_count = count;
    }
    else if(a->type == FT_DEEP)
    {
        int l = two_three_digit_element_count(a->node.deep->left);
        int r = two_three_digit_element_count(a->node.deep->right);
        int c = 0;

        if(a->node.deep->center == 0)
        {
            c = 0;
        }
        else if(a->node.deep->center->type == FT_ELEMENT)
        {
            c = 1;
        }
        else if(a->node.deep->center->type == FT_SINGLE)
        {
            c = a->node.deep->center->node.single->element_count;
        }
        else
        {
            c = a->node.deep->center->node.deep->element_count;
        }

        count = a->node.deep->element_count = l + r + c;
        a->node.deep->element_count = count;
    }

    return count;
}

inline TwoThreeFingerTree* two_three_single(TwoThreeFingerTree* a)
{
    TwoThreeFingerTree* single = new TwoThreeFingerTree();
    single->type = FT_SINGLE;
    single->node.single = new Single;
    single->node.single->a = a;
    two_three_element_count(single);
    return single;
}

inline Digit* construct_digit()
{
    Digit* digit = new Digit;
    digit->one = 0;
    digit->two = 0;
    digit->three = 0;
    digit->four = 0;
    digit->size = 0;
}

inline TwoThreeFingerTree* two_three_deep()
{
    TwoThreeFingerTree* deep = new TwoThreeFingerTree();
    deep->type = FT_DEEP;
    deep->node.deep = new Deep;
    deep->node.deep->left = construct_digit();
    deep->node.deep->center = 0;
    deep->node.deep->right = construct_digit();
    return deep;
}

//Left-most finger, so recurse left-word.
inline TwoThreeFingerTree* two_three_element(const object& a)
{
    TwoThreeFingerTree* tree = new TwoThreeFingerTree;
    tree->node.a = new object;
    *tree->node.a = a;
    tree->type = FT_ELEMENT;
    return tree;
}

inline TwoThreeFingerTree* two_three_node3(
        TwoThreeFingerTree* a,
        TwoThreeFingerTree* b,
        TwoThreeFingerTree* c
        )
{
    TwoThreeFingerTree* tree = new TwoThreeFingerTree;
    tree->type = FT_NODE3;
    tree->node.node3 = new Node3;
    tree->node.node3->a = a;
    tree->node.node3->b = b;
    tree->node.node3->c = c;
    two_three_node_deep_element_count(tree);
    return tree;
}

inline TwoThreeFingerTree* two_three_node2(
        TwoThreeFingerTree* a,
        TwoThreeFingerTree* b
        )
{
    TwoThreeFingerTree* tree = new TwoThreeFingerTree;
    tree->type = FT_NODE2;
    tree->node.node2 = new Node2;
    tree->node.node2->a = a;
    tree->node.node2->b = b;
    two_three_node_deep_element_count(tree);
    return tree;
}

inline TwoThreeFingerTree* two_three_cons(TwoThreeFingerTree* finger_tree, TwoThreeFingerTree* a)
{
    test_num++;
    if(finger_tree == 0)
    {
        return two_three_single(a);
    }
    if(finger_tree->type == FT_SINGLE)
    {
        TwoThreeFingerTree* deep = two_three_deep();
        deep->node.deep->left->one = a;
        deep->node.deep->left->size = 1;
        deep->node.deep->right->one = finger_tree->node.single->a;
        deep->node.deep->right->size = 1;
        deep->node.deep->center = 0;
        two_three_element_count(deep);
        return deep;
    }
    else if(finger_tree->type == FT_DEEP)
    {
        TwoThreeFingerTree* deep = two_three_deep();
        deep->node.deep->right = finger_tree->node.deep->right;
        //Digits with 4 items are "dangerous" and should be split up when it hits 5
        switch(finger_tree->node.deep->left->size)
        {
        case 1:
            deep->node.deep->left->two = finger_tree->node.deep->left->one;
            deep->node.deep->left->one = a;
            deep->node.deep->left->size = 2;
            deep->node.deep->center = finger_tree->node.deep->center;
            break;
        case 2:
            deep->node.deep->left->three = finger_tree->node.deep->left->two;
            deep->node.deep->left->two = finger_tree->node.deep->left->one;
            deep->node.deep->left->one = a;
            deep->node.deep->left->size = 3;
            deep->node.deep->center = finger_tree->node.deep->center;
            break;
        case 3:
            deep->node.deep->left->four = finger_tree->node.deep->left->three;
            deep->node.deep->left->three = finger_tree->node.deep->left->two;
            deep->node.deep->left->two = finger_tree->node.deep->left->one;
            deep->node.deep->left->one = a;
            deep->node.deep->left->size = 4;
            deep->node.deep->center = finger_tree->node.deep->center;
            break;
        case 4:
            //Shift last 3 into new Node3, then push it down the middle tree.
            TwoThreeFingerTree* node3 = two_three_node3(
                        finger_tree->node.deep->left->two,
                        finger_tree->node.deep->left->three,
                        finger_tree->node.deep->left->four
                        );
            //            two_three_element_count(node3);
            deep->node.deep->center = two_three_cons(finger_tree->node.deep->center,node3);
            //Append to the beginning and shift one to two.
            deep->node.deep->left->two = finger_tree->node.deep->left->one;
            deep->node.deep->left->one = a;
            //Zero out digits three and four.
            deep->node.deep->left->size = 2;
            break;
        }
        two_three_element_count(deep);
        return deep;
    }
    else
    {
        out() << "Error: Malformed list call." << std::endl;
        correct_parsing = false;
        return 0;
    }
}

inline TwoThreeFingerTree* two_three_append(TwoThreeFingerTree* finger_tree, TwoThreeFingerTree* a)
{
    test_num++;
    if(finger_tree == 0)
    {
        return two_three_single(a);
    }
    else if(finger_tree->type == FT_SINGLE)
    {
        TwoThreeFingerTree* deep = two_three_deep();
        deep->node.deep->left->one = finger_tree->node.single->a;
        deep->node.deep->left->size = 1;
        deep->node.deep->right->one = a;
        deep->node.deep->right->size = 1;
        deep->node.deep->center = 0;
        two_three_element_count(deep);
        return deep;
    }
    else if(finger_tree->type == FT_DEEP)
    {
        TwoThreeFingerTree* deep = two_three_deep();
        deep->node.deep->left = finger_tree->node.deep->left;
        deep->node.deep->center = finger_tree->node.deep->center;
        //Digits with 4 items are "dangerous" and should be split up
        switch(finger_tree->node.deep->right->size)
        {
        case 1:
            deep->node.deep->right->one = finger_tree->node.deep->right->one;
            deep->node.deep->right->two = a;
            deep->node.deep->right->size = 2;
            break;
        case 2:
            deep->node.deep->right->one = finger_tree->node.deep->right->one;
            deep->node.deep->right->two = finger_tree->node.deep->right->two;
            deep->node.deep->right->three = a;
            deep->node.deep->right->size = 3;
            break;
        case 3:
            deep->node.deep->right->one = finger_tree->node.deep->right->one;
            deep->node.deep->right->two = finger_tree->node.deep->right->two;
            deep->node.deep->right->three = finger_tree->node.deep->right->three;
            deep->node.deep->right->four = a;
            deep->node.deep->right->size = 4;
            break;
        case 4:
            //Shift last 3 into new Node3, then push it down the middle tree.
            TwoThreeFingerTree* node3 = two_three_node3(
                        finger_tree->node.deep->right->one,
                        finger_tree->node.deep->right->two,
                        finger_tree->node.deep->right->three
                        );
            deep->node.deep->center = two_three_cons(finger_tree->node.deep->center,node3);
            //Append to the beginning and shift one to two.
            deep->node.deep->right->one = finger_tree->node.deep->right->four;
            deep->node.deep->right->two = a;
            //Zero out digits three and four.
            deep->node.deep->right->size = 2;
            break;
        }
        two_three_element_count(deep);
        return deep;
    }
    else
    {
        out() << "Error: Malformed list call." << std::endl;
        correct_parsing = false;
        return 0;
    }
}

inline TwoThreeFingerTree* two_three_head(TwoThreeFingerTree* finger_tree)
{
    if(finger_tree == 0)
    {
        out() << "Error: Attempted to call head on an empty list." << std::endl;
        correct_parsing = false;
        return 0;
    }
    else if(finger_tree->type == FT_SINGLE)
    {
        return finger_tree->node.single->a;
    }
    else if(finger_tree->type == FT_DEEP)
    {
        return finger_tree->node.deep->left->one;
    }
    else
    {
        out() << "Error: Malformed list call." << std::endl;
        correct_parsing = false;
        return 0;
    }
}

inline TwoThreeFingerTree* two_three_last(TwoThreeFingerTree* finger_tree)
{
    if(finger_tree == 0)
    {
        out() << "Error: Attempted to call head on an empty list." << std::endl;
        correct_parsing = false;
        return 0;
    }
    else if(finger_tree->type == FT_SINGLE)
    {
        return finger_tree->node.single->a;
    }
    else if(finger_tree->type == FT_DEEP)
    {
        switch(finger_tree->node.deep->right->size)
        {
        case 0:
            switch(finger_tree->node.deep->right->size)
            {
            case 2:
                return finger_tree->node.deep->left->two;
            case 3:
                return finger_tree->node.deep->left->three;
            case 4:
                return finger_tree->node.deep->left->four;
            }
        case 1:
            return finger_tree->node.deep->right->one;
        case 2:
            return finger_tree->node.deep->right->two;
        case 3:
            return finger_tree->node.deep->right->three;
        case 4:
            return finger_tree->node.deep->right->four;
        }
    }
    else
    {
        out() << "Error: Malformed list call." << std::endl;
        correct_parsing = false;
        return 0;
    }
}

inline TwoThreeFingerTree* tree_of_digits(Digit* digit)
{
    if(digit->size == 0)
    {
        return 0;
    }
    else if(digit->size == 1)
    {
        return two_three_single(digit->one);
    }
    else if(digit->size == 2 || digit->size == 3 || digit->size == 4)
    {
        TwoThreeFingerTree* deep = new TwoThreeFingerTree();
        deep->type = FT_DEEP;
        deep->node.deep = new Deep;
        deep->node.deep->left = digit;
        deep->node.deep->center = 0;
        deep->node.deep->right = construct_digit();

        switch(digit->size)
        {
        case 2:
            deep->node.deep->right->one = deep->node.deep->left->two;
            deep->node.deep->right->size = 1;
            deep->node.deep->left->two = 0;
            deep->node.deep->left->size = 1;
            break;
        case 3:
            deep->node.deep->right->one = deep->node.deep->left->three;
            deep->node.deep->right->size = 1;
            deep->node.deep->left->three = 0;
            deep->node.deep->left->size = 2;
            break;
        case 4:
            deep->node.deep->right->one = deep->node.deep->left->four;
            deep->node.deep->right->size = 1;
            deep->node.deep->left->four = 0;
            deep->node.deep->left->size = 3;
            break;
        }

        two_three_element_count(deep);
        return deep;
    }
}

inline Digit* node_to_digit(TwoThreeFingerTree* tree)
{
    Digit* digit = construct_digit();
    if(tree->type == FT_NODE2)
    {
        digit->size = 2;
        digit->one = tree->node.node2->a;
        digit->two = tree->node.node2->b;
        return digit;
    }
    else if(tree->type == FT_NODE3)
    {
        digit->size = 3;
        digit->one = tree->node.node3->a;
        digit->two = tree->node.node3->b;
        digit->three = tree->node.node3->c;
        return digit;
    }
    else
    {
        out() << "Error: malformed list operation." << std::endl;
        correct_parsing = false;
        return 0;
    }
}

inline TwoThreeFingerTree* two_three_tail(TwoThreeFingerTree* finger_tree)
{
    if(finger_tree == 0)
    {
        out() << "Error: Attempted to call tail on an empty list." << std::endl;
        return 0;
    }
    else if(finger_tree->type == FT_SINGLE)
    {
        return 0;
    }
    else if(finger_tree->type == FT_DEEP)
    {
        TwoThreeFingerTree* deep;
        switch(finger_tree->node.deep->left->size)
        {
        case 1:
            if(finger_tree->node.deep->center == 0)
            {
                return tree_of_digits(finger_tree->node.deep->right);
            }
            else
            {
                deep = two_three_deep();
                deep->node.deep->left = node_to_digit(two_three_head(finger_tree->node.deep->center));
                deep->node.deep->center = two_three_tail(finger_tree->node.deep->center);
                deep->node.deep->right = finger_tree->node.deep->right;
                two_three_element_count(deep);
                return deep;
            }
        case 2:
            deep = two_three_deep();
            deep->node.deep->center = finger_tree->node.deep->center;
            deep->node.deep->right = finger_tree->node.deep->right;
            deep->node.deep->left->one = finger_tree->node.deep->left->two;
            deep->node.deep->left->size = 1;
            deep->node.deep->left->two = 0;
            deep->node.deep->left->three = 0;
            deep->node.deep->left->four = 0;
            two_three_element_count(deep);
            return deep;
        case 3:
            deep = two_three_deep();
            deep->node.deep->center = finger_tree->node.deep->center;
            deep->node.deep->right = finger_tree->node.deep->right;
            deep->node.deep->left->one = finger_tree->node.deep->left->two;
            deep->node.deep->left->two = finger_tree->node.deep->left->three;
            deep->node.deep->left->size = 2;
            deep->node.deep->left->three = 0;
            deep->node.deep->left->four = 0;
            two_three_element_count(deep);
            return deep;
        case 4:
            deep = two_three_deep();
            deep->node.deep->center = finger_tree->node.deep->center;
            deep->node.deep->right = finger_tree->node.deep->right;
            deep->node.deep->left->one = finger_tree->node.deep->left->two;
            deep->node.deep->left->two = finger_tree->node.deep->left->three;
            deep->node.deep->left->three = finger_tree->node.deep->left->four;
            deep->node.deep->left->size = 3;
            deep->node.deep->left->four = 0;
            two_three_element_count(deep);
            return deep;
        }
    }
    else
    {
        out() << "Error: Malformed list call." << std::endl;
        correct_parsing = false;
        return 0;
    }
}

TwoThreeFingerTree* two_three_init(TwoThreeFingerTree* finger_tree)
{
    if(finger_tree == 0)
    {
        out() << "Error: Attempted to call tail on an empty list." << std::endl;
        return 0;
    }
    else if(finger_tree->type == FT_SINGLE)
    {
        return 0;
    }
    else if(finger_tree->type == FT_DEEP)
    {
        TwoThreeFingerTree* deep;
        switch(finger_tree->node.deep->right->size)
        {
        case 1:
            if(finger_tree->node.deep->center == 0)
            {
                return tree_of_digits(finger_tree->node.deep->left);
            }
            else
            {
                deep = two_three_deep();
                deep->node.deep->left = finger_tree->node.deep->left;
                deep->node.deep->center = two_three_init(finger_tree->node.deep->center);
                deep->node.deep->right = node_to_digit(two_three_last(finger_tree->node.deep->center));
                two_three_element_count(deep);
                return deep;
            }
        case 2:
            deep = two_three_deep();
            deep->node.deep->center = finger_tree->node.deep->center;
            deep->node.deep->left = finger_tree->node.deep->left;
            deep->node.deep->right->one = finger_tree->node.deep->right->one;
            deep->node.deep->right->two = 0;
            deep->node.deep->right->three = 0;
            deep->node.deep->right->four = 0;
            deep->node.deep->right->size = 1;
            two_three_element_count(deep);
            return deep;
        case 3:
            deep = two_three_deep();
            deep->node.deep->center = finger_tree->node.deep->center;
            deep->node.deep->left = finger_tree->node.deep->left;
            deep->node.deep->right->one = finger_tree->node.deep->right->one;
            deep->node.deep->right->two = finger_tree->node.deep->right->two;
            deep->node.deep->right->three = 0;
            deep->node.deep->right->four = 0;
            deep->node.deep->right->size = 2;
            two_three_element_count(deep);
            return deep;
        case 4:
            deep = two_three_deep();
            deep->node.deep->center = finger_tree->node.deep->center;
            deep->node.deep->left = finger_tree->node.deep->left;
            deep->node.deep->right->one = finger_tree->node.deep->right->one;
            deep->node.deep->right->two = finger_tree->node.deep->right->two;
            deep->node.deep->right->three = finger_tree->node.deep->right->three;
            deep->node.deep->right->four = 0;
            deep->node.deep->right->size = 3;
            two_three_element_count(deep);
            return deep;
        }
    }
    else
    {
        out() << "Error: Malformed list call." << std::endl;
        correct_parsing = false;
        return 0;
    }
}

TwoThreeFingerTree* two_three_recursive_append(TwoThreeFingerTree* list,TwoThreeFingerTree* nodes)
{
    if(nodes==0)
    {
        return list;
    }
    return two_three_recursive_append(two_three_append(list,two_three_head(nodes)),two_three_tail(nodes));
}

TwoThreeFingerTree* two_three_recursive_cons(TwoThreeFingerTree* list,TwoThreeFingerTree* nodes)
{
    if(nodes==0)
    {
        return list;
    }
    return two_three_recursive_cons(two_three_cons(list,two_three_last(nodes)),two_three_init(nodes));
}

TwoThreeFingerTree* shunt_to_nodes(Digit* digit1, TwoThreeFingerTree* list, Digit* digit2)
{
    //    test_num++;
    TwoThreeFingerTree* node_list = 0;

    if(digit1!=0)
    {
        switch(digit1->size)
        {
        case 0:
            break;
        case 1:
            node_list = two_three_append(node_list,digit1->one);
            break;
        case 2:
            node_list = two_three_append(node_list,digit1->one);
            node_list = two_three_append(node_list,digit1->two);
            break;
        case 3:
            node_list = two_three_append(node_list,digit1->one);
            node_list = two_three_append(node_list,digit1->two);
            node_list = two_three_append(node_list,digit1->three);
            break;
        case 4:
            node_list = two_three_append(node_list,digit1->one);
            node_list = two_three_append(node_list,digit1->two);
            node_list = two_three_append(node_list,digit1->three);
            node_list = two_three_append(node_list,digit1->four);
            break;
        }
    }

    if(list != 0)
    {
        node_list = two_three_recursive_append(node_list,list);
    }

    if(digit2!=0)
    {
        switch(digit2->size)
        {
        case 0:
            break;
        case 1:
            node_list = two_three_append(node_list,digit2->one);
            break;
        case 2:
            node_list = two_three_append(node_list,digit2->one);
            node_list = two_three_append(node_list,digit2->two);
            break;
        case 3:
            node_list = two_three_append(node_list,digit2->one);
            node_list = two_three_append(node_list,digit2->two);
            node_list = two_three_append(node_list,digit2->three);
            break;
        case 4:
            node_list = two_three_append(node_list,digit2->one);
            node_list = two_three_append(node_list,digit2->two);
            node_list = two_three_append(node_list,digit2->three);
            node_list = two_three_append(node_list,digit2->four);
            break;
        }
    }

    return node_list;
}

TwoThreeFingerTree* pack_nodes(TwoThreeFingerTree* nodes)
{
    test_num++;
    if(nodes == 0)
    {
        return 0;
    }

    TwoThreeFingerTree* list = 0;
    TwoThreeFingerTree* new_list = 0;
    TwoThreeFingerTree* a;
    TwoThreeFingerTree* b;
    a = two_three_head(nodes);
    list = two_three_tail(nodes);
    b = two_three_head(list);
    list = two_three_tail(list);

    TwoThreeFingerTree* c;
    if(two_three_head(list)==0)
    {
        return two_three_append(new_list,two_three_node2(a,b));
    }
    else
    {
        c = two_three_head(list);
        list = two_three_tail(list);
    }

    TwoThreeFingerTree* d;
    if(two_three_head(list)==0)
    {
        return two_three_append(new_list,two_three_node3(a,b,c));
    }
    else
    {
        d = two_three_head(list);
        list = two_three_tail(list);
    }

    if(two_three_head(list)==0)
    {
        list = two_three_append(new_list,two_three_node2(a,b));
        return two_three_append(new_list,two_three_node2(c,d));
    }
    else
    {
        list = two_three_cons(list,d);
        return two_three_cons(pack_nodes(list),two_three_node3(a,b,c));
    }
}

TwoThreeFingerTree* two_three_concat(TwoThreeFingerTree* list,TwoThreeFingerTree* nodes,TwoThreeFingerTree* list2)
{
    test_num++;
    if(list == 0 && list2 == 0)
    {
        return nodes;
    }
    if(list==0 && list2!=0)
    {
        return two_three_recursive_cons(list2,nodes);
    }
    if(list!=0 && list2==0)
    {
        return two_three_recursive_append(list,nodes);
    }
    if(list->type == FT_SINGLE)
    {
        return two_three_cons(two_three_recursive_cons(list2,nodes),list->node.single->a);
    }
    if(list2->type == FT_SINGLE)
    {
        return two_three_append(two_three_recursive_append(list,nodes),list2->node.single->a);
    }
    if(list->type == FT_DEEP)
    {
        TwoThreeFingerTree* deep = two_three_deep();
        deep->node.deep->left = list->node.deep->left;
        deep->node.deep->right = list2->node.deep->right;
        TwoThreeFingerTree* node_list = shunt_to_nodes(list->node.deep->right,nodes,list2->node.deep->left);
        deep->node.deep->center = two_three_concat(list->node.deep->center,node_list,list2->node.deep->center);
        two_three_element_count(deep);
        return deep;
    }
}

TwoThreeFingerTree* two_three_list_concatenation(TwoThreeFingerTree* list,TwoThreeFingerTree* list2)
{
    //    test_num = 0;
    //    return two_three_concat(list,0,list2);
    //Stop gap, replace with log(n) version.
    return two_three_recursive_append(list,list2);
}

//List hooks
inline TwoThreeFingerTree* two_three_list_cons(TwoThreeFingerTree* list,const object& obj)
{
    TwoThreeFingerTree* element = two_three_element(obj);
    return two_three_cons(list,element);
}

inline TwoThreeFingerTree* two_three_list_append(TwoThreeFingerTree* list,const object& obj)
{
    TwoThreeFingerTree* element = two_three_element(obj);
    return two_three_append(list,element);
}

inline object two_three_list_head(TwoThreeFingerTree* list)
{
    TwoThreeFingerTree* element = two_three_head(list);
    return *(element->node.a);
}

object two_three_list_last(TwoThreeFingerTree* list)
{
    TwoThreeFingerTree* element = two_three_last(list);
    return *element->node.a;
}


inline bool two_three_print(TwoThreeFingerTree *list)
{
    if(list == 0)
    {
        return true;
    }
    print_object_in_array(two_three_list_head(list),1);
    return two_three_print(two_three_tail(list));
}

TwoThreeFingerTree* map_binary_function1(TwoThreeFingerTree* list,const object& arg2,const object& op)
{
    TwoThreeFingerTree* iterative_list = list;
    TwoThreeFingerTree* new_list = 0;

    while(iterative_list>0)
    {
        optic_stack.push_back(arg2);
        optic_stack.push_back(two_three_list_head(iterative_list));
        optic_stack.push_back(op);

        object obj;
        if(evaluate_top())
        {
            obj = optic_stack.back();
            optic_stack.pop_back();
        }

        else
        {
            out() << "Error: malformed List operation." << std::endl;
            correct_parsing = false;
            clear_stack();
            return false;
        }
        iterative_list = two_three_tail(iterative_list);
        new_list = two_three_list_append(new_list,obj);
    }
    return new_list;
}

TwoThreeFingerTree* map_binary_function2(TwoThreeFingerTree* list,const object& arg1,const object& op)
{
    TwoThreeFingerTree* iterative_list = list;
    TwoThreeFingerTree* new_list = 0;

    while(iterative_list>0)
    {
        optic_stack.push_back(two_three_list_head(iterative_list));
        optic_stack.push_back(arg1);
        optic_stack.push_back(op);

        object obj;
        if(evaluate_top())
        {
            obj = optic_stack.back();
            optic_stack.pop_back();
        }

        else
        {
            out() << "Error: malformed List operation." << std::endl;
            correct_parsing = false;
            clear_stack();
            return false;
        }
        iterative_list = two_three_tail(iterative_list);
        new_list = two_three_list_append(new_list,obj);
    }
    return new_list;
}

TwoThreeFingerTree* map_binary_function3(TwoThreeFingerTree* list,TwoThreeFingerTree* list2,const object& op)
{
    bool tripped1 = false;
    bool tripped2 = false;
    TwoThreeFingerTree* iterative_list = list;
    TwoThreeFingerTree* iterative_list2 = list2;
    TwoThreeFingerTree* new_list = 0;

    while(true)
    {
        if(iterative_list==0)
        {
            tripped1 = true;
        }

        if(iterative_list2==0)
        {
            tripped2 = true;
        }

        if(tripped1&&tripped2)
        {
            break;
        }

        if(iterative_list==0)
        {
            iterative_list = list;
        }

        if(iterative_list2==0)
        {
            iterative_list2 = list2;
        }

        optic_stack.push_back(two_three_list_head(iterative_list2));
        optic_stack.push_back(two_three_list_head(iterative_list));
        optic_stack.push_back(op);

        object obj;
        if(evaluate_top())
        {
            obj = optic_stack.back();
            optic_stack.pop_back();
        }

        else
        {
            out() << "Error: malformed List operation." << std::endl;
            correct_parsing = false;
            clear_stack();
            return false;
        }
        iterative_list = two_three_tail(iterative_list);
        iterative_list2 = two_three_tail(iterative_list2);
        new_list = two_three_list_append(new_list,obj);
        //        new_list = two_three_list_cons(new_list,obj);
    }

    return new_list;
}

TwoThreeFingerTree* two_three_digit_lookup_check(Digit* digit,int& index)
{
    int size_one, size_two, size_three, size_four;
    switch(digit->size)
    {
    case 4:
        switch(digit->four->type)
        {
        case FT_NODE2:
            size_four = digit->four->node.node2->element_count;
            break;
        case FT_NODE3:
            size_four = digit->four->node.node3->element_count;
            break;
        case FT_ELEMENT:
            size_four = 1;
            break;
        }
    case 3:
        switch(digit->three->type)
        {
        case FT_NODE2:
            size_three = digit->three->node.node2->element_count;
            break;
        case FT_NODE3:
            size_three = digit->three->node.node3->element_count;
            break;
        case FT_ELEMENT:
            size_three = 1;
            break;
        }
    case 2:
        switch(digit->two->type)
        {
        case FT_NODE2:
            size_two = digit->two->node.node2->element_count;
            break;
        case FT_NODE3:
            size_two = digit->two->node.node3->element_count;
            break;
        case FT_ELEMENT:
            size_two = 1;
            break;
        }
    case 1:
        switch(digit->one->type)
        {
        case FT_NODE2:
            size_one = digit->one->node.node2->element_count;
            break;
        case FT_NODE3:
            size_one = digit->one->node.node3->element_count;
            break;
        case FT_ELEMENT:
            size_one = 1;
            break;
        }
    }

    switch(digit->size)
    {
    case 4:
        if(index < size_one )
        {
            return digit->one;
        }
        if(index < size_one + size_two )
        {
            index -= size_one;
            return digit->two;
        }
        if(index < size_one + size_two + size_three )
        {
            index -= size_one + size_two;
            return digit->three;
        }
        if(index < size_one + size_two + size_three + size_four )
        {
            index -= size_one + size_two + size_three;
            return digit->four;
        }
    case 3:
        if(index < size_one )
        {
            return digit->one;
        }
        if(index < size_one + size_two )
        {
            index -= size_one;
            return digit->two;
        }
        if(index < size_one + size_two + size_three )
        {
            index -= size_one + size_two;
            return digit->three;
        }
    case 2:
        if(index < size_one )
        {
            return digit->one;
        }
        if(index < size_one + size_two )
        {
            index -= size_one;
            return digit->two;
        }
    case 1:
        if(index < size_one )
        {
            return digit->one;
        }
    }

    return 0;
}

inline TwoThreeFingerTree* two_three_node3_lookup(TwoThreeFingerTree* tree, int& index)
{
    int size_one, size_two, size_three;

    switch(tree->node.node3->a->type)
    {
    case FT_NODE2:
        size_one = tree->node.node3->a->node.node2->element_count;
        break;
    case FT_NODE3:
        size_one = tree->node.node3->a->node.node3->element_count;
        break;
    case FT_ELEMENT:
        size_one = 1;
        break;
    }

    if(index < size_one )
    {
        return tree->node.node3->a;
    }

    switch(tree->node.node3->b->type)
    {
    case FT_NODE2:
        size_two = tree->node.node3->b->node.node2->element_count;
        break;
    case FT_NODE3:
        size_two = tree->node.node3->b->node.node3->element_count;
        break;
    case FT_ELEMENT:
        size_two = 1;
        break;
    }

    if(index < size_one+size_two )
    {
        index -= size_one;
        return tree->node.node3->b;
    }

    switch(tree->node.node3->c->type)
    {
    case FT_NODE2:
        size_three = tree->node.node3->c->node.node2->element_count;
        break;
    case FT_NODE3:
        size_three = tree->node.node3->c->node.node3->element_count;
        break;
    case FT_ELEMENT:
        size_three = 1;
        break;
    }

    if(index < size_one+size_two+size_three )
    {
        index -= size_one+size_two;
        return tree->node.node3->c;
    }
    return 0;
}

inline TwoThreeFingerTree* two_three_node2_lookup(TwoThreeFingerTree* tree, int &index)
{
    int size_one, size_two;

    switch(tree->node.node2->a->type)
    {
    case FT_NODE2:
        size_one = tree->node.node2->a->node.node2->element_count;
    case FT_NODE3:
        size_one = tree->node.node2->a->node.node3->element_count;
    case FT_ELEMENT:
        size_one = 1;
    }


    if(index < size_one )
    {
        return tree->node.node2->a;
    }

    switch(tree->node.node2->b->type)
    {
    case FT_NODE2:
        size_two = tree->node.node2->b->node.node2->element_count;
    case FT_NODE3:
        size_two = tree->node.node2->b->node.node3->element_count;
    case FT_ELEMENT:
        size_two = 1;
    }

    if(index < size_one+size_two )
    {
        return tree->node.node2->b;
    }

    std::cout << "Node2 NOTHING!?" << std::endl;
    return 0;
}

object two_three_lookup(TwoThreeFingerTree* tree, int index)
{
    if(tree == 0)
    {
        object n = mem_alloc(NIL);
        return n;
    }

    TwoThreeFingerTree* search_tree = tree;
    int i = index;
    test_num = 0;
    while(true)
    {
        std::cout << search_tree->type << " , i: " << i << std::endl;
        switch(search_tree->type)
        {
        case FT_NODE3:
            search_tree = two_three_node3_lookup(search_tree, i);
            continue;
        case FT_NODE2:
            search_tree = two_three_node2_lookup(search_tree, i);
            continue;
        case FT_DEEP:
            test_num++;
            if(i < search_tree->node.deep->left->element_count)
            {
                search_tree = two_three_digit_lookup_check(search_tree->node.deep->left,i);
                continue;
            }
            int center_size;

            if(search_tree->node.deep->center == 0)
            {
                center_size = 0;
            }
            else if(search_tree->node.deep->center->type == FT_DEEP)
            {
                center_size = search_tree->node.deep->center->node.deep->element_count;
            }
            else if(search_tree->node.deep->center->type == FT_SINGLE)
            {
                center_size = search_tree->node.deep->center->node.single->element_count;
            }
            else
            {
                center_size = 1;
            }

            if(i - (search_tree->node.deep->left->element_count + center_size) >= 0)
            {
                i = i - (search_tree->node.deep->left->element_count + center_size);
                search_tree = two_three_digit_lookup_check(search_tree->node.deep->right,i);
                continue;
            }
            else
            {
                i = i - search_tree->node.deep->left->element_count;
                search_tree = search_tree->node.deep->center;
                continue;
            }
        case FT_SINGLE:
            search_tree = search_tree->node.single->a;
            continue;
        case FT_ELEMENT:
            complexity_test();
            return *search_tree->node.a;
        }
    }
}
#endif

}
