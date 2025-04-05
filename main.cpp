#include "src/game/game.h"
#include <windows.h>
#include <csignal>
#include <iostream>

#ifdef __arm64__
#include <ApplicationServices/ApplicationServices.h>
#endif
#ifdef _WIN64
LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS* pExceptionInfo) {
	// Handle the exception here
	std::cerr << "Unhandled exception occurred! 0x" << pExceptionInfo->ExceptionRecord->ExceptionCode << std::endl;
	return EXCEPTION_EXECUTE_HANDLER;
}
#endif

int main() {
#ifdef __arm64__
	// perform arm64 related operations
	ProcessSerialNumber psn = {0, kCurrentProcess};
   TransformProcessType(&psn, kProcessTransformToForegroundApplication);
   SetFrontProcess(&psn);
#endif
#ifdef _WIN32
	// Set up exception handling
	SetUnhandledExceptionFilter(ExceptionHandler);
	SetProcessDPIAware();
#endif

	// begin
	Game game;
	game.run();
	return 0;
}
