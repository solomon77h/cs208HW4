/* Ella Visconti and Helana Solomon
 * Starter file for CS 208 assignment: Queues in C
 * Adapted by Aaron Bauer and then Jeff Ondich
 * from a lab developed at CMU by R. E. Bryant, 2017-2018
 */
/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    q->node_count=0;
    if (q==NULL){
      fprintf(stderr, "Space could not be allocated");
      return NULL;
    }
    q->head = NULL;
    q->tail=NULL;
    q->node_count=0;
    return q;
}

/* Free all storage used by queue by looping through list nodes
starting at the head, freeing each node and its value. */
void q_free(queue_t *q)
{
  list_ele_t *current_node;
  list_ele_t *freed_node;
  current_node=q->head;
  freed_node=NULL;
    if (q == NULL|| q->head==NULL){
      return;
    }
    while (current_node->next!=NULL){
      free(current_node->value);
      freed_node=current_node;
      current_node=current_node->next;
      freed_node->next=NULL;
      free(freed_node);
      q->node_count--;
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *new_node;
    // TODO check if q is NULL; what should you do if so?

    // TODO Create a new node, copy the string s into its value.
    new_node = malloc(sizeof(list_ele_t)); // allocates space on a the heap for the new node
    // TODO check if malloc returned NULL
    // TODO use malloc to allocate space for the value and copy s to value
    // If this second malloc call returns NULL, you need to free new_node before returning

    // TODO Hey wait a second. Aren't we also gonna do q_insert_tail? Should
    // we maybe write a utility function to allocate and return a new node so
    // we can reuse it there?
    
    // Connect the new node to the front of the queue.
    new_node->next = q->head;
    q->head = new_node;

    // TODO if the list was empty, the tail might also need updating, however it
    // is you're implementing the notion of tail.
    //increments node count
    q->node_count++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    // TODO implement in similar fashion to q_insert_head
    // You'll certainly want to add a field to queue_t so we can access
    // the tail efficiently.
    // TODO If the list was empty, the head might also need updating
    //increment node count
    q->node_count++;
    return false;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    // TODO check if q is NULL or empty
    if (q==NULL||q->head==NULL){
      return false;
    }
    list_ele_t *removed_head;
    if (sp!=NULL){
      strncpy(sp, q->head->value, bufsize-1);
      sp[bufsize-1]='\0';
    }
    removed_head=q->head;
    // TODO if sp is not NULL, copy value at the head to sp
    // Use strncpy (http://www.cplusplus.com/reference/cstring/strncpy/)
    // bufsize is the number of characters already allocated for sp
    // Think about:
    //    - what should happen if q->head->value is longer than bufsize?
    //    - what should happen if bufsize == 0?
    //    - under what conditions will strncpy copy the \0 character
    //        into sp, and when will it fail to do so (so you'll have
    //        to insert a \0 manually)?

    // TODO update q->head to remove the current head from the queue
    q->head = q->head->next;
    free(removed_head->value);
    removed_head->next=NULL;
    free(removed_head);
    q->node_count--;
    // TODO if the last list element was removed, the tail might need updating
    // TODO hey, did you forget to free the removed list element?
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q){
    // TODO implement this function. If you add a field to queue_t
    // to keep track of the number of nodes in the queue, then this
    // function is fast-running and easy to write. But it also means
    // you have to be very careful about keeping track of the number
    // of nodes elsewhere in your code.

    // TODO what if q == NULL or q->head == NULL?
    if (q==NULL || q->head==NULL){
      fprintf(stderr,"Something went wrong filling queue");
      return 0;
    }
    return q->node_count;
}

/*
  Reverse elements in queue by switching
  current node, previous node, and next node
  No effect if q is NULL or empty
 */
void q_reverse(queue_t *q)
{
  if (q==NULL || q->head==NULL){
    return;
  }
  list_ele_t *current_node=q->head;
  list_ele_t *next_node= q->head;
  list_ele_t *previous_node=NULL;
  
  while (next_node!=NULL){
    current_node->next=previous_node;
    previous_node=current_node;
    current_node=next_node;
    next_node=next_node->next;
  }
  current_node->next=previous_node;
  q->head=current_node;
  q->tail=q->head;
}
