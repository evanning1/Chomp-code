#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <chrono>
#include <string.h>
#include <cmath>

using namespace std;

list<long long int> baseprimes;
int baseprimeslist;
list<long long int> primes;
long long int primecount = 0;
const long long int groupsize = 6000000; 
const long long int arrsize = 1000000; 
const long long int firstsize = 3000; //approx sqrt of groupsize
bool arr1 [arrsize];
bool arr5 [arrsize];

void print(){ //to print all the primes, uncomment all the primes.push_back
    for(list<long long int>::iterator i = primes.begin(); i!= primes.end(); ++i){
        std::cout << *i << " ";
    }
}

void printbase(){
    for(list<long long int>::iterator i = baseprimes.begin(); i!= baseprimes.end(); ++i){
        std::cout << *i << " ";
    }
}

void countprimes(){
    long long int counter = 0;
    for(list<long long int>::iterator i = primes.begin(); i!= primes.end(); ++i){
        counter++;
    }
    cout << counter;
}

void firstsieve(){
    memset(arr1, false, arrsize);
    memset(arr5, false, arrsize);
    long long int q = 5;
    bool modone = false;
    while(q<firstsize){
        if(modone == true){
            if(arr1[(q-1)/6] == false){
                baseprimes.push_back(q);
                primecount++;
                baseprimeslist++;
                /*primes.push_back(q);*/

                long long int iter1 = (q*q-1)/6;
                long long int iter5 = (q*q+4*q-5)/6;
                while(iter1<(firstsize/6)){
                    arr1[iter1] = true;
                    iter1+=q;
                }
                while(iter5<(firstsize/6)){
                    arr5[iter5] = true;
                    iter5+=q;
                }
            }
            q+=4;
            modone = false;
        }

        if(modone == false){
            if(arr5[(q-5)/6] == false){
                baseprimes.push_back(q);
                primecount++;
                baseprimeslist++;
                /*primes.push_back(q);*/

                long long int iter1 = (q*q-1)/6;
                long long int iter5 = (q*q+2*q-5)/6;
                while(iter1<(firstsize/6)){
                    arr1[iter1] = true;
                    iter1+=q;
                }
                while(iter5<(firstsize/6)){
                    arr5[iter5] = true;
                    iter5+=q;
                } 
            }
            q+=2;
            modone = true;
        }
    }
}

struct arg{
    long long int threads;
    long long int ID;
    long long int loop;
    long long int root;
};

void *sieve(void* args){
    std::chrono::steady_clock::time_point threadstart = std::chrono::steady_clock::now();
    arg* tmp = (arg*) args;
    long long int startindex = (tmp->ID)*arrsize/(tmp->threads);
    long long int len = arrsize/(tmp->threads);
    long long int start = (tmp->loop)*groupsize + (tmp->ID)*groupsize/(tmp->threads);

    for(list<long long int>::iterator i = baseprimes.begin(); i!= baseprimes.end(); ++i){
        long long int temp = start%(*i);
        long long int multiple = start-temp;

        long long int modulo = (*i)%6;
        long long int div = (*i-modulo)/6;

        long long int modsix = multiple%6;
        long long int tempsix = temp/6;
        if(modsix != 0){
            tempsix = (temp+(6-temp%6))/6;
        }

        long long int idone = startindex-tempsix;
        long long int idfive = startindex-tempsix;

        if(modulo == 1){/*7, 13, 19, 31, etc*/

            if(modsix == 0){
                idone += div;
                idfive += 5*div;
            }
            else if(modsix == 1){
                idone += (6*div+1);
                idfive += 4*div;
            }
            else if(modsix == 2){
                idone += (5*div+1);
                idfive += 3*div;
            }
            else if(modsix == 3){
                idone += (4*div+1);
                idfive += 2*div;
            }
            else if(modsix == 4){
                idone += (3*div+1);
                idfive += 1*div;
            }
            else if(modsix == 5){
                idone += (2*div+1);
                idfive += (6*div+1);
            }
        }

        if(modulo == 5){/*5, 11, 17, 23, etc*/

            if(modsix == 0){
                idone += 5*(div+1)-1;
                idfive += div;
            }
            else if(modsix == 1){
                idone += (6*(div+1)-1);
                idfive += (2*(div+1)-1);
            }
            else if(modsix == 2){
                idone += (div+1);
                idfive += (3*(div+1)-1);
            }
            else if(modsix == 3){
                idone += 2*(div+1);
                idfive += (4*(div+1)-1);
            }
            else if(modsix == 4){
                idone += 3*(div+1);
                idfive += (5*(div+1)-1);
            }
            else if(modsix == 5){
                idone += 4*(div+1);
                idfive += (6*(div+1)-1);
            }
        }
        while(idone<(len+startindex)){
            arr1[idone] = true;
            idone+=(*i);
        }
        while(idfive<(len+startindex)){
            arr5[idfive] = true;
            idfive+=(*i);
        }
    }
    std::chrono::steady_clock::time_point threadend = std::chrono::steady_clock::now();
    std::cout << tmp->ID << " time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(threadend - threadstart).count() << "[µs]" << std::endl;
    pthread_exit(NULL);
}

void primesieve(long long int threads, long long int lim){
    pthread_t thread[threads];
    int x;
    arg arglist [threads];
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    firstsieve();
    long long int j = 0;
    long long int root = ceil(sqrt(lim));
    for(int ppp = 0; ppp<(lim/groupsize); ppp++){
        memset(arr1, false, arrsize);
        memset(arr5, false, arrsize);
        for(int j = 0; j<threads; j++){
            arglist[j].threads = threads;
            arglist[j].ID = j;
            arglist[j].loop = ppp;
            x = pthread_create(&thread[j], NULL, &sieve, (void*) &arglist[j]);
            if(x != 0) {
                            printf("Error: pthread_create() failed\n");
                            exit(EXIT_FAILURE);
                }
        }
        for(long long int j = 0; j<threads; j++){
            x = pthread_join(thread[j], NULL);
        }
        for(long long int p = 0; p<(arrsize); p++){
            if(arr1[p] == false){
                if((ppp*groupsize+6*p+1)!=1){
                    primecount++;;
                    /*primes.push_back(ppp*groupsize+6*p+1);*/

                    if(ppp*groupsize+6*p+1<root && ppp*groupsize+6*p+1>firstsize){
                        baseprimes.push_back(ppp*groupsize+6*p+1);
                    }
                }
            }
            if(arr5[p] == false){
                primecount++;;
                /*primes.push_back(ppp*groupsize+6*p+5);*/

                if(ppp*groupsize+6*p+5<root && ppp*groupsize+6*p+1>firstsize){
                    baseprimes.push_back(ppp*groupsize+6*p+5);
                }
            }
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
}

int main(int argc, char* argv[]){
    long long int threads = atoi(argv[1]);
    long long int lim = strtoull(argv[2], NULL, 10);
    primesieve(threads, lim);
    primecount+=2;
    cout << primecount;
    return 0;
}