# README 과제 정리

* 철학자의 3가지 모드

1. 먹기
- 먹기 위해서는 양 옆에 있는 포크를 1개씩 집어야 먹을 수 있다.
- 다 먹었으면 포크를 내려놓고 잠을 잔다.

2. 잠자기

3. 생각하기

- 세 가지 모드중 하나만 될 수 있다.

* 옵션
- 철학자수(=포크수)
- 철학자 수명 => 프로그램 시작부터 수명이 지나면 죽음. 밥 먹고나서 리셋됨.

철학자의 수명 (time_to_die): 밀리초 단위로, 철학자가 마지막으로 밥을 먹은 지 'time_to_die' 시간만큼이 지나거나, 프로그램 시작 후 'time_to_die' 시간만큼이 지나면 해당 철학자는 사망합니다.

- 밥먹시간 => 밥 먹는데 소비되는 시간. 이 시간동안 포크 2개를 소유하고 있어야 한다.
- 잠자는시간
- [각 철학자 최소 식사횟수][종료조건] => 모든 철학자가 이 횟수를 만족하면 종료된다.
	=> 이 값 명시가 안되어 있을 경우, 누구한명이 사망할 때까지 계속됨.

* About 디버그...

timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died

철학자의 사망 시점과 이를 출력하기 까지의 틈이 10ms 이상이 되면 안 됩니다.

memset, printf, malloc, free, write, usleep

```C
#include <sys/time.h>
int gettimeofday(struct timeval *tv, struct timezone *tz);
struct timeval {
	time_t		tv_sec;
	suseconds_t	tv_usec;
}
int main()
{
	struct timeval startTime, endTime;
	double diffTime;

	gettimeofday(&startTime, NULL);
	// 특정 작업 수행
	sleep(1);
	gettimeofday(&endTime, NULL);
	diffTime = ( endTime.tv_sec - startTime.tv_sec ) + (( endTime.tv_usec - startTime.tv_usec ) / 1000000);
	printf("%f s\n", diffTime);
	return 0;
}
```

- 컴파일시 -lpthread 옵션 붙여넣기!
```C
#include <pthread.h>
int pthread_create(pthread_t *th_id, const pthread_attr_t *attr, void* 함수명, void *arg );
/*
	th_id	: thread's id
	attr	: 옵션같은거
	함수	 : 쓰레드가 수행할 함수. 함수반환값은 고정이다.
	arg		: 분기할 함수로 넘겨줄 인자 값. 자료형의 자유를 위해 void로 넘겨준다.
	return	: 성공하면 0 반환.
*/

int pthread_join(pthread_t th_id, void** thread_return);
/*
	th_id	: wait할 쓰레드의 id
	thread_return : pthread의 리턴값. => 어떻게 사용해야 할지 잘 모르겠다... 왜 투포인터지?
*/

int pthread_detach(pthread_t th_id);
/*
	th_id	: 해당 쓰레드는 부모 쓰레드로부터 독립한다. => ...? 독립이 무슨개념인지?
	독립된 쓰레드는 pthread_join()이 없어도 종료시 자동으로 리소스가 해제된다.

	pthread_create()를 사용하여 생성시 쓰레드가 종료되어도 리소스회수가 안됨!
	pthread_join()을 사용하면 자원을 반납시킬 수 있다.
	pthread_detach()는 join을 안써도 쓰레드 종료시 모든 자원을 해제해줌.

	join, detach 둘다 종료시 자원반납을 하는 점은 같은데 왜 나누어져 있을까?
	차이점은 부모 쓰레드에서 기다리느냐의 여부?
*/
int pthread_mutex_init(pthread_mutex_t * mutex, const pthread_mutex_attr *attr);
/*
	mutex	: 해당 뮤택스객체를 초기화.
	attr	: 옵션같은거("fast", "recurisev", "error checking" 의 종류가 있으며, 디폴트으로 "fast")
	- pthread_mutex_lock()   :  critical section 시작
	- pthread_mutex_unlock() :   critical section 종료
*/
pthread_mutex_destroy
pthread_mutex_lock
pthread_mutex_unlock
```
* 뮤탹스?
포크를 복제하는 것을 막기 위해서, 각 포크의 현재 상태를 뮤텍스를 이용하여 보호해주어야 합니다.

* 스레드?
각 철학자는 스레드로 구현되어 있어야 합니다.