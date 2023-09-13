return {
    description = {
        identifier = "unfiredPotDry"
    },
    components = {
        hs_object = {
            model = "unfiredPotDry"
        },
        hs_resource = {
            -- a new storage is defined in this mod
            display_object = "unfiredPotDry",
            storage_identifier = "unfiredPotWet_storage"
        },
        hs_craftable = {
            display_object = "firedPot",
            hs_output = {
                simple_output = { "firedPot" }
            },
            skill = "potteryFiring",
            action_sequence = "fireStickCook",
            craft_area = "campfire",
            resources = {
                {
                    resource = "unfiredPotDry",
                    action = {
                        action_type = "inspect",
                        duration = 0.5,             --TODO: reset
                        duration_without_skill = 10 --TODO: reset
                    }
                }
            }
        }
    }
}
