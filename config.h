static const unsigned int borderpx              = 3;    /* border pixel of windows */
static const unsigned int snap                  = 32;   /* snap pixel for floating windows*/
static const unsigned int systraypinning        = 0;    /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft         = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing        = 2;    /* systray spacing */
static const unsigned int gappx                 = 0;    /* gap pixel between windows */
static const int systraypinningfailfirst        = 1;    /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray                    = 1;    /* 0 means no systray */
static const int showbar                        = 1;    /* 0 means no bar */
static const int topbar                         = 1;    /* 0 means bottom bar */
static const int focusonwheel                   = 0;
static const char *fonts[]                      = { "JetBrainsMono Nerd Font:size=11", "JoyPixels:pixelsize=12" };
static const char dmenufont[]                   = "JetBrainsMono Nerd Font:size=11";
static const char col_gray1[]                   = "#282828";
static const char col_gray2[]                   = "#504945";
static const char col_gray3[]                   = "#bdae93";
static const char col_gray4[]                   = "#ebdbb2";
static const char col_cyan[]                    = "#665c54";
static const char *colors[][3]                  = {
	/*                      fg         bg         border   */
	[SchemeNorm]        = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]         = { col_gray4, "#fb4934",  "#fb4934"  },
    [SchemeStatus]      = { col_gray3, col_gray1,  "#000000"  },  // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]     = { col_gray4, col_cyan,  "#000000"  },   // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]    = { col_gray3, col_gray1,  "#000000"  },  // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]     = { col_gray4, col_cyan,  "#000000"  },   // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]    = { col_gray3, col_gray1,  "#000000"  },  // infobar middle  unselected {text,background,not used but cannot be empty}
};

static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                    instance    title       tags mask     isfloating   monitor */
	{ "Gimp",                   NULL,       NULL,       0,            1,           -1 },
	{ "Steam",                  NULL,       NULL,       0,            1,           -1 },
	{ "VirtualBox Manager",     NULL,       NULL,       0,            1,           -1 },
	{ "KOReader",               NULL,       NULL,       0,            1,           -1 },
};

static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
#include "tcl.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
    { "|||",       tcl },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
    { "HHH",      grid },
    { NULL,       NULL },
};

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-p", ">", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-g", "8", "-l", "5", NULL };
// static const char *termcmd[]  = { "alacritty", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *roficmd[] = {"rofi", "-show", "drun", NULL};

#include "movestack.c"
static Key keys[] = {
/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = roficmd } },
	{ MODKEY,		                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ControlMask,           XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ControlMask,           XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                    XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
    { MODKEY|ControlMask,		    XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { MODKEY|ShiftMask,             XK_r,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
