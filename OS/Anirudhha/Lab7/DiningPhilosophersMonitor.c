#include <stdio.h>


#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#define N 5

//starvation is not handled and this is a psuedocode

monitor DiningPhilosophers {

	enum {THINKING,HUNGRY,EATING} state[N];
	condition self [N];

	void pickup(int i){
		state[i]=HUNGRY;
		test(i);
		if( state[i] != EATING ){
			self[i].wait();
		}
	}

	void putdown(int i){
		state[i] = THINKING;
		// test left and right neighbours
		test( LEFT );
		test( RIGHT );
	}

	void test(int i){
		if( state[ LEFT ] != EATING && state[i]==HUNGRY && state[ RIGHT ] != EATING ){
			state[i] = EATING;
			self[i].signal();
		}
	}

	initialization_code(){
		for (int i = 0; i < N; ++i)
		{
			state[i] = THINKING;
		}
	}
}

int main(){

	for (int i = 0; i < N; ++i)
	{
		DiningPhilosophers.pickup(i);
		EAT();
		DiningPhilosophers.putdown(i);
	}
	return 0;
}