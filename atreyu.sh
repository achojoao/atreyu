#!/bin/bash

#insert in slack
#shutdown
#toggle mute
#search
#replace
#copy
#paste

CURRENT_APP=""
while :
do
    APP=$(osascript <<EOD
        tell application "System Events"
            set frontApp to name of first application process whose frontmost is true
            return frontApp
        end tell
EOD)
    if [ "$APP" != "$CURRENT_APP" ]
    then
        CURRENT_APP="$APP"
        TRELLIS_PAGE=""
        if [ "$CURRENT_APP" = "Terminal" ]
        then
            TRELLIS_PAGE="page3";
        elif [ "$CURRENT_APP" = "Qt Creator" ] || [ "$CURRENT_APP" = "studio" ] || [ "$CURRENT_APP" = "Xcode" ] 
        then
            TRELLIS_PAGE="page1";
        elif [ "$CURRENT_APP" = "firefox" ] || [ "$CURRENT_APP" = "Google Chrome" ]
        then
            TRELLIS_PAGE="page2";
        elif [ "$CURRENT_APP" = "Sublime Text 2" ]
        then
            TRELLIS_PAGE="page0";
        fi
        mosquitto_pub -t toAtreyu -m "$TRELLIS_PAGE"
    fi 
done &

mosquitto_sub -t fromAtreyu | while read MESSAGE
do
if [ "$MESSAGE" = "0" ] #Page 0 #F11
then
osascript <<EOD
    tell application "System Events"
    key code 103
    end tell
EOD
elif [ "$MESSAGE" = "1" ] # # + Tab
then
osascript <<EOD
    tell application "System Events"
        key down command
        keystroke tab
        key up command
    end tell
EOD
elif [ "$MESSAGE" = "2" ]
then
sleep 2;
osascript <<EOD
    tell application "System Events"
        set frontApp to name of first application process whose frontmost is true
    end tell
EOD
elif [ "$MESSAGE" = "3" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "4" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "5" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "6" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "7" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "8" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "9" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "10" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "11" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "12" ] #Page 1
then
    echo "Neato cool"
elif [ "$MESSAGE" = "13" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "14" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "15" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "16" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "17" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "18" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "19" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "20" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "21" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "22" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "23" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "24" ] #Page 2
then
    echo "Neato cool"
elif [ "$MESSAGE" = "25" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "26" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "27" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "28" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "29" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "30" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "31" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "32" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "33" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "34" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "35" ]
then
    echo "Neato cool"
elif [ "$MESSAGE" = "36" ] #Page 3 
then
    echo "Enga"
elif [ "$MESSAGE" = "37" ] # Search term global
then
    echo "Neato cool"
elif [ "$MESSAGE" = "38" ] # Go to parent
then
    echo "Neato cool"
elif [ "$MESSAGE" = "39" ] # Refactor
then
    echo "Neato cool"
elif [ "$MESSAGE" = "40" ] # Run App
then
    echo "Neato cool"
elif [ "$MESSAGE" = "41" ] # Debug App
then
    echo "Neato cool"
elif [ "$MESSAGE" = "42" ] # Clean App
then
    echo "Neato cool"
elif [ "$MESSAGE" = "43" ] # Show Console
then
    echo "Neato cool"
elif [ "$MESSAGE" = "44" ] # Debug Run
then
osascript <<EOD
    tell application "System Events"
        set frontApp to name of first application process whose frontmost is true
        if frontApp = "Qt Creator" then
            key down command
            key code 16
            key up command
        else if frontApp = "studio" then
            key down control
            key code 2
            key up control
        else if frontApp = "Xcode" then
        end if
    end tell
EOD
elif [ "$MESSAGE" = "45" ] # Debug Next
then
osascript <<EOD
    tell application "System Events"
        key down shift
        key down command
        key code 31
        key up shift
        key up command
    end tell
EOD
elif [ "$MESSAGE" = "46" ] # Debug In
then
osascript <<EOD
    tell application "System Events"
        key down shift
        key down command
        key code 34
        key up shift
        key up command
    end tell
EOD
else # Debug Exit
osascript <<EOD
    tell application "System Events"
        key down command
        key code 17
        key up command
    end tell
EOD
fi
done
