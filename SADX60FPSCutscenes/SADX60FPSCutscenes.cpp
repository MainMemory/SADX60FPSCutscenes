#include "pch.h"
#include "..\sadx-mod-loader\SADXModLoader\include\SADXModLoader.h"
#include "..\sadx-mod-loader\libmodutils\Trampoline.h"

#define trampptr(name) decltype(name##_r)* ptr = (decltype(name##_r)*)name##Tramp->Target()

Trampoline* EventPlayActionTramp = nullptr;
void EventPlayAction_r(ObjectMaster* a1, NJS_ACTION* a2, NJS_TEXLIST* a3, float a4, char a5, char a6)
{
	trampptr(EventPlayAction);
	ptr(a1, a2, a3, a4 / 2, a5, a6);
}

Trampoline* EventPlayMotionTramp = nullptr;
void EventPlayMotion_r(ObjectMaster* a1, NJS_OBJECT* a2, NJS_MOTION* a3, NJS_TEXLIST* a4, float a5, char a6, char a7)
{
	trampptr(EventPlayMotion);
	ptr(a1, a2, a3, a4, a5 / 2, a6, a7);
}

Trampoline* EventChangeCameraRotationTramp = nullptr;
void EventChangeCameraRotation_r(char a1, int a2, int a3, int a4, int a5)
{
	trampptr(EventChangeCameraRotation);
	if (a2 > 1)
		a2 *= 2;
	ptr(a1, a2, a3, a4, a5);
}

Trampoline* EventChangeCameraPositionTramp = nullptr;
void EventChangeCameraPosition_r(char a1, int a2, float a3, float a4, float a5)
{
	trampptr(EventChangeCameraPosition);
	if (a2 > 1)
		a2 *= 2;
	ptr(a1, a2, a3, a4, a5);
}

Trampoline* EventChangeCameraFOVTramp = nullptr;
void EventChangeCameraFOV_r(char a1, int a2, int a3)
{
	trampptr(EventChangeCameraFOV);
	if (a2 > 1)
		a2 *= 2;
	ptr(a1, a2, a3);
}

Trampoline* EventWaitTramp = nullptr;
void EventWait_r(int a1)
{
	trampptr(EventWait);
	ptr(a1 * 2);
}

Trampoline* EventMoveObjectTramp = nullptr;
void EventMoveObject_r(ObjectMaster* a1, float a2, float a3, float a4, float a5, float a6, float a7, signed int a8)
{
	trampptr(EventMoveObject);
	ptr(a1, a2, a3, a4, a5, a6, a7, a8 * 2);
}

extern "C"
{
	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{
		EventPlayActionTramp = new Trampoline(0x42FE00, 0x42FE06, EventPlayAction_r);
		EventPlayMotionTramp = new Trampoline(0x42FE20, 0x42FE26, EventPlayMotion_r);
		EventChangeCameraRotationTramp = new Trampoline(0x430C90, 0x430C98, EventChangeCameraRotation_r);
		EventChangeCameraPositionTramp = new Trampoline(0x430D00, 0x430D08, EventChangeCameraPosition_r);
		EventChangeCameraFOVTramp = new Trampoline(0x431060, 0x43106A, EventChangeCameraFOV_r);
		EventWaitTramp = new Trampoline(0x4314D0, 0x4314D8, EventWait_r);
		WriteCall((char*)EventWaitTramp->Target() + 3, (void*)0x4015E0);
		EventMoveObjectTramp = new Trampoline(0x6EC2B0, 0x6EC2B6, EventMoveObject_r);
		WriteCall((char*)EventMoveObjectTramp->Target() + 1, (void*)0x6EBA90);
		WriteData((char*)0x42F8B7, (char)1);
		WriteData((char*)0x42F8B9, (char)1);
		WriteData((char*)0x431488, (char)1);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}