#!/bin/bash

# Ubuntu/14.04/3.16.0-43-generic/x64
# Ubuntu/16.04/4.4.0-47-generic/x64

[ -n "`cat /etc/issue | grep "Ubuntu 16.04"`" ] && echo "Ubuntu 16.04" && KER_VER="4.4.0-47-generic"
[ -n "`cat /etc/issue | grep "Ubuntu 14.04"`" ] && echo "Ubuntu 14.04" && KER_VER="3.16.0-43-generic"

cp /etc/default/grub /etc/default/grub.old
sed -ir "s/GRUB_DEFAULT=.*/GRUB_DEFAULT=\"Advanced options for Ubuntu>Ubuntu, with Linux $KER_VER\"/g" /etc/default/grub
# update-grub
apt-get update
apt-get install -y linux-image-extra-$KER_VER
# reboot

mkdir -p /appex
cat > /appex/appexinstall.sh << TEMPEOF
wget --no-check-certificate -qO /tmp/appex.sh "https://raw.githubusercontent.com/0oVicero0/serverSpeeder_Install/master/appex.sh" && bash /tmp/appex.sh 'install' << EOF

EOF
cp /etc/rc.local.old.ruisu /etc/rc.local 
rm /etc/rc.local.old.ruisu
TEMPEOF

# bash /appex/appexinstall.sh 
# ps aux | grep appex


if [ ! -f "/etc/rc.local.old.ruisu" ]; then
    echo "first time run this script, backup the rc.local"
    cp /etc/rc.local /etc/rc.local.old.ruisu
fi
# cp /etc/rc.local /etc/rc.local.old.ruisu
sed -i '$d' /etc/rc.local
echo "bash /appex/appexinstall.sh" >> /etc/rc.local
echo "exit 0" >> /etc/rc.local
chmod 0755 /etc/rc.local
reboot
