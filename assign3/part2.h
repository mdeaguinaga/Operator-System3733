struct node {
   int pagenum;
   struct node* up;
   struct node* down;
};
typedef struct node node;

void push(int page, node** top); 
int pop(node** top); 
int peek(node** top); 
int peer(int page, node** top);
int cut(int page, node** top); 
void tracestack(node** top); 
void freestack(node** top); 


