#include<condition_variable>
#include<thread>
#include<mutex>
#include <iostream>



class pcMonitor
{

public:

        explicit pcMonitor(int n): capacidad{n},putptr{},takeptr{},cont{},
        buffer{new int[n]}
        {}

        ~pcMonitor(){delete [] buffer;}

        void depositar(int dato)
        {
                std::unique_lock<std::mutex> lock(cerrojo);


                while(cont==capacidad){notfull.wait(lock);}

                buffer [putptr] = dato;
                putptr=(putptr+1) % capacidad;
                ++cont;

                notempty.notify_one();

        }

        int extraer()
        {
                std::unique_lock<std::mutex> lock(cerrojo);

                while(cont==0){notempty.wait(lock);}

                int res = buffer[takeptr];
                takeptr = (takeptr + 1) % capacidad;
                --cont;

                notfull.notify_one();

                return res;
        }

private:

        int* buffer;
        int capacidad, takeptr, putptr , cont;

        std::mutex cerrojo;

        std::condition_variable notfull;
        std::condition_variable notempty;

};


void productor(int produ, pcMonitor& buffer)
 {
         for(int i=0; i<produ; ++i)
         {
                 buffer.depositar(i);
                //  std::cout<<"Productor "<<i<<" inserto "<<i<<std::endl;
         }
 }

 void consumidor(int extr, pcMonitor& buffer)
 {
         for(int i=0; i<extr; ++i)
         {
                 int valor = buffer.extraer();
                //  std::cout<<"Consumidor "<<i<<" extrajo "<<i<<std::endl;
         }
 }
