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
  queue_t *q = malloc(sizeof(queue_t));
  q->node_count = 0;
  if (q == NULL)
  {
    fprintf(stderr, "Space could not be allocated");
    return NULL;
  }
  q->head = NULL;
  q->tail = NULL;
  q->node_count = 0;
  return q;
}

/*
param 1: queue struct, q
Free all storage used by queue by looping through list nodes
starting at the head, freeing each node and its value. */
void q_free(queue_t *q)
{
  if (q == NULL || q->head == NULL)
  {
    return;
  }
  list_ele_t *current_node;
  list_ele_t *freed_node;
  current_node = q->head;
  freed_node = NULL;
  while (current_node->next != NULL)
  {
    free(current_node->value);
    freed_node = current_node;
    current_node = current_node->next;
    freed_node->next = NULL;
    free(freed_node);
    q->node_count--;
  }
  free(current_node->value);
  free(current_node);
  free(q);
}

/*
  param 1: (struct) pointed to the queue,
  param 2: (string ) points to the string to be stored
  Function inserts element(string) into the queue at the head.
  Return true if successful.
  Return false if q is NULL or could not allocate space.

 */
bool q_insert_head(queue_t *q, char *s)
{
  if (q == NULL)
  {
    fprintf(stderr, "queue is null");
    return false;
  }
  list_ele_t *new_node;

  new_node = malloc(sizeof(list_ele_t)); // allocates space on a the heap for the new node
  if (new_node == NULL)
  {
    fprintf(stderr, "Error malloc\n");
    return false;
  }

  new_node->value = malloc(sizeof(char) * (strlen(s) + 1));
  if (new_node->value == NULL)
  {
    fprintf(stderr, "Error malloc\n");
    free(new_node);
    return false;
  }

  strcpy(new_node->value, s);
  new_node->next = NULL;

  // makes the new_node the head
  new_node->next = q->head;
  q->head = new_node;

  if (q->tail == NULL)
  {

    q->tail = new_node;
  }
  q->node_count++;

  return true;
}

/*
  param 1: (struct) pointed to the queue
  param 2: (string ) points to the string to be stored
  Functions inserts element(string) at the tail of the queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, char *s)
{
  if (q == NULL)
  {
    fprintf(stderr, "queue is null\n");
    return false;
  }

  list_ele_t *another_new_node;
  another_new_node = malloc(sizeof(list_ele_t));

  if (another_new_node == NULL)
  {
    fprintf(stderr, "Error malloc\n");
    return false;
  }

  another_new_node->value = malloc(sizeof(char) * (strlen(s) + 1));
  if (another_new_node->value == NULL)
  {
    fprintf(stderr, "Error malloc\n");
    free(another_new_node);
    return false;
  }
  // copy string into the node value
  strcpy(another_new_node->value, s);
  another_new_node->next = NULL;

  // adding another_new_node into the queue
  if (q->tail == NULL)
  {
    q->tail = another_new_node;
  }
  else
  {
    q->tail->next = another_new_node;
    q->tail = another_new_node;
    q->tail->next = NULL;
  }

  q->node_count++;
  return true;
}

/*
  param 1: (struct) queue
  param 2: (string) variable that holds the removed string
  param 3: (unsigned long size_t) buffer
  Removes element from the head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.

*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
  if (q == NULL || q->head == NULL)
  {
    return false;
  }
  list_ele_t *removed_head;
  if (sp != NULL)
  {
    strncpy(sp, q->head->value, bufsize - 1);
    sp[bufsize - 1] = '\0';
  }

  // removing head
  removed_head = q->head;
  q->head = q->head->next;
  free(removed_head->value);
  removed_head->next = NULL;
  free(removed_head);
  q->node_count--;
  // TODO if the last list element was removed, the tail might need updating
  // TODO hey, did you forget to free the removed list element?
  return true;
}

/*
  param:(queue) struct
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
  if (q == NULL || q->head == NULL)
  {
    fprintf(stderr, "Something went wrong filling queue");
    return 0;
  }
  return q->node_count;
}

/*
  param: struct (queue)
  Reverse elements in queue by switching
  current node, previous node, and next node.
  No effect if q is NULL or empty.
 */
void q_reverse(queue_t *q)
{
  if (q == NULL || q->head == NULL)
  {
    return;
  }

  list_ele_t *current_node = q->head;
  list_ele_t *next_node = q->head;
  list_ele_t *previous_node = NULL;
  // reversing the queue
  if (q->node_count == 1)
  {
    return;
  }
  while (next_node != NULL && q->node_count != 1)
  {
    next_node = current_node->next;
    current_node->next = previous_node;
    previous_node = current_node;
    current_node = next_node;
    next_node = next_node->next;
  }
  current_node->next = previous_node;
  q->tail = q->head;
  q->head = current_node;
}
