#!/bin/sh

cd /home/root/pApp_MVE_Upgraded_1V0

if grep -E 'gpio-0.*lo' /sys/kernel/debug/gpio; then
    echo Factory Reset
	if [ -e fdata/pApp.Factory ]
        then
                echo "ok"
		cp -f fdata/pApp.Factory pApp_MVE_Upgraded_1V0
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
		cp cdata/newfirmware pApp_MVE_Upgraded_1V0
		rm cdata/newfirmware
		chmod +x pApp_MVE_Upgraded_1V0
		rm  tmp/*
    fi
	
fi

./pApp_MVE_Upgraded_1V0

exit 0


