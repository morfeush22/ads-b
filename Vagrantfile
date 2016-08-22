# -*- mode: ruby -*-
# vi: set ft=ruby :

$script = <<SCRIPT
ECLIPSE_DL=http://mirror.onet.pl/pub/mirrors/eclipse//technology/epp/downloads/release/kepler/SR2/eclipse-cpp-kepler-SR2-linux-gtk-x86_64.tar.gz
GNURADIO_DL=http://www.sbrac.org/files/build-gnuradio
REPO_DL=https://github.com/morfeush22/ads-b.git
VIRTUALBOX_DL=http://download.virtualbox.org/virtualbox/5.1.2/VBoxGuestAdditions_5.1.2.iso

GIT_USER_NAME=kpatro
GIT_USER_EMAIL=patro.kacper@gmail.com


yum update -y
yum install -y epel-release
yum install -y cmake dkms policycoreutils-python wget @"Development Tools" @"X Window system" @"xfce"
yum install -y alsa-utils sox usbutils
yum install -y valgrind git

git config --global user.name $GIT_USER_NAME
git config --global user.email $GIT_USER_EMAIL

provision_file=/etc/provision\.sh

(
cat <<'EOF'
#!/bin/bash

wget -c $VIRTUALBOX_DL -P /tmp/
virtualbox_base="${VIRTUALBOX_DL##*/}"
chmod +x /tmp/$virtualbox_base
mount -t iso9660 -o ro /tmp/$virtualbox_base /media/ 
/media/VBoxLinuxAdditions.run
sync && umount /media/

cd /tmp && wget $GNURADIO_DL && chmod a+x ./build-gnuradio && ./build-gnuradio
sed -i "$ a export PYTHONPATH=/usr/local/lib64/python2.7/site-packages" /home/vagrant/.bashrc

sed -i "\@$provision_file@ d" /etc/rc.d/rc.local
chmod -x /etc/rc.d/rc.local
systemctl set-default graphical.target

reboot
EOF
) > $provision_file

sed -i "$ a $provision_file" /etc/rc.d/rc.local
chmod +x $provision_file
chmod +x /etc/rc.d/rc.local

echo "blacklist dvb_usb_rtl28xxu" >> /etc/modprobe.d/rtlsdr.conf

cd /home/vagrant
git clone $REPO_DL
wget -qO- $ECLIPSE_DL | tar xvz
eclipse_launcher=/home/vagrant/Desktop/eclipse\.desktop

(
cat <<'EOF'
[Desktop Entry]
Version=1.0
Type=Application
Name=eclipse
Comment=
Exec=/home/vagrant/eclipse/eclipse
Icon=/home/vagrant/eclipse/icon.xpm
Path=/home/vagrant/eclipse
Terminal=false
StartupNotify=false
EOF
) > $eclipse_launcher

chmod +x $eclipse_launcher

reboot
SCRIPT


Vagrant.configure(2) do |config|
  config.vm.define "ws" do |ws|
	ws.vm.box = "centos/7"
    ws.vm.synced_folder ".", "/home/vagrant/sync", disabled: true
    ws.vm.network "public_network"
    ws.vm.provision "shell", inline: $script
    
    ws.vm.provider "virtualbox" do |vb|
        vb.gui = true
        vb.customize ["modifyvm", :id, "--usb", "on"]
        vb.customize ["modifyvm", :id, "--usbehci", "on"]
        vb.customize ["usbfilter", "add", "0", 
            "--target", :id, 
            "--name", "59d30485-664f-4b77-abba-e938fa81c801",
            "--manufacturer", "Realtek",
            "--product", "RTL2838UHIDIR"]
    end
  end
end
