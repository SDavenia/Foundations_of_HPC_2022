#include <iostream>
#include <chrono>
#include <vector>
#include <random>
/*
Try to asses time of transpose with strided read/write.
It appears that when the strided read is used on size 5000 the second version takes approximately less

If you increase to larger values behavious becomes erratic (already at around 6000, and the second one seems to take longer).
** THIS DOES NOT COMPILE ON ORFEO FOR SOME REASON **

*/


class CMatrix{
    int nrow;
    int ncol;
public:
    std::vector<int> data;
    // Constructors
    CMatrix(int r, int c){
        //std::cout<<"Non empty constructor is being called\n";
        nrow = r;
        ncol = c;
        data.resize(r*c);
    }
    CMatrix(){
        //std::cout<<"Empty constructor is being called\n";
        nrow = 0;
        ncol = 0;
        data.clear();
    }
    // Function to print matrix
    void print();
    // Function to fill with random numbers the matrix;
    void random_fill();

    // We write two transpose, the first reads in order and writes strided
    CMatrix transpose_slow();
    CMatrix transpose();
};

int main()
{
    int nrow{6000}, ncol{6000};
    
    {CMatrix arr(nrow, ncol);
    arr.random_fill();
    auto t_start = std::chrono::steady_clock::now(); 
    auto tarr = arr.transpose_slow();
    auto t_end = std::chrono::steady_clock::now(); 
    auto total = std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count();
    std::cout<<"Using the strided write the time it took is: "<<total<<"\n";}


    {CMatrix arr2(nrow, ncol);
    arr2.random_fill();
    auto t_start2 = std::chrono::steady_clock::now(); 
    auto tarr2 = arr2.transpose();
    auto t_end2 = std::chrono::steady_clock::now(); 
    auto total2 = std::chrono::duration_cast<std::chrono::milliseconds>(t_end2-t_start2).count();
    std::cout<<"Using the strided read the time it took is: "<<total2<<"\n";}
    
}


void CMatrix::print(){
    for (int i=0; i<nrow; i++){
        for(int j=0; j<ncol; j++){
            std::cout<<data[j + i*ncol]<<" ";
        }
        std::cout<<"\n";
    }
}

void CMatrix::random_fill(){
    /*
    Fills the matrix with random numbers between 0 and 10.
    */
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    std::uniform_int_distribution<int> dist {1, 52};
    
    auto gen = [&dist, &mersenne_engine](){
                   return dist(mersenne_engine);
               };

    
    std::generate(data.begin(), data.end(), gen);
    /*
    constexpr auto low_bound = 0;
	constexpr auto up_bound = 10;
    //take the seed from current time 
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine dre(seed);//engine
    std::uniform_int_distribution<int> di(low_bound,up_bound);//distribution
    std::generate(data.begin(), data.end(), [&](){ return di(dre);});//fill
    */
}

CMatrix CMatrix::transpose_slow(){
    CMatrix tresult(ncol, nrow);
    for(int i = 0; i < nrow; i++){
        for(int j = 0; j < nrow; j++){
            // std::cout<< data[j + i*ncol]<<"\n"; 
            tresult.data[i + j*nrow] = data[j + i*ncol];
        }
    }

    return tresult;
}

CMatrix CMatrix::transpose(){
    CMatrix tresult(ncol, nrow);
    for(int j = 0; j < ncol; j++){
        for(int i = 0; i < ncol; i++){
            //std::cout<<data[j + i*ncol]<<"\n";
            tresult.data[i + j*nrow] = data[j + i*ncol];
        }
    }
    return tresult;
}