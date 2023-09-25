# AnsiEditor
A QT6-based WYSIWYG ANSI-CP437 files Editor written in c++

## Description
AnsiEditor is a WYSIWYG (What You See Is What You Get) editor of ANSI-CP437 files, graphics files viewable in the console of MSDOS systems, very popular in the 80s and 90s due to the use made of them by the [BBSs](https://en.wikipedia.org/wiki/Bulletin_board_system) of the time.

AnsiEditor is a WYSIWYG (What You See Is What You Get) editor of ANSI-CP437 files, graphics files viewable in the console of MSDOS systems, very popular in the 80s and 90s due to the use made of them by the BBSs of the time.

It is an editor that allows you to use all the graphic characters of the CP437 set, in 8+8 foreground colors and 8 background colors, with the possibility of using brigth text and blink text. Furthermore, the editor has the ability to independently draw filled rectangles and frames.

The project is written for Linux and is based on Qt6. With a few changes, you can also adapt it to Windows and Mac.

## ScreenShots
![Program Screenshot](/assets/Main.png)

![Views](/assets/AllOpen.png)

## Installation
To install AnsiEditor you need to do some actions in your shell:

    git clone https://github.com/felmur/AnsiEditor.git
    cd AnsiEditor
    qmake6
    make
    sudo make install

**NOTICE:** On some system, qmake6 is simply **qmake**.

Then, you can run AnsiEditor from your bash with:

    ansieditor

Alternatively, you can launch the editor from your KDE-Plasma menù:

![Menu](/assets/menu.png)



**Enjoy**
