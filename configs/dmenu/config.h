//      ██
//     ░██
//     ░██ ██████████   █████  ███████  ██   ██
//  ██████░░██░░██░░██ ██░░░██░░██░░░██░██  ░██
// ██░░░██ ░██ ░██ ░██░███████ ░██  ░██░██  ░██
//░██  ░██ ░██ ░██ ░██░██░░░░  ░██  ░██░██  ░██
//░░██████ ███ ░██ ░██░░██████ ███  ░██░░██████
// ░░░░░░ ░░░  ░░  ░░  ░░░░░░ ░░░   ░░  ░░░░░░
//
//  ▓▓▓▓▓▓▓▓▓▓
// ░▓ author ▓ worbgge <me@worbgge.xyz>
// ░▓▓▓▓▓▓▓▓▓▓
//  ░░░░░░░░░░

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"Terminus:size=14",
	"NotoColorEmoji:pixelsize=10:antialias=true:autohint=true"
};
static const unsigned int bgalpha = 0xe0;
static const unsigned int fgalpha = OPAQUE;
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#fbf1c7", "#282828" },
	[SchemeSel] = { "#ebdbb2", "#98971a" },
	[SchemeOut] = { "#1d2021", "#8ec07c" },
};

/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";

