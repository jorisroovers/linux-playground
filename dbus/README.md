# DBus

## Doing RPC calls on NetworkManager
This will only work on the Centos VM, because the Ubuntu VM does not have NetworkManager installed.

```bash
python dbus_example.py
```

## Server
For this you first need to add the following line to ```/etc/dbus-1/system.conf```. This tells dbus to allow you to run
a service called ```org.me.test``` and send messages to it.
```xml
    <policy>
        ...
        <allow own="org.me.test" />
        <allow send_destination="org.me.test" />
    </policy>
```

Then reload the dbus service for the changes to take effect and start the server and client:
```bash
sudo systemctl reload dbus # centos
sudo service dbus reload # ubuntu
python dbus_server.py & # run this in the background
python dbus_client.py
```

## Other useful commands

```
# Print object model of the NetworkManager when using gdbus
gdbus introspect --system --dest org.freedesktop.NetworkManager --object-path /org/freedesktop/NetworkManager --recurse

# dbus-send allows you to explore with doing e.g. method calls without having to code
dbus-send --system --dest=org.freedesktop.DBus --type=method_call --print-reply \
/org/freedesktop/DBus org.freedesktop.DBus.ListNames

dbus-send --system --dest=org.freedesktop.NetworkManager --type=method_call --print-reply \
/org/freedesktop/NetworkManager org.freedesktop.NetworkManager.GetDevices
```