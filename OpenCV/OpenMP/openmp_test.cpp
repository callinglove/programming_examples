#include <iostream>
#include <time.h>
#include <omp.h>

using namespace std;

void Test1(int argc, char* argv[])
{
    // clock_t t1 = clock();
    double t1 = omp_get_wtime();
    #pragma omp parallel for num_threads(4) // 对for循环进行并行，设置线程组中成员个数为4
    for (int i=0;i<8;i++)
    {
        int k = omp_get_thread_num(); // 获得每个线程的ID
        int n = omp_get_num_threads(); // 获得线程组线程个数
        // cout << "enter " << k << "/" << n << endl;
        {
            long a = 0;
            for (int j = 0; j < 100000; j++)
            {
                a++;
            }
        }
        // cout << k << "/" << n << " is over" << endl;
    }
    // clock_t t2 = clock();
    double t2 = omp_get_wtime();
    std::cout<<"time: "<<t2-t1<<std::endl;
}

/*
在#pragma omp parallel for 后面加上了 reduction(+:sum)，
它的意思是告诉编译器：下面的for循环你要分成多个线程跑，
但每个线程都要保存变量sum的拷贝，循环结束后，所有线程把
自己的sum累加起来作为最后的输出。
*/
void Test2(int argc, char *argv[])
{
    int sum = 0;
    int a[10] = {1,2,3,4,5,6,7,8,9,10};

#pragma omp parallel for reduction(+:sum)
    for (int i=0;i<10;i++)
        sum = sum + a[i];

    std::cout<<"sum: "<<sum<<std::endl;
}

// reduction虽然很方便，但它只支持一些基本操作，比如+,-,*,&,|,&&,||等。
// 有些情况下，我们既要避免race condition，但涉及到的操作又超出了reduction
// 的能力范围，应该怎么办呢？这就要用到openMP的另一个工具，critical。
// 来看下面的例子，该例中我们求数组a的最大值，将结果保存在max里。

void Test3(int argc, char *argv[])
{
    int max = 0;
    int a[10] = {11,2,33,49,113,20,321,250,689,16};

#pragma omp parallel for
    for (int i=0;i<10;i++)
    {
        int temp = a[i];
#pragma omp critical
        {
            if (temp > max)
                max = temp;
        }
    }
    std::cout<<"max: "<<max<<std::endl;
}

/*
上例中，for循环还是被自动分成N份来并行执行，但我们用#pragma omp critical将 
if (temp > max) max = temp 括了起来，它的意思是：各个线程还是并行执行for
里面的语句，但当你们执行到critical里面时，要注意有没有其他线程正在里面执行，
如果有的话，要等其他线程执行完再进去执行。这样就避免了race condition问题，
但显而易见，它的执行速度会变低，因为可能存在线程等待的情况。
*/

/*
#pragma omp parallel sections
{
    #pragma omp section
    {
        function1();
    }
　　#pragma omp section
    {
        function2();
    }
}
*/

// eval pi: pi = 4 / 1 - 4 / 3 + 4 / 5 - 4 / 7 + 4 / 9 - 4 / 11 + 4 / 13 - ...
void Test5(int argc, char* argv[])
{
    double factor = 1;
    double sum = 0.0;
    long n = 0xFFFFFFF;
    int thread_cnt = 2 * omp_get_num_procs();//获得处理器个数
    cout << thread_cnt << endl;

#pragma omp parallel for num_threads(thread_cnt) reduction(+:sum) private(factor)
    for (long i = 0; i < n; i++)
    {
        if (i % 2 == 0)
            factor = 1.0;
        else
            factor = -1.0;
        sum += factor / (2 * i + 1);
    }
    double pi_approx = 4.0*sum;

    cout << pi_approx << endl;
}

int main(int argc, char *argv[])
{
    Test1(argc, argv);
    // Test5(argc, argv);
    
    #pragma omp parallel
    {
        cout << "Hello World" << endl;
    }

    return 0;
}