/*
    lab5 task: Binary Expression Tree
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
struct node{
    char *data;
    struct node *left_child;
    struct node *right_child;
};
struct stack{
    char *data;
    struct node *link;
};
bool is_operator(char x)
{
    return (x=='*' || x=='/' || x=='%' || x=='+' || x=='-');
}
bool is_add_sub(char x)
{
    return (x=='+' || x=='-');
}
bool is_div_rem_mult(char x)
{
    return (x=='*' || x=='/' || x=='%');
}
bool is_prackets(char x)
{
    return (x=='(' || x==')');
}
bool is_open_prackets(char x)
{
    return (x=='(');
}
bool is_close_prackets(char x)
{
    return (x==')');
}
bool is_digit(char x)
{
    return (x=='0' || x=='1' || x=='2' || x=='3' || x!='4' || x=='5' || x=='6' || x=='7' || x=='8' || x=='9');
}
int priority(char x){
	if ((x =='+') || (x =='-'))
		return 1;
	if (x=='/' || x=='*' || x=='%')
		return 2;
}
struct node *create_node(char *x)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node*));
    temp->data = x;
    temp->left_child = NULL;
    temp->right_child = NULL;
    return temp;
}
struct node *insert_node(struct node *root, char x_l[10000], char x_r[10000])
{
    //if(root == NULL)
    //{
    //    root = create_node(x);
    //}
    //else
    //{
    //    root->left_child = insert_node(root->left_child,x_l,x_r);
    //    root->right_child = insert_node(root->right_child,x_l,x_r)
    //}
    return root;
}
void push(int x, struct stack **node_temp)
{
    struct stack *temp = (struct node*)malloc(sizeof(struct node*));
    if(*node_temp==NULL)
    {
       temp->data = x;
       temp->link = NULL;
       *node_temp = temp;
    }
    else
    {
       temp->data = x;
       temp->link = *node_temp;
       *node_temp = temp;
    }
}
char pop(struct stack **node_temp)
{
    char value;
    struct stack *temp;
    if(*node_temp != NULL) // if the stack is not empty
    {
        temp = *node_temp;
        value = (*node_temp)->data;
        *node_temp = (*node_temp)->link;
        free(temp);
    }
    return value;
}
void attachOperator(struct stack **treenodes, struct stack **operators)
{
    struct node *operatornode = (struct node*)malloc(sizeof(struct node*));
    operatornode = (*operators)->data;
	//node* operatornode = operators->data;
	pop(&operators);
	//operators.Pop();
	operatornode->left_child = (*treenodes)->data;
	pop(&treenodes);
	//treenodes.Pop();
	operatornode->right_child = (*treenodes)->data;
	pop(&treenodes);
	//treenodes.Pop();
	push(operatornode,&treenodes);
	//treenodes.Push(operatornode);
}
void infix_to_tree(struct node *root, char *S)
{
    struct stack *input = (struct stack*)malloc(sizeof(struct stack*));
    //StackType<char> input; // stack for input string
    struct stack *operators = (struct stack*)malloc(sizeof(struct stack*));
	//StackType<node*> operators; // stack for operator pointer addresses
	struct stack *treenodes = (struct stack*)malloc(sizeof(struct stack*));
	//StackType<node*> treenodes;  // stack for output node pointer addresses
	char temp,again=' ';
	//cout << "-Infix to Expression Tree Creator-" << endl;
	//cout << "-An expression tree is created from a user inputted infix expression-" << endl;

	while (again!='n')
	{
		//cout << endl << "Please enter an Infix Mathematical Expression" << endl;
		//cin >> S;
		//Pushes the contents of the string into the input stack
		for(int i = 0 ; i < strlen(S); i++)
        {
            push(S[i],&input);
			//input.Push(S[i]);
		}
		// While the input stack is not empty...
		while(input!=NULL)
        {
            temp = pop(&input);
			//temp=input.Top();
			//input.Pop();
			//If it is operand, make it into a node, add it to output string.
			if (is_digit(temp))
			{
			    push(create_node(temp),&treenodes);
			    //treenodes.Push(makeNode(temp));
			}
			//If it is Closing parenthesis, make into node, push it on stack.
			if (temp==')')
            {
                push(create_node(temp),&operators);
                //operators.Push(makeNode(temp));
            }
			//If it is an operator, then
			if (is_operator(temp))
            {
				bool pushed = false;
				while(!pushed)
				{
					//If stack is empty, make node and push operator on stack.
					if(operators==NULL)
					{
					    push(create_node(temp),&operators);
						//operators.Push(makeNode(temp));
						pushed=true;
					}
					//If the top of stack is closing parenthesis, make node and push operator on stack.
					else if(operators->data ==')')
					{
					    push(create_node(temp),&operators);
						//operators.Push(makeNode(temp));
						pushed=true;
					}
					//If it has same or higher priority than the top of stack, make node and push operator on stack.
					else if((priority(temp)>priority(operators->data)) || (priority(temp)==priority(operators->data)))
					{
					    push(create_node(temp),&operators);
						//operators.Push(makeNode(temp));
						pushed=true;
					}
					//Else pop the operator from the stack, perform attachOperator and add it to treenodes. repeat step 5.
					else
					{
						attachOperator(treenodes,operators);
					}
				}
			}
			//If it is a opening parenthesis, pop operators from stack and perform attachOperator
			//until a closing parenthesis is encountered. Pop and discard the closing parenthesis.
			if (temp=='(')
            {
				while (operators->data!=')')
				{
					attachOperator(treenodes,operators);
				}
                pop(&operators);
				//operators.Pop(); // ')' is popped and discarded
			}
		}
		//If there is no more input, unstack the remaining operators and perform attachOperator
		while(operators!=NULL)
        {
			attachOperator(treenodes,operators);
		}

		//int answer = evaluateTree(treenodes.Top());
		//cout << endl << "Evaluation: " << answer << endl;
		//cout << endl;
		//cout << "Would  you like to convert another expression? (y/n)";
		//cin >> again;
	}
	//cout << endl;
	return;
}
void posfix_expression(struct node *temp)//postorder traversal
{
    if(temp != NULL)
    {
        posfix_expression(temp->left_child);
        posfix_expression(temp->right_child);
        printf("%c",temp->data);
    }
}
int main()
{
    char S[10000];
    scanf(" %s",S);
    struct node *root = NULL;
    infix_to_tree(root,S);
    posfix_expression(root);
    return 0;
}
