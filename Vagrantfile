# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

SHARED_DIR = "/opt/linux-playground"

INSTALL_DEPS=<<EOF
/bin/true
EOF

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|

    config.vm.define "ubuntu", primary: true do |ubuntu|
        ubuntu.vm.box = "ubuntu/trusty64"
        ubuntu.vm.synced_folder ".", SHARED_DIR
        ubuntu.vm.provision "shell", inline: "echo 'cd #{SHARED_DIR}' >> /home/vagrant/.bashrc"

        ubuntu.vm.provision "shell", inline: "#{INSTALL_DEPS}"
    end

    config.vm.define "centos" do |centos|
        # I couldn't get a bunch of Centos 7 images to work with synced folders (requires guest additions), this box does seem to work
        centos.vm.box = "https://github.com/tommy-muehle/puppet-vagrant-boxes/releases/download/1.1.0/centos-7.0-x86_64.box"
        centos.vm.synced_folder ".", SHARED_DIR
        centos.vm.provision "shell", inline: "echo 'cd #{SHARED_DIR}' >> /home/vagrant/.bashrc"
    end

    if Vagrant.has_plugin?("vagrant-cachier")
        config.cache.scope = :box
    end

end
