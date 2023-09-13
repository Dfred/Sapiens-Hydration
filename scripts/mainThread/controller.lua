local mod = {
    -- Load order will be used to queue up all the mods that need to modify this script.
	loadOrder = 1,
}

-- This will be called when the controller file is itself requried. 
-- The 'controller' object paramater contains the parent module.
-- You can edit this module's exposed functions and paramaters. 
-- Local variables and functions are 'hidden', and cannot be easily modified
-- using shadows, as they are considered part of the module's private implementation.
function mod:onload(controller)
	mj:log("Loading Hydration mod, with Hammerstone framework...")

end

return mod
