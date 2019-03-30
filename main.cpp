#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "HWBP.h"

AwBreakPoint BP;

__declspec(naked) void hook(IDirect3DDevice9* pDevice)
{
__asm
{
mov edi,edi
push ebp
mov ebp,esp
}
pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,255,0), 1.0f, 0);

__asm
{
mov eax,0x4FE571A0
add eax,0x5
jmp eax
}

}

void Handle(EXCEPTION_POINTERS* ep) //ÝZÝ PÝZÝ LÝMON SKUYZÝ
{
if(ep->ContextRecord->Eip == 0x4FE571A0)
{
ep->ContextRecord->Eip = (unsigned long)&hook;
}
}

void SetBP()
{
BP.SetExceptionHandler(Handle);
BP.SetHWBreakPoint(0x4FE571A0,0);
}


bool __stdcall DllMain(HINSTANCE hInst,DWORD uReason,void* lpReserved)
{
if(uReason == DLL_PROCESS_ATTACH)
{
SetBP();
}
return true;
}