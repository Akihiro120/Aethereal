#pragma once
#include "../../screen_base.h"
#include "../../../services/injector/injector.h"
#include "../../manager/screen_manager.h"
#include "../../../database/database.h"
#include "fecs/registry/registry.h"

namespace Aethereal::Screen::MainMenu
{
    class Species : public ScreenBase,
                    public Service::Injector<Species, ScreenManager, FECS::Registry, Database>
    {
    public:
        Species();

        virtual void Render() override;
        virtual void Update() override;

    private:
        ScreenManager& m_ScreenManager;
        Database& m_Database;
        FECS::Registry& m_ECS;
    };
}
