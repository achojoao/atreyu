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
        TRELLIS_PAGE="page0"
        if [ "$CURRENT_APP" = "Qt Creator" ] || [ "$CURRENT_APP" = "studio" ] || [ "$CURRENT_APP" = "Xcode" ] # develop
        then
            TRELLIS_PAGE="page1";
        elif [ "$CURRENT_APP" = "firefox" ] || [ "$CURRENT_APP" = "Google Chrome" ] # browsing
        then
            TRELLIS_PAGE="page2";
        elif [ "$CURRENT_APP" = "Sublime Text 2" ] # editing
        then
            TRELLIS_PAGE="page3";
        fi
        mosquitto_pub -t toAtreyu -m "$TRELLIS_PAGE"
    fi 
done &

mosquitto_sub -t fromAtreyu | while read KEY
do    
if [ "$KEY" = "0" ] ## Exposé
then
osascript <<EOD
    tell application "System Events"
    key code 103
    end tell
EOD
elif [ "$KEY" = "1" ] # # + Tab
then
osascript <<EOD
    tell application "System Events"
        key down command
        keystroke tab
        key up command
    end tell
EOD
elif [ "$KEY" = "2" ]
then
sleep 2;
osascript <<EOD
    tell application "System Events"
        set frontApp to name of first application process whose frontmost is true
    end tell
EOD
elif [ "$KEY" = "3" ]
then
    echo "Neato cool"
elif [ "$KEY" = "4" ]
then
    echo "Neato cool"
elif [ "$KEY" = "5" ]
then
    echo "Neato cool"
elif [ "$KEY" = "6" ]
then
    echo "Neato cool"
elif [ "$KEY" = "7" ]
then
    echo "Neato cool"
elif [ "$KEY" = "8" ]
then
    echo "Neato cool"
elif [ "$KEY" = "9" ]
then
    echo "Neato cool"
elif [ "$KEY" = "10" ]
then
    echo "Neato cool"
elif [ "$KEY" = "11" ]
then
    echo "Neato cool"
elif [ "$KEY" = "12" ] ##
then
    echo "Neato cool"
elif [ "$KEY" = "13" ] # Search term global
then
    echo "Neato cool"
elif [ "$KEY" = "14" ] # Go to parent
then
    echo "Neato cool"
elif [ "$KEY" = "15" ] # Refactor
then
    echo "Neato cool"
elif [ "$KEY" = "16" ] # Run App
then
    echo "Neato cool"
elif [ "$KEY" = "17" ] # Debug App
then
    echo "Neato cool"
elif [ "$KEY" = "18" ] # Clean App
then
    echo "Neato cool"
elif [ "$KEY" = "19" ] # Show Console
then
    echo "Neato cool"
elif [ "$KEY" = "20" ] # Debug Run
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
elif [ "$KEY" = "21" ] # Debug Next
then
osascript <<EOD
    tell application "System Events"
        set frontApp to name of first application process whose frontmost is true
        if frontApp = "Qt Creator" then
            key down shift
            key down command
            key code 31
            key up shift
            key up command
        else if frontApp = "studio" then            
        else if frontApp = "Xcode" then
        end if
    end tell
EOD
elif [ "$KEY" = "22" ] # Debug In
then
osascript <<EOD
    tell application "System Events"
        set frontApp to name of first application process whose frontmost is true
        if frontApp = "Qt Creator" then
            key down shift
            key down command
            key code 34
            key up shift
            key up command
        else if frontApp = "studio" then            
        else if frontApp = "Xcode" then
        end if
    end tell
EOD
elif [ "$KEY" = "23" ] # Debug Out
then
osascript <<EOD
    tell application "System Events"
        set frontApp to name of first application process whose frontmost is true
        if frontApp = "Qt Creator" then
            key down command
            key code 17
            key up command
        else if frontApp = "studio" then            
        else if frontApp = "Xcode" then
        end if        
    end tell
EOD
elif [ "$KEY" = "24" ] ##
then
    echo "Neato cool"
elif [ "$KEY" = "25" ] 
then
    echo "Neato cool"
elif [ "$KEY" = "26" ] # 
then
    echo "Neato cool"
elif [ "$KEY" = "27" ] #
then
    echo "Neato cool"
elif [ "$KEY" = "28" ] # 
then
    echo "Neato cool"
elif [ "$KEY" = "29" ] # 
then
    echo "Neato cool"
elif [ "$KEY" = "30" ] # 
then
    echo "Neato cool"
elif [ "$KEY" = "31" ] # 
then
    echo "Neato cool"
elif [ "$KEY" = "32" ] # 
then
    echo "Neato cool"
elif [ "$KEY" = "33" ] # 
then
    echo "Neato cool"
elif [ "$KEY" = "34" ] # 
then
    echo "Neato cool"
elif [ "$KEY" = "35" ] # 
then
    echo "Neato cool"
elif [ "$KEY" = "36" ] ##
then
    echo "Enga"
elif [ "$KEY" = "37" ] #
then
    echo "Neato cool"
elif [ "$KEY" = "38" ] #
then
    echo "Neato cool"
elif [ "$KEY" = "39" ] #
then
    echo "Neato cool"
elif [ "$KEY" = "40" ] #
then
    echo "Neato cool"
elif [ "$KEY" = "41" ] #
then
    echo "Neato cool"
elif [ "$KEY" = "42" ] #
then
    echo "Neato cool"
elif [ "$KEY" = "43" ] #
then
    echo "Neato cool"
elif [ "$KEY" = "44" ] #
then
    echo "Neato cool"
elif [ "$KEY" = "45" ] #
then
    echo "Neato cool"
elif [ "$KEY" = "46" ] #
then
elif [ "$KEY" = "47" ] #
    echo "Neato cool"
fi
done
