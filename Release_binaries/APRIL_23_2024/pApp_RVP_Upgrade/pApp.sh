#!/bin/sh

cd /home/root/pApp_RVP_Upgrade

if grep -E 'gpio-0.*lo' /sys/kernel/debug/gpio; then
    echo Factory Reset
	if [ -e fdata/pApp.Factory ]
        then
                echo "ok"
		cp -f fdata/pApp.Factory pApp_RVP_Upgrade
		mkdir cdata
		mkdir tmp
		mkdir tdata
		rm  cdata/*
		rm  tmp/*
		rm  tdata/*
        else
            echo "nok"
    fi
else
    echo normal boot
	
	if [ -e cdata/newfirmware ]
        then
                echo "ok"
		cp cdata/newfirmware pApp_RVP_Upgrade
		rm cdata/newfirmware
		chmod +x pApp_RVP_Upgrade
		rm  tmp/*
    fi
	
fi

echo 7 > /sys/class/backlight/backlight/brightness

sleep 2

./pApp_RVP_Upgrade

exit 0


