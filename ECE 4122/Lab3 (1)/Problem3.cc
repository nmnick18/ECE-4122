using namespace std;
#include <iostream>
#include <vector>
#include <cmath>
// Integration problem from the first homework assignment
#include <omp.h>
#include <random>

using std::vector;
using namespace std;

float monte_omp(int N)
{   
    const int iNUM_THREADS = 5;

    int x1, x2, x3, z;
    int nTrial = 1;

   
    std::default_random_engine generator;
    std::uniform_real_distribution<int> distribution1(0,1);//range from 0 to 1
    std::uniform_real_distribution<int> distribution2(1,2);//range from 0 to 1
    std::uniform_real_distribution<int> distribution3(2,3);//range from 0 to 1


    double start_time = omp_get_wtime();
    long ii = 0;
    long nThreads = 0;

    long lNumSteps = 500000000;
    double dStep = 1.0 / (double)lNumSteps;

    omp_set_num_threads(iNUM_THREADS);

#pragma omp parallel
    {
        long ii;
        long iID = omp_get_thread_num();
        long n = omp_get_num_threads(); 
        int dSum = 0;
        double dx;

        x1 = distribution1(generator);
        x2 = distribution1(generator);
        x3 = distribution1(generator);
        

        z = pow((exp(x1)+x2),2)+ (3*pow(((1-x3)),2)); 

        nThreads = n; 

#pragma omp atomic //critical
    }
    // Implied barrier here at the end of the threading section

    cout << "The answer is: " << dStep << " in " << 1000.0*(omp_get_wtime() - start_time) << " millsec with Number threads = " << nThreads << endl;

    return 0;
}

int main(int argc, char* argv[]) {

    float value;
    value = monte_omp();
}                    