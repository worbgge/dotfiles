-- Forked from https://gist.github.com/garoto/e0eb539b210ee077c980e01fb2daef4a.
-- Only tested on Windows. Date is set to dd/mmm/yyyy and time to machine-wide format.
-- Save as "excessive-history.lua" in your mpv scripts dir. Log will be saved to same folder as mpv.conf.
-- Make sure to leave a comment if you make any improvements/changes to the script!

-- Not much testing has been done.

-- *Changes made from original*
-- logs only path, no title
-- logs to where mpv.conf is
-- 4 digit year instead of 2
-- logs which parts are played

-- *Known flaws*
-- Probably wouldn't work properly if speed was not 1x.
-- Seeking right over to next file records "play 0.000" incorrectly.
-- End file entry could be logged twice if playing a folder.

-- *Other possibly notable irregularities*
-- Position logged when file has ended, or when seeking has started, is calculated by taking difference between two recordings of the system time. Which is probably not as precise as if this value came directly from mpv. E.g. across multiple tests, the end time (when triggered by end of file) can vary by a fractional second.
-- Location of history file is decided using the undocumented mp.find_config_file() with mpv.conf passed. Which wouldn't work if user doesn't have mpv.conf.
-- Multiple logs are sometimes logged while seeking rapidly (e.g. holding down a seek button). These are likely to always only be fractions of a second.

local msg = require "mp.msg" --for debugging
local utils = require "mp.utils"

local HISTFILE = (mp.find_config_file("mpv.conf"):sub(0,-9)).."history.txt"; -- File does not have to exist, but parent folder does.
local loggerfile;
local loggerfile = io.open(HISTFILE, "a+");
local started;
local paused;
local firstseek; -- mpv "seeks" as the file is opened. This is to ignore that.
local seeking;
local a_time;
local b_time;
local time_pos;
local a_pos;
local b_pos;

function get_a_time_and_pos()
	a_time = mp.get_time();
	a_pos = mp.get_property("time-pos");
end

function logtime()
	loggerfile:write(("<%s>\n"):format(os.date("%d/%b/%Y %X")));
end

function logplay()
	get_a_time_and_pos();
	logtime();
	loggerfile:write(("play %s "):format(a_pos));
end

mp.register_event("file-loaded", function()
	started = false;

	loggerfile:write(("%s\n"):format(mp.get_property("path")));
	if not mp.get_property_bool("pause") then
		started = true;
		logplay();
	end

	firstseek = mp.get_property_bool("seeking") and true or false;
end)

mp.observe_property("pause", "bool", function(name, value)
	time_pos = mp.get_property("time-pos");

	if value == true and started then
		paused = true;
		loggerfile:write(("pause %s\n"):format(time_pos));
	end

	if started == false then -- This is for if "file-loaded" never sets this to true. Which should be when video launches in paused state.
		started = true;
	end

	if value == false and started then -- if play
		paused = false;
		logplay();
	end
end)

mp.observe_property("seeking", "bool", function(name, value)
	time_pos = mp.get_property("time-pos");

	if value == false then -- if play
		seeking = false;
		
		if firstseek then
			firstseek = false;
		else
			if not mp.get_property_bool("pause") then
				if time_pos ~= nil then -- (not fully implemented) don't log if seeked right over to next file
					logtime();
					loggerfile:write(("seek stop %s "):format(time_pos));
				end
			end

			get_a_time_and_pos(); -- update when "rapidly seeking"
		end
	end
end)

mp.register_event("seek", function()
	if (not firstseek) and (not seeking) and (not mp.get_property_bool("pause")) then
		b_time = mp.get_time();
		b_pos = a_pos + (b_time - a_time);
		loggerfile:write(("seek start %s\n"):format(b_pos));

		seeking = true; -- so multiple seeks are not logged when seeking "rapidly"
	end
end)

mp.register_event("end-file", function()
	if (started and (not paused)) then -- started is to avoid error when playing a folder
		b_time = mp.get_time();
		b_pos = a_pos + (b_time - a_time);
		loggerfile:write(("end %s\n"):format(b_pos));
	end
	loggerfile:write("\n");
end)

mp.register_event("shutdown", function()
	loggerfile:close();
end)