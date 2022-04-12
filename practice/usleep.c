#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main(){
	struct timeval my_time;
	gettimeofday(&my_time, NULL);
	printf("time: %ld\n", my_time.tv_sec);
	printf("micro time: %d\n", my_time.tv_usec);
	// while(1)
	// {
	// 	printf("I Print This every 1 second!\n");
	// 	usleep(1 * 1000000);
	// }
}
