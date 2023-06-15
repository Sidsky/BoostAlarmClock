#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <thread>

using namespace boost::asio;

template <typename T>
T add(T&& a, T&& b) {
    return a+b;
}

int main() {
    io_service ioService1;
    io_service ioService2;

    steady_timer timer1 (ioService1, std::chrono::seconds{3});

    timer1.async_wait([](const boost::system::error_code &ec){
        std::cout<<"3 seconds completed\n";
    });

    steady_timer timer2 (ioService2, std::chrono::seconds{4});

    timer2.async_wait([](const boost::system::error_code &ec){
        std::cout<<"4 seconds completed\n";
    });

    std::thread t1 ([&ioService1](){ioService1.run();});
    std::thread t2 ([&ioService2](){ioService2.run();});
    t1.join();
    t2.join();

    std::cout<<add(2, 3)<<std::endl;

    // ioService.run() is like butler; it runs in its own thread. If you call run twice, it is equivalent to 2 butlers who
    // will run the same service.
    return 0;

}
