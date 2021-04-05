/*
 *  compile command : g++ -std=c++11 -pthread observer1.cpp
 */

#include<iostream>
#include<memory>
#include<thread>
#include<chrono>


// Observer thred
std::thread observer;

void observe(std::weak_ptr<int> wp) {
	//Start observer thread
	observer = std::thread([wp](){
			while(true) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
				
				//Try acquiring a shared_ptr from weak_ptr
				if(std::shared_ptr<int> p = wp.lock()) {
					//Success
					std::cout << "Observing: " << *p << "\n";
				} else {
					    //The managed object is destroyed. 
					    std::cout << "Stop\n";
					    break;
				}
			}
		}
	);
}

int main() 
{
	{ 
		//Block Start  
		auto sp = std::shared_ptr<int>(new int());
		
		//Create a weak_ptr<int> from sp for observing
		observe(sp);  

		//Wait few seconds
		 std::this_thread::sleep_for(std::chrono::seconds(5));

		 //shared_ptr is destroyed and the
		 // managed object is deleted when
		 // block ends
 	}

	//Wait for the observer thread to end
	 observer.join();
	 return 0;
}
