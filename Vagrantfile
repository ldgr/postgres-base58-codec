# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.hostname = "cenv-virtualbox"
  config.vm.box = "ubuntu/trusty64"
  config.vm.synced_folder "../postgres-base58-codec", "/home/vagrant/workspace"
  config.vm.provider "virtualbox" do |vb|
    vb.memory = "1024"
  end
  config.vm.network "private_network", type: "dhcp"
  config.vm.provision :file, source: '.vimrc', destination: '/home/vagrant/.vimrc'
  config.vm.provision "shell", inline: <<-SHELL
        sudo apt-get update
        sudo apt-get install -y git htop ncdu python python-dev python-pip tmux tree vim gcc texinfo automake gdb build-essential postgresql-server-dev-all postgresql libgmp3-dev postgresql-contrib-9.3
  SHELL
end

