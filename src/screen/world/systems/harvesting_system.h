#pragma once
#include <fecs.h>
#include "../../../services/service_locator.h"
#include "../../../components/interaction/harvest_component.h"
#include "../../../components/interaction/input_mode_component.h"
#include "../../../components/world_component.h"
#include "../../../components/identifiers/harvest_indicator_component.h"
#include "../../../game/state/game_state.h"
#include "../../../components/player_component.h"
#include "../../../components/inventory/inventory_component.h"
#include "utility.h"

class HarvestingSystem {
public:
    HarvestingSystem() {
        m_ecs = ServiceLocator::get_service<FECS>();
        m_gs = ServiceLocator::get_service<GameState>();
    }

    void harvest() {
        m_ecs->query<InputModeComponent, HarvestComponent>([&](Entity p_id, 
                InputModeComponent& input,
                HarvestComponent& harvest) {
            if (input.mode == InputModeComponent::InputMode::HARVEST) {
                
                // get the tile, read the tile, and harvest the tile, replace the tile with empty
                // add the harvested item to the inventory
                m_ecs->query<WorldComponent>([&](Entity _, WorldComponent& world) {
                    GameUtils::get_tile_world(world, harvest.selected_tile_pos, [&](Tile* tile) {
                        // valid tile
                        // check if the tile is harvestable
                        bool is_harvestable = false;
                        bool is_persistent = false;
                        for (auto& tag : tile->tags) {
                            if (tag == Tag::HARVESTABLE) {
                                is_harvestable = true;
                            }
                            if (tag == Tag::PERSISTENT) {
                                is_persistent = true;
                            }
                        }

                        // indicator effects
                        m_ecs->query<HarvestIndicatorComponent, RenderComponent>([&](Entity h_id, auto& h, auto& r) {
                            if (tile->render.code != 0x00) {
                                if (is_harvestable) {
                                    r.bg_color = color_from_name("green");    
                                } else {
                                    r.bg_color = color_from_name("red");    
                                }
                                r.code = tile->render.code;
                                r.color = tile->render.color;
                            } else {
                                r.code = ' ';
                                r.bg_color = color_from_name("white");    
                            }
                        });

                        // harvest tile
                        if (is_harvestable) {
                            if (harvest.is_harvesting) {
                                // add the item to the inventory
                                // TODO: add duration for harvesting
                                m_gs->log("Harvested Item: " + tile->tile_obj_id);
                                m_ecs->query<PlayerComponent, InventoryComponent>([&](Entity id, 
                                            auto& _, 
                                            InventoryComponent& inventory) {

                                    m_ecs->attach<InventoryAddItemComponent>(p_id, {
                                        .item = {
                                            .name = tile->tile_obj_id,
                                            .amount = 1
                                        }
                                    });
                                });

                                // remove
                                tile->yield -= 1;
                                if (tile->yield <= 0) {
                                    // remove the tile
                                    if (!is_persistent) {
                                        *tile = Tile{};
                                    }
                                }
                            }
                        }
                        // disable
                        harvest.is_harvesting = false;
                    });
                });
            }
        }); 
    } 

private:
    

    std::shared_ptr<FECS> m_ecs;
    std::shared_ptr<GameState> m_gs;
};
