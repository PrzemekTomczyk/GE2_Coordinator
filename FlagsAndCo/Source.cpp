#include <iostream>
#include <mutex>
#include <thread>
#include <mutex>

const int n = 5;
int arrive[n];
int continue_n[n];
std::mutex coutMutex;

void Coordinator()
{
	while (true)
	{
		for (size_t i = 0; i < n; i++)
		{
			while (arrive[i] != 1)
			{
				continue;
			}
			arrive[i] = 0;
		}
		for (size_t i = 0; i < n; i++)
		{
			continue_n[i] = 1;
		}
	}
}

void Worker(int i)
{
	while (true)
	{
		coutMutex.lock();
		std::cout << "Worker task " << i << std::endl;
		coutMutex.unlock();

		arrive[i] = 1;
		while (continue_n[i] != 1)
		{
			continue;
		}
		continue_n[i] = 0;
	}
}

int main()
{
	for (int i = 0; i < n; i++)
	{
		arrive[i] = 0;
		continue_n[i] = 0;
	}


	std::thread worker1{ Worker, 0 };
	std::thread worker2{ Worker, 1 };
	std::thread worker3{ Worker, 2 };
	std::thread worker4{ Worker, 3 };
	std::thread worker5{ Worker, 4 };

	std::thread coordinator{ Coordinator };





	worker1.join();
	worker2.join();
	worker3.join();
	worker4.join();
	worker5.join();
	coordinator.join();

	return EXIT_SUCCESS;
}