#include "world.h"
#include "../utilities/draw_utilities.h"

void World::render() {
	
	terminal_color("white");
	DrawUtils::draw_box_heavy({ 0, 0, 32, 16 });
}

void World::update() {

}
