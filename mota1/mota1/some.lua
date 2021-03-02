local monster = require "monster"
local door = require "door"
local wall = require "wall"

function fight(player, pos)
print(debug.traceback())
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

local function mwall(player, pos)
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

local function mdoor(player, pos)
	local d = door[pos]
	if not d then
		return
	end
	return player
end

function move(player, pos)
	if pos >= 3000 then
		--1000
	elseif pos >= 2000 then
		mdoor(player, pos)
	elseif pos >= 1000 then
		mwall(player, pos)
	elseif pos >= 0 then
		fight(player, pos)
	end
	return player
end