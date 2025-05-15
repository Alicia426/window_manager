wget https://download.opensuse.org/repositories/home:/manuelschneid3r/Debian_12/amd64/albert_0.27.8-0+701.1_amd64.deb
sudo apt install xorg -y
sudo apt install libx11-dev -y
sudo apt install ./albert_0.27.8-0+701.1_amd64.deb -y
sudo apt install pop-icon-theme -y
sudo apt install build-essential libssl-dev libffi-dev python3 python3-dev
sudo apt install python3-xlib
make
rm -f -- ~/.xinitrc
echo "exec albert" >> ~/.xinitrc
echo "exec python3 $(realpath wm)" >> ~/.xinitrc