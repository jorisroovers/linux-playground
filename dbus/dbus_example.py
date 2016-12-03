import dbus

# https://georgemuraruc.wordpress.com/2015/07/16/d-bus-tutorial-for-python/

# Inspect dbus object
# gdbus introspect --system --dest org.freedesktop.NetworkManager --object-path /org/freedesktop/NetworkManager --recurse | less

# Systembus is a global bus started during boot, shared by everyone
# <-> Sessionbus, which is local to the user's DESKTOP session (you don't have access to a Sessionbus on a pure CLI app).
bus = dbus.SystemBus()

print "*" * 50
print "Services"
print "*" * 50
for service in dbus.SystemBus().list_names():
    print(service)
print "*" * 50

# using dbus-send:
# dbus-send --system --dest=org.freedesktop.NetworkManager --type=method_call --print-reply \
#  /org/freedesktop/NetworkManager org.freedesktop.NetworkManager.GetDevices

remote_object = bus.get_object('org.freedesktop.NetworkManager', '/org/freedesktop/NetworkManager')
remote_method = remote_object.get_dbus_method('GetDevices')
devices = remote_method()
print devices
