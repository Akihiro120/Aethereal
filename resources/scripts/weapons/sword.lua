return
{
    id = "sword",
    name = "Rusty Sword",
    description = "An old blade.",
    rarity = "Common",

    stats =
    {
        attack = 10
    },

    scalings =
    {
        strength = 50
    },

    passive = function(self, owner)
    end,

    inspect = function(self, owner)
        return {
            "Its an old, ordinary sword."
        }
    end,

    onHit = function(self, owner, target)
    end,

    onUse = function(self, owner)
    end,

    onEquip = function(self, owner)
    end,

    onDrop = function(self, owner)
    end,
}
