#!/bin/sh
echo "#####################################"
echo "    MVE SCRIPT TO UPGPRADE LINUX     "
echo "#####################################"
KernelZimage='zImage'
KernelDTBemmc='imx6ul-var-dart-6ulcustomboard-emmc-wifi.dtb'
KernelDTBsd='imx6ul-var-dart-6ulcustomboard-emmc-sd-card.dtb'
KernelMVEDTB='imx6ul-var-dart-MVE.dtb'

AppPath='/home/root/'

ScriptFile='pApp.sh'
ScriptPath='/opt'

cdataPath='cdata'

pAppUSBpath='pApp_MVE_Upgraded_1V0'
pAppNAME='pApp_MVE_Upgraded_1V0'
pAppFolder='pApp_MVE_Upgraded_1V0'

echo "mount the pendrive"

usbdev='/dev/sda1'

PenDriveMountPath='/home/root/PenDriveMount'

emmcdev='/dev/mmcblk1p1'
emmcDriveMountPath='/home/root/eMMCMount'
echo "mount emmc $emmcdev"

mkdir -p $emmcDriveMountPath
mount $emmcdev $emmcDriveMountPath

sleep 3

mkdir -p $PenDriveMountPath
mount $usbdev $PenDriveMountPath

sleep 3

cp $PenDriveMountPath/$pAppUSBpath/$KernelZimage $emmcDriveMountPath/$KernelZimage
cp $PenDriveMountPath/$pAppUSBpath/$KernelDTBemmc $emmcDriveMountPath/$KernelDTBemmc
cp $PenDriveMountPath/$pAppUSBpath/$KernelDTBsd $emmcDriveMountPath/$KernelDTBsd
cp $PenDriveMountPath/$pAppUSBpath/$KernelMVEDTB $emmcDriveMountPath/$KernelMVEDTB

sleep 3
sync
sync
umount $emmcDriveMountPath
umount $emmcdev
rm -rf $emmcDriveMountPath

sleep 3
sync
sync

echo "#####################################"
echo "       UPGRADING LINUX DONE          "
echo "#####################################"

echo "#####################################"
echo "MVE SCRIPT TO UPGRATE THE QT FIRMWARE"
echo "#####################################"

echo "mouting the pendrive --> $PenDriveMountPath"
echo "system app path is ----> $AppPath"
echo "usb application path --> $pAppUSBpath"
echo "pApp application name -> $pAppNAME"

echo "MVE Checking for errors"
cp -r $PenDriveMountPath/$pAppFolder $AppPath
cp $PenDriveMountPath/$pAppFolder/$pAppNAME $AppPath/$pAppFolder/$cdataPath/newfirmware
cp $PenDriveMountPath/$pAppFolder/$ScriptFile $ScriptPath/$ScriptFile

umount $PenDriveMountPath/
umount $usbdev*

echo "MVE Unmounting is Successful"

rm -rf $PenDriveMountPath

echo "#####################################"
echo "      QT APP UPGRADE COMPLETE!!!!    "
echo "#####################################"

echo "*************************************"
echo "      MUST RESTART THE SYSTEM!!!!    "
echo "*************************************"
