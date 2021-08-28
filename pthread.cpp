#include <chrono>

using namespace std::chrono;
using namespace std;
 
//size of the matrix
const int N = 100;
 
//number of threads
const int NUM_THREADS = 4;

//declare variables
static int matrix1[N][N];
static int matrix2[N][N];
static long int result[N][N];
int step = 0;

//function to multiply two matrices
void* multiply(void* arg)
{
    int i, j, k;
    int thread_num = step++;
    for (i = thread_num * N / NUM_THREADS; i < (thread_num + 1) * N / NUM_THREADS; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

//function to fill the matrix with random values
void initialize(int matrix[N][N], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = rand() % 100 + 1;
        }
    }
}

//function to print a matrix to the console
void print_matrix(long int matrix[N][N])
{
    cout << "Matrix: \n";
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++)
			cout << matrix[i][j] << ", ";
		cout << "\n";
	}
}

//main function
int main()
{

    initialize(matrix1, N, N);
    initialize(matrix2, N, N);

    pthread_t * threads;
    //start time variable
    auto start = high_resolution_clock::now();

    //declaring four threads
    //pthread_t threads[NUM_THREADS];
    threads = (pthread_t *) malloc( NUM_THREADS * sizeof(pthread_t) );
 
    //creating threads and then each thread evaluate its own part
    for (int i = 0; i < NUM_THREADS; i++) {
        
        int* x;
        pthread_create(&threads[i], NULL, multiply, (void*)(x));
    }
 
    //waiting for all threads to complete then join them to the main thread
    for (int j = 0; j < NUM_THREADS; j++)
        pthread_join(threads[j], NULL);
    
    //stop time variable
    auto stop = high_resolution_clock::now();

    //calculate the time taken by the function
    auto duration = duration_cast<microseconds>(stop - start);
    
    //print result matrix
    print_matrix(result);
    //print time taken
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

 
    return 0;
}
