#!/bin/sh

rmtrash ~/Library/Quicklook/QLFit.qlgenerator; xcodebuild -configuration Debug && cp -rv build/Debug/QLFit.qlgenerator ~/Library/Quicklook &&  qlmanage -r && qlmanage -m plugins; qlmanage -d 2 -p 2012-06-02-13-24-04.fit
