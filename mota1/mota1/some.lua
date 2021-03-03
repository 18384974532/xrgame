local monster = require "monster"
local door = require "door"
local wall = require "wall"
local item = require "item"

local function fight(player, pos)
	local m = monster[pos]
	if not m then
		return
	end
	if player.attack <= m.defence then
		return
	end
	local round
	local pattackm = player.attack - m.defence
	local mattackp = m.attack - player.defence
	if mattackp < 0 then
		mattackp = 0
	end
	if m.life % pattackm == 0 then
		round = m.life / pattackm - 1
	else
		round = m.life / pattackm
	end
	if player.life <= round*mattackp then
		return
	else
		player.life = player.life - round*mattackp
		player.exp = player.exp + m.exp
		player.suc = 1
	end
end

local function meet_wall(player, pos)
	local w = wall[pos]
	if not w then
		return
	end
	if w.cross == 1 then
		player.suc = 1
	else
		return
	end
	return player
end

local function meet_door(player, pos)
	local d = door[pos]
	if not d then
		return
	end
	if player[d.needKey] then --player.yellow_key
		player[d.needKey] = player[d.needKey] - 1
		player.suc = 1
	elseif d.uodStair then
		player.building_level = player.building_level + d.uodStair
	end
	return player
end

local function meet_item(player, pos)
	local i = item[pos]
	if not i then
		return
	end
	for k, v in pairs(i) do
		if k == 'attributeUp' then
			for k1, v1 in pairs(v) do
				player[k1] = player[k1] + v1
			end
		end
	end
	player.suc = 1
	return player
end

function move(player, pos)
	if pos >= 3000 then
		meet_item(player, pos)
	elseif pos >= 2000 then
		meet_door(player, pos)
	elseif pos >= 1000 then
		meet_wall(player, pos)
	elseif pos >= 0 then
		fight(player, pos)
	end
	return player
end