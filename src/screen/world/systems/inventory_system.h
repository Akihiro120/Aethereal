#pragma once
#include <fecs.h>
#include "../../../services/service_locator.h"
#include "../../../components/inventory/inventory_component.h"
#include "../../../logging.h"
#include "../../../game/state/game_state.h"


class InventorySystem {
public:
    
    InventorySystem() {
        m_ecs = ServiceLocator::get_service<FECS>();
        m_gs = ServiceLocator::get_service<GameState>();
    }

    void update() {
        wait_add_inventory_event();
        wait_remove_inventory_event();
    }

    // wait for an event to add an item to the inventory
    void wait_add_inventory_event() {
        m_ecs->query<InventoryAddItemComponent>([&](Entity id, InventoryAddItemComponent& event) {

            // add
            m_ecs->query<InventoryComponent>([&](Entity id, InventoryComponent& inventory) {
                // check if the item already exists
                for (auto& item : inventory.items) {
                    if (item.name == event.item.name) {
                        item.amount += event.item.amount;
                        return;
                    }
                }

                // add the item to the inventory
                inventory.items.push_back(event.item);
            });
            
            // remove the add item event
            m_gs->log("Item event received: Add: " + event.item.name);
            m_ecs->detach<InventoryAddItemComponent>(id);
        });
    }

    // wait for an event to remove an item from the inventory
    void wait_remove_inventory_event() {
        m_ecs->query<InventoryRemoveItemComponent>([&](Entity id, auto& event) {
            
            // remove the add item event
            m_ecs->detach<InventoryRemoveItemComponent>(id);
            m_gs->log("Item event received: Remove");
        });
    }

private:
    std::shared_ptr<FECS> m_ecs;
    std::shared_ptr<GameState> m_gs;
};
