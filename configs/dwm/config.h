//      ██
//     ░██
//     ░██ ███     ██ ██████████
//  ██████░░██  █ ░██░░██░░██░░██
// ██░░░██ ░██ ███░██ ░██ ░██ ░██
//░██  ░██ ░████░████ ░██ ░██ ░██
//░░██████ ███░ ░░░██ ███ ░██ ░██
// ░░░░░░ ░░░    ░░░ ░░░  ░░  ░░
//
//  ▓▓▓▓▓▓▓▓▓▓
// ░▓ author ▓ worbgge <me@worbgge.xyz>
// ░▓▓▓▓▓▓▓▓▓▓
//  ░░░░░░░░░░

#define TERMINAL "st"
#define BROWSER "firefox"

static unsigned int borderpx=3;
static unsigned int snap=32;
static unsigned int gappih=20;
static unsigned int gappiv=10;
static unsigned int gappoh=10;
static unsigned int gappov=20;
static int swallowfloating=1;
static int smartgaps=0;
static int showbar=1;
static int topbar=1;
static char*fonts[]={"terminus:size=13","Openmoji:pixelsize=12:antialias=true:autohint=true"};
static char normbgcolor[]="#282828";
static char normbordercolor[]="#444444";
static char normfgcolor[]="#bbbbbb";
static char selfgcolor[]="#eeeeee";
static char selbordercolor[]="#770000";
static char*colors[][3]={
    /*               fg           bg           border   */
    [SchemeNorm]={normfgcolor,normbgcolor,normbordercolor},
    [SchemeSel]={selfgcolor,normbordercolor,selbordercolor}
};

typedef struct{
    const char*name;
    const void*cmd;
} Sp;
const char *spcmd1[]={TERMINAL,"-n","spterm","-g","120x34",NULL};
const char *spcmd2[]={TERMINAL,"-n","spcalc","-f","monospace:size=16","-g","50x20","-e","bc","-lq",NULL};
static Sp scratchpads[]={
    {"spterm",spcmd1},
    {"spcalc",spcmd2}
};

static const char*tags[]={"I","II","III","IV","V","VI","VII","VIII","IX"};

static const Rule rules[]={
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
    */
    /* class                  instance      title                 tags mask   isfloating   isterminal   noswallow   monitor */
    {"firefox",               NULL,         NULL,                 1,          0,           0,           0,        -1 },
    {"vesktop",               NULL,         NULL,                 2,          0,           0,           0,        -1 },
    {"Steam",                 NULL,         NULL,                 4,          0,           0,           0,        -1 },
    {TERMINAL,                NULL,         NULL,                 0,          0,           1,           0,        -1 },
    {NULL,                    NULL,         "Event Tester",       0,          0,           0,           1,        -1 },
    {TERMINAL,                "floatterm",  NULL,                 0,          1,           1,           0,        -1 },
    {"RuneLite",              NULL,         NULL,                 0,          1,           1,           0,        -1 },
    {"waspcycle.exe",         NULL,         NULL,                 0,          1,           1,           0,        -1 },
    {"open-joystick-display", NULL,         NULL,                 0,          1,           1,           0,        -1 },
    {"simpsons.exe",          NULL,         NULL,                 0,          1,           1,           0,        -1 },
    {"Toolkit",               NULL,         "Picture-in-Picture", 0,          1,          -1                       },
    {"firefox",               NULL,         "Picture-in-Picture", 0,          1,          -1                       },
    {TERMINAL,                "bg",          NULL,                1 << 7,     0,           1,           0,        -1 },
    {TERMINAL,                "spterm",      NULL,                SPTAG(0),   1,           1,           0,        -1 },
    {TERMINAL,                "spcalc",      NULL,                SPTAG(1),   1,           1,           0,        -1 },
};

static float mfact=0.55;
static int nmaster=1;
static int resizehints=0;
static const int lockfullscreen=1;
#define FORCE_VSPLIT 1
#include"vanitygaps.c"
static const Layout layouts[]={
    /* symbol arrange function */
    {"[]=",  tile},
    {"TTT",  bstack},
    {"[@]",  spiral},
    {"[\\]", dwindle},
    {"[D]",  deck},
    {"[M]",  monocle},
    {"|M|",  centeredmaster},
    {">M>",  centeredfloatingmaster},
    {"><>",  NULL},
    {NULL,    NULL},
};

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)\
    {MODKEY,                       KEY, view,       {.ui = 1 << TAG} },\
    {MODKEY|ControlMask,           KEY, toggleview, {.ui = 1 << TAG} },\
    {MODKEY|ShiftMask,             KEY, tag,        {.ui = 1 << TAG} },\
    {MODKEY|ControlMask|ShiftMask, KEY, toggletag,  {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
    { MOD, XK_j, ACTION##stack, {.i=INC(+1)}},\
    { MOD, XK_k, ACTION##stack, {.i=INC(-1)}},\
    { MOD, XK_v, ACTION##stack, {.i=0}},\

#define SHCMD(cmd){.v=(const char*[]){"/bin/sh","-c",cmd,NULL}}

static const char *termcmd[]={TERMINAL,NULL};

ResourcePref resources[]={
        {"color0",          STRING,  &normbordercolor},
        {"color8",          STRING,  &selbordercolor},
        {"color0",          STRING,  &normbgcolor},
        {"color4",          STRING,  &normfgcolor},
        {"color0",          STRING,  &selfgcolor},
        {"borderpx",        INTEGER, &borderpx},
        {"snap",            INTEGER, &snap},
        {"showbar",         INTEGER, &showbar},
        {"topbar",          INTEGER, &topbar},
        {"nmaster",         INTEGER, &nmaster},
        {"resizehints",     INTEGER, &resizehints},
        {"mfact",           FLOAT,   &mfact},
        {"gappih",          INTEGER, &gappih},
        {"gappiv",          INTEGER, &gappiv},
        {"gappoh",          INTEGER, &gappoh},
        {"gappov",          INTEGER, &gappov},
        {"swallowfloating", INTEGER, &swallowfloating},
        {"smartgaps",       INTEGER, &smartgaps},
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static const Key keys[]={
    /* modifier        key              function        argument */
    STACKKEYS(         MODKEY,          focus)
    STACKKEYS(         MODKEY|ShiftMask,push)
    {MODKEY,           XK_grave,        spawn, {.v = (const char*[]){ "dmenuunicode", NULL } } },
    TAGKEYS(           XK_1,            0)
    TAGKEYS(           XK_2,            1)
    TAGKEYS(           XK_3,            2)
    TAGKEYS(           XK_4,            3)
    TAGKEYS(           XK_5,            4)
    TAGKEYS(           XK_6,            5)
    TAGKEYS(           XK_7,            6)
    TAGKEYS(           XK_8,            7)
    TAGKEYS(           XK_9,            8)
    {MODKEY,           XK_0,            view,            {.ui=~0}},
    {MODKEY|ShiftMask, XK_0,            tag,             {.ui=~0}},
    {MODKEY,           XK_BackSpace,    spawn,           {.v=(const char*[]){"sysact",NULL}}},
    {MODKEY,           XK_Tab,          view,            {0}},
    {MODKEY|ShiftMask, XK_q,            killclient,      {0}},
    {MODKEY,           XK_w,            spawn,           {.v=(const char*[]){BROWSER,"-p",NULL}}},
    {MODKEY,		   XK_e,        	spawn,	         SHCMD(TERMINAL " -e neomutt ; rmdir ~/.abook 2>/dev/null")},
	{MODKEY|ShiftMask, XK_e,        	spawn,	    	 SHCMD(TERMINAL " -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook")},
    {MODKEY,           XK_v,            spawn,           {.v=(const char*[]){"clipmenu",NULL}}},
    {MODKEY,           XK_r,            spawn,           {.v=(const char*[]){TERMINAL,"-e","lfub",NULL}}},
    {MODKEY,           XK_t,            setlayout,       {.v=&layouts[0]}},
    {MODKEY|ShiftMask, XK_t,            setlayout,       {.v=&layouts[1]}},
    {MODKEY,           XK_y,            setlayout,       {.v=&layouts[2]}},
    {MODKEY|ShiftMask, XK_y,            setlayout,       {.v=&layouts[3]}},
    {MODKEY,           XK_u,            setlayout,       {.v=&layouts[4]}},
    {MODKEY|ShiftMask, XK_u,            setlayout,       {.v=&layouts[5]}},
    {MODKEY,           XK_i,            setlayout,       {.v=&layouts[6]}},
    {MODKEY|ShiftMask, XK_i,            setlayout,       {.v=&layouts[7]}},
    {MODKEY,           XK_o,            incnmaster,      {.i=+1 } },
    {MODKEY|ShiftMask, XK_o,            incnmaster,      {.i=-1 } },
    {MODKEY,           XK_bracketleft,  spawn,           {.v=(const char*[]){"cmus-remote","-v","-10",NULL}}},
    {MODKEY,           XK_bracketright, spawn,           {.v=(const char*[]){"cmus-remote","-v","+10",NULL}}},
    {MODKEY,           XK_backslash,    view,            {0}},
    {MODKEY,           XK_a,            togglegaps,      {0}},
    {MODKEY|ShiftMask, XK_a,            defaultgaps,     {0}},
    {MODKEY,           XK_s,            togglesticky,    {0}},
    {MODKEY,           XK_p,            spawn,           {.v=(const char*[]){"dmenu_run",NULL}}},
    {MODKEY|ShiftMask, XK_p,            spawn,           {.v=(const char*[]){"passmenu",NULL}}},
    {MODKEY,           XK_f,            togglefullscr,   {0}},
    {MODKEY|ShiftMask, XK_f,            setlayout,       {.v=&layouts[8]} },
    {MODKEY,           XK_g,            shiftview,       {.i=-1}},
    {MODKEY|ShiftMask, XK_g,            shifttag,        {.i=-1}},
    {MODKEY,           XK_h,            setmfact,        {.f=-0.05}},
    {MODKEY,           XK_l,            setmfact,        {.f=+0.05}},
    {MODKEY,           XK_semicolon,    shiftview,       {.i=1}},
    {MODKEY|ShiftMask, XK_semicolon,    shifttag,        {.i=1}},
    {MODKEY,           XK_apostrophe,   togglescratch,   {.ui=1}},
    {MODKEY|ShiftMask, XK_apostrophe,   togglesmartgaps, {0}},
    {MODKEY,           XK_Return,       spawn,           {.v=termcmd}},
    {MODKEY|ShiftMask, XK_Return,       togglescratch,   {.ui=0}},
    {MODKEY,           XK_comma,        focusmon,        {.i=-1}},
    {MODKEY,           XK_period,       focusmon,        {.i=+1}},
    {MODKEY|ShiftMask, XK_comma,        tagmon,          {.i=-1}},
    {MODKEY|ShiftMask, XK_period,       tagmon,          {.i=+1}},
    {MODKEY,           XK_z,            incrgaps,        {.i=+3}},
    {MODKEY,           XK_x,            incrgaps,        {.i=-3}},
    {MODKEY,           XK_c,            spawn,           {.v=(const char*[]){TERMINAL,"-e","weechat",NULL}}},
    {MODKEY,           XK_b,            togglebar,       {0}},
    {MODKEY,           XK_n,            spawn,           {.v=(const char*[]){TERMINAL,"-e","nvim",NULL}}},
    {MODKEY|ShiftMask, XK_n,            spawn,           {.v=(const char*[]){TERMINAL,"-e","newsboat",NULL}}},
    {MODKEY,           XK_m,            spawn,           {.v=(const char*[]){TERMINAL,"-e","cmus",NULL}}},
    {MODKEY|ShiftMask, XK_m,            spawn,           {.v=(const char*[]){"mpv","--player-operation-mode=pseudo-gui",NULL}}},
    {MODKEY,           XK_Left,         focusmon,        {.i=-1}},
    {MODKEY|ShiftMask, XK_Left,         tagmon,          {.i=-1}},
    {MODKEY,           XK_Right,        focusmon,        {.i=+1}},
    {MODKEY|ShiftMask, XK_Right,        tagmon,          {.i=+1}},
    {MODKEY,           XK_Page_Up,      shiftview,       {.i=-1}},
    {MODKEY|ShiftMask, XK_Page_Up,      shifttag,        {.i=-1}},
    {MODKEY,           XK_Page_Down,    shiftview,       {.i=+1}},
    {MODKEY|ShiftMask, XK_Page_Down,    shifttag,        {.i=+1}},
    {MODKEY,           XK_F1,           spawn,           {.v=(const char*[]){BROWSER,"-p",NULL}}},
    {MODKEY,           XK_F2,           spawn,           {.v=(const char*[]){TERMINAL,"-e","htop",NULL}}},
    {MODKEY,           XK_F3,           spawn,           {.v=(const char*[]){TERMINAL,"-e","pulsemixer",NULL}}},
    {MODKEY,           XK_F4,           spawn,           {.v=(const char*[]){"mailsync",NULL}}},
    {MODKEY,           XK_F5,           spawn,           {.v=(const char*[]){"dmenurecord",NULL}}},
    {MODKEY|ShiftMask, XK_F6,           spawn,           {.v=(const char*[]){"dmenurecord","kill",NULL}}},
    {MODKEY,           XK_F9,           spawn,           {.v=(const char*[]){"cmus-remote","-r",NULL}}},
    {MODKEY,           XK_F10,          spawn,           {.v=(const char*[]){"cmus-remote","-u",NULL}}},
    {MODKEY,           XK_F11,          spawn,           {.v=(const char*[]){"cmus-remote","-n",NULL}}},
    {MODKEY,		   XK_F12,        	spawn,	         SHCMD("maim -s ~/pic/screen/$(date +%Y-%m-%d_%H-%M-%S).png && xclip -selection clipboard -t image/png ~/pic/screen/$(ls -r1 ~/pic/screen | head -1)")},
    {MODKEY|ShiftMask, XK_F12,        	spawn,	         SHCMD("maim ~/pic/screen/$(date +%Y-%m-%d_%H-%M-%S).png && xclip -selection clipboard -t image/png ~/pic/screen/$(ls -r1 ~/pic/screen | head -1)")},
    {MODKEY,           XK_space,        zoom,            {0}},
    {MODKEY|ShiftMask, XK_space,        togglefloating,  {0}},
};

static const Button buttons[] = {
    /* click         event mask      button          function        argument */
    { ClkLtSymbol,   0,      Button1, setlayout,      {0}},
    { ClkLtSymbol,   0,      Button3, setlayout,      {.v=&layouts[2]}},
    { ClkWinTitle,   0,      Button2, zoom,           {0}},
    { ClkStatusText, 0,      Button2, spawn,          {.v=termcmd}},
    { ClkClientWin,  MODKEY, Button4, incrgaps,       {.i=+1}},
    { ClkClientWin,  MODKEY, Button5, incrgaps,       {.i=-1}},
    { ClkClientWin,  MODKEY, Button1, movemouse,      {0}},
    { ClkClientWin,  MODKEY, Button2, togglefloating, {0}},
    { ClkClientWin,  MODKEY, Button3, resizemouse,    {0}},
    { ClkTagBar,     0,      Button1, view,           {0}},
    { ClkTagBar,     0,      Button3, toggleview,     {0}},
    { ClkTagBar,     MODKEY, Button1, tag,            {0}},
    { ClkTagBar,     MODKEY, Button3, toggletag,      {0}},
    { ClkTagBar,     0,      Button4, shiftview,      {.i=-1}},
    { ClkTagBar,     0,      Button5, shiftview,      {.i=1}}
};

