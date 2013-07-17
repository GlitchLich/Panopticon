#ifndef LIST_H
#define LIST_H

#include "../core/types.h"
#include "../../include/core/containers.h"
#include "../../include/Grammar/parse.h"
#include "core/Memory.h"
#include "../../include/core/stack.h"
#include "../../include/Grammar/parsingutilities.h"
#include "../../include/core/operators.h"
#include "../../include/core/heap.h"
#include "include/core/operators.h"
#include <math.h>

namespace panopticon
{

//general / language callbacks
void complexity_test();
bool print_list(const object &A, int arrayNum);
bool prepend(object& result_A, const object& B, const object& container_C);
bool append(object& result_A, const object& container_B, const object& object_C);
bool concat(object& A, const object& B, const object& C);


//Braun-Tree implemented List
List* create_braun_node(List* l,const object& x, List* r);
bool braun_null(List* list);
List* braun_cons(const object& x, List* list);
List* braun_join(List* list1,List* list2);
List* braun_tail(List* list);
List* braun_update(List* list, int index, const object &y);
object braun_head(List* list);
object braun_lookup(List* list, int index);
bool convert_array_to_list(object &result, object& array);
bool print_braun_tree(List* list);
int braun_length(List* list);

//Finger-Tree implemented List

object two_three_list_last(TwoThreeFingerTree* list);
object two_three_list_head(TwoThreeFingerTree* list);
TwoThreeFingerTree* two_three_list_cons(TwoThreeFingerTree* list, const object &obj);
TwoThreeFingerTree* two_three_list_append(TwoThreeFingerTree* list, const object &obj);
TwoThreeFingerTree* two_three_list_concatenation(TwoThreeFingerTree* list,TwoThreeFingerTree* list2);
TwoThreeFingerTree* two_three_init(TwoThreeFingerTree* finger_tree);
TwoThreeFingerTree* two_three_tail(TwoThreeFingerTree* finger_tree);
bool two_three_print(TwoThreeFingerTree* list);
int two_three_element_count(TwoThreeFingerTree* a);
int two_three_length(TwoThreeFingerTree* a);
object two_three_lookup(TwoThreeFingerTree* tree, int index);

TwoThreeFingerTree* map_binary_function3(TwoThreeFingerTree* list,TwoThreeFingerTree* list2,const object& op);
TwoThreeFingerTree* map_binary_function2(TwoThreeFingerTree* list,const object& arg1,const object& op);
TwoThreeFingerTree* map_binary_function1(TwoThreeFingerTree* list,const object& arg2,const object& op);

struct TwoThreeFingerTree;
union FingerTreeNode;

struct Digit
{
    int element_count;
    int size;
    TwoThreeFingerTree* one;
    TwoThreeFingerTree* two;
    TwoThreeFingerTree* three;
    TwoThreeFingerTree* four;
};

struct Deep
{
    int element_count;
    Digit* left;
    TwoThreeFingerTree* center;
    Digit* right;
};

struct Single
{
    int element_count;
    TwoThreeFingerTree* a;
};

struct Node2
{
    int element_count;
    TwoThreeFingerTree* a;
    TwoThreeFingerTree* b;
};

struct Node3
{
    int element_count;
    TwoThreeFingerTree* a;
    TwoThreeFingerTree* b;
    TwoThreeFingerTree* c;
};


union FingerTreeNode
{
    object* a;
    Single* single;
    Deep* deep;
    Node2* node2;
    Node3* node3;
};

struct TwoThreeFingerTree
{
    int type;
    FingerTreeNode node;
};


}

#endif // LIST_H
