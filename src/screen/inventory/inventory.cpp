#include "inventory.h"
#include <BearLibTerminal.h>
#include "../../services/service_locator.h"
#include "../../components/inventory/inventory_component.h"
#include "../../components/player_component.h"
#include "../../components/interaction/input_mode_component.h"
#include <glm/glm.hpp>

InventoryScreen::InventoryScreen() {
    m_ecs = ServiceLocator::get_service<FECS>();
	m_im = ServiceLocator::get_service<InputManager>();
	m_sm = ServiceLocator::get_service<ScreenManager>();
    m_gs = ServiceLocator::get_service<GameState>();

    int width = terminal_state(TK_WIDTH);
    int height = terminal_state(TK_HEIGHT);

    Box game_bounds = Box(0.0f, 0.0f, width*0.75f-1, (float)height);

    int inventory_width = game_bounds.width * 0.6f;
    int inventory_height = game_bounds.height * 0.6f;
    m_inventory_bounds = Box{
        (game_bounds.width - inventory_width) / 2.0f,
        (game_bounds.height - inventory_height) / 2.0f,
        (float)inventory_width,
        (float)inventory_height
    };
}

void InventoryScreen::render() {

    // render inventory items
    m_ecs->query<PlayerComponent, InventoryComponent, InputModeComponent>([&](Entity id, 
                auto& _, 
                InventoryComponent& inventory,
                InputModeComponent& input_mode) {

        // render inventory items
        if (input_mode.mode != InputModeComponent::InputMode::INVENTORY) {
            return;
        }

        terminal_color("white");
        DrawUtils::draw_box_heavy(m_inventory_bounds);
        terminal_print(m_inventory_bounds.x + 1, m_inventory_bounds.y, "Inventory");

        terminal_color("black");
        for (int i = 1; i < m_inventory_bounds.width; ++i) {
            for (int j = 1; j < m_inventory_bounds.height; ++j) {
                terminal_put(m_inventory_bounds.x + i, m_inventory_bounds.y + j, ' ');
            }
        }
        
        terminal_color("white");
        m_ecs->query<InventoryComponent>([&](Entity id, InventoryComponent& inv) {
            for (int i = 0; i < inv.items.size(); ++i) {
                auto item = inv.items[i];

                // highlight selected item
                terminal_color("white");
                terminal_bkcolor("black");
                if (i == m_selected_item) {
                    terminal_color("black");
                    terminal_bkcolor("white"); 
                }
                std::string item_display = std::to_string(item.amount) + "x " + item.name;
                terminal_print(m_inventory_bounds.x + 1, m_inventory_bounds.y + i + 1, item_display.c_str());
            }
        });
        terminal_bkcolor("black");
    });
}

void InventoryScreen::update() {

    m_ecs->query<InputModeComponent>([&](Entity id, InputModeComponent& input_mode) {
        
        // not input mode
        if (input_mode.mode != InputModeComponent::InputMode::INVENTORY) {
            m_sm->pop();
            m_gs->log("Inventory closed: Not in Inventory Mode!!!");
            return;
        }

        // process only if the inventory is active
        m_im->process_input([&](int key) {
            if (key == TK_ESCAPE && input_mode.mode == InputModeComponent::InputMode::INVENTORY) {
                input_mode.mode = InputModeComponent::InputMode::DEFAULT;
                input_mode.last_mode = InputModeComponent::InputMode::INVENTORY;
                m_gs->log("Inventory closed");
                m_sm->pop();

                return;
            }

            // navigate the inventory
            auto inv = m_ecs->get<InventoryComponent>(id);
            if (inv) {
                if (key == TK_K) {
                    m_selected_item = glm::clamp(m_selected_item - 1, 0, (int)inv->items.size() - 1);
                }
                if (key == TK_J) {
                    m_selected_item = glm::clamp(m_selected_item + 1, 0, (int)inv->items.size() - 1);
                }
            }
        });
    });
}
