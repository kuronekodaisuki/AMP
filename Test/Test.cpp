// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>
#include<vector>
#include <amp.h>

using concurrency::accelerator;

std::vector<accelerator> findAccelerators(){
	std::vector<accelerator> accels;
	accels = accelerator::get_all();

	for (int i = 0; i<accels.size(); i++){
		std::wcout << i + 1 << "th device = " << accels[i].get_description() << "\n";
	}

	//emulatorのアクセラレータを削除します
	accels.erase(std::remove_if(accels.begin(), accels.end(), [](accelerator& accel){return accel.get_is_emulated(); }), accels.end());

	return accels;
}

void getAccelDiscription(const accelerator& accel){
	std::wcout << "accelerator: " << accel.get_description() << std::endl;
	std::cout << "\tversion of the accelerator: " << accel.get_version() << std::endl;
	std::cout << "\tmemory: " << accel.get_dedicated_memory() / 1024. / 1000. << " [GB]" << std::endl;;
	std::cout << "\tis supporting double precision: " << (accel.get_supports_double_precision() ? "yes" : "no") << std::endl;
	std::cout << "\tis attached to a display: " << (accel.get_has_display() ? "yes" : "no") << std::endl;
	std::cout << "\tis supporting cpu shared memory: " << (accel.get_supports_cpu_shared_memory() ? "yes" : "no") << std::endl;
	return;
}

int main(int argc, char* argv[])
{
	std::vector<accelerator> gpu = findAccelerators();

	for (size_t i = 0; i < gpu.size(); i++)
	{
		getAccelDiscription(gpu[i]);
	}
	return 0;
}

