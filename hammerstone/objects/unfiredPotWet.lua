return {
    description = {
        identifier = "unfiredPotWet"
    },
    components = {
        hs_object = {
            model = "unfiredPotWet"
        },
        hs_resource = {
            -- a new storage is defined in this mod
            display_object = "unfiredPotWet",
            storage_identifier = "unfiredPotWet_storage"
        },
        hs_evolving_object = {
            time_years = 0.0033,
            category = "dry",
            transform_to = {
                "unfiredPotDry"
            },
        },
        hs_craftable = {
            display_object = "unfiredPotWet",
            skill = "pottery",
            action_sequence = "potteryCraft",
            hs_output = {
                simple_output = { "unfiredPotWet" },
            },
            resources = {
                {
                    resource = "clay",
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
