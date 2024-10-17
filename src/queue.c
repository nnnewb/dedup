#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "queue.h"

struct linkqueue *queue_creat()
{
	struct linkqueue *q = (struct linkqueue *) malloc (sizeof (struct linkqueue));
	if (NULL == q)
		return NULL;
	q->front = q->rear = (struct qnode *)malloc(sizeof(struct qnode));
	if (NULL == q->front)
		return NULL;
  	q->front->next = NULL;
  	return q;
}

int queue_destroy(struct linkqueue *q)
{
	while(q->front)
	{
		q->rear = q->front->next;
		free(q->front);
		q->front = q->rear;
	}
	return 0;
}

int queue_empty(struct linkqueue *q)
{
	return (q->front == q->rear)? 0 : -1;
}

int queue_push(struct linkqueue *q, void *e)
{
	struct qnode *p = (struct qnode *)malloc(sizeof(struct qnode));
	if(NULL == p) 
		return errno;
	p->data = e;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;
	return 0;
}

int queue_pop(struct linkqueue *q, void **e)
{
	struct qnode *p;
	if(queue_empty(q) == 0) return -1;
	p = q->front->next;
	*e = p->data;
	q->front->next = p->next;
	if(q->rear == p) q->rear = q->front;
	free(p);
	return 0;
}

int queue_lrupush(struct linkqueue *q, void *e)
{
	struct qnode *p, *pre;

	if (queue_empty(q) != 0)
	{
		pre = q->front;
		p = pre->next;
		while(p && q->compare(p->data, e) != 0 )
		{
			pre = p;
			p= p->next;
		}
		if (p)
		{
			pre->next = p->next;
			if (q->rear == p) q->rear = pre;
			free(p->data);
			free(p);
		}
	}

	return queue_push(q, e);
}

#if TESTQUEUE

int compare(void *e1, void *e2)
{
	return strcmp((char*)e1, (char *)e2);
}

int main(int argc, char *argv[])
{
	int i;
	void *e;
	struct linkqueue *q = queue_creat();
	q->compare = compare;
	for (i = 1; i < argc; ++i)
		queue_repush(q, (void *)strdup(argv[i]));

	while(1)
	{ 
		if (0 == queue_pop(q, &e))
			fprintf(stderr, "%s\n",(char *)e);
		else	
			break;
	}
	queue_destroy(q);

	return 0;
}
#endif
