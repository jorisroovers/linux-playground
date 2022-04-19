# Nix

Linux/Unix package manager with atomic upgrades and rollbacks, side-by-side installation of multiple versions of a package, multi-user package management and easy setup of build environments.

# Installation
```sh
# Install
vagrant up ubuntu
vagrant ssh ubuntu
curl https://nixos.org/nix/install | sh
```

# Basics
```sh
# Install package
# Note that nix by default uses a huge amount of memory: https://github.com/NixOS/nix/issues/1910
# For this reason, you need to use -f and -iA
nix-env -f '<nixpkgs>' -iA hello

# Execute hello command, check where the binary was installed
# Note:
#  1. $PATH includes ~/.nix-profile/bin
#  2. Files in ~/.nix-profile/bin/ really point to /nix/store/bin
hello
which hello
echo $PATH
ls -la $(which hello)

# List installed packages
nix-env -q
```

# Generations and rollback
```sh
# Nix uses generations (=revisions) of the system state that you can easily switch between
# Install 2 more packages (use separate lines to create separate generations)
nix-env -f '<nixpkgs>' -iA ripgrep
nix-env -f '<nixpkgs>' -iA jq

# List generations, rollback to prev generation (jq command won't work anymore)
nix-env --list-generations
nix-env --rollback
# Switch generations manually (in this case: roll forward, jq will work again)
nix-env --switch-generation 4

# Even when uninstalling a package, you can still rollback to a prev generation that does have it
nix-env --uninstall ripgrep
# rg doesn't work at this point
nix-env --rollback
# rg works again

# Actually clean up, remove uninstalled and unused packages
nix-collect-garbage
```

# Profiles

Profiles are isolated environments: packages installed in one profile are not available in a different profile.

Note: There seem to be some issues with the `nix-env` being unavailable after switching profiles
https://github.com/NixOS/nix/issues/1396
This is because `nix-env` is not installed globally if you're not using NixOS, but in the profile itself.
New profiles won't have the nix-env command, so you have to work around this by installing nix itself using the
`nix-env` command from the default profile


```sh
# In case you mess something up, use this command to switch back to the default profile
/nix/var/nix/profiles/per-user/vagrant/profile/bin/nix-env --switch-profile /nix/var/nix/profiles/per-user/vagrant/profile

# Switch to new profile
nix-env --switch-profile /nix/var/nix/profiles/newprofile
# Use nix-env command from default profile to install nix in new profile
/nix/var/nix/profiles/per-user/vagrant/profile/bin/nix-env -f '<nixpkgs>' -iA nix

# Profiles are completely isolated: any installation command will only affect the current profile
nix-env -f '<nixpkgs>' -iA bat

# Switching back to the old profile
nix-env --switch-profile /nix/var/nix/profiles/per-user/vagrant/profile
```


# Nixery
Ad-hoc container images that contain packages from the Nix package manager.
Images with arbitrary packages can be requested via the image name.
This is not an official part Nix, but a nice play on it.

```sh
# Start a docker container with shell, git and htop installed, run bash command
docker run -ti nixery.dev/shell/git/htop bash
# Same, but with commands switched around in image name. Shows that the order doesn't matter, same result
docker run -ti nixery.dev/shell/htop/git bash

# You can basically use anything that's available in the Nix packaging system
nerdctl run -ti nixery.dev/shell/python310/xsv/git/jq/gitlint/gcc gcc --version

# NOTE: "Meta-packages" automatically expands to several other packages and MUST be put first in the path name.
# currently only 2 meta packages: `shell` and `arm64`

# Example of piping some input into a NIX container running jq
curl -s "https://api.github.com/users/jorisroovers/repos" | docker run -i nixery.dev/shell/jq jq -r ".[].name "

# Note that you don't even have to include the 'shell' meta-package for many things to work:
curl -s "https://api.github.com/users/jorisroovers/repos" | docker run -i nixery.dev/jq jq ".[].name "
```