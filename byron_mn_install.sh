#/bin/bash
echo "*******************************"
echo "*    Byron-Core Masternode    *"
echo "*           SETUP             *"
echo "*******************************"
echo && echo && echo
cd /root
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

IP==$(curl -s4 icanhazip.com)
echo -e "${GREEN}Please enter your private key: (Copy from Windows and right click to paste and press enter)${NC}" 
read KEY
sleep 2

sudo apt-get update -y &>/dev/null
sudo apt-get upgrade -y &>/dev/null
echo -e "${GREEN}Completion: 2%...${NC}"
sudo wget https://github.com/Byronteam/Byron/releases/download/V1.0/ubuntu-1804.zip
echo -e "${GREEN}Completion: 3%...${NC}"

echo -e "${GREEN}Completion: 5%...${NC}"
sudo apt-get install libboost-all-dev libevent-dev software-properties-common -y &>/dev/null
sudo add-apt-repository ppa:bitcoin/bitcoin -y &>/dev/null
echo -e "${GREEN}Completion: 10%...${NC}"
sudo apt-get update &>/dev/null
echo -e "${GREEN}Completion: 20%...${NC}"
sudo apt-get install libdb4.8-dev libdb4.8++-dev -y &>/dev/null
echo -e "${GREEN}Completion: 30%...${NC}"
sudo apt-get install libpthread-stubs0-dev -y &>/dev/null
sudo apt-get install libzmq3-dev -y &>/dev/null
echo -e "${GREEN}Completion: 40%...${NC}"
sudo apt install -y make build-essential libtool software-properties-common autoconf libssl-dev libboost-dev libboost-chrono-dev libboost-filesystem-dev \
libboost-program-options-dev libboost-system-dev libboost-test-dev libboost-thread-dev sudo automake git curl libdb4.8-dev \
bsdmainutils libdb4.8++-dev libminiupnpc-dev libgmp3-dev ufw pkg-config libevent-dev libdb5.3++ unzip libzmq5 &>/dev/null
echo -e "${GREEN}Completion: 75%...${NC}"
sudo apt install unzip
sudo unzip ubuntu-1804.zip

sleep 2
cd /var
sudo touch swap.img &>/dev/null
sudo chmod 600 swap.img &>/dev/null
sudo dd if=/dev/zero of=/var/swap.img bs=1024k count=2000 &>/dev/null
sudo mkswap /var/swap.img &>/dev/null
sudo swapon /var/swap.img &>/dev/null
sudo free &>/dev/null
sudo echo "/var/swap.img none swap sw 0 0" >> /etc/fstab &>/dev/null
echo -e "${GREEN}Completion: 85%...${NC}"
cd
sleep 2
sudo apt-get install -y ufw &>/dev/null
sudo ufw allow ssh/tcp &>/dev/null
sudo ufw limit ssh/tcp &>/dev/null
sudo ufw allow 27215/tcp &>/dev/null
sudo ufw logging on &>/dev/null
echo "y" | sudo ufw enable &>/dev/null
echo -e "${GREEN}Completion: 90%...${NC}"
sleep 2
cd /root
sudo chmod +x byron*
sudo mv byron* /usr/local/bin
sleep 2
sudo mkdir /root/.byron
echo "rpcuser=user"`shuf -i 100000-10000000 -n 1` > /root/.byron/byron.conf
echo "rpcpassword=pass"`shuf -i 100000-10000000 -n 1` >> /root/.byron/byron.conf
echo "rpcport=27216" >> /root/.byron/byron.conf
echo "rpcallowip=127.0.0.1" >> /root/.byron/byron.conf
echo "listen=1" >> /root/.byron/byron.conf
echo "server=1" >> /root/.byron/byron.conf
echo -e "${GREEN}Completion: 95%...${NC}"
echo "daemon=1" >> /root/.byron/byron.conf
echo "staking=0" >> /root/.byron/byron.conf
echo "maxconnections=250" >> /root/.byron/byron.conf
echo "masternode=1" >> /root/.byron/byron.conf
echo "masternodeaddr$IP:27215" >> /root/.byron/byron.conf
echo "masternodeprivkey=$KEY" >> /root/.byron/byron.conf
echo -e "${GREEN}Completion: 99%...${NC}"
cd /root
echo -e "${GREEN}Completion: 100%...${NC}"
echo -e "Thank you for installing the byron daemon. Please configure you masternode.conf in windows ${RED}NEXT${NC} step. start alias"
byrond -datadir=/root/.byron
echo -e "${GREEN}you masternode is installed and runing%...${NC}"
