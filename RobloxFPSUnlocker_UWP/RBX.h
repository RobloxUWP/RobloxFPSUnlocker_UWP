#pragma once

// define roblox namespace which i store roblox classes in
namespace RBX {

	// define roblox task scheduler class scaffolding
	// generated using ReclassEx 32bit https://github.com/ajkhoury/ReClassEx/releases/tag/v1.2.0.0
	class TaskScheduler {
	private:
		char pad_0x0000[0x118]; //0x0000
	public:
		double Framerate; //0x0118 
		// delay per each frame (default: 0.01667)
		// TODO: Use offset signature to find framerate in task scheduler

	public: // functions
		static TaskScheduler* Singleton() {
			// get the roblox Singleton function for task scheduler then cast to task schduler scaffold
			// you can find this function by locating the SchedulerRate string in cheat engine
			// it should be directly after that string if u xref the address
			static uintptr_t rSchedulerSingletonAddr = findSig("55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 83 EC 14 56 A1 ? ? ? ? 33 C5 50 8D 45 F4 64 A3 ? ? ? ? 64 A1 ? ? ? ? 8B 08 A1 ? ? ? ? 3B 81 ? ? ? ? 7F 2B A1 ? ? ? ? 8B 4D F4 64 89 0D ? ? ? ? 59 5E 8B E5 5D C3 8D 4D E4 E8 ? ? ? ? 68 ? ? ? ? 8D 45 E4 50 E8 ? ? ? ? 68 ? ? ? ? E8 ? ? ? ? 83 C4 04 83 3D ? ? ? ? FF 75 BF 68 ? ? ? ? C7");

			// call function and return task scheduler singleton
			return CallFunc<TaskScheduler*>(rSchedulerSingletonAddr);
		}

		static void SetFPS(double fps) {
			// get task scheduler singleton
			TaskScheduler* scheduler = Singleton();

			// set fps to how long between frames (1/fps)
			scheduler->Framerate = 1 / fps;
		}
	};
}