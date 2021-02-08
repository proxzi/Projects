#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG 0
#define END 0
#define READFILE 0

typedef struct Node
{
    struct Node* next;
    void* data;
} Node;

typedef struct Literal {
    int value;
    int step;
    int index;
} Literal;

typedef struct Clause {
    Node* value;
    int step;
    int index;
} Clause;

typedef struct Tree {
    int value;
    int visited;
    int flag_pure;
    int index;
} Tree;

typedef struct Access {
    Node* arr;
    int number;
} Access;

// List declarations
void* init(void* value);
void* push_back(Node* head, void* value);
Node* getLast(Node* head);
Node* getNth(Node* head, int n);
void* popBack(Node** head);
void* deleteNth(Node** head, int n);
void* pop(Node** head);

typedef void (*ReleaseData)(void*);
void deleteList(Node** head, ReleaseData release_data);
// End list declarations

// ----------------------------
Access* init_ac(Node* arr, int number);
Literal* init_li(int value, int step, int index);
Clause* init_cl(Node* value, int step, int index);
Tree* init_tr(int value, int visited, int flag_pure, int index);

void release_li(void* data);
void release_cl(void* data);
void release_tr(void* data);
void release_ac(void* data);

void printClause(Node* cl_root, int i);
void printLiteral(Node* li_root, int i);
void printTree(Node* tr_root);
void printAccess(Node* root);
// ----------------------------
void readfile(char* filename);
void backtrack(int step_back);
int dpll(Node** clause_root, int literal);
int random_literal();
int pure_literal(Node* clause_root);
int solution(int value);
void shuffle(int* arr, int N);
int downhill(int res);
// ----------------------------
int variables = 0;
int clauses = 0;
int step = 0;
Node* data_clause = NULL;
Node* clause_root = NULL;
Node* literal_root = NULL;
Node* tree_root = NULL;
int* random_arr = NULL;

Node* direct_access = NULL;

int main(int argc, char* argv[])
{
    /*Node* cl_root = NULL;
    for (int i = 0; i < 100; ++i)
    {
        Node* li_root = NULL;
        for (int j = 0; j < 100; ++j)
        {
            Literal* li_element = init_li(j, 0, 0);
            if (li_root == NULL) li_root = init(li_element);
            else push_back(li_root, li_element);
        }
        Clause* cl_element = init_cl(li_root, 0, 0);
        if (cl_root == NULL) cl_root = init(cl_element);
        else push_back(cl_root, cl_element);
    }

    Clause* cl = deleteNth(&cl_root, 5);
    Literal* li_5 = deleteNth(&cl->value, 5);

    free(li_5);
    deleteList(&cl->value, release_li);
    free(cl);

    Clause* tmp = popBack(&cl_root);
    release_cl(tmp);

    deleteList(&cl_root, release_cl); */

    if (argc < 2)
    {
        printf("Not enough args: ./a.out [input.cnf]\n");
        return 1;
    }
    char* filename = argv[1];
    printf("%s\n", filename);

    readfile(filename);

    int res = solution(0);

    if (res == 0) res = downhill(res);

    if (END)
    {
        printf("\n----Data------\n");
        printClause(data_clause, 0);
        printf("\n----clauses------\n");
        printClause(clause_root, 1);
        printf("\n----literals------\n");
        printLiteral(literal_root, 1);
    }

    if (res == 1) printf("SAT\n");
    else printf("UNSAT\n");


    if (data_clause != NULL)
        deleteList(&data_clause, release_cl);
    if (tree_root != NULL)
        deleteList(&tree_root, release_tr);
    if (literal_root != NULL)
        deleteList(&literal_root, release_li);
    if (clause_root != NULL)
        deleteList(&clause_root, release_cl);

    free(random_arr);
    return EXIT_SUCCESS;
}

int downhill(int res)
{
    while (res == 0 && tree_root != NULL)
    {
        Clause* last_clause = (Clause*)getLast(clause_root)->data;
        Literal* last_literal = (Literal*)getLast(literal_root)->data;

        int step_back = 0;

        if (END) printf("step: %d\n", step);

        if ((data_clause == NULL || res == 0) &&
            !(last_clause->step != last_literal->step &&
                last_clause->step > last_literal->step && res == 1))
        {
            if (DEBUG) printf("UNSAT\n");

            Node* tmp = getLast(tree_root);
            Tree* tmp_d = tmp->data;
            int last_flag = 0;
            step = tmp_d->index;
            int stephere = 0;
            last_flag = tmp_d->flag_pure;
            stephere = tmp_d->index;

            while (last_flag == 1)
            {
                if (tmp_d->visited == 1 && tmp_d->flag_pure == 0)
                {
                    tmp_d->value *= -1;
                    tmp_d->visited += 1;
                }
                else if (tmp_d->visited == 2 || tmp_d->flag_pure == 1)
                {
                    free(tmp_d);
                    popBack(&tree_root);
                    tmp = getLast(tree_root);
                    if (tmp == NULL) break;
                    tmp_d = tmp->data;
                    if (tmp_d->flag_pure == 1 || tmp_d->visited == 2) continue;
                    tmp_d->value *= -1;
                    tmp_d->visited += 1;
                }
                stephere = tmp_d->index;
                last_flag = tmp_d->flag_pure;
            }

            if (tmp == NULL) break;
            if (END) printTree(tree_root);
            //printf("END TREE\n");
            if (last_flag == 1) backtrack(stephere - 2);
            else backtrack(stephere - 1);
            res = solution(tmp_d->value);
        }
    }
    return res;
}

int solution(int value)
{
    int res = 0;
    if (value != 0)
    {
        res = dpll(&data_clause, value);
        value = 0;
    }

    while (data_clause != NULL)
    {
        int literal = pure_literal(data_clause);

        Tree* tr_element = NULL;
        if (literal != 0)  tr_element = init_tr(literal, 1, 1, 0);
        else               tr_element = init_tr(0, 1, 0, 0);

        if (tree_root == NULL) tree_root = init(tr_element);
        else
        {
            Tree* tr_last = getLast(tree_root)->data;
            tr_element->index = tr_last->index + 1;
            Node* last_node = push_back(tree_root, tr_element);
            tr_element = last_node->data;
        }

        step = tr_element->index;

        if (literal != 0)
        {
            if (DEBUG) printf("PURE_LITERAL: %d\n", literal);
            res = dpll(&data_clause, literal);
        }
        else
        {
            res = dpll(&data_clause, random_literal());
        }

        if (res == 0) break;
        if (DEBUG)
        {
            printClause(data_clause, 0);
            printf("\n");
        }
    }

    return res;
}

void fill_access(Node* cl_element)
{
    Node* beg_li = ((Clause*)cl_element->data)->value;

    Node* tmp_dir = direct_access;
    while (beg_li != NULL)
    {
        Literal* li_element = (Literal*)beg_li->data;
        Access* ac_element = init_ac(NULL, li_element->value);
        if (tmp_dir == NULL)
        {
            ac_element->arr = init(cl_element);
            direct_access = init(ac_element);
        }
        else
        {
            int find_place = 0;
            while (tmp_dir != NULL)
            {
                if (((Access*)tmp_dir->data)->number == li_element->value)
                {
                    push_back(((Access*)tmp_dir->data)->arr, cl_element);
                    find_place = 1;
                    break;
                }
                tmp_dir = tmp_dir->next;
            }

            if (find_place == 0)
            {
                ac_element->arr = init(cl_element);
                push_back(direct_access, ac_element);
            }
        }

        beg_li = beg_li->next;
        tmp_dir = direct_access;
    }
}

void readfile(char* filename)
{
    FILE* mf;
    char line[256];
    mf = fopen(filename, "r");
    if (!mf) { printf("error"); exit(1); }
    int index = 0;
    while (fgets(line, sizeof(line), mf)) {
        if (line[0] == '%') break;
        if (line[0] == 'c') continue;
        if (line[0] == 'p') {
            if (sscanf(line, "p cnf %d %d", &variables, &clauses));
        }
        else
        {
            Node* li_root = NULL;
            char* istr;
            istr = strtok(line, " ");
            if (istr != NULL)
            {
                Literal* li_element = init_li(atoi(istr), 0, 0);
                li_root = init(li_element);
                istr = strtok(NULL, " ");
            }
            while (istr != NULL)
            {
                if (atoi(istr) != 0)
                {
                    Literal* li_element = init_li(atoi(istr), 0, 0);
                    push_back(li_root, li_element);
                }
                istr = strtok(NULL, " ");
            }
            if (READFILE) printLiteral(li_root, 0);

            Clause* cl_element = init_cl(li_root, 0, index);
            Node* tmp = NULL;
            if (index == 0)
            {
                data_clause = init(cl_element);
                tmp = data_clause;
            }
            if (index > 0)
            {
                tmp = push_back(data_clause, cl_element);
            }
            //fill_access(tmp);
            index++;
        }
    }

    random_arr = malloc(variables * sizeof(int));
    int val = 1;
    for (int i = 0; i < variables; i++)
    {
        random_arr[i] = val++;
    }
    shuffle(random_arr, variables);
    if (READFILE)
    {
        for (int i = 0; i < variables; i++)
        {
            printf("a[%d] = %d\n", i, random_arr[i]);
        }
        printf("after ------------------- \n");
    }

    fclose(mf);
    //printAccess(direct_access);
}

int random_literal()
{
    srand((unsigned)time(NULL));
    int rand_val = 0;
    Node* tmp = NULL;
    int symbol = rand() % 2;
    for (int i = 0; i < variables; ++i)
    {
        tmp = tree_root;
        Node* last = NULL;
        while (tmp != NULL)
        {
            rand_val = random_arr[i];
            last = tmp;
            if (rand_val == abs(((Tree*)tmp->data)->value))
            {
                break;
            }
            tmp = tmp->next;
        }
        if (last != NULL && rand_val == abs(((Tree*)last->data)->value))
        {
            continue;
        }
        break;
    }
    if (rand_val == random_arr[variables - 1])
    {
        printf("d");
    }
    if (symbol == 1) rand_val *= (-1);
    if (DEBUG) printf("RANDOM: %d\n", rand_val);
    tmp = getLast(tree_root);
    ((Tree*)tmp->data)->value = rand_val;
    return rand_val;
}

int pure_literal(Node* lst)
{
    int amount = 0;
    Node* list = lst;
    while (list != NULL)
    {
        Node* lit = ((Clause*)list->data)->value;
        Node* tmp = NULL;
        while (lit != NULL)
        {
            amount++;
            tmp = lit;
            lit = lit->next;
        }
        if (amount == 1)
        {
            return ((Literal*)tmp->data)->value;
        }
        amount = 0;
        list = list->next;
    }
    return 0;

}

int dpll(Node** data_clause, int literal)
{
    if (END) { printf("STEPS: \n"); printTree(tree_root); printf("\n"); }

    Node* beg_cl = *data_clause;
    int i = 0;
    int mark_delete = 0;
    int conflict = 0;

    /*
    Node* beg_ac = direct_access;
    while (beg_ac != NULL)
    {
        Access* ac = (Access*)beg_ac->data;
        if (ac->number == literal)
        {
            Node* beg_node = ac->arr;

            while (beg_node != NULL)
            {
                Node* current = (Node*)beg_node->data;
                Clause* cl = (Clause*)(deleteCurrent(data_clause, current));
                Clause cl_element = (*cl);
                if (clause_root == NULL) clause_root = init(&cl_element, sizeof(Clause));
                else push_back(clause_root, &cl_element, sizeof(Clause));
            }
            mark_delete = 1;
            beg_ac = beg_ac->next;

        }
        else if (-(ac->number) == literal)
        {

        }
    }
   */

    while (beg_cl != NULL)
    {
        Clause* clause = beg_cl->data;
        Node* beg_li = clause->value;
        int j = 0;
        while (beg_li != NULL)
        {
            int index = clause->index;

            if (((Literal*)(beg_li)->data)->value == literal)
            {
                Node* next = beg_cl->next;
                Clause* cl_element = deleteNth(data_clause, i);
                mark_delete = 1;
                --i;
                beg_cl = next;

                cl_element->step = step;
                cl_element->index = index;

                if (clause_root == NULL) clause_root = init(cl_element);
                else push_back(clause_root, cl_element);

                break;
            }
            else if (-(((Literal*)(beg_li)->data)->value) == literal)
            {
                int tmp = ((Literal*)(beg_li)->data)->value;
                beg_li = beg_li->next;

                Literal* li_element = deleteNth(&clause->value, j);

                li_element->step = step;
                li_element->index = index;

                if (literal_root == NULL) literal_root = init(li_element);
                else push_back(literal_root, li_element);

                if (clause->value == NULL)
                {
                    Node* next = beg_cl->next;
                    Clause* cl_to_delete = deleteNth(data_clause, i);
                    deleteList(&(cl_to_delete->value), release_li);
                    free(cl_to_delete);
                    --i;
                    beg_cl = next;
                    mark_delete = 1;
                    conflict = 1;
                }
                ++j;
                continue;
            }
            beg_li = beg_li->next;
            ++j;
        }
        ++i;
        if (mark_delete == 0)
        {
            beg_cl = beg_cl->next;
        }
        mark_delete = 0;
    }

    if (DEBUG)
    {
        printClause(*data_clause, 0);
        printf("\n----clauses------\n");
        printClause(clause_root, 1);
        printf("\n----literals------\n");
        printLiteral(literal_root, 1);
    }
    if (conflict == 1) return 0;
    return 1;
}

void backtrack(int step_back)
{
    while (step > step_back)
    {
        Node* beg_li = getLast(literal_root);
        Node* beg_cl = getLast(clause_root);
        Literal* tmpli = beg_li->data;
        Clause* tmpcl = beg_cl->data;

        while (beg_cl != NULL && ((Clause*)beg_cl->data)->step == step)
        {
            tmpcl = beg_cl->data;
            popBack(&clause_root);

            if (data_clause == NULL) data_clause = init(tmpcl);
            else push_back(data_clause, tmpcl);
            //free(tmpcl->data);

            beg_cl = getLast(clause_root);
        }
        // backrtack
        /*
        printf("----------backtrack\n");
        printClause(data_clause, 0);
        printf("----------clause_root\n");
        printClause(clause_root, 1);
        printf("----------literal_root\n");
        printLiteral(literal_root, 1);
        */

        while (beg_li != NULL && ((Literal*)beg_li->data)->step == step)
        {
            tmpli = beg_li->data;

            Node* lst = data_clause;
            int indexInLst = 0;
            while (lst != NULL)
            {
                if (((Clause*)lst->data)->index == tmpli->index)
                {
                    indexInLst = 1;
                    break;
                }
                lst = lst->next;
            }
            if (indexInLst == 0)
            {
                Node* rt = init(tmpli);
                Clause* cl_element = init_cl(rt, 0, tmpli->index);
                push_back(data_clause, cl_element);
            }
            else
            {
                //Literal* li_element = init_li(((Literal*)tmpli->data)->value, 0, ((Literal*)tmpli->data)->index);

                push_back(((Clause*)lst->data)->value, tmpli);

            }
            //free(tmpli->data);
            popBack(&literal_root);

            beg_li = getLast(literal_root);
        }
        --step;
    }
    if (DEBUG)
    {
        printClause(data_clause, 0);
        printf("\n----clauses------\n");
        printClause(clause_root, 1);
        printf("\n----literals------\n");
        printLiteral(literal_root, 1);
    }
}

void shuffle(int* arr, int N)
{
    srand((unsigned)time(NULL));

    for (int i = N - 1; i >= 1; i--)
    {
        int j = rand() % (i + 1);

        int tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
    }
}
////////////////////////////////////////////////////////////////////
// List Impl
void* init(void* value)
{
    Node* root = malloc(sizeof(Node));
    if (root == NULL) exit(EXIT_FAILURE);

    root->data = value;
    root->next = NULL;

    return root;
}

void* push_back(Node* head, void* value)
{
    Node* last = getLast(head);
    if (last == NULL) exit(EXIT_FAILURE);
    Node* tmp = malloc(sizeof(Node));
    if (tmp == NULL) exit(EXIT_FAILURE);

    tmp->data = value;
    tmp->next = NULL;

    last->next = tmp;

    return tmp;
}

Node* getLast(Node* head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

Node* getNth(Node* head, int n) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }
    return head;
}

void* pop(Node** head) {
    Node* prev = NULL;
    void* val = NULL;

    if (!head) exit(-1);
    if (!(*head)) exit(-1);

    prev = (*head);
    val = prev->data;
    (*head) = (*head)->next;
    free(prev);
    return val;
}

void* popBack(Node** head) {
    Node* pFwd = NULL;  //текущий узел
    Node* pBwd = NULL;  //предыдущий узел
    void* val = NULL;
    //Получили NULL
    if (!head) {
        exit(-1);
    }
    //Список пуст
    if (!(*head)) {
        exit(-1);
    }

    pFwd = *head;
    while (pFwd->next) {
        pBwd = pFwd;
        pFwd = pFwd->next;
    }

    if (pBwd == NULL) {
        val = (*head)->data;
        free(*head);
        *head = NULL;
    }
    else {
        val = pFwd->data;
        free(pFwd);
        pBwd->next = NULL;
    }

    return val;
}

void* deleteNth(Node** head, int n) {
    if (n == 0) {
        return pop(head);
    }
    else {
        Node* prev = getNth(*head, n - 1);
        Node* elm = prev->next;
        void* val = elm->data;

        prev->next = elm->next;
        free(elm);
        return val;
    }
}

void* deleteCurrent(Node** head, Node* current)
{
    Node* first_node = (*head);
    Node* prev = NULL;

    while ((*head) != NULL)
    {
        if ((*head) == current)
        {
            if (first_node == (*head)) {
                return pop(head);
            }
            else
            {
                Node* tmp = (*head)->data;
                prev->next = (*head)->next;
                free((*head));
                return tmp;
            }
        }
        prev = (*head);
        (*head) = (*head)->next;
    }
}


void deleteList(Node** head, ReleaseData release_data)
{
    if ((*head) == NULL) return;

    Node* prev = NULL;
    while ((*head)->next) {
        prev = (*head);
        (*head) = (*head)->next;
        release_data(prev->data);
        free(prev);
    }
    release_data((*head)->data);
    free((*head));
}
///////////////////////////////////////////////////
// end List Impl

// Struct ctor and dctor
Literal* init_li(int value, int step, int index)
{
    Literal* li = malloc(sizeof(Literal));
    if (li == NULL) exit(EXIT_FAILURE);

    li->value = value;
    li->step = step;
    li->index = index;
    return li;
}

void release_li(void* data) { free(data); }

Clause* init_cl(Node* value, int step, int index)
{
    Clause* cl = malloc(sizeof(Clause));
    if (cl == NULL) exit(EXIT_FAILURE);

    cl->value = value;
    cl->step = step;
    cl->index = index;
    return cl;
}

void release_cl(void* data)
{
    Clause* cl = data;
    deleteList(&cl->value, release_li);
    free(cl);
}

Tree* init_tr(int value, int visited, int flag_pure, int index)
{
    Tree* tr = malloc(sizeof(Tree));
    if (tr == NULL) exit(EXIT_FAILURE);

    tr->value = value;
    tr->visited = visited;
    tr->flag_pure = flag_pure;
    tr->index = index;
    return tr;
}

void release_tr(void* data) { free(data); }

Access* init_ac(Node* arr, int number)
{
    Access* ac = malloc(sizeof(Access));
    if (ac == NULL) exit(EXIT_FAILURE);

    ac->arr = arr;
    ac->number = number;
    return ac;
}

void release_ac(void* data)
{
    // ToDo
    free(data);
}

// Print lists
void printClause(Node* cl_root, int i)
{
    Node* beg_cl = cl_root;
    while (beg_cl != NULL)
    {
        Clause* cl = (Clause*)beg_cl->data;
        printf("[%d] ", cl->index);
        Node* beg_li = cl->value;
        while (beg_li != NULL)
        {
            Literal* li = (Literal*)beg_li->data;
            printf("%d ", li->value);
            beg_li = beg_li->next;
        }
        if (i == 1) printf("s: %d", cl->step);
        printf("\n");
        beg_cl = beg_cl->next;
    }
}

void printLiteral(Node* li_root, int i)
{
    Node* beg_li = li_root;
    while (beg_li != NULL)
    {
        Literal* li = (Literal*)beg_li->data;
        if (i != 0) printf("[%d] ", li->index);
        printf("%d ", li->value);
        if (i == 1) printf("s: %d \n", li->step);;
        beg_li = beg_li->next;
    }
    printf("\n");
}

void printTree(Node* tr_root)
{
    Node* beg_tr = tr_root;
    while (beg_tr != NULL)
    {
        Tree* tr = (Tree*)beg_tr->data;
        printf("[%d] val: %d, vis: %d, pure: %d\n", tr->index, tr->value, tr->visited, tr->flag_pure);
        beg_tr = beg_tr->next;
    }
}

void printAccess(Node* root)
{
    Node* beg_ac = root;
    while (beg_ac != NULL)
    {
        Access* ac = (Access*)beg_ac->data;
        Node* beg_cl = ac->arr;
        printf("NUMBER [%d] --------------- \n", ac->number);
        while (beg_cl != NULL)
        {
            Clause* cl = (Clause*)((Node*)beg_cl->data)->data;
            Node* beg_li = cl->value;
            printf("[ ");
            while (beg_li != NULL)
            {
                Literal* li = (Literal*)beg_li->data;
                printf("%d ", li->value);
                beg_li = beg_li->next;
            }
            printf(" ]\n");
            beg_cl = beg_cl->next;
        }
        printf("\n");
        beg_ac = beg_ac->next;
    }
}