#include <pthread.h>

pthread_cond_t cond1, cond2, cond3;
pthread_mutex_t lock;
int loops = 5;
int xkh_cnt, zkh_cnt;

void showch(ch) {
    for(int i=0;i<loops;i++){
        switch (ch)
        {
        case '(':
            pthread_mutex_lock(&lock);
            putch('(');
            xkh_cnt++;
            pthread_mutex_unlock(&lock);
            break;
        case ')':
            pthread_mutex_lock(&lock);
            while(xkh_cnt == 0)
                pthread_cond_wait(&cond1, &lock);
            putch(')');
            xkh_cnt--;
            if(zkh_cnt) pthread_cond_broadcast(&cond3);
            else pthread_cond_broadcast(&cond2);
            pthread_mutex_unlock(&lock);
            break;
        case '[':
            pthread_mutex_lock(&lock);
            while(xkh_cnt)
                pthread_cond_wait(&cond2, &lock);
            putch('[');
            zkh_cnt++;
            pthread_cond_broadcast(&cond3);
            pthread_mutex_unlock(&lock);
            break;
        case ']':
            pthread_mutex_lock(&lock);
            while(zkh_cnt == 0 || xkh_cnt)
                pthread_cond_wait(&cond3, &lock);
            putch('[');
            zkh_cnt++;
            pthread_cond_broadcast(&cond2);
            pthread_mutex_unlock(&lock);
            break;
        }
    }
        
}


int main() {

    pthread_create();

    return 0;
}
