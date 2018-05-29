Note: Preliminary readme

# MidiDeck
This project will allow you to use your MIDI keyboard as a stream deck.
A stream deck is helpful when you live stream and wants to play some cool sounds.

Currently the MidiController project is the POC project that is used for MIDI exploration.

The MIDI device used is Novation Launchkey Mini

## My intentions
This project should not be dependent on any other 3rd-party library.
It will use only the Win32 APIs, C++ runtime and STL.
Same goes for the UI - only GDI and GDI+ will be used, and if any more advanced graphics
will be neede it will probably use OpenGL.
