## dwm - dynamic window manager - ابراهيم's build
![my build]

note: I'd highly recommend setting up your own build! using mine or anyone else's is a starting point, but patching dwm manually not only allows for precise customization, but it will also allow you to learn how your WM works.
a great way to test build changes without refreshing/restarting your running WM is with [Xephyr](https://wiki.archlinux.org/title/Xephyr), a nested X server that runs as an application.

## patches applied:
some occasional modification here and there;
* [attachaside](https://dwm.suckless.org/patches/attachaside/)
* [barpadding](https://dwm.suckless.org/patches/barpadding/)
* [bidi (RTL TEXT)](https://dwm.suckless.org/patches/bidi/)
* [centeredwindowname](https://dwm.suckless.org/patches/centeredwindowname/)
* [colorbar](https://dwm.suckless.org/patches/colorbar/)
* [fullgaps](https://dwm.suckless.org/patches/fullgaps/)
* [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/)
* [statuscmd](https://dwm.suckless.org/patches/statuscmd/)
* [unicode ellipses](https://dwm.suckless.org/patches/unicode-ellipsis/)
* [urgent border](https://dwm.suckless.org/patches/urgentborder/)
* [xrdb](https://dwm.suckless.org/patches/xrdb/)


## installation, setup:
```
git clone https://github.com/isarker8/dwm
cd dwm
sudo make clean install
```

* Basic ```~/.xinitrc``` requirement: ```exec dwm```

* Configure settings (fonts, bindings, gap pixels, etc) in **config.def.h** before compiling.
  - Defaults: Mod is bound to the windows key
  - ```mod + enter``` to open terminal
  - ```mod + q``` to quit window
  - ```mod + shift + q``` to fully exit


I use [dwmblocks-async](https://github.com/UtkarshVerma/dwmblocks-async) for my statusbar ([bar scripts](https://github.com/isarker8/.dotfiles/tree/main/scripts)).
If you intend to use another statusbar, [modify dwm appropriately](https://dwm.suckless.org/patches/anybar/)


## colours, other stuff:
If you aren't using ```~/.Xresources``` with or without [pywal16](https://github.com/eylles/pywal16).


I have wal generate a template containing [dwm Xresource strings](https://dwm.suckless.org/patches/xrdb/). Then, I merge it with wal's auto-generated Xresources file, using ```xrdb -merge```.


```~/.config/wal/templates/colors.Xresources```
``` dwm.normbordercolor: {color0}
dwm.normbgcolor:     {background}
dwm.normfgcolor:     {foreground}
dwm.selbordercolor:  {color4}
dwm.selbgcolor:      {color4}
dwm.selfgcolor:      {color15}

dmenu.background:     {background}
dmenu.foreground:     {foreground}
dmenu.backgroundSel:  {color4}
dmenu.foregroundSel:  {color15}
dmenu.backgroundOut:  {background}
dmenu.foregroundOut:  {color4}
```

After creating the template, add these to your wal post-script for automatic xrdb merge and refresh.

```
ln -sf ~/.cache/wal/colors.Xresources ~/.Xresources
xrdb -merge ~/.cache/wal/colors.Xresources
xdotool key super+backspace # xrdb refresh keybind
```

Alternatively, if you prefer a different color-setting method, follow the instructions on [pywal16's wiki](https://github.com/eylles/pywal16/wiki/Customization#dwm).


I use [slock](https://tools.suckless.org/slock/) for a lockscreen activated via keybind.

My config has a few glyphs used cosmetically; for those to render properly, install a [font with extra glyphs](https://www.nerdfonts.com/#home).
