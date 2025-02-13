#!/bin/sh
~/.config/cmus/cmus_status_scrobbler.py "$@" &
~/.config/cmus/cmushnotify "$@" &
