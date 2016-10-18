# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

SHARED_DIR = "/opt/linux-playground"

INSTALL_DEPS=<<EOF
/bin/true
EOF

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|

    config.vm.box = "ubuntu/trusty64"

    config.vm.define "dev" do |dev|
        dev.vm.synced_folder ".", SHARED_DIR
        dev.vm.provision "shell", inline: "echo 'cd #{SHARED_DIR}' >> /home/vagrant/.bashrc"

        dev.vm.provision "shell", inline: "#{INSTALL_DEPS}"
    end

    if Vagrant.has_plugin?("vagrant-cachier")
        config.cache.scope = :box
    end

end
