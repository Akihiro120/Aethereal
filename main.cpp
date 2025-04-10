#include "src/game/game.h"
#include "src/logging.h"
#include <iostream>

// define defaults
#define MAX_SPARSE_SIZE 2000
#define MAX_COMPONENTS 100

#ifdef __arm64__
#include <csignal>
#include <ApplicationServices/ApplicationServices.h>
#endif
#ifdef _WIN64
#include <windows.h>
LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS* pExceptionInfo) {
	// Handle the exception here
	// std::cerr << "Unhandled exception occurred! 0x" << pExceptionInfo->ExceptionRecord->ExceptionCode << std::endl;
	AETHEREAL_LOG("Unhandled exception occurred! 0x" << pExceptionInfo->ExceptionRecord->ExceptionCode);
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
