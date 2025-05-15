wget https://download.opensuse.org/repositories/home:/manuelschneid3r/Debian_12/amd64/albert_0.27.8-0+701.1_amd64.deb
sudo apt install xorg -y
sudo apt install libx11-dev -y
sudo apt install ./albert_0.27.8-0+701.1_amd64.deb -y
sudo apt install numix-icon-theme -y
make
rm -f -- ~/.xinitrc
echo "exec albert" >> ~/.xinitrc
echo "exec $(realpath wm)" >> ~/.xinitrc