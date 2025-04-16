#pragma once
#include <BearLibTerminal.h>
#include <fecs.h>
#include "../../../services/service_locator.h"
#include "../../../components/velocity_component.h"
#include "../../../components/player_component.h"
#include "../../screen_manager/screen_manager.h"
#include "../../../components/interaction/input_mode_component.h"
#include "../../inventory/inventory.h"
#include "../../../components/interaction/harvest_component.h"
#include "../../../components/render_component.h"
#include "../../../components/position_component.h"
#include "../../../components/identifiers/harvest_indicator_component.h"

class PlayerSystem {
public:
	PlayerSystem() {
	    m_ecs = ServiceLocator::get_service<FECS>();
        m_sm = ServiceLocator::get_service<ScreenManager>();
        m_gs = ServiceLocator::get_service<GameState>();
    }

	// control player movement
	void movement(int key) {
		m_ecs->query<PlayerComponent, VelocityComponent>([&](Entity id, auto& _, auto& vel) {
            // check input mode
            if (m_ecs->get<InputModeComponent>(id)->mode != InputModeComponent::InputMode::DEFAULT) {
                return;
            }

			if (key == TK_H || key == TK_LEFT) {
				vel.x -= 1.0f;
			}	
			if (key == TK_J || key == TK_DOWN) {
				vel.y += 1.0f;
			}	
			if (key == TK_K || key == TK_UP) {
				vel.y -= 1.0f;
			}	
			if (key == TK_L || key == TK_RIGHT) {
				vel.x += 1.0f;
			}	
		});
	}

    void inventory(int key) {
        m_ecs->query<InputModeComponent>([&](Entity id, InputModeComponent& input_mode) {
            if (key == TK_I && input_mode.mode == InputModeComponent::InputMode::DEFAULT) {
                input_mode.mode = InputModeComponent::InputMode::INVENTORY;
                m_sm->push(std::make_shared<InventoryScreen>());

                m_gs->log("Inventory opened");
            }
        });
    }

    void harvest(int key) {
        m_ecs->query<PlayerComponent, InputModeComponent>([&](Entity id, auto& p, InputModeComponent& input_mode) {
                    
            // attach
            if (key == TK_Q && input_mode.mode == InputModeComponent::InputMode::DEFAULT) {
                input_mode.mode = InputModeComponent::InputMode::HARVEST;

                // attach harvest component
                auto pos = m_ecs->get<PositionComponent>(id);
                m_ecs->attach<HarvestComponent>(id, HarvestComponent{
                    .selected_tile_pos = glm::ivec2(pos->x-1, pos->y),
                });
                m_gs->log("Harvesting mode enabled");

                // create rendering entity
                auto h_id = m_ecs->create_entity();
                m_ecs->attach<PositionComponent>(h_id, PositionComponent());
                m_ecs->attach<RenderComponent>(h_id, RenderComponent{
                    .code = (int)' ', 
                    .color = 0x00,
                    .bg_color = color_from_name("white")
                });
                m_ecs->attach<HarvestIndicatorComponent>(h_id, HarvestIndicatorComponent{});
            }

            if (input_mode.mode == InputModeComponent::InputMode::HARVEST) {
                if (key == TK_ENTER) {
                    auto harvest = m_ecs->get<HarvestComponent>(id);
                    harvest->is_harvesting = true;
                }

                // move the indicator
                m_ecs->query<HarvestComponent>([&](Entity h_id, HarvestComponent& h) {
                    // TODO: add range limit to selection
                    if (key == TK_H || key == TK_LEFT) {
                        h.selected_tile_pos.x -= 1.0f;
                    }	
                    if (key == TK_J || key == TK_DOWN) {
                        h.selected_tile_pos.y += 1.0f;
                    }	
                    if (key == TK_K || key == TK_UP) {
                        h.selected_tile_pos.y -= 1.0f;
                    }	
                    if (key == TK_L || key == TK_RIGHT) {
                        h.selected_tile_pos.x += 1.0f;
                    }	

                    m_ecs->query<HarvestIndicatorComponent, PositionComponent>([&](Entity h_id, auto& i, auto& pos) {
                        pos.x = h.selected_tile_pos.x;
                        pos.y = h.selected_tile_pos.y;
                    });
                });
                
                // detach
                if (key == TK_ESCAPE) {
                    input_mode.mode = InputModeComponent::InputMode::DEFAULT;
                    m_ecs->detach<HarvestComponent>(id);

                    // remove rendering entity
                    m_ecs->query<HarvestIndicatorComponent, RenderComponent>([&](Entity h_id, auto& h, auto& r) {
                        m_ecs->remove_entity(h_id);
                    });

                    m_gs->log("Harvesting mode disabled");
                }
            }
        });
    }

private:
    std::shared_ptr<FECS> m_ecs;
    std::shared_ptr<ScreenManager> m_sm;
    std::shared_ptr<GameState> m_gs;
};
