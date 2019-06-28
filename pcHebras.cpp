#include "pcMonitor.hpp"
#include <sstream>
#include <chrono>
#include <ctime>



int main(int argc, char* argv[])
{

        std::istringstream ntam(argv[1]);

        int tam{};
        ntam>>tam;

        int ext{tam/5};

        pcMonitor buffer(tam);



        std::thread hilos[10];

        std::chrono::time_point<std::chrono::system_clock> start, end;


        start = std::chrono::system_clock::now();


        for(int i=0; i<5; i++)hilos[i]=std::thread(productor, ext, std::ref(buffer));
        for(int i=5; i<10; i++)hilos[i]=std::thread(consumidor, ext, std::ref(buffer));
        for(int i=0; i<10; i++)hilos[i].join();

        end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end-start;

        std::cout  << "Tiempo: " << elapsed_seconds.count()<<"secs"<<std::endl;


}
