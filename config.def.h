/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const Gap default_gap = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMonoNerdFont-Regular:size=12", "KiwiMaru-Regular:size=12" };
static const char dmenufont[]       = "JetBrainsMonoNerdFont-Regular:size=12";
static const char dmenuprompt[]		= "Program to run => ";
static const char col_unsel_bg[]    = "#11111b"; // mocha crust
static const char col_unsel_bd[]    = "#6c7086"; // mocha overlay0
static const char col_unsel_fg[]    = "#a6adc8"; // mocha subtext0
static const char col_sel_fg[]      = "#cdd6f4"; // mocha text
static const char col_sel_bg[]      = "#1e1e2e"; // mocha base
static const char col_sel_bd[] 		= "#b4befe"; // mocha lavender
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_unsel_fg, col_unsel_bg, col_unsel_bd },
	[SchemeSel]  = { col_sel_fg, col_sel_bg,  col_sel_bd  },
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "タイル",      tile },    /* first entry is default */
	{ "フロート",      NULL },    /* no layout function means floating behavior */
	{ "モノクル",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-p", dmenuprompt, "-fn", dmenufont, "-nb", col_unsel_bg, "-nf", col_unsel_fg, "-sb", col_sel_bg, "-sf", col_sel_fg, NULL };
static const char *termcmd[]  = { "st", NULL };
//static const char *volupcmd[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+10%", NULL } ;
//static const char *voldowncmd[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-10%", NULL } ;
//static const char *volmutecmd[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL } ;

static const char *volupcmd[] = { "/home/clair/Scripts/f_keys.sh", "volume_up", NULL } ;
static const char *voldowncmd[] = { "/home/clair/Scripts/f_keys.sh", "volume_down", NULL } ;
static const char *volmutecmd[] = { "/home/clair/Scripts/f_keys.sh", "mute_volume", NULL } ;
static const char *micmutecmd[] = { "/home/clair/Scripts/f_keys.sh", "mute_mic", NULL } ;

static const char *screenshot_quickcmd[] = { "gnome-screenshot", "-a", NULL } ;
static const char *screenshot_interactivecmd[] = { "gnome-screenshot", "-i", NULL } ;
static const char *exitcmd[] = { "bash", "/home/clair/Scripts/confirmexit.sh", "-m", dmenumon, "-fn", dmenufont, "-nb", col_unsel_bg, "-nf", col_unsel_fg, "-sb", col_sel_bg, "-sf", col_sel_fg, NULL } ;
static const char *brightnessmenucmd[] = { "bash", "/home/clair/Scripts/setbrightness.sh", "-m", dmenumon, "-fn", dmenufont, "-nb", col_unsel_bg, "-nf", col_unsel_fg, "-sb", col_sel_bg, "-sf", col_sel_fg, NULL } ;
static const char *volumemenucmd[] = { "bash", "/home/clair/Scripts/volumecontrol.sh", "-m", dmenumon, "-fn", dmenufont, "-nb", col_unsel_bg, "-nf", col_unsel_fg, "-sb", col_sel_bg, "-sf", col_sel_fg, NULL } ;

static const Key keys[] = {
	/* modifier                     key        function        	argument */
	{ 0,		                    XK_Super_L,spawn,          	{.v = dmenucmd } },
	{ MODKEY,			            XK_Return, spawn,          	{.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      	{0} },
	{ MODKEY,                       XK_j,      focusstack,     	{.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     	{.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     	{.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     	{.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       	{.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       	{.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           	{0} },
	{ MODKEY,                       XK_Tab,    view,           	{0} },
	{ MODKEY,			            XK_q,      killclient,     	{0} },
	{ MODKEY,                       XK_t,      setlayout,      	{.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      	{.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,  	   	{.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      	{0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, 	{0} },
	{ MODKEY,                       XK_0,      view,           	{.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            	{.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       	{.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       	{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         	{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         	{.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	{ 0,			  XF86XK_AudioRaiseVolume, spawn, 			{.v = volupcmd} },
	{ 0, 			  XF86XK_AudioLowerVolume, spawn, 			{.v = voldowncmd} },
	{ 0,				 XF86XK_AudioMute, 		spawn, 			{.v = volmutecmd} },
	{ 0,				 XF86XK_AudioMicMute, 		spawn, 			{.v = micmutecmd} },
	{ 0, 							XK_Print, 	spawn, 			{.v = screenshot_quickcmd} },
	{ MODKEY,						XK_Print,	spawn,			{.v = screenshot_interactivecmd} },
	{ MODKEY,						XK_b,		spawn,			{.v = brightnessmenucmd} },
	{ MODKEY,						XK_v,		spawn,			{.v = volumemenucmd} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	// below is actually a restart due to ~/.rundwm running dwm in a while loop
	{ MODKEY,        			    XK_r,      quit,           {0} }, 
	// below is a script that spawns dmenu prompting "exit? yes/no"
	// and then either exits or doesnt based on user choice
	{ MODKEY|ShiftMask,				XK_e,	   spawn,			{.v = exitcmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

