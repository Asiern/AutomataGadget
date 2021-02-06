#include <Windows.h>
#include <TlHelp32.h>
#include "NierHook.hpp"

//Hook to NieR:Automata process
void NieRHook::_hook(void)
{
	DWORD ID = this->_pID;
	while (ID <= 0)
	{
		ID = this->_getProcessID();
	}
	this->_pID = ID;
	this->_baseAddress = this->_getModuleBaseAddress(ID, L"NieRAutomata.exe");
	this->_hooked = true;
}
//unHook NieR:Automata
void NieRHook::_unHook(void)
{
	this->_hooked = false;
	this->_baseAddress = 0;
	this->_entityAddress = 0;
	this->_pID = 0;
	this->Health = 0;
	this->MaxHealth = 0;
	this->Xpos = 0.000000;
	this->Ypos = 0.000000;
	this->Zpos = 0.000000;
	this->EXP = 0;
	this->Funds = 0;
	this->Level = 0;
	this->InfiniteAirDash(false);
	this->InfiniteDoubleJump(false);
	this->IgnoreUpgradeMaterials(false);
	this->NoCLip(false);
	this->NoCooldown(false);
	this->setGameSpeed(1);
}

//Search for window named "NieR:Automata" returns: process ID
DWORD NieRHook::_getProcessID(void)
{
	//Search game window
	HWND hwnd = FindWindowA(NULL, "NieR:Automata");
	if (hwnd == NULL)
	{
		//return if game window not found
		return 0;
	}
	DWORD pID;													  //Process ID
	GetWindowThreadProcessId(hwnd, &pID);						  //Get Process ID
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID); //Open process
	if (pHandle == INVALID_HANDLE_VALUE)
	{
		//return if couldn't open the process
		return 0;
	}
	return pID;
}
//Find modules in NieR:Automata process returns: memory address of module
uintptr_t NieRHook::_getModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap); //Close handle to prevent memory leaks
	return modBaseAddr;
}

void NieRHook::_updatePosition(void)
{
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	float Xpos;
	float Ypos;
	float Zpos;
	uintptr_t XAddress = static_cast<uintptr_t>((DWORD)this->_entityAddress) + 0x50;
	uintptr_t YAddress = static_cast<uintptr_t>((DWORD)this->_entityAddress) + 0x54;
	uintptr_t ZAddress = static_cast<uintptr_t>((DWORD)this->_entityAddress) + 0x58;
	ReadProcessMemory(pHandle, (LPCVOID)XAddress, &Xpos, sizeof(Xpos), NULL);
	ReadProcessMemory(pHandle, (LPCVOID)YAddress, &Ypos, sizeof(Ypos), NULL);
	ReadProcessMemory(pHandle, (LPCVOID)ZAddress, &Zpos, sizeof(Zpos), NULL);
	this->Xpos = Xpos;
	this->Ypos = Ypos;
	this->Zpos = Zpos;
}

void NieRHook::_updateHealth(void)
{
	int h = 0;
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	ReadProcessMemory(pHandle, (LPCVOID)(this->_entityAddress + 0x858), &h, sizeof(h), NULL);
	this->Health = h;
	ReadProcessMemory(pHandle, (LPCVOID)(this->_entityAddress + 0x85c), &h, sizeof(h), NULL);
	CloseHandle(pHandle); //Close handle to prevent memory leaks
	this->MaxHealth = h;
}

void NieRHook::_updateEntity(void)
{
	//Get entity address from pointer at offset 0x16053B8
	uintptr_t entityAdd = 0;
	uintptr_t entityAddPointer = this->_baseAddress + 0x16053B8;
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	ReadProcessMemory(pHandle, (LPCVOID)entityAddPointer, &entityAdd, sizeof(entityAdd), NULL);
	CloseHandle(pHandle); //Close handle to prevent memory leaks
	this->_entityAddress = entityAdd;
}

void NieRHook::_updateLevel(void)
{
	int lvl = 0;
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	ReadProcessMemory(pHandle, (LPCVOID)(this->_entityAddress + 0x14BC), &lvl, sizeof(lvl), NULL);
	CloseHandle(pHandle); //Close handle to prevent memory leaks
	this->Level = lvl;
}

void NieRHook::_updateFunds(void)
{
	int funds = 0;
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	ReadProcessMemory(pHandle, (LPCVOID)(this->_baseAddress + 0x197C4C0), &funds, sizeof(funds), NULL);
	CloseHandle(pHandle); //Close handle to prevent memory leaks
	this->Funds = funds;
}

void NieRHook::_updateEXP(void)
{
	int exp = 0;
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	ReadProcessMemory(pHandle, (LPCVOID)(this->_baseAddress + 0x1984670), &exp, sizeof(exp), NULL);
	CloseHandle(pHandle); //Close handle to prevent memory leaks
	this->EXP = exp;
}
//Fill memory with no Operations
void NieRHook::Nop(BYTE* destination, unsigned int size, HANDLE hProcess)
{
	BYTE* nopArray = new BYTE[size];
	memset(nopArray, 0x90, size);
	Patch(destination, nopArray, size, hProcess);
	delete[] nopArray;
}
//Fill memory with custom values
void NieRHook::Patch(BYTE* destination, BYTE* src, unsigned int size, HANDLE hProcess)
{
	DWORD oldprotection;
	VirtualProtectEx(hProcess, destination, size, PAGE_EXECUTE_READWRITE, &oldprotection);
	WriteProcessMemory(hProcess, destination, src, size, nullptr);
	VirtualProtectEx(hProcess, destination, size, oldprotection, &oldprotection);
}

void NieRHook::hookStatus(void)
{
	if (this->_pID != this->_getProcessID())
	{
		this->_unHook();
	}
}
//Update Player Attributes
void NieRHook::update(void)
{
	_updateEntity();
	_updateHealth();
	_updatePosition();
	_updateLevel();
	_updateFunds();
	_updateEXP();
}

float NieRHook::getXPosition(void)
{
	return this->Xpos;
}

float NieRHook::getYPosition(void)
{
	return this->Ypos;
}

float NieRHook::getZPosition(void)
{
	return this->Zpos;
}

int NieRHook::getFunds(void)
{
	return this->Funds;
}

int NieRHook::getEXP(void)
{
	return this->EXP;
}

void NieRHook::setPosition(float X, float Y, float Z)
{
	NoCLip(true); //Enable noclip to teleport
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	//Write values at offsets 0x50, 0x54, 0x58 with X,Y,Z
	WriteProcessMemory(pHandle, (LPVOID)(this->_entityAddress + 0x50), &X, sizeof(X), NULL);
	WriteProcessMemory(pHandle, (LPVOID)(this->_entityAddress + 0x54), &Y, sizeof(Y), NULL);
	WriteProcessMemory(pHandle, (LPVOID)(this->_entityAddress + 0x58), &Z, sizeof(Z), NULL);
	Sleep(500);
	NoCLip(false); //Disable noclip
	CloseHandle(pHandle);
}

void NieRHook::setHealth(int health)
{
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	//Write Memory at offset 0x858 to set current health
	WriteProcessMemory(pHandle, (LPVOID)(this->_entityAddress + 0x858), &health, sizeof(health), NULL);
	CloseHandle(pHandle);
}

void NieRHook::setGameSpeed(float speed)
{
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	//Write memory at offset 0x160E6D8 to set game speed (default 1.0 float)
	WriteProcessMemory(pHandle, (LPVOID)(this->_baseAddress + 0x160E6D8), &speed, sizeof(speed), NULL);
	CloseHandle(pHandle);
}

void NieRHook::NoCooldown(bool enabled)
{
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	if (enabled)
	{ //Enable No cooldown
		//Set memory at offset 0x23821F = 90 90 90 90
		Nop((BYTE*)(this->_baseAddress + 0x23821F), 9, pHandle);
	}
	else
	{ //Disable No cooldown
		//Set memory at offsets 0x1354B1 & 0x135758 = previous values
		Patch((BYTE*)(this->_baseAddress + 0x23821F), (BYTE*)"\xF3\x0F\x11\x84\xC3\x24\x6A\x01\x00", 9, pHandle);
	}
	CloseHandle(pHandle);
}

void NieRHook::InfiniteAirDash(bool enabled)
{

	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	if (enabled)
	{ //Enable Inf Air Dash
		//Set memory at offset 0x1E2E5D = 90 90 90 90 90 90 90 90 90 90
		Nop((BYTE*)(this->_baseAddress + 0x1E2E89), 10, pHandle);
	}
	else
	{ //Disable Inf Air Dash
		//Set memory at offset 0x1E2E5D = previous values
		Patch((BYTE*)(this->_baseAddress + 0x1E2E89), (BYTE*)"\xC7\x83\x88\x0A\x01\x00\x01\x00\x00\x00", 10, pHandle);
	}
	CloseHandle(pHandle);
}

void NieRHook::IgnoreUpgradeMaterials(bool enabled)
{
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	if (enabled)
	{ //Enable Ignore Upgrade Materials
		//Set memory at offset 0x5EE5CE = 90 90 90 to disable Weapon
		Nop((BYTE*)(this->_baseAddress + 0x5EE5CE), 3, pHandle);
		//Set memory at offset 0x5EE7F0 = 90 90 90 to disable Pod
		Nop((BYTE*)(this->_baseAddress + 0x5EE7F0), 3, pHandle);
	}
	else
	{ //Disable Ignore Upgrade Materials
		//Set memory at offset 0x5EE5CE = previous values
		Patch((BYTE*)(this->_baseAddress + 0x5EE5CE), (BYTE*)"\x41\x3B\xC2\x7C\x31", 5, pHandle);
		//Set memory at offset 0x5EE7F0 = previous values
		Patch((BYTE*)(this->_baseAddress + 0x5EE7F0), (BYTE*)"\x83\xFB\xFF", 3, pHandle);

	}
	CloseHandle(pHandle);
}
/*
	Add item to inventory
	If Item is not in the inventory, Creates a new Item on memory
	returns: true if successful and false if not
*/
bool NieRHook::addItem(int ID, int number)
{
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	uintptr_t Address = this->_baseAddress + 0x197C4C4;
	uintptr_t emptySlot = 0;
	unsigned int currentID;
	if (!this->_hooked)
	{
		return false;
	}
	while (Address <= this->_baseAddress + 0x197CE18)
	{
		ReadProcessMemory(pHandle, (LPVOID)Address, &currentID, sizeof(currentID), NULL);
		if (ID == currentID)
		{																						 //Item found on memory
			WriteProcessMemory(pHandle, (LPVOID)(Address + 0x8), &number, sizeof(number), NULL); //Set level
			return true;
		}
		else if (emptySlot == 0 && currentID == 0xffffffff)
		{ //Get empty slot address
			emptySlot = Address;
		}
		Address += 0xC; //Go to the next slot
	}
	if (emptySlot == 0)
	{ //empty slot == 0 => no free slots on memory
		return false;
	}
	//Item not found on memory, create on empty slot
	WriteProcessMemory(pHandle, (LPVOID)(emptySlot), &ID, sizeof(ID), NULL);			   //Set level
	WriteProcessMemory(pHandle, (LPVOID)(emptySlot + 0x8), &number, sizeof(number), NULL); //Set level
	CloseHandle(pHandle);
}

bool NieRHook::removeItem(int ID)
{
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	uintptr_t Address = this->_baseAddress + 0x197C4C4;
	unsigned int currentID;
	int emptySlotID = 0xffffffff;
	if (!this->_hooked)
	{
		//Not hooked return
		return false;
	}
	while (Address <= this->_baseAddress + 0x197CE18)
	{
		ReadProcessMemory(pHandle, (LPVOID)Address, &currentID, sizeof(currentID), NULL);
		if (ID == currentID) //Item found
		{
			//Remove item from memory																				 //Item found on memory
			WriteProcessMemory(pHandle, (LPVOID)(Address), &emptySlotID, sizeof(emptySlotID), NULL); //Set level
			return true;
		}
		Address += 0xC; //Go to the next slot
	}
	return false;
}

/*
	Add weapon to memory by ID
	returns: true if successful and false if not
*/
bool NieRHook::addWeapon(int ID, int level)
{
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	uintptr_t Address = this->_baseAddress + 0x197DCC4;
	uintptr_t emptySlot = 0;
	unsigned int currentID;
	if (!this->_hooked)
	{
		return false; //Return if not hooked
	}
	while (Address <= this->_baseAddress + 0x197DFBC)
	{
		ReadProcessMemory(pHandle, (LPVOID)Address, &currentID, sizeof(currentID), NULL);
		if (ID == currentID)
		{																					   //Weapon found on memory
			WriteProcessMemory(pHandle, (LPVOID)(Address + 0x4), &level, sizeof(level), NULL); //Set level
			return true;
		}
		if (emptySlot == 0 && currentID == 0xffffffff)
		{ //Get empty slot address
			emptySlot = Address;
		}
		Address += 0x14; //Go to the next slot
	}
	if (emptySlot == 0)
	{ //empty slot == 0 => no free slots on memory
		return false;
	}
	//Weapon not found on memory
	WriteProcessMemory(pHandle, (LPVOID)(emptySlot), &ID, sizeof(ID), NULL);			 //Set Weapon ID
	WriteProcessMemory(pHandle, (LPVOID)(emptySlot + 0x4), &level, sizeof(level), NULL); //Set level, level at offset 0x4 from ID
	CloseHandle(pHandle);
	return true;
}

bool NieRHook::removeWeapon(int ID)
{
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	uintptr_t Address = this->_baseAddress + 0x197DCC4;
	uintptr_t emptySlotID = 0xffffffff;
	unsigned int currentID;
	if (!this->_hooked)
	{
		return false; //Return if not hooked
	}
	while (Address <= this->_baseAddress + 0x197DFBC)
	{
		ReadProcessMemory(pHandle, (LPVOID)Address, &currentID, sizeof(currentID), NULL);
		if (ID == currentID)
		{																							 //Weapon found on memory
			WriteProcessMemory(pHandle, (LPVOID)(Address), &emptySlotID, sizeof(emptySlotID), NULL); //Set level
			return true;
		}
		Address += 0x14; //Go to the next slot
	}
	return false;
}

void NieRHook::setHUDOpacity(float opacity)
{
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, this->_pID);
	WriteProcessMemory(pHandle, (LPVOID)(this->_baseAddress + 0x19861AC), &opacity, sizeof(opacity), NULL);
	CloseHandle(pHandle);
}

void NieRHook::setColor(float R, float G, float B)
{
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, this->_pID);
	WriteProcessMemory(pHandle, (LPVOID)(this->_baseAddress + 0x160EB80), &R, sizeof(R), NULL);
	WriteProcessMemory(pHandle, (LPVOID)(this->_baseAddress + 0x160EB84), &G, sizeof(G), NULL);
	WriteProcessMemory(pHandle, (LPVOID)(this->_baseAddress + 0x160EB88), &B, sizeof(B), NULL);
	CloseHandle(pHandle);
}

void NieRHook::NoCLip(bool enabled)
{
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	if (enabled)
	{ //Enable noclip
		//Set memory at offsets 0x1354B1 & 0x135758 = 90 90 90 90
		Nop((BYTE*)(this->_baseAddress + 0x1354B1), 4, pHandle);
		Nop((BYTE*)(this->_baseAddress + 0x135758), 4, pHandle);
	}
	else
	{ //Disable noclip
		//Set memory at offsets 0x1354B1 & 0x135758 = previous values
		Patch((BYTE*)(this->_baseAddress + 0x1354B1), (BYTE*)"\x0F\x29\x42\x50", 4, pHandle);
		Patch((BYTE*)(this->_baseAddress + 0x135758), (BYTE*)"\x0F\x29\x43\x50", 4, pHandle);
	}
	CloseHandle(pHandle);
}

void NieRHook::InfiniteDoubleJump(bool enabled)
{
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pID);
	if (enabled)
	{
		//Write FF 0f 8c to enable
		Patch((BYTE*)(this->_baseAddress + 0x1E2D4C), (BYTE*)"\xFF\x0F\x8C", 3, pHandle);
	}
	else
	{
		//Write 02 0F 8D to disable
		Patch((BYTE*)(this->_baseAddress + 0x1E2D4C), (BYTE*)"\x02\x0f\x8D", 3, pHandle);
	}
	CloseHandle(pHandle);
}

NieRHook::NieRHook()
{
	this->_hooked = false;
	this->_baseAddress = 0;
	this->_entityAddress = 0;
	this->_pID = 0;
	this->Health = 0;
	this->MaxHealth = 0;
	this->Xpos = 0.000000;
	this->Ypos = 0.000000;
	this->Zpos = 0.000000;
	this->EXP = 0;
	this->Funds = 0;
	this->Level = 0;
}

NieRHook::~NieRHook()
{
}

void NieRHook::start(void)
{
	this->_hook(); //Hook
	this->_updateEntity();
}

void NieRHook::stop(void)
{
	this->_unHook();
}

DWORD NieRHook::getProcessID(void)
{
	return this->_pID;
}

bool NieRHook::isHooked(void)
{
	return this->_hooked;
}

int NieRHook::getLevel(void)
{
	return this->Level;
}

int NieRHook::getHealth(void)
{
	return this->Health;
}

int NieRHook::getMaxHealth(void)
{
	return this->MaxHealth;
}
