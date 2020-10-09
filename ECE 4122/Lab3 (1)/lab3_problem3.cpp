#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <random>

using namespace std;


void compute(int N)
{   
    const int iNUM_THREADS = 5;

    double x1, x2, x3, z;
    int trial = 1;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution1(0.0,1.0);//range from 0 to 1
    std::uniform_real_distribution<double> distribution2(1.0,2.0);//range from 1 to 2
    std::uniform_real_distribution<double> distribution3(2.0,3.0);//range from 2 to 3

    double start_time = omp_get_wtime();
    long ii = 0;
    long nThreads = 0;
    int dSum = 0;
    double dx;

    omp_set_num_threads(iNUM_THREADS);

    int i;
    #pragma omp parallel
    {
        long n = omp_get_num_threads(); 
        long t = omp_get_thread_num();

            
        #pragma omp parallel for 
        for(i = 1; i < N; i++)//int i is private by default
        {
            x1 = distribution1(generator);
            x2 = distribution2(generator);
            x3 = distribution3(generator);
            z = pow((exp(x1)+x2),2)+ (3*pow(((1-x3)),2)); 
            //cout <<"The Z:" << z << " : " << "Thread: "<< t <<endl;
        }  

        nThreads = n;         
    }

    std::cout << "The answer is: " << z << " in " << 1000.0*(omp_get_wtime() - start_time) << " millsec with Number threads = " << nThreads << std::endl;
    std::cout << "The answer is: " << x1 << " : " << x2 << " : " << x3;
    

}


int main(int argc, char* argv[]) 
{
    //N = number of Trials
    unsigned long N = strtol(argv[1], NULL, 10); 
    compute(N);
}
