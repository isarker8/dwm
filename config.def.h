/* See LICENSE file for copyright and license details. */

/* appearance */
static       unsigned int borderpx  = 3;        /* border pixel of windows */
static       unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 5;        /* gaps between windows */
static       int showbar            = 1;        /* 0 means no bar */
static       int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=13", "Noto Kufi Arabic:size=13" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=15";

/* default colors used if xrdb is not loaded */
static char normbgcolor[]           = "#2e3440";
static char normbordercolor[]       = "#4c566a";
static char normfgcolor[]           = "#d8dee9";

static char selfgcolor[]            = "#eceff4";
static char selbordercolor[]        = "#a3be8c";
static char selbgcolor[]            = "#b48ead";

static char *colors[][3] = {
        /*               fg           bg           border   */
		[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
		[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
		/* for bar --> {text, background, null} */
		[SchemeStatus]  = { normfgcolor, normbgcolor,  normbgcolor  }, /* status R */
        [SchemeTagsSel]  = { normfgcolor, normbgcolor,  normbgcolor  }, /* tag L selected */
		[SchemeTagsNorm]  = { selbordercolor, normbgcolor,  normbgcolor  }, /* tag L unselected */
		[SchemeInfoSel]  = { normfgcolor, normbgcolor,  normbgcolor  }, /* info M selected */
		[SchemeInfoNorm]  = { normfgcolor, normbgcolor,  normbgcolor  }, /* info M unselected */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static float mfact = 0.55;           /* factor of master area size [0.05..0.95] */
static int nmaster = 1;              /* number of clients in master area */
static int resizehints = 1;          /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
 	{ "",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define STATUSBAR "dwmblocks"
#define BROWSER "waterfox"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-c", "-l", " 5", "-bw", " 3", "-p", "Run:", NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_BackSpace, xrdb,        {.v = NULL } },
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

    /* Gaps */
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },

    /* Other */
    { MODKEY,                       XK_w,      spawn,          {.v = (const char*[]){ BROWSER, NULL } } },
    { MODKEY|ShiftMask,		        XK_w,      spawn,          {.v = (const char*[]){ "wallpapermenu", NULL } } }, 
    { MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("powermenu") }, 
    { MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("screenshot") },
    { MODKEY|ShiftMask,             XK_a,      spawn,          SHCMD("audio") },
    { MODKEY|ShiftMask,             XK_v,      spawn,          SHCMD("clipmenu -b -bw 3 -l 5 -i -p '󰅌 Clipboard:'") },    /* Select from clipmenu add to primary */
    { MODKEY|ShiftMask,             XK_BackSpace, spawn,       SHCMD("toggle-layout") },    
    { MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("bookmarks") },    

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkStatusText,        0,              6,              sigstatusbar,   {.i = 6} },
	{ ClkStatusText,        0,              7,              sigstatusbar,   {.i = 7} },
	{ ClkStatusText,        0,              8,              sigstatusbar,   {.i = 8} },
	{ ClkStatusText,        0,              9,              sigstatusbar,   {.i = 9} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
   	{ ClkStatusText,        ShiftMask,  	Button3,	    spawn,          SHCMD("st -e vim ~/repos/Suckless/dwmblocks/blocks.h") },
};

