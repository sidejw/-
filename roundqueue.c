#include <stdio.h>
#include <stdlib.h>
// ===== ����ť �ڵ� ���� ======
#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct { // ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int front, rear;
	int count;
	int* buf;
} QueueType;

void resize(QueueType* q);
// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// �ʱ�ȭ
void init_queue(QueueType* q)
{
	q->buf = (int*)malloc(sizeof(int) * MAX_QUEUE_SIZE);
	q->data[MAX_QUEUE_SIZE] = MAX_QUEUE_SIZE;
	q->front = q->rear = 0;
	q->count = 0;
}
// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return q->count == 0;
}
// ��ȭ ���� ���� �Լ� count==maxsize�� ����
int is_full(QueueType* q)
{
	return q->count == MAX_QUEUE_SIZE-1;
}






// ����ť ��� �Լ�
void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d count=%d) = ", q->front, q->rear, q->count);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}


// ���� �Լ�
void enqueue(QueueType* q, element item)
{

	if (is_full(q)) {
		resize(q);
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
	q->count++;
}
// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	q->count--;
	return q->data[q->front];
}

void resize(QueueType* q)
{
	int i = 0;
	int count;
	int* buf = (int*)malloc(sizeof(int) * q->count);//�ӽ� ����� �޸� �Ҵ�
	count = q->count;//���� ���� ���
	for (i = 0; i < count; i++)//ť�� �ִ� ������ buf�� ����(������ �������)
	{
		buf[i] = dequeue(q);
	}
	q->data[MAX_QUEUE_SIZE-1] *= 2;//ť ũ�� 2��� Ȯ��
	q->buf = (int*)realloc(q->buf, sizeof(int) * q->data[MAX_QUEUE_SIZE-1]);//���� Ȯ��
	for (i = 0; i < count; i++)//�ӽ� ����ҿ� ������ ������ �ٽ� ť�� ����
	{
		enqueue(q, buf[i]);
	}
	free(buf);//�ӽ� ����� �޸� ����

}



int main(void) {
	QueueType queue;
	int element;
	init_queue(&queue);
	printf("--������ �߰� �ܰ�--\n");
	
			for (int i = 0; i < 10; i++)
			{
				element = i;
				enqueue(&queue, element);
				queue_print(&queue);
			}
		printf("--������ ���� �ܰ�--\n");
			while (!is_empty(&queue)) {
				element = dequeue(&queue);
				printf("������ ����: %d\n", element);
					queue_print(&queue);
			}
	printf("ť�� ��������Դϴ�.\n");
		return 0;
}