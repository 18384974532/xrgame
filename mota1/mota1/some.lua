local monster = require "monster"
local door = require "door"
local wall = require "wall"

local function move( player, pos)
		if pos < 1000 then
				fight(player, pos)
		end
end

local function fight(player, pos)
		local m = monster[pos]
		if player[attack] <= m.defence then
				return
		end
		local round
		local pattackm = player.attack - m.defence 
		local mattackp = m.attack - player.defence
		if mattackp < 0 then
				mattackp = 0
		end
		if m.life / pattackm == 0 then
				round = m.life / pattackm - 1
		else
				round = m.life / pattackm
		end
		if player.life <= round*mattackp then
				
		end
end
