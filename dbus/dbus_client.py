import dbus

bus = dbus.SystemBus()
session = bus.get_object("org.me.test", "/org/me/test")

method_message1 = session.get_dbus_method('bus_message_1', 'org.me.test1')
method_message2 = session.get_dbus_method('bus_message_2', 'org.me.test2')

# Call the methods with their specific parameters
print(method_message1())
print(method_message2("Hello", "world"))
