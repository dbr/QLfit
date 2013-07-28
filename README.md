# .fit Quicklook plugin

A Quicklook plugin for the questionably abbreviated ["Flexible and
Interoperable Data Transfer" (.FIT) files][fit], created by devices like the
Garmin Edge 500

[fit]: http://www.thisisant.com/pages/products/fit-sdk


## Installation

Copy the `QLFit.qlgenerator` file to `~/Library/QuickLook/`

To do this (based on OS X 10.7):

* In the Finder menu bar click "Go > Go to folder.."
* Enter `~/Library`
* Find or create a `QuickLook` folder
* Drag the `QLFit.qlgenerator` into this folder

If it doens't seem to work, you could try running the command
`qlmanage -r` in a terminal (or rebooting, if it's easier)

## Building

Open the Xcode project, and click build.

## Supported operating systems

Whatever I am currently running, currently OS X 10.7
