#!/bin/sh

rmtrash ~/Library/Quicklook/QLFit.qlgenerator; xcodebuild -configuration Debug && cp -rv build/Debug/QLFit.qlgenerator ~/Library/Quicklook &&  qlmanage -r && qlmanage -m plugins; qlmanage -d 2 -p wide.fit; qlmanage -p tall.fit
