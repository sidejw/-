#include <stdio.h>
#include <stdlib.h>
// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct { // 큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
	int count;
	int* buf;
} QueueType;

void resize(QueueType* q);
// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 초기화
void init_queue(QueueType* q)
{
	q->buf = (int*)malloc(sizeof(int) * MAX_QUEUE_SIZE);
	q->data[MAX_QUEUE_SIZE] = MAX_QUEUE_SIZE;
	q->front = q->rear = 0;
	q->count = 0;
}
// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return q->count == 0;
}
// 포화 상태 검출 함수 count==maxsize가 같냐
int is_full(QueueType* q)
{
	return q->count == MAX_QUEUE_SIZE-1;
}






// 원형큐 출력 함수
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


// 삽입 함수
void enqueue(QueueType* q, element item)
{

	if (is_full(q)) {
		resize(q);
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
	q->count++;
}
// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	q->count--;
	return q->data[q->front];
}

void resize(QueueType* q)
{
	int i = 0;
	int count;
	int* buf = (int*)malloc(sizeof(int) * q->count);//임시 저장소 메모리 할당
	count = q->count;//보관 개수 기억
	for (i = 0; i < count; i++)//큐에 있는 내용을 buf로 복사(보관한 순서대로)
	{
		buf[i] = dequeue(q);
	}
	q->data[MAX_QUEUE_SIZE-1] *= 2;//큐 크기 2배로 확장
	q->buf = (int*)realloc(q->buf, sizeof(int) * q->data[MAX_QUEUE_SIZE-1]);//버퍼 확장
	for (i = 0; i < count; i++)//임시 저장소에 보관한 내용을 다시 큐에 보관
	{
		enqueue(q, buf[i]);
	}
	free(buf);//임시 저장소 메모리 해제

}



int main(void) {
	QueueType queue;
	int element;
	init_queue(&queue);
	printf("--데이터 추가 단계--\n");
	
			for (int i = 0; i < 10; i++)
			{
				element = i;
				enqueue(&queue, element);
				queue_print(&queue);
			}
		printf("--데이터 삭제 단계--\n");
			while (!is_empty(&queue)) {
				element = dequeue(&queue);
				printf("꺼내진 정수: %d\n", element);
					queue_print(&queue);
			}
	printf("큐는 공백상태입니다.\n");
		return 0;
}