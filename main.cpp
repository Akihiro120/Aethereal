#include "src/game/game.h"
#include <ApplicationServices/ApplicationServices.h>

int main() {
#ifdef __arm64__
	// perform arm64 related operations
	ProcessSerialNumber psn = {0, kCurrentProcess};
   TransformProcessType(&psn, kProcessTransformToForegroundApplication);
   SetFrontProcess(&psn);
#endif

	// begin
	Game game;
	game.run();
	return 0;
}
