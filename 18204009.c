  #include<stdio.h>
  #include<stdlib.h>

  struct Node {
     int data;
     struct Node *next;
  };

  struct Node* top = NULL;

  void display() {
     struct Node* Pointer;
     if(top==NULL)
     printf("Stack Is Empty\n");

     else {
        Pointer = top;
        printf("Stack Elements Are\n");
        while (Pointer != NULL) {
            printf("%d", Pointer->data);
            Pointer = Pointer->next;
        }
     }
    printf("\n");
  }

  void push(int Count) {
     struct Node* newnode = (struct Node*) malloc(sizeof(struct Node));
     newnode->next = top;
     newnode->data = Count;
     top = newnode;
  }

  void pop() {
     if(top==NULL)
        printf("Stack Underflow\n");
     else {
       printf("The Popped Element Is %d\n ", top->data);
        top = top->next;
     }
  }


  int main() {
     int Choice, Count;
     printf("\n1) Do You Want To Push in stack\n" );
     printf("\n2) Do You Want To Pop from stack\n" );
     printf("\n3) Do You Want To Display stack\n" );
     printf("\n4) Do You Want To Exit\n");
     do {
        printf("Enter Choice\n");
        scanf("%d", &Choice);
        switch(Choice) {
           case 1: {
                     printf("\nEnter The value to be pushed in the stack :\n");
                     scanf("%d", &Count);
                     push(Count);
                      break;
                   }

           case 2: {  pop();
                      break;
                   }

           case 3: {
                     display();
                     break;
                   }

           case 4: {
                      printf("Exit\n");
                      break;
                   }

           default: {
                        printf("Invalid Choice");
                   }
       }

     }while(Choice!=4);
  return 0;
  }
