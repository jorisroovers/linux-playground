from gi.repository import GLib
import dbus
import dbus.service
from dbus.mainloop.glib import DBusGMainLoop


class MyDBusService(dbus.service.Object):
    def __init__(self):
        # IMPORTANT: you can only use dbus.Systembus() here. Sessionbus is only supported when you have an actual
        # X11/desktop environment with sessions.
        bus_name = dbus.service.BusName('org.me.test', bus=dbus.SystemBus())
        dbus.service.Object.__init__(self, bus_name, '/org/me/test')

    # Interface and Method
    @dbus.service.method('org.me.test1')
    def bus_message_1(self):
        return "System Bus 1 method call return"

    # Method with arguments
    @dbus.service.method('org.me.test2')
    def bus_message_2(self, string1, string2):
        return string1 + " " + string2


DBusGMainLoop(set_as_default=True)
dbus_service = MyDBusService()

try:
    GLib.MainLoop().run()
except KeyboardInterrupt:
    print("\nThe MainLoop will close...")
    GLib.MainLoop().quit()
